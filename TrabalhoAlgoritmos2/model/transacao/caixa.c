#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caixa.h"
#include "../../controller/saida.h"

void obter_data_hoje(char* buffer) {
    strcpy(buffer, "06/12/2025");
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

//carrega o caixa para uma lista (pra view poder exibir)
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
    //binario seria similar
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