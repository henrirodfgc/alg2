#include "fornece_e_parce_controller.h"
#include "../model/fornece_e_parce.h"
#include "../view/fornece_e_parce_view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciar_fornecedor_e_parceiro() {
  // Inicialização das variáveis do controlador
  NoFornecedores_e_parceiros *listaFornecedores_e_parceiros =
      NULL;     // Lista encadeada (inicia vazia)
  int opcao;    // Armazena a escolha do usuário no menu
  int id_busca; // ID para operações de busca/atualização/exclusão
  Fornecedores_e_parceiros temp; // Estrutura temporária para novos dados

  // =============================================
  // LOOP PRINCIPAL DA APLICAÇÃO
  // Mantém o sistema rodando até usuário escolher sair
  // =============================================
  do {
    // Exibe o menu de opções para o usuário
    exibir_menu_principal_fornece_parce();

    // Solicita e lê a opção do usuário
    scanf("%d", &opcao);
    getchar(); // Limpar buffer

    // =============================================
    // PROCESSAMENTO DAS OPÇÕES DO MENU
    // =============================================
    switch (opcao) {
    // =============================================
    // CASO 1: CADASTRAR FORNECEDOR
    // =============================================
    case 1: {
      // Coleta dados do novo fornecedor
      temp = ler_dados_fornecedor();

      // Verifica se já existe registro com o mesmo ID
      if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros,
                                        temp.id) != NULL) {
        exibir_mensagem_fornece_e_parce(
            "ERRO: Já existe um registro com este ID. Tente novamente");
        break;
      }
      else {
        // Adiciona novo fornecedor na lista
        listaFornecedores_e_parceiros =
            adicionar_fornecedor_na_lista(listaFornecedores_e_parceiros, temp);
        exibir_mensagem_fornece_e_parce("Fornecedor cadastrado com sucesso");
      }
      break;
    }

    // =============================================
    // CASO 2: CADASTRAR PARCEIRO
    // =============================================
    case 2: {
      // Coleta dados do novo parceiro
      temp = ler_dados_parceiro();

      // Verifica se já existe registro com o mesmo ID
      if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros,
                                        temp.id) != NULL) {
        exibir_mensagem_fornece_e_parce(
            "ERRO: Já existe um registro com este ID. Tente novamente");
        break;
      }
      else {
        // Adiciona novo parceiro na lista
        listaFornecedores_e_parceiros =
            adicionar_parceiros_na_lista(listaFornecedores_e_parceiros, temp);
        exibir_mensagem_fornece_e_parce("Parceiro cadastrado com sucesso");
      }
      break;
    }

    // =============================================
    // CASO 3: BUSCAR POR ID (AMBOS)
    // =============================================
    case 3: {
      // Solicita ID do registro a ser buscado
      id_busca = ler_id_para_operacao_fornece_e_parce();

      // Busca registro pelo ID
      Fornecedores_e_parceiros *registro_encontrado =
          buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros,
                                        id_busca);

      if (registro_encontrado != NULL) {
        exibir_fornece_e_parce(registro_encontrado); // Exibe dados formatados
      }
      else {
        exibir_mensagem_fornece_e_parce("Registro não encontrado");
      }
      break;
    }

    // =============================================
    // CASO 4: LISTAR TODOS OS REGISTROS
    // =============================================
    case 4: {
      exibir_todas_fornece_e_parce(
          listaFornecedores_e_parceiros); // Exibe lista completa
      break;
    }

    // =============================================
    // CASO 5: ATUALIZAR FORNECEDOR
    // =============================================
    case 5: {
      // Solicita ID do fornecedor a ser atualizado
      id_busca = ler_id_para_operacao_fornece_e_parce(); 
    
    Fornecedores_e_parceiros *fornecedor_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);

    if (fornecedor_encontrado == NULL) {
        exibir_mensagem_fornece_e_parce("Nenhum fornecedor cadastrado com este ID");
    } else if (fornecedor_encontrado->tipo != TIPO_CNPJ) {
        exibir_mensagem_fornece_e_parce("Este ID pertence a um parceiro, não a um fornecedor");
    } else {
        // VIEW: Toda a interação com usuário está na view
        char nome_fantasia[50], razao_social[100], endereco[256];
        char cnpj[15], telefone[20];
        TipoServico servico;

        ler_dados_atualizacao_fornecedor(fornecedor_encontrado, nome_fantasia, razao_social, 
                                        endereco, cnpj, telefone, &servico);

        // MODEL: Apenas chamada da função de atualização
        atualizar_fornecedor_por_id(listaFornecedores_e_parceiros, id_busca,  
                                    nome_fantasia, razao_social, endereco,   
                                    cnpj, telefone, servico);
        
        exibir_mensagem_fornece_e_parce("Fornecedor atualizado com sucesso");
    }
    break;
}
    

    // =============================================
    // CASO 6: ATUALIZAR PARCEIRO
    // =============================================
    case 6: {
     id_busca = ler_id_para_operacao_fornece_e_parce(); 
    
    Fornecedores_e_parceiros *parceiro_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);

    if (parceiro_encontrado == NULL) {
        exibir_mensagem_fornece_e_parce("Nenhum parceiro cadastrado com este ID");
    } else if (parceiro_encontrado->tipo != TIPO_CPF) {
        exibir_mensagem_fornece_e_parce("Este ID pertence a um fornecedor, não a um parceiro");
    } else {
        // VIEW: Toda a interação com usuário está na view
        char nome_fantasia[50], razao_social[100], endereco[256];
        char cpf[12], telefone[20];
        TipoServico servico;
        
        ler_dados_atualizacao_parceiro(parceiro_encontrado, nome_fantasia, razao_social, 
                                      endereco, cpf, telefone, &servico);
        // MODEL: Apenas chamada da função de atualização
        atualizar_parceiro_por_id(listaFornecedores_e_parceiros, id_busca,  
                                  nome_fantasia, razao_social, endereco,   
                                  cpf, telefone, servico);
        
        exibir_mensagem_fornece_e_parce("Parceiro atualizado com sucesso");
    }
    break;
}

    // =============================================
    // CASO 7: EXCLUIR REGISTRO
    // =============================================
    case 7: {
      // Solicita ID do registro a ser deletado
      id_busca = ler_id_para_operacao_fornece_e_parce();

      // Verifica se o registro existe antes de tentar deletar
      if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros,
                                        id_busca) == NULL) {
        exibir_mensagem_fornece_e_parce(
            "Nenhum registro para deletar com este ID");
        break;
      }

      // Remove registro da lista
      listaFornecedores_e_parceiros = deletar_fornece_e_parce_por_id(
          listaFornecedores_e_parceiros, id_busca);
      exibir_mensagem_fornece_e_parce("Registro deletado com sucesso");
      break;
    }

    // =============================================
    // CASO 0: SAIR DO SISTEMA
    // =============================================
    case 0:
      exibir_mensagem_fornece_e_parce(
          "Saindo do sistema de fornecedores e parceiros...");
      break;

    // =============================================
    // CASO PADRÃO: OPÇÃO INVÁLIDA
    // =============================================
    default:
      exibir_mensagem_fornece_e_parce("Opção inválida! Tente novamente.");
    }

    // Pausa para usuário ver o resultado antes de continuar
    if (opcao != 0) {
      printf("\nPressione Enter para continuar...");
      while (getchar() != '\n')
        ; // Espera usuário pressionar Enter
    }

  } while (opcao != 0); // Condição de saída: opção 0

  // =============================================
  // LIMPEZA FINAL - LIBERAÇÃO DE MEMÓRIA
  // =============================================
  desalocar_lista_fornece_e_parce(listaFornecedores_e_parceiros);
  exibir_mensagem_fornece_e_parce("Memória liberada. Sistema encerrado.");
}