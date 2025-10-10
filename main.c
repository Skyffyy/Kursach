#include <stdio.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define DATABASE_FILE "database.txt"

struct Student {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    int birthYear;
    int classNumber;
    float averageGrade;
};

void loadDatabase(struct Student students[], int *count);
void saveDatabase(struct Student students[], int count);
void listStudents(struct Student students[], int count);
void addStudent(struct Student students[], int *count);
void deleteStudent(struct Student students[], int *count);
void sortByName(struct Student students[], int count);
void sortByBirthYear(struct Student students[], int count);
void sortByGrade(struct Student students[], int count);
int strEqual(const char *a, const char *b);
void showHelp();

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
            printf("✅ Sorted by alphabet.\n");
        } 
        else if (strEqual(sortType, "grade")) {
            sortByGrade(students, count);
            printf("✅ Sorted by grade (descending).\n");
        } 
        else if (strEqual(sortType, "yearborn")) {
            sortByBirthYear(students, count);
            printf("✅ Sorted by birth year (ascending).\n");
        } 
        else {
            printf("❌ Unknown sort type.\n");
            return 0;
        }

        saveDatabase(students, count);
        listStudents(students, count);
    }
    else {
        printf("Unknown command. Type ./main help\n");
    }

    return 0;
}

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

void listStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("The student list is empty.\n");
        return;
    }

    printf("\n=== Student List ===\n");
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

void addStudent(struct Student students[], int *count) {
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
    printf("✅ Student added and saved.\n");
}

void deleteStudent(struct Student students[], int *count) {
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

int strEqual(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

void sortByName(struct Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int k = 0;
            while (students[j].name[k] == students[j + 1].name[k] &&
                   students[j].name[k] != '\0' &&
                   students[j + 1].name[k] != '\0') {
                k++;
            }
            if (students[j].name[k] > students[j + 1].name[k]) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void sortByBirthYear(struct Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].birthYear > students[j + 1].birthYear) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void sortByGrade(struct Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].averageGrade > students[j + 1].averageGrade) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}


void showHelp() {
    printf("\n=== Commands ===\n");
    printf("help     — show available commands\n");
    printf("list     — show all students\n");
    printf("sort     — sort students (by alphabete, by grade, by yearborn)\n");
    printf("add      — add new student\n");
    printf("delete   — delete student by name and surname\n");
    printf("\nExamples:\n");
    printf("  ./main list\n");
    printf("  ./main add\n");
    printf("  ./main sort\n");
}
