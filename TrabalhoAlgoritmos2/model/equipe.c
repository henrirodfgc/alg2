#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipe.h"
// #include "../view/equipe_view.h" //a view a gente faz dps

//--- funções auxiliares ---
//copia tudo de um membro pro outro
void copiar_dados_equipe(MembroEquipe *destino, const MembroEquipe *origem) {
    if (!origem || !destino) return; //se for null sai fora pra n dar bo
    
    destino->codigo = origem->codigo;
    destino->valor_diaria_hora = origem->valor_diaria_hora; //copia o valor da diaria/hora
    
    //cópia segura de todas as strings
    strncpy(destino->nome, origem->nome, sizeof(destino->nome) - 1);
    destino->nome[sizeof(destino->nome) - 1] = '\0';
    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';
    strncpy(destino->funcao, origem->funcao, sizeof(destino->funcao) - 1);
    destino->funcao[sizeof(destino->funcao) - 1] = '\0';
}


//--- funções de manipulação de lista ligada (crud) ---
//cria um novo nó e põe ele no começo da lista (create)
NoEquipe* adicionar_membro_na_lista(NoEquipe* lista, MembroEquipe novo_membro) {
    NoEquipe *novo_no = (NoEquipe*) malloc(sizeof(NoEquipe)); //pede memoria pra esse nó novo
    if (novo_no == NULL) {
        //se n der pra alocar, a gente só retorna a lista antiga
        return lista; 
    }

    //copia os dados pro nó que a gente acabou de criar
    copiar_dados_equipe(&(novo_no->dados), &novo_membro);

    //o novo nó sempre vira a cabeça da lista (a lista fica invertida)
    novo_no->proximo = lista;

    return novo_no; //devolve a nova cabeça da lista
}

//procura o membro pelo código (read)
MembroEquipe* buscar_membro_por_codigo(NoEquipe* lista, int codigo_busca) {
    NoEquipe *atual = lista;
    //percorre a lista até achar o código ou a lista acabar
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca) {
            return &(atual->dados); //achou! devolve o ponteiro pros dados
        }
        atual = atual->proximo;
    }
    return NULL; //não achou, termina
}

//atualiza os dados de quem já existe na lista (update)
void atualizar_membro_por_codigo(NoEquipe* lista, int codigo_busca, const char* nome, const char* cpf, const char* funcao, float valor_diaria_hora) {
    MembroEquipe *membro_existente = buscar_membro_por_codigo(lista, codigo_busca);
    
    if (membro_existente) {
        //atualiza o float (valor)
        membro_existente->valor_diaria_hora = valor_diaria_hora;
        
        //atualiza as strings com cópia segura (strncpy)
        strncpy(membro_existente->nome, nome, sizeof(membro_existente->nome) - 1);
        membro_existente->nome[sizeof(membro_existente->nome) - 1] = '\0';
        strncpy(membro_existente->cpf, cpf, sizeof(membro_existente->cpf) - 1);
        membro_existente->cpf[sizeof(membro_existente->cpf) - 1] = '\0';
        strncpy(membro_existente->funcao, funcao, sizeof(membro_existente->funcao) - 1);
        membro_existente->funcao[sizeof(membro_existente->funcao) - 1] = '\0';
    }
}


//deleta o nó da lista (delete)
NoEquipe* deletar_membro_por_codigo(NoEquipe* lista, int codigo_busca) {
    NoEquipe *atual = lista;
    NoEquipe *anterior = NULL;

    //procura o nó pra apagar
    while (atual != NULL && atual->dados.codigo != codigo_busca) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return lista; //se n achou volta a lista como ta

    if (anterior == NULL) {
        lista = atual->proximo; //se era a cabeça, o próximo vira a cabeça
    } else {
        anterior->proximo = atual->proximo; //pula o nó do meio
    }
    
    free(atual); //libera a memoria dele (sem memory leak!)
    return lista;
}

//função essencial: libera a memória de geral
void desalocar_lista_equipe(NoEquipe* lista) {
    NoEquipe *atual = lista;
    NoEquipe *proximo_no;
    //roda a lista toda dando free em cada nó
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

//função pra mostrar geral (a view vai usar essa)
//void exibir_todos_membros(NoEquipe* lista) { ... }