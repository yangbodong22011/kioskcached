C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
CC = gcc
LD = ld

C_FLAGS = -std=gnu99


all: $(S_OBJECTS) $(C_OBJECTS) link 
