#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "historico_permanente.h"
#include "titulos_avulsos.h"
#include "infracoes.h"
#include "avencas.h"
#include "menu.h"

int pesquisarTitulo(Titulo** head_titulos_avulsos, char* matricula, int horas, int minutos, int dia, int mes, int ano)
{
  /*
  time_t agora = time(NULL);
  struct tm hora_atual;
  
  // Local time separa os valores (horas, minutos, segundos, etc...) do epoch e manda cada um para um campo
  // do struct tm
  localtime_r(&agora, &hora_atual);
  */

  Titulo* current = *head_titulos_avulsos;

  printf("A Procurar na Lista de Títulos Avulsos...\n");
  sleep(3);

  // Percorre a lista dos Titulos Avulsos
  while (current != NULL)
  {
    if (strcmp(matricula, current->matricula) == 0)
    {
      printf("Matrícula Encontrada. A Verificar a Validade para as %02d:%02d de %02d/%02d/%02d...\n", horas, minutos, dia, mes, ano);
      sleep(3);
      
       // Verifica se à hora e data introduzidas, o veículo está a cometer uma infração (Titulo expirado)
       if (ano != current->ano || mes != current->mes || dia != current->dia || horas > current->tm_fim.tm_hour || (horas == current->tm_fim.tm_hour && minutos > current->tm_fim.tm_min))
       {
         printf("Título Inválido.\n");
         return -1;
        }
        
        
        // Titulo valido
        else
          return 1;
      }
      
      current = current->next;
    }
    
    return -1;
  }
  
  
  int pesquisarInfracao(char* matricula, int dia, int mes, int ano)
  {
    Infracao* current = head_infracao;
    
    printf("A Procurar na Lista de Infrações...\n");
    sleep(3);

    // Se a matricula for encontrada nas infraçoes, retornar 1
    while (current != NULL)
    {
      if ( (strcmp(matricula, current->matricula) == 0) && (ano == current->ano) && (mes == current->mes) && (dia == current->dia) )
      {
        return 1;
      }
      
      current = current->next;
    }
    
    // Caso nao tenha sido encontrada, retornar -1
    return -1;
  }


int pesquisarAvenca(AvencaAtiva* head_avencas, char* matricula, char* zona, int ano, int mes) {
  AvencaAtiva* atual = head_avencas;

  printf("A Procurar na Lista de Avenças...\n");
  sleep(3);

  while (atual != NULL) {
    if (strcmp(atual->matricula, matricula) == 0) // Avença encontrada
    {
      if (strcmp(atual->zona, zona) == 0 && atual->ano == ano && atual->mes == mes) return 1; // Avença válida
      
      return -1; // Avença encontrada não é válida
    }

    atual = atual->next;
  }

  return -1; // Nenhuma avença válida encontrada
}


void fiscalizar()
{
  char matricula[30], zona[10];
  int ano, mes, dia, horas, minutos;

  printPrompt("Introduza a Matricula: ");
  scanf("%s", matricula);
  
  printPrompt("Introduza a Zona: ");
  scanf("%s", zona);
  
  printPrompt("Introduza o Dia (MM): ");
  scanf("%d", &dia);
  printPrompt("Introduza o Mês (MM): ");
  scanf("%d", &mes);
  printPrompt("Introduza o Ano (AAAA): ");
  scanf("%d", &ano);

  printPrompt("Insira a hora (HH): ");
  scanf("%d", &horas);
  printPrompt("Insira os minutos (MM): ");
  scanf("%d", &minutos);

  // Pesquisa titulo avulso
  if (pesquisarTitulo(&head_titulos_avulsos, matricula, horas, minutos, dia, mes, ano) == 1)
  {
    printf("Válido por Título.\n");
    return;
  }
  
  // Pesquisa avença
  if (pesquisarAvenca(listaAvencasAtivas, matricula, zona, ano, mes) == 1) {
    printf("Válido por Avença.\n");
    return;
  }

  // Pesquisa infraçao
  if (pesquisarInfracao(matricula, dia, mes, ano) == 1)
  {
    printf("Infração Registada no Mesmo Dia.\n");
    return;
  }

  adicionarInfracao(matricula, dia, mes, ano, horas, minutos);
  
  printf("Inválido - Infração Registada.\n");
  registarNoHistoricoTXT("Infração registada.");
}