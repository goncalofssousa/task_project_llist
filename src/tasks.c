#include "tasks.h"
#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Filters filters = NULL; 

void lerString(char *dest, int max) {
    if (fgets(dest, max, stdin) != NULL) {
        dest[strcspn(dest, "\n")] = '\0';

        if (strlen(dest) == max - 1 && dest[max - 2] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
        }
    }
}

void printTask(Tarefas tmp){
    printf("=== Tarefa %d ===\n", tmp->num); 
    printf("Titulo: %s\n", (tmp)->title);
    if((tmp)->str[0] == '\0'){
        printf("Sem descrição\n"); 
    } else {
            printf("Descrição: %s\n", (tmp)->str);
    }
    printf("Prioridade: %s\n", (tmp)->prioridadeStr);
    char state[10] = ""; 
    if(tmp->taskState == 0) strcpy(state, "Pendente"); 
    else strcpy(state,"Concluida");
    printf("Estado: %s", state);   
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
    novaTarefa->prioridade = prioridade; 
    novaTarefa->taskState = 0; 
   
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
    int count = 1; 
    if(*tarefas == NULL){
        consoleMessage("Lista de tarefas vazia"); 
    }
    else{
        Tarefas tmp = *tarefas;
        printf("=== Lista de Tarefas ===\n"); 
        printf("\n"); 
        while(tmp != NULL){
            tmp->num = count; 
            printTask(tmp); 
            tmp = tmp->prox;
            printf("\n"); 
            count ++; 
        }
        getchar(); 
    }
}

void removeTask(Tarefas *tarefas){
    if(*tarefas == NULL) {
        consoleMessage("Nao ha tarefas a remover");
        return;
    }
    int num = -1;
    int times = 0; 
    int flag = 0; 
    do{
        if(times > 0){
            consoleMessage("Numero invalido"); 
        }
        system("clear");
        printf("=== Remover Tarefa ===\n"); 
        printf("Digite o numero da tarefa a remover(-1 para sair): "); 
        scanf("%d", &num); 
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        Tarefas *tmp = tarefas;
        if(num != -1){
            while(*tmp != NULL){
                if((*tmp)->num == num){
                    Tarefas tmp2 = *tmp; 
                    *tmp = (*tmp)->prox;
                    free(tmp2); 
                    flag = 1; 
                    break; 
                }
                tmp = &((*tmp)->prox); 
            }
        }
        else{
            consoleMessage("Operacao cancelada"); 
            return; 
        }
        times++; 
    } 
    while(num == -1 || !flag);  
    consoleMessage("Tarefa removida com sucesso"); 
}

void markAsDone(Tarefas *tarefas){
    if(*tarefas == NULL) {
            consoleMessage("Nao ha tarefas para concluir");
            return;
    }
    int num = -1;
    int times = 0; 
    int flag = 0; 
    do{
        if(times > 0){
            consoleMessage("Numero invalido"); 
        }
        system("clear");
        printf("=== Marcar como concluida ===\n"); 
        printf("Digite o numero da tarefa a marcar com concluida (-1 para sair): "); 
        scanf("%d", &num); 
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        Tarefas tmp = *tarefas;
        if(num != -1){
            while(tmp != NULL){
                if(tmp->num == num){
                    tmp->taskState = 1; 
                    flag =1; 
                    break; 
                }
                tmp = tmp->prox; 
            }
        }
        else{
            consoleMessage("Operacao cancelada"); 
            return; 
        }
        times++; 
    } 
    while(num == -1 || !flag);  
    consoleMessage("Tarefa marcada como concluida"); 
}


void handleFilterStatus(Tarefas *tarefas){
    int statusFilter = -1; 
    int times = 0; 
    do{
        if(times > 0){
            consoleMessage("Status errado, escolha 0 ou 1"); 
            system("clear"); 
        }
        printf("Digite o Status desejado (0- pendente, 1-concluida): ");
        scanf("%d", &statusFilter);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        times++;  
    }
    while(statusFilter != 0 && statusFilter != 1);
    Tarefas tmp = *tarefas; 
    system("clear");
    printf("=== Lista de Tarefas ===\n"); 
    printf("\n");
    while(tmp != NULL){
        if(tmp->taskState == statusFilter){
            printTask(tmp); 
            printf("\n");
        }
        tmp = tmp->prox;
    }
        getchar(); 
    return; 
}

