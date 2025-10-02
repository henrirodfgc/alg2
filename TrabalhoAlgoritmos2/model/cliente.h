#ifndef CLIENTE_H
#define CLIENTE_H

// =============================
// MODEL: representa os dados
// =============================

// Estrutura básica de Cliente (ESTA PARTE ESTÁ OK)
typedef struct {
    int id;
    char nome_cliente[50]; //nome do cliente
    char nome_razao[100]; //nome da empresa
    int idade;
    char endereco[256];
    int cpf[11]; //do cliente
    int cnpj[14]; // da empresa
    char email[50];
    // Aqui você pode expandir: adicionar CPF, email, endereço, telefone, etc.
} Cliente;

// Funções do modelo (CRUD)
// CORREÇÃO: Usar const char* para strings e const int* para arrays de CPF/CNPJ
Cliente* criar_cliente(int id, const char* nome_cliente, int idade, const char* nome_razao, const int* cpf, const int* cnpj, const char* endereco, const char* email);

// CORREÇÃO: Usar const char* para nome, nome_razao, endereco e email. Usar const int* para cpf/cnpj.
void atualizar_cliente(Cliente* cliente, const char* nome_cliente, int idade, const char* nome_razao, const int* cpf, const int* cnpj, const char* endereco, const char* email);

void deletar_cliente(Cliente* cliente);

#endif