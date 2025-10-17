#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50
#define MAX_STUDENTS 100
#define MAX_PARENTS 100
#define MAX_PARENTS_PER_STUDENT 2

struct Parent {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    char personalID[20];  
    char email[100];
    char phone[20];
    char birthDate[20];
    char gender[10];
};

struct Student {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    char personalID[20]; 
    char email[100];
    char phone[20];
    char birthDate[20];
    char gender[10];

    float averageGrade;
    int birthYear;

    int parentCount;
    char parentPersonalIDs[MAX_PARENTS_PER_STUDENT][20];
};

// Utility
int strEqual(const char *a, const char *b);

// Static array operations
void listStudentsStatic(struct Student students[], struct Parent parents[], int studentCount, int parentCount);
void addStudentStatic(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount);
void deleteStudentStatic(struct Student students[], int *studentCount);

// Dynamic array operations
struct Student* createStudentArray(int initialCapacity);
void freeStudentArray(struct Student *students);
struct Parent* createParentArray(int initialCapacity);
void freeParentArray(struct Parent *parents);

void addStudentDynamic(struct Student **students, struct Parent **parents, int *studentCount, int *parentCount, int *capacity);
void deleteStudentDynamic(struct Student **students, int *studentCount);
void listStudentsDynamic(struct Student *students, struct Parent *parents, int studentCount, int parentCount);

#endif
