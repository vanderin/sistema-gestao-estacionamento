#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "titulos_avulsos.h"

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
    printf("Erro ao normalizar data/hora.\n");
    return;
  }

  printf("Tempo inserido: %02d:%02d:00\n", horas, minutos);
  //printf("Horas Inicio: %d:%d:00\n", tm_inicio.tm_hour, tm_inicio.tm_min);
  printf("Estacionamento válido até às: %02d:%02d:00\n", novo_titulo->tm_fim.tm_hour, novo_titulo->tm_fim.tm_min);
}

// Inserir valor e matricula
void pedirValorMatricula(char matricula[30], float* valor)
{
  printf("Insira a matricula do veiculo: ");
  scanf("%s", matricula);

  while (*valor < 0.25)
    {
      printf("Insira o valor a pagar (mínimo 0.25€): ");
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
  
  pedirValorMatricula(matricula, &valor); 
  
  Titulo* novo_titulo = (Titulo*)malloc(sizeof(Titulo));

  if (novo_titulo == NULL)
  {
    printf("ERRO: Falha ao criar novo Título.\n");
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
    return;
  }

  novo_titulo->next = *head;
  *head = novo_titulo;
}

// Listar cada nó da linked list dos Titulos Avulsos
void listarTitulos(Titulo** head)
{
  if (*head == NULL)
  {
    printf("Lista de pedidos vazia.\n");
    return;
  }

  Titulo* current = *head;

  printf("\n");
  
  while (current != NULL)
  {
    printf("Matricula: %s\n", current->matricula);
    printf("Hora do fim: %d:%d:00\n", current->tm_fim.tm_hour, current->tm_fim.tm_min);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    
    current = current->next;
  }

  printf("\n");
}

