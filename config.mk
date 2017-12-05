PROJECT_NAME:=karl

MCU=atmega324pa
AVRDUDE=avrdude
AVRDUDE_PROGRAMMERID=usbasp

OBJCOPY=avr-objcopy
PROGMEM:=./progmem
SERIEVIA:=./serieViaUSB

SRC_DIR:=src
BUILD_DIR=build
LIB_DIR:=lib_dir
EXEC_DIR:=exec_dir
DATA_DIR:=data
INCLUDE_DIR=include

EXEC_SRC_DIR:=$(EXEC_DIR)/$(SRC_DIR)
EXEC_BUILD_DIR:=$(EXEC_DIR)/$(BUILD_DIR)
EXEC_DATA_DIR:=$(EXEC_DIR)/$(DATA_DIR)
LIB_SRC_DIR:=$(LIB_DIR)/$(SRC_DIR)
LIB_BUILD_DIR:=$(LIB_DIR)/$(BUILD_DIR)


LIB:=marx
LIBL:=$(BUILD_DIR)/lib$(LIB).a

CC:=avr-gcc

DEPFLAGS = -MMD
WARNFLAGS= -Wall -Wextra -Wno-comment
CCFLAGS:=$(DEPFLAGS) $(WARNFLAGS) -g -mmcu=$(MCU) -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char
CXXFLAGS=-fno-exceptions

SEPARATOR:=-------------------------------------------------------------------------------
BIG_SEPARATOR:= ===$(SEPARATOR)===
