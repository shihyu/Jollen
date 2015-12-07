/*
 * Automatically generated by make menuconfig: don't edit
 */
#define AUTOCONF_INCLUDED
#define CONFIG_ARM 1
#undef  CONFIG_EISA
#undef  CONFIG_SBUS
#undef  CONFIG_MCA
#define CONFIG_UID16 1
#define CONFIG_RWSEM_GENERIC_SPINLOCK 1
#undef  CONFIG_RWSEM_XCHGADD_ALGORITHM
#undef  CONFIG_GENERIC_BUST_SPINLOCK
#undef  CONFIG_GENERIC_ISA_DMA

/*
 * Code maturity level options
 */
#define CONFIG_EXPERIMENTAL 1
#undef  CONFIG_OBSOLETE

/*
 * Loadable module support
 */
#define CONFIG_MODULES 1
#undef  CONFIG_MODVERSIONS
#define CONFIG_KMOD 1

/*
 * System Type
 */
#undef  CONFIG_ARCH_ANAKIN
#undef  CONFIG_ARCH_ARCA5K
#undef  CONFIG_ARCH_CLPS7500
#undef  CONFIG_ARCH_CLPS711X
#undef  CONFIG_ARCH_CO285
#undef  CONFIG_ARCH_PXA
#undef  CONFIG_ARCH_EBSA110
#undef  CONFIG_ARCH_CAMELOT
#undef  CONFIG_ARCH_FOOTBRIDGE
#undef  CONFIG_ARCH_INTEGRATOR
#undef  CONFIG_ARCH_L7200
#undef  CONFIG_ARCH_MX1ADS
#undef  CONFIG_ARCH_RPC
#undef  CONFIG_ARCH_SA1100
#undef  CONFIG_ARCH_S3C2400
#define CONFIG_ARCH_S3C2410 1
#undef  CONFIG_ARCH_SHARK
#undef  CONFIG_ARCH_LUBBOCK
#undef  CONFIG_ARCH_PXA_IDP
#undef  CONFIG_ARCH_PXA_CERF
#undef  CONFIG_ARCH_PREMIUM
#undef  CONFIG_ARCH_NIPC2
#undef  CONFIG_ARCH_AUTCPU12
#undef  CONFIG_ARCH_CDB89712
#undef  CONFIG_ARCH_CLEP7312
#undef  CONFIG_ARCH_EDB7211
#undef  CONFIG_ARCH_P720T
#undef  CONFIG_ARCH_FORTUNET
#define CONFIG_S3C2410_SMDK 1
#define CONFIG_SMDK_AIJI 1
#undef  CONFIG_S3C2410_USB
#undef  CONFIG_S3C2410_USB_CHAR
#undef  CONFIG_ARCH_ACORN
#undef  CONFIG_FOOTBRIDGE
#undef  CONFIG_FOOTBRIDGE_HOST
#undef  CONFIG_FOOTBRIDGE_ADDIN
#define CONFIG_CPU_32 1
#undef  CONFIG_CPU_26
#undef  CONFIG_CPU_32v3
#define CONFIG_CPU_32v4 1
#undef  CONFIG_CPU_ARM610
#undef  CONFIG_CPU_ARM710
#undef  CONFIG_CPU_ARM720T
#define CONFIG_CPU_ARM920T 1
#define CONFIG_CPU_ARM920_CPU_IDLE 1
#define CONFIG_CPU_ARM920_I_CACHE_ON 1
#define CONFIG_CPU_ARM920_D_CACHE_ON 1
#undef  CONFIG_CPU_ARM920_WRITETHROUGH
#undef  CONFIG_CPU_ARM922T
#undef  CONFIG_CPU_ARM926T
#undef  CONFIG_CPU_ARM1020
#undef  CONFIG_CPU_SA110
#undef  CONFIG_CPU_SA1100
#undef  CONFIG_ARM_THUMB
#undef  CONFIG_DISCONTIGMEM

/*
 * General setup
 */
#define CONFIG_MIZI 1
#undef  CONFIG_PCI
#define CONFIG_ISA 1
#undef  CONFIG_ISA_DMA
#undef  CONFIG_ZBOOT_ROM
#define CONFIG_ZBOOT_ROM_TEXT 0x0
#define CONFIG_ZBOOT_ROM_BSS 0x0
#define CONFIG_HOTPLUG 1

/*
 * PCMCIA/CardBus support
 */
