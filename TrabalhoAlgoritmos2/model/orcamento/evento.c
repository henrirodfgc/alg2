#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"
#include "../../controller/saida.h" 

void copiar_dados_evento(Evento *destino, const Evento *origem) {
    if (!destino || !origem) return;
    
    destino->codigo = origem->codigo;
    destino->codigo_cliente = origem->codigo_cliente;
    destino->quantidade_convidados = origem->quantidade_convidados;
    destino->valor_total = origem->valor_total;
    destino->status = origem->status;
    
    strncpy(destino->nome_evento, origem->nome_evento, sizeof(destino->nome_evento)-1);
    destino->nome_evento[sizeof(destino->nome_evento)-1] = '\0';
    strncpy(destino->data_inicio, origem->data_inicio, sizeof(destino->data_inicio)-1);
    destino->data_inicio[sizeof(destino->data_inicio)-1] = '\0';
    strncpy(destino->data_fim, origem->data_fim, sizeof(destino->data_fim)-1);
    destino->data_fim[sizeof(destino->data_fim)-1] = '\0';
}

NoEvento* adicionar_evento_na_lista(NoEvento* lista, Evento novo_evento) {
    NoEvento *novo_no = (NoEvento*) malloc(sizeof(NoEvento));
    if (novo_no == NULL) return lista;
    
    copiar_dados_evento(&(novo_no->dados), &novo_evento);
    novo_no->proximo = lista; 
    
    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/eventos.txt", "a"); 
        if (!file) file = fopen("../b_output/eventos.txt", "a");
        
        if (file) {
            fprintf(file, 
                "cod:%d,cli:%d,nome:%s,inicio:%s,fim:%s,qtd:%d,valor:%.2f,status:%d\n",
                novo_evento.codigo,
                novo_evento.codigo_cliente,
                novo_evento.nome_evento,
                novo_evento.data_inicio,
                novo_evento.data_fim,
                novo_evento.quantidade_convidados,
                novo_evento.valor_total,
                novo_evento.status
            );
            fclose(file);
        }
    }
    else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/eventos.bin", "ab"); 
        if (!file) file = fopen("../b_output/eventos.bin", "ab");

        if (file) {
            fwrite(&novo_evento, sizeof(Evento), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

Evento* buscar_evento_por_codigo(NoEvento* lista, int codigo) {
    NoEvento *atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo == codigo) return &(atual->dados);
        atual = atual->proximo;
    }
    return NULL;
}

NoEvento* carregar_eventos(NoEvento* lista) {
    if (lista != NULL) return lista;
    int tipo = verificar_tipo_saida();

    if (tipo == 1) { 
        FILE *file = fopen("b_output/eventos.txt", "r"); 
        if (!file) file = fopen("../b_output/eventos.txt", "r");
        if (!file) return lista;
        
        Evento e;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha, 
                "cod:%d,cli:%d,nome:%99[^,],inicio:%11[^,],fim:%11[^,],qtd:%d,valor:%f,status:%d",
                &e.codigo, &e.codigo_cliente, e.nome_evento, e.data_inicio,
                e.data_fim, &e.quantidade_convidados, &e.valor_total, &e.status) == 8) {
                    
                NoEvento *novo = (NoEvento*) malloc(sizeof(NoEvento));
                if (novo) {
                    copiar_dados_evento(&(novo->dados), &e);
                    novo->proximo = lista;
                    lista = novo;
                }
            }
        }
        fclose(file);
    }
    else if (tipo == 2) { 
        FILE *file = fopen("b_output/eventos.bin", "rb"); 
        if (!file) file = fopen("../b_output/eventos.bin", "rb");
        if (!file) return lista;

        Evento e;
        while (fread(&e, sizeof(Evento), 1, file) == 1) {
            NoEvento *novo = (NoEvento*) malloc(sizeof(NoEvento));
            if (novo) {
                copiar_dados_evento(&(novo->dados), &e);
                novo->proximo = lista;
                lista = novo;
            }
        }
        fclose(file);
    }
    return lista;
}

void desalocar_lista_eventos(NoEvento* lista) {
    NoEvento *atual = lista;
    while (atual != NULL) {
        NoEvento *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

void reescrever_arquivo_eventos(NoEvento* lista) {
    int tipo = verificar_tipo_saida();
    if (tipo == 3) return;

    if (tipo == 1) { 
        FILE *file = fopen("b_output/eventos.txt", "w"); 
        if (!file) file = fopen("../b_output/eventos.txt", "w"); 
        if (!file) return;

        NoEvento *atual = lista;
        while (atual != NULL) {
            fprintf(file, 
                "cod:%d,cli:%d,nome:%s,inicio:%s,fim:%s,qtd:%d,valor:%.2f,status:%d\n",
                atual->dados.codigo,
                atual->dados.codigo_cliente,
                atual->dados.nome_evento,
                atual->dados.data_inicio,
                atual->dados.data_fim,
                atual->dados.quantidade_convidados,
                atual->dados.valor_total,
                atual->dados.status 
            );
            atual = atual->proximo;
        }
        fclose(file);
    }
    else if (tipo == 2) {
        FILE *file = fopen("b_output/eventos.bin", "wb"); 
        if (!file) file = fopen("../b_output/eventos.bin", "wb"); 
        if (!file) return;

        NoEvento *atual = lista;
        while (atual != NULL) {
            fwrite(&(atual->dados), sizeof(Evento), 1, file);
            atual = atual->proximo;
        }
        fclose(file);
    }
}