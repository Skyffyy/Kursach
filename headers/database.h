#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"

#define DATABASE_FILE "database.txt"

// Updated functions with parents support
void loadDatabase(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount);
void saveDatabase(struct Student students[], struct Parent parents[], int studentCount, int parentCount);

#endif