#undef  CONFIG_PCMCIA
#define CONFIG_PCMCIA_MODULE 1
#define CONFIG_PCMCIA_PROBE 1
#undef  CONFIG_I82092
#define CONFIG_I82365 1
#undef  CONFIG_TCIC
#undef  CONFIG_PCMCIA_CLPS6700
#undef  CONFIG_PCMCIA_SA1100
#undef  CONFIG_PCMCIA_PXA
#define CONFIG_NET 1
#define CONFIG_SYSVIPC 1
#undef  CONFIG_BSD_PROCESS_ACCT
#define CONFIG_SYSCTL 1
#define CONFIG_FPE_NWFPE 1
#undef  CONFIG_FPE_FASTFPE
#define CONFIG_KCORE_ELF 1
#undef  CONFIG_KCORE_AOUT
#undef  CONFIG_BINFMT_AOUT
#define CONFIG_BINFMT_ELF 1
#undef  CONFIG_BINFMT_MISC
#undef  CONFIG_PM
#undef  CONFIG_APM
#undef  CONFIG_CONSOLE_PM
#undef  CONFIG_NO_OOM_KILLER
#undef  CONFIG_REDUCE_TTY_MODULAR
#undef  CONFIG_ARTHUR
#undef  CONFIG_NO_TAG_CMDLINE
#define CONFIG_CMDLINE "mem=64M console=ttyS0,115200"
#undef  CONFIG_LEDS
#define CONFIG_ALIGNMENT_TRAP 1

/*
 * Parallel port support
 */
#undef  CONFIG_PARPORT

/*
 * Memory Technology Devices (MTD)
 */
#define CONFIG_MTD 1
#undef  CONFIG_MTD_DEBUG
#define CONFIG_MTD_PARTITIONS 1
#undef  CONFIG_MTD_CONCAT
#undef  CONFIG_MTD_REDBOOT_PARTS
#define CONFIG_MTD_CMDLINE_PARTS 1
#undef  CONFIG_MTD_AFS_PARTS
#define CONFIG_MTD_CHAR 1
#define CONFIG_MTD_BLOCK 1
#define CONFIG_FTL 1
#define CONFIG_NFTL 1
#define CONFIG_NFTL_RW 1

/*
 * RAM/ROM/Flash chip drivers
 */
#define CONFIG_MTD_CFI 1
#undef  CONFIG_MTD_JEDECPROBE
#define CONFIG_MTD_GEN_PROBE 1
#define CONFIG_MTD_CFI_ADV_OPTIONS 1
#define CONFIG_MTD_CFI_NOSWAP 1
#undef  CONFIG_MTD_CFI_BE_BYTE_SWAP
#undef  CONFIG_MTD_CFI_LE_BYTE_SWAP
#undef  CONFIG_MTD_CFI_GEOMETRY
#undef  CONFIG_MTD_CFI_INTELEXT
#undef  CONFIG_MTD_CFI_AMDSTD
#undef  CONFIG_MTD_RAM
#undef  CONFIG_MTD_ROM
#undef  CONFIG_MTD_ABSENT
#undef  CONFIG_MTD_OBSOLETE_CHIPS
#undef  CONFIG_MTD_AMDSTD
#undef  CONFIG_MTD_SHARP
#undef  CONFIG_MTD_JEDEC

/*
 * Mapping drivers for chip access
 */
#undef  CONFIG_MTD_PHYSMAP
#undef  CONFIG_MTD_ARM_INTEGRATOR
#undef  CONFIG_MTD_CDB89712
#undef  CONFIG_MTD_SA1100
#undef  CONFIG_MTD_DC21285
#undef  CONFIG_MTD_LUBBOCK
#undef  CONFIG_MTD_FORTUNET
#undef  CONFIG_MTD_EPXA10DB
#undef  CONFIG_MTD_PXA_CERF
#undef  CONFIG_MTD_AUTCPU12
#undef  CONFIG_MTD_PCI

/*
 * Self-contained MTD device drivers
 */
#undef  CONFIG_MTD_PMC551
#undef  CONFIG_MTD_SLRAM
#undef  CONFIG_MTD_MTDRAM
#undef  CONFIG_MTD_BLKMTD
#undef  CONFIG_MTD_DOC1000
#undef  CONFIG_MTD_DOC2000
#undef  CONFIG_MTD_DOC2001
#undef  CONFIG_MTD_DOCPROBE

/*
 * NAND Flash Device Drivers
 */
#define CONFIG_MTD_NAND 1
#define CONFIG_MTD_NAND_ECC 1
#define CONFIG_MTD_NAND_VERIFY_WRITE 1
#define CONFIG_MTD_NAND_ECC_JFFS2 1
#undef  CONFIG_MTD_SMC
#undef  CONFIG_MTD_NANDY

/*
 * Plug and Play configuration
 */
#undef  CONFIG_PNP
#undef  CONFIG_ISAPNP

/*
 * Block devices
 */
#undef  CONFIG_BLK_DEV_FD
#undef  CONFIG_BLK_DEV_XD
#undef  CONFIG_PARIDE
#undef  CONFIG_BLK_CPQ_DA
#undef  CONFIG_BLK_CPQ_CISS_DA
#undef  CONFIG_BLK_DEV_DAC960
#define CONFIG_BLK_DEV_LOOP 1
#define CONFIG_BLK_DEV_NBD 1
#define CONFIG_BLK_DEV_RAM 1
#define CONFIG_BLK_DEV_RAM_SIZE (4096)
#define CONFIG_BLK_DEV_INITRD 1

