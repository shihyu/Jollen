#ifndef _CDATA_IOCTL_H_
#define _CDATA_IOCTL_H_

#include <linux/ioctl.h>

#define IOCTL_EMPTY  _IO(0xD0, 1)
#define IOCTL_SYNC  _IO(0xD1, 2)
#define IOCTL_NAME _IOW(0XDD, 3, int)
#define IOCTL_WRITE _IOW(0XDE, 4, int)
#endif
