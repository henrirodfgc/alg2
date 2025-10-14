#ifndef CLIENTE_H
#define CLIENTE_H

// =============================================
// ESTRUTURAS DE DADOS (MODEL)
// =============================================

typedef struct {
    int id;
    char nome_cliente[50];
    char nome_razao[100];
    int idade;
    char endereco[256];
    char cpf[12];
    char cnpj[15];
    char email[50];
    
    //coloquei esses dois q tavam faltando
    char telefone[20];
    char nome_contato[50];
} Cliente;

//mudei pro do cliente pro nó pra dar pra ter mais de 1 cliente ao msm tempo (lista ligada)
typedef struct NoCliente {
    Cliente dados;              // Contém a struct Cliente (os dados do registro)
    struct NoCliente *proximo;  // Ponteiro para o próximo registro/nó da lista
} NoCliente;


// =============================================
//mudança: as funçoes mexem no ponteiro do nó agr
// =============================================

//cria o nó na memória, copia os dados e retorna a nova cabeça da lista (head)
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente);

//atualiza os dados de um cliente existente na lista pelo id
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato);

//remove o nó da lista e retorna a nova cabeça (head), liberando a memória do q foi removido
NoCliente* deletar_cliente_por_id(NoCliente* lista, int id_busca);

//procura um cliente pelo id e retorna o ponteiro para a struct Cliente dentro do nó
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca);

//função essencial: libera a memória de TODOS os nós da lista p evitar memory leak
//memory leak é basicamente qnd vc aloca um espaço na ram com malloc e nao libera ele quando n ta mais sendo usado, pra isso serve o free
void desalocar_lista_clientes(NoCliente* lista); 

//nova opçao do menu: exibe todos os clientes na lista
void exibir_todos_clientes(NoCliente* lista); 

//funçao pra exibir os cliente da lista
void exibir_todos_clientes(NoCliente* lista); 

#endif