/*
 * Multi-device support (RAID and LVM)
 */
#undef  CONFIG_MD
#undef  CONFIG_BLK_DEV_MD
#undef  CONFIG_MD_LINEAR
#undef  CONFIG_MD_RAID0
#undef  CONFIG_MD_RAID1
#undef  CONFIG_MD_RAID5
#undef  CONFIG_MD_MULTIPATH
#undef  CONFIG_BLK_DEV_LVM

/*
 * Networking options
 */
#define CONFIG_PACKET 1
#define CONFIG_PACKET_MMAP 1
#undef  CONFIG_NETLINK_DEV
#undef  CONFIG_NETFILTER
#undef  CONFIG_FILTER
#define CONFIG_UNIX 1
#define CONFIG_INET 1
#define CONFIG_IP_MULTICAST 1
#undef  CONFIG_IP_ADVANCED_ROUTER
#undef  CONFIG_IP_PNP
#undef  CONFIG_NET_IPIP
#undef  CONFIG_NET_IPGRE
#undef  CONFIG_IP_MROUTE
#undef  CONFIG_ARPD
#undef  CONFIG_INET_ECN
#undef  CONFIG_SYN_COOKIES
#undef  CONFIG_IPV6
#undef  CONFIG_KHTTPD
#undef  CONFIG_ATM
#undef  CONFIG_VLAN_8021Q
#undef  CONFIG_IPX
#undef  CONFIG_ATALK
#undef  CONFIG_DECNET
#undef  CONFIG_BRIDGE
#undef  CONFIG_X25
#undef  CONFIG_LAPB
#undef  CONFIG_LLC
#undef  CONFIG_NET_DIVERT
#undef  CONFIG_ECONET
#undef  CONFIG_WAN_ROUTER
#undef  CONFIG_NET_FASTROUTE
#undef  CONFIG_NET_HW_FLOWCONTROL

/*
 * QoS and/or fair queueing
 */
#undef  CONFIG_NET_SCHED

/*
 * Network device support
 */
#define CONFIG_NETDEVICES 1

/*
 * ARCnet devices
 */
#undef  CONFIG_ARCNET
#define CONFIG_DUMMY 1
#undef  CONFIG_BONDING
#undef  CONFIG_EQUALIZER
#undef  CONFIG_TUN
#undef  CONFIG_ETHERTAP

/*
 * Ethernet (10 or 100Mbit)
 */
#define CONFIG_NET_ETHERNET 1
#undef  CONFIG_ARM_AM79C961A
#undef  CONFIG_SUNLANCE
#undef  CONFIG_SUNBMAC
#undef  CONFIG_SUNQE
#undef  CONFIG_SUNGEM
#undef  CONFIG_NET_VENDOR_3COM
#undef  CONFIG_LANCE
#undef  CONFIG_NET_VENDOR_SMC
#undef  CONFIG_NET_VENDOR_RACAL
#undef  CONFIG_AT1700
#undef  CONFIG_DEPCA
#undef  CONFIG_HP100
#undef  CONFIG_NET_ISA
#define CONFIG_NET_PCI 1
#undef  CONFIG_PCNET32
#undef  CONFIG_ADAPTEC_STARFIRE
#undef  CONFIG_AC3200
#undef  CONFIG_APRICOT
#undef  CONFIG_CS89x0
#define CONFIG_CERF_CS8900A 1
#undef  CONFIG_TULIP
#undef  CONFIG_DM9102
#undef  CONFIG_EEPRO100
#undef  CONFIG_LNE390
#undef  CONFIG_FEALNX
#undef  CONFIG_NATSEMI
#undef  CONFIG_NE2K_PCI
#undef  CONFIG_NE3210
#undef  CONFIG_ES3210
#undef  CONFIG_8139CP
#undef  CONFIG_8139TOO
#undef  CONFIG_8139TOO_PIO
#undef  CONFIG_8139TOO_TUNE_TWISTER
#undef  CONFIG_8139TOO_8129
#undef  CONFIG_8139_NEW_RX_RESET
#undef  CONFIG_SIS900
#undef  CONFIG_EPIC100
#undef  CONFIG_SUNDANCE
#undef  CONFIG_VIA_RHINE
#undef  CONFIG_VIA_RHINE_MMIO
#undef  CONFIG_WINBOND_840
#undef  CONFIG_NET_POCKET

/*
 * Ethernet (1000 Mbit)
 */
#undef  CONFIG_ACENIC
#undef  CONFIG_DL2K
#undef  CONFIG_MYRI_SBUS
#undef  CONFIG_NS83820
#undef  CONFIG_HAMACHI
#undef  CONFIG_YELLOWFIN
#undef  CONFIG_SK98LIN
#undef  CONFIG_FDDI
#undef  CONFIG_HIPPI
#undef  CONFIG_PLIP
#undef  CONFIG_PPP
#undef  CONFIG_SLIP

