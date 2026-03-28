#include <stdio.h>
#include <string.h>
#include <time.h>
#include "titulos_avulsos.h"

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