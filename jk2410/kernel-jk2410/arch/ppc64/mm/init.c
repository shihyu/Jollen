/*
 *  
 *
 *  PowerPC version 
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Dave Engebretsen <engebret@us.ibm.com>
 *      Rework for PPC64 port.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 *
 */

#include <linux/config.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/ptrace.h>
#include <linux/mman.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/stddef.h>
#include <linux/vmalloc.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/bootmem.h>
#ifdef CONFIG_BLK_DEV_INITRD
#include <linux/blk.h>		/* for initrd_* */
#endif

#include <asm/pgalloc.h>
#include <asm/page.h>
#include <asm/abs_addr.h>
#include <asm/prom.h>
#include <asm/lmb.h>
#include <asm/rtas.h>
#include <asm/io.h>
#include <asm/mmu_context.h>
#include <asm/pgtable.h>
#include <asm/mmu.h>
#include <asm/uaccess.h>
#include <asm/smp.h>
#include <asm/machdep.h>
#include <asm/tlb.h>
#include <asm/Naca.h>

#include <asm/ppcdebug.h>

#define	PGTOKB(pages)	(((pages) * PAGE_SIZE) >> 10)

#ifdef CONFIG_PPC_ISERIES
#include <asm/iSeries/iSeries_dma.h>
#endif

struct mmu_context_stack_t mmu_context_stack;
int mem_init_done;
unsigned long ioremap_bot = IMALLOC_BASE;

static int boot_mapsize;
static unsigned long totalram_pages;
static struct device_node *memory_node;

extern pgd_t swapper_pg_dir[];
extern char __init_begin, __init_end;
extern char __chrp_begin, __chrp_end;
extern char __openfirmware_begin, __openfirmware_end;
extern struct _of_tce_table of_tce_table[];
extern char _start[], _end[];
extern char _stext[], etext[];
extern struct task_struct *current_set[NR_CPUS];
extern struct Naca *naca;

void mm_init_ppc64(void);

void make_pte(HPTE * htab,
              unsigned long va, unsigned long pa, 
              int mode, unsigned long hash_mask);

unsigned long *pmac_find_end_of_memory(void);
extern unsigned long *find_end_of_memory(void);

extern pgd_t ioremap_dir[];
extern pgd_t bolted_dir[];
pgd_t * ioremap_pgd = (pgd_t *)&ioremap_dir;
pgd_t * bolted_pgd  = (pgd_t *)&bolted_dir;

static void map_io_page(unsigned long va, unsigned long pa, int flags);
extern void die_if_kernel(char *,struct pt_regs *,long);

unsigned long klimit = (unsigned long)_end;

HPTE *Hash=0;
unsigned long Hash_size=0;
unsigned long _SDR1=0;
unsigned long _ASR=0;

/* max amount of RAM to use */
unsigned long __max_memory;

/* This is declared as we are using the more or less generic 
 * include/asm-ppc64/tlb.h file -- tgall
 */
mmu_gather_t     mmu_gathers[NR_CPUS];

int do_check_pgt_cache(int low, int high)
{
	int freed = 0;

	if (pgtable_cache_size > high) {
		do {
			if (pgd_quicklist)
				free_page((unsigned long)pgd_alloc_one_fast(0)), ++freed;
			if (pmd_quicklist)
				free_page((unsigned long)pmd_alloc_one_fast(0, 0)), ++freed;
			if (pte_quicklist)
				free_page((unsigned long)pte_alloc_one_fast(0, 0)), ++freed;
		} while (pgtable_cache_size > low);
	}
	return freed;	
}

