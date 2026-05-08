//
// Created by Utilizador on 21/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "titulos_avulsos.h"
#include "avencas.h"
#include "infracoes.h"

void guardarDadosBinarios() {
    // Guardar Títulos Avulsos
    FILE *fTitulos = fopen("titulos.bin", "wb");
    if (fTitulos) {
        Titulo* atual = head;
        while (atual != NULL) {
            // Gravamos a estrutura, mas o campo 'next' gravado será ignorado ao ler
            fwrite(atual, sizeof(Titulo), 1, fTitulos);
            atual = atual->next;
        }
        fclose(fTitulos);
    }

    // Guardar Pedidos de Avença
    FILE *fPedidos = fopen("pedidos.bin", "wb");
    if (fPedidos) {
        Pedido* atual = filaPedidos.frente;
        while (atual != NULL) {
            fwrite(atual, sizeof(Pedido), 1, fPedidos);
            atual = atual->next;
        }
        fclose(fPedidos);
    }

    // Guardar Avenças Ativas
    FILE *fAtivas = fopen("avencas_ativas.bin", "wb");
    if (fAtivas) {
        AvencaAtiva* atual = listaAvencasAtivas;
        while (atual != NULL) {
            fwrite(atual, sizeof(AvencaAtiva), 1, fAtivas);
            atual = atual->next;
        }
        fclose(fAtivas);
    }

    // Guardar Lista de Infrações
    FILE *fInfracoes = fopen("infracoes.bin", "wb");
    if (fInfracoes) {
        Infracao* atual = head_infracao; // Usa a global externa
        while (atual != NULL) {
            // Gravamos a estrutura (o ponteiro 'next' será ignorado na leitura)
            fwrite(atual, sizeof(Infracao), 1, fInfracoes);
            atual = atual->next;
        }
        fclose(fInfracoes);
    }
}




void carregarDadosBinarios() {
    // Carregar Títulos
    FILE *fTitulos = fopen("titulos.bin", "rb");
    if (fTitulos) {
        // Limpar a lista atual para evitar duplicados ou fugas de memória
        head = NULL;
        Titulo temp;
        while (fread(&temp, sizeof(Titulo), 1, fTitulos)) {
            Titulo* novo = (Titulo*)malloc(sizeof(Titulo));
            if (novo) {
                *novo = temp;       // Copia os dados
                novo->next = head;  // Insere no início e limpa o ponteiro antigo lido
                head = novo;
            }
        }
        fclose(fTitulos);
    }

    // Carregar Pedidos de Avença
    FILE *fPedidos = fopen("pedidos.bin", "rb");
    if (fPedidos) {
        // Reinicializa a fila
        filaPedidos.frente = NULL;
        filaPedidos.fim = NULL;
        Pedido temp;
        while (fread(&temp, sizeof(Pedido), 1, fPedidos)) {
            // Criamos um novo nó para evitar usar o ponteiro 'next' inválido do ficheiro
            Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
            if (novo) {
                *novo = temp;
                novo->next = NULL; // Limpeza

                // Reconstrução da Fila (FIFO)
                if (filaPedidos.fim == NULL) {
                    filaPedidos.frente = novo;
                } else {
                    filaPedidos.fim->next = novo;
                }
                filaPedidos.fim = novo;
            }
        }
        fclose(fPedidos);
    }

    // Carregar Avenças Ativas
    FILE *fAtivas = fopen("avencas_ativas.bin", "rb");
    if (fAtivas) {
        listaAvencasAtivas = NULL;
        AvencaAtiva temp;
        while (fread(&temp, sizeof(AvencaAtiva), 1, fAtivas)) {
            AvencaAtiva* nova = (AvencaAtiva*)malloc(sizeof(AvencaAtiva));
            if (nova) {
                *nova = temp;
                nova->next = listaAvencasAtivas; // Insere e limpa ponteiro antigo
                listaAvencasAtivas = nova;
            }
        }
        fclose(fAtivas);
    }

    // Carregar Lista de Infrações
    FILE *fInfracoes = fopen("infracoes.bin", "rb");
    if (fInfracoes) {
        head_infracao = NULL; // Garante que a lista começa limpa
        Infracao temp;
        while (fread(&temp, sizeof(Infracao), 1, fInfracoes)) {
            // Alocar memória para o novo nó
            Infracao* nova = (Infracao*)malloc(sizeof(Infracao));
            if (nova) {
                *nova = temp;       // Copia os dados (matrícula, data, etc)
                nova->next = head_infracao; // Insere no início da lista
                head_infracao = nova;
            }
        }
        fclose(fInfracoes);
    }
}