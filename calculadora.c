#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

/*Utilizado para limpar o terminal dependendo do sistema*/
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

/*Checagem se o char eh um numero*/
int ehnumero(char entrada){
    if(entrada == '0' || entrada == '2'  || entrada == '1'|| entrada == '3' || entrada == '4' || entrada == '.' ||
    entrada == '5' || entrada == '6' || entrada == '7' || entrada == '8' || entrada == '9' )
    {
        return 1;
    }    
    else{
        return 0;
    } 
}
//Fim ehnumero()
int ehoperando(char entrada){
    if(entrada == '*' || entrada == '/'  || entrada == '-'  || entrada == '+' ){
        return 1;   
    }
    else{
        return 0;
    }
}

/*Transformacao de char para double*/
double chpdb(char* numero){
    int k;
    k = 0;
    double dec = 0;
    double frac = 0;
    double cont_frac = 1;

    while(k < strlen(numero) && numero[k] != '.'){
        dec = dec*10 + (numero[k] - 48);
        k++;
    }

    if(numero[k] == '.'){
        k++;
        while(numero[k] != '\0'){
            cont_frac = cont_frac * 0.1;
            frac = frac + (numero[k] - 48) * cont_frac;
            k++;
        }
    }

    return dec + frac;
}
//Fim chpdb()

/*Funcao para receber input*/
void pega_expressao(char* expressao, s_pilha* simbolos){
    int i = 0;
    scanf(" %[^\n]s", expressao);
    while(expressao[i] != '\0'){
        if(expressao[i] != ' '){
            push(simbolos, expressao[i]);
        }
        i++;
    } 
    push(simbolos, expressao[i]);
}   

/*Inicio das funcoes exclusivas ao modo de resolucao*/

/*Primeira etapa: Analisar a validade da funcao*/
int validade(char* expressao){
    int i = 0;
    int contador = 0; //utilizada para definir de onde ate onde vao os numeros
    
    s_pilha* validador = cria_pilha();
    
    /*Inicialmente sera checado  se os simbolos sao validos*/
    while(expressao[i] != '\0'){
        if(expressao[i] == '('){
            if(ehnumero(expressao[i-1])){
                return 0;
            }
            push(validador, 'a');
            contador = 0;
        }

        else if(expressao[i] == ')'){
            if(pilha_vazia(validador) || ehoperando(expressao[i-1])){
                return 0;
            }
            push(validador, 'f');
            contador = 0;
        }

        else if(ehnumero(expressao[i]) && contador == 0){
            if(expressao[i-1]== ')'){
                return 0;
            }
            else{
                push(validador, 'v');
                contador = 1;
            }
        }

        else if(ehoperando(expressao[i])){
            if(expressao[i] == '-'){ /*Sem isso a funcao 2*(-5) fica invalidada*/
            }
            else if(expressao[i-1] == '(' || ehoperando(expressao[i-1])){
                return 0;
            }
        }
        i++;
    }
    limpar_pilha(validador); //nao eh possivel reaproveitar o mesmo nome
    
    /*Agora serao checados os parenteses*/
    s_pilha* parenteses = cria_pilha();
    i = 0;

    while(expressao[i] != '\0'){
        if(expressao[i] == '('){
            push(parenteses, '(');
            
        }
        else if(expressao[i] == ')'){
            if(pilha_vazia(parenteses)){
                return 0;
            }
            else if (parenteses->quantidade == 1){
                if(parenteses->inicio->caractere == '('){
                    pop(parenteses);
                }
                else{
                    return 0;
                }
            }

            else{
                pop(parenteses);
            }
        }
        i++;
        
    }
    if(pilha_vazia(parenteses)){    
        limpar_pilha(parenteses); 
        
        return 1;
    }
    else{
        limpar_pilha(parenteses); 

        return 0;
    }


}
/*Fim da validacao da expressao*/
/*Fim da primeira etapa*/