/*
 * Wireless LAN (non-hamradio)
 */
#define CONFIG_NET_RADIO 1
#undef  CONFIG_STRIP
#undef  CONFIG_WAVELAN
#undef  CONFIG_ARLAN
#undef  CONFIG_AIRONET4500
#undef  CONFIG_AIRONET4500_NONCS
#undef  CONFIG_AIRONET4500_PROC
#undef  CONFIG_AIRO
#undef  CONFIG_HERMES
#define CONFIG_HERMES_MODULE 1
#undef  CONFIG_PCMCIA_HERMES
#define CONFIG_PCMCIA_HERMES_MODULE 1
#undef  CONFIG_AIRO_CS
#define CONFIG_NET_WIRELESS 1

/*
 * Token Ring devices
 */
#undef  CONFIG_TR
#undef  CONFIG_NET_FC
#undef  CONFIG_RCPCI
#undef  CONFIG_SHAPER

/*
 * Wan interfaces
 */
#undef  CONFIG_WAN

/*
 * PCMCIA network device support
 */
#define CONFIG_NET_PCMCIA 1
#undef  CONFIG_PCMCIA_3C589
#define CONFIG_PCMCIA_3C589_MODULE 1
#undef  CONFIG_PCMCIA_3C574
#define CONFIG_PCMCIA_3C574_MODULE 1
#undef  CONFIG_PCMCIA_FMVJ18X
#undef  CONFIG_PCMCIA_PCNET
#define CONFIG_PCMCIA_PCNET_MODULE 1
#undef  CONFIG_PCMCIA_AXNET
#undef  CONFIG_PCMCIA_NMCLAN
#undef  CONFIG_PCMCIA_SMC91C92
#undef  CONFIG_PCMCIA_XIRC2PS
#define CONFIG_PCMCIA_XIRC2PS_MODULE 1
#undef  CONFIG_ARCNET_COM20020_CS
#undef  CONFIG_PCMCIA_IBMTR
#undef  CONFIG_NET_PCMCIA_RADIO

/*
 * Amateur Radio support
 */
#undef  CONFIG_HAMRADIO

/*
 * IrDA (infrared) support
 */
#undef  CONFIG_IRDA
#define CONFIG_IRDA_MODULE 1
#undef  CONFIG_IRLAN
#undef  CONFIG_IRNET
#undef  CONFIG_IRCOMM
#undef  CONFIG_IRDA_ULTRA
#define CONFIG_IRDA_CACHE_LAST_LSAP 1
#define CONFIG_IRDA_FAST_RR 1
#define CONFIG_IRDA_DEBUG 1

/*
 * Infrared-port device drivers
 */
#undef  CONFIG_IRTTY_SIR
#define CONFIG_IRTTY_SIR_MODULE 1
#undef  CONFIG_IRPORT_SIR
#define CONFIG_DONGLE 1
#undef  CONFIG_ESI_DONGLE
#undef  CONFIG_ACTISYS_DONGLE
#undef  CONFIG_TEKRAM_DONGLE
#undef  CONFIG_GIRBIL_DONGLE
#undef  CONFIG_LITELINK_DONGLE
#undef  CONFIG_OLD_BELKIN_DONGLE
#undef  CONFIG_S3C2410_IR
#define CONFIG_S3C2410_IR_MODULE 1
#undef  CONFIG_USB_IRDA
#undef  CONFIG_NSC_FIR
#undef  CONFIG_WINBOND_FIR
#undef  CONFIG_TOSHIBA_FIR
#undef  CONFIG_SMC_IRCC_FIR
#undef  CONFIG_ALI_FIR
#undef  CONFIG_VLSI_FIR

/*
 * ATA/IDE/MFM/RLL support
 */
#undef  CONFIG_IDE
#undef  CONFIG_BLK_DEV_IDE_MODES
#undef  CONFIG_BLK_DEV_HD

/*
 * SCSI support
 */
#undef  CONFIG_SCSI

/*
 * I2O device support
 */
#undef  CONFIG_I2O
#undef  CONFIG_I2O_BLOCK
#undef  CONFIG_I2O_LAN
#undef  CONFIG_I2O_SCSI
#undef  CONFIG_I2O_PROC

/*
 * ISDN subsystem
 */
#undef  CONFIG_ISDN

/*
 * Input core support
 */
#define CONFIG_INPUT 1
#define CONFIG_INPUT_KEYBDEV 1
#define CONFIG_INPUT_MOUSEDEV 1
#define CONFIG_INPUT_MOUSEDEV_SCREEN_X (640)
#define CONFIG_INPUT_MOUSEDEV_SCREEN_Y (480)
#undef  CONFIG_INPUT_JOYDEV
#undef  CONFIG_INPUT_EVDEV

