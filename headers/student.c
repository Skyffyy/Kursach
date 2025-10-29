#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "utils.h"
#include "parent.h"
#include "sort.h"

struct Student* createStudentArray(int initialCapacity){
    struct Student *arr = malloc(sizeof(struct Student) * initialCapacity);
    if(!arr){ printf("Memory allocation failed\n"); return NULL; }
    return arr;
}

void freeStudentArray(struct Student *students){
    free(students);
}

void listStudentsStatic(struct Student students[], int studentCount, struct Parent parents[], int parentCount){
    if(studentCount == 0){
        printf("No students\n");
        return;
    }
    for(int i=0;i<studentCount;i++){
        struct Student *s = &students[i];
        printf("\n%d) %s %s\n", i+1, s->name, s->surname);
        printf("   ID: %s\n", s->personalID);
        printf("   Class: %s\n", s->class);
        printf("   Email: %s\n", s->email);
        printf("   Phone: %s\n", s->phone);
        printf("   Birth: %02d.%02d.%d\n", s->birthDay, s->birthMonth, s->birthYear);
        printf("   Gender: %s\n", s->gender);
        printf("   Avg grade: %.2f\n", s->averageGrade);

        if(s->parentCount <= 0){
            printf("   Parents: none\n");
        } else {
            printf("   Parents:\n");
            for(int p=0;p<s->parentCount;p++){
                const char *pid = s->parentPersonalIDs[p];
                int found = 0;
                for(int k=0;k<parentCount;k++){
                    if(strEqual(parents[k].personalID, pid)){
                        /* show full parent info */
                        printParentInfo(&parents[k]);
                        found = 1;
                        break;
                    }
                }
                if(!found) printf("     - Parent ID %s (not in DB)\n", pid);
            }
        }
    }
}

void addStudentStatic(struct Student students[], int *studentCount, struct Parent parents[], int *parentCount){
    if(*studentCount >= MAX_STUDENTS){ printf("Student database full\n"); return; }
    struct Student *s = &students[*studentCount];
    printf("=== Adding New Student ===\n");
    printf("Name: "); scanf("%49s", s->name);
    printf("Surname: "); scanf("%49s", s->surname);
    printf("Personal ID: "); scanf("%19s", s->personalID);
    printf("Class: "); scanf("%9s", s->class);
    printf("Email: "); scanf("%99s", s->email);
    printf("Phone: "); scanf("%19s", s->phone);
    printf("Birth Day (1-31): "); scanf("%d", &s->birthDay);
    printf("Birth Month (1-12): "); scanf("%d", &s->birthMonth);
    printf("Birth Year: "); scanf("%d", &s->birthYear);
    printf("Gender: "); scanf("%9s", s->gender);
    printf("Average Grade: "); scanf("%f", &s->averageGrade);
    printf("Number of parents (0-2): "); scanf("%d", &s->parentCount);
    if(s->parentCount < 0) s->parentCount = 0;
    if(s->parentCount > 2) s->parentCount = 2;
    for(int i=0;i<s->parentCount;i++){
        char pid[MAX_ID_LENGTH];
        printf("Enter parent %d personal ID: ", i+1);
        scanf("%19s", pid);
        int found = 0;
        for(int j=0;j<*parentCount;j++){
            if(strEqual(parents[j].personalID, pid)){
                strCopy(s->parentPersonalIDs[i], parents[j].personalID);
                /* link parent->child if not already */
                int already = 0;
                for(int c=0;c<parents[j].childCount;c++) if(strEqual(parents[j].childPersonalIDs[c], s->personalID)) { already = 1; break; }
                if(!already) linkParentToStudent(&parents[j], s->personalID);
                found = 1;
                break;
            }
        }
        if(!found){
            if(*parentCount >= MAX_PARENTS){
                printf("Parent DB full, skipping add for this parent.\n");
                s->parentCount = i;
                break;
            }
            struct Parent *p = &parents[*parentCount];
            printf("Parent not found, entering parent details now.\n");
            printf("Parent name: "); scanf("%49s", p->name);
            printf("Parent surname: "); scanf("%49s", p->surname);
            strCopy(p->personalID, pid);
            printf("Parent email: "); scanf("%99s", p->email);
            printf("Parent phone: "); scanf("%19s", p->phone);
            printf("Parent birth day: "); scanf("%d", &p->birthDay);
            printf("Parent birth month: "); scanf("%d", &p->birthMonth);
            printf("Parent birth year: "); scanf("%d", &p->birthYear);
            printf("Parent gender: "); scanf("%9s", p->gender);
            p->childCount = 0;
            strCopy(s->parentPersonalIDs[i], p->personalID);
            linkParentToStudent(p, s->personalID);
            (*parentCount)++;
        }
    }
    (*studentCount)++;
    printf("Student added.\n");
}

