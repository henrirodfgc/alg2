#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/recursos.h"
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
    scanf("%d", &opcao); 
    return opcao;
}

//pega todos os dados pra criar um novo equipamento
Equipamento ler_dados_recurso() {
    Equipamento e;
    float frete, imposto, margem_lucro;

    printf("codigo:"); scanf("%d", &e.codigo);
    
    //limpeza de buffer antes de ler string
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("descricao (ex: caixa de som ativa):"); 
    scanf("%99[^\n]", e.descricao); 
    
    //limpeza de buffer
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("categoria (ex: sonorizacao):"); 
    scanf("%49[^\n]", e.categoria);

    printf("quantidade em estoque:"); scanf("%d", &e.quantidade_estoque);
    
    //aqui começa a logica do calculo
    printf("preco de custo (r$):"); scanf("%f", &e.preco_custo);
    
    printf("valor do frete (r$):"); scanf("%f", &frete);
    printf("valor do imposto (r$):"); scanf("%f", &imposto);
    printf("margem de lucro pretendida (%%):"); scanf("%f", &margem_lucro);

    //calculo: (custo + frete + imposto) * (margem / 100)
    float custo_total = e.preco_custo + frete + imposto;
    e.valor_locacao = custo_total * (margem_lucro / 100.0);

    printf(">> valor de locacao calculado automaticamente: r$ %.2f\n", e.valor_locacao);

    e.status = 1; 
    return e; 
}

//pega so os dados novos pra atualizar
void ler_dados_atualizacao_recurso(char* descricao, char* categoria, int* quantidade_estoque, float* preco_custo, float* valor_locacao) {
    float frete, imposto, margem_lucro;
    int ch;

    //limpa buffer
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("nova descricao:"); scanf("%99[^\n]", descricao);
    
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("nova categoria:"); scanf("%49[^\n]", categoria);
    
    printf("nova quantidade em estoque:"); scanf("%d", quantidade_estoque);
    
    printf("novo preco de custo (r$):"); scanf("%f", preco_custo);
    
    //pede os dados pra recalcular a locacao
    printf("novo valor do frete (r$):"); scanf("%f", &frete);
    printf("novo valor do imposto (r$):"); scanf("%f", &imposto);
    printf("nova margem de lucro (%%):"); scanf("%f", &margem_lucro);

    float custo_total = *preco_custo + frete + imposto;
    *valor_locacao = custo_total * (margem_lucro / 100.0);

    printf(">> novo valor de locacao calculado: r$ %.2f\n", *valor_locacao);
}

//mostra um equipamento com todos os campos
void exibir_recurso(const Equipamento* recurso) {
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
        while (getchar() != '\n'); 
        return -1; 
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