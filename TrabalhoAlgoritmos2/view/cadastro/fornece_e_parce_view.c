#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornece_e_parce_view.h"

const char* servico_para_string(TipoServico servico) {
    switch(servico) {
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
    getchar();
    
    switch(opcao_servico) {
        case 1: return SERVICO_BUFFET;
        case 2: return SERVICO_SEGURANCA;
        case 3: return SERVICO_ATRACAO_MUSICAL;
        default: 
            printf("opcao invalida, definindo padrao (Buffet).\n");
            return SERVICO_BUFFET;
    }
}

TipoServico obter_novo_servico_usuario(TipoServico servico_atual) {
    int alterar;
    printf("deseja alterar o servico (atual: %s)? (1-sim / 0-nao): ", servico_para_string(servico_atual));
    scanf("%d", &alterar);
    getchar();

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
    if(!f) return;
    char tipo_str[20];
    if(f->tipo == TIPO_CNPJ) strcpy(tipo_str, "Fornecedor");
    else strcpy(tipo_str, "Parceiro");

    printf("\n----------------------------\n");
    printf("id: %d | tipo: %s\n", f->id, tipo_str);
    printf("nome fantasia: %s\n", f->nome_fantasia);
    printf("razao social: %s\n", f->nome_razao);
    printf("endereco: %s\n", f->endereco);
    if(f->tipo == TIPO_CNPJ) printf("cnpj: %s\n", f->cnpj);
    else printf("cpf: %s\n", f->cpf);
    printf("telefone: %s\n", f->telefone);
    printf("servico: %s\n", servico_para_string(f->servico));
    printf("status: %d\n", f->status);
    printf("----------------------------\n");
}

Fornecedores_e_parceiros ler_dados_fornecedor() {
    Fornecedores_e_parceiros f;
    printf("\nid: "); scanf("%d", &f.id); getchar();
    printf("nome fantasia: "); fgets(f.nome_fantasia, 50, stdin); f.nome_fantasia[strcspn(f.nome_fantasia, "\n")] = 0;
    printf("razao social: "); fgets(f.nome_razao, 100, stdin); f.nome_razao[strcspn(f.nome_razao, "\n")] = 0;
    printf("endereco: "); fgets(f.endereco, 256, stdin); f.endereco[strcspn(f.endereco, "\n")] = 0;
    printf("cnpj: "); fgets(f.cnpj, 15, stdin); f.cnpj[strcspn(f.cnpj, "\n")] = 0;
    printf("telefone: "); fgets(f.telefone, 20, stdin); f.telefone[strcspn(f.telefone, "\n")] = 0;
    f.servico = obter_servico_usuario();
    f.tipo = TIPO_CNPJ;
    f.status = 1;
    return f;
}

Fornecedores_e_parceiros ler_dados_parceiro() {
    Fornecedores_e_parceiros p;
    printf("\nid: "); scanf("%d", &p.id); getchar();
    printf("nome fantasia: "); fgets(p.nome_fantasia, 50, stdin); p.nome_fantasia[strcspn(p.nome_fantasia, "\n")] = 0;
    printf("nome completo: "); fgets(p.nome_razao, 100, stdin); p.nome_razao[strcspn(p.nome_razao, "\n")] = 0;
    printf("endereco: "); fgets(p.endereco, 256, stdin); p.endereco[strcspn(p.endereco, "\n")] = 0;
    printf("cpf: "); fgets(p.cpf, 12, stdin); p.cpf[strcspn(p.cpf, "\n")] = 0;
    printf("telefone: "); fgets(p.telefone, 20, stdin); p.telefone[strcspn(p.telefone, "\n")] = 0;
    p.servico = obter_servico_usuario();
    p.tipo = TIPO_CPF;
    p.status = 1;
    return p;
}

int ler_id_para_operacao_fornece_e_parce() {
    int id;
    printf("digite o id para a operacao: ");
    scanf("%d", &id);
    getchar();
    return id;
}

void exibir_mensagem_fornece_e_parce(const char* msg) {
    printf(">> %s\n", msg);
}

void exibir_todas_fornece_e_parce(NoFornecedores_e_parceiros* lista) {
    NoFornecedores_e_parceiros *atual = lista;
    if (atual == NULL) {
        printf("nenhum registro encontrado.\n");
        return;
    }
    printf("\n==== lista ====\n");
    while (atual != NULL) {
        if(atual->dados.status == 1) {
            exibir_fornece_e_parce(&(atual->dados));
        }
        atual = atual->proximo;
    }
    printf("===============\n");
}

void ler_dados_atualizacao_fornecedor(Fornecedores_e_parceiros *atual, char *nome_fantasia, char *razao_social, char *endereco, char *cnpj, char *telefone, TipoServico *servico) {
    printf("novo nome fantasia (atual: %s): ", atual->nome_fantasia);
    fgets(nome_fantasia, 50, stdin);
    nome_fantasia[strcspn(nome_fantasia, "\n")] = 0;
    if(strlen(nome_fantasia) == 0) strcpy(nome_fantasia, atual->nome_fantasia);

    printf("nova razao (atual: %s): ", atual->nome_razao);
    fgets(razao_social, 100, stdin);
    razao_social[strcspn(razao_social, "\n")] = 0;
    if(strlen(razao_social) == 0) strcpy(razao_social, atual->nome_razao);

    printf("novo endereco (atual: %s): ", atual->endereco);
    fgets(endereco, 256, stdin);
    endereco[strcspn(endereco, "\n")] = 0;
    if(strlen(endereco) == 0) strcpy(endereco, atual->endereco);

    printf("novo cnpj (atual: %s): ", atual->cnpj);
    fgets(cnpj, 15, stdin);
    cnpj[strcspn(cnpj, "\n")] = 0;
    if(strlen(cnpj) == 0) strcpy(cnpj, atual->cnpj);

    printf("novo telefone (atual: %s): ", atual->telefone);
    fgets(telefone, 20, stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    if(strlen(telefone) == 0) strcpy(telefone, atual->telefone);

    *servico = obter_novo_servico_usuario(atual->servico);
}

void ler_dados_atualizacao_parceiro(Fornecedores_e_parceiros *atual, char *nome_fantasia, char *razao_social, char *endereco, char *cpf, char *telefone, TipoServico *servico) {
    printf("novo nome fantasia (atual: %s): ", atual->nome_fantasia);
    fgets(nome_fantasia, 50, stdin);
    nome_fantasia[strcspn(nome_fantasia, "\n")] = 0;
    if(strlen(nome_fantasia) == 0) strcpy(nome_fantasia, atual->nome_fantasia);

    printf("novo nome completo (atual: %s): ", atual->nome_razao);
    fgets(razao_social, 100, stdin);
    razao_social[strcspn(razao_social, "\n")] = 0;
    if(strlen(razao_social) == 0) strcpy(razao_social, atual->nome_razao);

    printf("novo endereco (atual: %s): ", atual->endereco);
    fgets(endereco, 256, stdin);
    endereco[strcspn(endereco, "\n")] = 0;
    if(strlen(endereco) == 0) strcpy(endereco, atual->endereco);

    printf("novo cpf (atual: %s): ", atual->cpf);
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    if(strlen(cpf) == 0) strcpy(cpf, atual->cpf);

    printf("novo telefone (atual: %s): ", atual->telefone);
    fgets(telefone, 20, stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    if(strlen(telefone) == 0) strcpy(telefone, atual->telefone);

    *servico = obter_novo_servico_usuario(atual->servico);
}