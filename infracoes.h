#ifndef INFRACOES_H
#define INFRACOES_H

typedef struct Infracao
{
	char matricula[30];
	struct Infracao* next;
} Infracao;

extern Infracao* head_infracao;

Infracao* criarInfracao(Infracao** head_infracao, char* matricula);
void adicionarInfracao(Infracao** head_infracao, char* matricula);
void listarInfracoes(Infracao** head_infracao);

#endif