void show_mem(void)
{
	int i,free = 0,total = 0,reserved = 0;
	int shared = 0, cached = 0;
	struct task_struct *p;

	printk("Mem-info:\n");
	show_free_areas();
	printk("Free swap:       %6dkB\n",nr_swap_pages<<(PAGE_SHIFT-10));
	i = max_mapnr;
	while (i-- > 0) {
		total++;
		if (PageReserved(mem_map+i))
			reserved++;
		else if (PageSwapCache(mem_map+i))
			cached++;
		else if (!atomic_read(&mem_map[i].count))
			free++;
		else
			shared += atomic_read(&mem_map[i].count) - 1;
	}
	printk("%d pages of RAM\n",total);
	printk("%d free pages\n",free);
	printk("%d reserved pages\n",reserved);
	printk("%d pages shared\n",shared);
	printk("%d pages swap cached\n",cached);
	printk("%d pages in page table cache\n",(int)pgtable_cache_size);
	show_buffers();
	printk("%-8s %3s %8s %8s %8s %9s %8s", "Process", "Pid",
	       "Ctx", "Ctx<<4", "Last Sys", "pc", "task");
#ifdef CONFIG_SMP
	printk(" %3s", "CPU");
#endif /* CONFIG_SMP */
	printk("\n");
	for_each_task(p)
	{
		printk("%-8.8s %3d %8ld %8ld %8ld %c%08lx %08lx ",
		       p->comm,p->pid,
		       (p->mm)?p->mm->context:0,
		       (p->mm)?(p->mm->context<<4):0,
		       p->thread.last_syscall,
		       (p->thread.regs)?user_mode(p->thread.regs) ? 'u' : 'k' : '?',
		       (p->thread.regs)?p->thread.regs->nip:0,
		       (ulong)p);
		{
			int iscur = 0;
#ifdef CONFIG_SMP
			printk("%3d ", p->processor);
			if ( (p->processor != NO_PROC_ID) &&
			     (p == current_set[p->processor]) )
			{
				iscur = 1;
				printk("current");
			}
#else
			if ( p == current )
			{
				iscur = 1;
				printk("current");
			}
			
			if ( p == last_task_used_math )
			{
				if ( iscur )
					printk(",");
				printk("last math");
			}			
#endif /* CONFIG_SMP */
			printk("\n");
		}
	}
}

void si_meminfo(struct sysinfo *val)
{
 	val->totalram = totalram_pages;
	val->sharedram = 0;
	val->freeram = nr_free_pages();
	val->bufferram = atomic_read(&buffermem_pages);
	val->totalhigh = 0;
	val->freehigh = 0;
	val->mem_unit = PAGE_SIZE;
}

void *
ioremap(unsigned long addr, unsigned long size)
{
	return __ioremap(addr, size, _PAGE_NO_CACHE);
}

extern struct vm_struct * get_im_area( unsigned long size );

void *
__ioremap(unsigned long addr, unsigned long size, unsigned long flags)
{
	unsigned long pa, ea, i;

	/*
	 * Choose an address to map it to.
	 * Once the imalloc system is running, we use it.
	 * Before that, we map using addresses going
	 * up from ioremap_bot.  imalloc will use
	 * the addresses from ioremap_bot through
	 * IMALLOC_END (0xE000001fffffffff)
	 * 
	 */
	pa = addr & PAGE_MASK;
	size = PAGE_ALIGN(addr + size) - pa;

	// MIKEC: Do we still need to support this?
	/*
	 * If the address lies within the first 16 MB, assume it's in ISA
	 * memory space
	 */
	if (pa < 16*1024*1024)
	    pa += _ISA_MEM_BASE;

	/*
	 * Don't allow anybody to remap normal RAM that we're using.
	 * mem_init() sets high_memory so only do the check after that.
	 */
#if 0  /* DRENG / PPPBBB assert to not remap DRAM is not right when I/O
        * space is in the middle of DRAM ranges ...
	*/
	if ( mem_init_done && (pa < virt_to_phys(high_memory)) )
	{
		printk("__ioremap(): phys addr %0lx is RAM lr %p\n", pa,
		       __builtin_return_address(0));
		return NULL;
	}
#endif
	if (size == 0)
		return NULL;

	if (mem_init_done) {
		struct vm_struct *area;
		area = get_im_area(size);
		if (area == 0)
			return NULL;
		ea = (unsigned long)(area->addr);
	} 
	else {
		ea = ioremap_bot;
		ioremap_bot += size;
        }

	if ((flags & _PAGE_PRESENT) == 0)
		flags |= pgprot_val(PAGE_KERNEL);
	if (flags & (_PAGE_NO_CACHE | _PAGE_WRITETHRU))
		flags |= _PAGE_GUARDED;

	for (i = 0; i < size; i += PAGE_SIZE) {
		map_io_page(ea+i, pa+i, flags);
	}

	return (void *) (ea + (addr & ~PAGE_MASK));
}

void iounmap(void *addr)
{
	/* DRENG / PPPBBB todo */
}

unsigned long iopa(unsigned long addr)
{
	pmd_t *pd;
	pte_t *pg;

	/* Do we have a page table? */
	if (init_mm.pgd == NULL)
		return 0;

	/* Use upper 10 bits of addr to index the first level map */
	pd = (pmd_t *) (init_mm.pgd + (addr >> PGDIR_SHIFT));
	if (pmd_none(*pd))
		return 0;

	/* Use middle 10 bits of addr to index the second-level map */
	pg = pte_offset(pd, addr);
	return (pte_val(*pg) & PAGE_MASK) | (addr & ~PAGE_MASK);
}

