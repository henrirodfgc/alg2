#include <stdio.h>
#include <stdlib.h>
#include "evento_view.h"

int exibir_menu_eventos() {
    int op;
    printf("\n==== menu de eventos e orcamentos ====\n");
    printf("1 - criar novo orcamento\n");
    printf("2 - listar eventos\n");
    printf("3 - aprovar evento\n");
    printf("4 - finalizar evento e liberar estoque");
    printf("0 - voltar\n");
    printf("escolha: ");
    scanf("%d", &op);
    return op;
}

Evento ler_dados_evento() {
    Evento e;
    int ch;
    
    printf("\n--- novo orcamento ---\n");
    printf("codigo do evento: "); scanf("%d", &e.codigo);
    printf("codigo do cliente: "); scanf("%d", &e.codigo_cliente);
    
    while ((ch = getchar()) != '\n' && ch != EOF); 
    
    printf("nome do evento: "); 
    scanf("%99[^\n]", e.nome_evento);
    
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    printf("data inicio (dd/mm/aaaa): "); scanf("%11s", e.data_inicio);
    printf("data fim (dd/mm/aaaa): "); scanf("%11s", e.data_fim);
    printf("qtd convidados: "); scanf("%d", &e.quantidade_convidados);
    
    printf("valor total estimado (r$): "); scanf("%f", &e.valor_total);
    
    e.status = 0; 
    return e;
}

void exibir_evento(const Evento* e) {
    if(!e) return;
    printf("\n+-----------------------------+\n");
    printf("| cod: %d - %s\n", e->codigo, e->nome_evento);
    printf("| cliente id: %d\n", e->codigo_cliente);
    printf("| data: %s ate %s\n", e->data_inicio, e->data_fim);
    printf("| valor: r$ %.2f\n", e->valor_total);
    
    char* st;
    if(e->status == 0) st = "orcamento";
    else if(e->status == 1) st = "aprovado";
    else st = "outro";
    
    printf("| status: %s\n", st);
    printf("+-----------------------------+\n");
}

void exibir_mensagem_evento(const char* msg) {
    printf(">> %s\n", msg);
}

int ler_id_evento_view(const char* prompt) {
    int id;
    printf("%s: ", prompt);
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        return 0; 
    }
    while (getchar() != '\n');
    return id;
}

int confirmar_aprovacao_view() {
    int confirmar;
    printf("deseja aprovar? (1-sim, 0-nao): ");
    scanf("%d", &confirmar);
    while (getchar() != '\n');
    return confirmar;
}

void pausar_tela_evento() {
    printf("\npressione enter para continuar...");
    while (getchar() != '\n'); 
    getchar();
}