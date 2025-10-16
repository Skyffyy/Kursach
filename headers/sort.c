#include "sort.h"

int strCompare(const char *a, const char *b){
    int i=0;
    while(a[i] && b[i]){
        if(a[i]!=b[i]) return a[i]-b[i];
        i++;
    }
    return a[i]-b[i];
}

void sortByName(struct Student students[], int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(strCompare(students[j].name, students[j+1].name)>0){
                struct Student tmp=students[j];
                students[j]=students[j+1];
                students[j+1]=tmp;
            }
        }
    }
}

void sortByBirthYear(struct Student students[], int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(students[j].birthYear>students[j+1].birthYear){
                struct Student tmp=students[j];
                students[j]=students[j+1];
                students[j+1]=tmp;
            }
        }
    }
}

void sortByGrade(struct Student students[], int count){
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(students[j].averageGrade<students[j+1].averageGrade){
                struct Student tmp=students[j];
                students[j]=students[j+1];
                students[j+1]=tmp;
            }
        }
    }
}
