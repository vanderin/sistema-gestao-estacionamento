#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avencas.h"
#include "titulos_avulsos.h"
#include "historico_sessao.h"
#include "historico_permanente.h"
#include "motor_de_pesquisa.h"
#include "infracoes.h"

int main()
{
    criarPedido("ABC123", "John", "A1", 01, 2020);
    listarPedidos();
    listarPedidosPagamento();
    listarAvencasAtivas();
    
    processarProximoPedido(&filaPedidos);
    listarPedidos();
    listarPedidosPagamento();
    listarAvencasAtivas();
    
    pagarAvenca("ABC123");
    listarPedidos();
    listarPedidosPagamento();
    listarAvencasAtivas();

    criarPedido("HGY632", "Malaquias", "B3", 5, 2026);
    listarPedidos();
    listarPedidosPagamento();
    listarAvencasAtivas();
    
    processarProximoPedido(&filaPedidos);
    listarPedidos();
    listarPedidosPagamento();
    listarAvencasAtivas();
    
    pagarAvenca("HGY632");
    listarPedidos();
    listarPedidosPagamento();
    listarAvencasAtivas();
    
    
   return 0;
}