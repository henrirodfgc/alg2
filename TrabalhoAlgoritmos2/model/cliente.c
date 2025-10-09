#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "../view/cliente_view.h"

//--- FUNÇÕES AUXILIARES ---
//Função auxiliar para COPIAR DADOS de uma struct para outra
void copiar_dados(Cliente *destino, const Cliente *origem) {
    if (!origem || !destino) return;
    
    destino->id = origem->id;
    destino->idade = origem->idade;
    
    //Cópia segura de todas as strings (incluindo Telefone e Contato)
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
//FUNÇÃO QUE ADICIONA O NÓ NA LISTA (Implementação principal do CRUD/CREATE)
NoCliente* adicionar_cliente_na_lista(NoCliente* lista, Cliente novo_cliente) {
    NoCliente *novo_no = (NoCliente*) malloc(sizeof(NoCliente));
    if (novo_no == NULL) {
        exibir_mensagem("ERRO: Falha ao alocar nó da lista.");
        return lista; 
    }

    //Copia a struct Cliente preenchida para dentro do novo nó
    copiar_dados(&(novo_no->dados), &novo_cliente);

    //O novo nó se torna a cabeça da lista
    novo_no->proximo = lista;

    return novo_no;
}

//FUNÇÃO DE BUSCA DO NÓ NA LISTA (Utilizada por outras funções e pelo Controller)
Cliente* buscar_cliente_por_id(NoCliente* lista, int id_busca) {
    NoCliente *atual = lista;
    while (atual != NULL) {
        if (atual->dados.id == id_busca) {
            return &(atual->dados); //Retorna o ponteiro para o DADO (Cliente)
        }
        atual = atual->proximo;
    }
    return NULL; //Não encontrado
}

//FUNÇÃO QUE ATUALIZA O CLIENTE NA LISTA (Implementação corrigida para usar todos os parâmetros)
void atualizar_cliente_por_id(NoCliente* lista, int id_busca, const char* nome_cliente, int idade, const char* nome_razao, const char* cpf, const char* cnpj, const char* endereco, const char* email, const char* telefone, const char* nome_contato) {
    Cliente *cliente_existente = buscar_cliente_por_id(lista, id_busca);
    
    if (cliente_existente) {
        //Atualizando os campos não string
        cliente_existente->idade = idade;
        
        //Atualizando TODOS os campos string com CÓPIA SEGURA
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


//FUNÇÃO QUE DELETA O NÓ NA LISTA
NoCliente* deletar_cliente_por_id(NoCliente* lista, int id_busca) {
    NoCliente *atual = lista;
    NoCliente *anterior = NULL;

    while (atual != NULL && atual->dados.id != id_busca) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return lista; //Não encontrou

    if (anterior == NULL) {
        lista = atual->proximo; //É a cabeça
    } else {
        anterior->proximo = atual->proximo; //Nó no meio/fim
    }
    
    free(atual);
    return lista;
}

//FUNÇÃO CRÍTICA: LIBERAÇÃO DE MEMÓRIA (de todos os NÓS)
void desalocar_lista_clientes(NoCliente* lista) {
    NoCliente *atual = lista;
    NoCliente *proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
}

//FUNÇÃO DE LISTAR TODOS (para a nova opção do menu)
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
        exibir_cliente(&(atual->dados)); //Passa o Cliente* que está dentro do nó
        atual = atual->proximo;
    }
    printf("=======================================\n");
}