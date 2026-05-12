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


void guardarDadosBinarios();
void carregarDadosBinarios();

void menuAvenças() {
    int opcao;
    char matricula[30], nome[100], zona[10], mes[10];

    do {
        printf("\n--- GESTaO DE AVENcAS ---");
        printf("\n1. Submeter Pedido");
        printf("\n2. Processar Proximo Pedido (Aprovar/Rejeitar)");
        printf("\n3. Registar Pagamento e Ativar Avenca");
        printf("\n4. Listar Pedidos Pendentes");
        printf("\n5. Listar Avencas Ativas");
        printf("\n0. Voltar");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Matricula: "); scanf("%s", matricula);
                printf("Nome: "); scanf("%s", nome);
                printf("Zona (ex: C4): "); scanf("%s", zona);
                printf("Mês/Ano (MM/AAAA): "); scanf("%s", mes);
                submeterPedido(matricula, nome, zona, mes);
                break;
            case 2:
                if (filaPedidos.frente == NULL) {
                    printf("Fila vazia.\n");
                } else {
                    int dec;
                    printf("Aprovar pedido de %s? (1-Sim, 0-Não): ", filaPedidos.frente->matricula);
                    scanf("%d", &dec);
                    processarProximoPedido(dec);
                }
                break;
            case 3:
                printf("Matrícula para pagamento: "); scanf("%s", matricula);
                pagarAvenca(matricula);
                break;
            case 4:
                listarPedidos();
                break;
            case 5:
                listarAvencasAtivas();
                break;
        }
    } while (opcao != 0);
}

int main() {
    int opcao;

    // Carregar dados guardados (Persistência Binária)
    carregarDadosBinarios();
    inicializarFila(); // Garante que os ponteiros da fila estão prontos se o ficheiro não existir

    push("Sistema iniciado."); // Registo na Pilha de Sessão

    do {
        printf("\n========================================");
        printf("\n   SISTEMA DE GESTÃO DE ESTACIONAMENTO");
        printf("\n========================================");
        printf("\n1. Emitir Título (Parquímetro)");
        printf("\n2. Efetuar Fiscalização");
        printf("\n3. Gestão de Avenças");
        printf("\n4. Listar Títulos Ativos");
        printf("\n5. Ver Histórico da Sessão (Pilha)");
        printf("\n6. Ver Lista de Infrações");
        printf("\n0. Sair e Guardar");
        printf("\n----------------------------------------");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirTitulo(&head);
                push("Título emitido no parquímetro.");
                break;
            case 2:
                fiscalizar(); // Fluxo sequencial
                break;
            case 3:
                menuAvenças();
                break;
            case 4:
                listarTitulos(&head);
                break;
            case 5:
                listarSessao();
                break;
            case 6:
                listarInfracoes(&head_infracao);
                break;
            case 0:
                printf("\nA guardar dados e a encerrar...\n");
                guardarDadosBinarios();
                limparPilha();
                break;
            default:
                printf("\nOpção inválida!");
        }
    } while (opcao != 0);

    return 0;
}