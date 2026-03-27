void registarHistoricoTitulo(char *matricula, float valor, struct tm inicio, struct tm fim) {
    FILE *f = fopen("historico.txt", "a");
    if (f == NULL) {
        printf("Erro ao abrir historico.txt\n");
        return;
    }

    fprintf(f,
        "Pagamento Parquímetro | Matrícula: %s | Valor: %.2f€ | Início: %02d/%02d/%04d %02d:%02d | Fim: %02d/%02d/%04d %02d:%02d\n",
        matricula, valor,
        inicio.tm_mday, inicio.tm_mon + 1, inicio.tm_year + 1900, inicio.tm_hour, inicio.tm_min,
        fim.tm_mday, fim.tm_mon + 1, fim.tm_year + 1900, fim.tm_hour, fim.tm_min
    );

    fclose(f);
}
//
// Created by Utilizador on 27/03/2026.
//