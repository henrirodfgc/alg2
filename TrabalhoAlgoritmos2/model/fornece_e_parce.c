#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornece_e_parce.h"
#include "../view/fornece_e_parce_view.h"

// =============================================
// FUNÇÃO: copiar_dados
// OBJETIVO: Copia todos os campos de uma estrutura para outra
// PARÂMETROS:
//   - destino: Ponteiro para estrutura de destino
//   - origem: Ponteiro para estrutura de origem
// =============================================
void copiar_dados_fornece_e_parce(Fornecedores_e_parceiros *destino, const Fornecedores_e_parceiros *origem){
    
    if (!origem || !destino) return;

    destino->id = origem->id;
    destino->tipo = origem->tipo;  // NOVO: copia o tipo
    destino->servico = origem->servico;

    strncpy(destino->nome_fantasia, origem->nome_fantasia, sizeof(destino->nome_fantasia) - 1);
    destino->nome_fantasia[sizeof(destino->nome_fantasia) - 1] = '\0';

    strncpy(destino->nome_razao, origem->nome_razao, sizeof(destino->nome_razao) - 1);
    destino->nome_razao[sizeof(destino->nome_razao) - 1] = '\0';

    strncpy(destino->endereco, origem->endereco, sizeof(destino->endereco) - 1);
    destino->endereco[sizeof(destino->endereco) - 1] = '\0';

    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';

    strncpy(destino->cnpj, origem->cnpj, sizeof(destino->cnpj) - 1);
    destino->cnpj[sizeof(destino->cnpj) - 1] = '\0';

    strncpy(destino->telefone, origem->telefone, sizeof(destino->telefone) - 1);
    destino->telefone[sizeof(destino->telefone) - 1] = '\0';
}

NoFornecedores_e_parceiros* adicionar_fornecedor_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_fornecedor){
    // Define explicitamente como fornecedor (CNPJ)
    novo_fornecedor.tipo = TIPO_CNPJ;

    NoFornecedores_e_parceiros *novo_no = (NoFornecedores_e_parceiros*) malloc(sizeof(NoFornecedores_e_parceiros));
    // Verifica se a alocação foi bem sucedida
    if (novo_no == NULL) {
        exibir_mensagem_fornece_e_parce("ERRO: Falha ao alocar nó da lista");
        return lista; // Retorna lista original em caso de falha
    }

    // Copia os dados do novo fornecedor para o nó
    copiar_dados_fornece_e_parce(&(novo_no->dados), &novo_fornecedor);

    // Configura o próximo ponteiro (insere no início)
    novo_no->proximo = lista;

    // Retorna o novo nó como início da lista
    return novo_no;
}

NoFornecedores_e_parceiros* adicionar_parceiros_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_parceiro){
    // Define explicitamente como parceiro (CPF)
    novo_parceiro.tipo = TIPO_CPF;

    NoFornecedores_e_parceiros *novo_no = (NoFornecedores_e_parceiros*) malloc(sizeof(NoFornecedores_e_parceiros));
    // Verifica se a alocação foi bem sucedida
    if (novo_no == NULL) {
        exibir_mensagem_fornece_e_parce("ERRO: Falha ao alocar nó da lista");
        return lista; // Retorna lista original em caso de falha
    }

    // Copia os dados do novo parceiro para o nó
    copiar_dados_fornece_e_parce(&(novo_no->dados), &novo_parceiro);

    // Configura o próximo ponteiro (insere no início)
    novo_no->proximo = lista;

    // Retorna o novo nó como início da lista
    return novo_no;
}

Fornecedores_e_parceiros* buscar_fornece_e_parce_por_id(NoFornecedores_e_parceiros* lista, int id_busca){  // CORREÇÃO: int em vez de const char*
    NoFornecedores_e_parceiros *atual = lista;
    
    while (atual != NULL) {
        // CORREÇÃO: comparar inteiros diretamente
        if (atual->dados.id == id_busca) {
            return &(atual->dados); // Retorna ponteiro para os dados encontrados
        }
        atual = atual->proximo; // Avança para o próximo nó
    }
    return NULL;
}

void atualizar_fornecedor_por_id(NoFornecedores_e_parceiros* lista, int id_busca, const char* nome_fantasia, const char* razao_social, const char* endereco, const char* cnpj, const char* telefone, TipoServico servico){
    Fornecedores_e_parceiros *fornecedor_existente = buscar_fornece_e_parce_por_id(lista, id_busca);
    
    if (fornecedor_existente != NULL) {
        // Mantém o tipo como fornecedor
        fornecedor_existente->tipo = TIPO_CNPJ;
        fornecedor_existente->servico = servico;

        strncpy(fornecedor_existente->nome_fantasia, nome_fantasia, sizeof(fornecedor_existente->nome_fantasia) - 1);
        fornecedor_existente->nome_fantasia[sizeof(fornecedor_existente->nome_fantasia) - 1] = '\0';

        strncpy(fornecedor_existente->nome_razao, razao_social, sizeof(fornecedor_existente->nome_razao) - 1);
        fornecedor_existente->nome_razao[sizeof(fornecedor_existente->nome_razao) - 1] = '\0';

        strncpy(fornecedor_existente->endereco, endereco, sizeof(fornecedor_existente->endereco) - 1);
        fornecedor_existente->endereco[sizeof(fornecedor_existente->endereco) - 1] = '\0';

        strncpy(fornecedor_existente->cnpj, cnpj, sizeof(fornecedor_existente->cnpj) - 1);
        fornecedor_existente->cnpj[sizeof(fornecedor_existente->cnpj) - 1] = '\0';

        strncpy(fornecedor_existente->telefone, telefone, sizeof(fornecedor_existente->telefone) - 1);
        fornecedor_existente->telefone[sizeof(fornecedor_existente->telefone) - 1] = '\0';

        // Limpa o CPF pois é fornecedor
        strcpy(fornecedor_existente->cpf, "");
    }
}  

