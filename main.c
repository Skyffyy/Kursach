#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "parent.h"
#include "database.h"
#include "sort.h"
#include "utils.h"

void showHelp() {
    printf("\n=== Commands ===\n");
    printf("help     — show available commands\n");
    printf("list     — show all students\n");
    printf("add      — add new student\n");
    printf("delete   — delete student\n");
    printf("sort     — sort students\n");
    printf("dynamic  — work with dynamic array\n");
    printf("parents  — manage parents\n");
    printf("\nExamples:\n");
    printf("  ./main list\n");
    printf("  ./main add\n");
    printf("  ./main sort\n");
    printf("  ./main dynamic\n");
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: ./main command\nUse ./main help for commands.\n");
        return 0;
    }

    // Static arrays
    struct Student students[MAX_STUDENTS];
    struct Parent parents[MAX_PARENTS];
    int studentCount = 0;
    int parentCount = 0;

    // Load database
    loadDatabase(students, parents, &studentCount, &parentCount);

    if(strEqual(argv[1], "help")){
        showHelp();
    }
    else if(strEqual(argv[1], "list")){
        listStudentsStatic(students, studentCount, parents, parentCount);
    }
    else if(strEqual(argv[1], "add")){
        addStudentStatic(students, &studentCount, parents, &parentCount);
        saveDatabase(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "delete")){
        deleteStudentStatic(students, &studentCount);
        saveDatabase(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "sort")){
        char sortType[20];
        printf("Enter sort type (name / surname / grade): ");
        scanf("%19s", sortType);
        if(strEqual(sortType,"name")) sortByName(students, studentCount);
        else if(strEqual(sortType,"surname")) sortBySurname(students, studentCount);
        else if(strEqual(sortType,"grade")) sortByAverageGrade(students, studentCount);
        else { printf("Unknown sort type.\n"); return 0; }
        listStudentsStatic(students, studentCount, parents, parentCount);
    }
    else if(strEqual(argv[1], "dynamic")){
        int dynCap = 2;
        int dynStudentCount = 0, dynParentCount = 0;
        struct Student *dynStudents = createStudentArray(dynCap);
        struct Parent *dynParents = createParentArray(dynCap);
        if(!dynStudents || !dynParents) return 1;

        char cmd[20];
        printf("Dynamic mode. Commands: add, delete, list, sort, exit\n");
        while(1){
            printf("\nEnter command: ");
            scanf("%19s", cmd);

            if(strEqual(cmd,"add")){
                addStudentDynamic(&dynStudents, &dynParents, &dynStudentCount, &dynParentCount, &dynCap);
            }
            else if(strEqual(cmd,"delete")){
                deleteStudentDynamic(&dynStudents, &dynStudentCount);
            }
            else if(strEqual(cmd,"list")){
                listStudentsDynamic(dynStudents, dynStudentCount, dynParents, dynParentCount);
            }
            else if(strEqual(cmd,"sort")){
                char sortType[20];
                printf("Enter sort type (name / surname / grade): ");
                scanf("%19s", sortType);
                if(strEqual(sortType,"name")) sortByName(dynStudents, dynStudentCount);
                else if(strEqual(sortType,"surname")) sortBySurname(dynStudents, dynStudentCount);
                else if(strEqual(sortType,"grade")) sortByAverageGrade(dynStudents, dynStudentCount);
                else { printf("Unknown sort type.\n"); continue; }
                listStudentsDynamic(dynStudents, dynStudentCount, dynParents, dynParentCount);
            }
            else if(strEqual(cmd,"exit")){
                saveDatabase(dynStudents, dynParents, dynStudentCount, dynParentCount);
                break;
            }
            else printf("Unknown command.\n");
        }

        freeStudentArray(dynStudents);
        freeParentArray(dynParents);
    }
    else if(strEqual(argv[1], "parents")){
        int cap = MAX_PARENTS;
        char cmd[20];
        while(1){
            printf("\nParent mode: list, add, delete, exit\nCommand: ");
            scanf("%19s", cmd);
            if(strEqual(cmd,"list")) listParentsStatic(parents, parentCount);
            else if(strEqual(cmd,"add")){
                addParentStatic(parents, &parentCount);
                saveDatabase(students, parents, studentCount, parentCount);
            }
            else if(strEqual(cmd,"delete")){
                deleteParentStatic(parents, &parentCount);
                saveDatabase(students, parents, studentCount, parentCount);
            }
            else if(strEqual(cmd,"exit")) break;
            else printf("Unknown command.\n");
        }
    }
    else{
        printf("Unknown command. Use ./main help\n");
    }

    return 0;
}
