#include <stdio.h>
#include <stdlib.h>
#include "student.h"

// Utility
int strEqual(const char *a, const char *b) {
    int i = 0;
    while(a[i] && b[i]) { 
        if(a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

// Static array
void listStudentsStatic(struct Student students[], struct Parent parents[], int studentCount, int parentCount) {
    if(studentCount==0){printf("Student list empty.\n"); return;}
    for(int i=0;i<studentCount;i++){
        struct Student s = students[i];
        printf("%d. %s %s, birth %s, email %s, phone %s, gender %s\n",
               i+1, s.name, s.surname, s.birthDate, s.email, s.phone, s.gender);
        printf("   Parents (%d):\n", s.parentCount);
        for(int j=0;j<s.parentCount;j++){
            int pid = s.parentIDs[j];
            if(pid>0 && pid<=parentCount){
                struct Parent p = parents[pid-1];
                printf("      - %s %s, email %s, phone %s\n", p.name, p.surname, p.email, p.phone);
            }
        }
    }
}

int addParentInteractive(struct Parent parents[], int *parentCount){
    if(*parentCount >= MAX_PARENTS){printf("Parent database full.\n"); return -1;}
    struct Parent *p = &parents[*parentCount];
    p->id = (*parentCount) + 1;

    printf("Parent first name: "); scanf("%99s", p->name);
    printf("Parent last name: "); scanf("%99s", p->surname);
    printf("Personal ID: "); scanf("%19s", p->personalID);
    printf("Email: "); scanf("%99s", p->email);
    printf("Phone: "); scanf("%19s", p->phone);
    printf("Birth date (YYYY-MM-DD): "); scanf("%19s", p->birthDate);
    printf("Gender (M/F): "); scanf("%9s", p->gender);

    (*parentCount)++;
    printf("Parent added with ID %d\n", p->id);
    return p->id;
}

void addStudentStatic(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount){
    if(*studentCount >= MAX_STUDENTS){printf("Student database full.\n"); return;}
    struct Student *s = &students[*studentCount];
    s->id = (*studentCount)+1;

    printf("Student first name: "); scanf("%99s", s->name);
    printf("Student last name: "); scanf("%99s", s->surname);
    printf("Personal ID: "); scanf("%19s", s->personalID);
    printf("Email: "); scanf("%99s", s->email);
    printf("Phone: "); scanf("%19s", s->phone);
    printf("Birth date (YYYY-MM-DD): "); scanf("%19s", s->birthDate);
    printf("Gender (M/F): "); scanf("%9s", s->gender);

    printf("How many parents (1 or 2): ");
    scanf("%d", &s->parentCount);
    if(s->parentCount<1) s->parentCount=1;
    if(s->parentCount>2) s->parentCount=2;

    for(int i=0;i<s->parentCount;i++){
        printf("Is parent #%d already in system? (y/n): ", i+1);
        char ans; scanf(" %c", &ans);
        if(ans=='y'||ans=='Y'){
            int pid;
            printf("Enter parent ID: "); scanf("%d", &pid);
            s->parentIDs[i] = pid;
        } else {
            int newID = addParentInteractive(parents, parentCount);
            s->parentIDs[i] = newID;
        }
    }

    (*studentCount)++;
    printf("✅ Student added.\n");
}

void deleteStudentStatic(struct Student students[], int *studentCount){
    if(*studentCount==0){printf("Database empty.\n"); return;}
    char name[MAX_NAME], surname[MAX_NAME];
    printf("Enter first name: "); scanf("%99s", name);
    printf("Enter last name: "); scanf("%99s", surname);
    int found=0;
    for(int i=0;i<*studentCount;i++){
        if(strEqual(students[i].name,name) && strEqual(students[i].surname,surname)){
            for(int j=i;j<*studentCount-1;j++) students[j]=students[j+1];
            (*studentCount)--;
            found=1;
            printf("❌ Student %s %s deleted.\n", name, surname);
            break;
        }
    }
    if(!found) printf("Student %s %s not found.\n", name, surname);
}

// Dynamic array 
struct Student* createStudentArray(int initialCapacity){
    struct Student *arr=(struct Student*)malloc(sizeof(struct Student)*initialCapacity);
    if(!arr){printf("Memory allocation failed.\n"); return NULL;}
    return arr;
}

void freeStudentArray(struct Student *students){ free(students); }

void addStudentDynamic(struct Student **students, struct Parent **parents, int *studentCount, int *parentCount, int *capacity){
    if(*studentCount >= *capacity){
        int newCap = (*capacity)*2;
        struct Student *newArr = (struct Student*)realloc(*students, sizeof(struct Student)*newCap);
        if(!newArr){printf("Memory allocation failed.\n"); return;}
        *students = newArr;
        *capacity = newCap;
    }

    struct Student *s = &((*students)[*studentCount]);
    s->id = (*studentCount)+1;

    printf("Student first name: "); scanf("%99s", s->name);
    printf("Student last name: "); scanf("%99s", s->surname);
    printf("Personal ID: "); scanf("%19s", s->personalID);
    printf("Email: "); scanf("%99s", s->email);
    printf("Phone: "); scanf("%19s", s->phone);
    printf("Birth date (YYYY-MM-DD): "); scanf("%19s", s->birthDate);
    printf("Gender (M/F): "); scanf("%9s", s->gender);

    printf("How many parents (1 or 2): ");
    scanf("%d", &s->parentCount);
    if(s->parentCount<1) s->parentCount=1;
    if(s->parentCount>2) s->parentCount=2;

    for(int i=0;i<s->parentCount;i++){
        printf("Is parent #%d already in system? (y/n): ", i+1);
        char ans; scanf(" %c", &ans);
        if(ans=='y'||ans=='Y'){
            int pid;
            printf("Enter parent ID: "); scanf("%d", &pid);
            s->parentIDs[i] = pid;
        } else {
            if(*parentCount >= MAX_PARENTS){
                printf("Parent database full.\n"); s->parentIDs[i]=-1; continue;
            }
            struct Parent *p = &((*parents)[*parentCount]);
            p->id = (*parentCount)+1;

            printf("Parent first name: "); scanf("%99s", p->name);
            printf("Parent last name: "); scanf("%99s", p->surname);
            printf("Personal ID: "); scanf("%19s", p->personalID);
            printf("Email: "); scanf("%99s", p->email);
            printf("Phone: "); scanf("%19s", p->phone);
            printf("Birth date (YYYY-MM-DD): "); scanf("%19s", p->birthDate);
            printf("Gender (M/F): "); scanf("%9s", p->gender);

            s->parentIDs[i] = p->id;
            (*parentCount)++;
            printf("Parent added with ID %d\n", p->id);
        }
    }

    (*studentCount)++;
    printf("✅ Student added (dynamic array with parents).\n");
}

void deleteStudentDynamic(struct Student **students, int *studentCount){
    if(*studentCount==0){printf("Dynamic array empty.\n"); return;}
    char name[MAX_NAME], surname[MAX_NAME];
    printf("Enter first name: "); scanf("%99s", name);
    printf("Enter last name: "); scanf("%99s", surname);
    int found=0;
    for(int i=0;i<*studentCount;i++){
        if(strEqual((*students)[i].name,name) && strEqual((*students)[i].surname,surname)){
            for(int j=i;j<*studentCount-1;j++) (*students)[j]=(*students)[j+1];
            (*studentCount)--;
            found=1;
            printf("❌ Student %s %s deleted.\n", name, surname);
            break;
        }
    }
    if(!found) printf("Student %s %s not found.\n", name, surname);
}

void listStudentsDynamic(struct Student *students, struct Parent *parents, int studentCount, int parentCount){
    if(studentCount==0){printf("Dynamic student list empty.\n"); return;}
    for(int i=0;i<studentCount;i++){
        struct Student s = students[i];
        printf("%d. %s %s, birth %s, email %s, phone %s, gender %s\n",
               i+1, s.name, s.surname, s.birthDate, s.email, s.phone, s.gender);
        printf("   Parents (%d):\n", s.parentCount);
        for(int j=0;j<s.parentCount;j++){
            int pid = s.parentIDs[j];
            if(pid>0 && pid<=
