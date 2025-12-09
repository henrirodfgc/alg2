#include <stdio.h>
#include <stdlib.h>
#include "item_orcamento_view.h"

int exibir_menu_itens() {
    int op;
    printf("\n--- gerenciar itens do evento ---\n");
    printf("1 - adicionar equipamento (estoque)\n");
    printf("2 - adicionar equipe (funcionarios)\n"); 
    printf("3 - adicionar servico (parceiros)\n");  
    printf("4 - ver itens adicionados\n");
    printf("0 - finalizar insercao de itens\n");
    printf("escolha: ");
    scanf("%d", &op);
    return op;
}

ItemOrcamento ler_dados_item_orcamento(int id_evento, int tipo) {
    ItemOrcamento item;
    item.id_evento = id_evento;
    item.tipo_item = tipo;
    
    if (tipo == 1) printf("digite o id do recurso/equipamento: ");
    else if (tipo == 2) printf("digite o id do funcionario (equipe): ");
    else if (tipo == 3) printf("digite o id do fornecedor/parceiro: ");
    
    scanf("%d", &item.id_estrangeiro);
    
    if (tipo == 2) printf("digite horas/dias trabalhados: ");
    else printf("digite a quantidade: ");
    
    scanf("%d", &item.quantidade);
    
    if (tipo == 3) {
        printf("digite o valor combinado deste servico (unitario): ");
        scanf("%f", &item.valor_unitario);
    }
    
    return item;
}

void exibir_lista_itens_evento(NoItemOrcamento* lista, int id_evento) {
    NoItemOrcamento *atual = lista;
    int encontrou = 0;
    
    printf("\n--- itens do evento %d ---\n", id_evento);
    while (atual != NULL) {
        if (atual->dados.id_evento == id_evento && atual->dados.status == 1) {
            char* tipo_str = "";
            if(atual->dados.tipo_item == 1) tipo_str = "Equip";
            else if(atual->dados.tipo_item == 2) tipo_str = "Equipe";
            else if(atual->dados.tipo_item == 3) tipo_str = "Servico";

            printf("[%s] ID Ref: %d | Qtd: %d | Unit: %.2f | Total: %.2f\n",
                tipo_str,
                atual->dados.id_estrangeiro,
                atual->dados.quantidade,
                atual->dados.valor_unitario,
                atual->dados.valor_total_item);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    
    if (!encontrou) printf("nenhum item adicionado neste evento.\n");
    printf("--------------------------\n");
}

void exibir_mensagem_item(const char* msg) {
    printf("%s\n", msg);
}

void exibir_mensagem_item_formatada(const char* formato, float valor) {
    printf(formato, valor);
    printf("\n");
}

void pausar_tela_itens() {
    printf("pressione enter...");
    while (getchar() != '\n'); 
    getchar();
}

void exibir_numero_item(int num) {
    printf("%d", num);
}