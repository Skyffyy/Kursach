#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "utils.h"
#include "parent.h"

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
        printf("\n%d. Student: %s %s\n", i+1, s.name, s.surname);
        printf("   Personal ID: %s\n", s.personalID);
        printf("   Email: %s\n", s.email);
        printf("   Phone: %s\n", s.phone);
        printf("   Birth Date: %02d.%02d.%d\n", s.birthDay, s.birthMonth, s.birthYear);
        printf("   Gender: %s\n", s.gender);
        printf("   Average Grade: %.2f\n", s.averageGrade);
        
        printf("   Parents:\n");
        int displayedParents = 0;
        for(int j=0;j<s.parentCount;j++){
            char *pid = s.parentPersonalIDs[j];
            for(int k=0;k<parentCount;k++){
                if(strEqual(parents[k].personalID,pid)){
                    printf("     Parent %d:\n", displayedParents + 1);
                    printParentInfo(&parents[k]);
                    displayedParents++;
                    break;
                }
            }
        }
        if(displayedParents == 0) {
            printf("     No parents assigned\n");
        }
    }
}

void addStudentStatic(struct Student students[], int *studentCount, struct Parent parents[], int *parentCount){
    if(*studentCount>=MAX_STUDENTS){ printf("Student database full\n"); return; }
    struct Student *s = &students[*studentCount];
    
    printf("=== Adding New Student ===\n");
    printf("Name: "); scanf("%49s", s->name);
    printf("Surname: "); scanf("%49s", s->surname);
    printf("Personal ID: "); scanf("%19s", s->personalID);
    printf("Email: "); scanf("%99s", s->email);
    printf("Phone: "); scanf("%19s", s->phone);
    
    printf("Birth Day (1-31): "); scanf("%d", &s->birthDay);
    printf("Birth Month (1-12): "); scanf("%d", &s->birthMonth);
    printf("Birth Year: "); scanf("%d", &s->birthYear);
    
    printf("Gender: "); scanf("%9s", s->gender);
    printf("Average Grade: "); scanf("%f", &s->averageGrade);
    
    printf("Number of parents (0-2): "); scanf("%d", &s->parentCount);
    if(s->parentCount > 2) s->parentCount = 2;
    
    for(int i=0;i<s->parentCount;i++){
        if(*parentCount>=MAX_PARENTS) {
            printf("Cannot add more parents. Database full.\n");
            break;
        }
        
        printf("\n=== Adding Parent %d ===\n", i+1);
        struct Parent *p = &parents[*parentCount];
        
        printf("Parent Name: "); scanf("%49s", p->name);
        printf("Parent Surname: "); scanf("%49s", p->surname);
        printf("Parent Personal ID: "); scanf("%19s", p->personalID);
        printf("Parent Email: "); scanf("%99s", p->email);
        printf("Parent Phone: "); scanf("%19s", p->phone);
        
        printf("Parent Birth Day (1-31): "); scanf("%d", &p->birthDay);
        printf("Parent Birth Month (1-12): "); scanf("%d", &p->birthMonth);
        printf("Parent Birth Year: "); scanf("%d", &p->birthYear);
        
        printf("Parent Gender: "); scanf("%9s", p->gender);
        p->childCount = 0;
        
        strCopy(s->parentPersonalIDs[i], p->personalID);
        linkParentToStudent(p, s->personalID);
        
        (*parentCount)++;
        printf("Parent added and linked to student!\n");
    }
    (*studentCount)++;
    printf("=== Student added successfully! ===\n");
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