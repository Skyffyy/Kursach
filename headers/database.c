#include <stdio.h>
#include "database.h"
#include "student.h"
#include "parent.h"
#include "utils.h"

void loadDatabase(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount){
    FILE *f = fopen(DATABASE_FILE, "r");
    if(!f){ *studentCount = 0; *parentCount = 0; return; }

    if(fscanf(f, "%d\n", studentCount) != 1) *studentCount = 0;
    if(fscanf(f, "%d\n", parentCount) != 1) *parentCount = 0;

    for(int i=0;i<*studentCount;i++){
        struct Student *s = &students[i];
        fscanf(f, "%49s %49s %19s %9s %99s %19s %d %d %d %9s %f\n",
               s->name, s->surname, s->personalID, s->class, s->email, s->phone,
               &s->birthDay, &s->birthMonth, &s->birthYear, s->gender, &s->averageGrade);
        fscanf(f, "%d", &s->parentCount);
        for(int p=0;p<s->parentCount;p++) fscanf(f, " %19s", s->parentPersonalIDs[p]);
        fscanf(f, "\n");
    }

    for(int i=0;i<*parentCount;i++){
        struct Parent *p = &parents[i];
        fscanf(f, "%49s %49s %19s %99s %19s %d %d %d %9s %d",
               p->name, p->surname, p->personalID, p->email, p->phone,
               &p->birthDay, &p->birthMonth, &p->birthYear, p->gender, &p->childCount);
        for(int c=0;c<p->childCount;c++) fscanf(f, " %19s", p->childPersonalIDs[c]);
        fscanf(f, "\n");
    }

    fclose(f);
}

void saveDatabase(struct Student students[], struct Parent parents[], int studentCount, int parentCount){
    FILE *f = fopen(DATABASE_FILE, "w");
    if(!f) return;
    fprintf(f, "%d\n", studentCount);
    fprintf(f, "%d\n", parentCount);

    for(int i=0;i<studentCount;i++){
        struct Student *s = &students[i];
        fprintf(f, "%s %s %s %s %s %s %d %d %d %s %.2f\n",
                s->name, s->surname, s->personalID, s->class, s->email, s->phone,
                s->birthDay, s->birthMonth, s->birthYear, s->gender, s->averageGrade);
        fprintf(f, "%d", s->parentCount);
        for(int p=0;p<s->parentCount;p++) fprintf(f, " %s", s->parentPersonalIDs[p]);
        fprintf(f, "\n");
    }

    for(int i=0;i<parentCount;i++){
        struct Parent *p = &parents[i];
        fprintf(f, "%s %s %s %s %s %d %d %d %s %d",
                p->name, p->surname, p->personalID, p->email, p->phone,
                p->birthDay, p->birthMonth, p->birthYear, p->gender, p->childCount);
        for(int c=0;c<p->childCount;c++) fprintf(f, " %s", p->childPersonalIDs[c]);
        fprintf(f, "\n");
    }

    fclose(f);
}