#ifndef FORNECE_E_PARCE_VIEW_H
#define FORNECE_E_PARCE_VIEW_H

#include "../model/fornece_e_parce.h"

// Funções de exibição
void exibir_fornece_e_parce(const Fornecedores_e_parceiros* Fornecedores_e_parceiros);
void exibir_menu_principal_fornece_parce();
void exibir_mensagem_fornece_e_parce(const char* msg);

// Funções de leitura de dados
Fornecedores_e_parceiros ler_dados_fornecedor();
Fornecedores_e_parceiros ler_dados_parceiro();
int ler_id_para_operacao();  // Função original
int ler_id_para_operacao_fornece_e_parce();  // NOVA: para compatibilidade com outros módulos

// Funções auxiliares para serviço
TipoServico obter_servico_usuario();
TipoServico obter_novo_servico_usuario(TipoServico servico_atual);
const char* servico_para_string(TipoServico servico);

// Funções de atualização
void ler_dados_atualizacao_fornecedor(Fornecedores_e_parceiros *atual, 
                                      char *nome_fantasia, char *razao_social, 
                                      char *endereco, char *cnpj, char *telefone, 
                                      TipoServico *servico);

void ler_dados_atualizacao_parceiro(Fornecedores_e_parceiros *atual, 
                                    char *nome_fantasia, char *razao_social, 
                                    char *endereco, char *cpf, char *telefone, 
                                    TipoServico *servico);

#endif