#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avencas.h"
#include "historico_sessao.h"

AvencaAtiva* listaAvencasAtivas = NULL;

void inicializarFila() {
    filaPedidos.frente = NULL;
    filaPedidos.fim = NULL;
    filaPedidosPagamento.frente = NULL;
    filaPedidosPagamento.fim = NULL;
}

void criarPedido(char* matricula, char* nome, char* zona, char* mes) {
    static int id_gerador = 1;
    Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
    
    if (novo == NULL)
    {
        printf("Erro ao criar novo pedido.\n");
        return;
    }

    novo->id = id_gerador++;
    strcpy(novo->matricula, matricula);
    strcpy(novo->nome, nome);
    strcpy(novo->zona, zona);
    novo->mes = mes;
    novo->ano = ano;
    strcpy(novo->estado, "Submetido");
    novo->next = NULL;

    if (filaPedidos.fim == NULL) {
        filaPedidos.frente = novo;
    } else {
        filaPedidos.fim->next = novo;
    }
    filaPedidos.fim = novo;

    push("Novo pedido de avença submetido."); // Registo na Pilha de Sessão
}

void listarPedidos() {
    Pedido* atual = filaPedidos.frente;
    printf("\n--- PEDIDOS DE AVENÇA ---\n");
    while (atual) {
        printf("ID: %d | Matrícula: %s | Nome: %s | Zona: %s | Estado: %s\n",
               atual->id, atual->matricula, atual->nome, atual->zona, atual->estado);
        atual = atual->next;
    }
}

void listarPedidosPagamento() {
    Pedido* atual = filaPedidosPagamento.frente;
    
    printf("\n--- PEDIDOS DE AVENÇA A AGUARDAR PAGAMENTO ---\n");
    while (atual) {
        printf("ID: %d | Matrícula: %s | Nome: %s | Zona: %s | Estado: %s\n",
               atual->id, atual->matricula, atual->nome, atual->zona, atual->estado);
        atual = atual->next;
    }
}

// EDITAR ISTO
void listarAvencasAtivas() {
    AvencaAtiva* atual = listaAvencasAtivas;
    printf("\n--- AVENÇAS ATIVAS ---\n");
    while (atual) {
        printf("ID: %d | Matrícula: %s | Zona: %s | Validade: %s\n",
               atual->id, atual->matricula, atual->zona, atual->mes_ano);
        atual = atual->next;
    }
}

// Adiciona o pedido a uma fila
void adicionarPedido(FilaPedidos* fila, Pedido* pedido)
{   
    if (fila->frente == NULL)
    {
        fila->frente = pedido;
        fila->fim = pedido;
        
        return;
    }

    fila->fim->next = pedido;
    fila->fim = pedido;
}

// Retira e apaga da memoria um pedido de uma fila
void rejeitarPedido(FilaPedidos* fila)
{
    if (fila->frente == NULL)
    {
        fila->fim = NULL;
        
        return NULL;
    }

    Pedido* del_pedido = fila->frente;

    fila->frente = fila->frente->next;
    if (fila->frente == NULL)
        fila->fim = NULL;
        
    free(del_pedido);
    }
    
// Aprova o Pedido: Retira o pedido de uma fila (filaPedidos) e move para outra fila (filaPedidosPagamento)
void aprovarPedido(FIlaPedidos* filaPedidos, FilaPedidos filaPedidosPagamento)
{
    Pedido* pedido = filaPedidos->frente;

    filaPedidos->frente = filaPedidos->frente->next;
    if (filaPedidos->frente == NULL)
        filaPedidos->fim = NULL;
    
    adicionarPedido(filaPedidosPagamento, pedido);
}

// Processar pedido (Ler primeiro Pedido da Fila e decidir)
void processarProximoPedido(FilaPedidos* filaPedidos) {
    if (filaPedidos.frente == NULL) {
        printf("Não existem pedidos pendentes.\n");
        
        return;
    }

    int opcao = 0;

    Pedido* temp = filaPedidos.frente;

    printf("Pedido de Avença:\n");
    printf("ID: %d\n", temp->id);
    printf("Matrícula: %s\n", temp->matricula);
    printf("Nome: %s\n", temp->nome);
    printf("Zona: %s\n", temp->zona);
    printf("Mes/Ano: %d/%d\n\n", temp->mes, temp->ano);

    do
    {
        printf("1: Aprovar\n2: Rejeitar\n>> ");
        scanf("%d", &opcao);
    
        if (opcao != 1 && opcao != 2)
        {
            printf("ERRO: Insira uma opção válida.\n");
        }
    }
    while(opcao != 1 && opcao != 2);
    
    if (opcao == 1) {
        Pedido* pedido_aprovado = filaPedidos->frente;

        aprovarPedido(filaPedidos, &filaPedidosPagamento)

        strcpy(pedido_aprovado->estado, "Aprovado a aguardar pagamento");

        printf("Pedido %d aprovado. Aguarda pagamento para ativação.\n", pedido_aprovado->id);
        push("Pedido de avença aprovado."); // Faz push para a stack do historico/logs
        
    } else {
        printf("Pedido %d rejeitado.\n", temp->id);
        push("Pedido de avença rejeitado.");
        rejeitarPedido(filaPedidos);
    }
}

// Registar pagamento e ativar (Mover para Avenças Ativas)
void pagarAvenca(char* matricula) {
    // Procura nos pedidos aprovados
    Pedido* atual = filaPedidosPagamento.frente;
    Pedido* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) 
        {
            // Criar Avença Ativa
            AvencaAtiva* nova = (AvencaAtiva*)malloc(sizeof(AvencaAtiva));
            nova->id = atual->id;
            strcpy(nova->matricula, atual->matricula);
            strcpy(nova->zona, atual->zona);
            strcpy(nova->mes_ano, atual->mes_ano);
            nova->pago = 1;
            // Inserir na lista de Ativas
            nova->next = listaAvencasAtivas;
            listaAvencasAtivas = nova;
            // Remover da fila de pedidos
            if (anterior == NULL) filaPedidos.frente = atual->next;
            else anterior->next = atual->next;
            if (atual == filaPedidos.fim) filaPedidos.fim = anterior;

            free(atual);
            printf("Pagamento registado. Avença ativada para a zona %s.\n", nova->zona);
            push("Pagamento de avença recebido.");
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    printf("Nenhum pedido aprovado encontrado para esta matrícula.\n");
}