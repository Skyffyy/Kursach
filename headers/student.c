#include <stdio.h>
#include <stdlib.h>
#include "student.h"

// Compares two strings for equality without using string.h
int strEqual(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

// Lists all students in a static array
void listStudentsStatic(struct Student students[], int count) {
    if (count == 0) {
        printf("The student list is empty.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("%d. %s %s, born %d, class %d, average grade: %.2f\n",
               i + 1,
               students[i].name,
               students[i].surname,
               students[i].birthYear,
               students[i].classNumber,
               students[i].averageGrade);
    }
}

// Adds a student to a static array if there is space
void addStudentStatic(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Database is full!\n");
        return;
    }

    struct Student *s = &students[*count];

    printf("First name: ");
    scanf("%49s", s->name);
    printf("Last name: ");
    scanf("%49s", s->surname);
    printf("Birth year: ");
    scanf("%d", &s->birthYear);
    printf("Class number: ");
    scanf("%d", &s->classNumber);
    printf("Average grade: ");
    scanf("%f", &s->averageGrade);

    (*count)++;
    printf("✅ Student added.\n");
}

// Deletes a student by name and surname from a static array
void deleteStudentStatic(struct Student students[], int *count) {
    if (*count == 0) {
        printf("Database is empty.\n");
        return;
    }

    char name[MAX_NAME], surname[MAX_NAME];
    printf("Enter first name: ");
    scanf("%49s", name);
    printf("Enter last name: ");
    scanf("%49s", surname);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strEqual(students[i].name, name) && strEqual(students[i].surname, surname)) {
            // Shift students after deleted one to the left
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            printf("❌ Student %s %s deleted.\n", name, surname);
            break;
        }
    }

    if (!found)
        printf("Student %s %s not found.\n", name, surname);
}

// Creates a dynamic array of students with initial capacity
struct Student* createStudentArray(int initialCapacity) {
    struct Student *arr = (struct Student*)malloc(sizeof(struct Student) * initialCapacity);
    if (!arr) {
        printf("Failed to allocate memory.\n");
        return NULL;
    }
    return arr;
}

// Frees the dynamic array
void freeStudentArray(struct Student *students) {
    free(students);
}

// Adds a student to dynamic array, reallocates if capacity exceeded
void addStudentDynamic(struct Student **students, int *count, int *capacity) {
    if (*count >= *capacity) {
        int newCapacity = (*capacity) * 2;
        struct Student *newArr = (struct Student*)realloc(*students, sizeof(struct Student) * newCapacity);
        if (!newArr) {
            printf("Failed to allocate more memory.\n");
            return;
        }
        *students = newArr;
        *capacity = newCapacity;
    }

    struct Student *s = &((*students)[*count]);

    printf("First name: ");
    scanf("%49s", s->name);
    printf("Last name: ");
    scanf("%49s", s->surname);
    printf("Birth year: ");
    scanf("%d", &s->birthYear);
    printf("Class number: ");
    scanf("%d", &s->classNumber);
    printf("Average grade: ");
    scanf("%f", &s->averageGrade);

    (*count)++;
    printf("✅ Student added.\n");
}

// Deletes a student by name and surname from dynamic array
void deleteStudentDynamic(struct Student **students, int *count) {
    if (*count == 0) {
        printf("Database is empty.\n");
        return;
    }

    char name[MAX_NAME], surname[MAX_NAME];
    printf("Enter first name: ");
    scanf("%49s", name);
    printf("Enter last name: ");
    scanf("%49s", surname);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strEqual((*students)[i].name, name) && strEqual((*students)[i].surname, surname)) {
            // Shift students after deleted one to the left
            for (int j = i; j < *count - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }
            (*count)--;
            found = 1;
            printf("❌ Student %s %s deleted.\n", name, surname);
            break;
        }
    }

    if (!found)
        printf("Student %s %s not found.\n", name, surname);
}

// Lists all students in dynamic array
void listStudentsDynamic(struct Student *students, int count) {
    if (count == 0) {
        printf("The student list is empty.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("%d. %s %s, born %d, class %d, average grade: %.2f\n",
               i + 1,
               students[i].name,
               students[i].surname,
               students[i].birthYear,
               students[i].classNumber,
               students[i].averageGrade);
    }
}
