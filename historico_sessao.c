//
// Created by Utilizador on 15/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico_sessao.h"
#include "historico_permanente.h" // Para gravar no TXT ao mesmo tempo

// A pilha começa vazia no início da execução
NoPilha* topo = NULL;

// Inserir um novo evento no topo da pilha
void push(char* mensagem) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo == NULL) return;

    strcpy(novo->evento, mensagem);
    novo->next = topo;
    topo = novo;

    registarNoHistoricoTXT(mensagem);
}

// Remover o elemento do topo
void pop() {
    if (topo == NULL) return;
    NoPilha* temp = topo;
    topo = topo->next;
    free(temp);
}

// Listar o histórico da sessão
void listarSessao() {
    if (topo == NULL) {
        printf("Nenhum evento registado nesta sessão.\n");
        return;
    }

    printf("\n--- HISTÓRICO DA SESSÃO ATUAL (Pilha) ---\n");
    NoPilha* atual = topo;
    while (atual != NULL) {
        printf("-> %s\n", atual->evento);
        atual = atual->next;
    }
    printf("\n");
}

// Limpar a memória no final do programa
void limparPilha() {
    while (topo != NULL) {
        pop();
    }
}