/*
 * Character devices
 */
#define CONFIG_VT 1
#define CONFIG_VT_CONSOLE 1
#undef  CONFIG_SERIAL
#undef  CONFIG_SERIAL_EXTENDED
#undef  CONFIG_SERIAL_NONSTANDARD

/*
 * Serial drivers
 */
#undef  CONFIG_SERIAL_ANAKIN
#undef  CONFIG_SERIAL_ANAKIN_CONSOLE
#undef  CONFIG_SERIAL_AMBA
#undef  CONFIG_SERIAL_AMBA_CONSOLE
#undef  CONFIG_SERIAL_CLPS711X
#undef  CONFIG_SERIAL_CLPS711X_CONSOLE
#undef  CONFIG_SERIAL_21285
#undef  CONFIG_SERIAL_21285_OLD
#undef  CONFIG_SERIAL_21285_CONSOLE
#undef  CONFIG_SERIAL_UART00
#undef  CONFIG_SERIAL_UART00_CONSOLE
#undef  CONFIG_SERIAL_SA1100
#undef  CONFIG_SERIAL_SA1100_CONSOLE
#undef  CONFIG_SERIAL_S3C2400
#undef  CONFIG_SERIAL_S3C2400_CONSOLE
#define CONFIG_SERIAL_S3C2410 1
#define CONFIG_SERIAL_S3C2410_CONSOLE 1
#undef  CONFIG_SERIAL_8250
#undef  CONFIG_SERIAL_8250_CONSOLE
#undef  CONFIG_SERIAL_8250_EXTENDED
#undef  CONFIG_SERIAL_8250_MANY_PORTS
#undef  CONFIG_SERIAL_8250_SHARE_IRQ
#undef  CONFIG_SERIAL_8250_DETECT_IRQ
#undef  CONFIG_SERIAL_8250_MULTIPORT
#undef  CONFIG_SERIAL_8250_HUB6
#define CONFIG_SERIAL_CORE 1
#define CONFIG_SERIAL_CORE_CONSOLE 1
#undef  CONFIG_S3C2410_TOUCHSCREEN
#undef  CONFIG_S3C2410_GPIO_BUTTONS
#undef  CONFIG_JK2410_GPIO
#undef  CONFIG_JK2410_LED
#define CONFIG_UNIX98_PTYS 1
#define CONFIG_UNIX98_PTY_COUNT (256)

/*
 * I2C support
 */
#undef  CONFIG_I2C

/*
 * L3 serial bus support
 */
#undef  CONFIG_L3
#undef  CONFIG_L3_ALGOBIT
#undef  CONFIG_L3_BIT_SA1100_GPIO
#undef  CONFIG_L3_SA1111
#undef  CONFIG_BIT_SA1100_GPIO

/*
 * Mice
 */
#undef  CONFIG_BUSMOUSE
#undef  CONFIG_MOUSE

/*
 * Joysticks
 */
#undef  CONFIG_INPUT_GAMEPORT
#undef  CONFIG_INPUT_NS558
#undef  CONFIG_INPUT_LIGHTNING
#undef  CONFIG_INPUT_PCIGAME
#undef  CONFIG_INPUT_CS461X
#undef  CONFIG_INPUT_EMU10K1
#undef  CONFIG_INPUT_SERIO
#undef  CONFIG_INPUT_SERPORT
#undef  CONFIG_INPUT_ANALOG
#undef  CONFIG_INPUT_A3D
#undef  CONFIG_INPUT_ADI
#undef  CONFIG_INPUT_COBRA
#undef  CONFIG_INPUT_GF2K
#undef  CONFIG_INPUT_GRIP
#undef  CONFIG_INPUT_INTERACT
#undef  CONFIG_INPUT_TMDC
#undef  CONFIG_INPUT_SIDEWINDER
#undef  CONFIG_INPUT_IFORCE_USB
#undef  CONFIG_INPUT_IFORCE_232
#undef  CONFIG_INPUT_WARRIOR
#undef  CONFIG_INPUT_MAGELLAN
#undef  CONFIG_INPUT_SPACEORB
#undef  CONFIG_INPUT_SPACEBALL
#undef  CONFIG_INPUT_STINGER
#undef  CONFIG_INPUT_DB9
#undef  CONFIG_INPUT_GAMECON
#undef  CONFIG_INPUT_TURBOGRAFX
#undef  CONFIG_QIC02_TAPE

/*
 * Watchdog Cards
 */
#undef  CONFIG_WATCHDOG
#undef  CONFIG_INTEL_RNG
#undef  CONFIG_NVRAM
#undef  CONFIG_RTC
#define CONFIG_S3C2410_RTC 1
#undef  CONFIG_DTLK
#undef  CONFIG_R3964
#undef  CONFIG_APPLICOM

