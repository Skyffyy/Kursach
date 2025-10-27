#ifndef STUDENT_H
#define STUDENT_H

#include "constants.h"

// Предварительное объявление struct Parent
struct Parent;

struct Student {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_SURNAME_LENGTH];
    char personalID[MAX_ID_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int birthDay;
    int birthMonth;
    int birthYear;
    char gender[MAX_GENDER_LENGTH];
    float averageGrade;

    int parentCount;
    char parentPersonalIDs[2][MAX_ID_LENGTH];
};

// Static
void listStudentsStatic(struct Student *students, int studentCount,
                        struct Parent *parents, int parentCount);
void addStudentStatic(struct Student *students, int *studentCount,
                      struct Parent *parents, int *parentCount);
void deleteStudentStatic(struct Student *students, int *studentCount);

// Dynamic - ИСПРАВЛЕНО: добавлены ** для указателей на указатели
struct Student* createStudentArray(int initialCapacity);
void freeStudentArray(struct Student *students);
void addStudentDynamic(struct Student **students, struct Parent **parents,  // ИСПРАВЛЕНО: **
                       int *studentCount, int *parentCount, int *capacity);
void deleteStudentDynamic(struct Student **students, int *studentCount);    // ИСПРАВЛЕНО: **
void listStudentsDynamic(struct Student *students, int studentCount,
                         struct Parent *parents, int parentCount);

#endif
