#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "sort.h"
#include "database.h"

void showHelp() {
    printf("\n=== Commands ===\n");
    printf("help     — show available commands\n");
    printf("list     — show all students (static array)\n");
    printf("add      — add new student (static array)\n");
    printf("delete   — delete student (static array)\n");
    printf("sort     — sort students (static array)\n");
    printf("dynamic  — work with dynamic array\n");
    printf("\nExamples:\n");
    printf("  ./main list\n");
    printf("  ./main add\n");
    printf("  ./main sort\n");
    printf("  ./main dynamic\n");
}

int main(int argc, char *argv[]) {
    struct Student students[MAX_STUDENTS];
    struct Parent parents[MAX_PARENTS];
    int studentCount = 0;
    int parentCount = 0;

    loadDatabase(students, parents, &studentCount, &parentCount);

    if(argc < 2) {
        printf("Usage: ./main command\n");
        printf("Use ./main help to see available commands.\n");
        return 0;
    }

    if(strEqual(argv[1], "help")) {
        showHelp();
    }
    else if(strEqual(argv[1], "list")) {
        listStudentsStatic(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "add")) {
        addStudentStatic(students, parents, &studentCount, &parentCount);
        saveDatabase(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "delete")) {
        deleteStudentStatic(students, &studentCount);
        saveDatabase(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "sort")) {
        char sortType[20];
        printf("Enter sort type (name / birth / grade): ");
        scanf("%19s", sortType);

        if(strEqual(sortType, "name")) sortByName(students, studentCount);
        else if(strEqual(sortType, "birth")) sortByBirthYear(students, studentCount);
        else if(strEqual(sortType, "grade")) sortByGrade(students, studentCount);
        else { printf("Unknown sort type.\n"); return 0; }

        listStudentsStatic(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "dynamic")) {
        int dynCount = 0;
        int dynParentCount = 0;
        int dynCap = 2;
        struct Student *dynStudents = createStudentArray(dynCap);
        struct Parent *dynParents = (struct Parent*)malloc(sizeof(struct Parent)*MAX_PARENTS);
        if(!dynStudents || !dynParents) return 1;

        char cmd[20];
        printf("Dynamic array mode. Commands: add, delete, list, sort, exit\n");

        while(1) {
            printf("\nEnter command: ");
            scanf("%19s", cmd);

            if(strEqual(cmd, "add")) {
                addStudentDynamic(&dynStudents, &dynParents, &dynCount, &dynParentCount, &dynCap);
            }
            else if(strEqual(cmd, "delete")) {
                deleteStudentDynamic(&dynStudents, &dynCount);
            }
            else if(strEqual(cmd, "list")) {
                listStudentsDynamic(dynStudents, dynParents, dynCount, dynParentCount);
            }
            else if(strEqual(cmd, "sort")) {
                char sortType[20];
                printf("Enter sort type (name / birth / grade): ");
                scanf("%19s", sortType);

                if(strEqual(sortType, "name")) sortByName(dynStudents, dynCount);
                else if(strEqual(sortType, "birth")) sortByBirthYear(dynStudents, dynCount);
                else if(strEqual(sortType, "grade")) sortByGrade(dynStudents, dynCount);
                else { printf("Unknown sort type.\n"); continue; }

                listStudentsDynamic(dynStudents, dynParents, dynCount, dynParentCount);
            }
            else if(strEqual(cmd, "exit")) {
                break;
            }
            else {
                printf("Unknown command. Available: add, delete, list, sort, exit\n");
            }
        }

        free(dynStudents);
        free(dynParents);
    }
    else {
        printf("Unknown command. Use ./main help to see available commands.\n");
    }

    return 0;
}
