#ifndef EQUIPE_VIEW_H
#define EQUIPE_VIEW_H

#include "../model/equipe.h"

// =============================================
// FUNÇÕES DE INTERFACE (VIEW) DA EQUIPE
// Só pra interagir com o usuário
// =============================================

// Exibe o menu e pega a escolha do usuário para o módulo Equipe
int exibir_menu_equipe();

// Pega os dados pra criar um novo membro e devolve a struct preenchida
MembroEquipe ler_dados_membro();

// Pega os dados novos pra atualizar
void ler_dados_atualizacao_membro(char* nome, char* cpf, char* funcao, float* valor_diaria_hora);

// Mostra um membro da equipe com todos os campos bonitinho
void exibir_membro(const MembroEquipe* membro);

// Função pra ler o CÓDIGO que o user quer usar pra alguma operação
int ler_codigo_para_operacao(const char* operacao);

// Mostra uma mensagem simples na tela tipo "sucesso" ou "erro"
void exibir_mensagem_equipe(const char* msg);


#endif
