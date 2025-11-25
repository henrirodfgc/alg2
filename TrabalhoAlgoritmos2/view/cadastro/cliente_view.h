#ifndef CLIENTE_VIEW_H
#define CLIENTE_VIEW_H

#include "../../model/cadastro/cliente.h"

//mostra os dados de um client ou avisa se n existe
void exibir_cliente(const Cliente* cliente);

//exibe o menu e pega a escolha do user
int exibir_menu();

//pega os dados pra criar um client e devolve a struct preenchida
Cliente ler_dados_cliente();

//pega os dados novos pra atualizar
void ler_dados_atualizacao(char* nome_cliente, int* idade, char* endereco, char* nome_razao, char* email, char* cpf, char* cnpj, char* telefone, char* nome_contato);

//mostra uma mensagem na tela tipo "sucesso" ou "erro"
void exibir_mensagem(const char* msg);

//função pra ler o ID q o user quer usar pra alguma operação
int ler_id_para_operacao(const char* operacao);

#endif