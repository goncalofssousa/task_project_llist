#include "console.h"
#include <stdio.h>
#include <stdlib.h>

void consoleMessage(const char *message) {
    system("clear");
    printf("%s\nPressione Enter para continuar...", message);
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

void consoleMessage1(const char *message) {
    system("clear");
    printf("%s", message);
    int c;
    while ((c = getchar()) != '\n');
}
