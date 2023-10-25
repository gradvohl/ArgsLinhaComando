#include <stdio.h>  
#include <getopt.h> /* Cabecalho para o getopt.*/

int main(int argc, char *argv[])
{
  int opcao;

  /*Análise de cada uma das opcoes*/
  while ((opcao = getopt(argc, argv, "abC")) != -1) 
  {
     switch (opcao) 
     {
      case 'a':
        printf("A opcao a foi identificada\n");
        break;
      case 'b':
        printf("A opcao b foi identificada\n");
        break;
      case 'C':
        printf("A opcao C foi identificada\n");
        break;
     }
  }
  
  return 0;
}
