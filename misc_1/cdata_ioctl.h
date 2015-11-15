#ifndef _CDATA_IOCTL_H_
#define _CDATA_IOCTL_H_

#include <linux/ioctl.h>

#define IOCTL_EMPTY	_IO(0XCE, 1)
#define IOCTL_SYNC	_IO(0XCE, 2)
#define IOCTL_NAME	_IO(0XCE, 3)

#endif
