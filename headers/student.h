#ifndef STUDENT_H
#define STUDENT_H

#include "parent.h"
#define MAX_STUDENTS 100

struct Student {
    char name[50];
    char surname[50];
    char personalID[20];
    char email[100];
    char phone[20];
    char birthDate[20];
    char gender[10];
    float averageGrade;

    int parentCount;
    char parentPersonalIDs[2][20];
};

// Utility
int strEqual(const char *a, const char *b);

// Static
void listStudentsStatic(struct Student students[], int studentCount,
                        struct Parent parents[], int parentCount);
void addStudentStatic(struct Student students[], int *studentCount,
                      struct Parent parents[], int *parentCount);
void deleteStudentStatic(struct Student students[], int *studentCount);

// Dynamic
struct Student* createStudentArray(int initialCapacity);
void freeStudentArray(struct Student *students);
void addStudentDynamic(struct Student **students, struct Parent **parents,
                       int *studentCount, int *parentCount, int *capacity);
void deleteStudentDynamic(struct Student **students, int *studentCount);
void listStudentsDynamic(struct Student *students, int studentCount,
                         struct Parent *parents, int parentCount);

#endif
