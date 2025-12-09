#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "caixa.h"
#include "../../controller/saida.h"

NoCaixa *listaCaixa = NULL;

long data_para_long(const char* data) {
    int d, m, a;
    sscanf(data, "%d/%d/%d", &d, &m, &a);
    return (a * 10000) + (m * 100) + d;
}

void obter_data_hoje(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

float obter_saldo_atual() {
    return 0.0; 
}

void lancar_no_caixa(float valor, int tipo, const char* descricao) {
    LancamentoCaixa lanc;
    lanc.id = rand() % 10000;
    obter_data_hoje(lanc.data);
    strncpy(lanc.descricao, descricao, 99);
    lanc.descricao[99] = '\0';
    lanc.valor = valor;
    lanc.tipo = tipo;
    
    float saldo_anterior = obter_saldo_atual(); 
    if(tipo == 1) lanc.saldo_final = saldo_anterior + valor;
    else lanc.saldo_final = saldo_anterior - valor;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/financeiro/caixa.txt", "a");
        if (!file) file = fopen("../b_output/financeiro/caixa.txt", "a");
        
        if (file) {
            fprintf(file, 
                "id:%d,data:%s,desc:%s,val:%.2f,tipo:%d,saldo:%.2f\n",
                lanc.id, lanc.data, lanc.descricao, 
                lanc.valor, lanc.tipo, lanc.saldo_final
            );
            fclose(file);
        }
    }
    else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/financeiro/caixa.bin", "ab");
        if (!file) file = fopen("../b_output/financeiro/caixa.bin", "ab");
        
        if (file) {
            fwrite(&lanc, sizeof(LancamentoCaixa), 1, file);
            fclose(file);
        }
    }
}

NoCaixa* carregar_extrato_caixa(NoCaixa* lista) {
    if (lista != NULL) return lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/financeiro/caixa.txt", "r");
        if (!file) file = fopen("../b_output/financeiro/caixa.txt", "r");
        if (!file) return lista;

        LancamentoCaixa lc;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha, "id:%d,data:%11[^,],desc:%99[^,],val:%f,tipo:%d,saldo:%f",
                &lc.id, lc.data, lc.descricao, &lc.valor, &lc.tipo, &lc.saldo_final) == 6) {
                
                NoCaixa *novo = (NoCaixa*) malloc(sizeof(NoCaixa));
                if (novo) {
                    novo->dados = lc;
                    novo->proximo = lista;
                    lista = novo;
                }
            }
        }
        fclose(file);
    }
    return lista;
}

void desalocar_lista_caixa(NoCaixa* lista) {
    NoCaixa *atual = lista;
    while (atual != NULL) {
        NoCaixa *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}
void exibir_extrato_caixa_filtrado(NoCaixa* lista, const char* data_inicio, const char* data_fim) {
    NoCaixa *atual = lista;
    long inicio = data_para_long(data_inicio);
    long fim = data_para_long(data_fim);
    int encontrou = 0;

    printf("\n=== EXTRATO DE CAIXA (%s a %s) ===\n", data_inicio, data_fim);
    
    while (atual != NULL) {
        long data_atual = data_para_long(atual->dados.data);
        
        if (data_atual >= inicio && data_atual <= fim) {
             printf("%s | %s | %s | R$ %.2f | Saldo: %.2f\n",
                atual->dados.data, 
                (atual->dados.tipo == 1 ? "ENTRADA" : "SAIDA"),
                atual->dados.descricao,
                atual->dados.valor,
                atual->dados.saldo_final);
             encontrou = 1;
        }
        atual = atual->proximo;
    }
    
    if (!encontrou) printf("nenhum lancamento neste periodo.\n");
    printf("==========================================\n");
}