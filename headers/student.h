#ifndef STUDENT_H
#define STUDENT_H

#include "constants.h"

/* Предварительное объявление struct Parent */
struct Parent;

struct Student {
    char *name;
    char *surname;
    char *personalID;
    char *email;
    char *phone;
    char *class;
    int birthDay;
    int birthMonth;
    int birthYear;
    char *gender;
    float averageGrade;

    int parentCount;
    char *parentPersonalIDs[2];
};

/* Dynamic array helpers */
struct Student* createStudentArray(int initialCapacity);
void freeStudentArray(struct Student *students, int count);
void freeStudentRecord(struct Student *s);

/* Operations (dynamic-only) */
void listStudents(struct Student *students, int studentCount, struct Parent *parents, int parentCount);
void addStudent(struct Student **students, int *studentCount, int *studentCapacity,
                struct Parent **parents, int *parentCount, int *parentCapacity);
void deleteStudent(struct Student *students, int *studentCount, struct Parent *parents, int parentCount);
void filterStudents(struct Student *students, int studentCount, struct Parent *parents, int parentCount);

#endif