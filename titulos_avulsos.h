#ifndef TITULOS_AVULSOS_H
#define TITULOS_AVULSOS_H
#include <time.h>

typedef struct Titulo
{
  int id;
  char matricula[30];
  float valor;
  struct tm tm_fim; // Struct do tipo tm que armazena a hora do fim
  struct Titulo* next;
} Titulo;

extern Titulo* head;

void pedirValorMatricula(char matricula[30], float* valor);
Titulo* criarTitulo();
Titulo* inserirTitulo(Titulo** head);
void listarTitulos(Titulo** head);
void obterHoras();


#endif
