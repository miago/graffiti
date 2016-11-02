# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
elseifeq ($(OSTYPE),msys)
    CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.exe
elseifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

UNITY_ROOT=./
C_COMPILER=gcc

CFLAGS=-std=c89
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror 
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

TARGET_BASE1=laser
TARGET_STM=stmtest


TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
STM_TEST_TARGET = $(TARGET_STM)$(TARGET_EXTENSION)

STM_LIB_FILES = $(UNITY_ROOT)/unity_src/unity.c test/stmtest.c test/test_stmtestlib.c test/test_runners/test_stmtestlib_runner.c
SRC_FILES1=$(UNITY_ROOT)/unity_src/unity.c ../src/laser.c -L./ -lstmtest test/test_laser.c test/test_runners/test_laser_runner.c

INC_DIRS=-I../src -I$(UNITY_ROOT)/unity_src -I../inc -I./inc
SYMBOLS=-DTEST

all: clean default

default: stmlib
	#export LD_LIBRARY_PATH=$(UNITY_ROOT):$LD_LIBRARY_PATH
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_laser.c test/test_runners/test_laser_runner.c
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	./$(TARGET1)

stmlib:
	$(C_COMPILER) -Wall -Wundef -I./inc $(SYMBOLS) test/stmtest.c -c -o libstmtest.o
	ar rcs libstmtest.a libstmtest.o
	
stmlibtest: stmlib
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_stmtestlib.c test/test_runners/test_stmtestlib_runner.c
	$(C_COMPILER) -I./inc -I$(UNITY_ROOT)/unity_src $(SYMBOLS) -L./ -lstmtest $(STM_LIB_FILES) -o $(STM_TEST_TARGET)
	./$(STM_TEST_TARGET)
	
clean:
	$(CLEANUP)

