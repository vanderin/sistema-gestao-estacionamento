#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avencas.h"
#include "historico_sessao.h"

FilaPedidos filaPedidos = {NULL, NULL};

Pedido* listaPedidosPagamento = NULL;
AvencaAtiva* listaAvencasAtivas = NULL;

void inicializarFila() {
    filaPedidos.frente = NULL;
    filaPedidos.fim = NULL;
}

// Adiciona o pedido `a fila dos Pedidos
void adicionarPedido(FilaPedidos* fila, Pedido* pedido)
{   
    if (fila == NULL || pedido == NULL) return;

    pedido->next = NULL;

    if (fila->frente == NULL)
    {
        fila->frente = pedido;
        fila->fim = pedido;
        
        return;
    }

    fila->fim->next = pedido;
    fila->fim = pedido;
}

// Retira e apaga da memoria um pedido da fila dos Pedidos
void rejeitarPedido(FilaPedidos* fila)
{
    if (fila->frente == NULL)
    {
        fila->fim = NULL;
        
        return;
    }

    Pedido* del_pedido = fila->frente;

    fila->frente = fila->frente->next;
    if (fila->frente == NULL)
        fila->fim = NULL;
        
    free(del_pedido);
}

// Aprova o Pedido, ou seja, retira o pedido da fila de pedidos e move para a lista de pagamentos
void aprovarPedido(FilaPedidos* filaPedidos, Pedido** listaPedidosPagamento)
{
    Pedido* pedido = filaPedidos->frente;

    filaPedidos->frente = filaPedidos->frente->next;
    if (filaPedidos->frente == NULL)
        filaPedidos->fim = NULL;
    
    pedido->next = *listaPedidosPagamento;
    *listaPedidosPagamento = pedido;
}

// Processar pedido (Ler primeiro Pedido da Fila e decidir)
void processarProximoPedido(FilaPedidos* filaPedidos) {
    if (filaPedidos->frente == NULL) {
        printf("Não existem pedidos pendentes.\n");
        
        return;
    }

    int opcao = 0;

    Pedido* temp = filaPedidos->frente;

    printf("\n--- APROVAR/REJEITAR PEDIDO DE AVENÇA ---\n");
    printf("ID: %d\n", temp->id);
    printf("Matrícula: %s\n", temp->matricula);
    printf("Nome: %s\n", temp->nome);
    printf("Zona: %s\n", temp->zona);
    printf("Mes/Ano: %02d/%d\n\n", temp->mes, temp->ano);

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

        aprovarPedido(filaPedidos, &listaPedidosPagamento);

        strcpy(pedido_aprovado->estado, "Aprovado a aguardar pagamento");

        printf("Pedido %d aprovado. A aguardar pagamento para ativação.\n", pedido_aprovado->id);
        push("Pedido de avença aprovado."); // Faz push para a stack do historico/logs
        
    } else {
        rejeitarPedido(filaPedidos);
        printf("Pedido %d rejeitado. Eliminado do sistema.\n", temp->id);
        push("Pedido de avença rejeitado.");
    }
}

void criarPedido(char* matricula, char* nome, char* zona, int mes, int ano) {
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
    
    // Adicionar `a fila dos pedidos
    adicionarPedido(&filaPedidos, novo);

    // Log
    push("Novo pedido de avença submetido.");

    printf("Criado Pedido de Avença:\n");
    printf("\tMatrícula: %s\n", novo->matricula);
    printf("\tNome: %s\n", novo->nome);
    printf("\tZona: %s\n", novo->zona);
    printf("\tData: %02d/%d\n", novo->mes, novo->ano);
}

void listarPedidos() {
    Pedido* atual = filaPedidos.frente;

    printf("\n--- PEDIDOS DE AVENÇA ---\n");
    while (atual != NULL)
    {
        printf("ID: %d | Matrícula: %s | Nome: %s | Zona: %s | Estado: %s | Validade: %02d/%d\n",
            atual->id, atual->matricula, atual->nome, atual->zona, atual->estado, atual->mes, atual->ano);
            
            atual = atual->next;
    }
    printf("\n");
}
    
