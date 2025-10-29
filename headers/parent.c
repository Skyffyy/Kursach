#include <stdio.h>
#include <stdlib.h>
#include "parent.h"
#include "student.h"
#include "utils.h"

static void initParentSlot(struct Parent *p){
    if(!p) return;
    p->name = p->surname = p->personalID = p->email = p->phone = p->gender = NULL;
    p->childCount = 0;
    for(int i=0;i<MAX_CHILDREN;i++) p->childPersonalIDs[i] = NULL;
    p->birthDay = p->birthMonth = p->birthYear = 0;
}

struct Parent* createParentArray(int initialCapacity){
    if(initialCapacity <= 0) initialCapacity = 8;
    struct Parent *arr = malloc(sizeof(struct Parent) * initialCapacity);
    if(!arr){ printf("Memory allocation failed\n"); return NULL; }
    for(int i=0;i<initialCapacity;i++) initParentSlot(&arr[i]);
    return arr;
}

void freeParentRecord(struct Parent *p){
    if(!p) return;
    if(p->name) free(p->name);
    if(p->surname) free(p->surname);
    if(p->personalID) free(p->personalID);
    if(p->email) free(p->email);
    if(p->phone) free(p->phone);
    if(p->gender) free(p->gender);
    for(int i=0;i<p->childCount;i++){
        if(p->childPersonalIDs[i]) free(p->childPersonalIDs[i]);
        p->childPersonalIDs[i] = NULL;
    }
    p->childCount = 0;
}

void freeParentArray(struct Parent *parents, int count){
    if(!parents) return;
    for(int i=0;i<count;i++) freeParentRecord(&parents[i]);
    free(parents);
}

void printParentInfo(struct Parent *parent){
    if(!parent) return;
    printf("     Parent: %s %s\n", parent->name ? parent->name : "(no name)", parent->surname ? parent->surname : "");
    printf("       ID: %s\n", parent->personalID ? parent->personalID : "(no id)");
    printf("       Email: %s\n", parent->email ? parent->email : "(no email)");
    printf("       Phone: %s\n", parent->phone ? parent->phone : "(no phone)");
    printf("       Birth: %02d.%02d.%d\n", parent->birthDay, parent->birthMonth, parent->birthYear);
    printf("       Gender: %s\n", parent->gender ? parent->gender : "(no gender)");
    if(parent->childCount > 0){
        printf("       Children IDs:");
        for(int i=0;i<parent->childCount;i++) printf(" %s", parent->childPersonalIDs[i] ? parent->childPersonalIDs[i] : "(null)");
        printf("\n");
    } else {
        printf("       Children: none\n");
    }
}

void linkParentToStudent(struct Parent *parent, const char *studentID){
    if(!parent || !studentID) return;
    if(parent->childCount >= MAX_CHILDREN) return;
    parent->childPersonalIDs[parent->childCount++] = strDup(studentID);
}

struct Parent* findParentByID(struct Parent *parents, int parentCount, const char *id){
    if(!id) return NULL;
    for(int i=0;i<parentCount;i++){
        if(parents[i].personalID && strEqual(parents[i].personalID, id)) return &parents[i];
    }
    return NULL;
}

void showParentAndChildren(struct Parent *parents, int parentCount,
                           struct Student *students, int studentCount, const char *parentID){
    struct Parent *p = findParentByID(parents, parentCount, parentID);
    if(!p){ printf("Parent ID %s not found.\n", parentID ? parentID : "(null)"); return; }

    printf("Parent: %s %s, ID: %s\nEmail: %s\nPhone: %s\nBirth: %02d.%02d.%d\nGender: %s\n",
           p->name ? p->name : "(no)", p->surname ? p->surname : "(no)", p->personalID ? p->personalID : "(no)",
           p->email ? p->email : "(no)", p->phone ? p->phone : "(no)", p->birthDay, p->birthMonth, p->birthYear, p->gender ? p->gender : "(no)");
    printf("Children:\n");
    for(int i=0;i<p->childCount;i++){
        for(int j=0;j<studentCount;j++){
            if(students[j].personalID && p->childPersonalIDs[i] && strEqual(students[j].personalID, p->childPersonalIDs[i])){
                printf("  - %s %s, ID: %s, Grade: %.2f\n",
                       students[j].name ? students[j].name : "(no)", students[j].surname ? students[j].surname : "(no)",
                       students[j].personalID ? students[j].personalID : "(no)", students[j].averageGrade);
            }
        }
    }
}

