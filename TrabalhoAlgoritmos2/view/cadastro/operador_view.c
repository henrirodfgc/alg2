#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/operador.h"
#include "operador_view.h"

char ler_codigo_para_a_operacao(const char* operacao){
    int codigo;

    printf("\nDigite o codigo do operador %s: \n", operacao);

    if (scanf("%d", &codigo) != 1) {  // ← &codigo
        // tratamento de erro
        printf("Erro: Código inválido!\n");
        while (getchar() != '\n'); // limpar buffer
        return -1; // valor inválido
        
    }

    getchar();
    return codigo;
    
}

void exibir_operador(const Operador* operador){

    if (!operador)
    {
        printf("+-------------------------+\n");
        printf("|  Operador Inexistente!  |\n");
        printf("+-------------------------+\n");

        return;
    }
    printf("\n+-----------------------+\n");
    printf("|Codigo : %d\n", operador->codigo);
    printf("|Nome   : %s\n", operador->nome);
    printf("|Usuário: %s\n", operador->usuario);
    printf("|Senha  : %s\n", operador->senha);
    printf("\n+-----------------------+\n");
    
}

void exibir_menu_operador(){

    printf("1 - Criar operador\n");
    printf("2 - Atualizar operador\n");
    printf("3 - Exibir operador\n");
    printf("4 - Deletar operador\n");
    printf("5 - Listar todos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");

}

Operador ler_dados_operador(){
    Operador c;
    int ch;

    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Código:");
    scanf("%d", &c.codigo);
    while ((ch = getchar()) != '\n' && ch !=EOF);
    
    printf("Nome:");
    scanf("%50[^\n]", c.nome);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Usuário:");
    scanf("%60[^\n]", c.usuario);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Senha:");
    scanf("%20[^\n]", c.senha);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    return c;

}

void ler_dados_atualizacao_operador(int* codigo, char* nome, char* usuario, char* senha){

    printf("Novo código: ");
    scanf("%d", codigo);

    printf("Novo nome: ");
    scanf("%50[^\n]", nome);

    printf("Novo usuário: ");
    scanf("%60[^\n]", usuario);

    printf("Nova senha: ");
    scanf("%20[^\n]", senha);
}

void exibir_mensagem_operador(const char* msg){

    printf("%s\n", msg);
}