/*
 * Ftape, the floppy tape device driver
 */
#undef  CONFIG_FTAPE
#undef  CONFIG_AGP
#undef  CONFIG_DRM

/*
 * PCMCIA character devices
 */

/*
 * Multimedia devices
 */
#undef  CONFIG_VIDEO_DEV

/*
 * File systems
 */
#undef  CONFIG_QUOTA
#undef  CONFIG_AUTOFS_FS
#define CONFIG_AUTOFS4_FS 1
#undef  CONFIG_REISERFS_FS
#undef  CONFIG_REISERFS_CHECK
#undef  CONFIG_REISERFS_PROC_INFO
#undef  CONFIG_ADFS_FS
#undef  CONFIG_ADFS_FS_RW
#undef  CONFIG_AFFS_FS
#undef  CONFIG_HFS_FS
#undef  CONFIG_BFS_FS
#undef  CONFIG_EXT3_FS
#undef  CONFIG_JBD
#undef  CONFIG_JBD_DEBUG
#define CONFIG_FAT_FS 1
#undef  CONFIG_MSDOS_FS
#undef  CONFIG_UMSDOS_FS
#define CONFIG_VFAT_FS 1
#undef  CONFIG_EFS_FS
#undef  CONFIG_JFFS_FS
#define CONFIG_JFFS2_FS 1
#define CONFIG_JFFS2_FS_DEBUG (0)
#define CONFIG_CRAMFS 1
#define CONFIG_TMPFS 1
#define CONFIG_RAMFS 1
#undef  CONFIG_ISO9660_FS
#undef  CONFIG_JOLIET
#undef  CONFIG_ZISOFS
#undef  CONFIG_MINIX_FS
#undef  CONFIG_VXFS_FS
#undef  CONFIG_NTFS_FS
#undef  CONFIG_NTFS_RW
#undef  CONFIG_HPFS_FS
#define CONFIG_PROC_FS 1
#define CONFIG_DEVFS_FS 1
#define CONFIG_DEVFS_MOUNT 1
#undef  CONFIG_DEVFS_DEBUG
#define CONFIG_DEVPTS_FS 1
#undef  CONFIG_QNX4FS_FS
#undef  CONFIG_QNX4FS_RW
#define CONFIG_ROMFS_FS 1
#define CONFIG_EXT2_FS 1
#undef  CONFIG_SYSV_FS
#undef  CONFIG_UDF_FS
#undef  CONFIG_UDF_RW
#undef  CONFIG_UFS_FS
#undef  CONFIG_UFS_FS_WRITE

/*
 * Network File Systems
 */
#undef  CONFIG_CODA_FS
#undef  CONFIG_INTERMEZZO_FS
#define CONFIG_NFS_FS 1
#define CONFIG_NFS_V3 1
#undef  CONFIG_ROOT_NFS
#undef  CONFIG_NFSD
#undef  CONFIG_NFSD_V3
#define CONFIG_SUNRPC 1
#define CONFIG_LOCKD 1
#define CONFIG_LOCKD_V4 1
#undef  CONFIG_SMB_FS
#undef  CONFIG_NCP_FS
#undef  CONFIG_NCPFS_PACKET_SIGNING
#undef  CONFIG_NCPFS_IOCTL_LOCKING
#undef  CONFIG_NCPFS_STRONG
#undef  CONFIG_NCPFS_NFS_NS
#undef  CONFIG_NCPFS_OS2_NS
#undef  CONFIG_NCPFS_SMALLDOS
#undef  CONFIG_NCPFS_NLS
#undef  CONFIG_NCPFS_EXTRAS
#undef  CONFIG_ZISOFS_FS
#define CONFIG_ZLIB_FS_INFLATE 1

/*
 * Partition Types
 */
#define CONFIG_PARTITION_ADVANCED 1
#undef  CONFIG_ACORN_PARTITION
#undef  CONFIG_OSF_PARTITION
#undef  CONFIG_AMIGA_PARTITION
#undef  CONFIG_ATARI_PARTITION
#undef  CONFIG_MAC_PARTITION
#define CONFIG_MSDOS_PARTITION 1
#undef  CONFIG_BSD_DISKLABEL
#undef  CONFIG_MINIX_SUBPARTITION
#undef  CONFIG_SOLARIS_X86_PARTITION
#undef  CONFIG_UNIXWARE_DISKLABEL
#undef  CONFIG_LDM_PARTITION
#undef  CONFIG_SGI_PARTITION
#undef  CONFIG_ULTRIX_PARTITION
#undef  CONFIG_SUN_PARTITION
#undef  CONFIG_SMB_NLS
#define CONFIG_NLS 1

/*
 * Native Language Support
 */
