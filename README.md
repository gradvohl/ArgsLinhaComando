
# Passagem de argumentos pela linha de comando para programas na linguagem C
Este é um breve tutorial para a passagem de argumentos pela linha de comando para programas na linguagem C. A vantagem dessa passagem de argumentos é informar, já no início do programa, quais são os dados básicos necessários para seu funcionamento. Se o programa tiver todos os dados que precisa já no seu início, não será preciso ficar solicitando ao usuário por mais dados.

Destacamos que os programas exemplo que estão neste repositório foram escritos para a linguagem C para o sistema operacional Linux. Os conceitos são os mesmos para outros sistemas operacionais. Mas, as bibliotecas utilizadas podem ser um pouco diferentes.

Dividimos esse tutorial em duas partes. A [primeira parte](#passagem-de-argumentos-pela-linha-de-comando) é bem básica, para aqueles que estão iniciando ou que querem fazer um programa rápido, no qual o usuário já sabe de antemão a quantidade e o tipo dos argumentos que o programa espera receber.

A segunda parte é mais avançada e utiliza uma biblioteca que permite uma especificação mais profissional dos argumentos que serão passados para o programa.

## Passagem de argumentos pela linha de comando
Para que seu programa receba argumentos da linha de comando, é preciso que a sua função ``main`` tenha a seguinte assinatura:
```c
int main( int argc, char *argv[ ] )
```
Vamos aos detalhes:

``argc`` -- é uma variável do tipo inteiro que contém a quantidade de argumentos passados na chamada do programa. **Importante**: o nome do programa também é um argumento. Portanto, a variável ``argc`` terá sempre um valor maior ou igual a 1.

``argv`` – é uma variável do tipo "ponteiro para vetor de _strings_". Isso significa que ``argv`` é um vetor alocado dinamicamente, cujo tamanho depende da quantidade de argumentos passados pela linha de comando. Cada elemento desse vetor, por sua vez, é uma _string_ que contém um dos argumentos passados para o programa. 

Se você entendeu bem as definições anteriores, pode perceber que:

1. A variável ``argc`` determina o tamanho do vetor ``argv``.
2. A posição zero do vetor ``argv``, isto é ``argv[0]``, armazenará o nome do programa.
3. Todos os argumentos informados ao programa estarão armazenados no vetor ``argv`` na ordem em que foram informados.

Ilustremos esses conceitos básicos com um programa bem simples a seguir. Esse programa foi chamado de ``primeiro.c`` e está disponível neste repositório.
```c
#include <stdio.h>
int main(int argc, char *argv[])
{
  int cont;
  printf("Quantidade de parametros: %d\n", argc);
  for(cont=0; cont < argc; cont++)
  {
    printf("argv[%d]: %s\n", cont, argv[cont]);
  }
  return 0;
}

```
Note, no laço com o comando ``for``, que a variável ``cont`` varia entre zero e menor que ``argc``. Com isso, o comando ``printf`` no laço mostrará o conteúdo da posição indicada por ``cont`` no vetor ``argv``. 

Compile o programa ``primeiro.c`` com a linha de comando a seguir.
```bash
gcc primeiro.c -o primeiro.o
```
Depois de compilado, execute o programa passando vários argumentos pela linha de comando. Eis um exemplo:
```bash
./primeiro.o 1 2 abc 3.45
```
Se tudo funcionou, a saída esperada do programa é a seguinte:
```bash
Quantidade de parametros: 5
argv[0]: ./primeiro.o
argv[1]: 1
argv[2]: 2
argv[3]: abc
argv[4]: 3.45
```
Como comentamos antes, note que o primeiro argumento (que está em ``argv[0]``) é o próprio nome do programa. Em seguida, estão os demais argumentos.

**É importante destacar que cada um dos argumentos é uma _string_. Afinal, estão armazenados em ``argv``, um vetor de _strings_.** Portanto, se você quiser utilizar os argumentos como valores inteiros ou reais, é preciso convertê-los antes. Vejamos como fazer a seguir.

### Conversão de argumentos de strings para valores numéricos
No exemplo anterior, nossa preocupação era apenas mostrar os argumentos passados pela linha de comando. Agora, faremos um programa um pouco mais complexo para ilustrar a conversão de parâmetros. 
O programa a seguir receberá três parâmetros da linha de comando na seguinte sequência: um número inteiro; um operador entre ``+``, ``-``, ``*`` ou ``/``; e outro número inteiro. No final, o programa mostrará a operação matemática do primeiro número com o segundo.
Vejamos o programa:
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int operando1;
  int operando2;
  char operacao;

  /*Caso o usuario nao informe a quantidade correta de parametros*/
  if (argc != 4)
  {
    fprintf(stderr,"Uso:\n\t %s numero <operacao> numero\n", argv[0]);
    fprintf(stderr,"\nOnde <operacao> e uma das operacoes matematicas basicas (+, -, *, /)\n");
    return 1;
  }

  operando1 = atoi(argv[1]);

 /* Na string da posicao 2 do vetor argv, isto e, argv[2],
  * vamos pegar o primeiro caractere, isto é, argv[2][0].
  */
  operacao = argv[2][0];

  operando2 = atoi(argv[3]);

  switch(operacao)
  {
   case '+': printf("%d + %d = %d\n", operando1, operando2, operando1 + operando2);
             break;
   case '-': printf("%d - %d = %d\n", operando1, operando2, operando1 - operando2);
             break;
   case '*': printf("%d * %d = %d\n", operando1, operando2, operando1 * operando2);
             break;
   case '/': printf("%d / %d = %.2f\n", operando1, operando2, operando1 / (float) operando2);
             break;
   default: fprintf(stderr,"Operacao (%c) desconhecida.\n", operacao);
            return 1;
  }
  return 0;
}
```
Observe que, no primeiro teste feito no comando ``if``, verificamos se o usuário informou a quantidade correta de argumentos (4 nesse exemplo). Se a quantidade de argumentos, informada na variável ``argc`` for diferente de 4, então o programa emite uma mensagem de erro e termina retornando o código 1.
Se o programa não terminou, então a variável ``operando1`` receberá o primeiro argumento após o nome do programa (que está na variável ``argv[1]``), já convertido de _string_ para número inteiro,  usando a função ``atoi``.  Os detalhes sobre a função ``atoi`` podem ser vistos utilizando o comando ``man atoi``.
Em seguida, a variável ``operacao`` receberá o segundo argumento após o nome do programa (que está na variável ``argv[2]``). Note que a variável ``operacao`` é do tipo ``char``, isto é, armazena um único caractere; enquanto a variável ``argv[2]`` é uma _string_ que deve conter dois caracteres (o operador, que pode ser ``+``, ``-``, ``*`` ou ``/`` e o terminador de _strings_, o ``\0``). No nosso caso, estamos interessados apenas no primeiro caractere (o operador). Por isso, obtemos a primeira posição (posição zero) do vetor ``argv`` na posição 2. Ou seja, o comando é o seguinte:
```c
operacao = argv[2][0];
```
Por fim, a variável ``operando2`` obtém o terceiro argumento após o nome do programa (que está na variável ``argv[3]``), já convertido de _string_ para número inteiro,  usando a função ``atoi``, na mesma forma que a variável ``operando1`` obteve.


Para ver o exemplo funcionando, compile o programa ``segundo.c`` com a linha de comando a seguir.
```bash
gcc segundo.c -o segundo.o
```
Depois de compilado, execute o programa passando os argumentos pela linha de comando. Eis um exemplo:
```bash
./segundo.o 1 + 2 
```

Faça outros testes e verifique como o programa se comporta.

### Em resumo
Para resumir, fique atento aos tipos de dados que você utilizar para representar os argumentos da linha de comando. Se você for utilizar um determinado argumento como _string_, você poderá utilizar a posição específica da variável ``argv`` sem problemas. Embora minha recomendação seja copiar a posição específica da variável ``argv`` para outra _string_, para não causar confusão.

Se você deseja interpretar um determinado argumento como um número **inteiro**, utilize a função ``atoi`` para converter a posição específica da variável ``argv`` para inteiro.

Se você deseja interpretar um determinado argumento como um número **real**, utilize a função ``atof`` para converter a posição específica da variável ``argv`` para real.
