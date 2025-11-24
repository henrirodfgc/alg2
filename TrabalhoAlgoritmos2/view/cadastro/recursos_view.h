#ifndef RECURSOS_VIEW_H
#define RECURSOS_VIEW_H

#include "../../model/cadastro/recursos.h" //precisa do molde da struct

//funcoes de interface (view) do modulo de recursos
//so pra interagir com o usuario

//exibe o menu e pega a escolha do usuario
int exibir_menu_recursos();

//pega todos os dados pra criar um novo equipamento
Equipamento ler_dados_recurso();

//pega so os dados novos pra atualizar
void ler_dados_atualizacao_recurso(char* descricao, char* categoria, int* quantidade_estoque, float* preco_custo, float* valor_locacao);

//mostra um equipamento com todos os campos bonitinho
void exibir_recurso(const Equipamento* recurso);

//funcao pra ler o codigo que o user quer usar pra alguma operacao
int ler_codigo_para_operacao_recursos(const char* operacao);

//mostra uma mensagem simples na tela
void exibir_mensagem_recursos(const char* msg);

//funcoes auxiliares pra lista
void exibir_cabecalho_lista_recursos();
void exibir_rodape_lista_recursos();

#endif