PWD  := $(shell pwd)

# we can override this in command line
KDIR ?= /lib/modules/$(shell uname -r)/build

# we are making cross-compile
export CROSS_COMPILE := arm-linux-gnueabihf-
export ARCH          := arm

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