/*
 * map_io_page currently only called by __ioremap
 * map_io_page adds an entry to the ioremap page table
 * and adds an entry to the HPT, possibly bolting it
 */
static void map_io_page(unsigned long ea, unsigned long pa, int flags)
{
	pgd_t *pgdp;
	pmd_t *pmdp;
	pte_t *ptep;
	unsigned long vsid;
	
	if (mem_init_done) {
		spin_lock(&init_mm.page_table_lock);
		pgdp = pgd_offset_i(ea);
		pmdp = pmd_alloc(&init_mm, pgdp, ea);
		ptep = pte_alloc(&init_mm, pmdp, ea);
		set_pte(ptep, mk_pte_phys(pa & PAGE_MASK, __pgprot(flags)));
		spin_unlock(&init_mm.page_table_lock);
	} else {
		/* If the mm subsystem is not fully up, we cannot create a
		 * linux page table entry for this mapping.  Simply bolt an
		 * entry in the hardware page table. 
 		 */
		vsid = get_kernel_vsid(ea);
		make_pte(htab_data.htab,
			(vsid << 28) | (ea & 0xFFFFFFF), // va (NOT the ea)
			pa, 
			_PAGE_NO_CACHE | _PAGE_GUARDED | PP_RWXX,
			htab_data.htab_hash_mask); 
	}
}

void
local_flush_tlb_all(void)
{
	/* Implemented to just flush the vmalloc area.
	 * vmalloc is the only user of flush_tlb_all.
	 */
	local_flush_tlb_range( NULL, VMALLOC_START, VMALLOC_END );
}

void
local_flush_tlb_mm(struct mm_struct *mm)
{
	if ( mm->map_count ) {
		struct vm_area_struct *mp;
		for ( mp = mm->mmap; mp != NULL; mp = mp->vm_next )
			local_flush_tlb_range( mm, mp->vm_start, mp->vm_end );
	}
	else	/* MIKEC: It is not clear why this is needed */
		local_flush_tlb_range( mm, USER_START, USER_END );
}


/*
 * Callers should hold the mm->page_table_lock
 */
void
local_flush_tlb_page(struct vm_area_struct *vma, unsigned long vmaddr)
{
	unsigned long context = 0;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *ptep;
	pte_t pte;
	
	switch( REGION_ID(vmaddr) ) {
	case VMALLOC_REGION_ID:
		pgd = pgd_offset_k( vmaddr );
		break;
	case IO_REGION_ID:
		pgd = pgd_offset_i( vmaddr );
		break;
	case BOLTED_REGION_ID:
		pgd = pgd_offset_b( vmaddr );
		break;
	case USER_REGION_ID:
		pgd = pgd_offset( vma->vm_mm, vmaddr );
		context = vma->vm_mm->context;
		break;
	default:
		panic("local_flush_tlb_page: invalid region 0x%016lx", vmaddr);
	
	}


	if (!pgd_none(*pgd)) {
		pmd = pmd_offset(pgd, vmaddr);
		if (!pmd_none(*pmd)) {
			ptep = pte_offset(pmd, vmaddr);
			/* Check if HPTE might exist and flush it if so */
			pte = __pte(pte_update(ptep, _PAGE_HPTEFLAGS, 0));
			if ( pte_val(pte) & _PAGE_HASHPTE ) {
				flush_hash_page(context, vmaddr, pte);
			}
		}
	}
}

