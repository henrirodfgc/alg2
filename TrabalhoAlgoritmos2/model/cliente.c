#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

// Cria e inicializa um cliente
Cliente* criar_cliente(int id, const char* nome, int idade, const char* nome_razao, const int* cpf, const int* cnpj, char endereco, char email) {
    Cliente* novo = (Cliente*) malloc(sizeof(Cliente));
    if (!novo) {
        return NULL; // erro de memória
    }
    novo->id = id;
    strncpy(novo->nome_cliente, nome, sizeof(novo->nome_cliente));
    novo->idade = idade;
    return novo;
}

// Atualiza os dados do cliente
void atualizar_cliente(Cliente* cliente, const char* nome, int idade) {
    if (!cliente) return;
    strncpy(cliente->nome_cliente, nome, sizeof(cliente->nome_cliente));
    cliente->idade = idade;
}

// Remove o cliente (libera memória)
void deletar_cliente(Cliente* cliente) {
    if (cliente) free(cliente);
}

