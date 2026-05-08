//
// Created by CisaveTek1 on 27/03/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avencas.h"
#include "historico_sessao.h"

FilaPedidos filaPedidos = {NULL, NULL};
AvencaAtiva* listaAvencasAtivas = NULL;

void inicializarFila() {
    filaPedidos.frente = NULL;
    filaPedidos.fim = NULL;
}
// Submeter pedido (Adicionar à Fila)
void submeterPedido(char* matricula, char* nome, char* zona, char* mes) {
    static int id_gerador = 1;
    Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
    if (!novo) return;

    novo->id = id_gerador++;
    strcpy(novo->matricula, matricula);
    strcpy(novo->nome, nome);
    strcpy(novo->zona, zona);
    strcpy(novo->mes_ano, mes);
    strcpy(novo->estado, "Submetido");
    novo->next = NULL;

    if (filaPedidos.fim == NULL) {
        filaPedidos.frente = novo;
    } else {
        filaPedidos.fim->next = novo;
    }
    filaPedidos.fim = novo;

    push("Novo pedido de avença submetido."); // Registo na Pilha de Sessão
}

// Processar pedido (Retirar da Fila e decidir) [cite: 65]
void processarProximoPedido(int aprovar) {
    if (filaPedidos.frente == NULL) {
        printf("Não existem pedidos pendentes.\n");
        return;
    }

    Pedido* temp = filaPedidos.frente;

    if (aprovar) {
        strcpy(temp->estado, "Aprovado a aguardar pagamento");
        printf("Pedido %d aprovado. Aguarda pagamento para ativação.\n", temp->id);
        push("Pedido de avença aprovado.");
        // Nota: O enunciado sugere que pedidos aprovados mas não pagos
        // permanecem no sistema[cite: 20]. Aqui, poderiam ser movidos para uma lista temporária.
    } else {
        printf("Pedido %d rejeitado.\n", temp->id);
        push("Pedido de avença rejeitado.");
        filaPedidos.frente = filaPedidos.frente->next;
        if (filaPedidos.frente == NULL) filaPedidos.fim = NULL;
        free(temp);
    }
}

// Registar pagamento e ativar (Mover para Avenças Ativas) [cite: 19, 66]
void pagarAvenca(char* matricula) {
    // Procura nos pedidos aprovados
    Pedido* atual = filaPedidos.frente;
    Pedido* anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0 &&
            strcmp(atual->estado, "Aprovado a aguardar pagamento") == 0) {
            // Criar Avença Ativa [cite: 32]
            AvencaAtiva* nova = (AvencaAtiva*)malloc(sizeof(AvencaAtiva));
            nova->id = atual->id;
            strcpy(nova->matricula, atual->matricula);
            strcpy(nova->zona, atual->zona);
            strcpy(nova->mes_ano, atual->mes_ano);
            nova->pago = 1;
            // Inserir na lista de Ativas
            nova->next = listaAvencasAtivas;
            listaAvencasAtivas = nova;
            // Remover da fila de pedidos
            if (anterior == NULL) filaPedidos.frente = atual->next;
            else anterior->next = atual->next;
            if (atual == filaPedidos.fim) filaPedidos.fim = anterior;

            free(atual);
            printf("Pagamento registado. Avença ativada para a zona %s.\n", nova->zona);
            push("Pagamento de avença recebido.");
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    printf("Nenhum pedido aprovado encontrado para esta matrícula.\n");
}

void listarPedidos() {
    Pedido* atual = filaPedidos.frente;
    printf("\n--- PEDIDOS DE AVENÇA ---\n");
    while (atual) {
        printf("ID: %d | Matrícula: %s | Nome: %s | Zona: %s | Estado: %s\n",
               atual->id, atual->matricula, atual->nome, atual->zona, atual->estado);
        atual = atual->next;
    }
}

void listarAvencasAtivas() {
    AvencaAtiva* atual = listaAvencasAtivas;
    printf("\n--- AVENÇAS ATIVAS ---\n");
    while (atual) {
        printf("ID: %d | Matrícula: %s | Zona: %s | Validade: %s\n",
               atual->id, atual->matricula, atual->zona, atual->mes_ano);
        atual = atual->next;
    }
}