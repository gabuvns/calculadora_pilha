#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"
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
void get(s_pilha* pilha){
    if(pilha_vazia(pilha)){
        printf("A pilha encontra-se vazia!\n");
    }
    else{
        s_elemento* elem_aux = pilha->inicio;
        while(elem_aux->proximo != NULL){
            elem_aux = elem_aux->proximo;
        }
    printf("Elemento número %d no topo da lista: %c\n", pilha->quantidade, elem_aux->caractere);

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
        printf("=====Fim da Pilha========\n\n\n\n");
        free(elem_aux);
    }
}




