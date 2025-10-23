#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "../view/cliente_view.h"

//--- funções auxiliares ---
//copia tudo de uma struct cliente pra outra de forma segura
void copiar_dados(Cliente *destino, const Cliente *origem) {
    if (!origem || !destino) return; //se for null sai fora pra n dar bo
    
    destino->id = origem->id;
    destino->idade = origem->idade;
    destino->status = origem->status; //agora copia o status tbm!
    
    //cópia segura de todas as strings (strncpy é vida)
    strncpy(destino->nome_cliente, origem->nome_cliente, sizeof(destino->nome_cliente) - 1);
    destino->nome_cliente[sizeof(destino->nome_cliente) - 1] = '\0';
    strncpy(destino->nome_razao, origem->nome_razao, sizeof(destino->nome_razao) - 1);
    destino->nome_razao[sizeof(destino->nome_razao) - 1] = '\0';
    strncpy(destino->endereco, origem->endereco, sizeof(destino->endereco) - 1);
    destino->endereco[sizeof(destino->endereco) - 1] = '\0';
    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';
    strncpy(destino->cnpj, origem->cnpj, sizeof(destino->cnpj) - 1);
    destino->cnpj[sizeof(destino->cnpj) - 1] = '\0';
    strncpy(destino->email, origem->email, sizeof(destino->email) - 1);
    destino->email[sizeof(destino->email) - 1] = '\0';
    strncpy(destino->telefone, origem->telefone, sizeof(destino->telefone) - 1);
    destino->telefone[sizeof(destino->telefone) - 1] = '\0';
    strncpy(destino->nome_contato, origem->nome_contato, sizeof(destino->nome_contato) - 1);
    destino->nome_contato[sizeof(destino->nome_contato) - 1] = '\0';
}

//procura um client pelo id e retorna o ponteiro pra struct cliente independente do status
//essa é auxiliar pra exclusão/restauração e nao é exportada no .h
Cliente* buscar_cliente_qualquer_status(NoCliente* lista, int id_busca) {
    NoCliente *atual = lista;
    while (atual != NULL) {
        if (atual->dados.id == id_busca) { 
            return &(atual->dados); //achou, não importa o status
        }
        atual = atual->proximo;
    }
    return NULL; //não achou
}

//--- funções de manipulação de lista ligada (crud) ---
//cria um novo nó e põe ele no começo da lista (create)
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente) {
    NoCliente *novo_no = (NoCliente*) malloc(sizeof(NoCliente)); //pede memoria pro novo nó
    if (novo_no == NULL) {
        exibir_mensagem("erro: falha ao alocar nó da lista");
        return lista; 
    }
    
    //o cliente que a view le nao tem status, ent a gente seta ele pra 1 aqui (ativo)
    novo_cliente.status = 1; 

    //copia os dados pro espaço alocado
    copiar_dados(&(novo_no->dados), &novo_cliente);

    //o novo nó vira a cabeça da lista
    novo_no->proximo = lista;

    return novo_no; //devolve a nova cabeça
}

//procura um client pelo id e retorna o ponteiro pra struct cliente
//agora só retorna se o status for 1 (ativo)
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca) {
    NoCliente *atual = lista;
    //percorre a lista
    while (atual != NULL) {
        //checa se o id bate e se o status é 1
        if (atual->dados.id == id_busca && atual->dados.status == 1) { 
            return &(atual->dados); //achou e tá ativo
        }
        atual = atual->proximo;
    }
    return NULL; //não achou ou tá inativo
}

//muda o status pra 0 (soft delete)
void deletar_cliente_por_id_logico(NoCliente* lista, int id_busca) {
    //aqui a gente busca ele mesmo se tiver inativo pra n criar duplicidade na restauração
    Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca); 
    
    //se a busca encontrar o cliente, muda o status
    if (cliente_existente) { 
        cliente_existente->status = 0; //seta pra inativo/deletado
    }
}

