#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/equipe.h"
#include "equipe_view.h"

// Função pra ler o CÓDIGO
int ler_codigo_para_operacao(const char* operacao) {
    int codigo;
    printf("Digite o CÓDIGO do membro para %s: ", operacao);
    if (scanf("%d", &codigo) != 1) {
        // Limpa o buffer se o cara digitar letra no lugar de numero
        while (getchar() != '\n'); 
        return -1; // Retorna -1 pra indicar erro
    }
    return codigo;
}

// Mostra um membro com todos os campos bonitinho
void exibir_membro(const MembroEquipe* membro) {
    if (!membro) {
        printf("+--------------------------+\n");
        printf("| Membro inexistente!      |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("\n+---------------------------------+\n");
    printf("| Código          : %d\n", membro->codigo);
    printf("| Nome            : %s\n", membro->nome);
    printf("| CPF             : %s\n", membro->cpf);
    printf("| Função          : %s\n", membro->funcao);
    printf("| Valor Diária/Hora: R$ %.2f\n", membro->valor_diaria_hora);
    printf("+---------------------------------+\n");
}

// Desenha o menu e pega a escolha
int exibir_menu_equipe() {
    int opcao;
    printf("\n==== MENU EQUIPE ====\n");
    printf("1 - Criar membro\n");
    printf("2 - Atualizar membro\n");
    printf("3 - Exibir membro\n");
    printf("4 - Deletar membro (físico)\n");
    printf("5 - Listar todos\n"); 
    printf("0 - Voltar ao Menu Principal\n");
    printf("Escolha: ");
    scanf("%d", &opcao); // Pega a escolha
    return opcao;
}

// Lê TODOS os dados de um membro pra criar um novo
MembroEquipe ler_dados_membro() {
    MembroEquipe m;
    printf("CÓDIGO: "); scanf("%d", &m.codigo);
    printf("Nome: "); scanf(" %[^\n]", m.nome); // %[] pra ler strings com espaço
    printf("CPF (11 digitos): "); scanf(" %11[^\n]", m.cpf); 
    printf("Função: "); scanf(" %[^\n]", m.funcao);
    printf("Valor Diária/Hora (R$): "); scanf("%f", &m.valor_diaria_hora);
    return m; // Devolve a struct cheia
}

// Lê os dados novos pra atualização
void ler_dados_atualizacao_membro(char* nome, char* cpf, char* funcao, float* valor_diaria_hora) {
    printf("Novo Nome: "); scanf(" %[^\n]", nome);
    printf("Novo CPF (11 digitos): "); scanf(" %11[^\n]", cpf);
    printf("Nova Função: "); scanf(" %[^\n]", funcao);
    printf("Novo Valor Diária/Hora (R$): "); scanf("%f", valor_diaria_hora);
}

// Função simples pra mostrar mensagem
void exibir_mensagem_equipe(const char* msg) {
    printf("%s\n", msg);
}