void atualizar_parceiro_por_id(NoFornecedores_e_parceiros* lista, int id_busca, const char* nome_fantasia, const char* razao_social, const char* endereco, const char* cpf, const char* telefone, TipoServico servico){
    Fornecedores_e_parceiros *parceiro_existente = buscar_fornece_e_parce_por_id(lista, id_busca);
    
    if (parceiro_existente != NULL) {
        // Mantém o tipo como parceiro
        parceiro_existente->tipo = TIPO_CPF;
        parceiro_existente->servico = servico;

        strncpy(parceiro_existente->nome_fantasia, nome_fantasia, sizeof(parceiro_existente->nome_fantasia) - 1);
        parceiro_existente->nome_fantasia[sizeof(parceiro_existente->nome_fantasia) - 1] = '\0';

        strncpy(parceiro_existente->nome_razao, razao_social, sizeof(parceiro_existente->nome_razao) - 1);
        parceiro_existente->nome_razao[sizeof(parceiro_existente->nome_razao) - 1] = '\0';

        strncpy(parceiro_existente->endereco, endereco, sizeof(parceiro_existente->endereco) - 1);
        parceiro_existente->endereco[sizeof(parceiro_existente->endereco) - 1] = '\0';

        strncpy(parceiro_existente->cpf, cpf, sizeof(parceiro_existente->cpf) - 1);
        parceiro_existente->cpf[sizeof(parceiro_existente->cpf) - 1] = '\0';

        strncpy(parceiro_existente->telefone, telefone, sizeof(parceiro_existente->telefone) - 1);
        parceiro_existente->telefone[sizeof(parceiro_existente->telefone) - 1] = '\0';

        // Limpa o CNPJ pois é parceiro
        strcpy(parceiro_existente->cnpj, "");
    }
}

NoFornecedores_e_parceiros* deletar_fornece_e_parce_por_id(NoFornecedores_e_parceiros * lista, int id_busca) {  // CORREÇÃO: int em vez de const char*
    NoFornecedores_e_parceiros *atual = lista;
    NoFornecedores_e_parceiros *anterior = NULL;

    // Percorre a lista procurando pelo ID
    while (atual != NULL && atual->dados.id != id_busca) {  // CORREÇÃO: comparar inteiros
        anterior = atual;
        atual = atual->proximo;
    }

    // Se não encontrou, retorna lista original
    if (atual == NULL) return lista;

    // Remove o nó encontrado
    if (anterior == NULL) {
        // Caso especial: remover o primeiro nó
        lista = atual->proximo;
    } else {
        // Caso geral: remover nó do meio ou final
        anterior->proximo = atual->proximo;
    }
    
    // Libera a memória do nó removido
    free(atual);
    return lista;
}

void desalocar_lista_fornece_e_parce(NoFornecedores_e_parceiros* lista) {  // CORREÇÃO: nome da função
    NoFornecedores_e_parceiros *atual = lista;
    NoFornecedores_e_parceiros *proximo_no;
    
    // Percorre a lista liberando cada nó
    while (atual != NULL) {
        proximo_no = atual->proximo; // Guarda referência do próximo
        free(atual);                 // Libera nó atual
        atual = proximo_no;          // Avança para o próximo
    }
}

void exibir_todas_fornece_e_parce(NoFornecedores_e_parceiros* lista) {
    NoFornecedores_e_parceiros *atual = lista;
    
    // Verifica se a lista está vazia
    if (atual == NULL) {
        printf("+-------------------------------------------+\n");
        printf("| Nenhum Fornecedor ou Parceiro cadastrado! |\n");
        printf("+-------------------------------------------+\n");
        return;
    }

    // Cabeçalho da lista
    printf("\n==== LISTA DE FORNECEDORES E PARCEIROS CADASTRADAS ====\n");
    
    // Percorre e exibe todos os registros
    while (atual != NULL) {
        exibir_fornece_e_parce(&(atual->dados)); // Usa função da view para exibir
        atual = atual->proximo;
    }
    
    // Rodapé da lista
    printf("=======================================\n");
}

// =============================================
// FUNÇÃO NOVA: exibir_registro_por_id
// OBJETIVO: Exibir um registro específico baseado no ID
// =============================================
void exibir_registro_por_id(NoFornecedores_e_parceiros* lista, int id) {
    Fornecedores_e_parceiros *registro = buscar_fornece_e_parce_por_id(lista, id);
    if (registro != NULL) {
        exibir_fornece_e_parce(registro);
    } else {
        printf("Registro com ID %d não encontrado!\n", id);
    }
}