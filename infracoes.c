#include <stdio.h>
#include <string.h>

typedef struct Infracao
{
    char matricula[30];
    struct Infracao next;
} Infracao;

int pesquisarInfracao(Infracao** head_infracao)
{
    Infracao* current = *head_infracao;
    char matricula[30];

    printf("Inserir matricula; ");
    scanf("%s", matricula);

    while (current != NULL)
    {
        if (strcmp(matricula, current->matricula) == 0)
        {
            printf("Infração Repetida no Mesmo Dia\n");
            return 1;
        }
        
        current = current->next;
    }
    
    printf("Infração Não Repetida\n");
    return -1;
}

void adicionarInfracao(Infracao** head_infracao)
{
    if (pesquisarInfracao(&head_infracao) == -1)
    {
        // ADICIONAR INFRAÇAO
    }
    else
    {
        // NAO FAZER NADA
    }
}