//novo: muda o status de 0 pra 1 (restauração)
void restaurar_cliente_por_id(NoCliente* lista, int id_busca) {
    //aqui a gente busca ele com qualquer status, já que ele tá "escondido"
    Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca);
    
    //se encontrou e ele estava inativo, reativa
    if (cliente_existente && cliente_existente->status == 0) { 
        cliente_existente->status = 1; //seta pra ativo
    }
}

//atualiza os dados de um client q já existe pelo id
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato) {
    Cliente *cliente_existente = buscar_cliente_por_id(lista, id_busca);
    
    if (cliente_existente) {
        //o status continua 1, a gente só atualiza os outros campos
        cliente_existente->idade = idade;
        
        //atualiza os campos string com cópia segura (strncpy)
        strncpy(cliente_existente->nome_cliente, nome_cliente, sizeof(cliente_existente->nome_cliente) - 1);
        cliente_existente->nome_cliente[sizeof(cliente_existente->nome_cliente) - 1] = '\0';
        strncpy(cliente_existente->nome_razao, nome_razao, sizeof(cliente_existente->nome_razao) - 1);
        cliente_existente->nome_razao[sizeof(cliente_existente->nome_razao) - 1] = '\0';
        strncpy(cliente_existente->endereco, endereco, sizeof(cliente_existente->endereco) - 1);
        cliente_existente->endereco[sizeof(cliente_existente->endereco) - 1] = '\0';
        strncpy(cliente_existente->cpf, cpf, sizeof(cliente_existente->cpf) - 1);
        cliente_existente->cpf[sizeof(cliente_existente->cpf) - 1] = '\0';
        strncpy(cliente_existente->cnpj, cnpj, sizeof(cliente_existente->cnpj) - 1);
        cliente_existente->cnpj[sizeof(cliente_existente->cnpj) - 1] = '\0';
        strncpy(cliente_existente->email, email, sizeof(cliente_existente->email) - 1);
        cliente_existente->email[sizeof(cliente_existente->email) - 1] = '\0';
        strncpy(cliente_existente->telefone, telefone, sizeof(cliente_existente->telefone) - 1);
        cliente_existente->telefone[sizeof(cliente_existente->telefone) - 1] = '\0';
        strncpy(cliente_existente->nome_contato, nome_contato, sizeof(cliente_existente->nome_contato) - 1);
        cliente_existente->nome_contato[sizeof(cliente_existente->nome_contato) - 1] = '\0';
    }
}


//função essencial: libera a memória
void desalocar_lista_clientes(NoCliente* lista) {
    NoCliente *atual = lista;
    NoCliente *proximo_no;
    //roda a lista toda dando free em cada nó
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

//função pra mostrar todos (read all)
//so mostra quem tem status 1
void exibir_todos_clientes(NoCliente* lista) {
    NoCliente *atual = lista;
    int contador_ativos = 0;

    printf("\n==== lista de clientes cadastrados ====\n");
    while (atual != NULL) {
        //so mostra se o cliente tiver ativo
        if (atual->dados.status == 1) {
            exibir_cliente(&(atual->dados)); //chama a view pra mostrar cada cliente
            contador_ativos++;
        }
        atual = atual->proximo;
    }

    if (contador_ativos == 0) {
        printf("+--------------------------+\n");
        printf("| nenhum cliente cadastrado! |\n");
        printf("+--------------------------+\n");
    }
    printf("=======================================\n");
}
//novo: função pra mostrar TODOS os clientes (ativos e inativos)
void exibir_todos_clientes_e_inativos(NoCliente* lista) {
    NoCliente *atual = lista;
    int contador_total = 0; //mudei o nome da variável pra ficar mais claro

    printf("\n==== lista de TODOS os clientes (ativos e inativos) ====\n");
    while (atual != NULL) {
        //agora exibe TUDO, sem perguntar o status!
        exibir_cliente(&(atual->dados)); //chama a view pra mostrar cada cliente
        contador_total++;
        
        atual = atual->proximo;
    }

    if (contador_total == 0) {
        printf("+--------------------------+\n");
        printf("| nenhum cliente cadastrado! |\n");
        printf("+--------------------------+\n");
    }
    printf("=======================================\n");
}