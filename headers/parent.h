#ifndef PARENT_H
#define PARENT_H

#include "constants.h"

// Предварительное объявление struct Student
struct Student;

struct Parent {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_SURNAME_LENGTH];
    char personalID[MAX_ID_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int birthDay;
    int birthMonth;
    int birthYear;
    char gender[MAX_GENDER_LENGTH];

    int childCount;
    char childPersonalIDs[MAX_CHILDREN][MAX_ID_LENGTH];
};

// Utility
struct Parent* findParentByID(struct Parent *parents, int parentCount, const char *id);
void showParentAndChildren(struct Parent *parents, int parentCount,
                           struct Student *students, int studentCount, const char *parentID);

// Static
void listParentsStatic(struct Parent *parents, int parentCount);
void addParentStatic(struct Parent *parents, int *parentCount);
void deleteParentStatic(struct Parent *parents, int *parentCount);

// Dynamic - ИСПРАВЛЕНО: добавлены ** для указателей на указатели
struct Parent* createParentArray(int initialCapacity);
void freeParentArray(struct Parent *parents);
void addParentDynamic(struct Parent **parents, int *parentCount, int *capacity);  // ИСПРАВЛЕНО: **
void deleteParentDynamic(struct Parent **parents, int *parentCount);              // ИСПРАВЛЕНО: **

// New functions
void printParentInfo(struct Parent *parent);
void linkParentToStudent(struct Parent *parent, const char *studentID);

#endif