void listarPedidosPagamento() {
    Pedido* atual = listaPedidosPagamento;
        
    printf("\n--- PEDIDOS DE AVENÇA A AGUARDAR PAGAMENTO ---\n");
    while (atual != NULL)
    {
        printf("ID: %d | Matrícula: %s | Nome: %s | Zona: %s | Estado: %s | Validade: %02d/%d\n",
            atual->id, atual->matricula, atual->nome, atual->zona, atual->estado, atual->mes, atual->ano);

        atual = atual->next;
    }
    printf("\n");
}

void listarAvencasAtivas() {
    AvencaAtiva* atual = listaAvencasAtivas;

    printf("\n--- AVENÇAS ATIVAS ---\n");
    while (atual != NULL) 
    {
        printf("ID: %d | Matrícula: %s | Nome: %s | Zona: %s | Validade: %02d/%d\n",
               atual->id, atual->matricula, atual->nome, atual->zona, atual->mes, atual->ano);

        atual = atual->next;
    }
    printf("\n");
}

// Move o pedido da lista de pedidos a aguardar pagamento para a lista das avenças ativas
void adicionarAListaAvencas(AvencaAtiva* avenca)
{
    if (avenca == NULL) return;

    avenca->next = listaAvencasAtivas;
    listaAvencasAtivas = avenca;

    push("Pedido de avença ativado.");
}

// Procurar pedido a aguardar pagamento por matricula
Pedido* procurarPedidoPagamento(Pedido* listaPedidosPagamento, char* matricula)
{
    if (listaPedidosPagamento == NULL)
    {
        printf("Lista de pedidos a aguardar pagamento está vazia.\n");
        
        return NULL;
    }

    Pedido* atual = listaPedidosPagamento;

    while (atual != NULL)
    {
        if (strcmp(atual->matricula, matricula) == 0)
        {
            printf("Pedido a aguardar pagamento encontrado.\n");

            return atual;
        }

        atual = atual->next;
    }

    printf("Não foi encontrado nenhum pedido a aguardar pagamento para a matrícula %s.\n", matricula);
    return NULL;
}


// Efetuar pagamento de pedido a aguardar pagamento e converte-lo para Avença (Mover para Avenças Ativas)
void pagarAvenca(char* matricula) {
    Pedido* atual = listaPedidosPagamento;
    Pedido* anterior = NULL;
    float dinheiro_inserido;

    // Procura pedido por matrícula na lista de pagamentos, guardando o nó anterior.
    while (atual != NULL && strcmp(atual->matricula, matricula) != 0)
    {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL)
    {
        printf("Não foi encontrado nenhum pedido a aguardar pagamento para a matrícula %s\n", matricula);
        return;
    }
    
    do
    {
        printf("Efetue o pagamento da Avença (10 €): ");
        scanf("%f", &dinheiro_inserido);

        if (dinheiro_inserido < 10)
        {
            printf("Valor inserido insuficiente. Introduza novamente.\n");
        }
        else if (dinheiro_inserido > 10)
        {
            printf("Pagamento realizado com sucesso.\n");
            printf("Troco: %.2f €\n", dinheiro_inserido - 10);
        }
    }
    while (dinheiro_inserido < 10);

    // Criar Avença Ativa
    AvencaAtiva* nova = (AvencaAtiva*)malloc(sizeof(AvencaAtiva));
    if (nova == NULL)
    {
        printf("Erro ao ativar avença: memória insuficiente.\n");
        return;
    }

    nova->id = atual->id;
    strcpy(nova->matricula, atual->matricula);
    strcpy(nova->nome, atual->nome);
    strcpy(nova->zona, atual->zona);
    nova->mes = atual->mes;
    nova->ano = atual->ano;
    nova->next = NULL;
            
    // Remover da lista de pedidos
    if (anterior == NULL) listaPedidosPagamento = atual->next;
    else anterior->next = atual->next;
    
    free(atual);
    printf("Pagamento registado. Avença ativada para a matrícula %s (zona: %s).\n", nova->matricula, nova->zona);
    push("Pagamento de avença recebido.");
    
    // Inserir na lista de Ativas
    adicionarAListaAvencas(nova);
}