#define CONFIG_NLS_DEFAULT "iso8859-1"
#undef  CONFIG_NLS_CODEPAGE_437
#define CONFIG_NLS_CODEPAGE_437_MODULE 1
#undef  CONFIG_NLS_CODEPAGE_737
#undef  CONFIG_NLS_CODEPAGE_775
#undef  CONFIG_NLS_CODEPAGE_850
#undef  CONFIG_NLS_CODEPAGE_852
#undef  CONFIG_NLS_CODEPAGE_855
#undef  CONFIG_NLS_CODEPAGE_857
#undef  CONFIG_NLS_CODEPAGE_860
#undef  CONFIG_NLS_CODEPAGE_861
#undef  CONFIG_NLS_CODEPAGE_862
#undef  CONFIG_NLS_CODEPAGE_863
#undef  CONFIG_NLS_CODEPAGE_864
#undef  CONFIG_NLS_CODEPAGE_865
#undef  CONFIG_NLS_CODEPAGE_866
#undef  CONFIG_NLS_CODEPAGE_869
#undef  CONFIG_NLS_CODEPAGE_936
#define CONFIG_NLS_CODEPAGE_936_MODULE 1
#undef  CONFIG_NLS_CODEPAGE_950
#define CONFIG_NLS_CODEPAGE_950_MODULE 1
#undef  CONFIG_NLS_CODEPAGE_932
#undef  CONFIG_NLS_CODEPAGE_949
#define CONFIG_NLS_CODEPAGE_949_MODULE 1
#undef  CONFIG_NLS_CODEPAGE_874
#undef  CONFIG_NLS_ISO8859_8
#undef  CONFIG_NLS_CODEPAGE_1250
#undef  CONFIG_NLS_CODEPAGE_1251
#undef  CONFIG_NLS_ISO8859_1
#define CONFIG_NLS_ISO8859_1_MODULE 1
#undef  CONFIG_NLS_ISO8859_2
#undef  CONFIG_NLS_ISO8859_3
#undef  CONFIG_NLS_ISO8859_4
#undef  CONFIG_NLS_ISO8859_5
#undef  CONFIG_NLS_ISO8859_6
#undef  CONFIG_NLS_ISO8859_7
#undef  CONFIG_NLS_ISO8859_9
#undef  CONFIG_NLS_ISO8859_13
#undef  CONFIG_NLS_ISO8859_14
#undef  CONFIG_NLS_ISO8859_15
#undef  CONFIG_NLS_KOI8_R
#undef  CONFIG_NLS_KOI8_U
#undef  CONFIG_NLS_UTF8

/*
 * Console drivers
 */
#define CONFIG_PC_KEYMAP 1
#undef  CONFIG_VGA_CONSOLE

/*
 * Frame-buffer support
 */
#undef  CONFIG_FB

/*
 * Sound
 */
#undef  CONFIG_SOUND
#define CONFIG_SOUND_MODULE 1
#undef  CONFIG_SOUND_MK4002
#undef  CONFIG_SOUND_BT878
#undef  CONFIG_SOUND_CMPCI
#undef  CONFIG_SOUND_EMU10K1
#undef  CONFIG_MIDI_EMU10K1
#undef  CONFIG_SOUND_FUSION
#undef  CONFIG_SOUND_CS4281
#undef  CONFIG_SOUND_ES1370
#undef  CONFIG_SOUND_ES1371
#undef  CONFIG_SOUND_ESSSOLO1
#undef  CONFIG_SOUND_MAESTRO
#undef  CONFIG_SOUND_MAESTRO3
#undef  CONFIG_SOUND_ICH
#undef  CONFIG_SOUND_RME96XX
#undef  CONFIG_SOUND_SONICVIBES
#undef  CONFIG_SOUND_TRIDENT
#undef  CONFIG_SOUND_MSNDCLAS
#undef  CONFIG_SOUND_MSNDPIN
#undef  CONFIG_SOUND_VIA82CXXX
#undef  CONFIG_MIDI_VIA82CXXX
#undef  CONFIG_SOUND_SMDK2410_UDA1341
#define CONFIG_SOUND_SMDK2410_UDA1341_MODULE 1
#undef  CONFIG_SOUND_OSS
#undef  CONFIG_SOUND_WAVEARTIST
#undef  CONFIG_SOUND_PXA_AC97
#undef  CONFIG_SOUND_TVMIXER

/*
 * Multimedia Capabilities Port drivers
 */
#undef  CONFIG_MCP
#undef  CONFIG_MCP_SA1100
#undef  CONFIG_MCP_UCB1200
#undef  CONFIG_MCP_UCB1200_AUDIO
#undef  CONFIG_MCP_UCB1200_TS
#undef  CONFIG_MCP_UCB1400_TS

/*
 * USB support
 */
