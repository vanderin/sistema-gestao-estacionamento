#include "titulos_avulsos.h"
#include "motor_de_pesquisa.h"
#include "infracoes.h"

int main()
{
/*
inserirTitulo(&head);
inserirTitulo(&head);
inserirTitulo(&head);

listarTitulos(&head);

pesquisarTitulo(&head);
*/
  
  inserirTitulo(&head);
  inserirTitulo(&head);
  inserirTitulo(&head);

  listarTitulos(&head);

  fiscalizar();
  
  listarInfracoes(&head_infracao);
  
  return 0;
}