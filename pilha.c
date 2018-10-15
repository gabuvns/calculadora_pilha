#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/*Utilizado para limpar o terminal dependendo do sistema*/
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

/*Definição da função para criar pilha e elemento*/
s_pilha* cria_pilha(){
    s_pilha* ptr = (s_pilha*) malloc(sizeof(s_pilha));
    ptr->quantidade = 0;
    ptr->inicio = NULL; 
    ptr->topo = NULL;
    return ptr;
}

/*Criar o elemento*/
s_elemento* cria_elemento(char input){
    s_elemento* ptr = (s_elemento*) malloc(sizeof(s_elemento));
    ptr->caractere = input;
    ptr->proximo = NULL;
    return ptr;
}

/*Retira elementos da pilha*/
void pop(s_pilha* pilha){
    if(pilha_vazia(pilha)){
        printf("Nao existem elementos para retirar da pilha!\n");
    }

    else if(pilha->quantidade == 1){
        free(pilha->inicio);
        pilha->inicio = NULL;
        pilha->topo = NULL;
        pilha->quantidade--;
    }

    else{
        s_elemento* elem_atual = pilha->inicio;
        s_elemento* elem_ant;

        while(elem_atual->proximo != NULL){

            elem_ant = elem_atual;
            elem_atual = elem_atual->proximo;
        }

        free(elem_atual);
        elem_ant->proximo = NULL;
        pilha->topo = elem_ant;
        pilha->quantidade--;
    }
}

/*Adiciona novos elementos à pilha*/
void push(s_pilha* pilha, char input){
    if(pilha->inicio == NULL){
        pilha->inicio = cria_elemento(input);
    }

    else{
        s_elemento* elem_aux = pilha->inicio;
        while(elem_aux->proximo != NULL){
            elem_aux = elem_aux->proximo;
           
        }

        elem_aux->proximo = cria_elemento(input);
        pilha->topo = elem_aux->proximo;
    }
    pilha->quantidade++;

}

