#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operador.h"
#include "../../controller/saida.h"

void copiar_dados_operador(Operador *destino, const Operador *origem) {
    *destino = *origem;
}

NoOperador* adicionar_operador_na_lista(NoOperador* lista, Operador novo_operador) {
    NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));
    if(novo_no == NULL) return lista;
    novo_no->dados = novo_operador;
    novo_no->proximo = lista;
    
    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/operador/operadores.txt", "a");
        if (!file) file = fopen("../b_output/operador/operadores.txt", "a");
        if (file) {
            fprintf(file, "id:%d,nome:%s,usuario:%s,senha:%s,status:%d\n",
                    novo_operador.codigo, novo_operador.nome, 
                    novo_operador.usuario, novo_operador.senha, novo_operador.status);
            fclose(file);
        }
    } else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/operador/operadores.bin", "ab");
        if (!file) file = fopen("../b_output/operador/operadores.bin", "ab");
        if (file) {
            fwrite(&novo_operador, sizeof(Operador), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

void atualizar_operador_por_codigo(NoOperador* lista, int codigo, const char* nome, const char* usuario, const char* senha) {
    NoOperador* atual = lista;
    while(atual != NULL) {
        if(atual->dados.codigo == codigo && atual->dados.status == 1) {
            strcpy(atual->dados.nome, nome);
            strcpy(atual->dados.usuario, usuario);
            strcpy(atual->dados.senha, senha);
            break;
        }
        atual = atual->proximo;
    }

}

int deletar_operador_por_codigo(NoOperador* lista, int codigo) {
    NoOperador* atual = lista;
    while(atual != NULL) {
        if(atual->dados.codigo == codigo) {
            atual->dados.status = 0; 
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

Operador* buscar_operador_por_codigo(NoOperador* lista, int codigo) {
    NoOperador* atual = lista;
    while(atual != NULL) {
        if(atual->dados.codigo == codigo && atual->dados.status == 1) {
            return &(atual->dados);
        }
        atual = atual->proximo;
    }
    return NULL;
}

void desalocar_lista_operador(NoOperador* lista) {
    NoOperador* atual = lista;
    while(atual != NULL) {
        NoOperador* prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

NoOperador* carregar_operadores(NoOperador* lista) {
    if(lista != NULL) return lista;
    
    int tipo = verificar_tipo_saida();
    if(tipo == 1) {
        FILE *file = fopen("b_output/operador/operadores.txt", "r");
        if (!file) file = fopen("../b_output/operador/operadores.txt", "r");
        if(!file) return lista;
        
        Operador op;
        char linha[256];
        while(fgets(linha, sizeof(linha), file)) {
            if(sscanf(linha, "id:%d,nome:%49[^,],usuario:%59[^,],senha:%19[^,],status:%d",
               &op.codigo, op.nome, op.usuario, op.senha, &op.status) == 5) {
                   NoOperador* novo = (NoOperador*)malloc(sizeof(NoOperador));
                   novo->dados = op;
                   novo->proximo = lista;
                   lista = novo;
            }
        }
        fclose(file);
    } 
    return lista;
}