#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*Utilizado para limpar o terminal dependendo do sistema*/
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif
void menu();
int main(){
    CLEAR;
    printf("==Bem vindo a calculadora de expressoes==\n");
    menu();
    printf("==Programa encerrado==\n");
    return 0;
}