/*Inicio segunda etapa: infixa para posfixa*/
/*Funcao de Prioridade*/
int prioridade(char caractere, char topo){
    int vcarac;
    int vtopo;

    if(caractere == '+' || caractere == '-'){
        vcarac = 0;
    }
    else if(caractere == '*' || caractere == '/'){
        vcarac = 1;
    }
    else if(caractere == '('){
        vcarac = 2;
    }

    if(topo == '+' || topo == '-'){
        vtopo = 0;
    }
    else if(topo == '*' || topo == '/'){
        vtopo = 1;
    }
    else if(topo == '('){
        vtopo = 2;
    }

    if(vtopo < vcarac){
        return 1;
    }
    else if(vtopo == vcarac){
        return 2;
    }
    else {
        return 2;
    }

}


/*Infixa para posfixa*/
void inftopos(s_pilha* simbolos, char* calculo_final){

    s_elemento* elem_aux;
    s_pilha* anda = cria_pilha();
    elem_aux = simbolos->inicio;
    char ch[100];
    double db;
    int k, i; //k sera usado para o vetor ch e i para a string que ira para a proxima funcao
    char tt;
    printf("Expressao pos-fixa = \n");

    while(elem_aux->caractere != '\0'){
        if(ehnumero(elem_aux->caractere)){
            k = 0;
            while(ehnumero(elem_aux->caractere)){
                ch[k] = elem_aux->caractere;
                elem_aux = elem_aux->proximo;
                calculo_final[i] = ch[k];
                i++;
                k++;
            }
            calculo_final[i] = ' ';
            i++;

            db = chpdb(ch);
            printf("%.2lf ", db);

        }

        else if(elem_aux->caractere == ' '){
            elem_aux = elem_aux->proximo;
            calculo_final[i] = ' ';
            i++;
            calculo_final[i] = ' ';
            i++;

        }

        else if(elem_aux->caractere == (')')){
            
            while(!pilha_vazia(anda)){
                if(get(anda) != '('){
                    printf("%c ", get(anda));
                    calculo_final[i] = get(anda);
                    i++;
                    calculo_final[i] = ' ';
                    i++;

                }
                pop(anda);
   
            }
            elem_aux = elem_aux->proximo;

        }
        
       else{

            if(pilha_vazia(anda)){
                push(anda, elem_aux->caractere);
                
            }

            else if(prioridade(elem_aux->caractere, get(anda)) == 1){
                push(anda, elem_aux->caractere);

            }

           else if(prioridade(elem_aux->caractere, get(anda)) == 2){
               
                tt = get(anda);
                if(tt != '('){
                    while(!pilha_vazia(anda) && prioridade(elem_aux->caractere, get(anda)) == 2){
                        tt = get(anda);
                        printf("%c ", tt);
                        calculo_final[i] = tt;
                        i++;
                        calculo_final[i] = ' ';
                        i++;
                        pop(anda);

                    }
                    push(anda, elem_aux->caractere);
                }
                else{
                    push(anda, elem_aux->caractere);
                }
            
            }
            elem_aux = elem_aux->proximo;

        }
    }

    while(!pilha_vazia(anda)){
        printf("%c ", get(anda));
        calculo_final[i] = get(anda);
        i++;
        pop(anda);

    }
    calculo_final[i] = '\0';
    limpar_pilha(anda);
    char z;
    do{
        printf("\nDigite 'r' para a proxima etapa.\n");
        scanf(" %c", &z);

    }while(z != 'R' && z!= 'r');
 CLEAR;
}
/*Fim da terceira etapa*/
/*Início da terceira etapa*/
double operacao(double elem1, double elem2, char operando){
    float n;
    if(operando == '+'){
        n = elem1 + elem2;
        return n;
    }
    else if(operando == '-'){
        n = elem2 - elem1;
        return n;
        
    }
    else if(operando == '*'){
        n = elem1 * elem2;
        return n;
    }
    else if(operando == '/'){
        n = elem2 / elem1;
        return n;
    }
    else{
        return 1;
    }
}
void calcula_expressao(char* calculo_final){
    n_pilha* calcular = cria_pilhanumerica();
    double db;
    char entry[21];
    double elem1, elem2, elem3;
    int i, j;

    while(calculo_final[i] != '\0'){
        j = 0;

        if(ehnumero(calculo_final[i])){
            while(ehnumero(calculo_final[i])){
                entry[j] = calculo_final[i];
                j++;
                i++;

            }
            db = chpdb(entry);  
            push_num(calcular, db);

        }
        else if(ehoperando(calculo_final[i])){
            elem1 = getnum(calcular);
            n_pop(calcular);
            elem2 = getnum(calcular);
            n_pop(calcular);
            elem3 = operacao(elem1, elem2, calculo_final[i]);
            push_num(calcular, elem3);
            i++;  

        }
        
        else if (calculo_final[i]){
            i++;
        }
    }
    printf("Resultado da operacao = %.3lf\n", getnum(calcular));
    char y;
    do{
        printf("Digite 'r'  para retornar ao menu.\n");
        scanf(" %c", &y);

    }while(y != 'R' && y != 'r');
    limpar_pilha_num(calcular);
}

