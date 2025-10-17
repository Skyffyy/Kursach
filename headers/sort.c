#include "sort.h"

// String comparison
int strCompare(const char *a, const char *b){
    int i = 0;
    while(a[i] && b[i]){
        if(a[i] != b[i]) return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

// ===== Student sorting =====
void sortByName(struct Student students[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(strCompare(students[j].name, students[j+1].name) > 0){
                struct Student tmp = students[j];
                students[j] = students[j+1];
                students[j+1] = tmp;
            }
}

void sortBySurname(struct Student students[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(strCompare(students[j].surname, students[j+1].surname) > 0){
                struct Student tmp = students[j];
                students[j] = students[j+1];
                students[j+1] = tmp;
            }
}

void sortByBirthYear(struct Student students[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(students[j].birthYear > students[j+1].birthYear){
                struct Student tmp = students[j];
                students[j] = students[j+1];
                students[j+1] = tmp;
            }
}

void sortByAverageGrade(struct Student students[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(students[j].averageGrade < students[j+1].averageGrade){
                struct Student tmp = students[j];
                students[j] = students[j+1];
                students[j+1] = tmp;
            }
}

// ===== Parent sorting =====
void sortParentsByName(struct Parent parents[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(strCompare(parents[j].name, parents[j+1].name) > 0){
                struct Parent tmp = parents[j];
                parents[j] = parents[j+1];
                parents[j+1] = tmp;
            }
}

void sortParentsBySurname(struct Parent parents[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(strCompare(parents[j].surname, parents[j+1].surname) > 0){
                struct Parent tmp = parents[j];
                parents[j] = parents[j+1];
                parents[j+1] = tmp;
            }
}

void sortParentsByPersonalID(struct Parent parents[], int count){
    for(int i=0;i<count-1;i++)
        for(int j=0;j<count-i-1;j++)
            if(strCompare(parents[j].personalID, parents[j+1].personalID) > 0){
                struct Parent tmp = parents[j];
                parents[j] = parents[j+1];
                parents[j+1] = tmp;
            }
}
