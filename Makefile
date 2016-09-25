# Needed for Ubuntu/Debian since sh points to dash instead of bash...
SHELL := /bin/bash

SRC_DIR   := src
HOST_SRC_DIR := ${SRC_DIR}/host
INCLUDE_DIR := -Isrc/include -I/usr/include/libxml2 -Isrc/host/parseXml -Isrc/host/execute

# Common cflags and lflags (for all targets)
# These flags will be propagated through the hierarchy
cflags = -Wall -g -O3

APPLICATION=JpegDecoder

# Give the application name to compile the respective application.
APPLICATION_UPPER_CASE=$(shell echo $(APPLICATION) | tr a-z A-Z)

ifndef APPLICATION
	APP_SRC_DIR := ${SRC_DIR}/common/application
	COMMON_FILES := $(wildcard ${APP_SRC_DIR}/*/*.cpp) $(wildcard ${SRC_DIR}/common/*/*.cpp)
	COMMON_INCLUDE_DIR := $(patsubst %,-I%,$(subst :, ,$(wildcard ${SRC_DIR}/common/*/))) $(patsubst %,-I%,$(subst :, ,$(wildcard ${APP_SRC_DIR}/*/))) 
else
	APP_SRC_DIR := ${SRC_DIR}/common/application/${APPLICATION}
	COMMON_FILES := $(wildcard ${APP_SRC_DIR}/*.cpp) $(wildcard ${SRC_DIR}/common/*/*.cpp)
	COMMON_INCLUDE_DIR := $(patsubst %,-I%,$(subst :, ,$(wildcard ${SRC_DIR}/common/*/))) -I${APP_SRC_DIR}/
	COMMON_FLAGS += -DAPPLICATION=${APPLICATION_UPPER_CASE} 
endif

executable := dataflow 
# Common flags for host programs
srcs := $(wildcard ${HOST_SRC_DIR}/*.cpp) $(wildcard ${HOST_SRC_DIR}/*/*.cpp) ${COMMON_FILES}
cflags := -Wall -g -O3 ${COMMON_INCLUDE_DIR} ${COMMON_FLAGS} ${INCLUDE_DIR}
lflags := -lxml2 -lpthread -lm

all:
	g++ ${cflags} ${srcs} -o ${executable} ${lflags}
