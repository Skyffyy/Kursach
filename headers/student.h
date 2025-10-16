#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50
#define MAX_STUDENTS 100

struct Student {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    int birthYear;
    int classNumber;
    float averageGrade;
};

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

// Wrappers
void listStudents(struct Student *students, int count);
void addStudent(struct Student *students, int *count, int *capacity, int dynamic);
void deleteStudent(struct Student *students, int *count, int *capacity, int dynamic);

// Utility
int strEqual(const char *a, const char *b);

#endif
