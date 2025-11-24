#ifndef PRODUTORA_CONTROLLER_H
#define PRODUTORA_CONTROLLER_H

// =============================================
// ARQUIVO: produtora_controller.h
// DESCRIÇÃO: Controlador principal do módulo de Produtoras
// OBJETIVO: Orquestrar a comunicação entre Model e View
// =============================================

// =============================================
// FUNÇÃO: iniciar_produtora
// OBJETIVO: Inicializar e gerenciar o fluxo principal do sistema de produtoras
// COMPORTAMENTO:
//   - Controla o loop principal do menu
//   - Coordena as operações entre Model (dados) e View (interface)
//   - Gerencia o ciclo de vida da aplicação
//   - Processa as escolhas do usuário e direciona para as funções apropriadas
// FLUXO ESPERADO:
//   1. Exibe menu de opções
//   2. Captura escolha do usuário
//   3. Executa operação correspondente (CRUD)
//   4. Mantém o loop até usuário escolher sair
// DEPENDÊNCIAS:
//   - Model (produtora.h): Operações de dados e lógica de negócio
//   - View (produtora_view.h): Interface com usuário e exibição
// =============================================
void iniciar_produtora();

#endif