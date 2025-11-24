#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornece_e_parce_view.h"

// =============================================
// FUNÇÕES AUXILIARES PARA SERVIÇO (VIEW)
// =============================================

// Função para converter enum serviço em string
const char* servico_para_string(TipoServico servico) {
    switch(servico) {
        case SERVICO_BUFFET: return "Buffet";
        case SERVICO_SEGURANCA: return "Segurança";
        case SERVICO_ATRACAO_MUSICAL: return "Atração Musical";
        default: return "Desconhecido";
    }
}

// Função para exibir menu de serviços e obter escolha do usuário
TipoServico obter_servico_usuario() {
    int opcao_servico;
    
    printf("\nSelecione o serviço:\n");
    printf("1 - Buffet\n");
    printf("2 - Segurança\n");
    printf("3 - Atração Musical\n");
    printf("Escolha: ");
    scanf("%d", &opcao_servico);
    getchar();
    
    switch(opcao_servico) {
        case 1: return SERVICO_BUFFET;
        case 2: return SERVICO_SEGURANCA;
        case 3: return SERVICO_ATRACAO_MUSICAL;
        default: 
            printf("Opção inválida! Definindo como Buffet.\n");
            return SERVICO_BUFFET;
    }
}

// Função para obter novo serviço do usuário (para atualizações)
TipoServico obter_novo_servico_usuario(TipoServico servico_atual) {
    int opcao_servico;
    const char* servico_atual_str = servico_para_string(servico_atual);
    
    printf("\nServiço atual: %s\n", servico_atual_str);
    printf("Novo Serviço:\n");
    printf("1 - Buffet\n");
    printf("2 - Segurança\n");
    printf("3 - Atração Musical\n");
    printf("4 - Manter serviço atual\n");
    printf("Escolha: ");
    scanf("%d", &opcao_servico);
    getchar();
    
    switch(opcao_servico) {
        case 1: return SERVICO_BUFFET;
        case 2: return SERVICO_SEGURANCA;
        case 3: return SERVICO_ATRACAO_MUSICAL;
        case 4: return servico_atual;
        default: 
            printf("Opção inválida! Mantendo serviço atual.\n");
            return servico_atual;
    }
}

// =============================================
// FUNÇÃO: exibir_menu_principal_fornece_parce
// OBJETIVO: Exibir menu principal unificado
// =============================================
void exibir_menu_principal_fornece_parce() {
    printf("\n+===================================+\n");
    printf("|   SISTEMA FORNEC. E PARCEIROS    |\n");
    printf("+===================================+\n");
    printf("| 1 - Cadastrar Fornecedor         |\n");
    printf("| 2 - Cadastrar Parceiro           |\n");
    printf("| 3 - Buscar por ID (Ambos)        |\n");
    printf("| 4 - Listar Todos                 |\n");
    printf("| 5 - Atualizar Fornecedor         |\n");
    printf("| 6 - Atualizar Parceiro           |\n");
    printf("| 7 - Excluir Registro             |\n");
    printf("| 0 - Voltar ao Menu Principal     |\n");
    printf("+===================================+\n");
    printf("Escolha: ");
}

// =============================================
// FUNÇÃO: exibir_fornece_e_parce
// OBJETIVO: Exibir dados de um fornecedor/parceiro
// =============================================
void exibir_fornece_e_parce(const Fornecedores_e_parceiros* registro) {
    if (registro == NULL) {
        printf("Registro inválido!\n");
        return;
    }
    
    printf("\n+-----------------------------------+\n");
    printf("|          DADOS CADASTRADOS        |\n");
    printf("+-----------------------------------+\n");
    printf("| ID: %-29d |\n", registro->id);
    printf("| Nome Fantasia: %-19s |\n", registro->nome_fantasia);
    printf("| Razão Social: %-20s |\n", registro->nome_razao);
    printf("| Endereço: %-23s |\n", registro->endereco);
    printf("| Telefone: %-23s |\n", registro->telefone);
    printf("| Serviço: %-24s |\n", servico_para_string(registro->servico));
    
    if (registro->tipo == TIPO_CPF) {
        printf("| CPF: %-26s |\n", registro->cpf);
        printf("| Tipo: Parceiro (Pessoa Física)   |\n");
    } else {
        printf("| CNPJ: %-25s |\n", registro->cnpj);
        printf("| Tipo: Fornecedor (Pessoa Jurídica)|\n");
    }
    printf("+-----------------------------------+\n");
}

