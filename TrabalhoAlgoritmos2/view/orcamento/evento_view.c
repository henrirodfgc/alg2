#include <stdio.h>
#include <stdlib.h>
#include "evento_view.h"

int exibir_menu_eventos() {
    int op;
    printf("\n==== MENU DE EVENTOS E ORCAMENTOS ====\n");
    printf("1 - Criar Novo Orcamento\n");
    printf("2 - Listar Eventos\n");
    printf("3 - Aprovar Evento\n"); 
    printf("0 - Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

Evento ler_dados_evento() {
    Evento e;
    int ch;
    
    printf("\n--- Novo Orcamento ---\n");
    printf("Codigo do Evento: "); scanf("%d", &e.codigo);
    printf("Codigo do Cliente: "); scanf("%d", &e.codigo_cliente);
    
    while ((ch = getchar()) != '\n' && ch != EOF); //limpa buffer
    
    printf("Nome do Evento: "); 
    scanf("%99[^\n]", e.nome_evento);
    
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    printf("Data Inicio (dd/mm/aaaa): "); scanf("%11s", e.data_inicio);
    printf("Data Fim (dd/mm/aaaa): "); scanf("%11s", e.data_fim);
    printf("Qtd Convidados: "); scanf("%d", &e.quantidade_convidados);
    printf("Valor Total Estimado (R$): "); scanf("%f", &e.valor_total);
    
    e.status = 0; //começa como orcamento (0)
    return e;
}

void exibir_evento(const Evento* e) {
    if(!e) return;
    printf("\n+-----------------------------+\n");
    printf("| Cod: %d - %s\n", e->codigo, e->nome_evento);
    printf("| Cliente ID: %d\n", e->codigo_cliente);
    printf("| Data: %s ate %s\n", e->data_inicio, e->data_fim);
    printf("| Valor: R$ %.2f\n", e->valor_total);
    
    char* st;
    if(e->status == 0) st = "Orcamento";
    else if(e->status == 1) st = "Aprovado";
    else st = "Outro";
    
    printf("| Status: %s\n", st);
    printf("+-----------------------------+\n");
}

void exibir_mensagem_evento(const char* msg) {
    printf(">> %s\n", msg);
}