#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cdata_ioctl.h"

int main(void)
{
    int fd;
    int ret_val=0;
    char hostname[128];
    pid_t child;
    char* private_d="hi, hugh is here";
    hostname[127] = '\0';
    gethostname(hostname, 128);

    child = fork();

    fd = open("/dev/cdata", O_RDWR);
 
    if(fd==-1)
    {
	printf("1 open file failed fd=%d\n\n", fd);
    }
    
    #if 1
    if (child > 0 ){
    	write(fd, "parent:hello", 12);
    }
    else{
    	write(fd, "child:hello", 11);
    }
    #endif

    //write(fd, "parent:hello", 12);
    
    //1. send device name to buf firse
    ret_val = ioctl(fd, IOCTL_WRITE, hostname);
    if (ret_val < 0) {
   	 printf ("2 ioctl_write failed:%d\n", ret_val);
    }
    
    //2. print device name via IOCTL_SYNC

    ret_val = ioctl(fd, IOCTL_SYNC, 0);
    if (ret_val < 0) {
   	 printf ("3 ioctl_sync failed:%d\n", ret_val);
    }
    
    //3. clean buf via IOCTL_EMPTY
    ret_val = ioctl(fd, IOCTL_EMPTY, 0);
    if (ret_val < 0) {
   	 printf ("4 ioctl_enpty failed:%d\n", ret_val);
    }

    //3. print
    ret_val = ioctl(fd, IOCTL_SYNC, 0);
    if (ret_val < 0) {
   	 printf ("5 ioctl_sync failed:%d\n", ret_val);
    }

    //4. send another string to buf
    ret_val = ioctl(fd, IOCTL_WRITE, private_d);
    if (ret_val < 0) {
   	 printf ("6 ioctl_write failed:%d\n", ret_val);
    }

    //3. print
    ret_val = ioctl(fd, IOCTL_SYNC, 0);
    if (ret_val < 0) {
   	 printf ("7 ioctl_sync failed:%d\n", ret_val);
    }

    close(fd);
    return 0;
}

