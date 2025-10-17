#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void loadDatabase(struct Student students[], struct Parent parents[], int *studentCount, int *parentCount) {
    FILE *f = fopen(DATABASE_FILE, "r");
    if (!f) {
        f = fopen(DATABASE_FILE, "w");
        if (!f) { printf("Failed to create file %s\n", DATABASE_FILE); *studentCount=0; *parentCount=0; return; }
        fclose(f);
        printf("File %s not found. Created empty database.\n", DATABASE_FILE);
        *studentCount = 0;
        *parentCount = 0;
        return;
    }

    *studentCount = 0;
    *parentCount = 0;
    char type;
    while(fscanf(f," %c",&type)==1){
        if(type=='S'){
            struct Student *s = &students[*studentCount];
            int p1=-1,p2=-1;
            fscanf(f,"%d %99s %99s %19s %99s %19s %19s %9s %d %d %d",
                   &s->id, s->name, s->surname, s->personalID, s->email, s->phone,
                   s->birthDate, s->gender, &s->parentCount, &p1, &p2);
            s->parentIDs[0] = p1;
            s->parentIDs[1] = p2;
            (*studentCount)++;
        } else if(type=='P'){
            struct Parent *p = &parents[*parentCount];
            fscanf(f,"%d %99s %99s %19s %99s %19s %19s %9s",
                   &p->id, p->name, p->surname, p->personalID, p->email, p->phone,
                   p->birthDate, p->gender);
            (*parentCount)++;
        }
    }

    fclose(f);
}

void saveDatabase(struct Student students[], struct Parent parents[], int studentCount, int parentCount) {
    FILE *f = fopen(DATABASE_FILE, "w");
    if (!f){ printf("Failed to save file %s\n", DATABASE_FILE); return; }

    // parents
    for(int i=0;i<parentCount;i++){
        struct Parent p = parents[i];
        fprintf(f,"P %d %s %s %s %s %s %s %s\n",
                p.id, p.name, p.surname, p.personalID, p.email, p.phone, p.birthDate, p.gender);
    }

    // students
    for(int i=0;i<studentCount;i++){
        struct Student s = students[i];
        fprintf(f,"S %d %s %s %s %s %s %s %s %d %d %d\n",
                s.id, s.name, s.surname, s.personalID, s.email, s.phone, s.birthDate, s.gender,
                s.parentCount, s.parentIDs[0], s.parentIDs[1]);
    }

    fclose(f);
}
