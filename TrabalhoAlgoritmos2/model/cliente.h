#ifndef CLIENTE_H
#define CLIENTE_H

// =============================================
// estruturas de dados (model)
// onde fica o molde dos dados
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
    char telefone[20];
    char nome_contato[50];
    int status; //campo do soft delete
} Cliente;

//o nó da lista ligada pra dar pra ter vários clients ao mesmo tempo
typedef struct NoCliente {
    Cliente dados;              //guarda os dados do client mesmo
    struct NoCliente *proximo;  //ponteiro pro proximo registro da lista
} NoCliente;


// =============================================
// funções de manipulação (crud)
// operações do model
// =============================================

//cria o nó copia os dados e retorna a nova cabeça da lista
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente);

//atualiza os dados de um client q já existe pelo id
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato);

//agora so muda o status pra 0 (soft delete)
void deletar_cliente_por_id_logico(NoCliente* lista, int id_busca);

//novo: muda o status de 0 pra 1
void restaurar_cliente_por_id(NoCliente* lista, int id_busca); 

//procura um client pelo id e retorna o ponteiro pra struct Cliente
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca);

//mt crítica: libera a memória de todos os nós da lista pra n dar memory leak
void desalocar_lista_clientes(NoCliente* lista); 

//função pra mostrar todos os clientes
void exibir_todos_clientes(NoCliente* lista); 

//função pra mostrar os clientes inativos também
void exibir_todos_clientes_e_inativos(NoCliente* lista);

#endif