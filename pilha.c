#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"
/*Definição da função para criar pilha e elemento*/
s_pilha* cria_pilha(){
    s_pilha* ptr = (s_pilha*) malloc(sizeof(s_pilha));
    ptr->quantidade = 0;
    ptr->inicio = NULL; 
    return ptr;
}

s_elemento* cria_elemento(char digitado){
    s_elemento* ptr = (s_elemento*) malloc(sizeof(s_elemento));
    ptr->digitado = digitado;
    return ptr;
}






