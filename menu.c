#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

#define C_RESET   "\033[0m"
#define C_TITULO  "\033[1;36m"
#define C_OPCAO   "\033[0;37m"
#define C_PROMPT  "\033[0;33m"
#define C_SAIDA   "\033[0;37m"
#define C_AVISO   "\033[1;33m"
#define C_ERRO    "\033[1;31m"

static void printComCor(const char *cor, const char *texto)
{
    printf("%s%s%s", cor, texto, C_RESET);
}

void printTitulo(const char *texto)
{
    printComCor(C_TITULO, texto);
}

void printOpcao(const char *texto)
{
    printComCor(C_OPCAO, texto);
}

void printPrompt(const char *texto)
{
    printComCor(C_PROMPT, texto);
}

void printSaida(const char *texto)
{
    printComCor(C_SAIDA, texto);
}

void printAviso(const char *texto)
{
    printComCor(C_AVISO, texto);
}

void printErro(const char *texto)
{
    printComCor(C_ERRO, texto);
}

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
    printTitulo("\n========================================");
    printTitulo("\n   SISTEMA DE GESTÃO DE ESTACIONAMENTO");
    printTitulo("\n========================================\n");
    
    printOpcao("1: Clientes\n");
    printOpcao("2: Fiscais\n\n");

    printOpcao("3: Histórico da Sessão\n\n");

    printOpcao("0: Sair\n");
    printPrompt(">> ");
}

void menuCliente()
{
    //limparTerminal();
    printTitulo("\n========================================");
    printTitulo("\n              MENU CLIENTE");
    printTitulo("\n========================================\n");
    
    printOpcao("1: Criar Título Avulso\n");
    printOpcao("2: Criar Pedido de Avença\n");
    printOpcao("3: Efetuar Pagamento de Avença\n\n");
    
    printOpcao("4: Histórico da Sessão\n\n");
    
    printOpcao("0: Voltar Atrás\n");
    
    printPrompt(">> ");
}

void menuFiscal()
{
    //limparTerminal();
    printTitulo("\n========================================");
    printTitulo("\n              MENU FISCAL");
    printTitulo("\n========================================\n");
    
    printOpcao("1: Fiscalizar\n");
    printOpcao("2: Processar Pedido de Avença\n");
    printOpcao("3: Mostrar Pedidos de Avença\n");
    printOpcao("4: Mostrar Pedidos a Aguardar Pagamento\n");
    printOpcao("5: Mostrar Avenças Ativas\n");
    printOpcao("6: Mostrar Títulos Avulsos\n");
    printOpcao("7: Mostrar Infrações\n\n");

    printOpcao("8: Histórico da Sessão\n\n");
    
    printOpcao("0: Voltar Atrás\n");
    
    printPrompt(">> ");
}