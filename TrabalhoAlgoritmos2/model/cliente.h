#ifndef CLIENTE_H
#define CLIENTE_H

// =============================
// MODEL: representa os dados
// =============================

// Estrutura básica de Cliente
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
Cliente* criar_cliente(int id, const char* nome, int idade);
void atualizar_cliente(Cliente* cliente, const char* nome, int idade);
void deletar_cliente(Cliente* cliente);

#endif

