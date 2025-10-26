#include <stdio.h>
#include "database.h"
#include "student.h"
#include "parent.h"
#include "utils.h"

void loadDatabase(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount){
    FILE *f = fopen(DATABASE_FILE, "r");
    if(!f){
        *studentCount = 0;
        *parentCount = 0;
        return;
    }

    *studentCount = 0;
    *parentCount = 0;
    char type;

    while(fscanf(f, " %c", &type) == 1){
        if(type == 'P'){
            struct Parent *p = &parents[*parentCount];
            fscanf(f, " %49s %49s %19s %99s %19s %d %d %d %9s %d",
                   p->name, p->surname, p->personalID, p->email, p->phone,
                   &p->birthDay, &p->birthMonth, &p->birthYear, p->gender, &p->childCount);
            for(int i=0; i<p->childCount; i++)
                fscanf(f, " %19s", p->childPersonalIDs[i]);
            (*parentCount)++;
        }
        else if(type == 'S'){
            struct Student *s = &students[*studentCount];
            s->parentCount = 0;
            fscanf(f, " %49s %49s %19s %99s %19s %d %d %d %9s %f %d",
                   s->name, s->surname, s->personalID, s->email, s->phone,
                   &s->birthDay, &s->birthMonth, &s->birthYear, s->gender, &s->averageGrade, &s->parentCount);
            for(int i=0; i<s->parentCount; i++)
                fscanf(f, " %19s", s->parentPersonalIDs[i]);
            (*studentCount)++;
        }
    }

    fclose(f);
}

void saveDatabase(struct Student students[], struct Parent parents[], int studentCount, int parentCount){
    FILE *f = fopen(DATABASE_FILE, "w");
    if(!f) return;

    // Сохраняем родителей
    for(int i=0; i<parentCount; i++){
        struct Parent p = parents[i];
        fprintf(f, "P %s %s %s %s %s %d %d %d %s %d",
                p.name, p.surname, p.personalID, p.email, p.phone,
                p.birthDay, p.birthMonth, p.birthYear, p.gender, p.childCount);
        for(int j=0; j<p.childCount; j++)
            fprintf(f, " %s", p.childPersonalIDs[j]);
        fprintf(f, "\n");
    }

    // Сохраняем студентов
    for(int i=0; i<studentCount; i++){
        struct Student s = students[i];
        fprintf(f, "S %s %s %s %s %s %d %d %d %s %.2f %d",
                s.name, s.surname, s.personalID, s.email, s.phone,
                s.birthDay, s.birthMonth, s.birthYear, s.gender, s.averageGrade, s.parentCount);
        for(int j=0; j<s.parentCount; j++)
            fprintf(f, " %s", s.parentPersonalIDs[j]);
        fprintf(f, "\n");
    }

    fclose(f);
}