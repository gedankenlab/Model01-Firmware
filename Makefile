# This stub makefile for a Kaleidoglyph plugin pulls in 
# all targets from the Kaleidoglyph-Plugin library

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
SKETCHBOOK_DIR ?= $(HOME)/Documents/Arduino
PACKAGE_DIR ?= $(HOME)/Library/Arduino15
else
SKETCHBOOK_DIR ?= $(HOME)/Arduino
PACKAGE_DIR ?= $(HOME)/.arduino15
endif


ARDUINO_INSTALLED_ENV=$(shell ls -dt $(PACKAGE_DIR)/packages/keyboardio/hardware/avr/* 2>/dev/null |head -n 1)
MANUALLY_INSTALLED_ENV=$(shell ls -dt $(SKETCHBOOK_DIR)/hardware/keyboardio/avr 2>/dev/null |head -n 1)



ifneq ("$(wildcard $(ARDUINO_INSTALLED_ENV)/boards.txt)","")

ifneq ("$(wildcard $(MANUALLY_INSTALLED_ENV)/boards.txt)","")

$(info ***************************************************************************)
$(info It appears that you have installed two copies of Kaleidoglyph. One copy was)
$(info installed using Arduino's "Board Manager", while the other was installed by)
$(info hand, probably using "git".)
$(info )
$(info This will likely cause some trouble as you try to build keyboard firmware)
$(info using Kaleidoglyph. You may want to remove either: )
$(info )
$(info $(PACKAGE_DIR)/packages/keyboardio/ which was installed using Arduino)
$(info )
$(info or)
$(info )
$(info $(SKETCHBOOK_DIR)/hardware/keyboardio/ which was installed by hand.)
$(info )
$(info ***************************************************************************)
$(info )

endif

BOARD_HARDWARE_PATH = $(ARDUINO_INSTALLED_ENV)
KALEIDOGLYPH_PLUGIN_MAKEFILE_DIR ?= build-tools/makefiles/
KALEIDOGLYPH_BUILDER_DIR ?= $(ARDUINO_INSTALLED_ENV)/libraries/Kaleidoglyph-Core/bin/



endif


BOARD_HARDWARE_PATH ?= $(SKETCHBOOK_DIR)/hardware
KALEIDOGLYPH_PLUGIN_MAKEFILE_DIR ?= keyboardio/avr/build-tools/makefiles/

include $(BOARD_HARDWARE_PATH)/$(KALEIDOGLYPH_PLUGIN_MAKEFILE_DIR)/rules.mk
