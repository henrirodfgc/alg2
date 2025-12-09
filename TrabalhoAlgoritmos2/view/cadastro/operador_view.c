#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/operador.h"
#include "operador_view.h"

int ler_codigo_para_a_operacao(const char* operacao){
    int codigo;
    printf("\nDigite o codigo do operador para %s: ", operacao);
    if (scanf("%d", &codigo) != 1) {  
        printf("Erro: Codigo invalido!\n");
        while (getchar() != '\n'); 
        return -1; 
    }
    getchar();
    return codigo;
}

void exibir_operador(const Operador* operador){
    if (!operador) {
        printf("+-------------------------+\n");
        printf("|  Operador Inexistente!  |\n");
        printf("+-------------------------+\n");
        return;
    }
    printf("\n+-----------------------+\n");
    printf("|Codigo : %d\n", operador->codigo);
    printf("|Nome   : %s\n", operador->nome);
    printf("|Usuario: %s\n", operador->usuario);
    printf("+-----------------------+\n");
}

int exibir_menu_operador(){
    int op;
    printf("\n=== MENU OPERADOR ===\n");
    printf("1 - Criar operador\n");
    printf("2 - Atualizar operador\n");
    printf("3 - Exibir operador\n");
    printf("4 - Deletar operador\n");
    printf("5 - Listar todos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

Operador ler_dados_operador(){
    Operador c;
    c.codigo = 0; 

    int ch;
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Nome: ");
    scanf(" %50[^\n]", c.nome);
    while (getchar() != '\n');

    printf("Usuario: ");
    scanf(" %60[^\n]", c.usuario);
    while (getchar() != '\n');

    printf("Senha: ");
    scanf(" %20[^\n]", c.senha);
    while (getchar() != '\n');

    c.status = 1; 
    return c;
}

void ler_dados_atualizacao_operador(char* nome, char* usuario, char* senha){
    printf("Novo nome: ");
    scanf(" %50[^\n]", nome);
    while (getchar() != '\n');

    printf("Novo usuario: ");
    scanf(" %60[^\n]", usuario);
    while (getchar() != '\n');

    printf("Nova senha: ");
    scanf(" %20[^\n]", senha);
    while (getchar() != '\n');
}

void exibir_mensagem_operador(const char* msg){
    printf("%s\n", msg);
}

void exibir_todos_operadores(NoOperador* lista) {
    NoOperador* atual = lista;
    printf("\n==== LISTA DE OPERADORES ====\n");
    int cont = 0;
    while(atual != NULL) {
        if(atual->dados.status == 1) {
            exibir_operador(&(atual->dados));
            cont++;
        }
        atual = atual->proximo;
    }
    if(cont == 0) printf("Nenhum operador ativo.\n");
    printf("=============================\n");
}