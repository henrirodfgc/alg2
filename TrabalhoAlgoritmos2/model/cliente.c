#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

// Cria e inicializa um cliente
// Assinatura de acordo com o .h
Cliente* criar_cliente(int id, const char* nome_cliente, int idade, const char* nome_razao, const int* cpf, const int* cnpj, const char* endereco, const char* email) {
    Cliente* novo = (Cliente*) malloc(sizeof(Cliente));
    if (!novo) {
        return NULL; 
    }
    novo->id = id;
    
    
    strncpy(novo->nome_cliente, nome_cliente, sizeof(novo->nome_cliente) - 1);
    novo->nome_cliente[sizeof(novo->nome_cliente) - 1] = '\0';
    
    novo->idade = idade;
    
    strncpy(novo->nome_razao, nome_razao, sizeof(novo->nome_razao) - 1);
    novo->nome_razao[sizeof(novo->nome_razao) - 1] = '\0'; 
    
    
    memcpy(novo->cpf, cpf, sizeof(novo->cpf));
    memcpy(novo->cnpj, cnpj, sizeof(novo->cnpj));
    
    strncpy(novo->endereco, endereco, sizeof(novo->endereco) - 1);
    novo->endereco[sizeof(novo->endereco) - 1] = '\0';
    
    strncpy(novo->email, email, sizeof(novo->email) - 1);
    novo->email[sizeof(novo->email) - 1] = '\0';
    
    return novo;
}

// Atualiza os dados do cliente
// Assinatura de acordo com o .h
void atualizar_cliente(Cliente* cliente, const char* nome_cliente, int idade, const char* nome_razao, const int* cpf, const int* cnpj, const char* endereco, const char* email) {
    if (!cliente) return;
    
    
    strncpy(cliente->nome_cliente, nome_cliente, sizeof(cliente->nome_cliente) - 1);
    cliente->nome_cliente[sizeof(cliente->nome_cliente) - 1] = '\0';
    
    strncpy(cliente->nome_razao, nome_razao, sizeof(cliente->nome_razao) - 1);
    cliente->nome_razao[sizeof(cliente->nome_razao) - 1] = '\0';
    
    cliente->idade = idade;
    
    
    memcpy(cliente->cpf, cpf, sizeof(cliente->cpf));
    memcpy(cliente->cnpj, cnpj, sizeof(cliente->cnpj));
    
    strncpy(cliente->endereco, endereco, sizeof(cliente->endereco) - 1);
    cliente->endereco[sizeof(cliente->endereco) - 1] = '\0';
    
    strncpy(cliente->email, email, sizeof(cliente->email) - 1);
    cliente->email[sizeof(cliente->email) - 1] = '\0';  
}

// Remove o cliente (libera memória)
void deletar_cliente(Cliente* cliente) {
    if (cliente) free(cliente);
}