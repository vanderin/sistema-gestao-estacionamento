#ifndef HISTORICO_SESSAO_H
#define HISTORICO_SESSAO_H


typedef struct NoPilha {
    char evento[150];
    struct NoPilha* next;
} NoPilha;


void push(char* mensagem);
void pop();
void listarSessao();
void limparPilha();

#endif