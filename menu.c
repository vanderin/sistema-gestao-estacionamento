#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menuInicial()
{
    //limparTerminal();
    printf("\n========================================");
    printf("\n   SISTEMA DE GESTÃO DE ESTACIONAMENTO");
    printf("\n========================================\n");
    
    printf("1: Clientes\n");
    printf("2: Fiscais\n");
    printf("0: Sair\n");
    printf(">> ");
}

void menuCliente()
{
    //limparTerminal();
    printf("\n========================================");
    printf("\n              MENU CLIENTE");
    printf("\n========================================\n");
    
    printf("1: Criar Título Avulso\n");
    printf("2: Criar Pedido de Avença\n");
    printf("3: Efetuar Pagamento de Avença\n");
    printf("0: Voltar Atrás\n");
    
    printf(">> ");
}

void menuFiscal()
{
    //limparTerminal();
    printf("\n========================================");
    printf("\n              MENU FISCAL");
    printf("\n========================================\n");
    
    printf("1: Fiscalizar\n");
    printf("2: Processar Pedido de Avença\n");
    printf("3: Mostrar Pedidos de Avença\n");
    printf("4: Mostrar Pedidos a Aguardar Pagamento\n");
    printf("5: Mostrar Avenças Ativas\n");
    printf("6: Mostrar Títulos Avulsos\n");
    printf("0: Voltar Atrás\n");
    
    printf(">> ");
}