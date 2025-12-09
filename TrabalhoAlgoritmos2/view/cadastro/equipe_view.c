#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/equipe.h"
#include "equipe_view.h"

int ler_codigo_para_operacao(const char* operacao) {
    int codigo;
    printf("digite o codigo do membro para %s: ", operacao);
    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n'); 
        return -1;
    }
    return codigo;
}

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
    
    m.codigo = 0; 

    printf("nome: "); scanf(" %49[^\n]", m.nome);
    while (getchar() != '\n');

    printf("cpf (11 digitos): "); scanf(" %11[^\n]", m.cpf);
    while (getchar() != '\n');

    printf("funcao: "); scanf(" %49[^\n]", m.funcao);
    while (getchar() != '\n');

    printf("valor diaria/hora (r$): "); scanf("%f", &m.valor_diaria_hora);
    
    m.status = 1; 
    return m;
}

void ler_dados_atualizacao_membro(char* nome, char* cpf, char* funcao, float* valor_diaria_hora) {
    printf("novo nome: "); scanf(" %49[^\n]", nome);
    while (getchar() != '\n');
    printf("novo cpf (11 digitos): "); scanf(" %11[^\n]", cpf);
    while (getchar() != '\n');
    printf("nova funcao: "); scanf(" %49[^\n]", funcao);
    while (getchar() != '\n');
    printf("novo valor diaria/hora (r$): "); scanf("%f", valor_diaria_hora);
}

void exibir_mensagem_equipe(const char* msg) {
    printf("%s\n", msg);
}