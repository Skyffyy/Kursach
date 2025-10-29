#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "utils.h"
#include "parent.h"
#include "sort.h"

/* Helper to init one student slot */
static void initStudentSlot(struct Student *s) {
    if(!s) return;
    s->name = s->surname = s->personalID = s->email = s->phone = s->class = s->gender = NULL;
    s->averageGrade = 0.0f;
    s->birthDay = s->birthMonth = s->birthYear = 0;
    s->parentCount = 0;
    s->parentPersonalIDs[0] = s->parentPersonalIDs[1] = NULL;
}

struct Student* createStudentArray(int initialCapacity){
    if(initialCapacity <= 0) initialCapacity = 8;
    struct Student *arr = malloc(sizeof(struct Student) * initialCapacity);
    if(!arr){ printf("Memory allocation failed\n"); return NULL; }
    for(int i=0;i<initialCapacity;i++) initStudentSlot(&arr[i]);
    return arr;
}

void freeStudentRecord(struct Student *s){
    if(!s) return;
    if(s->name) free(s->name);
    if(s->surname) free(s->surname);
    if(s->personalID) free(s->personalID);
    if(s->email) free(s->email);
    if(s->phone) free(s->phone);
    if(s->class) free(s->class);
    if(s->gender) free(s->gender);
    for(int i=0;i<s->parentCount && i<2;i++){
        if(s->parentPersonalIDs[i]) free(s->parentPersonalIDs[i]);
        s->parentPersonalIDs[i] = NULL;
    }
    s->parentCount = 0;
}

void freeStudentArray(struct Student *students, int count){
    if(!students) return;
    for(int i=0;i<count;i++) freeStudentRecord(&students[i]);
    free(students);
}

/* Local helper: read token into heap-allocated exact sized string */
static char* readTokenAlloc(const char *prompt, int bufSize){
    char buf[512];
    if(prompt) printf("%s", prompt);
    if(scanf("%511s", buf) != 1) return NULL;
    return strDup(buf);
}

/* Print students (uses printParentInfo to show parent full info) */
void listStudents(struct Student *students, int studentCount, struct Parent *parents, int parentCount){
    if(studentCount == 0){
        printf("No students\n");
        return;
    }
    for(int i=0;i<studentCount;i++){
        struct Student *s = &students[i];
        printf("\n%d) %s %s\n", i+1, s->name ? s->name : "(no name)", s->surname ? s->surname : "");
        printf("   ID: %s\n", s->personalID ? s->personalID : "(no id)");
        printf("   Class: %s\n", s->class ? s->class : "(no class)");
        printf("   Email: %s\n", s->email ? s->email : "(no email)");
        printf("   Phone: %s\n", s->phone ? s->phone : "(no phone)");
        printf("   Birth: %02d.%02d.%d\n", s->birthDay, s->birthMonth, s->birthYear);
        printf("   Gender: %s\n", s->gender ? s->gender : "(no gender)");
        printf("   Avg grade: %.2f\n", s->averageGrade);

        if(s->parentCount <= 0){
            printf("   Parents: none\n");
        } else {
            printf("   Parents:\n");
            for(int p=0;p<s->parentCount && p<2;p++){
                const char *pid = s->parentPersonalIDs[p];
                int found = 0;
                for(int k=0;k<parentCount;k++){
                    if(parents[k].personalID && pid && strEqual(parents[k].personalID, pid)){
                        printParentInfo(&parents[k]);
                        found = 1;
                        break;
                    }
                }
                if(!found) printf("     - Parent ID %s (not in DB)\n", pid ? pid : "(null)");
            }
        }
    }
}

