# $Id: Makefile,v 1.1.1.1 2006/01/25 03:57:25 root Exp $

prism54-objs := islpci_eth.o islpci_mgt.o \
                isl_38xx.o isl_ioctl.o islpci_dev.o \
		islpci_hotplug.o oid_mgt.o

obj-$(CONFIG_PRISM54) += prism54.o

EXTRA_CFLAGS = -I$(PWD) #-DCONFIG_PRISM54_WDS

