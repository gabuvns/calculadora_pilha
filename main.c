#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*Verificação se alocacção está fucionando como deveria*/
int main(){

    char digitado;
    s_pilha* pilha= cria_pilha();
    scanf(" %c", &digitado);
    s_elemento* elemento = cria_elemento(digitado);
    printf("%c", elemento->digitado);
    free(elemento);
    free(pilha);
    return 0;
}