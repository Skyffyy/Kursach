#include <stdio.h>
#include "database.h"

void loadDatabase(struct Student students[], int *count) {
    FILE *f = fopen(DATABASE_FILE, "r");
    if (f == NULL) {
        printf("File '%s' not found. A new one will be created.\n", DATABASE_FILE);
        *count = 0;
        return;
    }

    *count = 0;
    while (*count < MAX_STUDENTS &&
           fscanf(f, "%49s %49s %d %d %f",
                  students[*count].name,
                  students[*count].surname,
                  &students[*count].birthYear,
                  &students[*count].classNumber,
                  &students[*count].averageGrade) == 5) {
        (*count)++;
    }

    fclose(f);
}

void saveDatabase(struct Student students[], int count) {
    FILE *f = fopen(DATABASE_FILE, "w");
    if (f == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %d %d %.2f\n",
                students[i].name,
                students[i].surname,
                students[i].birthYear,
                students[i].classNumber,
                students[i].averageGrade);
    }

    fclose(f);
}
