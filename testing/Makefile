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
	LIB_EXTENSION=.a
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
	LIB_EXTENSION=.a
endif

UNITY_ROOT=./
C_COMPILER=gcc

CFLAGS=-std=c89
CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -Werror 
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
#CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

LASER_BASE=laser
SERVOS_BASE=servos
JOYSTICK_BASE=joystick
TARGET_STM=stmtest
STM_LIB_BASE=stm

LASER = $(LASER_BASE)$(TARGET_EXTENSION)
SERVOS = $(SERVOS_BASE)$(TARGET_EXTENSION)
JOYSTICK = $(JOYSTIC_BASE)$(TARGET_EXTENSION)
STM_TEST_TARGET = $(TARGET_STM)$(TARGET_EXTENSION)
STM_LIB = lib$(STM_LIB_BASE)$(LIB_EXTENSION)

STM_LIB_SRC = test/libstm.c
STM_LIB_TEST_SRC = $(UNITY_ROOT)/unity_src/unity.c test/test_libstm.c test/test_runners/test_libstm_runner.c
LASER_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/laser_app.c ../src/hal/laser_hal.c -L./ -l$(STM_LIB_BASE) test/test_laser.c test/test_runners/test_laser_runner.c
SERVOS_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/servos_app.c ../src/hal/servos_hal.c -L./ -l$(STM_LIB_BASE) test/test_servos.c test/test_runners/test_servos_runner.c
JOYSTICK_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/joystick_app.c ../src/hal/joystick_hal.c -L./ -l$(STM_LIB_BASE) test/test_joystick.c test/test_runners/test_joystick_runner.c



INC_DIRS=-I../inc/app  -I../inc/hal -I$(UNITY_ROOT)/unity_src -I./inc
SYMBOLS=-DTEST

all: clean default

# require that the stmlib is built
default: laser servos joystick

joystick: libstm
	# generate test runners
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_joystick.c test/test_runners/test_joystick_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(JOYSTICK_TEST_SRC) -o $(JOYSTICK)
	# execute
	./$(JOYSTICK)

laser: libstm
	# generate test runners
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_laser.c test/test_runners/test_laser_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(LASER_TEST_SRC) -o $(LASER)
	# execute
	./$(LASER)
	
servos: libstm
	# generate test runners
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_servos.c test/test_runners/test_servos_runner.c	
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SERVOS_TEST_SRC) -o $(SERVOS)
	# execute
	./$(SERVOS)
	
libstm:
	# compile stmtest with -c flag: needed because we don't have a main function
	# since it's gonna be a library
	$(C_COMPILER) -Wall -Wundef -I./inc $(SYMBOLS) $(STM_LIB_SRC) -c -o lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	# generate library (.a file) from object file
	ar rcs $(STM_LIB) lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	$(CLEANUP) lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	
# to test the stmlib we need a compiled stm
libstmtest: libstm
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_libstm.c test/test_runners/test_libstm_runner.c
	# compile library, don't know why it does not work when linking the library.
	$(C_COMPILER) -Wall -Wundef -I./inc $(SYMBOLS) $(STM_LIB_SRC) -c -o lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	# compile test
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(STM_LIB_TEST_SRC) lib$(STM_LIB_BASE)$(TARGET_EXTENSION) -o $(STM_TEST_TARGET)
	# execute
	./$(STM_TEST_TARGET)

clean:
	$(CLEANUP) $(LASER)	
	$(CLEANUP) $(SERVOS)
	$(CLEANUP) $(STM_LIB)
	$(CLEANUP) $(STM_TEST_TARGET)
	$(CLEANUP) lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	$(CLEANUP) test/test_runners/test_libstm_runner.c
	$(CLEANUP) test/test_runners/test_laser_runner.c
