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
