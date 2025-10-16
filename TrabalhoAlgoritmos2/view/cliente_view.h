#ifndef CLIENTE_VIEW_H
#define CLIENTE_VIEW_H

#include "../model/cliente.h"

// =============================================
// FUNÇÕES DE INTERFACE (VIEW)
// Só pra interagir com o usuário
// =============================================

// Mostra os dados de um client ou avisa se n existe
void exibir_cliente(const Cliente* cliente);

// Exibe o menu e pega a escolha do user
int exibir_menu();

// Pega os dados pra criar um client e devolve a struct preenchida
Cliente ler_dados_cliente();

// Pega os dados novos pra atualizar
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, char* cpf, char* cnpj, char* telefone, char* nome_contato);

// Mostra uma mensagem na tela tipo "sucesso" ou "erro"
void exibir_mensagem(const char* msg);

// Função pra ler o ID q o user quer usar pra alguma operação
int ler_id_para_operacao(const char* operacao);

#endif