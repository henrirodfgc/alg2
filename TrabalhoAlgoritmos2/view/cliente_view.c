#include <stdio.h>
#include "../model/cliente.h"
#include "cliente_view.h"

//Função auxiliar para leitura de ID 
int ler_id_para_operacao(const char* operacao) {
    int id;
    printf("Digite o ID do cliente para %s: ", operacao);
    if (scanf("%d", &id) != 1) {
        //Limpa o buffer em caso de entrada inválida
        while (getchar() != '\n'); 
        return -1; 
    }
    return id;
}

//Exibe um cliente com todos os campos
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
    printf("| Razão Social    : %s\n", cliente->nome_razao);
    printf("| Idade           : %d\n", cliente->idade);
    printf("| Endereco        : %s\n", cliente->endereco);
    printf("| CPF             : %s\n", cliente->cpf);
    printf("| CNPJ            : %s\n", cliente->cnpj);
    printf("| Email           : %s\n", cliente->email);
    printf("| Telefone        : %s\n", cliente->telefone);
    printf("| Nome do Contato : %s\n", cliente->nome_contato);
    printf("+---------------------------------+\n");
}

int exibir_menu() {
    int opcao;
    printf("\n==== MENU CLIENTE ====\n");
    printf("1 - Criar cliente\n");
    printf("2 - Atualizar cliente\n");
    printf("3 - Exibir cliente\n");
    printf("4 - Deletar cliente\n");
    printf("5 - Listar todos\n"); 
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    return opcao;
}

Cliente ler_dados_cliente() {
    Cliente c;
    printf("ID: "); scanf("%d", &c.id);
    printf("Nome (ou Razão Social): "); scanf(" %[^\n]", c.nome_cliente);
    printf("Nome Fantasia (ou Razão Social): "); scanf(" %[^\n]", c.nome_razao);
    printf("Idade: "); scanf("%d", &c.idade);
    printf("Endereco: "); scanf(" %[^\n]", c.endereco);
    printf("CPF (11 dígitos): "); scanf(" %11[^\n]", c.cpf);
    printf("CNPJ (14 dígitos): "); scanf(" %14[^\n]", c.cnpj);
    printf("Email: "); scanf(" %[^\n]", c.email);
    printf("Telefone: "); scanf(" %[^\n]", c.telefone);
    printf("Nome do Contato: "); scanf(" %[^\n]", c.nome_contato);
    return c;
}

//Lê todos os dados para atualização (exceto ID)
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, char* cpf, char* cnpj, char* telefone, char* nome_contato) {
    printf("Novo nome (ou Razão Social): "); scanf(" %[^\n]", nome_cliente);
    printf("Nova idade: "); scanf("%d", idade);
    printf("Novo endereço: "); scanf(" %[^\n]", endereco);
    printf("Novo nome de razão: "); scanf(" %[^\n]", nome_razao);
    printf("Novo email: "); scanf(" %[^\n]", email);
    printf("Novo CPF (11 dígitos): "); scanf(" %11[^\n]", cpf);
    printf("Novo CNPJ (14 dígitos): "); scanf(" %14[^\n]", cnpj);
    printf("Novo telefone: "); scanf(" %[^\n]", telefone);
    printf("Novo Nome do Contato: "); scanf(" %[^\n]", nome_contato);
}

void exibir_mensagem(const char* msg) {
    printf("%s\n", msg);
}