#include <stdio.h>
#include <string.h>
#include <time.h>

#include "historico_permanente.h"
#include "titulos_avulsos.h"
#include "infracoes.h"
#include "avencas.h"

int pesquisarTitulo(Titulo** head, char* matricula)
{
  time_t agora = time(NULL);
  struct tm hora_atual;

  // Local time separa os valores (horas, minutos, segundos, etc...) do epoch e manda cada um para um campo
  // do struct tm
  localtime_r(&agora, &hora_atual);

  Titulo* current = *head;

  while (current != NULL)
  {
    if (strcmp(matricula, current->matricula) == 0)
    {
      printf("Matricula encontrada!\n");

      // Titulo invalido (hora do fim ultrapassada)
      if (hora_atual.tm_hour >= current->tm_fim.tm_hour || (hora_atual.tm_hour == current->tm_fim.tm_hour && hora_atual.tm_min > current->tm_fim.tm_min))
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
  return -1;
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


int pesquisarAvenca(AvencaAtiva* head, char* matricula) {
  AvencaAtiva* atual = head;

  while (atual != NULL) {
    // Verifica se a matrícula coincide e se a avença está ativa (pago = 1)
    if (strcmp(atual->matricula, matricula) == 0) {
      return 1; // Avença encontrada e válida
    }
    atual = atual->next;
  }
  return -1; // Nenhuma avença válida encontrada
}


void fiscalizar()
{
  char matricula[30];

  printf("Introduza a matricula: ");
  scanf("%s", matricula);

  // Pesquisa titulo avulso
  if (pesquisarTitulo(&head_titulos_avulsos, matricula) == 1)
  {
    printf("Válido por Título\n");
    return;
  }
  
  // Pesquisa avença
  if (pesquisarAvenca(listaAvencasAtivas, matricula) == 1) {
    printf("Veículo com Avença de Morador Ativa.\n");
    return;
  }

  // Pesquisa infraçao
  if (pesquisarInfracao(&head_infracao, matricula) == 1)
  {
    printf("Infração Registada no Mesmo Dia\n");
    return;
  }

  adicionarInfracao(&head_infracao, matricula);
  registarNoHistoricoTXT("Infracao registrada.");
  printf("Inválido - Infração Registada\n");
}