// =============================================
// FUNÇÃO: ler_dados_fornecedor
// OBJETIVO: Ler dados específicos para fornecedor
// =============================================
Fornecedores_e_parceiros ler_dados_fornecedor() {
    Fornecedores_e_parceiros novo;
    
    printf("\n+-----------------------------+\n");
    printf("|   CADASTRO DE FORNECEDOR   |\n");
    printf("+-----------------------------+\n");
    
    printf("ID: ");
    scanf("%d", &novo.id);
    getchar();
    
    printf("Nome Fantasia: ");
    fgets(novo.nome_fantasia, sizeof(novo.nome_fantasia), stdin);
    novo.nome_fantasia[strcspn(novo.nome_fantasia, "\n")] = 0;
    
    printf("Razão Social: ");
    fgets(novo.nome_razao, sizeof(novo.nome_razao), stdin);
    novo.nome_razao[strcspn(novo.nome_razao, "\n")] = 0;
    
    printf("Endereço: ");
    fgets(novo.endereco, sizeof(novo.endereco), stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = 0;
    
    printf("Telefone: ");
    fgets(novo.telefone, sizeof(novo.telefone), stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = 0;
    
    printf("CNPJ: ");
    fgets(novo.cnpj, sizeof(novo.cnpj), stdin);
    novo.cnpj[strcspn(novo.cnpj, "\n")] = 0;
    
    // SERVIÇO: Agora toda a lógica está na view
    novo.servico = obter_servico_usuario();
    
    // Define como fornecedor (CNPJ)
    novo.tipo = TIPO_CNPJ;
    strcpy(novo.cpf, "");
    
    return novo;
}

// =============================================
// FUNÇÃO: ler_dados_parceiro
// OBJETIVO: Ler dados específicos para parceiro
// =============================================
Fornecedores_e_parceiros ler_dados_parceiro() {
    Fornecedores_e_parceiros novo;
    
    printf("\n+-----------------------------+\n");
    printf("|    CADASTRO DE PARCEIRO    |\n");
    printf("+-----------------------------+\n");
    
    printf("ID: ");
    scanf("%d", &novo.id);
    getchar();
    
    printf("Nome Fantasia: ");
    fgets(novo.nome_fantasia, sizeof(novo.nome_fantasia), stdin);
    novo.nome_fantasia[strcspn(novo.nome_fantasia, "\n")] = 0;
    
    printf("Razão Social: ");
    fgets(novo.nome_razao, sizeof(novo.nome_razao), stdin);
    novo.nome_razao[strcspn(novo.nome_razao, "\n")] = 0;
    
    printf("Endereço: ");
    fgets(novo.endereco, sizeof(novo.endereco), stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = 0;
    
    printf("Telefone: ");
    fgets(novo.telefone, sizeof(novo.telefone), stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = 0;
    
    printf("CPF: ");
    fgets(novo.cpf, sizeof(novo.cpf), stdin);
    novo.cpf[strcspn(novo.cpf, "\n")] = 0;
    
    // SERVIÇO: Agora toda a lógica está na view
    novo.servico = obter_servico_usuario();
    
    // Define como parceiro (CPF)
    novo.tipo = TIPO_CPF;
    strcpy(novo.cnpj, "");
    
    return novo;
}

// =============================================
// FUNÇÃO: ler_dados_atualizacao_fornecedor
// OBJETIVO: Ler dados para atualização de fornecedor
// =============================================
void ler_dados_atualizacao_fornecedor(Fornecedores_e_parceiros *atual, 
                                      char *nome_fantasia, char *razao_social, 
                                      char *endereco, char *cnpj, char *telefone, 
                                      TipoServico *servico) {
    
    printf("Novo Nome Fantasia (atual: %s): ", atual->nome_fantasia);
    fgets(nome_fantasia, 50, stdin);
    nome_fantasia[strcspn(nome_fantasia, "\n")] = 0;
    if (strlen(nome_fantasia) == 0) {
        strcpy(nome_fantasia, atual->nome_fantasia);
    }

    printf("Nova Razão Social (atual: %s): ", atual->nome_razao);
    fgets(razao_social, 100, stdin);
    razao_social[strcspn(razao_social, "\n")] = 0;
    if (strlen(razao_social) == 0) {
        strcpy(razao_social, atual->nome_razao);
    }

    printf("Novo Endereço (atual: %s): ", atual->endereco);
    fgets(endereco, 256, stdin);
    endereco[strcspn(endereco, "\n")] = 0;
    if (strlen(endereco) == 0) {
        strcpy(endereco, atual->endereco);
    }

    printf("Novo CNPJ (atual: %s): ", atual->cnpj);
    fgets(cnpj, 15, stdin);
    cnpj[strcspn(cnpj, "\n")] = 0;
    if (strlen(cnpj) == 0) {
        strcpy(cnpj, atual->cnpj);
    }

    printf("Novo Telefone (atual: %s): ", atual->telefone);
    fgets(telefone, 20, stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    if (strlen(telefone) == 0) {
        strcpy(telefone, atual->telefone);
    }

    // SERVIÇO: Lógica movida para a view
    *servico = obter_novo_servico_usuario(atual->servico);
}

// =============================================
// FUNÇÃO: ler_dados_atualizacao_parceiro
// OBJETIVO: Ler dados para atualização de parceiro
// =============================================
void ler_dados_atualizacao_parceiro(Fornecedores_e_parceiros *atual, 
                                    char *nome_fantasia, char *razao_social, 
                                    char *endereco, char *cpf, char *telefone, 
                                    TipoServico *servico) {
    
    printf("Novo Nome Fantasia (atual: %s): ", atual->nome_fantasia);
    fgets(nome_fantasia, 50, stdin);
    nome_fantasia[strcspn(nome_fantasia, "\n")] = 0;
    if (strlen(nome_fantasia) == 0) {
        strcpy(nome_fantasia, atual->nome_fantasia);
    }

    printf("Nova Razão Social (atual: %s): ", atual->nome_razao);
    fgets(razao_social, 100, stdin);
    razao_social[strcspn(razao_social, "\n")] = 0;
    if (strlen(razao_social) == 0) {
        strcpy(razao_social, atual->nome_razao);
    }

    printf("Novo Endereço (atual: %s): ", atual->endereco);
    fgets(endereco, 256, stdin);
    endereco[strcspn(endereco, "\n")] = 0;
    if (strlen(endereco) == 0) {
        strcpy(endereco, atual->endereco);
    }

    printf("Novo CPF (atual: %s): ", atual->cpf);
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    if (strlen(cpf) == 0) {
        strcpy(cpf, atual->cpf);
    }

    printf("Novo Telefone (atual: %s): ", atual->telefone);
    fgets(telefone, 20, stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    if (strlen(telefone) == 0) {
        strcpy(telefone, atual->telefone);
    }

    // SERVIÇO: Lógica movida para a view
    *servico = obter_novo_servico_usuario(atual->servico);
}

// =============================================
// FUNÇÃO: exibir_mensagem_fornece_e_parce
// OBJETIVO: Exibir mensagem formatada
// =============================================
void exibir_mensagem_fornece_e_parce(const char* msg) {
    printf("\n+-----------------------------------+\n");
    printf("| %-33s |\n", msg);
    printf("+-----------------------------------+\n");
}

// =============================================
// FUNÇÃO: ler_id_para_operacao
// OBJETIVO: Ler ID do usuário para operações
// =============================================
int ler_id_para_operacao_fornece_e_parce() {
    int id;
    printf("Digite o ID: ");
    scanf("%d", &id);
    getchar();
    return id;
}