/*Fim calcula expressao*/
/*Fim da terceira etapa, retornar ao menu após*/


/*Modo de resolucao*/
void resmode(){
    CLEAR;
    char expressao[2000];
    char calculo_final[2000];

    char con;
    s_pilha* simbolos = cria_pilha();

    printf("Digite sua equacao a seguir:\n");
    pega_expressao(expressao, simbolos);

    if(!validade(expressao)){
        printf("Expressao invalida, reformule-a e tente novamente.\n");
        do{
            printf("Digite 'r'  para retornar ao menu.\n");
            scanf(" %c", &con);

        }while(con != 'R' && con != 'r');

    }

    else{
        printf("Expressao Valida!\n");
        do{
            printf("Digite 'r' para a proxima etapa.\n");
            scanf(" %c", &con);
        }while(con != 'R' && con != 'r');
        CLEAR;
        inftopos(simbolos, calculo_final);
        calcula_expressao(calculo_final);

    }
    limpar_pilha(simbolos);
    CLEAR;
}

/*Fim do modo de resolucao*/

/*Fim das definicoes referentes ao modo de resolucao*/

/*Configuracoes referentes ao modo calculadora*/
void calcmode(){
    n_pilha* calculadora = cria_pilhanumerica();
    char entrada[200];
    char k;
    double db, elem1, elem2, elem3;
    CLEAR;

    printf("Bem vindo, caso deseje sair, basta digitar 's'\n");

    while(entrada[0] != 's'  && entrada[0] != 'S'){
        mostrar_pilha_num(calculadora);
        scanf("%s", entrada);

        if(ehnumero(entrada[0])){
            db = chpdb(entrada);
            push_num(calculadora, db);
        }

        else if(ehoperando(entrada[0])){
            if(calculadora->quantidade == 1){
                printf("==Quantidade de operandos insuficientes!==\n");
                do{
                printf("Digite 'r'  para continuar.\n");
                scanf(" %c", &k);
                }while(k != 'R' && k != 'r');
            }
            else{
                elem1 = getnum(calculadora);
                n_pop(calculadora);
                elem2 = getnum(calculadora);
                n_pop(calculadora);
                elem3 = operacao(elem1, elem2, entrada[0]);
                push_num(calculadora, elem3);
            }
        }

        CLEAR;
    }
    limpar_pilha_num(calculadora);
    CLEAR;
}

/*Configuracoes referentes ao menu*/
void tutorial(){
    CLEAR;
    char x;
    printf("Basta selecionar um modo digitando a opcao desejada.\n\n");
    printf("1) No modo de Resolucao de Expressao, eh necessaria ");
    printf("a adicao de '.00' caso seja um numero inteiro, como a seguir:\n");
    printf("(60.00 + 35.5234)* 45.00 - 35.00\n\n");
    printf("2) No modo calculadora, basta digitar 's' para sair.\n\n");
    printf("Para mais informacoes consulte o readme\n");
    printf("Pressione qualquer tecla para retornar ao menu.\n");
    do{
        printf("Digite 'r'  para retornar ao menu.\n");
        scanf(" %c", &x);
    }while(x != 'R' && x != 'r');
}
/*Funcao para printar o menu*/
void show_menu(){
        printf("Selecione qual dos modos deseja utilizar\n");
        printf("1. Resolucao de Expressao\n");
        printf("2. Calculadora\n");
        printf("3. Tutorial\n");
        printf("4. Sair\n");
        
}


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

