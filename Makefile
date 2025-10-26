CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o student.o parent.o database.o sort.o utils.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c student.h parent.h database.h sort.h utils.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h parent.h utils.h
	$(CC) $(CFLAGS) -c student.c

parent.o: parent.c parent.h student.h utils.h
	$(CC) $(CFLAGS) -c parent.c

database.o: database.c database.h student.h parent.h
	$(CC) $(CFLAGS) -c database.c

sort.o: sort.c sort.h student.h parent.h
	$(CC) $(CFLAGS) -c sort.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJ) $(TARGET)
