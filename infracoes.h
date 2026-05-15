#ifndef INFRACOES_H
#define INFRACOES_H

typedef struct Infracao
{
	char matricula[30];
	int dia, mes, ano, horas, minutos;
	struct Infracao* next;
} Infracao;

extern Infracao* head_infracao;

Infracao* criarInfracao(char* matricula, int dia, int mes, int ano, int horas, int minutos);
void adicionarInfracao(char* matricula, int dia, int mes, int ano, int horas, int minutos);
void listarInfracoes();

#endif
