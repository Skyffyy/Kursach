# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Iheaders
TARGET = main

# Все исходные файлы
SRC = main.c headers/database.c headers/student.c headers/parent.c headers/sort.c headers/utils.c
OBJ = main.o database.o student.o parent.o sort.o utils.o

# Основная цель
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Правила компиляции объектных файлов
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

database.o: headers/database.c
	$(CC) $(CFLAGS) -c headers/database.c -o database.o

student.o: headers/student.c
	$(CC) $(CFLAGS) -c headers/student.c -o student.o

parent.o: headers/parent.c
	$(CC) $(CFLAGS) -c headers/parent.c -o parent.o

sort.o: headers/sort.c
	$(CC) $(CFLAGS) -c headers/sort.c -o sort.o

utils.o: headers/utils.c
	$(CC) $(CFLAGS) -c headers/utils.c -o utils.o

# Очистка
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean