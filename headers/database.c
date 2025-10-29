#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "student.h"
#include "parent.h"
#include "utils.h"

void loadDatabase(struct Student **students, struct Parent **parents,
                  int *studentCount, int *parentCount, int *studentCapacity, int *parentCapacity){
    FILE *f = fopen(DATABASE_FILE, "r");
    if(!f){
        *studentCount = 0;
        *parentCount = 0;
        return;
    }

    int sc = 0, pc = 0;
    if(fscanf(f, "%d\n", &sc) != 1) sc = 0;
    if(fscanf(f, "%d\n", &pc) != 1) pc = 0;

    /* ensure student capacity */
    if(*studentCapacity < sc){
        int cap = sc > 0 ? sc : *studentCapacity;
        struct Student *ns = realloc(*students, sizeof(struct Student) * cap);
        if(!ns){ printf("Memory allocation failed\n"); fclose(f); return; }
        *students = ns;
        *studentCapacity = cap;
    }

    if(*parentCapacity < pc){
        int cap = pc > 0 ? pc : *parentCapacity;
        struct Parent *np = realloc(*parents, sizeof(struct Parent) * cap);
        if(!np){ printf("Memory allocation failed\n"); fclose(f); return; }
        *parents = np;
        *parentCapacity = cap;
    }

    /* initialize records to NULL to be safe */
    for(int i=0;i<*studentCapacity;i++){
        (*students)[i].name = (*students)[i].surname = (*students)[i].personalID = NULL;
        (*students)[i].email = (*students)[i].phone = (*students)[i].class = NULL;
        (*students)[i].gender = NULL;
        (*students)[i].parentCount = 0;
        (*students)[i].parentPersonalIDs[0] = (*students)[i].parentPersonalIDs[1] = NULL;
        (*students)[i].birthDay = (*students)[i].birthMonth = (*students)[i].birthYear = 0;
        (*students)[i].averageGrade = 0.0f;
    }
    for(int i=0;i<*parentCapacity;i++){
        (*parents)[i].name = (*parents)[i].surname = (*parents)[i].personalID = NULL;
        (*parents)[i].email = (*parents)[i].phone = NULL; (*parents)[i].gender = NULL;
        (*parents)[i].childCount = 0;
        for(int c=0;c<MAX_CHILDREN;c++) (*parents)[i].childPersonalIDs[c] = NULL;
        (*parents)[i].birthDay = (*parents)[i].birthMonth = (*parents)[i].birthYear = 0;
    }

    /* read students */
    for(int i=0;i<sc;i++){
        char buf_name[256], buf_surname[256], buf_pid[256], buf_class[256], buf_email[256], buf_phone[256], buf_gender[256];
        int bd=0,bm=0,by=0;
        float avg=0.0f;
        if(fscanf(f, "%255s %255s %255s %255s %255s %255s %d %d %d %255s %f\n",
                  buf_name, buf_surname, buf_pid, buf_class, buf_email, buf_phone, &bd, &bm, &by, buf_gender, &avg) != 11){
            /* malformed, stop */
            break;
        }
        (*students)[i].name = strDup(buf_name);
        (*students)[i].surname = strDup(buf_surname);
        (*students)[i].personalID = strDup(buf_pid);
        (*students)[i].class = strDup(buf_class);
        (*students)[i].email = strDup(buf_email);
        (*students)[i].phone = strDup(buf_phone);
        (*students)[i].birthDay = bd; (*students)[i].birthMonth = bm; (*students)[i].birthYear = by;
        (*students)[i].gender = strDup(buf_gender);
        (*students)[i].averageGrade = avg;

        int pcnt = 0;
        if(fscanf(f, "%d", &pcnt) != 1) pcnt = 0;
        (*students)[i].parentCount = pcnt;
        for(int p=0;p<pcnt && p<2;p++){
            char bufpid[256];
            fscanf(f, " %255s", bufpid);
            (*students)[i].parentPersonalIDs[p] = strDup(bufpid);
        }
        /* consume rest of line */
        int ch = fgetc(f);
        if(ch != '\n' && ch != EOF){
            while(ch != '\n' && ch != EOF) ch = fgetc(f);
        }
    }

    /* read parents */
    for(int i=0;i<pc;i++){
        char buf_name[256], buf_surname[256], buf_pid[256], buf_email[256], buf_phone[256], buf_gender[256];
        int bd=0,bm=0,by=0;
        int childc = 0;
        if(fscanf(f, "%255s %255s %255s %255s %255s %d %d %d %255s %d",
                  buf_name, buf_surname, buf_pid, buf_email, buf_phone, &bd, &bm, &by, buf_gender, &childc) < 10){
            break;
        }
        (*parents)[i].name = strDup(buf_name);
        (*parents)[i].surname = strDup(buf_surname);
        (*parents)[i].personalID = strDup(buf_pid);
        (*parents)[i].email = strDup(buf_email);
        (*parents)[i].phone = strDup(buf_phone);
        (*parents)[i].birthDay = bd; (*parents)[i].birthMonth = bm; (*parents)[i].birthYear = by;
        (*parents)[i].gender = strDup(buf_gender);
        (*parents)[i].childCount = childc;
        for(int c=0;c<childc && c<MAX_CHILDREN;c++){
            char bufcid[256];
            fscanf(f, " %255s", bufcid);
            (*parents)[i].childPersonalIDs[c] = strDup(bufcid);
        }
        int ch = fgetc(f);
        if(ch != '\n' && ch != EOF){
            while(ch != '\n' && ch != EOF) ch = fgetc(f);
        }
    }

    *studentCount = sc;
    *parentCount = pc;

    fclose(f);
}

void saveDatabase(struct Student *students, struct Parent *parents, int studentCount, int parentCount){
    FILE *f = fopen(DATABASE_FILE, "w");
    if(!f) return;

    fprintf(f, "%d\n", studentCount);
    fprintf(f, "%d\n", parentCount);

    for(int i=0;i<studentCount;i++){
        struct Student *s = &students[i];
        fprintf(f, "%s %s %s %s %s %s %d %d %d %s %.2f\n",
                s->name ? s->name : "-", s->surname ? s->surname : "-", s->personalID ? s->personalID : "-",
                s->class ? s->class : "-", s->email ? s->email : "-", s->phone ? s->phone : "-",
                s->birthDay, s->birthMonth, s->birthYear, s->gender ? s->gender : "-", s->averageGrade);
        fprintf(f, "%d", s->parentCount);
        for(int p=0;p<s->parentCount && p<2;p++){
            fprintf(f, " %s", s->parentPersonalIDs[p] ? s->parentPersonalIDs[p] : "-");
        }
        fprintf(f, "\n");
    }

    for(int i=0;i<parentCount;i++){
        struct Parent *p = &parents[i];
        fprintf(f, "%s %s %s %s %s %d %d %d %s %d",
                p->name ? p->name : "-", p->surname ? p->surname : "-", p->personalID ? p->personalID : "-",
                p->email ? p->email : "-", p->phone ? p->phone : "-", p->birthDay, p->birthMonth, p->birthYear,
                p->gender ? p->gender : "-", p->childCount);
        for(int c=0;c<p->childCount && c<MAX_CHILDREN;c++){
            fprintf(f, " %s", p->childPersonalIDs[c] ? p->childPersonalIDs[c] : "-");
        }
        fprintf(f, "\n");
    }

    fclose(f);
}