#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    char binFile[50], txtFile[50];
    int numRecords;
    double rate;

    printf("Enter binary file name: ");
    scanf("%s", binFile);

    printf("Enter number of records: ");
    scanf("%d", &numRecords);

    printf("Enter text report file name: ");
    scanf("%s", txtFile);

    printf("Enter hourly rate: ");
    scanf("%lf", &rate);

    char creatorCmd[100], reporterCmd[100];
    sprintf(creatorCmd, "creator.exe %s %d", binFile, numRecords);
    sprintf(reporterCmd, "reporter.exe %s %s %.2lf", binFile, txtFile, rate);

    STARTUPINFO si1 = { sizeof(si1) }, si2 = { sizeof(si2) };
    PROCESS_INFORMATION pi1, pi2;

    if (!CreateProcess(NULL, creatorCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        printf("Failed to start Creator\n");
        return 1;
    }
    WaitForSingleObject(pi1.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);

    if (!CreateProcess(NULL, reporterCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        printf("Failed to start Reporter\n");
        return 1;
    }
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    printf("All processes completed successfully!\n");
    return 0;
}