void
local_flush_tlb_range(struct mm_struct *mm, unsigned long start, unsigned long end)
{
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *ptep;
	pte_t pte;
	unsigned long pgd_end, pmd_end;
	unsigned long context;

	if ( start >= end )
		panic("flush_tlb_range: start (%016lx) greater than end (%016lx)\n", start, end );

	if ( REGION_ID(start) != REGION_ID(end) )
		panic("flush_tlb_range: start (%016lx) and end (%016lx) not in same region\n", start, end );
	
	context = 0;

	switch( REGION_ID(start) ) {
	case VMALLOC_REGION_ID:
		pgd = pgd_offset_k( start );
		break;
	case IO_REGION_ID:
		pgd = pgd_offset_i( start );
		break;
	case BOLTED_REGION_ID:
		pgd = pgd_offset_b( start );
		break;
	case USER_REGION_ID:
		pgd = pgd_offset( mm, start );
		context = mm->context;
		break;
	default:
		panic("flush_tlb_range: invalid region for start (%016lx) and end (%016lx)\n", start, end);
	
	}

	do {
		pgd_end = (start + PGDIR_SIZE) & PGDIR_MASK;
		if ( pgd_end > end ) 
			pgd_end = end;
		if ( !pgd_none( *pgd ) ) {
			pmd = pmd_offset( pgd, start );
			do {
				pmd_end = ( start + PMD_SIZE ) & PMD_MASK;
				if ( pmd_end > end )
					pmd_end = end;
				if ( !pmd_none( *pmd ) ) {
					ptep = pte_offset( pmd, start );
					do {
						if ( pte_val(*ptep) & _PAGE_HASHPTE ) {
							pte = __pte(pte_update(ptep, _PAGE_HPTEFLAGS, 0));
							if ( pte_val(pte) & _PAGE_HASHPTE )
								flush_hash_page( context, start, pte );
						}
						start += PAGE_SIZE;
						++ptep;
					} while ( start < pmd_end );
				}
				else
					start = pmd_end;
				++pmd;
			} while ( start < pgd_end );
		}
		else
			start = pgd_end;
		++pgd;
	} while ( start < end );
}


void __init free_initmem(void)
{
	unsigned long a;
	unsigned long num_freed_pages = 0;
#define FREESEC(START,END,CNT) do { \
	a = (unsigned long)(&START); \
	for (; a < (unsigned long)(&END); a += PAGE_SIZE) { \
	  	clear_bit(PG_reserved, &mem_map[MAP_NR(a)].flags); \
		set_page_count(mem_map+MAP_NR(a), 1); \
		free_page(a); \
		CNT++; \
	} \
} while (0)

	FREESEC(__init_begin,__init_end,num_freed_pages);

	printk ("Freeing unused kernel memory: %ldk init\n",
		PGTOKB(num_freed_pages));
}

#ifdef CONFIG_BLK_DEV_INITRD
void free_initrd_mem(unsigned long start, unsigned long end)
{
	for (; start < end; start += PAGE_SIZE) {
		ClearPageReserved(mem_map + MAP_NR(start));
		set_page_count(mem_map+MAP_NR(start), 1);
		free_page(start);
		totalram_pages++;
	}
	printk ("Freeing initrd memory: %ldk freed\n", (end - start) >> 10);
}
#endif


/* Reserve all contexts < FIRST_USER_CONTEXT for kernel use.
 * The range of contexts [FIRST_USER_CONTEXT, NUM_USER_CONTEXT)
 * are stored on a stack for easy allocation and deallocation.
 */
void
init_context_stack(void)
{
        mm_context_t top;

        mmu_context_stack.lock = SPIN_LOCK_UNLOCKED;
        mmu_context_stack.top = FIRST_USER_CONTEXT;
        for(top=0; top < FIRST_USER_CONTEXT ;top++) {
                mmu_context_stack.stack[top] = NO_CONTEXT;
        }
        for(top=FIRST_USER_CONTEXT; top < NUM_USER_CONTEXT ;top++) {
                mmu_context_stack.stack[top] = top;
        }
}


/*
 * Do very early mm setup.
 */
void __init mm_init_ppc64(void) {
	ppc_md.progress("MM:init", 0);

	/* Reserve all contexts < FIRST_USER_CONTEXT for kernel use.
	 * The range of contexts [FIRST_USER_CONTEXT, NUM_USER_CONTEXT)
	 * are stored on a stack for easy allocation and deallocation.
	 */
	init_context_stack();

	ppc_md.progress("MM:exit", 0x211);
}



/*
 * Initialize the bootmem system and give it all the memory we
 * have available.
 */
