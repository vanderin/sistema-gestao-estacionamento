#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infracoes.h"

Infracao* head_infracao = NULL;

// Criar infração
Infracao* criarInfracao(char* matricula, int dia, int mes, int ano, int horas, int minutos)
{
    Infracao* nova_infracao = (Infracao*)malloc(sizeof(Infracao));

    if (nova_infracao == NULL)
    {
        return NULL;
    }

    strcpy(nova_infracao->matricula, matricula);
    nova_infracao->dia = dia;
    nova_infracao->mes = mes;
    nova_infracao->ano = ano;
    nova_infracao->horas = horas;
    nova_infracao->minutos = minutos;
    nova_infracao->next = NULL;

    return nova_infracao;
}

// Adicionar infração à linked-list das infrações
void adicionarInfracao(char* matricula, int dia, int mes, int ano, int horas, int minutos)
{
    Infracao* nova_infracao = criarInfracao(matricula, dia, mes, ano, horas, minutos);

    if (nova_infracao == NULL)
    {
        return;
    }

    nova_infracao->next = head_infracao;
    head_infracao = nova_infracao;
}

// Listar cada nó da linked list das infrações
void listarInfracoes()
{
    Infracao* current = head_infracao;

    printf("\n--- INFRAÇÕES ---\n");

    while (current != NULL)
    {
        printf("Matricula: %s | Data: %02d/%02d/%02d | Hora: %02d:%02d:00", current->matricula, current->dia, current->mes, current->ano, current->horas, current->minutos);
        printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        
        current = current->next;
    }
}

