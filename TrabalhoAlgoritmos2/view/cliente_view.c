#include <stdio.h>
#include "cliente_view.h"

// void exibir_cliente(const Cliente* cliente) {
//     if (!cliente) {
//         printf("Cliente inexistente!\n");
//         return;
//     }
//     printf("ID: %d | Nome: %s | Idade: %d\n",
//            cliente->id, cliente->nome, cliente->idade);
// }


void exibir_cliente(const Cliente* cliente) {
    if (!cliente) {
        printf("+--------------------------+\n");
        printf("| Cliente inexistente!     |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("+--------------------------+\n");
    printf("| ID   : %d\n", cliente->id);
    printf("| Nome : %s\n", cliente->nome_cliente);
    printf("| Nome_empresa : %s\n", cliente->nome_razao);
    printf("| Idade: %d\n", cliente->idade);
    printf("| Endereco : %s\n", cliente->endereco);
    printf("| Cpf: %d\n", cliente->cpf);
    printf("| Cnpj: %d\n", cliente->cnpj);
    printf("| email : %s\n", cliente->email);
    printf("+--------------------------+\n");
}



int exibir_menu() {
    int opcao;
    printf("\n==== MENU CLIENTE ====\n");
    printf("1 - Criar cliente\n");
    printf("2 - Atualizar cliente\n");
    printf("3 - Exibir cliente\n");
    printf("4 - Deletar cliente\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    return opcao;
}

Cliente ler_dados_cliente() {
    Cliente c;
    printf("ID: "); scanf("%d", &c.id);
    printf("Nome: "); scanf(" %[^\n]", c.nome_cliente);
    printf("Nome Empresa: "); scanf("%[^\n]", c.nome_razao);
    printf("Idade: "); scanf("%d", &c.idade);
    printf("Endereco: "); scanf("%[^\n]", c.endereco);
    printf("cpf: "); scanf("%d", &c.cpf);
    printf("cnpj: "); scanf("%d", &c.cnpj);
    printf("email: "); scanf("%[^\n]", c.email);
    return c;  // retorna a struct preenchida
}

void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, int* cpf, int* cnpj) {
    printf("Novo nome: "); scanf(" %[^\n]", nome_cliente);
    printf("Nova idade: "); scanf("%d", idade);
    printf("Novo endereco: "); scanf(" %[^\n]", endereco);
    printf("Novo nome de razão: "); scanf(" %[^\n]", nome_razao);
    printf("Novo email: "); scanf(" %[^\n]", email);
    printf("Novo cpf: "); scanf("%d", cpf);
    printf("Novo cnpj: "); scanf("%d", cnpj);
}

void exibir_mensagem(const char* msg) {
    printf("%s\n", msg);
}
