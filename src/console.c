#include "console.h"
#include <stdio.h>
#include <stdlib.h>

void consoleMessage(const char *message) {
    system("clear");
    printf("%s\nPressione Enter para continuar...", message);
    getchar();
}
