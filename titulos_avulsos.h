#ifndef TITULOS_AVULSOS_H
#define TITULOS_AVULSOS_H

typedef struct Titulo
{
  int id;
  char matricula[30];
  char inicio[9];
  char fim[9];
  float valor;
  struct Titulo* next;
} Titulo;

extern Titulo* head;

void pedirValorMatricula(char matricula[30], float* valor);
Titulo* criarTitulo();
Titulo* inserirTitulo(Titulo** head);
void listarTitulos(Titulo** head);


#endif
