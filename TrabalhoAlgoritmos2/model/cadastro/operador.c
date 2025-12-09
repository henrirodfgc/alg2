#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <errno.h>
#include <windows.h>
#include "operador.h"
#include "../../view/cadastro/operador_view.h"
#include "../../controller/saida.h"

void copiar_dados_operador(Operador *destino, const Operador *origem){
    if (!origem || !destino) return;
    destino->codigo = origem->codigo;
    strncpy(destino->nome, origem->nome, sizeof(destino->nome) - 1);
    destino->nome[sizeof(destino->nome) -1]= '\0';
    strncpy(destino->usuario, origem->usuario, sizeof(destino->usuario) - 1);
    destino->usuario[sizeof(destino->usuario) -1]= '\0';
    strncpy(destino->senha, origem->senha, sizeof(destino->senha) - 1);
    destino->senha[sizeof(destino->senha) -1]= '\0';
}

NoOperador* adicionar_operador_na_lista(NoOperador* lista, Operador novo_operador){
    NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));
    if(novo_no == NULL) return lista;

    novo_operador.status = 1;
    copiar_dados_operador(&(novo_no->dados), &novo_operador);
    novo_no->proximo = lista;

    if(verificar_tipo_saida() == 1){
        FILE *file = fopen("b_output/operador/operadores.txt", "a");
        if (!file) file = fopen("../b_output/operador/operadores.txt", "a");
        
        if (file != NULL){
            fprintf(file,
                "id:%d,nome:%s,usuario:%s,senha:%s,status:%d\n",
                novo_operador.codigo, novo_operador.nome, novo_operador.usuario, 
                novo_operador.senha, novo_operador.status);
            fclose(file);
        }
    }else if(verificar_tipo_saida() == 2){
        FILE *file = fopen("b_output/operador/operadores.bin", "ab");
        if (!file) file = fopen("../b_output/operador/operadores.bin", "ab");
        
        if (file != NULL){
            fwrite(&novo_operador, sizeof(Operador), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

void atualizar_operador_por_codigo(NoOperador* lista, int codigo_busca, const char* nome, const char* usuario, const char* senha){
    Operador *operador_existente = buscar_operador_por_codigo(lista, codigo_busca);
    if(operador_existente){
        strncpy(operador_existente->nome, nome, sizeof(operador_existente->nome) - 1);
        operador_existente->nome[sizeof(operador_existente->nome) -1]= '\0';
        strncpy(operador_existente->usuario, usuario, sizeof(operador_existente->usuario) - 1);
        operador_existente->usuario[sizeof(operador_existente->usuario) -1]= '\0';
        strncpy(operador_existente->senha, senha, sizeof(operador_existente->senha) - 1);
        operador_existente->senha[sizeof(operador_existente->senha) -1]= '\0';
    }
}

int deletar_operador_por_codigo(NoOperador* lista, int codigo_busca){
    if (verificar_tipo_saida() == 3){
        Operador *operador_existente = buscar_operador_por_codigo(lista, codigo_busca);
        if(operador_existente && operador_existente->status == 1){
            operador_existente->status = 0;
            return 1;
        }
    }
    return 0;
}
    
Operador* buscar_operador_por_codigo(NoOperador* lista, int codigo_busca){
    NoOperador *atual = lista;
    while(atual != NULL){
        if(atual->dados.codigo == codigo_busca && atual->dados.status == 1){
            return &(atual->dados);
        }
        atual = atual->proximo;
    }
    return NULL;
}

NoOperador* carregar_operadores(NoOperador* lista){
    if (lista != NULL) return lista;
    
    int tipo = verificar_tipo_saida();
    if (tipo == 1) { 
        FILE *file = fopen("b_output/operador/operadores.txt", "r");
        if (!file) file = fopen("../b_output/operador/operadores.txt", "r");
        if (!file) return lista;

        Operador op;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha,
                   "id:%d,nome:%49[^,],usuario:%59[^,],senha:%19[^,],status:%d",
                   &op.codigo, op.nome, op.usuario, op.senha, &op.status) == 5) {
                
                NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));
                if (novo_no != NULL) {
                    copiar_dados_operador(&(novo_no->dados), &op);
                    novo_no->dados.status = op.status;
                    novo_no->proximo = lista;
                    lista = novo_no;
                }
            }
        }
        fclose(file);
    }
    else if (tipo == 2) { 
        FILE *file = fopen("b_output/operador/operadores.bin", "rb");
        if (!file) file = fopen("../b_output/operador/operadores.bin", "rb");
        if (!file) return lista;

        Operador op;
        while (fread(&op, sizeof(Operador), 1, file) == 1) {
            NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));
            if (novo_no != NULL) {
                copiar_dados_operador(&(novo_no->dados), &op);
                novo_no->dados.status = op.status;
                novo_no->proximo = lista;
                lista = novo_no;
            }
        }
        fclose(file);
    }
    return lista;
}

void deslocar_lista_operador(NoOperador* lista){
    NoOperador *atual = lista;
    NoOperador *proximo_no;
    while (atual != NULL){
        proximo_no = atual -> proximo;
        free(atual);
        atual = proximo_no;
    }
}

void exibir_todos_operadores(NoOperador* lista){
    NoOperador *atual = lista;
    int cont = 0;
    while (atual != NULL){
        if (atual->dados.status == 1) {
            exibir_operador(&(atual->dados));
            cont++;
        }
        atual = atual -> proximo;
    }
    if (cont == 0) exibir_mensagem_operador("nenhum operador ativo.\n");
}