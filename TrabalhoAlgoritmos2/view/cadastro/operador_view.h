#ifndef OPERADOR_VIEW_H
#define OPERADOR_VIEW_H

#include "../../model/cadastro/operador.h"

void exibir_operador(const Operador* Operador);

void exibir_menu_operador();

Operador ler_dados_operador();

void ler_dados_atualizacao_operador(int* codigo, char* nome, char* usuario, char* senha);

void exibir_mensagem_operador(const char* msg);

int ler_codigo_para_a_operacao(const char* operacao);

#endif