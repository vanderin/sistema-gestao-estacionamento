#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Infracao
{
    char matricula[30];
    struct Infracao* next;
} Infracao;

Infracao* head_infracao = NULL;

// Criar infração
Infracao* criarInfracao(Infracao** head_infracao, char* matricula)
{
    Infracao* nova_infracao = (Infracao*)malloc(sizeof(Infracao));

    if (nova_infracao == NULL)
    {
        return NULL;
    }

    strcpy(nova_infracao->matricula, matricula);
    nova_infracao->next = NULL;

    return nova_infracao;
}

// Adicionar infração à linked-list das infrações
void adicionarInfracao(Infracao** head_infracao, char* matricula)
{
    Infracao* nova_infracao = criarInfracao(head_infracao, matricula);

    nova_infracao->next = *head_infracao;
    *head_infracao = nova_infracao;
}

// Listar cada nó da linked list das infrações
void listarInfracoes(Infracao** head_infracao)
{
    if (*head_infracao == NULL)
    {
        printf("Lista de infrações vazia.\n");
        return;
    }

    Infracao* current = *head_infracao;

    printf("\n");

    while (current != NULL)
    {
        printf("Matricula: %s\n", current->matricula);
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

        current = current->next;
    }
}

