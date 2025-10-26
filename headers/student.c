#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "utils.h"

struct Student* createStudentArray(int initialCapacity){
    struct Student *arr = malloc(sizeof(struct Student)*initialCapacity);
    if(!arr){ printf("Memory allocation failed\n"); return NULL; }
    return arr;
}

void freeStudentArray(struct Student *students){ free(students); }

void listStudentsStatic(struct Student students[], int studentCount, struct Parent parents[], int parentCount){
    if(studentCount==0){ printf("No students\n"); return; }
    for(int i=0;i<studentCount;i++){
        struct Student s = students[i];
        printf("%d. %s %s, ID: %s, Grade: %.2f\n", i+1, s.name, s.surname, s.personalID, s.averageGrade);
        for(int j=0;j<s.parentCount;j++){
            char *pid = s.parentPersonalIDs[j];
            for(int k=0;k<parentCount;k++){
                if(strEqual(parents[k].personalID,pid)){
                    struct Parent p = parents[k];
                    printf(" Parent: %s %s, ID: %s\n", p.name, p.surname, p.personalID);
                    break;
                }
            }
        }
    }
}

void addStudentStatic(struct Student students[], int *studentCount, struct Parent parents[], int *parentCount){
    if(*studentCount>=MAX_STUDENTS){ printf("Student database full\n"); return; }
    struct Student *s = &students[*studentCount];
    printf("Name: "); scanf("%49s", s->name);
    printf("Surname: "); scanf("%49s", s->surname);
    printf("ID: "); scanf("%19s", s->personalID);
    printf("Email: "); scanf("%99s", s->email);
    printf("Phone: "); scanf("%19s", s->phone);
    printf("BirthDate: "); scanf("%19s", s->birthDate);
    printf("Gender: "); scanf("%9s", s->gender);
    printf("Average Grade: "); scanf("%f", &s->averageGrade);
    printf("Number of parents: "); scanf("%d", &s->parentCount);
    for(int i=0;i<s->parentCount;i++){
        if(*parentCount>=MAX_PARENTS) break;
        struct Parent *p = &parents[*parentCount];
        printf("Parent %d Name: ", i+1); scanf("%49s", p->name);
        printf("Surname: "); scanf("%49s", p->surname);
        printf("ID: "); scanf("%19s", p->personalID);
        printf("Email: "); scanf("%99s", p->email);
        printf("Phone: "); scanf("%19s", p->phone);
        printf("BirthDate: "); scanf("%19s", p->birthDate);
        printf("Gender: "); scanf("%9s", p->gender);
        strCopy(s->parentPersonalIDs[i], p->personalID);
        (*parentCount)++;
    }
    (*studentCount)++;
}

void deleteStudentStatic(struct Student students[], int *studentCount){
    char id[20];
    printf("Enter student ID to delete: "); scanf("%19s", id);
    int found=0;
    for(int i=0;i<*studentCount;i++){
        if(strEqual(students[i].personalID,id)){
            for(int j=i;j<*studentCount-1;j++) students[j]=students[j+1];
            (*studentCount)--;
            found=1;
            printf("Student deleted\n");
            break;
        }
    }
    if(!found) printf("Student not found\n");
}

void addStudentDynamic(struct Student **students, struct Parent **parents, int *studentCount, int *parentCount, int *capacity){
    if(*studentCount>=*capacity){
        int newCap = (*capacity)*2;
        struct Student *newArr = realloc(*students,sizeof(struct Student)*newCap);
        struct Parent *newParents = realloc(*parents,sizeof(struct Parent)*newCap);
        if(!newArr || !newParents){ printf("Memory allocation failed\n"); return; }
        *students = newArr; *parents = newParents; *capacity = newCap;
    }
    addStudentStatic(*students, studentCount, *parents, parentCount);
}

void deleteStudentDynamic(struct Student **students, int *studentCount){
    deleteStudentStatic(*students, studentCount);
}

void listStudentsDynamic(struct Student *students, int studentCount, struct Parent *parents, int parentCount){
    listStudentsStatic(students, studentCount, parents, parentCount);
}
