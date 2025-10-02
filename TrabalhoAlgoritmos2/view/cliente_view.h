#ifndef CLIENTE_VIEW_H
#define CLIENTE_VIEW_H

#include "../model/cliente.h"

// Mostra dados de um cliente
void exibir_cliente(const Cliente* cliente);

// Exibe o menu principal e retorna a opção escolhida
int exibir_menu();

// Lê os dados de um cliente e RETORNA um Cliente preenchido
Cliente ler_dados_cliente();

// Pega dados atualizados de cliente (mantemos por referência para comparar)
// CORREÇÃO: Adicionar todos os ponteiros de retorno
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, int* cpf, int* cnpj);

// Exibe mensagem genérica
void exibir_mensagem(const char* msg);

#endif