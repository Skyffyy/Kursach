#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 100
#define MAX_STUDENTS 100
#define MAX_PARENTS 100

// Parent structure
struct Parent {
    int id;
    char name[MAX_NAME];
    char surname[MAX_NAME];
    char personalID[20];
    char email[100];
    char phone[20];
    char birthDate[20];
    char gender[10];
};

// Student structure
struct Student {
    int id;
    char name[MAX_NAME];
    char surname[MAX_NAME];
    char personalID[20];
    char email[100];
    char phone[20];
    char birthDate[20];
    char gender[10];
    int parentCount;
    int parentIDs[2];
};

// Static array operations 
void listStudentsStatic(struct Student students[], struct Parent parents[], int studentCount, int parentCount);
void addStudentStatic(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount);
void deleteStudentStatic(struct Student students[], int *studentCount);

//  Dynamic array operations 
struct Student* createStudentArray(int initialCapacity);
void freeStudentArray(struct Student *students);
void addStudentDynamic(struct Student **students, struct Parent **parents, int *studentCount, int *parentCount, int *capacity);
void deleteStudentDynamic(struct Student **students, int *studentCount);
void listStudentsDynamic(struct Student *students, struct Parent *parents, int studentCount, int parentCount);

//Wrappers 
void listStudents(struct Student *students, struct Parent *parents, int studentCount, int parentCount);
void addStudent(struct Student *students, struct Parent *parents, int *studentCount, int *parentCount, int dynamic, int *capacity);
void deleteStudent(struct Student *students, int *studentCount, int *parentCount, int dynamic);

// Utility 
int strEqual(const char *a, const char *b);

#endif
