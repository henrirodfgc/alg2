#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contas_receber.h"
#include "caixa.h" 
#include "../../controller/saida.h"
#include <time.h>

NoContaReceber* gerar_nova_conta(NoContaReceber* lista, int id_evento, int id_cliente, float valor) {
    NoContaReceber *novo_no = (NoContaReceber*) malloc(sizeof(NoContaReceber));
    if (novo_no == NULL) return lista;

    novo_no->dados.id = rand() % 10000 + 1; 
    novo_no->dados.id_evento = id_evento;
    novo_no->dados.id_cliente = id_cliente;
    novo_no->dados.valor_total = valor;
    novo_no->dados.status = 0; 
    
    time_t agora = time(NULL);
    agora += (30 * 24 * 60 * 60); 
    struct tm *tm_venc = localtime(&agora);
    sprintf(novo_no->dados.data_vencimento, "%02d/%02d/%04d", 
            tm_venc->tm_mday, tm_venc->tm_mon + 1, tm_venc->tm_year + 1900);

    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/financeiro/contas_receber.txt", "a"); 
        if (!file) file = fopen("../b_output/financeiro/contas_receber.txt", "a");
        if (file) {
            fprintf(file, "id:%d,evt:%d,cli:%d,val:%.2f,venc:%s,st:%d\n",
                novo_no->dados.id, novo_no->dados.id_evento, 
                novo_no->dados.id_cliente, novo_no->dados.valor_total,
                novo_no->dados.data_vencimento, novo_no->dados.status);
            fclose(file);
        }
    } else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/financeiro/contas_receber.bin", "ab");
        if (!file) file = fopen("../b_output/financeiro/contas_receber.bin", "ab");
        if (file) {
            fwrite(&(novo_no->dados), sizeof(ContaReceber), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

NoContaReceber* carregar_contas_receber(NoContaReceber* lista) {
    if (lista != NULL) return lista;
    int tipo = verificar_tipo_saida();
    
    if (tipo == 1) { 
        FILE *file = fopen("b_output/financeiro/contas_receber.txt", "r");
        if (!file) file = fopen("../b_output/financeiro/contas_receber.txt", "r");
        if (!file) return lista;

        ContaReceber c;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha, "id:%d,evt:%d,cli:%d,val:%f,venc:%11[^,],st:%d",
                &c.id, &c.id_evento, &c.id_cliente, &c.valor_total,
                c.data_vencimento, &c.status) == 6) {
                NoContaReceber *novo = (NoContaReceber*) malloc(sizeof(NoContaReceber));
                if (novo) { novo->dados = c; novo->proximo = lista; lista = novo; }
            }
        }
        fclose(file);
    } else if (tipo == 2) { 
        FILE *file = fopen("b_output/financeiro/contas_receber.bin", "rb");
        if (!file) file = fopen("../b_output/financeiro/contas_receber.bin", "rb");
        if (!file) return lista;
        ContaReceber c;
        while (fread(&c, sizeof(ContaReceber), 1, file) == 1) {
            NoContaReceber *novo = (NoContaReceber*) malloc(sizeof(NoContaReceber));
            if (novo) { novo->dados = c; novo->proximo = lista; lista = novo; }
        }
        fclose(file);
    }
    return lista;
}

void reescrever_arquivo_receber(NoContaReceber* lista) {
    int tipo = verificar_tipo_saida();
    if (tipo == 1) {
        FILE *f = fopen("b_output/financeiro/contas_receber.txt", "w");
        if (!f) f = fopen("../b_output/financeiro/contas_receber.txt", "w");
        if (!f) return;
        NoContaReceber* atual = lista;
        while(atual) {
            fprintf(f, "id:%d,evt:%d,cli:%d,val:%.2f,venc:%s,st:%d\n",
                atual->dados.id, atual->dados.id_evento, atual->dados.id_cliente,
                atual->dados.valor_total, atual->dados.data_vencimento, atual->dados.status);
            atual = atual->proximo;
        }
        fclose(f);
    } else if (tipo == 2) {
        FILE *f = fopen("b_output/financeiro/contas_receber.bin", "wb");
        if (!f) f = fopen("../b_output/financeiro/contas_receber.bin", "wb");
        if (!f) return;
        NoContaReceber* atual = lista;
        while(atual) {
            fwrite(&(atual->dados), sizeof(ContaReceber), 1, f);
            atual = atual->proximo;
        }
        fclose(f);
    }
}

void baixar_conta_receber(NoContaReceber* lista, int id_conta) {
    NoContaReceber* atual = lista;
    while(atual != NULL) {
        if (atual->dados.id == id_conta) {
            if (atual->dados.status == 1) {
                printf("Erro: Conta %d ja esta paga!\n", id_conta);
                return;
            }
            // Baixa
            atual->dados.status = 1; 
            reescrever_arquivo_receber(lista);
            
            char desc[100];
            sprintf(desc, "Recebimento Conta ID %d (Evento %d)", id_conta, atual->dados.id_evento);
            lancar_no_caixa(atual->dados.valor_total, 1, desc);
            
            printf(">> Sucesso! Conta %d recebida e valor lancado no caixa.\n", id_conta);
            return;
        }
        atual = atual->proximo;
    }
    printf("Erro: Conta ID %d nao encontrada.\n", id_conta);
}

void desalocar_lista_contas(NoContaReceber* lista) {
    NoContaReceber *atual = lista;
    while (atual != NULL) {
        NoContaReceber *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}