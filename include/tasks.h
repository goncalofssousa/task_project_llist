#ifndef TASKS_H
#define TASKS_H

typedef struct lligada {
    int num;
    char title[51];
    char str[101];
    char prioridadeStr[10];
    int prioridade; 
    struct lligada *prox;
} *Tarefas;
int count = 1; 

void newTask(Tarefas *tarefas, char *prioridadeStr, int prioridade, char *title, char *descr); 
void handleNewTask(Tarefas *tarefas);
void showTasks(Tarefas *tarefas);
void handleCommand(char *command, Tarefas *tarefas);
void readCommand(Tarefas *tarefas); 

#endif
