#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_FILE "database.txt"

// Предварительные объявления
struct Student;
struct Parent;

void loadDatabase(struct Student *students, struct Parent *parents, int *studentCount, int *parentCount);
void saveDatabase(struct Student *students, struct Parent *parents, int studentCount, int parentCount);

#endif