#include <stdio.h>
#include <string.h>
#include <time.h>
#include "titulos_avulsos.h"
#include "infracoes.h"

void pesquisarTitulo(Titulo** head)
{
  char matricula[30];
  time_t agora = time(NULL);
  struct tm hora_atual;

  // Local time separa os valores (horas, minutos, segundos, etc...) do epoch e manda cada um para um struct tm
  localtime_r(&agora, &hora_atual);
  
  printf("Insira a matricula: ");
  scanf("%s", matricula);

  Titulo* current = *head;

  while (current != NULL)
  {
    if (strcmp(matricula, current->matricula) == 0)
    {
      printf("Matricula encontrada!\n");

      if (hora_atual.tm_hour >= current->tm_fim.tm_hour || (hora_atual.tm_hour = current->tm_fim.tm_hour && hora_atual.tm_min > current->tm_fim.tm_min))
      {
        printf("Inválido - Infração Registada\n");
        return;
      }
      else
        printf("Válido por Título\n");
        return;
    }
    current = current->next;
  }

  printf("Matrícula %s não encontrada.\n", matricula);

}

// Pesquisa a infração atraves da matricula
// Se já existir uma infraçao com essa matricula, nao faz nada
// Se ainda nao existir uma infraçao com essa matricula, adiciona essa infraçao
void pesquisarInfracao(Infracao** head_infracao)
{
  Infracao* current = *head_infracao;
  char matricula[30];

    printf("Inserir matricula: ");
    scanf("%29s", matricula);

    // Se a matricula for encontrada nas infraçoes, nao faz nada
    while (current != NULL)
    {
        if (strcmp(matricula, current->matricula) == 0)
        {
            printf("Infração Repetida no Mesmo Dia\n");
            return;
        }
        
        current = current->next;
    }
    
    printf("Infração Não Repetida\n");
    
    // Adiciona infraçao caso matricula nao for encontrada nas infraçoes
    adicionarInfracao(head_infracao, matricula);
    printf("Infração adicionada\n");
}