void __init do_init_bootmem(void)
{
	unsigned long i;
	unsigned long start, bootmap_pages;
	unsigned long total_pages = lmb_end_of_DRAM() >> PAGE_SHIFT;

	PPCDBG(PPCDBG_MMINIT, "do_init_bootmem: start\n");
	/*
	 * Find an area to use for the bootmem bitmap.  Calculate the size of
	 * bitmap required as (Total Memory) / PAGE_SIZE / BITS_PER_BYTE.
	 * Add 1 additional page in case the address isn't page-aligned.
	 */
	bootmap_pages = bootmem_bootmap_pages(total_pages);

	start = (unsigned long)__a2p(lmb_alloc(bootmap_pages<<PAGE_SHIFT, PAGE_SIZE));
	if( start == 0 ) {
		udbg_printf("do_init_bootmem: failed to allocate a bitmap.\n");
		udbg_printf("\tbootmap_pages = 0x%lx.\n", bootmap_pages);
		PPCDBG_ENTER_DEBUGGER(); 
	}

	PPCDBG(PPCDBG_MMINIT, "\tstart               = 0x%lx\n", start);
	PPCDBG(PPCDBG_MMINIT, "\tbootmap_pages       = 0x%lx\n", bootmap_pages);
	PPCDBG(PPCDBG_MMINIT, "\tphysicalMemorySize  = 0x%lx\n", naca->physicalMemorySize);

	boot_mapsize = init_bootmem(start >> PAGE_SHIFT, total_pages);
	PPCDBG(PPCDBG_MMINIT, "\tboot_mapsize        = 0x%lx\n", boot_mapsize);

	/* add all physical memory to the bootmem map */
	for (i=0; i < lmb.memory.cnt ;i++) {
		unsigned long physbase = lmb.memory.region[i].physbase;
		unsigned long size = lmb.memory.region[i].size;
		free_bootmem(physbase, size);
	}
	/* reserve the sections we're already using */
	for (i=0; i < lmb.reserved.cnt ;i++) {
		unsigned long physbase = lmb.reserved.region[i].physbase;
		unsigned long size = lmb.reserved.region[i].size;
#if 0 /* PPPBBB */
		if ( (physbase == 0) && (size < (16<<20)) ) {
			size = 16 << 20;
		}
#endif
		reserve_bootmem(physbase, size);
	}

	PPCDBG(PPCDBG_MMINIT, "do_init_bootmem: end\n");
}

/*
 * paging_init() sets up the page tables - in fact we've already done this.
 */
void __init paging_init(void)
{
	unsigned long zones_size[MAX_NR_ZONES], i;

	/*
	 * All pages are DMA-able so we put them all in the DMA zone.
	 */
	zones_size[0] = lmb_end_of_DRAM() >> PAGE_SHIFT;
	for (i = 1; i < MAX_NR_ZONES; i++)
		zones_size[i] = 0;
	free_area_init(zones_size);
}

void __init mem_init(void)
{
	extern char *sysmap; 
	extern unsigned long sysmap_size;
	unsigned long addr;
	int codepages = 0;
	int datapages = 0;
	int initpages = 0;
	unsigned long va_rtas_base = (unsigned long)__va(rtas.base);
	max_mapnr = max_low_pfn;
	high_memory = (void *) __va(max_low_pfn * PAGE_SIZE);
	num_physpages = max_mapnr;	/* RAM is assumed contiguous */

	totalram_pages += free_all_bootmem();

	ifppcdebug(PPCDBG_MMINIT) {
		udbg_printf("mem_init: totalram_pages = 0x%lx\n", totalram_pages);
		udbg_printf("mem_init: va_rtas_base   = 0x%lx\n", va_rtas_base); 
		udbg_printf("mem_init: va_rtas_end    = 0x%lx\n", PAGE_ALIGN(va_rtas_base+rtas.size)); 
		udbg_printf("mem_init: pinned start   = 0x%lx\n", __va(0)); 
		udbg_printf("mem_init: pinned end     = 0x%lx\n", PAGE_ALIGN(klimit)); 
	}

	if ( sysmap_size )
		for (addr = (unsigned long)sysmap;
		     addr < PAGE_ALIGN((unsigned long)sysmap+sysmap_size) ;
		     addr += PAGE_SIZE)
			SetPageReserved(mem_map + MAP_NR(addr));
	
	for (addr = KERNELBASE; addr <= (unsigned long)__va(lmb_end_of_DRAM());
	     addr += PAGE_SIZE) {
		if (!PageReserved(mem_map + MAP_NR(addr)))
			continue;
		if (addr < (ulong) etext)
			codepages++;

		else if (addr >= (unsigned long)&__init_begin
			 && addr < (unsigned long)&__init_end)
			initpages++;
		else if (addr < klimit)
			datapages++;
	}

        printk("Memory: %luk available (%dk kernel code, %dk data, %dk init) [%08lx,%08lx]\n",
	       (unsigned long)nr_free_pages()<< (PAGE_SHIFT-10),
	       codepages<< (PAGE_SHIFT-10), datapages<< (PAGE_SHIFT-10),
	       initpages<< (PAGE_SHIFT-10),
	       PAGE_OFFSET, __va(lmb_end_of_DRAM()));
	mem_init_done = 1;

#ifdef CONFIG_PPC_ISERIES
	create_virtual_bus_tce_table();
#endif
}
