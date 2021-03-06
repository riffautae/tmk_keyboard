PJRC_DIR = protocol/pjrc

OPT_DEFS += -DHOST_PJRC

SRC +=	$(PJRC_DIR)/main.c \
	$(PJRC_DIR)/pjrc.c \
	$(PJRC_DIR)/usb_keyboard.c \
	$(PJRC_DIR)/usb_debug.c \
	$(PJRC_DIR)/usb.c

# Option modules
ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef EXTRAKEY_ENABLE
    SRC += $(PJRC_DIR)/usb_extra.c
endif

# Search Path
VPATH += $(TOP_DIR)/$(PJRC_DIR)
