#include "sort.h"
#include "student.h"
#include "parent.h"
#include "utils.h"

/* Простые пузырьковые сортировки для небольших наборов данных */

void sortByName(struct Student *students, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            const char *a = students[j].name ? students[j].name : "";
            const char *b = students[j+1].name ? students[j+1].name : "";
            if(strCompare(a,b) > 0){
                struct Student t = students[j];
                students[j] = students[j+1];
                students[j+1] = t;
            }
        }
    }
}

void sortBySurname(struct Student *students, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            const char *a = students[j].surname ? students[j].surname : "";
            const char *b = students[j+1].surname ? students[j+1].surname : "";
            if(strCompare(a,b) > 0){
                struct Student t = students[j];
                students[j] = students[j+1];
                students[j+1] = t;
            }
        }
    }
}

void sortByBirthYear(struct Student *students, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(students[j].birthYear > students[j+1].birthYear){
                struct Student t = students[j];
                students[j] = students[j+1];
                students[j+1] = t;
            }
        }
    }
}

void sortByAverageGrade(struct Student *students, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(students[j].averageGrade < students[j+1].averageGrade){
                struct Student t = students[j];
                students[j] = students[j+1];
                students[j+1] = t;
            }
        }
    }
}

/* Parent sorts */

void sortParentsByName(struct Parent *parents, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            const char *a = parents[j].name ? parents[j].name : "";
            const char *b = parents[j+1].name ? parents[j+1].name : "";
            if(strCompare(a,b) > 0){
                struct Parent t = parents[j];
                parents[j] = parents[j+1];
                parents[j+1] = t;
            }
        }
    }
}

void sortParentsBySurname(struct Parent *parents, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            const char *a = parents[j].surname ? parents[j].surname : "";
            const char *b = parents[j+1].surname ? parents[j+1].surname : "";
            if(strCompare(a,b) > 0){
                struct Parent t = parents[j];
                parents[j] = parents[j+1];
                parents[j+1] = t;
            }
        }
    }
}

void sortParentsByPersonalID(struct Parent *parents, int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            const char *a = parents[j].personalID ? parents[j].personalID : "";
            const char *b = parents[j+1].personalID ? parents[j+1].personalID : "";
            if(strCompare(a,b) > 0){
                struct Parent t = parents[j];
                parents[j] = parents[j+1];
                parents[j+1] = t;
            }
        }
    }
}