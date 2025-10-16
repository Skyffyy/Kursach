#include <stdio.h>
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
    // Статический массив студентов
    struct Student students[MAX_STUDENTS];
    int count = 0;
    loadDatabase(students, &count);

    if(argc < 2) {
        printf("Usage: ./main command\n");
        printf("Use ./main help to see available commands.\n");
        return 0;
    }

    if(strEqual(argv[1], "help")) {
        showHelp();
    }
    else if(strEqual(argv[1], "list")) {
        listStudentsStatic(students, count);
    }
    else if(strEqual(argv[1], "add")) {
        addStudentStatic(students, &count);
        saveDatabase(students, count);
    }
    else if(strEqual(argv[1], "delete")) {
        deleteStudentStatic(students, &count);
        saveDatabase(students, count);
    }
    else if(strEqual(argv[1], "sort")) {
        char sortType[20];
        printf("Enter sort type (name / grade / yearborn): ");
        scanf("%19s", sortType);

        if(strEqual(sortType, "name")) sortByName(students, count);
        else if(strEqual(sortType, "grade")) sortByGrade(students, count);
        else if(strEqual(sortType, "yearborn")) sortByBirthYear(students, count);
        else { printf("Unknown sort type.\n"); return 0; }

        listStudentsStatic(students, count);
    }
    else if(strEqual(argv[1], "dynamic")) {
        // Динамический массив студентов
        int dynCount = 0;
        int dynCap = 2;
        struct Student *dynStudents = createStudentArray(dynCap);
        if(!dynStudents) return 1;

        char cmd[20];
        printf("Dynamic array mode. Commands: add, delete, list, sort, exit\n");
        while(1) {
            printf("\nEnter command: ");
            scanf("%19s", cmd);

            if(strEqual(cmd, "add")) {
                addStudentDynamic(&dynStudents, &dynCount, &dynCap);
            }
            else if(strEqual(cmd, "delete")) {
                deleteStudentDynamic(&dynStudents, &dynCount);
            }
            else if(strEqual(cmd, "list")) {
                listStudentsDynamic(dynStudents, dynCount);
            }
            else if(strEqual(cmd, "sort")) {
                char sortType[20];
                printf("Enter sort type (name / grade / yearborn): ");
                scanf("%19s", sortType);

                if(strEqual(sortType, "name")) sortByName(dynStudents, dynCount);
                else if(strEqual(sortType, "grade")) sortByGrade(dynStudents, dynCount);
                else if(strEqual(sortType, "yearborn")) sortByBirthYear(dynStudents, dynCount);
                else { printf("Unknown sort type.\n"); continue; }

                listStudentsDynamic(dynStudents, dynCount);
            }
            else if(strEqual(cmd, "exit")) {
                break;
            }
            else {
                printf("Unknown command. Available: add, delete, list, sort, exit\n");
            }
        }

        freeStudentArray(dynStudents);
    }
    else {
        printf("Unknown command. Use ./main help to see available commands.\n");
    }

    return 0;
}
