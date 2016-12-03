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
LASER_IF_BASE=laser_if
SERVOS_BASE=servos
SERVOS_IF_BASE=servos_if
DISPLAY_IF_BASE=display_if
JOYSTICK_BASE=joystick
TARGET_STM=stmtest
STM_LIB_BASE=stm
OS_LIB_BASE=os
DISPLAY_LIB_BASE=display

LASER = $(LASER_BASE)$(TARGET_EXTENSION)
LASER_IF = $(LASER_IF_BASE)$(TARGET_EXTENSION)
SERVOS = $(SERVOS_BASE)$(TARGET_EXTENSION)
SERVOS_IF = $(SERVOS_IF_BASE)$(TARGET_EXTENSION)
DISPLAY_IF = $(DISPLAY_IF_BASE)$(TARGET_EXTENSION)
JOYSTICK = $(JOYSTICK_BASE)$(TARGET_EXTENSION)
STM_TEST_TARGET = $(TARGET_STM)$(TARGET_EXTENSION)
STM_LIB = lib$(STM_LIB_BASE)$(LIB_EXTENSION)
OS_LIB = lib$(OS_LIB_BASE)$(LIB_EXTENSION)
DISPLAY_LIB = lib$(DISPLAY_LIB_BASE)$(LIB_EXTENSION)

STM_LIB_SRC = test/libstm.c
OS_LIB_SRC = test/libos.c
DISPLAY_LIB_SRC = test/libdisplay.c

STM_LIB_TEST_SRC = $(UNITY_ROOT)/unity_src/unity.c test/test_libstm.c test/test_runners/test_libstm_runner.c
LASER_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/laser_app.c ../src/hal/laser_hal.c -L./ -l$(STM_LIB_BASE) test/test_laser.c test/test_runners/test_laser_runner.c
SERVOS_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/servos_app.c ../src/hal/servos_hal.c -L./ -l$(STM_LIB_BASE) test/test_servos.c test/test_runners/test_servos_runner.c
JOYSTICK_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/joystick_app.c ../src/hal/joystick_hal.c -L./ -l$(STM_LIB_BASE) test/test_joystick.c test/test_runners/test_joystick_runner.c

LASER_IF_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/laser_app.c ../src/hal/laser_hal.c -L./ -l$(STM_LIB_BASE) test/test_runners/test_laser_if_runner.c test/test_laser_if.c
SERVOS_IF_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/servos_app.c ../src/hal/servos_hal.c -L./ -l$(STM_LIB_BASE) test/test_runners/test_servos_if_runner.c test/test_servos_if.c

DISPLAY_IF_TEST_SRC=$(UNITY_ROOT)/unity_src/unity.c ../src/app/display_app.c -L./ -l$(DISPLAY_LIB_BASE) test/test_runners/test_display_if_runner.c test/test_display_if.c

INC_DIRS=-I../inc/app -I../inc/hal -I../inc/tasks -I$(UNITY_ROOT)/unity_src -I./inc

SYMBOLS=-DTEST

all: clean default

# require that the stmlib is built
default: laser servos joystick laser_if servos_if

joystick: libstm.a
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_joystick.c test/test_runners/test_joystick_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(JOYSTICK_TEST_SRC) -o $(JOYSTICK)
	# execute
	./$(JOYSTICK)

laser: libstm.a
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_laser.c test/test_runners/test_laser_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(LASER_TEST_SRC) -o $(LASER)
	# execute
	./$(LASER)

laser_if: libstm.a
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_laser_if.c test/test_runners/test_laser_if_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(LASER_IF_TEST_SRC) -o $(LASER_IF)
	# execute
	./$(LASER_IF)
	
servos: libstm.a
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_servos.c test/test_runners/test_servos_runner.c	
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SERVOS_TEST_SRC) -o $(SERVOS)
	# execute
	./$(SERVOS)

servos_if: libstm.a
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_servos_if.c test/test_runners/test_servos_if_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SERVOS_IF_TEST_SRC) -o $(SERVOS_IF)
	# execute
	./$(SERVOS_IF)

display_if: libdisplay.a
	# generate test runner
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_display_if.c test/test_runners/test_display_if_runner.c
	# compile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(DISPLAY_IF_TEST_SRC) -o $(DISPLAY_IF)
	# execute
	./$(DISPLAY_IF)
	
libstm.a:
	# compile stmtest with -c flag: needed because we don't have a main function
	# since it's gonna be a library
	$(C_COMPILER) -Wall -Wundef -I./inc $(SYMBOLS) $(STM_LIB_SRC) -c -o lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	# generate library (.a file) from object file
	ar rcs $(STM_LIB) lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	$(CLEANUP) lib$(STM_LIB_BASE)$(TARGET_EXTENSION)

libos.a:
	# compile my oslib
	$(C_COMPILER) -I./inc $(SYMBOLS) $(OS_LIB_SRC) -c -o lib$(OS_LIB_BASE)$(TARGET_EXTENSION)
	# generate library (.a file) from object file
	ar rcs $(OS_LIB) lib$(OS_LIB_BASE)$(TARGET_EXTENSION)
	$(CLEANUP) lib$(OS_LIB_BASE)$(TARGET_EXTENSION)

libdisplay.a:
	# compile my display file
	$(C_COMPILER) -I./inc $(SYMBOLS) $(DISPLAY_LIB_SRC) -c -o lib$(DISPLAY_LIB_BASE)$(TARGET_EXTENSION)
	# generate library (.a file) from object file
	ar rcs $(DISPLAY_LIB) lib$(DISPLAY_LIB_BASE)$(TARGET_EXTENSION)
	$(CLEANUP) lib$(DISPLAY_LIB_BASE)$(TARGET_EXTENSION)
	
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
	$(CLEANUP) $(LASER_IF)
	$(CLEANUP) $(SERVOS)
	$(CLEANUP) $(SERVOS_IF)
	$(CLEANUP) $(JOYSTICK)
	$(CLEANUP) $(STM_LIB)
	$(CLEANUP) $(STM_TEST_TARGET)
	$(CLEANUP) $(OS_LIB)
	$(CLEANUP) $(DISPLAY_LIB)
	$(CLEANUP) lib$(STM_LIB_BASE)$(TARGET_EXTENSION)
	$(CLEANUP) test/test_runners/test_libstm_runner.c
	$(CLEANUP) test/test_runners/test_stmtestlib_runner.c
	$(CLEANUP) test/test_runners/test_laser_runner.c
	$(CLEANUP) test/test_runners/test_laser_if_runner.c
	$(CLEANUP) test/test_runners/test_joystick_runner.c
	$(CLEANUP) test/test_runners/test_servos_runner.c
