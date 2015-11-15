#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "cdata_ioctl.h"



int main (void)
{
    int fd;

    fd = open("/dev/cdata", O_RDWR);

    if(fd==-1)
    {
	printf("open file failed\n\n");
	return -1;
    }


    close(fd);

return 0;
}