#undef  CONFIG_USB
#define CONFIG_USB_MODULE 1
#undef  CONFIG_USB_DEBUG
#define CONFIG_USB_DEVICEFS 1
#undef  CONFIG_USB_BANDWIDTH
#undef  CONFIG_USB_LONG_TIMEOUT
#undef  CONFIG_USB_UHCI
#undef  CONFIG_USB_UHCI_ALT
#undef  CONFIG_USB_UHCI124
#undef  CONFIG_USB_OHCI
#undef  CONFIG_USB_OHCI_SA1111
#undef  CONFIG_USB_OHCI_S3C2410
#define CONFIG_USB_OHCI_S3C2410_MODULE 1
#define CONFIG_MAX_ROOT_PORTS (1)
#undef  CONFIG_USB_AUDIO
#define CONFIG_USB_AUDIO_MODULE 1
#undef  CONFIG_USB_BLUETOOTH
#define CONFIG_USB_BLUETOOTH_MODULE 1
#undef  CONFIG_USB_STORAGE
#undef  CONFIG_USB_STORAGE_DEBUG
#undef  CONFIG_USB_STORAGE_DATAFAB
#undef  CONFIG_USB_STORAGE_FREECOM
#undef  CONFIG_USB_STORAGE_ISD200
#undef  CONFIG_USB_STORAGE_DPCM
#undef  CONFIG_USB_STORAGE_HP8200e
#undef  CONFIG_USB_STORAGE_SDDR09
#undef  CONFIG_USB_STORAGE_JUMPSHOT
#undef  CONFIG_USB_ACM
#define CONFIG_USB_ACM_MODULE 1
#undef  CONFIG_USB_PRINTER
#define CONFIG_USB_PRINTER_MODULE 1
#undef  CONFIG_USB_HID
#undef  CONFIG_USB_HIDDEV
#undef  CONFIG_USB_KBD
#undef  CONFIG_USB_MOUSE
#undef  CONFIG_USB_WACOM
#undef  CONFIG_USB_DC2XX
#define CONFIG_USB_DC2XX_MODULE 1
#undef  CONFIG_USB_MDC800
#define CONFIG_USB_MDC800_MODULE 1
#undef  CONFIG_USB_SCANNER
#define CONFIG_USB_SCANNER_MODULE 1
#undef  CONFIG_USB_MICROTEK
#undef  CONFIG_USB_HPUSBSCSI
#undef  CONFIG_USB_PEGASUS
#undef  CONFIG_USB_KAWETH
#undef  CONFIG_USB_CATC
#undef  CONFIG_USB_CDCETHER
#undef  CONFIG_USB_USBNET
#define CONFIG_USB_USBNET_MODULE 1
#undef  CONFIG_USB_USS720

/*
 * USB Serial Converter support
 */
#undef  CONFIG_USB_SERIAL
#undef  CONFIG_USB_SERIAL_GENERIC
#undef  CONFIG_USB_SERIAL_BELKIN
#undef  CONFIG_USB_SERIAL_WHITEHEAT
#undef  CONFIG_USB_SERIAL_DIGI_ACCELEPORT
#undef  CONFIG_USB_SERIAL_EMPEG
#undef  CONFIG_USB_SERIAL_FTDI_SIO
#undef  CONFIG_USB_SERIAL_VISOR
#undef  CONFIG_USB_SERIAL_IPAQ
#undef  CONFIG_USB_SERIAL_IR
#undef  CONFIG_USB_SERIAL_EDGEPORT
#undef  CONFIG_USB_SERIAL_KEYSPAN_PDA
#undef  CONFIG_USB_SERIAL_KEYSPAN
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28X
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28XA
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA28XB
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA19
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA18X
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA19W
#undef  CONFIG_USB_SERIAL_KEYSPAN_USA49W
#undef  CONFIG_USB_SERIAL_MCT_U232
#undef  CONFIG_USB_SERIAL_KLSI
#undef  CONFIG_USB_SERIAL_PL2303
#undef  CONFIG_USB_SERIAL_CYBERJACK
#undef  CONFIG_USB_SERIAL_XIRCOM
#undef  CONFIG_USB_SERIAL_OMNINET
#undef  CONFIG_USB_RIO500

/*
 * Bluetooth support
 */
#undef  CONFIG_BLUEZ

/*
 * Kernel hacking
 */
#define CONFIG_FRAME_POINTER 1
#define CONFIG_DEBUG_USER 1
#define CONFIG_DEBUG_INFO 1
#undef  CONFIG_NO_PGT_CACHE
#define CONFIG_DEBUG_KERNEL 1
#undef  CONFIG_DEBUG_SLAB
#define CONFIG_MAGIC_SYSRQ 1
#undef  CONFIG_DEBUG_SPINLOCK
#undef  CONFIG_DEBUG_WAITQ
#define CONFIG_DEBUG_BUGVERBOSE 1
#define CONFIG_DEBUG_ERRORS 1
#define CONFIG_DEBUG_LL 1
#undef  CONFIG_DEBUG_DC21285_PORT
#undef  CONFIG_DEBUG_CLPS711X_UART2