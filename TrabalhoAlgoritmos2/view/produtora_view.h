#ifndef PRODUTORA_VIEW_H
#define PRODUTORA_VIEW_H

#include "../model/produtora.h"

// =============================================
// ARQUIVO: produtora_view.h
// DESCRIÇÃO: Interface de usuário para o módulo de Produtoras
// OBJETIVO: Funções para interação com o usuário (entrada e saída de dados)
// =============================================

// =============================================
// FUNÇÃO: exibir_produtora
// OBJETIVO: Exibe os dados de uma produtora na tela
// PARÂMETROS:
//   - Produtora: Ponteiro para a estrutura Produtora a ser exibida
// COMPORTAMENTO: 
//   - Se o ponteiro for NULL, exibe mensagem de "não encontrada"
//   - Se válido, formata e exibe todos os dados da produtora
// =============================================
void exibir_produtora(const Produtora* Produtora);

// =============================================
// FUNÇÃO: exibir_menu_produtora
// OBJETIVO: Exibe o menu de opções para gerenciamento de produtoras
// COMPORTAMENTO:
//   - Mostra todas as operações disponíveis (CRUD)
//   - Formata visualmente o menu para melhor legibilidade
//   - Não coleta a escolha do usuário (apenas exibe)
// =============================================
void exibir_menu_produtora();

// =============================================
// FUNÇÃO: ler_dados_produtora
// OBJETIVO: Coleta todos os dados necessários para criar uma nova produtora
// RETORNO: Estrutura Produtora preenchida com os dados informados pelo usuário
// COMPORTAMENTO:
//   - Solicita cada campo individualmente
//   - Valida formatos básicos (quando aplicável)
//   - Retorna estrutura completamente preenchida
// =============================================
Produtora ler_dados_produtora();

// =============================================
// FUNÇÃO: ler_dados_atualizacao_produtora
// OBJETIVO: Coleta novos dados para atualizar uma produtora existente
// PARÂMETROS:
//   - nome_fantasia: Buffer para armazenar novo nome fantasia
//   - razao_social: Buffer para armazenar nova razão social
//   - inscricao_estadual: Buffer para armazenar nova inscrição estadual
//   - cnpj: Buffer para armazenar novo CNPJ
//   - email: Buffer para armazenar novo e-mail
//   - endereco_completo: Buffer para armazenar novo endereço
//   - telefone: Buffer para armazenar novo telefone
//   - nome_do_responsavel: Buffer para armazenar novo nome do responsável
//   - telefone_do_responsavel: Buffer para armazenar novo telefone do responsável
//   - margem_de_lucro_padrao: Buffer para armazenar nova margem de lucro
// COMPORTAMENTO:
//   - Preenche todos os buffers com os novos dados informados pelo usuário
//   - Permite ao usuário atualizar parcial ou totalmente os dados
// =============================================
void ler_dados_atualizacao_produtora(char* nome_fantasia, char* razao_social, 
                                   char* inscricao_estadual, char* cnpj, 
                                   char* email, char* endereco_completo, 
                                   char* telefone, char* nome_do_responsavel, 
                                   char* telefone_do_responsavel, 
                                   char* margem_de_lucro_padrao);

// =============================================
// FUNÇÃO: exibir_mensagem_produtora
// OBJETIVO: Exibe mensagens de feedback para o usuário
// PARÂMETROS:
//   - msg: String contendo a mensagem a ser exibida
// COMPORTAMENTO:
//   - Usada para mensagens de sucesso, erro, alertas
//   - Formata a mensagem de maneira padronizada
//   - Exemplos: "Produtora cadastrada com sucesso!", "ERRO: CNPJ não encontrado"
// =============================================
void exibir_mensagem_produtora(const char* msg);

// =============================================
// FUNÇÃO: ler_cnpj_para_operacao
// OBJETIVO: Solicita e retorna um CNPJ para operações específicas
// PARÂMETROS:
//   - operacao: String descrevendo a operação (ex: "buscar", "atualizar", "deletar")
// RETORNO: String alocada dinamicamente contendo o CNPJ informado
// COMPORTAMENTO:
//   - Exibe prompt contextualizado com a operação
//   - Lê o CNPJ digitado pelo usuário
//   - Retorna string que deve ser liberada com free() após o uso
//   - Exemplo: "Digite o CNPJ para buscar: "
// =============================================
char* ler_cnpj_para_operacao(const char* operacao);

#endif