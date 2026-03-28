#include "titulos_avulsos.h"
#include "motor_de_pesquisa.h"

int main()
{

  inserirTitulo(&head);
  inserirTitulo(&head);
  inserirTitulo(&head);
  
  listarTitulos(&head);

  pesquisarTitulo(&head);

  return 0;
}