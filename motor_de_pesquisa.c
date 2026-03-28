#include <stdio.h>
#include <string.h>
#include <time.h>
#include "titulos_avulsos.h"
#include "infracoes.h"

int pesquisarTitulo(Titulo** head, char* matricula)
{
  time_t agora = time(NULL);
  struct tm hora_atual;

  // Local time separa os valores (horas, minutos, segundos, etc...) do epoch e manda cada um para um struct tm
  localtime_r(&agora, &hora_atual);

  Titulo* current = *head;

  while (current != NULL)
  {
    if (strcmp(matricula, current->matricula) == 0)
    {
      printf("Matricula encontrada!\n");

      // Titulo invalido (hora do fim ultrapassada)
      if (hora_atual.tm_hour >= current->tm_fim.tm_hour || (hora_atual.tm_hour = current->tm_fim.tm_hour && hora_atual.tm_min > current->tm_fim.tm_min))
      {
        return -1;
      }

      // Titulo valido
      else
        return 1;
    }
    current = current->next;
  }

  printf("Matrícula %s não encontrada.\n", matricula);

}


int pesquisarInfracao(Infracao** head_infracao, char* matricula)
{
  Infracao* current = *head_infracao;

    // Se a matricula for encontrada nas infraçoes, retornar 1
    while (current != NULL)
    {
        if (strcmp(matricula, current->matricula) == 0)
        {
            return 1;
        }
        
        current = current->next;
    }

    // Caso nao tenha sido encontrada, retornar -1
    return -1;
}

void fiscalizar()
{
  char matricula[30];

  printf("Introduza a matricula: ");
  scanf("%s", matricula);

  // Pesquisa titulo avulso
  if (pesquisarTitulo(&head, matricula) == 1)
  {
    printf("Válido por Título\n");
    return;
  }
  
  // Pesquisa avença
  // PARTE DO GIL
  
  // Pesquisa infraçao
  if (pesquisarInfracao(&head_infracao, matricula) == 1)
  {
    printf("Infração Registada no Mesmo Dia\n");
    return;
  }

  adicionarInfracao(&head_infracao, matricula);
  printf("Inválido - Infração Registada\n");
}