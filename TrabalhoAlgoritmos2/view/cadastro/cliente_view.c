#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/cliente.h"
#include "cliente_view.h"

//funcao auxiliar pra ler o id
int ler_id_para_operacao(const char* operacao) {
    int id;
    printf("digite o id do cliente para %s: ", operacao);
    
    //tenta ler o id. se falhar retorna -1
    if (scanf("%d", &id) != 1) { 
        //limpa o buffer se o cara digitar letra no lugar de numero
        while (getchar() != '\n'); 
        return -1; //retorna -1 pra indicar erro
    }
    
    //limpa o buffer do '\n' que sobrou pra n bugar o proximo scanf
    while (getchar() != '\n'); 
    
    return id; //retorna o id correto
}

//mostra um client com todos os campos bonitinho
void exibir_cliente(const Cliente* cliente) {
    if (!cliente) {
        printf("+--------------------------+\n");
        printf("| cliente inexistente!     |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("\n+---------------------------------+\n");
    printf("| id              :%d\n", cliente->id);
    printf("| nome            :%s\n", cliente->nome_cliente);
    printf("| razao social    :%s\n", cliente->nome_razao);
    printf("| idade           :%d\n", cliente->idade);
    printf("| endereco        :%s\n", cliente->endereco);
    printf("| cpf             :%s\n", cliente->cpf);
    printf("| cnpj            :%s\n", cliente->cnpj);
    printf("| email           :%s\n", cliente->email);
    printf("| telefone        :%s\n", cliente->telefone);
    printf("| nome do contato :%s\n", cliente->nome_contato);
    printf("| status (ativo)  :%d\n", cliente->status);
    printf("+---------------------------------+\n");
}

//desenha o menu e pega a escolha
int exibir_menu() {
    int opcao;
    printf("\n==== menu cliente ====\n");
    printf("1 - criar cliente\n");
    printf("2 - atualizar cliente\n");
    printf("3 - exibir cliente\n");
    printf("4 - deletar cliente\n");
    printf("5 - listar todos\n"); 
    printf("6 - reativar cliente\n");
    printf("7 - menu clientes inativos\n");
    printf("0 - sair\n");
    printf("escolha: ");
    scanf("%d", &opcao); //pega a escolha
    return opcao;
}

//lê todos os dados de um client pra criar um novo
Cliente ler_dados_cliente() {
    Cliente c;
    printf("id: "); scanf("%d", &c.id);
    while (getchar() != '\n'); //limpa buffer dps do int
    printf("nome (ou razao social): "); scanf(" %49[^\n]", c.nome_cliente); //%[] pra ler strings com espaco
    while (getchar() != '\n');
    printf("nome fantasia (ou razao social): "); scanf(" %99[^\n]", c.nome_razao);
    while (getchar() != '\n');
    printf("idade: "); scanf("%d", &c.idade);
    while (getchar() != '\n');
    printf("endereco: "); scanf(" %255[^\n]", c.endereco);
    while (getchar() != '\n');
    printf("cpf (11 digitos): "); scanf(" %11[^\n]", c.cpf); //%11[] limita os digitos
    while (getchar() != '\n');
    printf("cnpj (14 digitos): "); scanf(" %14[^\n]", c.cnpj); //%14[] limita os digitos
    while (getchar() != '\n');
    printf("email: "); scanf(" %49[^\n]", c.email);
    while (getchar() != '\n');
    printf("telefone: "); scanf(" %19[^\n]", c.telefone);
    while (getchar() != '\n');
    printf("nome do contato: "); scanf(" %49[^\n]", c.nome_contato);
    while (getchar() != '\n');
    c.status = 1; //define como ativo ao criar
    return c; //devolve a struct cheia
}

//lê os dados novos pra atualização
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, char* cpf, char* cnpj, char* telefone, char* nome_contato) {
    printf("novo nome (ou razao social): "); scanf(" %49[^\n]", nome_cliente);
    while (getchar() != '\n');
    printf("nova idade: "); scanf("%d", idade);
    while (getchar() != '\n');
    printf("novo endereco: "); scanf(" %255[^\n]", endereco);
    while (getchar() != '\n');
    printf("novo nome de razao: "); scanf(" %99[^\n]", nome_razao);
    while (getchar() != '\n');
    printf("novo email: "); scanf(" %49[^\n]", email);
    while (getchar() != '\n');
    printf("novo cpf (11 digitos): "); scanf(" %11[^\n]", cpf);
    while (getchar() != '\n');
    printf("novo cnpj (14 digitos): "); scanf(" %14[^\n]", cnpj);
    while (getchar() != '\n');
    printf("novo telefone: "); scanf(" %19[^\n]", telefone);
    while (getchar() != '\n');
    printf("novo nome do contato: "); scanf(" %49[^\n]", nome_contato);
    while (getchar() != '\n');
}

//função simples pra mostrar mensagem
void exibir_mensagem(const char* msg) {
    printf("%s\n", msg);
}

void exibir_numero(int num) {
    printf("%d", num);
}