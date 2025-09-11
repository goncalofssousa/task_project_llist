#include "tasks.h"
#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void handleNewTask(Tarefas *tarefas, int *count) {
    char str[101] = ""; 
    char title[51] = ""; 
    int prioridade = 0; 
    int times = 0; 
    int c; 

    do {
        if (times > 0) {
            consoleMessage("Tarefa invalida, tenta de novo");
        } 

        system("clear"); 
        printf("=== Adicionar Tarefas ===\n"); 

        printf("Titulo da tarefa (max: 50 chars): ");  
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = '\0'; 

        printf("\nDescrição da tarefa (opcional, maxima 100 chars): ");  
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0'; 


        printf("\nDefina a prioridade (1- baixa, 2-media, 3-alta): ");  
        scanf("%d", &prioridade);

        printf("\nClica Enter para concluir");
        while ((c = getchar()) != '\n');
        getchar();

        times++; 
    }
    while (*title == '\0' || prioridade < 1 || prioridade > 3); 

    newTask(tarefas, prioridade, title, str, count); 
    consoleMessage("Tarefa adicionada com sucesso"); 
}

void newTask(Tarefas *tarefas, int prioridade, char *title, char *descr, int *count){
    Tarefas novaTarefa = malloc(sizeof(struct lligada));
    if(novaTarefa == NULL){
        consoleMessage("Erro de alloc"); 
        return; 
    }
    novaTarefa->prioridade =  prioridade; 
    strcpy(novaTarefa->title, title); 
    strcpy(novaTarefa->str, descr); 
    novaTarefa->num = (*count)++; 
    if(*tarefas == NULL || prioridade > (*tarefas)->prioridade){
        novaTarefa->prox = *tarefas; 
        *tarefas = novaTarefa;
        return;  
    }
    Tarefas ptr = *tarefas; 
    while(ptr->prox != NULL && ptr->prox->prioridade > prioridade){
        ptr = ptr->prox; 
    } 
    novaTarefa->prox = ptr->prox; 
    ptr->prox = novaTarefa; 
}

void showTasks(Tarefas *tarefas){
    Tarefas tmp = *tarefas;
    printf("=== Lista de Tarefas ===\n"); 
    printf("\n"); 
    while(tmp != NULL){
        printf("=== Tarefa %d ===\n", tmp->num); 
        printf("Titulo: %s\n", (tmp)->title);
        if((tmp)->str[0] == '\0'){
            printf("Sem descrição\n"); 
        } else {
            printf("Descrição: %s\n", (tmp)->str);
        }
        printf("Prioridade: %d\n", (tmp)->prioridade);
        tmp = tmp->prox;
        printf("\n"); 
    }
    getchar(); 
}

void handleCommand(char *command, Tarefas *tarefas, int *count){
    switch (command[0])
    {
        case '1':
            handleNewTask(tarefas, count); 
            break;
        case '2':
            system("clear"); 
            showTasks(tarefas); 
            break;
        case '3':
            //remover tarefa
            break;
        case '4':
            //marcar como concluida
            break;
        case '5':
            //filtrar tarefas
            break;
        case '6':
            //guadar em file
            break;
        case '7':
            //load from file
            break;
        case '8':  
            break; 
        default:
            command[strcspn(command, "\n")] = '\0';
            consoleMessage("Comando inválido"); 
            break;
        
    }
}
 


void readCommand(Tarefas *tarefas, int *count){
    char command[100] = "0";
    while (command[0] != '8') {
        system("clear"); 
        printf("=== Lista de Tarefas ===\n"); 
        printf("1. Adicionar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Remover tarefa\n");
        printf("4. Marcar tarefa como concluída\n");
        printf("5. Filtrar tarefas\n");
        printf("6. Guardar lista em ficheiro\n");
        printf("7. Carregar lista de ficheiro\n");
        printf("8. Sair\n");
        printf("Escolhe uma opção: "); 

        if (fgets(command, sizeof(command), stdin) == NULL) {
            continue; 
        }
        command[strcspn(command, "\n")] = '\0';

        int len = strlen(command); 
        if (len != 1) {
            consoleMessage("Comando inválido"); 
            command[0] = '0'; 
        } else {
            handleCommand(command, tarefas, count);  
        }
    }
}