#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*Utilizado para limpar o terminal dependendo do sistema*/
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

/*Verificacao da validade da expressao, 1 = valida, 0 = Invalida.*/
int validade(s_pilha* demarcacao){
    char entrada;
    int val = 1;
    
    while(scanf(" %c", &entrada) != '#'){
        if(entrada == '#'){
            return val;
        }
        else if(entrada == '('){
            push(demarcacao, entrada);
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

/*Modo de resolucao*/
void resmode(){
    CLEAR;
    char con;
    s_pilha* demarcacao = cria_pilha();
    printf("Digite a seguir sua equacao: ");

    if(!validade(demarcacao)){
        printf("Expressao invalida.\n");
        limpar_pilha(demarcacao);

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
    }
    CLEAR;
}

/*Modo de calculadora*/
void calcmode(){
printf("aqui");
}

/*Funcao para printar o menu*/
void show_menu(){
        printf("Utilize um '#' para indicar o fim de sua expressao!\n");
        printf("Selecione qual dos modos deseja utilizar\n");
        printf("1. Resolucao de Expressao\n");
        printf("2. Calculadora\n");
        printf("3. Sair\n");

}

/*Definicoes do menu*/
void menu(){   
    int input;

    while(input != 3){   
        show_menu();   
        printf("Selecione uma opcao: ");
        scanf("%d", &input);

        if(input == 1 || input == 2){
            switch(input){
            case 1: resmode();
                break;
            case 2: calcmode();
                break;
            }
        }
        else if(input != 3){
            printf("Por favor, digite uma opcao valida.\n");

        } 
    }
}



int main(){
    CLEAR;
    printf("Bem vindo a calculadora de expressoes\n");
    menu();
    printf("Programa encerrado\n");
    return 0;
}