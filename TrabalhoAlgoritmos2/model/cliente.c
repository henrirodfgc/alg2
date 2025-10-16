#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "../view/cliente_view.h"

//--- FUNÇÕES AUXILIARES ---
// Copia TUDO de uma struct Cliente pra outra de forma segura
void copiar_dados(Cliente *destino, const Cliente *origem) {
    if (!origem || !destino) return; // Se for NULL sai fora
    
    destino->id = origem->id;
    destino->idade = origem->idade;
    
    // Cópia segura de todas as strings pra n dar BO
    // Uso strncpy e garanto q o ultimo é \0
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


//--- FUNÇÕES DE MANIPULAÇÃO DE LISTA LIGADA (CRUD) ---
// Adiciona um nó no começo da lista (CREATE)
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente) {
    NoCliente *novo_no = (NoCliente*) malloc(sizeof(NoCliente)); // Aloca a memoria pro novo nó
    if (novo_no == NULL) {
        exibir_mensagem("ERRO: Falha ao alocar nó da lista"); // Avisa q n deu pra alocar
        return lista; 
    }

    // Copia os dados pro espaço alocado
    copiar_dados(&(novo_no->dados), &novo_cliente);

    // O novo nó vira a cabeça da lista
    novo_no->proximo = lista;

    return novo_no; // Retorna a nova cabeça
}

// Procura o client pelo ID (READ)
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca) {
    NoCliente *atual = lista;
    // Roda a lista até achar o ID ou a lista acabar
    while (atual != NULL) {
        if (atual->dados.id == id_busca) {
            return &(atual->dados); // Retorna o ponteiro pros dados do client
        }
        atual = atual->proximo;
    }
    return NULL; // Não achou
}

// Atualiza os dados do client q a gente achou (UPDATE)
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato) {
    Cliente *cliente_existente = buscar_cliente_por_id(lista, id_busca);
    
    if (cliente_existente) {
        // Atualiza campos q n são string
        cliente_existente->idade = idade;
        
        // Atualiza os campos string com CÓPIA SEGURA (strncpy)
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


// Deleta o nó da lista (DELETE)
NoCliente* deletar_cliente_por_id(NoCliente* lista, int id_busca) {
    NoCliente *atual = lista;
    NoCliente *anterior = NULL;

    // Acha o nó a ser deletado
    while (atual != NULL && atual->dados.id != id_busca) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return lista; // Se n achou volta a lista como ta

    if (anterior == NULL) {
        lista = atual->proximo; // Se for o primeiro o próximo vira a cabeça
    } else {
        anterior->proximo = atual->proximo; // Pula o nó q vai ser deletado
    }
    
    free(atual); // Libera a memoria do nó deletado (MT IMPORTANTE)
    return lista;
}

// FUNÇÃO ESSENCIAL: Libera a memória de GERAL
void desalocar_lista_clientes(NoCliente* lista) {
    NoCliente *atual = lista;
    NoCliente *proximo_no;
    // Roda a lista toda liberando um por um
    while (atual != NULL) {
        proximo_no = atual->proximo; // Guarda o próximo antes de dar free no atual
        free(atual);
        atual = proximo_no;
    }
}

// FUNÇÃO PRA MOSTRAR GERAL (READ ALL)
void exibir_todos_clientes(NoCliente* lista) {
    NoCliente *atual = lista;
    if (atual == NULL) {
        printf("+--------------------------+\n");
        printf("| Nenhum cliente cadastrado! |\n");
        printf("+--------------------------+\n");
        return;
    }

    printf("\n==== LISTA DE CLIENTES CADASTRADOS ====\n");
    while (atual != NULL) {
        exibir_cliente(&(atual->dados)); // Chama a view pra mostrar cada client
        atual = atual->proximo;
    }
    printf("=======================================\n");
}