void handleFilterPriority(Tarefas *tarefas){
    char prioridadeStr[10] = ""; 
    int prioridade = 0; 
    int valida = 0; 
    int times = 0; 
    do{
        if(times > 0){
            consoleMessage("Prioridade errado, escolha (Alta, Media ou Baixa)"); 
            system("clear"); 
        }
        printf("Digite a Prioridade desejada (Alta, Media ou Baixa): ");
        fgets(prioridadeStr, sizeof(prioridadeStr), stdin); 
        prioridadeStr[strcspn(prioridadeStr, "\n")] = '\0'; 
        if(strcasecmp(prioridadeStr, "Alta") == 0) {
            valida = 1; 
            prioridade = 3; 
        }
        else if(strcasecmp(prioridadeStr, "Media") == 0){
            valida = 1; 
            prioridade = 2; 
        }
        else if (strcasecmp(prioridadeStr, "Baixa") == 0){
            valida = 1; 
            prioridade = 1; 
        }
        else{}
        times++;  
    }
    while(!valida); 
    Tarefas tmp = *tarefas; 
    system("clear");
    printf("=== Lista de Tarefas ===\n"); 
    printf("\n");
    while(tmp != NULL){
        if(tmp->prioridade == prioridade){
            printTask(tmp);
            printf("\n"); 
        }
        tmp = tmp->prox; 
    }
    getchar(); 
    return;
}

void filterTasks(Tarefas *tarefas){
    if(*tarefas == NULL){
        consoleMessage("Nao ha tarefas"); 
        return; 

    }
    char filterStr[20] = ""; 
    int flagApply = 0; 
    int times2 = 0; 
    do{
        if(times2 > 0){
            consoleMessage("Categoria invalida, escolha Prioridade, Status ou Ambos");
        }
        system("clear"); 
        printf("Qual categoria deseja usar para filtrar(Prioridade, Status ou Ambos): "); 
        fgets(filterStr, sizeof(filterStr), stdin); 
        filterStr[strcspn(filterStr, "\n")] = '\0'; 
        if(strcasecmp(filterStr, "Prioridade") != 0 && strcasecmp(filterStr, "Status") != 0 && strcasecmp(filterStr, "Ambos") != 0){
            times2++; 
        }
        else{ 
            if(strcasecmp(filterStr, "Status") == 0){
                handleFilterStatus(tarefas); 
                flagApply = 1; 
            }
            else if (strcasecmp(filterStr, "Prioridade") == 0){
                handleFilterPriority(tarefas);
                flagApply = 1; 
            }
            else{
                char prioridadeStr[10] = ""; 
                int prioridade = 0; 
                int valida = 0; 
                int statusFilter = -1; 
                int times = 0; 
                do{
                    if(times > 0){
                        consoleMessage("Prioridade ou status errado"); 
                        system("clear"); 
                    }
                    printf("Digite a Prioridade desejada (Alta, Media ou Baixa): ");
                    fgets(prioridadeStr, sizeof(prioridadeStr), stdin); 
                    prioridadeStr[strcspn(prioridadeStr, "\n")] = '\0'; 
                    if(strcasecmp(prioridadeStr, "Alta") == 0) {
                        valida = 1; 
                        prioridade = 3; 
                    }
                    else if(strcasecmp(prioridadeStr, "Media") == 0){
                        valida = 1; 
                        prioridade = 2; 
                    }
                    else if (strcasecmp(prioridadeStr, "Baixa") == 0){
                        valida = 1; 
                        prioridade = 1; 
                    }
                    else{} 
                    times++;  
                    printf("\nDigite o Status desejado (0- pendente, 1-concluida): ");
                    scanf("%d", &statusFilter);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    times++;  
                }
                while(!valida && statusFilter != 0 && statusFilter != 1); 
                system("clear");
                printf("=== Lista de Tarefas ===\n"); 
                printf("\n");
                Tarefas tmp = *tarefas; 
                while(tmp != NULL){
                    if(tmp->taskState == statusFilter && tmp->prioridade ==  prioridade){
                        printTask(tmp); 
                        printf("\n"); 
                    }
                    tmp = tmp->prox;
                }
                flagApply = 1; 
                getchar(); 
            }
        }
    }
    while(!flagApply); 
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
            removeTask(tarefas); 
            break;
        case '4':
            markAsDone(tarefas); 
            break;
        case '5':
            filterTasks(tarefas);
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