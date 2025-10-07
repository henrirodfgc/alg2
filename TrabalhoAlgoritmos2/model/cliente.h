#ifndef CLIENTE_H
#define CLIENTE_H

// =============================
// MODEL: representa os dados
// =============================

typedef struct {
    int id;
    char nome_cliente[50]; //nome do cliente
    char nome_razao[100]; //nome da empresa
    int idade;
    char endereco[256];
    char cpf[12]; //do cliente
    char cnpj[15]; // da empresa
    char email[50];
    // Aqui você pode expandir: adicionar CPF, email, endereço, telefone, etc.
} Cliente;

// Funções do modelo (CRUD)
Cliente* criar_cliente(int id, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email);


void atualizar_cliente(Cliente* cliente, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email);

void deletar_cliente(Cliente* cliente);

#endif