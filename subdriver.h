#ifndef _SUBMARINO_H_
#define _SUBMARINO_H_

#define SUCCESS	0
#define FAILURE	-1
#define DEVICE_PATH "/dev/submarino"

#define IOC_MAGIC 's'

#define IOCTL_SET_KEY _IOW(IOC_MAGIC, 1, int)
#define IOCTL_GET_KEY _IOR(IOC_MAGIC, 2, char *)

#endif