/* list parents */
void listParents(struct Parent *parents, int parentCount){
    if(parentCount == 0){ printf("No parents\n"); return; }
    for(int i=0;i<parentCount;i++){
        struct Parent *p = &parents[i];
        printf("\n%d) %s %s\n", i+1, p->name ? p->name : "(no)", p->surname ? p->surname : "");
        printf("   ID: %s\n", p->personalID ? p->personalID : "(no)");
        printf("   Email: %s\n", p->email ? p->email : "(no)");
        printf("   Phone: %s\n", p->phone ? p->phone : "(no)");
        printf("   Birth: %02d.%02d.%d\n", p->birthDay, p->birthMonth, p->birthYear);
        printf("   Gender: %s\n", p->gender ? p->gender : "(no)");
        if(p->childCount > 0){
            printf("   Children:");
            for(int c=0;c<p->childCount;c++) printf(" %s", p->childPersonalIDs[c] ? p->childPersonalIDs[c] : "(null)");
            printf("\n");
        } else {
            printf("   Children: none\n");
        }
    }
}

/* add parent (may grow array) */
void addParent(struct Parent **parents, int *parentCount, int *parentCapacity){
    if(!parents || !parentCount || !parentCapacity) return;
    if(*parentCount >= *parentCapacity){
        int newCap = (*parentCapacity) * 2;
        if(newCap < 1) newCap = 8;
        struct Parent *np = realloc(*parents, sizeof(struct Parent) * newCap);
        if(!np){ printf("Memory allocation failed\n"); return; }
        for(int i=*parentCapacity;i<newCap;i++) initParentSlot(&np[i]);
        *parents = np;
        *parentCapacity = newCap;
    }

    struct Parent *p = &(*parents)[*parentCount];
    char buf[512];
    printf("=== Adding New Parent ===\n");
    printf("Name: "); scanf("%511s", buf); p->name = strDup(buf);
    printf("Surname: "); scanf("%511s", buf); p->surname = strDup(buf);
    printf("Personal ID: "); scanf("%511s", buf); p->personalID = strDup(buf);
    printf("Email: "); scanf("%511s", buf); p->email = strDup(buf);
    printf("Phone: "); scanf("%511s", buf); p->phone = strDup(buf);
    printf("Birth Day (1-31): "); scanf("%d", &p->birthDay);
    printf("Birth Month (1-12): "); scanf("%d", &p->birthMonth);
    printf("Birth Year: "); scanf("%d", &p->birthYear);
    printf("Gender: "); scanf("%511s", buf); p->gender = strDup(buf);

    p->childCount = 0;
    int ccount = 0;
    printf("Number of children to link (0-%d): ", MAX_CHILDREN);
    if(scanf("%d", &ccount) != 1) ccount = 0;
    if(ccount < 0) ccount = 0;
    if(ccount > MAX_CHILDREN) ccount = MAX_CHILDREN;
    for(int i=0;i<ccount;i++){
        printf("Enter child %d personal ID: ", i+1);
        if(scanf("%511s", buf) != 1) break;
        p->childPersonalIDs[p->childCount++] = strDup(buf);
    }
    (*parentCount)++;
    printf("Parent added.\n");
}

/* delete parent by ID */
void deleteParent(struct Parent *parents, int *parentCount){
    if(!parents || !parentCount) return;
    if(*parentCount == 0){ printf("No parents to delete\n"); return; }
    char id[256];
    printf("Enter parent ID to delete: "); if(scanf("%255s", id) != 1) return;
    int idx = -1;
    for(int i=0;i<*parentCount;i++){
        if(parents[i].personalID && strEqual(parents[i].personalID, id)){ idx = i; break; }
    }
    if(idx == -1){ printf("Parent not found\n"); return; }
    freeParentRecord(&parents[idx]);
    for(int j=idx;j<(*parentCount)-1;j++) parents[j] = parents[j+1];
    (*parentCount)--;
    printf("Parent deleted\n");
}