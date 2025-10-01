#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

// Cria e inicializa um cliente
Cliente* criar_cliente(int id, const char* nome_cliente, int idade, const char* nome_razao, const int* cpf, const int* cnpj, const char* endereco, const char* email) {
    Cliente* novo = (Cliente*) malloc(sizeof(Cliente));
    if (!novo) {
        return NULL; // erro de memória
    }
    novo->id = id;
    strncpy(novo->nome_cliente, nome_cliente, sizeof(novo->nome_cliente));
    novo->idade = idade;
    strncpy(novo->nome_razao, nome_razao, sizeof(novo->nome_razao)); 
    novo->cpf = cpf;
    novo->cnpj = cnpj;
    strncpy(novo->endereco, endereco, sizeof(novo->endereco));
    strncpy(novo->email, email, sizeof(novo->email));
    
    return novo;
}

// Atualiza os dados do cliente
void atualizar_cliente(Cliente* cliente, const char* nome, int idade, const char* nome_razao, int cpf, int cnpj, const char* endereco, const char* email) {
    if (!cliente) return;
    strncpy(cliente->nome_cliente, nome_cliente, sizeof(cliente->nome_cliente));
    strncpy(cliente->nome_razao, nome_razao, sizeof(cliente->nome_razao));
    cliente->idade = idade;
    cliente->cpf = cpf;
    cliente->cnpj = cnpj;
    strncpy(cliente->endereco, endereco, sizeof(cliente->endereco));
    strncpy(cliente->email, email, sizeof(cliente->email));   
}

// Remove o cliente (libera memória)
void deletar_cliente(Cliente* cliente) {
    if (cliente) free(cliente);
}

