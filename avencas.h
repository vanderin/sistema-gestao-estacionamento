#ifndef AVENCAS_H
#define AVENCAS_H

// Estrutura para um Pedido de Avença (Fila)
typedef struct Pedido {
    int id;
    char matricula[30];
    char nome[100];
    char zona[10];
    int mes;
    int ano; 
    char estado[40];  // Submetido, Aprovado a aguardar pagamento, Rejeitado
    struct Pedido* next;
} Pedido;

// Tanto serve para a fila dos Pedidos como para a fila dos Pedidos a aguardar pagamento (filaPedidosPagamento)
typedef struct FilaPedidos{
    Pedido* frente;
    Pedido* fim;
} FilaPedidos;

// Estrutura para Avença Ativa
typedef struct AvencaAtiva {
    int id;
    char matricula[30];
    char nome[100];
    char zona[10];
    int mes;
    int ano;
    struct AvencaAtiva* next;
} AvencaAtiva;

// Globais para gestão (podem ser passadas por referência no main)
extern FilaPedidos filaPedidos;
extern FilaPedidos filaPedidosPagamento;
extern AvencaAtiva* listaAvencasAtivas;

// Protótipos
void inicializarFila();
void criarPedido(char* matricula, char* nome, char* zona, int mes, int ano);
void processarProximoPedido(FilaPedidos* filaPedidos);
void pagarAvenca(char* matricula);
void listarPedidos();
void listarPedidosPagamento();
void listarAvencasAtivas();

#endif