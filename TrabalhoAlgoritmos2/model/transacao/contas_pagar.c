#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contas_pagar.h"
#include "../../controller/saida.h"

NoContaPagar* gerar_nova_conta_pagar(NoContaPagar* lista, int id_recurso, float valor) {
    NoContaPagar *novo_no = (NoContaPagar*) malloc(sizeof(NoContaPagar));
    if (novo_no == NULL) return lista;

    novo_no->dados.id = rand() % 10000 + 1;
    novo_no->dados.id_recurso_compra = id_recurso;
    novo_no->dados.valor_total = valor;
    novo_no->dados.status = 0; 
    strcpy(novo_no->dados.data_vencimento, "05/01/2026"); 

    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/financeiro/contas_pagar.txt", "a");
        if (!file) file = fopen("../b_output/financeiro/contas_pagar.txt", "a");
        
        if (file) {
            fprintf(file, "id:%d,rec:%d,val:%.2f,venc:%s,st:%d\n",
                novo_no->dados.id, id_recurso, valor, 
                novo_no->dados.data_vencimento, 0);
            fclose(file);
        }
    }
    else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/financeiro/contas_pagar.bin", "ab");
        if (!file) file = fopen("../b_output/financeiro/contas_pagar.bin", "ab");
        
        if (file) {
            fwrite(&(novo_no->dados), sizeof(ContaPagar), 1, file);
            fclose(file);
        }
    }
    
    return novo_no;
}

NoContaPagar* carregar_contas_pagar(NoContaPagar* lista) {
    if (lista != NULL) return lista;
    
    int tipo = verificar_tipo_saida();
    if (tipo == 1) { 
        FILE *file = fopen("b_output/financeiro/contas_pagar.txt", "r");
        if (!file) file = fopen("../b_output/financeiro/contas_pagar.txt", "r");
        if (!file) return lista;

        ContaPagar c;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha, "id:%d,rec:%d,val:%f,venc:%11[^,],st:%d",
                &c.id, &c.id_recurso_compra, &c.valor_total, 
                c.data_vencimento, &c.status) == 5) {
                
                NoContaPagar *novo = (NoContaPagar*) malloc(sizeof(NoContaPagar));
                if (novo) {
                    novo->dados = c;
                    novo->proximo = lista;
                    lista = novo;
                }
            }
        }
        fclose(file);
    }
    else if (tipo == 2) {
        FILE *file = fopen("b_output/financeiro/contas_pagar.bin", "rb");
        if (!file) file = fopen("../b_output/financeiro/contas_pagar.bin", "rb");
        if (!file) return lista;
        
        ContaPagar c;
        while (fread(&c, sizeof(ContaPagar), 1, file) == 1) {
            NoContaPagar *novo = (NoContaPagar*) malloc(sizeof(NoContaPagar));
            if (novo) {
                novo->dados = c;
                novo->proximo = lista;
                lista = novo;
            }
        }
        fclose(file);
    }
    return lista;
}

void desalocar_lista_contas_pagar(NoContaPagar* lista) {
    NoContaPagar *atual = lista;
    while (atual != NULL) {
        NoContaPagar *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}