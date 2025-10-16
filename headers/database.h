#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"

#define DATABASE_FILE "database.txt"

void loadDatabase(struct Student students[], int *count);
void saveDatabase(struct Student students[], int count);

#endif
