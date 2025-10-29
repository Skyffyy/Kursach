#ifndef PARENT_H
#define PARENT_H

#include "constants.h"

/* Предварительное объявление struct Student */
struct Student;

struct Parent {
    char *name;
    char *surname;
    char *personalID;
    char *email;
    char *phone;
    int birthDay;
    int birthMonth;
    int birthYear;
    char *gender;

    int childCount;
    char *childPersonalIDs[MAX_CHILDREN];
};

/* Utilities */
struct Parent* findParentByID(struct Parent *parents, int parentCount, const char *id);
void showParentAndChildren(struct Parent *parents, int parentCount,
                           struct Student *students, int studentCount, const char *parentID);
void printParentInfo(struct Parent *parent);
void linkParentToStudent(struct Parent *parent, const char *studentID);

/* Dynamic array helpers */
struct Parent* createParentArray(int initialCapacity);
void freeParentArray(struct Parent *parents, int count);
void freeParentRecord(struct Parent *p);

/* Operations (dynamic-only) */
void listParents(struct Parent *parents, int parentCount);
void addParent(struct Parent **parents, int *parentCount, int *parentCapacity);
void deleteParent(struct Parent *parents, int *parentCount);

#endif