/*Verifica se a pilha encontra-se vazia*/
int pilha_vazia(s_pilha* pilha){
    if(pilha->inicio == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

/*Função que printa somente o último elemento da pilha*/
char get(s_pilha* pilha){
    if(pilha_vazia(pilha)){
        printf("A pilha encontra-se vazia!\n");
    }
    else{
        s_elemento* elem_aux2 = pilha->inicio;
        while(elem_aux2->proximo != NULL){
            elem_aux2 = elem_aux2->proximo;
        }
        return elem_aux2->caractere;

    }
}

void limpar_pilha(s_pilha* pilha){
    while(pilha->inicio != NULL){
        pop(pilha);
    }
    if(pilha_vazia(pilha)){
        free(pilha);
    }
}

/*Função para printar todos os itens da pilha*/
void mostrar_pilha(s_pilha* pilha){
    if(pilha_vazia(pilha)){
        printf("A pilha está vazia!\n");
    }
    
    else{
        s_elemento* elem_aux = pilha->inicio;
        int i;
        i = pilha->quantidade + 1;
        printf("==========Pilha==========\n");
        while(elem_aux != NULL){ 
            i--;
            printf("%d. %c\n", i, elem_aux->caractere);
            elem_aux = elem_aux->proximo;
        }
        printf("======Fim da Pilha=======\n\n\n\n");
        free(elem_aux);
    }
}

/*Funcoes relativas a calculadora*/

/*Verificacao da validade da expressao, 1 = valida, 0 = Invalida.*/
int validade(s_pilha* demarcacao, s_pilha* pilha_aux){
    char entrada;
    int val = 1;
    
    while(scanf(" %c", &entrada) != '#'){
        push(pilha_aux, entrada);

        if(entrada == '#'){
            return val;
        }
         if(entrada == '('){
            push(demarcacao, entrada);  
            if(!pilha_vazia(demarcacao)){
                val = 0;
            }
        }

        else if(entrada == ')'){
            if(pilha_vazia(demarcacao)){
                return 0;
            }
            else{
                if(demarcacao->quantidade == 1){
                    if(demarcacao->inicio->caractere == ('(')){
                        val = 1;
                        pop(demarcacao);
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    pop(demarcacao);
                }
            }
        }
    }
}

/*Define-se as prioridades relativas a pilha na funcao de conversao*/
/*Retorna 1 caso o elemento da pilha tenha maior prioridade e 2 caso contrario*/
int prioridade(s_pilha* anda, char caractere){
    int elem1;
    int elem2;
    char comp = get(anda);
    /*Prioridade elemento 1*/
    if(comp == '('){
        elem1 = 3;
    }
    else if(comp == '-' || comp == '+'){
        elem1 = 1;
    }
    else if(comp == '/' || comp == '*'){
        elem1 = 2;
    }

    /*prioridade elemento 2*/
    if(caractere == '('){
        elem2 = 3;
    }
    else if(caractere == '-' || caractere == '+'){
        elem2 = 1;
    }

    else if(caractere == '/' || caractere == '*'){
        elem2 = 2;
    }

    if(comp == '('){
        return 4;    
    }

    if(elem2 == '('){
        return 3;
    }
    

    else if(elem1 > elem2 || elem1 == elem2){
      
        return 1;
    }
    else if(elem1 < elem2){
       
        return 2;
    }
}


void inftopos(s_pilha* pilha_aux){
    s_elemento* elem_aux;
    s_pilha* anda = cria_pilha();
    elem_aux = pilha_aux->inicio;
    char saida[50];
    int i, j;
    i=0;
    int qtd = 0;
    int priori;
    while(elem_aux->caractere != '#'){
        if(elem_aux->caractere == ')'){
            for(j=0;j<qtd;j++){
                saida[i] = get(anda);
                pop(anda);
                i++;
            }
            pop(anda);
        }
        
        else if(elem_aux->caractere == '*' || elem_aux->caractere == '+' ||
        elem_aux->caractere == '-' || elem_aux->caractere == '/' ||
        elem_aux->caractere == '('){
            if(!pilha_vazia(anda)){
                priori = prioridade(anda, elem_aux->caractere);
                 if(priori == 1){
                    saida[i] = get(anda);
                    pop(anda);
                    push(anda, elem_aux->caractere);                   
                    i++;
                }
                else if(priori == 4){
                    push(anda, elem_aux->caractere);
                    qtd++;
                }
                else if(priori == 3){
                    push(anda, elem_aux->caractere);
                }

                else if(priori == 2){
                    push(anda, elem_aux->caractere);                   
                } 
            }
            else{
                push(anda, elem_aux->caractere);
            }
        }
        
        /*No caso de 'numeros'*/
        else{
            saida[i] = elem_aux->caractere;
            i++; 
        }
        elem_aux = elem_aux->proximo;
    }
    while(!pilha_vazia(anda)){
        saida[i] = get(anda);
        pop(anda);
        i++;
    }

    saida[i] = '\0';
    printf("Expressao pos-fixa = %s\n", saida);
    int ap;
    scanf("%d", &ap);
    
}

/*Modo de resolucao*/
void resmode(){
    CLEAR;
    char con;
    s_pilha* demarcacao = cria_pilha();
    s_pilha* pilha_aux = cria_pilha();
    printf("Digite a seguir sua equacao: ");

    if(!validade(demarcacao, pilha_aux)){
        printf("Expressao invalida.\n");
        limpar_pilha(demarcacao);
        limpar_pilha(pilha_aux);
        do{
            printf("Digite 'r'  para retornar ao menu.\n");
            scanf(" %c", &con);
        }while(con != 'R' && con != 'r');
        
    }
    else{
        printf("Expressao valida!\n");
        limpar_pilha(demarcacao);
        do{
            printf("Digite 'r' para a proxima etapa.\n");
            scanf(" %c", &con);
        }while(con != 'R' && con != 'r');
        inftopos(pilha_aux);
    }
    
    CLEAR;

}

/*Modo de calculadora*/
void calcmode(){

}

/*Funcao para printar o menu*/
void show_menu(){
        printf("Utilize um '#' para indicar o fim de sua expressao!\n");
        printf("Selecione qual dos modos deseja utilizar\n");
        printf("1. Resolucao de Expressao\n");
        printf("2. Calculadora\n");
        printf("3. Como utilizar\n");
        printf("4. Sair\n");
        

}
void tutorial(){
    CLEAR;
    char con;
    printf("1. Selecione um modo de operacao\n");
    printf("2. Sempre que inserir uma equação, utilize um '#' para indicar seu fim\n");
    printf("Como por exemplo na expressao a seguir\n");
    printf("Expressao valida: (A+B)*C/D-F#\n");
    printf("Expressao invaldia: (A+B)*C/D-F\n");
    printf("Caso esqueca de por a '#' apos a expressao, digita-la normalmente.\n");
   
    do{
        printf("Digite 'r' para retornar ao menu.\n");
        scanf(" %c", &con);
    }while(con != 'R' && con != 'r');
    CLEAR;
}

/*Definicoes do menu*/
void menu(){   
    char input = '5';

    while(input != '4'){   
        show_menu();   
        printf("Selecione uma opcao: ");
        scanf(" %c", &input);

        if(input == '1' || input == '2' || input == '3'){
            switch(input){
            case '1': resmode();
                break;
            case '2': calcmode();
                break;
            
            case '3': tutorial();
                break;
            }
        }

        else if(input != '4'){
            CLEAR;
            printf("Por favor, digite uma opcao valida.\n");
        } 
    }
}




