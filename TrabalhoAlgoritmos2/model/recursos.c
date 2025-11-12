#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursos.h"
#include "../controller/saida.h" //pra saber se ta em modo memoria (critico!)
#include "../view/recursos_view.h" //p exibir mensagem de erro

//--- funcoes auxiliares ---
//copia tudo de um recurso pro outro na moral
void copiar_dados_recurso(Equipamento *destino, const Equipamento *origem) {
    //verifica se eh nulo se for vaza
    if (!origem || !destino) return; 

    //copia os int e float direto
    destino->codigo = origem->codigo;
    destino->quantidade_estoque = origem->quantidade_estoque;
    destino->preco_custo = origem->preco_custo;
    destino->valor_locacao = origem->valor_locacao;
    destino->status = origem->status; //copia o status tbm
    
    //copia segura das strings (strncpy pra n dar errado)
    strncpy(destino->descricao, origem->descricao, sizeof(destino->descricao) - 1);
    destino->descricao[sizeof(destino->descricao) - 1] = '\0'; //garante o fim da string
    strncpy(destino->categoria, origem->categoria, sizeof(destino->categoria) - 1);
    destino->categoria[sizeof(destino->categoria) - 1] = '\0'; //garante o fim da string
}

//funcoes de manipulacao de lista ligada (crud)
//cria um novo no e poe ele no comeco da lista (c)
NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso) {
    //avisa se nao for modo memoria, a responsabilidade nao eh sua
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_recursos("");
        return lista; 
    }
    
    NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso)); //pede memoria pro no novo
    if (novo_no == NULL) {
        //se n deu pra alocar a gente so retorna a lista antiga
        exibir_mensagem_recursos("erro:falha ao alocar no de recurso na memoria.");
        return lista; 
    }
    
    //seta o status (ativo)
    novo_recurso.status = 1;

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
        //so retorna se o status for 1 (ativo)
        if (atual->dados.codigo == codigo_busca && atual->dados.status == 1) {
            return &(atual->dados); //achou! devolve o ponteiro pros dados do equip
        }
        atual = atual->proximo;
    }
    return NULL; //nao achou
}

//atualiza os dados de quem ja existe na lista (u)
void atualizar_recurso_por_codigo(NoRecurso* lista, int codigo_busca, const char* descricao, const char* categoria, int quantidade_estoque, float preco_custo, float valor_locacao) {
    //busca o recurso ativo na lista em memoria
    Equipamento *recurso_existente = buscar_recurso_por_codigo(lista, codigo_busca);
    
    if (recurso_existente) {
        //atualiza os floats e ints
        recurso_existente->quantidade_estoque = quantidade_estoque;
        recurso_existente->preco_custo = preco_custo;
        recurso_existente->valor_locacao = valor_locacao; 
        
        //atualiza as strings com copia segura
        strncpy(recurso_existente->descricao, descricao, sizeof(recurso_existente->descricao) - 1);
        recurso_existente->descricao[sizeof(recurso_existente->descricao) - 1] = '\0';
        strncpy(recurso_existente->categoria, categoria, sizeof(recurso_existente->categoria) - 1);
        recurso_existente->categoria[sizeof(recurso_existente->categoria) - 1] = '\0';
        
        //avisa se nao for memoria (a responsa do arquivo nao eh sua)
        if (verificar_tipo_saida() != 3) {
            exibir_mensagem_recursos("");
        }
    }
}


//deleta o no da lista (d) - so funciona em modo memoria
NoRecurso* deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    //avisa se nao for modo memoria, a responsa nao eh sua
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_recursos("");
        return lista;
    }
    
    NoRecurso *atual = lista;
    NoRecurso *anterior = NULL;

    //procura o no pra apagar (ignora o status pq vai sumir msm)
    while (atual != NULL && atual->dados.codigo != codigo_busca) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return lista; //se n achou volta a lista como ta

    if (anterior == NULL) {
        lista = atual->proximo; //se era a cabeca o proximo vira a cabeca
    } else {
        anterior->proximo = atual->proximo; //pula o no do meio
    }
    
    free(atual); //libera a memoria dele
    return lista;
}

//mt critica: libera a memoria p n dar memory leak (so em memoria)
void desalocar_lista_recursos(NoRecurso* lista) {
    //so faz se tiver em modo memoria
    if (verificar_tipo_saida() != 3) {
        return; //nao desaloca se nao eh modo memoria
    }
    
    NoRecurso *atual = lista;
    NoRecurso *proximo_no;
    //roda a lista toda dando free em cada no
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

//pra mostrar geral (so os ativos em memoria)
void exibir_todos_recursos(NoRecurso* lista) {
    //so exibe se estiver em modo memoria
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_recursos("");
        return;
    }
    
    NoRecurso *atual = lista;
    int contador = 0; //pra saber se a lista ta vazia

    exibir_cabecalho_lista_recursos(); //chama a view pra mostrar o cabecalho
    
    while (atual != NULL) {
        //filtra por status ativo
        if (atual->dados.status == 1) { 
            exibir_recurso(&(atual->dados)); //chama a view pra mostrar cada um
            contador++;
        }
        atual = atual->proximo;
    }

    if (contador == 0) {
        exibir_mensagem_recursos("nenhum recurso/equipamento cadastrado!");
    }
    exibir_rodape_lista_recursos(); //chama a view pra mostrar o rodape
}

//funcao auxiliar que so retorna a lista no modo memoria
NoRecurso* carregar_recursos(NoRecurso* lista) {
    return lista; //a lista ja ta no escopo global ent so retorna ela
}