#include <stdio.h>
#include <stdlib.h>
#include "../model/recursos.h"
#include "recursos_view.h"

//exibe o menu e pega a escolha do usuario
int exibir_menu_recursos() {
    int opcao;
    printf("\n==== menu recursos e equipamentos ====\n");
    printf("1-criar equipamento\n");
    printf("2-atualizar equipamento\n");
    printf("3-exibir equipamento\n");
    printf("4-deletar equipamento (fisico)\n");
    printf("5-listar todos\n"); 
    printf("0-voltar ao menu principal\n");
    printf("escolha:");
    scanf("%d", &opcao); //pega a escolha
    return opcao;
}

//pega todos os dados pra criar um novo equipamento
Equipamento ler_dados_recurso() {
    Equipamento e;
    printf("codigo:"); scanf("%d", &e.codigo);
    printf("descricao (ex: caixa de som ativa):"); scanf(" %99[^\n]", e.descricao); //%[] pra ler strings com espaco
    printf("categoria (ex: sonorizacao):"); scanf(" %49[^\n]", e.categoria);
    printf("quantidade em estoque:"); scanf("%d", &e.quantidade_estoque);
    printf("preco de custo (r$):"); scanf("%f", &e.preco_custo);
    printf("valor de locacao diaria (r$):"); scanf("%f", &e.valor_locacao);
    e.status = 1; //define o status aqui mas o model sobrescreve se precisar
    return e; //devolve a struct cheia
}

//pega so os dados novos pra atualizar
void ler_dados_atualizacao_recurso(char* descricao, char* categoria, int* quantidade_estoque, float* preco_custo, float* valor_locacao) {
    printf("nova descricao:"); scanf(" %99[^\n]", descricao);
    printf("nova categoria:"); scanf(" %49[^\n]", categoria);
    printf("nova quantidade em estoque:"); scanf("%d", quantidade_estoque);
    printf("novo preco de custo (r$):"); scanf("%f", preco_custo);
    printf("novo valor de locacao diaria (r$):"); scanf("%f", valor_locacao);
}

//mostra um equipamento com todos os campos bonitinho
void exibir_recurso(const Equipamento* recurso) {
    //se o ponteiro for nulo vaza
    if (!recurso) {
        printf("+--------------------------+\n");
        printf("| recurso inexistente!     |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("\n+---------------------------------+\n");
    printf("| codigo          :%d\n", recurso->codigo);
    printf("| descricao       :%s\n", recurso->descricao);
    printf("| categoria       :%s\n", recurso->categoria);
    printf("| estoque         :%d\n", recurso->quantidade_estoque);
    printf("| custo           :r$ %.2f\n", recurso->preco_custo);
    printf("| locacao diaria  :r$ %.2f\n", recurso->valor_locacao);
    printf("| status (ativo)  :%d\n", recurso->status);
    printf("+---------------------------------+\n");
}

//funcao pra ler o codigo que o user quer usar pra alguma operacao
int ler_codigo_para_operacao_recursos(const char* operacao) {
    int codigo;
    printf("digite o codigo do equipamento para %s:", operacao);
    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n'); //limpa o buffer se o cara digitar letra
        return -1; //retorna -1 pra indicar erro
    }
    return codigo;
}

//mostra uma mensagem simples na tela
void exibir_mensagem_recursos(const char* msg) {
    printf("%s\n", msg);
}

//cabecalho da lista
void exibir_cabecalho_lista_recursos() {
    printf("\n==== lista de recursos e equipamentos ====\n");
}

//rodape da lista
void exibir_rodape_lista_recursos() {
    printf("==========================================\n");
}