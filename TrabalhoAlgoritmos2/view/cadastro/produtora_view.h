#ifndef PRODUTORA_VIEW_H
#define PRODUTORA_VIEW_H

#include "../../model/cadastro/produtora.h"


void exibir_produtora(const Produtora* Produtora);


void exibir_menu_produtora();


Produtora ler_dados_produtora();



void ler_dados_atualizacao_produtora(char* nome_fantasia, char* razao_social, 
                                   char* inscricao_estadual, char* cnpj, 
                                   char* email, char* endereco_completo, 
                                   char* telefone, char* nome_do_responsavel, 
                                   char* telefone_do_responsavel, 
                                   char* margem_de_lucro_padrao);


void exibir_mensagem_produtora(const char* msg);


char* ler_cnpj_para_operacao(const char* operacao);
void exibir_todas_produtoras(NoProdutora* lista);
#endif