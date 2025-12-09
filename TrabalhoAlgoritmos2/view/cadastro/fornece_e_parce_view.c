#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../model/cadastro/fornece_e_parce.h"
#include "fornece_e_parce_view.h"

const char* servico_para_string(TipoServico s) {
    switch(s) {
        case SERVICO_BUFFET: return "Buffet";
        case SERVICO_SEGURANCA: return "Seguranca";
        case SERVICO_ATRACAO_MUSICAL: return "Atracao Musical";
        default: return "Desconhecido";
    }
}

TipoServico obter_servico_usuario() {
    int opcao_servico;
    printf("\nselecione o servico:\n");
    printf("1 - Buffet\n");
    printf("2 - Seguranca\n");
    printf("3 - Atracao Musical\n");
    printf("escolha: ");
    scanf("%d", &opcao_servico);
    while (getchar() != '\n'); 

    if (opcao_servico == 1) return SERVICO_BUFFET;
    if (opcao_servico == 2) return SERVICO_SEGURANCA;
    if (opcao_servico == 3) return SERVICO_ATRACAO_MUSICAL;
    
    printf("opcao invalida, definindo padrao (Buffet).\n");
    return SERVICO_BUFFET;
}

TipoServico obter_novo_servico_usuario(TipoServico servico_atual) {
    int alterar;
    printf("deseja alterar o servico (atual: %s)? (1-sim / 0-nao): ", servico_para_string(servico_atual));
    scanf("%d", &alterar);
    while (getchar() != '\n');

    if (alterar == 1) {
        return obter_servico_usuario();
    }
    return servico_atual;
}

void exibir_menu_principal_fornece_parce() {
    printf("\n==== menu fornecedores e parceiros ====\n");
    printf("1 - criar fornecedor\n");
    printf("2 - criar parceiro\n");
    printf("3 - exibir registro (id)\n");
    printf("4 - listar todos\n");
    printf("5 - atualizar fornecedor\n");
    printf("6 - atualizar parceiro\n");
    printf("7 - deletar registro\n");
    printf("0 - voltar\n");
    printf("escolha: ");
}

void exibir_fornece_e_parce(const Fornecedores_e_parceiros* f) {
    if (!f) {
        printf("registro nao encontrado.\n");
        return;
    }
    printf("\n----------------------------\n");
    printf("id: %d | tipo: %s\n", f->id, (f->tipo == TIPO_CPF ? "Parceiro (CPF)" : "Fornecedor (CNPJ)"));
    printf("nome fantasia: %s\n", f->nome_fantasia);
    printf("razao social: %s\n", f->nome_razao);
    printf("endereco: %s\n", f->endereco);
    if (f->tipo == TIPO_CNPJ) printf("cnpj: %s\n", f->cnpj);
    else printf("cpf: %s\n", f->cpf);
    printf("telefone: %s\n", f->telefone);
    printf("servico: %s\n", servico_para_string(f->servico));
    printf("status: %d\n", f->status);
    printf("----------------------------\n");
}

Fornecedores_e_parceiros ler_dados_fornecedor() {
    Fornecedores_e_parceiros f;
    f.id = 0; 
    f.tipo = TIPO_CNPJ; 

    printf("nome fantasia: "); scanf(" %49[^\n]", f.nome_fantasia);
    while (getchar() != '\n');
    
    printf("razao social: "); scanf(" %99[^\n]", f.nome_razao);
    while (getchar() != '\n');

    printf("endereco: "); scanf(" %255[^\n]", f.endereco);
    while (getchar() != '\n');

    printf("cnpj: "); scanf(" %14[^\n]", f.cnpj);
    while (getchar() != '\n');

    printf("telefone: "); scanf(" %19[^\n]", f.telefone);
    while (getchar() != '\n');

    f.servico = obter_servico_usuario();
    f.status = 1;
    return f;
}

Fornecedores_e_parceiros ler_dados_parceiro() {
    Fornecedores_e_parceiros p;
    p.id = 0; 
    p.tipo = TIPO_CPF; 

    printf("nome completo: "); scanf(" %49[^\n]", p.nome_fantasia); 
    while (getchar() != '\n');
    
    strcpy(p.nome_razao, p.nome_fantasia); 

    printf("endereco: "); scanf(" %255[^\n]", p.endereco);
    while (getchar() != '\n');

    printf("cpf: "); scanf(" %11[^\n]", p.cpf);
    while (getchar() != '\n');

    printf("telefone: "); scanf(" %19[^\n]", p.telefone);
    while (getchar() != '\n');

    p.servico = obter_servico_usuario();
    p.status = 1;
    return p;
}

int ler_id_para_operacao_fornece_e_parce() {
    int id;
    printf("digite o id para a operacao: ");
    if(scanf("%d", &id) != 1) {
        while(getchar() != '\n');
        return -1;
    }
    return id;
}

void exibir_mensagem_fornece_e_parce(const char* msg) {
    printf(">> %s\n", msg);
}

void exibir_todas_fornece_e_parce(NoFornecedores_e_parceiros* lista) {
    NoFornecedores_e_parceiros *atual = lista;
    printf("\n==== lista ====\n");
    while (atual != NULL) {
        if (atual->dados.status == 1) {
            printf("%d - %s (%s)\n", atual->dados.id, atual->dados.nome_fantasia, servico_para_string(atual->dados.servico));
        }
        atual = atual->proximo;
    }
    printf("===============\n");
}

void ler_dados_atualizacao_fornecedor(Fornecedores_e_parceiros* atual, char* nome_fantasia, char* razao_social, char* endereco, char* cnpj, char* telefone, TipoServico* servico) {
    printf("novo nome fantasia (atual: %s): ", atual->nome_fantasia);
    scanf(" %49[^\n]", nome_fantasia);
    while (getchar() != '\n');

    printf("nova razao (atual: %s): ", atual->nome_razao);
    scanf(" %99[^\n]", razao_social);
    while (getchar() != '\n');

    printf("novo endereco (atual: %s): ", atual->endereco);
    scanf(" %255[^\n]", endereco);
    while (getchar() != '\n');

    printf("novo cnpj (atual: %s): ", atual->cnpj);
    scanf(" %14[^\n]", cnpj);
    while (getchar() != '\n');

    printf("novo telefone (atual: %s): ", atual->telefone);
    scanf(" %19[^\n]", telefone);
    while (getchar() != '\n');

    *servico = obter_novo_servico_usuario(atual->servico);
}

void ler_dados_atualizacao_parceiro(Fornecedores_e_parceiros* atual, char* nome_fantasia, char* razao_social, char* endereco, char* cpf, char* telefone, TipoServico* servico) {
    printf("novo nome completo (atual: %s): ", atual->nome_fantasia);
    scanf(" %49[^\n]", nome_fantasia);
    while (getchar() != '\n');

    strcpy(razao_social, nome_fantasia); 

    printf("novo endereco (atual: %s): ", atual->endereco);
    scanf(" %255[^\n]", endereco);
    while (getchar() != '\n');

    printf("novo cpf (atual: %s): ", atual->cpf);
    scanf(" %11[^\n]", cpf);
    while (getchar() != '\n');

    printf("novo telefone (atual: %s): ", atual->telefone);
    scanf(" %19[^\n]", telefone);
    while (getchar() != '\n');

    *servico = obter_novo_servico_usuario(atual->servico);
}