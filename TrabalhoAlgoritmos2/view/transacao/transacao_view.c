#include <stdio.h>
#include <stdlib.h>
#include "transacao_view.h"

int exibir_menu_financeiro() {
    int op;
    printf("\n=== MODULO FINANCEIRO ===\n");
    printf("1 - Ver Contas a Receber\n");
    printf("2 - Ver Extrato do Caixa\n");
    printf("3 - Ver Contas a Pagar\n");
    printf("0 - Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

void exibir_lista_contas_receber(NoContaReceber* lista) {
    NoContaReceber *atual = lista;
    printf("\n=== CONTAS A RECEBER ===\n");
    if (!atual) printf("nenhuma conta registrada.\n");
    
    while (atual != NULL) {
        printf("ID: %d | Evento: %d | Cliente: %d | Valor: R$ %.2f | Status: %s\n",
            atual->dados.id, atual->dados.id_evento, atual->dados.id_cliente,
            atual->dados.valor_total, (atual->dados.status ? "Pago" : "Pendente"));
        atual = atual->proximo;
    }
    printf("========================\n");
}

void exibir_extrato_caixa_view(NoCaixa* lista) {
    NoCaixa *atual = lista;
    printf("\n=== EXTRATO DE CAIXA ===\n");
    if (!atual) printf("nenhum lancamento no caixa.\n");
    
    while (atual != NULL) {
         printf("%s | %s | %s | R$ %.2f | Saldo: %.2f\n",
            atual->dados.data, 
            (atual->dados.tipo == 1 ? "ENTRADA" : "SAIDA"),
            atual->dados.descricao,
            atual->dados.valor,
            atual->dados.saldo_final);
        atual = atual->proximo;
    }
    printf("========================\n");
}

void exibir_mensagem_transacao(const char* msg) {
    printf(">> %s\n", msg);
}
void exibir_lista_contas_pagar(NoContaPagar* lista) {
    NoContaPagar *atual = lista;
    printf("\n=== CONTAS A PAGAR (Aquisicao Equipamentos) ===\n");
    if (!atual) printf("nenhuma conta a pagar registrada.\n");
    
    while (atual != NULL) {
        printf("ID: %d | Ref. Equipamento ID: %d | Valor: R$ %.2f | Status: %s\n",
            atual->dados.id, atual->dados.id_recurso_compra,
            atual->dados.valor_total, (atual->dados.status ? "Pago" : "Pendente"));
        atual = atual->proximo;
    }
    printf("===============================================\n");
}