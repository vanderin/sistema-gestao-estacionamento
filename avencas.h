//
// Created by Utilizador on 21/04/2026.
//
#ifndef AVENCAS_H
#define AVENCAS_H

// Estrutura para um Pedido de Avença (Fila) [cite: 30]
typedef struct Pedido {
    int id;
    char matricula[30];
    char nome[100];
    char zona[10];
    char mes_ano[10]; // Formato MM/AAAA [cite: 21]
    char estado[40];  // Submetido, Aprovado a aguardar pagamento, Rejeitado
    struct Pedido* next;
} Pedido;

typedef struct {
    Pedido* frente;
    Pedido* fim;
} FilaPedidos;

// Estrutura para Avença Ativa (Lista Ligada ou Vetor) [cite: 32]
typedef struct AvencaAtiva {
    int id;
    char matricula[30];
    char zona[10];
    char mes_ano[10];
    int pago; // 1 para pago, 0 para não [cite: 33]
    struct AvencaAtiva* next;
} AvencaAtiva;

// Globais para gestão (podem ser passadas por referência no main)
extern FilaPedidos filaPedidos;
extern AvencaAtiva* listaAvencasAtivas;

// Protótipos
void inicializarFila();
void submeterPedido(char* matricula, char* nome, char* zona, char* mes);
void processarProximoPedido(int aprovar); // 1 para Aprovar, 0 para Rejeitar
void pagarAvenca(char* matricula);
void listarPedidos();
void listarAvencasAtivas();

#endif