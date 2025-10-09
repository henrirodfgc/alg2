#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int id;
    char nome_cliente[50];
    char nome_razao[100];
    int idade;
    char endereco[256];
    char cpf[12];
    char cnpj[15];
    char email[50];
    char telefone[20];       
    char nome_contato[50];   
} Cliente;

//Nó da lista ligada
typedef struct NoCliente {
    Cliente dados;              //Armazena a struct Cliente
    struct NoCliente *proximo;  //Ponteiro para o próximo cliente na lista
} NoCliente;

NoCliente* criar_cliente(int id, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato);
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente);
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato);
NoCliente* deletar_cliente_por_id(NoCliente* lista, int id_busca);
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca);
void desalocar_lista_clientes(NoCliente* lista); //Para liberar a memória no final

#endif