#include <stdio.h>
#include <string.h>
#include <time.h>

#include "historico_permanente.h"
#include "titulos_avulsos.h"
#include "infracoes.h"
#include "avencas.h"

int pesquisarTitulo(Titulo** head_titulos_avulsos, char* matricula)
{
  /*
  time_t agora = time(NULL);
  struct tm hora_atual;
  
  // Local time separa os valores (horas, minutos, segundos, etc...) do epoch e manda cada um para um campo
  // do struct tm
  localtime_r(&agora, &hora_atual);
  */

  int horas, minutos;
 
  printf("Insira a hora (HH): ");
  scanf("%d", &horas);

  printf("Insira os minutos (MM): ");
  scanf("%d", &minutos);

  Titulo* current = *head_titulos_avulsos;

  printf("A procurar a matrícula nos Titulos Avulsos...\n")
  // Percorre a lista dos Titulos Avulsos
  while (current != NULL)
  {
    if (strcmp(matricula, current->matricula) == 0)
    {
      printf("Matricula encontrada!\nA verificar a validade para as %d:%d\n");
      
      // Titulo invalido (hora do fim ultrapassada)
      /*
      if (hora_atual.tm_hour >= current->tm_fim.tm_hour || (hora_atual.tm_hour == current->tm_fim.tm_hour && hora_atual.tm_min > current->tm_fim.tm_min))
      {
        return -1;
        }
        */
       
       // Titulo invalido (hora do fim ultrapassada)
       if (horas > current->tm_fim.tm_hour || (horas == current->tm_fim.tm_hour && minutos > current->tm_fim.tm_min))
       {
         printf("Titulo expirado\n");
         return -1;
        }
        
        
        // Titulo valido
        else
        {
          printf("Válido por Título\n");
          return 1;
        }
      }
      
      current = current->next;
    }
    
    printf("Matrícula %s não encontrada.\n", matricula);
    return -1;
  }
  
  
  int pesquisarInfracao(Infracao** head_infracao, char* matricula)
  {
    Infracao* current = *head_infracao;
    
    printf("A procurar a matrícula nas Infrações...\n")

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
    printf("Matrícula não encontrada.\n");
    return -1;
  }


int pesquisarAvenca(AvencaAtiva* head_avencas, char* matricula) {
  AvencaAtiva* atual = head_avencas;

  printf("A procurar a matrícula nas Avenças...\n")
  while (atual != NULL) {

    if (strcmp(atual->matricula, matricula) == 0) {
      return 1; // Avença encontrada e válida
    }

    atual = atual->next;
  }
  printf("Matrícula não encontrada.\n")
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