#include <stdio.h>
#include <stdlib.h>
#include "student.h"

// Utility
int strEqual(const char *a, const char *b){
    int i = 0;
    while(a[i] && b[i]){
        if(a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

// Static array functions
void listStudentsStatic(struct Student students[], struct Parent parents[], int studentCount, int parentCount){
    if(studentCount==0){ printf("Student list empty.\n"); return; }
    for(int i=0;i<studentCount;i++){
        struct Student s = students[i];
        printf("%d. %s %s, Birth: %s, Email: %s, Phone: %s, Gender: %s, Grade: %.2f\n",
               i+1, s.name, s.surname, s.birthDate, s.email, s.phone, s.gender, s.averageGrade);
        if(s.parentCount > 0){
            printf("   Parents:\n");
            for(int j=0;j<s.parentCount;j++){
                char *pid = s.parentPersonalIDs[j];
                int found = 0;
                for(int k=0;k<parentCount;k++){
                    if(strEqual(parents[k].personalID, pid)){
                        struct Parent p = parents[k];
                        printf("     - %s %s, Birth: %s, Email: %s, Phone: %s, Gender: %s\n",
                               p.name, p.surname, p.birthDate, p.email, p.phone, p.gender);
                        found = 1;
                        break;
                    }
                }
                if(!found) printf("     - Parent ID %s not found\n", pid);
            }
        }
    }
}

void addStudentStatic(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount){
    if(*studentCount >= MAX_STUDENTS){ printf("Database full.\n"); return; }
    struct Student *s = &students[*studentCount];

    printf("First name: "); scanf("%49s", s->name);
    printf("Surname: "); scanf("%49s", s->surname);
    printf("Personal ID: "); scanf("%19s", s->personalID);
    printf("Email: "); scanf("%99s", s->email);
    printf("Phone: "); scanf("%19s", s->phone);
    printf("Birth date: "); scanf("%19s", s->birthDate);
    printf("Gender: "); scanf("%9s", s->gender);
    printf("Average grade: "); scanf("%f", &s->averageGrade);
    printf("Birth year: "); scanf("%d", &s->birthYear);

    printf("Does the student have parents? (0/1): ");
    int hasParents; scanf("%d", &hasParents);
    s->parentCount = 0;
    if(hasParents){
        int numParents = 0;
        printf("How many parents? (1 or 2): "); scanf("%d", &numParents);
        if(numParents>MAX_PARENTS_PER_STUDENT) numParents = MAX_PARENTS_PER_STUDENT;

        for(int i=0;i<numParents;i++){
            if(*parentCount >= MAX_PARENTS){
                printf("Parent database full.\n"); break;
            }
            struct Parent *p = &parents[*parentCount];
            printf("Parent %d first name: ", i+1); scanf("%49s", p->name);
            printf("Parent %d surname: ", i+1); scanf("%49s", p->surname);
            printf("Parent %d personal ID: ", i+1); scanf("%19s", p->personalID);
            printf("Parent %d email: ", i+1); scanf("%99s", p->email);
            printf("Parent %d phone: ", i+1); scanf("%19s", p->phone);
            printf("Parent %d birth date: ", i+1); scanf("%19s", p->birthDate);
            printf("Parent %d gender: ", i+1); scanf("%9s", p->gender);

            s->parentCount++;
            for(int k=0;k<20;k++) s->parentPersonalIDs[i][k] = p->personalID[k];

            (*parentCount)++;
        }
    }

    (*studentCount)++;
    printf("✅ Student added.\n");
}

void deleteStudentStatic(struct Student students[], int *studentCount){
    if(*studentCount==0){ printf("Database empty.\n"); return; }
    char pid[20];
    printf("Enter student personal ID to delete: "); scanf("%19s", pid);
    int found = 0;
    for(int i=0;i<*studentCount;i++){
        if(strEqual(students[i].personalID, pid)){
            for(int j=i;j<*studentCount-1;j++) students[j]=students[j+1];
            (*studentCount)--;
            found = 1;
            printf("Student deleted.\n");
            break;
        }
    }
    if(!found) printf("Student not found.\n");
}

// Dynamic arrays
struct Student* createStudentArray(int initialCapacity){
    struct Student *arr = malloc(sizeof(struct Student)*initialCapacity);
    if(!arr){ printf("Memory allocation failed.\n"); return NULL; }
    return arr;
}

struct Parent* createParentArray(int initialCapacity){
    struct Parent *arr = malloc(sizeof(struct Parent)*initialCapacity);
    if(!arr){ printf("Memory allocation failed.\n"); return NULL; }
    return arr;
}

void freeStudentArray(struct Student *students){ free(students); }
void freeParentArray(struct Parent *parents){ free(parents); }

void addStudentDynamic(struct Student **students, struct Parent **parents, int *studentCount, int *parentCount, int *capacity){
    if(*studentCount >= *capacity){
        int newCap = (*capacity)*2;
        struct Student *newArr = realloc(*students, sizeof(struct Student)*newCap);
        struct Parent *newParents = realloc(*parents, sizeof(struct Parent)*newCap);
        if(!newArr || !newParents){ printf("Memory allocation failed.\n"); return; }
        *students = newArr; *parents = newParents; *capacity = newCap;
    }
    addStudentStatic(*students, *parents,
