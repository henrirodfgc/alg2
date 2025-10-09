#ifndef CLIENTE_VIEW_H
#define CLIENTE_VIEW_H

#include "../model/cliente.h"

//Mostra dados de um cliente (ou mensagem de inexistente se for NULL)
void exibir_cliente(const Cliente* cliente);

//Exibe o menu principal e retorna a opção escolhida
int exibir_menu();

//Lê os dados de um cliente e RETORNA um Cliente preenchido
Cliente ler_dados_cliente();

//Pega dados atualizados de cliente
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, char* cpf, char* cnpj, char* telefone, char* nome_contato);

//Exibe mensagem genérica
void exibir_mensagem(const char* msg);

//Função auxiliar para o Controller ler o ID do usuário
int ler_id_para_operacao(const char* operacao);

#endif