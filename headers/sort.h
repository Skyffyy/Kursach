#ifndef SORT_H
#define SORT_H

// Предварительные объявления
struct Student;
struct Parent;

// Student sorting
void sortByName(struct Student *students, int count);
void sortBySurname(struct Student *students, int count);
void sortByBirthYear(struct Student *students, int count);
void sortByAverageGrade(struct Student *students, int count);

// Parent sorting
void sortParentsByName(struct Parent *parents, int count);
void sortParentsBySurname(struct Parent *parents, int count);
void sortParentsByPersonalID(struct Parent *parents, int count);

// Utility
int strCompare(const char *a, const char *b);

#endif