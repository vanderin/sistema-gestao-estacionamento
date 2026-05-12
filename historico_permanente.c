#include <stdio.h>
#include <time.h>
#include "historico_permanente.h"

void registarNoHistoricoTXT(char *mensagem) {
    // Abre "a" para nunca apagar o passado
    FILE *f = fopen("historico.txt", "a");

    if (f == NULL) {
        printf("Erro ao abrir historico.txt para escrita.\n");
        return;
    }

    // Obtém a hora atual do sistema
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);

    // Formata a entrada: [DD/MM/AAAA HH:MM] Mensagem
    fprintf(f, "[%02d/%02d/%04d %02d:%02d] %s\n",
            t->tm_mday,
            t->tm_mon + 1,
            t->tm_year + 1900,
            t->tm_hour,
            t->tm_min,
            mensagem);

    fclose(f);
}