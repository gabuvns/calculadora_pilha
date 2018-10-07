/*
Aluno: Carlos Gabriel Vilas Novas Soares
Matrícula: 18/0056298
Universidade de Brasília
Departamento de Ciência da Computação
Estruturas de Dados - Turma A - 2018/2
Prof. Dr. Marcos Caetano
*/

/*Doxygen*/

/**
@file pilha.h
@author Carlos Gabriel
@date Outubro de 2018
@brief Definições dos elementos de uma calculadora de expressões

@see https://github.com/gabuvns
*/

#ifndef __PILHA_H__
#define __PILHA_H__

/**
@brief Definições de uma calculadora-validadora de expressões, através do uso de pilhas.
*/

/*Aqui se encontram as defnições das structs utilizadas.*/
typedef struct elemento{
    char caractere; 
    struct elemento* proximo;
}s_elemento;

typedef struct pilha{
    int quantidade; 
    struct elemento* inicio;
    struct elemento* topo;
}s_pilha;


s_elemento* cria_elemento(char input);

/*Operações com a pilha*/

s_pilha* cria_pilha();
int pilha_vazia(s_pilha* pilha);
void limpar_pilha(s_pilha* pilha);
void get(s_pilha* pilha);
void pop(s_pilha* pilha);
void push(s_pilha* pilha, char input);
void mostrar_pilha(s_pilha* pilha);

#endif