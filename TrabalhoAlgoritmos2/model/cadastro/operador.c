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

    if(novo_no == NULL){
        exibir_mensagem_operador("ERRO: Falha ao alocar nó da lista");
        return lista;
    }

    copiar_dados_operador(&(novo_no->dados), &novo_operador);

    novo_no->proximo = lista;

    return novo_no;
}

Operador* buscar_operador_por_codigo(NoOperador* lista, int codigo_busca){
    NoOperador *atual = lista;

    while (atual != NULL){
        
        if (atual-> dados.codigo == codigo_busca)
        {
            return &(atual->dados);
        }
        
        atual = atual->proximo;
    }
    return NULL;
    
}

void atualizar_operador_por_codigo(NoOperador* lista, int codigo_busca, const char* nome, const char* usuario, const char* senha){

    Operador *operador_existente = buscar_operador_por_codigo(lista, codigo_busca);

    if (operador_existente != NULL)
    {
        strncpy(operador_existente->nome, nome, sizeof(operador_existente-> nome) -1);
        operador_existente->nome[sizeof(operador_existente->nome)-1] = '\0';

        strncpy(operador_existente->usuario, usuario, sizeof(operador_existente-> usuario) -1);
        operador_existente->usuario[sizeof(operador_existente->usuario)-1] = '\0';

        strncpy(operador_existente->senha, senha, sizeof(operador_existente-> senha) -1);
        operador_existente->senha[sizeof(operador_existente->senha)-1] = '\0';
    }
    
}

NoOperador* deletar_operador_por_codigo(NoOperador* lista, int codigo_busca){
    NoOperador *atual = lista;
    NoOperador *anterior = NULL;

    while (atual != NULL && atual->dados.codigo != codigo_busca)
    {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) return lista;

    if (anterior == NULL)
    {
        lista = atual->proximo;
    }else{
        anterior->proximo = atual-> proximo;
    }
    
    free(atual);
    return lista;
}
    
void deslocar_lista_operador(NoOperador* lista){

    NoOperador *atual = lista;
    NoOperador *proximo_no;

    while (atual != NULL)
    {
        proximo_no = atual -> proximo;
        free(atual);
        atual = proximo_no;
    }
    
}

void exibir_todos_operadores(NoOperador* lista){
    NoOperador *atual = lista;

    if (atual == NULL)
    {
        printf("+-----------------------+");
        printf("|Nunhum operador cadastrado|");
        printf("+-------------------------+");
        return;

    }

    printf("\n===LISTA DE OPERADORES CADASTRADOS========\n");

    while (atual !=NULL)
    {
        exibir_operador(&(atual->dados));
        atual = atual-> proximo;
    }
    
    printf("=============================================\n");
}

