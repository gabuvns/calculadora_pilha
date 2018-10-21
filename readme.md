# Calculadora de expressões
Versão do compilador e do OS utilizada:

gcc (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609

# Passos para compilar:

gcc -c pilha.c

gcc -c calculadora.c

gcc -o prog main.c pilha.c calculadora.c

./prog

# Bibliotecas utilizadas:

Foram incluidas: stdlib.h, stdio.h, string.h, "pilha.h"

# Código Legacy

Durante o projeto tornou-se necessário que o código fosse reescrito, tendo em vista a falta de consistência que resultavam em diversos bugs e não permitiam certas operações.

Para a versão mais atualizada visite: https://github.com/gabuvns/calculadora_pilha
