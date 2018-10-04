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

#ifndef __LISTA_H__
#define __LISTA_H__

/**
@brief Definições de uma calculadora-validadora de expressões, através do uso de pilhas.
*/

typedef struct elemento{
    char simb;
    int num;
    struct elemento* proximo;
}s_elemento

typedef struct pilha{
    int quantidade;

}s_pilha;
#endif 