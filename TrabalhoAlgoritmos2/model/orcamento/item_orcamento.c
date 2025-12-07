#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item_orcamento.h"
#include "../../controller/saida.h"

//copia dados com seguranca
void copiar_dados_item(ItemOrcamento *destino, const ItemOrcamento *origem) {
    if (!destino || !origem) return;
    *destino = *origem; 
}

//adiciona e salva
NoItemOrcamento* adicionar_item_na_lista(NoItemOrcamento* lista, ItemOrcamento novo_item) {
    NoItemOrcamento *novo_no = (NoItemOrcamento*) malloc(sizeof(NoItemOrcamento));
    if (novo_no == NULL) return lista;

    //calcula total do item antes de salvar
    novo_item.valor_total_item = novo_item.quantidade * novo_item.valor_unitario;
    novo_item.status = 1;

    copiar_dados_item(&(novo_no->dados), &novo_item);
    novo_no->proximo = lista;

    //persistencia txt
    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/itens_orcamento.txt", "a"); //com ../ se precisar
        if (!file) file = fopen("../b_output/itens_orcamento.txt", "a"); //tentativa com ../

        if (file) {
            //atualizado com tipo e id_estrangeiro
            fprintf(file, 
                "id:%d,evt:%d,tipo:%d,ref:%d,qtd:%d,unit:%.2f,tot:%.2f,st:%d\n",
                novo_item.id, novo_item.id_evento, 
                novo_item.tipo_item, novo_item.id_estrangeiro,
                novo_item.quantidade, novo_item.valor_unitario, 
                novo_item.valor_total_item, novo_item.status
            );
            fclose(file);
        }
    } 
    //persistencia bin
    else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/itens_orcamento.bin", "ab");
        if (!file) file = fopen("../b_output/itens_orcamento.bin", "ab");

        if (file) {
            fwrite(&novo_item, sizeof(ItemOrcamento), 1, file);
            fclose(file);
        }
    }

    return novo_no;
}

//carrega dados
NoItemOrcamento* carregar_itens_orcamento(NoItemOrcamento* lista) {
    if (lista != NULL) return lista;

    int tipo = verificar_tipo_saida();
    
    if (tipo == 1) { //txt
        FILE *file = fopen("b_output/itens_orcamento.txt", "r");
        if (!file) file = fopen("../b_output/itens_orcamento.txt", "r");
        if (!file) return lista;

        ItemOrcamento it;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            //atualizado leitura do tipo e ref
            if (sscanf(linha, 
                "id:%d,evt:%d,tipo:%d,ref:%d,qtd:%d,unit:%f,tot:%f,st:%d",
                &it.id, &it.id_evento, &it.tipo_item, &it.id_estrangeiro, 
                &it.quantidade, &it.valor_unitario, &it.valor_total_item, &it.status) == 8) {
                
                NoItemOrcamento *novo = (NoItemOrcamento*) malloc(sizeof(NoItemOrcamento));
                if (novo) {
                    copiar_dados_item(&(novo->dados), &it);
                    novo->proximo = lista;
                    lista = novo;
                }
            }
        }
        fclose(file);
    }
    else if (tipo == 2) { //bin
        FILE *file = fopen("b_output/itens_orcamento.bin", "rb");
        if (!file) file = fopen("../b_output/itens_orcamento.bin", "rb");
        if (!file) return lista;

        ItemOrcamento it;
        while (fread(&it, sizeof(ItemOrcamento), 1, file) == 1) {
            NoItemOrcamento *novo = (NoItemOrcamento*) malloc(sizeof(NoItemOrcamento));
            if (novo) {
                copiar_dados_item(&(novo->dados), &it);
                novo->proximo = lista;
                lista = novo;
            }
        }
        fclose(file);
    }
    return lista;
}

float calcular_total_evento(NoItemOrcamento* lista, int id_evento) {
    float total = 0.0;
    NoItemOrcamento *atual = lista;
    while (atual != NULL) {
        if (atual->dados.id_evento == id_evento && atual->dados.status == 1) {
            total += atual->dados.valor_total_item;
        }
        atual = atual->proximo;
    }
    return total;
}

void desalocar_lista_itens(NoItemOrcamento* lista) {
    NoItemOrcamento *atual = lista;
    while (atual != NULL) {
        NoItemOrcamento *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}