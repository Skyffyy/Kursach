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
    printf("filter   — filter for classes\n");
    printf("sort     — sort students\n");
    printf("parents  — manage parents\n");
    printf("\nExamples:\n");
    printf("  ./main list\n");
    printf("  ./main add\n");
    printf("  ./main sort\n");
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: ./main command\nUse ./main help for commands.\n");
        return 0;
    }

    /* dynamic arrays and capacities */
    int studentCapacity = 8, parentCapacity = 8;
    struct Student *students = createStudentArray(studentCapacity);
    struct Parent *parents = createParentArray(parentCapacity);
    int studentCount = 0, parentCount = 0;

    loadDatabase(&students, &parents, &studentCount, &parentCount, &studentCapacity, &parentCapacity);

    if(strEqual(argv[1], "help")) {
        showHelp();
    }
    else if(strEqual(argv[1], "list")) {
        listStudents(students, studentCount, parents, parentCount);
    }
    else if(strEqual(argv[1], "add")) {
        addStudent(&students, &studentCount, &studentCapacity, &parents, &parentCount, &parentCapacity);
        saveDatabase(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "delete")) {
        deleteStudent(students, &studentCount, parents, parentCount);
        saveDatabase(students, parents, studentCount, parentCount);
    }
    else if(strEqual(argv[1], "filter")) {
        filterStudents(students, studentCount, parents, parentCount);
    }
    else if(strEqual(argv[1], "sort")) {
        char sortType[32];
        printf("Enter sort type (name / surname /grade / year): ");
        scanf("%31s", sortType);
        if(strEqual(sortType,"name")) sortByName(students, studentCount);
        else if(strEqual(sortType,"surname")) sortBySurname(students, studentCount);
        else if(strEqual(sortType,"grade")) sortByAverageGrade(students, studentCount);
        else if(strEqual(sortType,"year")) sortByBirthYear(students, studentCount);
        else { printf("Unknown sort type.\n"); }
        listStudents(students, studentCount, parents, parentCount);
    }
    else if(strEqual(argv[1], "parents")) {
        char cmd[32];
        while(1){
            printf("\nParent mode: list, add, delete, show, save, exit\nCommand: ");
            if(scanf("%31s", cmd) != 1) break;
            if(strEqual(cmd,"list")) listParents(parents, parentCount);
            else if(strEqual(cmd,"add")) { addParent(&parents, &parentCount, &parentCapacity); saveDatabase(students, parents, studentCount, parentCount); }
            else if(strEqual(cmd,"delete")) { deleteParent(parents, &parentCount); saveDatabase(students, parents, studentCount, parentCount); }
            else if(strEqual(cmd,"show")){
                char pid[128];
                printf("Enter parent ID: "); scanf("%127s", pid);
                showParentAndChildren(parents, parentCount, students, studentCount, pid);
            }
            else if(strEqual(cmd,"save")) saveDatabase(students, parents, studentCount, parentCount);
            else if(strEqual(cmd,"exit")) break;
            else printf("Unknown command.\n");
        }
    }
    else {
        printf("Unknown command. Use ./main help\n");
    }

    /* free resources */
    freeStudentArray(students, studentCount);
    freeParentArray(parents, parentCount);
    return 0;
}