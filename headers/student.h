#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50
#define FILENAME "students.txt"

struct Student {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    int birthYear;
    int classNumber;
    float averageGrade;
};

// Static array max size
#define MAX_STUDENTS 100

// File operations
void saveToFile(struct Student students[], int count);
void loadFromFile(struct Student students[], int *count);

// Static array operations
void listStudentsStatic(struct Student students[], int count);
void addStudentStatic(struct Student students[], int *count);
void deleteStudentStatic(struct Student students[], int *count);

// Dynamic array operations
struct Student* createStudentArray(int initialCapacity);
void freeStudentArray(struct Student *students);
void addStudentDynamic(struct Student **students, int *count, int *capacity);
void deleteStudentDynamic(struct Student **students, int *count);
void listStudentsDynamic(struct Student *students, int count);

// Utility functions
int strEqual(const char *a, const char *b);

#endif