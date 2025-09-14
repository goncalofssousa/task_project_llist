#ifndef TASKS_H
#define TASKS_H
#include<stdlib.h>


typedef enum{
    UNDONE = 1, 
    DONE = 2,
} State; 


typedef struct lligada {
    int id;
    char title[51];
    char str[101];
    char prioridadeStr[10];
    State taskState; 
    int prioridade; 
    struct lligada *prox;
} *Tarefas;



void newTask(Tarefas *tarefas, char *prioridadeStr, int prioridade, char *title, char *descr, int state); 
void handleNewTask(Tarefas *tarefas);
void showTasks(Tarefas *tarefas);
void handleCommand(char *command, Tarefas *tarefas);
void readCommand(Tarefas *tarefas); 

#endif