void deleteStudentStatic(struct Student students[], int *studentCount){
    if(*studentCount == 0){ printf("No students to delete\n"); return; }
    char id[MAX_ID_LENGTH];
    printf("Enter student ID to delete: "); scanf("%19s", id);
    int idx = -1;
    for(int i=0;i<*studentCount;i++){
        if(strEqual(students[i].personalID, id)){ idx = i; break; }
    }
    if(idx == -1){ printf("Student not found\n"); return; }
    for(int j=idx;j<(*studentCount)-1;j++) students[j] = students[j+1];
    (*studentCount)--;
    printf("Student deleted\n");
}

void filterStudentStatic(struct Student students[], int studentCount, struct Parent parents[], int parentCount){
    if(studentCount == 0){ printf("No students in database\n"); return; }
    char classes[MAX_STUDENTS][MAX_CLASS_LENGTH];
    int classCount = 0;
    for(int i=0;i<studentCount;i++){
        if(students[i].class[0] == '\0') continue;
        int found = 0;
        for(int j=0;j<classCount;j++){
            if(strEqual(classes[j], students[i].class)){ found = 1; break; }
        }
        if(!found){
            strCopy(classes[classCount++], students[i].class);
            if(classCount >= MAX_STUDENTS) break;
        }
    }
    if(classCount == 0){ printf("No classes recorded\n"); return; }
    printf("Available classes:\n");
    for(int i=0;i<classCount;i++) printf("  %d) %s\n", i+1, classes[i]);
    int choice = 0;
    printf("Choose class number (0 to cancel): ");
    if(scanf("%d", &choice) != 1){ printf("Invalid input\n"); return; }
    if(choice <= 0 || choice > classCount){ printf("Cancelled or invalid choice\n"); return; }
    char *selClass = classes[choice-1];
    struct Student filtered[MAX_STUDENTS];
    int fcount = 0;
    for(int i=0;i<studentCount;i++){
        if(strEqual(students[i].class, selClass)){
            filtered[fcount++] = students[i];
            if(fcount >= MAX_STUDENTS) break;
        }
    }
    if(fcount == 0){ printf("No students in class %s\n", selClass); return; }
    char sortType[20];
    printf("Enter sort type for class (name / surname / grade / year / none): ");
    scanf("%19s", sortType);
    if(strEqual(sortType,"name")) sortByName(filtered, fcount);
    else if(strEqual(sortType,"surname")) sortBySurname(filtered, fcount);
    else if(strEqual(sortType,"grade")) sortByAverageGrade(filtered, fcount);
    else if(strEqual(sortType,"year")) sortByBirthYear(filtered, fcount);
    listStudentsStatic(filtered, fcount, parents, parentCount);
}

void addStudentDynamic(struct Student **students, struct Parent **parents, int *studentCount, int *parentCount, int *capacity){
    if(*studentCount >= *capacity){
        int newCap = (*capacity) * 2;
        struct Student *ns = realloc(*students, sizeof(struct Student) * newCap);
        struct Parent *np = realloc(*parents, sizeof(struct Parent) * newCap);
        if(!ns || !np){ printf("Memory allocation failed\n"); return; }
        *students = ns; *parents = np; *capacity = newCap;
    }
    addStudentStatic(*students, studentCount, *parents, parentCount);
}

void deleteStudentDynamic(struct Student **students, int *studentCount){
    deleteStudentStatic(*students, studentCount);
}

void listStudentsDynamic(struct Student *students, int studentCount, struct Parent *parents, int parentCount){
    listStudentsStatic(students, studentCount, parents, parentCount);
}