#include <stdio.h>
#include "student.h"
#include "sort.h"
#include "database.h"

void showHelp() {
    printf("\n=== Commands ===\n");
    printf("help     — show available commands\n");
    printf("list     — show all students\n");
    printf("sort     — sort students (by alphabete, by grade, by yearborn)\n");
    printf("add      — add new student\n");
    printf("delete   — delete student by name and surname\n");
    printf("dynamic  — ask a custom question and view sorted lists\n");
    printf("\nExamples:\n");
    printf("  ./main list\n");
    printf("  ./main add\n");
    printf("  ./main sort\n");
    printf("  ./main dynamic\n");
}

int main(int argc, char *argv[]) {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    loadDatabase(students, &count);

    if (argc < 2) {
        printf("Usage: ./main command\n");
        printf("Use ./main help to see available commands.\n");
        return 0;
    }

    if (strEqual(argv[1], "help")) {
        showHelp();
    }
    else if (strEqual(argv[1], "list")) {
        listStudents(students, count);
    }
    else if (strEqual(argv[1], "add")) {
        addStudent(students, &count);
        saveDatabase(students, count);
    }
    else if (strEqual(argv[1], "delete")) {
        deleteStudent(students, &count);
        saveDatabase(students, count);
    }
    else if (strEqual(argv[1], "sort")) {
        char sortType[20];
        printf("\nAvailable sorts:\n");
        printf("- by alphabete\n");
        printf("- by grade\n");
        printf("- by yearborn\n");
        printf("Enter sort type: ");
        scanf("%19s", sortType);

        if (strEqual(sortType, "alphabete")) {
            sortByName(students, count);
            listStudents(students, count);
        } else if (strEqual(sortType, "grade")) {
            sortByGrade(students, count);
            listStudents(students, count);
        } else if (strEqual(sortType, "yearborn")) {
            sortByYearBorn(students, count);
            listStudents(students, count);
        } else {
            printf("Unknown sort type.\n");
        }
    }
    else if (strEqual(argv[1], "dynamic")) {
        char question[256];
        printf("Would you like to ask a custom question? (yes/no): ");
        char answer[10];
        scanf("%9s", answer);
        if (strEqual(answer, "yes")) {
            printf("Enter your question: ");
            getchar(); // clear \n after scanf
            fgets(question, sizeof(question), stdin);
            printf("\nYour question: %s\n", question);

            printf("List of students (original order):\n");
            listStudents(students, count);

            printf("\nSorted by age (yearborn):\n");
            sortByYearBorn(students, count);
            listStudents(students, count);

            printf("\nSorted alphabetically (name+surname):\n");
            sortByName(students, count);
            listStudents(students, count);
        } else {
            printf("No custom question provided.\n");
        }
    }
    else {
        printf("Unknown command. Use ./main help to see available commands.\n");
    }
    return 0;
}