#include <stdio.h>
#include <stdlib.h>

struct employee {
    int id;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <binary file> <report file> <hourly rate>\n", argv[0]);
        return 1;
    }

    const char* binaryFile = argv[1];
    const char* reportFile = argv[2];
    double hourlyRate = atof(argv[3]);

    FILE* binFile = fopen(binaryFile, "rb");
    if (!binFile) {
        perror("Error opening binary file");
        return 1;
    }

    FILE* txtFile = fopen(reportFile, "w");
    if (!txtFile) {
        perror("Error opening report file");
        fclose(binFile);
        return 1;
    }

    fprintf(txtFile, "ID  Name      Hours  Salary\n");
    printf("ID  Name      Hours  Salary\n");

    struct employee emp;
    while (fread(&emp, sizeof(struct employee), 1, binFile) == 1) {
        double salary = emp.hours * hourlyRate;

        fprintf(txtFile, "%-3d %-10s %-6.2f %.2f\n", emp.id, emp.name, emp.hours, salary);

        printf("%-3d %-10s %-6.2f %.2f\n", emp.id, emp.name, emp.hours, salary);
    }

    fclose(binFile);
    fclose(txtFile);

    printf("\nReport saved to %s\n", reportFile);
    return 0;
}
