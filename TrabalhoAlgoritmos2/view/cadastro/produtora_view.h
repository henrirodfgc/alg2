#ifndef PRODUTORA_VIEW_H
#define PRODUTORA_VIEW_H

#include "../../model/cadastro/produtora.h"

void exibir_produtora(const Produtora* p);
int exibir_menu_produtora();
Produtora ler_dados_produtora();

// MUDOU: O ultimo parametro eh char*
void ler_dados_atualizacao_produtora(char* nome_fantasia, char* razao_social, 
                                   char* inscricao_estadual, char* endereco, 
                                   char* telefone, char* email, 
                                   char* nome_resp, char* tel_resp, 
                                   char* margem); // CHAR*

void exibir_mensagem_produtora(const char* msg);
void exibir_todas_produtoras(NoProdutora* lista);

int ler_cnpj_para_operacao(const char* operacao);

#endif