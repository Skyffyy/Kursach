#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_FILE "database.txt"

/* Предварительные объявления */
struct Student;
struct Parent;

/* Load/save operate on dynamic arrays; capacities may be updated by function. */
void loadDatabase(struct Student **students, struct Parent **parents,
                  int *studentCount, int *parentCount,
                  int *studentCapacity, int *parentCapacity);
void saveDatabase(struct Student *students, struct Parent *parents, int studentCount, int parentCount);

#endif