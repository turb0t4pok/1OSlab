#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct employee {
    int id;
    char name[10];
    double hours;
};

int isDuplicateID(int id, int* idArray, int count) {
    for (int i = 0; i < count; i++) {
        if (idArray[i] == id) {
            return 1;
        }
    }
    return 0;
}

int isValidName(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i])) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <binary file> <number of employees>\n", argv[0]);
        return 1;
    }

    const char* binaryFile = argv[1];
    int numEmployees = atoi(argv[2]);

    FILE* file = fopen(binaryFile, "wb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    struct employee emp;
    int* idArray = (int*)malloc(numEmployees * sizeof(int));
    if (!idArray) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    printf("Enter employee data (ID Name Hours):\n");
    for (int i = 0; i < numEmployees; i++) {
        int idValid = 0;
        while (!idValid) {
            printf("Employee #%d (ID Name Hours): ", i + 1);
            scanf("%d", &emp.id);

            if (emp.id <= 0) {
                printf("Error: ID must be a positive number greater than 0. Try again.\n");
                continue;
            }
            if (isDuplicateID(emp.id, idArray, i)) {
                printf("Error: Employee with ID %d already exists. Try again.\n", emp.id);
                continue;
            }

            idArray[i] = emp.id;
            idValid = 1;
        }

        int nameValid = 0;
        while (!nameValid) {
            printf("Enter name (only letters, max 10 chars): ");
            scanf("%9s", emp.name);

            if (strlen(emp.name) > 10) {
                printf("Error: Name must not exceed 10 characters. Try again.\n");
                continue;
            }
            if (!isValidName(emp.name)) {
                printf("Error: Name must contain only letters. Try again.\n");
                continue;
            }

            nameValid = 1;
        }

        printf("Enter worked hours: ");
        scanf("%lf", &emp.hours);

        fwrite(&emp, sizeof(struct employee), 1, file);
    }

    free(idArray);
    fclose(file);
    printf("Employee data saved to %s\n", binaryFile);
    return 0;
}
