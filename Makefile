obj-m = subdriver.o 

KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

default:
	make -C $(KDIR) SUBDIRS=$(PWD) modules