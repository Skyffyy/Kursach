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

//  Static array 
void listStudentsStatic(struct Student students[], int count) {
    if(count==0){printf("Student list empty.\n"); return;}
    for(int i=0;i<count;i++){
        printf("%d. %s %s, born %d, class %d, avg %.2f\n",
               i+1, students[i].name, students[i].surname,
               students[i].birthYear, students[i].classNumber,
               students[i].averageGrade);
    }
}

void addStudentStatic(struct Student students[], int *count){
    if(*count>=MAX_STUDENTS){printf("Database full.\n"); return;}
    struct Student *s=&students[*count];
    printf("First name: "); scanf("%49s", s->name);
    printf("Last name: "); scanf("%49s", s->surname);
    printf("Birth year: "); scanf("%d", &s->birthYear);
    printf("Class number: "); scanf("%d", &s->classNumber);
    printf("Average grade: "); scanf("%f", &s->averageGrade);
    (*count)++;
    printf("✅ Student added (static array).\n");
}

void deleteStudentStatic(struct Student students[], int *count){
    if(*count==0){printf("Database empty.\n"); return;}
    char name[MAX_NAME], surname[MAX_NAME];
    printf("Enter first name: "); scanf("%49s", name);
    printf("Enter last name: "); scanf("%49s", surname);
    int found=0;
    for(int i=0;i<*count;i++){
        if(strEqual(students[i].name,name) && strEqual(students[i].surname,surname)){
            for(int j=i;j<*count-1;j++) students[j]=students[j+1];
            (*count)--;
            found=1;
            printf("❌ Student %s %s deleted (static array).\n", name, surname);
            break;
        }
    }
    if(!found) printf("Student %s %s not found.\n", name, surname);
}

//Dynamic array 
struct Student* createStudentArray(int initialCapacity){
    struct Student *arr=(struct Student*)malloc(sizeof(struct Student)*initialCapacity);
    if(!arr){printf("Memory allocation failed.\n"); return NULL;}
    return arr;
}

void freeStudentArray(struct Student *students){ free(students); }

void addStudentDynamic(struct Student **students, int *count, int *capacity){
    if(*count>=*capacity){
        int newCap=(*capacity)*2;
        struct Student *newArr=(struct Student*)realloc(*students,sizeof(struct Student)*newCap);
        if(!newArr){printf("Memory allocation failed.\n"); return;}
        *students=newArr;
        *capacity=newCap;
    }
    struct Student *s=&((*students)[*count]);
    printf("First name: "); scanf("%49s", s->name);
    printf("Last name: "); scanf("%49s", s->surname);
    printf("Birth year: "); scanf("%d", &s->birthYear);
    printf("Class number: "); scanf("%d", &s->classNumber);
    printf("Average grade: "); scanf("%f", &s->averageGrade);
    (*count)++;
    printf("✅ Student added (dynamic array).\n");
}

void deleteStudentDynamic(struct Student **students, int *count){
    if(*count==0){printf("Dynamic array empty.\n"); return;}
    char name[MAX_NAME], surname[MAX_NAME];
    printf("Enter first name: "); scanf("%49s", name);
    printf("Enter last name: "); scanf("%49s", surname);
    int found=0;
    for(int i=0;i<*count;i++){
        if(strEqual((*students)[i].name,name) && strEqual((*students)[i].surname,surname)){
            for(int j=i;j<*count-1;j++) (*students)[j]=(*students)[j+1];
            (*count)--;
            found=1;
            printf("❌ Student %s %s deleted (dynamic array).\n", name, surname);
            break;
        }
    }
    if(!found) printf("Student %s %s not found.\n", name, surname);
}

void listStudentsDynamic(struct Student *students, int count){
    if(count==0){printf("Dynamic student list empty.\n"); return;}
    for(int i=0;i<count;i++){
        printf("%d. %s %s, born %d, class %d, avg %.2f\n",
               i+1, students[i].name, students[i].surname,
               students[i].birthYear, students[i].classNumber,
               students[i].averageGrade);
    }
}

// Wrappers 
void listStudents(struct Student *students, int count){ listStudentsStatic(students,count); }
void addStudent(struct Student *students, int *count, int *capacity, int dynamic){
    if(dynamic) addStudentDynamic(&students,count,capacity);
    else addStudentStatic(students,count);
}
void deleteStudent(struct Student *students, int *count, int *capacity, int dynamic){
    (void)capacity; 

    if(dynamic) deleteStudentDynamic(&students, count);
    else deleteStudentStatic(students, count);
}

