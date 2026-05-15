#ifndef MENU_H
#define MENU_H

void limparTerminal();
void menuInicial();
void menuFiscal();
void menuCliente();

void printTitulo(const char *texto);
void printOpcao(const char *texto);
void printPrompt(const char *texto);
void printSaida(const char *texto);
void printAviso(const char *texto);
void printErro(const char *texto);

#endif
