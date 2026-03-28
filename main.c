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

  adicionarInfracao(&head_infracao, "a");
  listarInfracoes(&head_infracao);
  
  pesquisarInfracao(&head_infracao);
  listarInfracoes(&head_infracao);
  
  return 0;
}