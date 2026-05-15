#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "titulos_avulsos.h"
#include "historico_sessao.h"
#include "menu.h"

Titulo* head_titulos_avulsos = NULL;

void obterHoras(int horas, int minutos, Titulo* novo_titulo)
{
  time_t agora = time(NULL);
  struct tm tm_inicio;
  struct tm tm_fim;

  // Local time separa os valores (horas, minutos, segundos, etc...) e manda para um struct tm
  localtime_r(&agora, &tm_inicio);
  localtime_r(&agora, &novo_titulo->tm_fim);

  novo_titulo->tm_fim.tm_hour = tm_inicio.tm_hour + horas;
  novo_titulo->tm_fim.tm_min = tm_inicio.tm_min + minutos;

  // mktime() normaliza as horas. Por exemplo, ao somar 70 minutos a 12:50, o resultado vai ser 14:00 em vez de 12:120.
  if (mktime(&novo_titulo->tm_fim) == (time_t)-1) {
    printErro("Erro ao normalizar data/hora.\n");
    return;
  }

  printf("Tempo inserido: %02d:%02d:00\n", horas, minutos);
  //printf("Horas Inicio: %d:%d:00\n", tm_inicio.tm_hour, tm_inicio.tm_min);
  printf("Estacionamento válido até às: %02d:%02d:00", novo_titulo->tm_fim.tm_hour, novo_titulo->tm_fim.tm_min);
}

// Inserir valor e matricula
void pedirValorMatricula(char matricula[30], float* valor)
{
  printPrompt("Insira a matricula do veiculo: ");
  scanf("%s", matricula);

  while (*valor < 0.25)
    {
      printPrompt("Insira o valor a pagar (mínimo 0.25€): ");
      scanf("%f", valor);
    }  
}

// Criar titulo
Titulo* criarTitulo()
{
  static int current_id = 1;
  char matricula[30];
  float valor = 0;
  int horas, minutos, incrementos, minutos_total;
  int dia, mes, ano;
  
  pedirValorMatricula(matricula, &valor); 
  
  Titulo* novo_titulo = (Titulo*)malloc(sizeof(Titulo));

  if (novo_titulo == NULL)
  {
    printErro("ERRO: Falha ao criar novo Título.\n");
    return NULL;
  }

  // Criar id
  novo_titulo->id = current_id;
  current_id++;

  // Copiar matricula
  strcpy(novo_titulo->matricula, matricula);

  // Calcular tempo de estacionamento a partir do valor
  incrementos = valor / 0.25;
  minutos_total = incrementos * 15;
  horas = minutos_total / 60;
  minutos = minutos_total % 60;
  
  //printf("Tempo de estacionamento: %d minutos\n", tempo_estacionamento);
  
  // Obter hora de inicio e hora de fim
  obterHoras(horas, minutos, novo_titulo);

  // Obter data atual
  time_t agora = time(NULL);
  struct tm* tm_local = localtime(&agora);
  novo_titulo->dia = tm_local->tm_mday;
  novo_titulo->mes = tm_local->tm_mon + 1;
  novo_titulo->ano = tm_local->tm_year + 1900;

  // Proximo titulo
  novo_titulo->next = NULL;

  printf("\n");

  return novo_titulo;
}

// Inserir titulo na linked list
// endereço do endereço do primeiro elemento -> endereço do primeiro elemento -> primeiro elemento
//               head                        ->             *head             ->       **head
void inserirTitulo(Titulo** head)
{
  Titulo* novo_titulo = criarTitulo();

  // Se não existir primeiro endereço, ou seja, não existir primeiro elemento
  if (*head == NULL)
  {
    *head = novo_titulo;
    push("Novo título avulso criado.");
    return;
  }

  novo_titulo->next = *head;
  *head = novo_titulo;

  push("Novo título avulso criado.");
}

// Listar cada nó da linked list dos Titulos Avulsos
void listarTitulos()
{
  Titulo* current = head_titulos_avulsos;
  
  printf("\n--- TÍTULOS AVULSOS ---\n");

  while (current != NULL)
  {
    printf("Matrícula: %s | Válido até: %02d:%02d:00 %02d/%02d/%02d", current->matricula, current->tm_fim.tm_hour, current->tm_fim.tm_min, current->dia, current->mes, current->ano);
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    
    current = current->next;
  }

  printf("\n");
}

