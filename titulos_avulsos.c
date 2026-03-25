#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "titulos_avulsos.h"

Titulo* head = NULL;

// Inserir valor e matricula
void pedirValorMatricula(char matricula[30], float* valor)
{
  while (*valor < 1.00)
    {
      printf("Insira o valor a pagar (minimo 1.00€): ");
      scanf("%f", valor);
    }
  
  printf("Insira a matricula do veiculo: ");
  scanf("%s", matricula);
}

// Criar titulo
Titulo* criarTitulo()
{
  static int current_id = 1;
  int tempo_estacionamento;
  int vezes;
  char matricula[30];
  float valor = 0;
  
  pedirValorMatricula(matricula, &valor); 
  
  Titulo* novo_titulo = (Titulo*)malloc(sizeof(Titulo));

  // Criar id
  novo_titulo->id = current_id;
  current_id++;

  // Copiar matricula
  strcpy(novo_titulo->matricula, matricula);

  // Calcular tempo de estacionamento a partir do valor
  vezes = valor / 0.25;
  tempo_estacionamento = vezes * 15;
  printf("Tempo de estacionamento: %d minutos\n", tempo_estacionamento);
  
  // Criar hora de inicio

  // Criar hora de fim

  // Proximo titulo
  novo_titulo->next = NULL;

  return novo_titulo;
}

// Inserir titulo na linked list
// endereço do endereço do primeiro elemento -> endereço do primeiro elemento -> primeiro elemento
//               head                        ->             *head             ->       **head
Titulo* inserirTitulo(Titulo** head)
{
  Titulo* novo_titulo = criarTitulo();

  // Se não existir primeiro endereço, ou seja, não existir primeiro elemento
  if (*head == NULL)
  {
    *head = novo_titulo;
    return *head;
  }

  novo_titulo->next = *head;
  *head = novo_titulo;

  return *head;
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

  while (current != NULL)
  {
    printf("Matricula: %s\n", current->matricula);
    current = current->next;
  }
}

// Remover titulo
Titulo* removerTitulo(Titulo* head)
{
  
}
