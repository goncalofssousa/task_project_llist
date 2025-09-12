#include "tasks.h"
#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void lerString(char *dest, int max) {
    if (fgets(dest, max, stdin) != NULL) {
        dest[strcspn(dest, "\n")] = '\0';

        if (strlen(dest) == max - 1 && dest[max - 2] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // limpa stdin
        }
    }
}


void handleNewTask(Tarefas *tarefas) {
    char str[101] = ""; 
    char title[51] = ""; 
    char prioridadeStr[10] = ""; 
    int prioridade =0 ; 
    int flagError = 0; 
    int times = 0; 

    do {
        flagError = 0; 
        if (times > 0) {
            consoleMessage("Tarefa invalida, tenta de novo");
        } 

        system("clear"); 
        printf("=== Adicionar Tarefas (ESC+ENTER para cancelar) ===\n"); 

        printf("Titulo da tarefa (max: 50 chars): ");  
        lerString(title, sizeof(title)); 
        if (title[0] == 27) {  
            consoleMessage("Operação cancelada");
            return; 
        }

        printf("\nDescrição da tarefa (opcional, max: 100 chars): ");  
        lerString(str, sizeof(str)); 
        if (str[0] == 27) {  
            consoleMessage("Operação cancelada");
            return; 
        }

        printf("\nDefina a prioridade (Baixa, Media, Alta): ");  
        lerString(prioridadeStr, sizeof(prioridadeStr));    
        if(prioridadeStr[0] == 27){  
            consoleMessage("Operação cancelada");
            return; 
        }

        if(strcasecmp(prioridadeStr, "Alta") == 0) {
            strcpy(prioridadeStr, "Alta"); 
            prioridade = 3; 
        }
        else if(strcasecmp(prioridadeStr, "Media") == 0) {
            strcpy(prioridadeStr, "Media"); 
            prioridade = 2;
        }
        else if(strcasecmp(prioridadeStr, "Baixa") == 0) {
            strcpy(prioridadeStr, "Baixa"); 
            prioridade = 1; 
        }
        else flagError = 1; 

        printf("\nClica Enter para concluir");
        getchar();

        times++; 
    }
    while (*title == '\0' || flagError);
    newTask(tarefas, prioridadeStr, prioridade, title, str); 
    consoleMessage("Tarefa adicionada com sucesso"); 
}

void newTask(Tarefas *tarefas, char *prioridadeStr, int prioridade,char *title, char *descr){
 
    Tarefas novaTarefa = malloc(sizeof(struct lligada));
    if(novaTarefa == NULL){
        consoleMessage("Erro de alloc"); 
        return; 
    } 
    strcpy(novaTarefa->prioridadeStr, prioridadeStr); 
    strcpy(novaTarefa->title, title); 
    strcpy(novaTarefa->str, descr); 
    novaTarefa->num = count++; 
    novaTarefa->prioridade = prioridade; 
   
    if(*tarefas == NULL || prioridade > (*tarefas)->prioridade){
        novaTarefa->prox = *tarefas; 
        *tarefas = novaTarefa;
        return;  
    }
    Tarefas ptr = *tarefas; 
    while(ptr->prox != NULL && ptr->prox->prioridade >= prioridade){
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
        printf("Prioridade: %s\n", (tmp)->prioridadeStr);
        tmp = tmp->prox;
        printf("\n"); 
    }
    getchar(); 
}

void handleCommand(char *command, Tarefas *tarefas){
    switch (command[0])
    {
        case '1':
            handleNewTask(tarefas); 
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
 


void readCommand(Tarefas *tarefas){
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
            handleCommand(command, tarefas);  
        }
    }
}