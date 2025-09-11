#ifndef TASKS_H
#define TASKS_H

typedef struct lligada {
    int prioridade;
    int num;
    char title[51];
    char str[101];
    struct lligada *prox;
} *Tarefas;

void newTask(Tarefas *tarefas, int prioridade, char *title, char *descr, int *count); 
void handleNewTask(Tarefas *tarefas, int *count);
void showTasks(Tarefas *tarefas);
void handleCommand(char *command, Tarefas *tarefas, int *count);
void readCommand(Tarefas *tarefas, int *count); 

#endif
