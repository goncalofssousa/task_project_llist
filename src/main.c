#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "console.h"

int main() {
    Tarefas tarefas = NULL;
    int count = 0;
    readCommand(&tarefas, &count);
    return 0;
}
