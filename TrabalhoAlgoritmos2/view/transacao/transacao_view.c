#include <stdio.h>
#include <stdlib.h>
#include "transacao_view.h"

int exibir_menu_financeiro() {
    int opcao;
    printf("\n=== MODULO FINANCEIRO ===\n");
    printf("1 - Ver Contas a Receber (Clientes)\n");
    printf("2 - Ver Extrato do Caixa\n");
    printf("3 - Ver Contas a Pagar (Fornecedores)\n");
    printf("4 - Baixar Conta a Receber (Entrada $$)\n"); 
    printf("5 - Baixar Conta a Pagar (Saida $$)\n");     
    printf("0 - Voltar\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    return opcao;
}

void exibir_lista_contas_receber(NoContaReceber* lista) {
    printf("\n=== CONTAS A RECEBER ===\n");
    if (!lista) { printf("nenhuma conta registrada.\n"); return; }
    
    NoContaReceber* atual = lista;
    while(atual) {
        printf("ID: %d | Evento: %d | Cliente: %d | Valor: R$ %.2f | Status: %s\n",
            atual->dados.id, atual->dados.id_evento, atual->dados.id_cliente,
            atual->dados.valor_total, 
            (atual->dados.status == 1 ? "Pago" : "Pendente"));
        atual = atual->proximo;
    }
    printf("========================\n");
}

void exibir_extrato_caixa_view(NoCaixa* lista) {
    printf("\n=== EXTRATO DE CAIXA ===\n");
    if(!lista) { printf("nenhum lancamento no caixa.\n"); return; }
    
    printf("ENTRADA   SAIDA\n");
    NoCaixa* atual = lista;
    while(atual) {
        printf("%s | %s | %s | R$ %.2f | Saldo: %.2f\n",
            atual->dados.data, 
            (atual->dados.tipo == 1 ? ">>" : "  "),
            atual->dados.descricao,
            atual->dados.valor,
            atual->dados.saldo_final);
        atual = atual->proximo;
    }
    printf("========================\n");
}

void exibir_lista_contas_pagar(NoContaPagar* lista) {
    printf("\n=== CONTAS A PAGAR (Aquisicao Equipamentos) ===\n");
    if (!lista) { printf("nenhuma conta a pagar registrada.\n"); return; }
    
    NoContaPagar* atual = lista;
    while(atual) {
        printf("ID: %d | Ref. Equipamento ID: %d | Valor: R$ %.2f | Status: %s\n",
            atual->dados.id, atual->dados.id_recurso_compra,
            atual->dados.valor_total, 
            (atual->dados.status == 1 ? "Pago" : "Pendente"));
        atual = atual->proximo;
    }
    printf("===============================================\n");
}

void exibir_mensagem_transacao(const char* msg) {
    printf("%s\n", msg);
}