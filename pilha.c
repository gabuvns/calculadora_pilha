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
//numerica
n_pilha* cria_pilhanumerica(){
    n_pilha* ptr = (n_pilha*) malloc(sizeof(n_pilha));
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
//No caso de um float
s_numerical* cria_elementonumerico(float input){
    s_numerical* ptr = (s_numerical*) malloc(sizeof(s_numerical));
    ptr->numero = input;
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

void n_pop(n_pilha* pilha){
    if(n_pilha_vazia(pilha)){
        printf("Nao existem elementos para retirar da pilha!\n");
    }

    else if(pilha->quantidade == 1){
        free(pilha->inicio);
        pilha->inicio = NULL;
        pilha->topo = NULL;
        pilha->quantidade--;
    }

    else{
        s_numerical* elem_atual = pilha->inicio;
        s_numerical* elem_ant;

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
//Funcao criada especificamente para o modo de resolucao
void push_num(n_pilha* numerical_pilha, float input){
    if(numerical_pilha->inicio == NULL){
        numerical_pilha->inicio = cria_elementonumerico(input);
    }

    else{
        s_numerical* elem_aux = numerical_pilha->inicio;
        while(elem_aux->proximo != NULL){
            elem_aux = elem_aux->proximo;
           
        }

        elem_aux->proximo = cria_elementonumerico(input);
        numerical_pilha->topo = elem_aux->proximo;
    }
    numerical_pilha->quantidade++;

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

int n_pilha_vazia(n_pilha* pilha){
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

float getnum(n_pilha* pilha){
    if(n_pilha_vazia(pilha)){
        printf("A pilha encontra-se vazia!\n");
    }
    else{
        s_numerical* elem_aux2 = pilha->inicio;
        while(elem_aux2->proximo != NULL){
            elem_aux2 = elem_aux2->proximo;
        }
        return elem_aux2->numero;

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

void limpar_pilha_num(n_pilha* pilha){
    while(pilha->inicio != NULL){
        n_pop(pilha);
    }
    if(n_pilha_vazia(pilha)){
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

/*Função para printar todos os itens da pilha numerica*/
void mostrar_pilha_num(n_pilha* pilha){
    if(n_pilha_vazia(pilha)){
        printf("A pilha está vazia!\n");
    }
    
    else{
        s_numerical* elem_aux = pilha->inicio;
        int i;
        i = pilha->quantidade + 1;
        printf("==========Pilha==========\n");
        while(elem_aux != NULL){ 
            i--;
            printf("%d. %lf\n", i, elem_aux->numero);
            elem_aux = elem_aux->proximo;
        }
        printf("======Fim da Pilha=======\n\n\n");
        free(elem_aux);
    }
}


