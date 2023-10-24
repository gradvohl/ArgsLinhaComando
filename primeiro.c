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
