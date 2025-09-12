#ifndef TASKS_H
#define TASKS_H
#include<stdlib.h>


typedef enum{
    UNDONE = 0, 
    DONE = 1,
} State; 

typedef enum{
    Prioridade = 0, 
    Status = 1,
    Both = 2
} Filter; 

typedef struct lligada {
    int num;
    char title[51];
    char str[101];
    char prioridadeStr[10];
    State taskState; 
    int prioridade; 
    struct lligada *prox;
} *Tarefas;

typedef struct lligadaF {
    Filter filter; 
    char prioridade[10];
    State status; 
    struct lligadaF *prox;  
} *Filters;



void newTask(Tarefas *tarefas, char *prioridadeStr, int prioridade, char *title, char *descr); 
void handleNewTask(Tarefas *tarefas);
void showTasks(Tarefas *tarefas);
void handleCommand(char *command, Tarefas *tarefas);
void readCommand(Tarefas *tarefas); 

#endif
