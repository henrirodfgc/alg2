#ifndef CLIENTE_H
#define CLIENTE_H

// =============================================
// ESTRUTURAS DE DADOS (MODEL)
// Onde fica o molde dos dados
// =============================================

typedef struct {
    int id;
    char nome_cliente[50];
    char nome_razao[100];
    int idade;
    char endereco[256];
    char cpf[12]; // 11 digitos + \0
    char cnpj[15]; // 14 digitos + \0
    char email[50];
    
    // esses dois eu adicionei lembra
    char telefone[20];
    char nome_contato[50];
} Cliente;

// O nó da lista ligada pra dar pra ter vários clients ao mesmo tempo
typedef struct NoCliente {
    Cliente dados;              // Guarda os dados do client mesmo
    struct NoCliente *proximo;  // Ponteiro pro proximo registro da lista
} NoCliente;


// =============================================
// FUNÇÕES DE MANIPULAÇÃO (CRUD)
// Operações do Model
// =============================================

// cria o nó copia os dados e retorna a nova cabeça da lista
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente);

// atualiza os dados de um client q já existe pelo id
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato);

// remove o nó libera a memoria e retorna a nova cabeça da lista
NoCliente* deletar_cliente_por_id(NoCliente* lista, int id_busca);

// procura um client pelo id e retorna o ponteiro pra struct Cliente
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca);

// MT CRÍTICA: libera a memória de TODOS os nós da lista pra n dar memory leak
void desalocar_lista_clientes(NoCliente* lista); 

// função pra mostrar todos os clients
void exibir_todos_clientes(NoCliente* lista); 

#endif