#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/produtora.h"
#include "produtora_view.h"

int ler_cnpj_para_operacao(const char* operacao) {
    return 0; 
}

void exibir_produtora(const Produtora* p) {
    if (!p) {
        printf("+--------------------------+\n");
        printf("| Produtora inexistente!   |\n");
        printf("+--------------------------+\n");
        return;
    }
    printf("\n+---------------------------------+\n");
    printf("| CNPJ                    : %s\n", p->cnpj);
    printf("| Nome Fantasia           : %s\n", p->nome_fantasia);
    printf("| Razao Social            : %s\n", p->razao_social);
    printf("| Iscricao Estadual       : %s\n", p->inscricao_estadual);
    printf("| Endereco                : %s\n", p->endereco_completo);
    printf("| Telefone                : %s\n", p->telefone);
    printf("| Email                   : %s\n", p->email);
    printf("| Nome do Responsavel     : %s\n", p->nome_do_responsavel);
    printf("| Telefone do Responsavel : %s\n", p->telefone_do_responsavel);
    printf("| Margem de Lucro Padrao  : %s%%\n", p->margem_de_lucro_padrao); 
    printf("| Status                  : %d\n", p->status);
    printf("+---------------------------------+\n");
}

int exibir_menu_produtora() {
    int op;
    printf("\n==== MENU PRODUTORA ====\n");
    printf("1 - Criar produtora\n");
    printf("2 - Atualizar produtora\n");
    printf("3 - Exibir produtora\n");
    printf("4 - Deletar produtora\n");
    printf("5 - Listar todas\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

Produtora ler_dados_produtora() {
    Produtora p;
    int ch;
    

    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("CNPJ: ");
    scanf("%14[^\n]", p.cnpj);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Nome Fantasia: ");
    scanf(" %50[^\n]", p.nome_fantasia);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Razao Social: ");
    scanf("%100[^\n]", p.razao_social);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Inscricao Estadual: ");
    scanf("%9[^\n]", p.inscricao_estadual);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Endereco: ");
    scanf(" %256[^\n]", p.endereco_completo);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Telefone: ");
    scanf("%11[^\n]", p.telefone);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Email: ");
    scanf(" %49[^\n]", p.email);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Nome do Responsavel: ");
    scanf(" %49[^\n]", p.nome_do_responsavel);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Telefone do Responsavel: ");
    scanf("%11[^\n]", p.telefone_do_responsavel);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Margem de Lucro Padrao (%%): ");
    scanf(" %5[^\n]", p.margem_de_lucro_padrao);
    
    p.status = 1;
    return p;
}

void ler_dados_atualizacao_produtora(char* nome_fantasia, char* razao_social, char* inscricao_estadual, char* endereco, char* telefone, char* email, char* nome_resp, char* tel_resp, char* margem) {
    int ch;
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Novo nome fantasia: ");
    scanf(" %50[^\n]", nome_fantasia);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Nova razao social: ");
    scanf(" %100[^\n]", razao_social);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Nova inscricao estadual: ");
    scanf(" %9[^\n]", inscricao_estadual);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Novo endereco: ");
    scanf(" %256[^\n]", endereco);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Novo telefone: ");
    scanf(" %11[^\n]", telefone);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Novo email: ");
    scanf(" %49[^\n]", email);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Novo nome do responsavel: ");
    scanf(" %49[^\n]", nome_resp);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Novo telefone do responsavel: ");
    scanf(" %11[^\n]", tel_resp);
    while ((ch = getchar()) != '\n' && ch !=EOF);

    printf("Nova margem de lucro: ");
    scanf(" %5[^\n]", margem);
}

void exibir_mensagem_produtora(const char* msg) {
    printf("%s\n", msg);
}

void exibir_todas_produtoras(NoProdutora* lista) {
    NoProdutora* atual = lista;
    int cont = 0;
    printf("\n==== lista de produtoras ====\n");
    while (atual) {
        if(atual->dados.status == 1) {
            exibir_produtora(&atual->dados);
            cont++;
        }
        atual = atual->proximo;
    }
    if (cont == 0) printf("nenhuma produtora ativa.\n");
    printf("=============================\n");
}