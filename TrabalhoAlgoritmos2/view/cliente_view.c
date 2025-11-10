#include <stdio.h>
#include <stdlib.h>
#include "../model/cliente.h"
#include "cliente_view.h"

// Função auxiliar pra ler o ID
int ler_id_para_operacao(const char* operacao) {
    int id;
    printf("Digite o ID do cliente para %s: ", operacao);
    id = scanf("%d", &id);
    /*
    if (scanf("%d", &id) != 0) {
        // Limpa o buffer se o cara digitar letra no lugar de numero
        while (getchar() != '\n'); 
        return -1; // Retorna -1 pra indicar erro
    }
    */
    return id;
}

// Mostra um client com todos os campos bonitinho
void exibir_cliente(const Cliente* cliente) {
    if (!cliente) {
        printf("+--------------------------+\n");
        printf("| Cliente inexistente!     |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("\n+---------------------------------+\n");
    printf("| ID              : %d\n", cliente->id);
    printf("| Nome            : %s\n", cliente->nome_cliente);
    printf("| Razao Social    : %s\n", cliente->nome_razao);
    printf("| Idade           : %d\n", cliente->idade);
    printf("| Endereco        : %s\n", cliente->endereco);
    printf("| CPF             : %s\n", cliente->cpf);
    printf("| CNPJ            : %s\n", cliente->cnpj);
    printf("| Email           : %s\n", cliente->email);
    printf("| Telefone        : %s\n", cliente->telefone);
    printf("| Nome do Contato : %s\n", cliente->nome_contato);
    printf("+---------------------------------+\n");
}

// Desenha o menu e pega a escolha
int exibir_menu() {
    int opcao;
    printf("\n==== MENU CLIENTE ====\n");
    printf("1 - Criar cliente\n");
    printf("2 - Atualizar cliente\n");
    printf("3 - Exibir cliente\n");
    printf("4 - Deletar cliente\n");
    printf("5 - Listar todos\n"); 
    printf("6 - Reativar cliente");
    printf("7 - Menu clientes inativos");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao); // Pega a escolha
    return opcao;
}

// Lê TODOS os dados de um client pra criar um novo
Cliente ler_dados_cliente() {
    Cliente c;
    printf("ID: "); scanf("%d", &c.id);
    printf("Nome (ou Razao Social): "); scanf(" %[^\n]", c.nome_cliente); // %[] pra ler strings com espaço
    printf("Nome Fantasia (ou Razao Social): "); scanf(" %[^\n]", c.nome_razao);
    printf("Idade: "); scanf("%d", &c.idade);
    printf("Endereco: "); scanf(" %[^\n]", c.endereco);
    printf("CPF (11 digitos): "); scanf(" %11[^\n]", c.cpf); // %11[] limita os digitos
    printf("CNPJ (14 digitos): "); scanf(" %14[^\n]", c.cnpj); // %14[] limita os digitos
    printf("Email: "); scanf(" %[^\n]", c.email);
    printf("Telefone: "); scanf(" %[^\n]", c.telefone);
    printf("Nome do Contato: "); scanf(" %[^\n]", c.nome_contato);
    return c; // Devolve a struct cheia
}

// Lê os dados novos pra atualização
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, char* cpf, char* cnpj, char* telefone, char* nome_contato) {
    printf("Novo nome (ou Razao Social): "); scanf(" %[^\n]", nome_cliente);
    printf("Nova idade: "); scanf("%d", idade);
    printf("Novo endereco: "); scanf(" %[^\n]", endereco);
    printf("Novo nome de razão: "); scanf(" %[^\n]", nome_razao);
    printf("Novo email: "); scanf(" %[^\n]", email);
    printf("Novo CPF (11 digitos): "); scanf(" %11[^\n]", cpf);
    printf("Novo CNPJ (14 digitos): "); scanf(" %14[^\n]", cnpj);
    printf("Novo telefone: "); scanf(" %[^\n]", telefone);
    printf("Novo Nome do Contato: "); scanf(" %[^\n]", nome_contato);
}

// Função simples pra mostrar mensagem
void exibir_mensagem(const char* msg) {
    printf("%s\n", msg);
}