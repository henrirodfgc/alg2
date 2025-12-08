#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../model/cadastro/equipe.h"
#include "equipe_view.h"

// Função pra ler o CÓDIGO
int ler_codigo_para_operacao(const char* operacao) {
    int codigo;
    printf("digite o codigo do membro para %s: ", operacao);
    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n'); //limpa o buffer se o cara digitar letra no lugar de numero
        return -1; //retorna -1 pra indicar erro
    }
    return codigo;
}

// Mostra um membro com todos os campos
void exibir_membro(const MembroEquipe* membro) {
    if (!membro) {
        printf("+--------------------------+\n");
        printf("| membro inexistente!      |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("\n+---------------------------------+\n");
    printf("| codigo          :%d\n", membro->codigo);
    printf("| nome            :%s\n", membro->nome);
    printf("| cpf             :%s\n", membro->cpf);
    printf("| funcao          :%s\n", membro->funcao);
    printf("| valor diaria/hora:r$ %.2f\n", membro->valor_diaria_hora);
    printf("| status (ativo)  :%d\n", membro->status);
    printf("+---------------------------------+\n");
}

// Desenha o menu e pega a escolha
int exibir_menu_equipe() {
    int opcao;
    printf("\n==== menu equipe ====\n");
    printf("1 - criar membro\n");
    printf("2 - atualizar membro\n");
    printf("3 - exibir membro\n");
    printf("4 - inativar membro (soft delete)\n"); 
    printf("5 - listar todos (ativos)\n"); 
    printf("6 - restaurar membro (reativar)\n"); 
    printf("7 - listar so inativos\n"); 
    printf("0 - voltar ao menu principal\n");
    printf("escolha: ");
    scanf("%d", &opcao); 
    return opcao;
}

MembroEquipe ler_dados_membro() {
    MembroEquipe m;
    printf("codigo: "); scanf("%d", &m.codigo);
    printf("nome: "); scanf(" %[^\n]", m.nome); //%[] pra ler strings com espaco
    printf("cpf (11 digitos): "); scanf(" %11[^\n]", m.cpf); 
    printf("funcao: "); scanf(" %[^\n]", m.funcao);
    printf("valor diaria/hora (r$): "); scanf("%f", &m.valor_diaria_hora);
    m.status = 1; //define o status aqui
    return m; //devolve a struct cheia
}

//lê os dados novos pra atualização
void ler_dados_atualizacao_membro(char* nome, char* cpf, char* funcao, float* valor_diaria_hora) {
    printf("novo nome: "); scanf(" %[^\n]", nome);
    printf("novo cpf (11 digitos): "); scanf(" %11[^\n]", cpf);
    printf("nova funcao: "); scanf(" %[^\n]", funcao);
    printf("novo valor diaria/hora (r$): "); scanf("%f", valor_diaria_hora);
}

//função simples pra mostrar mensagem
void exibir_mensagem_equipe(const char* msg) {
    printf("%s\n", msg);
}