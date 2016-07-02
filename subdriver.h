#ifndef _SUBMARINO_H_
#define _SUBMARINO_H_

#define SUCCESS	0
#define FAILURE	-1

#define IOC_MAGIC 's'

#define IOCTL_UP _IOW(IOC_MAGIC, 1, int)
#define IOCTL_RIGHT _IOW(IOC_MAGIC, 2, int)
#define IOCTL_DOWN _IOW(IOC_MAGIC, 3, int)
#define IOCTL_LEFT _IOW(IOC_MAGIC, 4, int)

#endif