/* Add student (may expand students and parents arrays) */
void addStudent(struct Student **students, int *studentCount, int *studentCapacity,
                struct Parent **parents, int *parentCount, int *parentCapacity){
    if(!students || !studentCount || !studentCapacity || !parents || !parentCount || !parentCapacity) return;

    if(*studentCount >= *studentCapacity){
        int newCap = (*studentCapacity) * 2;
        if(newCap < 1) newCap = 8;
        struct Student *ns = realloc(*students, sizeof(struct Student) * newCap);
        if(!ns){ printf("Memory allocation failed\n"); return; }
        /* init new slots */
        for(int i=*studentCapacity;i<newCap;i++) initStudentSlot(&ns[i]);
        *students = ns;
        *studentCapacity = newCap;
    }

    struct Student *s = &(*students)[*studentCount];
    printf("=== Adding New Student ===\n");
    s->name = readTokenAlloc("Name: ", MAX_NAME_LENGTH);
    s->surname = readTokenAlloc("Surname: ", MAX_SURNAME_LENGTH);
    s->personalID = readTokenAlloc("Personal ID: ", MAX_ID_LENGTH);
    s->class = readTokenAlloc("Class: ", MAX_CLASS_LENGTH);
    s->email = readTokenAlloc("Email: ", MAX_EMAIL_LENGTH);
    s->phone = readTokenAlloc("Phone: ", MAX_PHONE_LENGTH);

    printf("Birth Day (1-31): "); scanf("%d", &s->birthDay);
    printf("Birth Month (1-12): "); scanf("%d", &s->birthMonth);
    printf("Birth Year: "); scanf("%d", &s->birthYear);

    s->gender = readTokenAlloc("Gender: ", MAX_GENDER_LENGTH);

    printf("Average Grade: "); scanf("%f", &s->averageGrade);

    printf("Number of parents (0-2): "); scanf("%d", &s->parentCount);
    if(s->parentCount < 0) s->parentCount = 0;
    if(s->parentCount > 2) s->parentCount = 2;

    for(int i=0;i<s->parentCount;i++){
        char buf[MAX_ID_LENGTH + 10];
        printf("Enter parent %d personal ID: ", i+1);
        if(scanf("%19s", buf) != 1) { s->parentCount = i; break; }

        /* Search existing parent */
        int found = 0;
        for(int j=0;j<*parentCount;j++){
            if((*parents)[j].personalID && strEqual((*parents)[j].personalID, buf)){
                s->parentPersonalIDs[i] = strDup((*parents)[j].personalID);
                /* link child to parent if not already linked */
                int already = 0;
                for(int c=0;c<(*parents)[j].childCount;c++){
                    if((*parents)[j].childPersonalIDs[c] && s->personalID && strEqual((*parents)[j].childPersonalIDs[c], s->personalID)){ already = 1; break; }
                }
                if(!already) linkParentToStudent(&(*parents)[j], s->personalID);
                found = 1;
                break;
            }
        }
        if(found) continue;

        /* Parent not found: create new parent record (grow parents if needed) */
        if(*parentCount >= *parentCapacity){
            int newPcap = (*parentCapacity) * 2;
            if(newPcap < 1) newPcap = 8;
            struct Parent *np = realloc(*parents, sizeof(struct Parent) * newPcap);
            if(!np){ printf("Memory allocation failed for parents\n"); s->parentCount = i; break; }
            /* init new parent slots */
            for(int k=*parentCapacity;k<newPcap;k++){
                np[k].name = np[k].surname = np[k].personalID = np[k].email = np[k].phone = np[k].gender = NULL;
                np[k].childCount = 0;
                for(int c=0;c<MAX_CHILDREN;c++) np[k].childPersonalIDs[c] = NULL;
                np[k].birthDay = np[k].birthMonth = np[k].birthYear = 0;
            }
            *parents = np;
            *parentCapacity = newPcap;
        }

        struct Parent *p = &(*parents)[*parentCount];
        printf("Parent not found, entering parent details now.\n");
        p->name = readTokenAlloc("Parent name: ", MAX_NAME_LENGTH);
        p->surname = readTokenAlloc("Parent surname: ", MAX_SURNAME_LENGTH);
        p->personalID = strDup(buf);
        p->email = readTokenAlloc("Parent email: ", MAX_EMAIL_LENGTH);
        p->phone = readTokenAlloc("Parent phone: ", MAX_PHONE_LENGTH);
        printf("Parent birth day: "); scanf("%d", &p->birthDay);
        printf("Parent birth month: "); scanf("%d", &p->birthMonth);
        printf("Parent birth year: "); scanf("%d", &p->birthYear);
        p->gender = readTokenAlloc("Parent gender: ", MAX_GENDER_LENGTH);
        p->childCount = 0;
        s->parentPersonalIDs[i] = strDup(p->personalID);
        linkParentToStudent(p, s->personalID);
        (*parentCount)++;
    }

    (*studentCount)++;
    printf("Student added.\n");
}

