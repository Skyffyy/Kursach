#ifndef PARENT_H
#define PARENT_H

#include "student.h"
#include "utils.h"

#define MAX_PARENTS 100
#define MAX_CHILDREN 10

struct Parent {
    char name[50];
    char surname[50];
    char personalID[20];
    char email[100];
    char phone[20];
    char birthDate[20];
    char gender[10];

    int childCount;
    char childPersonalIDs[MAX_CHILDREN][20];
};

// Utility
struct Parent* findParentByID(struct Parent parents[], int parentCount, const char *id);
void showParentAndChildren(struct Parent parents[], int parentCount,
                           struct Student students[], int studentCount, const char *parentID);

// Static
void listParentsStatic(struct Parent parents[], int parentCount);
void addParentStatic(struct Parent parents[], int *parentCount);
void deleteParentStatic(struct Parent parents[], int *parentCount);

// Dynamic
struct Parent* createParentArray(int initialCapacity);
void freeParentArray(struct Parent *parents);
void addParentDynamic(struct Parent **parents, int *parentCount, int *capacity);
void deleteParentDynamic(struct Parent **parents, int *parentCount);

#endif
