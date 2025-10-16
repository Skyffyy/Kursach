CC = gcc
CFLAGS = -Wall -Wextra -I./headers
SRCDIR = headers
SOURCES = main.c $(SRCDIR)/student.c $(SRCDIR)/database.c $(SRCDIR)/sort.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
    ./$(TARGET)

.PHONY: all clean run