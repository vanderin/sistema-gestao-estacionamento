#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "avencas.h"
#include "titulos_avulsos.h"
#include "historico_sessao.h"
#include "historico_permanente.h"
#include "motor_de_pesquisa.h"
#include "infracoes.h"
#include "menu.h"

/*
void guardarDadosBinarios();
void carregarDadosBinarios();
*/

static void fluxoCliente(void)
{
    int opcao;
    char matricula[30];
    char nome[100];
    char zona[10];
    int mes;
    int ano;

    do
    {
        menuCliente();
        if (scanf("%d", &opcao) != 1)
        {
            scanf("%*s");
            opcao = -1;
        }

        switch (opcao)
        {
            case 1:
                inserirTitulo(&head_titulos_avulsos);
                sleep(5);
                break;
            case 2:
                printf("Matrícula: ");
                scanf("%29s", matricula);
                printf("Nome: ");
                scanf("%99s", nome);
                printf("Zona: ");
                scanf("%9s", zona);
                printf("Mês (1 - 12): ");
                scanf("%d", &mes);
                printf("Ano: ");
                scanf("%d", &ano);
                criarPedido(matricula, nome, zona, mes, ano);
                sleep(5);
                break;
            case 3:
                printf("Insira a Matrícula: ");
                scanf("%29s", matricula);
                pagarAvenca(matricula);
                sleep(5);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }
    while (opcao != 0);
}

static void fluxoFiscal(void)
{
    int opcao;

    do
    {
        menuFiscal();
        if (scanf("%d", &opcao) != 1)
        {
            scanf("%*s");
            opcao = -1;
        }

        switch (opcao)
        {
            case 1:
                fiscalizar();
                sleep(10);
                break;
            case 2:
                processarProximoPedido(&filaPedidos);
                sleep(3);
                break;
            case 3:
                listarPedidos();
                sleep(5);
                break;
            case 4:
                listarPedidosPagamento();
                sleep(5);
                break;
            case 5:
                listarAvencasAtivas();
                sleep(5);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
                sleep(3);
                break;
        }
    }
    while (opcao != 0);
}

int main()
{
    int opcao;

    inicializarFila();
    // carregarDadosBinarios();

    do
    {
        menuInicial();
        if (scanf("%d", &opcao) != 1)
        {
            scanf("%*s");
            opcao = -1;
        }

        switch (opcao)
        {
            case 1:
                fluxoCliente();
                break;
            case 2:
                fluxoFiscal();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }
    while (opcao != 0);

    // guardarDadosBinarios();
    return 0;
}