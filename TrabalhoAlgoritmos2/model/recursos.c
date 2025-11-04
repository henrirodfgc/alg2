#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursos.h"
// #include "../view/recursos_view.h" //a view a gente faz qdo for pra exibir bonitinho

//--- funcoes auxiliares ---
//copia tudo de um recurso pro outro na moral
void copiar_dados_recurso(Equipamento *destino, const Equipamento *origem) {
    if (!origem || !destino) return; //se for null vaza

    destino->codigo = origem->codigo;
    destino->quantidade_estoque = origem->quantidade_estoque;
    destino->preco_custo = origem->preco_custo;
    destino->valor_locacao = origem->valor_locacao;
    
    //copia segura das strings (strncpy pra n dar errado)
    strncpy(destino->descricao, origem->descricao, sizeof(destino->descricao) - 1);
    destino->descricao[sizeof(destino->descricao) - 1] = '\0';
    strncpy(destino->categoria, origem->categoria, sizeof(destino->categoria) - 1);
    destino->categoria[sizeof(destino->categoria) - 1] = '\0';
}


//--- funcoes de manipulacao de lista ligada (crud) ---
//cria um novo no e poe ele no comeco da lista (c)
NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso) {
    NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso)); //pede memoria pro no novo
    if (novo_no == NULL) {
        //se n deu pra alocar, a gente so retorna a lista antiga e da erro la no controller
        return lista; 
    }

    //copia os dados pro no q a gente criou
    copiar_dados_recurso(&(novo_no->dados), &novo_recurso);

    //o no novo sempre vira a cabeca da lista
    novo_no->proximo = lista;

    return novo_no; //devolve a nova cabeca
}

//procura o recurso pelo codigo (r)
Equipamento* buscar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    NoRecurso *atual = lista;
    //percorre a lista ate achar o codigo ou a lista acabar
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca) {
            return &(atual->dados); //achou! devolve o ponteiro pros dados do equip
        }
        atual = atual->proximo;
    }
    return NULL; //nao achou
}

//atualiza os dados de quem ja existe na lista (u)
void atualizar_recurso_por_codigo(NoRecurso* lista, int codigo_busca, const char* descricao, const char* categoria, int quantidade_estoque, float preco_custo, float valor_locacao) {
    Equipamento *recurso_existente = buscar_recurso_por_codigo(lista, codigo_busca);
    
    if (recurso_existente) {
        //atualiza os floats e ints
        recurso_existente->quantidade_estoque = quantidade_estoque;
        recurso_existente->preco_custo = preco_custo;
        recurso_existente->valor_locacao = valor_locacao; //lembrar q o calculo e feito na compra/controller
        
        //atualiza as strings com copia segura
        strncpy(recurso_existente->descricao, descricao, sizeof(recurso_existente->descricao) - 1);
        recurso_existente->descricao[sizeof(recurso_existente->descricao) - 1] = '\0';
        strncpy(recurso_existente->categoria, categoria, sizeof(recurso_existente->categoria) - 1);
        recurso_existente->categoria[sizeof(recurso_existente->categoria) - 1] = '\0';
    }
}


//deleta o no da lista (d)
NoRecurso* deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    NoRecurso *atual = lista;
    NoRecurso *anterior = NULL;

    //procura o no pra apagar
    while (atual != NULL && atual->dados.codigo != codigo_busca) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return lista; //se n achou volta a lista como ta

    if (anterior == NULL) {
        lista = atual->proximo; //se era a cabeca, o proximo vira a cabeca
    } else {
        anterior->proximo = atual->proximo; //pula o no do meio
    }
    
    free(atual); //libera a memoria dele (sem memory leak!)
    return lista;
}

//funcao essencial: libera a memoria de geral
void desalocar_lista_recursos(NoRecurso* lista) {
    NoRecurso *atual = lista;
    NoRecurso *proximo_no;
    //roda a lista toda dando free em cada no
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

//funcao pra mostrar todos (a view vai usar essa)
void exibir_todos_recursos(NoRecurso* lista) {
    NoRecurso *atual = lista;
    int contador = 0; //pra saber se a lista ta vazia

    printf("\n==== LISTA DE RECURSOS E EQUIPAMENTOS ====\n");
    while (atual != NULL) {
        //qdo a view tiver pronta a gente exibe bonitinho. por enquanto vai assim:
        printf("--------------------------------------\n");
        printf("Codigo: %d\n", atual->dados.codigo);
        printf("Descricao: %s\n", atual->dados.descricao);
        printf("Categoria: %s\n", atual->dados.categoria);
        printf("Estoque: %d\n", atual->dados.quantidade_estoque);
        printf("Custo: R$ %.2f\n", atual->dados.preco_custo);
        printf("Locacao Diaria: R$ %.2f\n", atual->dados.valor_locacao);
        printf("--------------------------------------\n");

        contador++;
        atual = atual->proximo;
    }

    if (contador == 0) {
        printf("+---------------------------------------+\n");
        printf("| nenhum recurso/equipamento cadastrado!|\n");
        printf("+---------------------------------------+\n");
    }
    printf("==========================================\n");
}