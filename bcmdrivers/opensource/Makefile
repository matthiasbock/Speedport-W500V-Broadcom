# File: modules/drivers/Makefile
#
# Makefile for the GPLed Linux kernel modules.
#

LN_NAME=bcm9$(BRCM_CHIP)
LN_DRIVER_DIRS =

-include $(KERNEL_DIR)/.config

ifneq ($(CONFIG_BCM_BOARD),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_BOARD_IMPL) char/board/$(BRCM_BOARD)/$(LN_NAME);
endif

ifneq ($(CONFIG_BCM_SERIAL),)
  LN_DRIVER_DIRS +=ln -sn impl$(CONFIG_BCM_SERIAL_IMPL) char/serial/$(LN_NAME);
endif

obj-$(CONFIG_BCM_BOARD) += char/board/$(BRCM_BOARD)/$(LN_NAME)/
obj-$(CONFIG_BCM_SERIAL) += char/serial/$(LN_NAME)/


symlinks:
	find . -lname "*" -name "$(LN_NAME)" -print -exec rm -f "{}" ";"	
	$(CONFIG_SHELL) -c "$(LN_DRIVER_DIRS)"
