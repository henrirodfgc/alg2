#ifndef FORNECE_E_PARCE_VIEW_H
#define FORNECE_E_PARCE_VIEW_H

#include "../../model/cadastro/fornece_e_parce.h"

// funcoes de exibicao
void exibir_fornece_e_parce(const Fornecedores_e_parceiros* Fornecedores_e_parceiros);
void exibir_menu_principal_fornece_parce();
void exibir_mensagem_fornece_e_parce(const char* msg);
void exibir_todas_fornece_e_parce(NoFornecedores_e_parceiros* lista);

// funcoes de leitura de dados
Fornecedores_e_parceiros ler_dados_fornecedor();
Fornecedores_e_parceiros ler_dados_parceiro();
int ler_id_para_operacao();  
int ler_id_para_operacao_fornece_e_parce(); 

// funcoes auxiliares para servico
TipoServico obter_servico_usuario();
TipoServico obter_novo_servico_usuario(TipoServico servico_atual);
const char* servico_para_string(TipoServico servico);

// funcoes de atualizacao
void ler_dados_atualizacao_fornecedor(Fornecedores_e_parceiros *atual, 
                                      char *nome_fantasia, char *razao_social, 
                                      char *endereco, char *cnpj, char *telefone, 
                                      TipoServico *servico);

void ler_dados_atualizacao_parceiro(Fornecedores_e_parceiros *atual, 
                                      char *nome_fantasia, char *razao_social, 
                                      char *endereco, char *cpf, char *telefone, 
                                      TipoServico *servico);

#endif