#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*Verificação se alocacção está fucionando como deveria*/
int main(){
    s_pilha* pilha = cria_pilha();
    push(pilha, 'a');
    pop(pilha);
    push(pilha, 'b');
    push(pilha, 'c');
    push(pilha, 'd');
    mostrar_pilha(pilha);
    get(pilha);
    limpar_pilha(pilha);

    return 0;
}