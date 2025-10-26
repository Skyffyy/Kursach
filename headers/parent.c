#include <stdio.h>
#include <stdlib.h>
#include "parent.h"

struct Parent* findParentByID(struct Parent parents[], int parentCount, const char *id){
    for(int i=0;i<parentCount;i++)
        if(strEqual(parents[i].personalID,id)) return &parents[i];
    return NULL;
}

void showParentAndChildren(struct Parent parents[], int parentCount,
                           struct Student students[], int studentCount, const char *parentID){
    struct Parent *p = findParentByID(parents,parentCount,parentID);
    if(!p){ printf("Parent ID %s not found.\n", parentID); return; }

    printf("Parent: %s %s, ID: %s\nEmail: %s\nPhone: %s\nBirth: %s\nGender: %s\n",
           p->name, p->surname, p->personalID, p->email, p->phone, p->birthDate, p->gender);
    printf("Children:\n");
    for(int i=0;i<p->childCount;i++){
        for(int j=0;j<studentCount;j++){
            if(strEqual(students[j].personalID,p->childPersonalIDs[i])){
                struct Student s = students[j];
                printf("  - %s %s, ID: %s, Grade: %.2f\n",
                       s.name, s.surname, s.personalID, s.averageGrade);
            }
        }
    }
}

// Static
void listParentsStatic(struct Parent parents[], int parentCount){
    if(parentCount==0){ printf("Parent list empty.\n"); return; }
    for(int i=0;i<parentCount;i++){
        struct Parent p = parents[i];
        printf("%d. %s %s, ID: %s\nEmail: %s\nPhone: %s\nBirth: %s\nGender: %s\n",
               i+1, p.name, p.surname, p.personalID, p.email, p.phone, p.birthDate, p.gender);
    }
}

void addParentStatic(struct Parent parents[], int *parentCount){
    if(*parentCount>=MAX_PARENTS){ printf("Parent database full.\n"); return; }
    struct Parent *p = &parents[*parentCount];
    printf("Parent first name: "); scanf("%49s", p->name);
    printf("Parent surname: "); scanf("%49s", p->surname);
    printf("Parent personal ID: "); scanf("%19s", p->personalID);
    printf("Parent email: "); scanf("%99s", p->email);
    printf("Parent phone: "); scanf("%19s", p->phone);
    printf("Parent birth date: "); scanf("%19s", p->birthDate);
    printf("Parent gender: "); scanf("%9s", p->gender);
    p->childCount = 0;
    (*parentCount)++;
    printf("✅ Parent added.\n");
}

void deleteParentStatic(struct Parent parents[], int *parentCount){
    if(*parentCount==0){ printf("Parent database empty.\n"); return; }
    char pid[20]; printf("Enter parent ID to delete: "); scanf("%19s", pid);
    int found = 0;
    for(int i=0;i<*parentCount;i++){
        if(strEqual(parents[i].personalID,pid)){
            for(int j=i;j<*parentCount-1;j++) parents[j]=parents[j+1];
            (*parentCount)--;
            found=1;
            printf("Parent deleted.\n");
            break;
        }
    }
    if(!found) printf("Parent not found.\n");
}

// Dynamic
struct Parent* createParentArray(int initialCapacity){
    return malloc(sizeof(struct Parent)*initialCapacity);
}
void freeParentArray(struct Parent *parents){ free(parents); }
void addParentDynamic(struct Parent **parents, int *parentCount, int *capacity){
    if(*parentCount>=*capacity){
        int newCap = (*capacity)*2;
        *parents = realloc(*parents,sizeof(struct Parent)*newCap);
        *capacity = newCap;
    }
    addParentStatic(*parents,parentCount);
}
void deleteParentDynamic(struct Parent **parents, int *parentCount){
    deleteParentStatic(*parents,parentCount);
}
