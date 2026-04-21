//
// Created by Utilizador on 21/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "titulos_avulsos.h"
#include "avencas.h"

void guardarDadosBinarios() {
    // 1. Guardar Títulos Avulsos (Lista Ligada)
    FILE *fTitulos = fopen("titulos.bin", "wb");
    if (fTitulos) {
        Titulo* atual = head;
        while (atual != NULL) {
            fwrite(atual, sizeof(Titulo), 1, fTitulos);
            atual = atual->next;
        }
        fclose(fTitulos);
    }

    // 2. Guardar Pedidos de Avença (Fila)
    FILE *fPedidos = fopen("pedidos.bin", "wb");
    if (fPedidos) {
        Pedido* atual = filaPedidos.frente;
        while (atual != NULL) {
            fwrite(atual, sizeof(Pedido), 1, fPedidos);
            atual = atual->next;
        }
        fclose(fPedidos);
    }

    // 3. Guardar Avenças Ativas (Lista Ligada)
    FILE *fAtivas = fopen("avencas_ativas.bin", "wb");
    if (fAtivas) {
        AvencaAtiva* atual = listaAvencasAtivas;
        while (atual != NULL) {
            fwrite(atual, sizeof(AvencaAtiva), 1, fAtivas);
            atual = atual->next;
        }
        fclose(fAtivas);
    }
}






void carregarDadosBinarios() {
    // 1. Carregar Títulos
    FILE *fTitulos = fopen("titulos.bin", "rb");
    if (fTitulos) {
        Titulo temp;
        while (fread(&temp, sizeof(Titulo), 1, fTitulos)) {
            Titulo* novo = (Titulo*)malloc(sizeof(Titulo));
            *novo = temp;
            novo->next = head; // Insere no início para simplificar
            head = novo;
        }
        fclose(fTitulos);
    }

    // 2. Carregar Pedidos de Avença (Fila)
    FILE *fPedidos = fopen("pedidos.bin", "rb");
    if (fPedidos) {
        Pedido temp;
        while (fread(&temp, sizeof(Pedido), 1, fPedidos)) {
            // Reutiliza a lógica de submeter para reconstruir a fila
            submeterPedido(temp.matricula, temp.nome, temp.zona, temp.mes_ano);
            // Nota: Pode ser necessário ajustar o estado lido se for diferente de "Submetido"
        }
        fclose(fPedidos);
    }

    // 3. Carregar Avenças Ativas
    FILE *fAtivas = fopen("avencas_ativas.bin", "rb");
    if (fAtivas) {
        AvencaAtiva temp;
        while (fread(&temp, sizeof(AvencaAtiva), 1, fAtivas)) {
            AvencaAtiva* nova = (AvencaAtiva*)malloc(sizeof(AvencaAtiva));
            *nova = temp;
            nova->next = listaAvencasAtivas;
            listaAvencasAtivas = nova;
        }
        fclose(fAtivas);
    }
}