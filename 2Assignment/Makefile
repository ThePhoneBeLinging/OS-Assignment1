CC = gcc

# Compilation flags
CCWARNINGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable
CCOPTS     = -std=c11 -g -O0
PKGFLAG = $(shell pkg-config --cflags check)
CFLAGS = $(CCWARNINGS) $(CCOPTS) $(PKGFLAG)

LDFLAGS = $(shell pkg-config --libs check)

TEST_SOURCES := check_mm.c mm.c memory_setup.c
TEST_OBJECTS := $(TEST_SOURCES:.c=.o)

APP_SOURCES := main.c io.c mm.c memory_setup.c
APP_OBJECTS := $(APP_SOURCES:.c=.o)

TEST_EXECUTABLE = malloc_check
APP_EXECUTABLE  = cmd_int

.PHONY: all clean

all: $(APP_EXECUTABLE) $(TEST_EXECUTABLE)

%.o: %.c mm.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $@ $(LDFLAGS)

$(APP_EXECUTABLE): $(APP_OBJECTS)
	$(CC) $(APP_OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf *o *~ $(TEST_EXECUTABLE) $(APP_EXECUTABLE)