/* Delete student by personalID */
void deleteStudent(struct Student *students, int *studentCount, struct Parent *parents, int parentCount){
    if(!students || !studentCount) return;
    if(*studentCount == 0){ printf("No students to delete\n"); return; }
    char id[MAX_ID_LENGTH + 8];
    printf("Enter student ID to delete: "); if(scanf("%19s", id) != 1) return;
    int idx = -1;
    for(int i=0;i<*studentCount;i++){
        if(students[i].personalID && strEqual(students[i].personalID, id)){ idx = i; break; }
    }
    if(idx == -1){ printf("Student not found\n"); return; }

    /* remove references from parents */
    for(int p=0;p<parentCount;p++){
        for(int c=0;c<parents[p].childCount;c++){
            if(parents[p].childPersonalIDs[c] && students[idx].personalID && strEqual(parents[p].childPersonalIDs[c], students[idx].personalID)){
                free(parents[p].childPersonalIDs[c]);
                /* shift left */
                for(int k=c;k<parents[p].childCount-1;k++) parents[p].childPersonalIDs[k] = parents[p].childPersonalIDs[k+1];
                parents[p].childPersonalIDs[parents[p].childCount-1] = NULL;
                parents[p].childCount--;
                break;
            }
        }
    }

    /* free student record resources */
    freeStudentRecord(&students[idx]);

    /* shift array left */
    for(int j=idx;j<(*studentCount)-1;j++) students[j] = students[j+1];

    (*studentCount)--;
    printf("Student deleted\n");
}

/* Filter by classes, build temporary shallow-copy array, optionally sort and print */
void filterStudents(struct Student *students, int studentCount, struct Parent *parents, int parentCount){
    if(studentCount == 0){ printf("No students in database\n"); return; }

    /* collect unique class strings (pointing to existing strings) */
    char **classes = malloc(sizeof(char*) * studentCount);
    int classCount = 0;
    for(int i=0;i<studentCount;i++){
        if(!students[i].class) continue;
        int found = 0;
        for(int j=0;j<classCount;j++){
            if(strEqual(classes[j], students[i].class)){ found = 1; break; }
        }
        if(!found) classes[classCount++] = students[i].class;
    }
    if(classCount == 0){ printf("No classes recorded\n"); free(classes); return; }

    printf("Available classes:\n");
    for(int i=0;i<classCount;i++) printf("  %d) %s\n", i+1, classes[i]);

    int choice = 0;
    printf("Choose class number (0 to cancel): ");
    if(scanf("%d", &choice) != 1){ printf("Invalid input\n"); free(classes); return; }
    if(choice <= 0 || choice > classCount){ printf("Cancelled or invalid choice\n"); free(classes); return; }
    const char *selClass = classes[choice-1];

    /* collect matching students (shallow copy) */
    struct Student *filtered = malloc(sizeof(struct Student) * studentCount);
    int fcount = 0;
    for(int i=0;i<studentCount;i++){
        if(students[i].class && strEqual(students[i].class, selClass)){
            filtered[fcount++] = students[i];
        }
    }
    if(fcount == 0){ printf("No students in class %s\n", selClass); free(filtered); free(classes); return; }

    char sortType[32];
    printf("Enter sort type for class (name / surname / grade / year / none): ");
    scanf("%31s", sortType);
    if(strEqual(sortType,"name")) sortByName(filtered, fcount);
    else if(strEqual(sortType,"surname")) sortBySurname(filtered, fcount);
    else if(strEqual(sortType,"grade")) sortByAverageGrade(filtered, fcount);
    else if(strEqual(sortType,"year")) sortByBirthYear(filtered, fcount);
    /* print filtered list (filtered contains shallow pointers to original strings) */
    listStudents(filtered, fcount, parents, parentCount);

    free(filtered);
    free(classes);
}