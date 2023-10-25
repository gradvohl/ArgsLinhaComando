#include <stdio.h>  
#include <getopt.h> /* Cabecalho para o getopt.*/

int main(int argc, char *argv[])
{
  int opcao;
  char *arqA;
  char *arqB;

  /*Análise de cada uma das opcoes*/
  while ((opcao = getopt(argc, argv, "a:b:")) != -1) 
  {
     switch (opcao) 
     {
      case 'a':
        printf("A opcao a foi identificada.\n");
	arqA = optarg;
	printf("Argumento da opcao a: %s\n", arqA);
        break;
      case 'b':
        printf("A opcao b foi identificada.\n");
	arqB = optarg;
	printf("Argumento da opcao b: %s\n", arqB);
        break;
     }
  }
 
  printf("Informacao indicada para a opcao A: %s\n", arqA);
  printf("Informacao indicada para a opcao B: %s\n", arqB);

  return 0;
}
