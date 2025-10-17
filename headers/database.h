#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"

#define DATABASE_FILE "database.txt"

// Database functions
void loadDatabase(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount);
void saveDatabase(struct Student students[], struct Parent parents[], int studentCount, int parentCount);

#endif
