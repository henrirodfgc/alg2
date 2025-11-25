#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/produtora.h"
#include "../../view/cadastro/produtora_view.h"
#include "produtora_controller.h"

// =============================================
// FUNÇÃO: iniciar_produtora
// OBJETIVO: Controlador principal do sistema de produtoras
// DESCRIÇÃO: Orquestra o fluxo entre Model e View, gerencia o menu principal
//            e coordena todas as operações CRUD do sistema
// =============================================
void iniciar_produtora() {
    // Inicialização das variáveis do controlador
    NoProdutora *listaProdutora = NULL;  // Lista encadeada de produtoras (inicia vazia)
    int opcao;                           // Armazena a escolha do usuário no menu
    char* cnpj_busca;                    // CNPJ para operações de busca/atualização/exclusão
    Produtora temp;                      // Estrutura temporária para novos dados

    // =============================================
    // LOOP PRINCIPAL DA APLICAÇÃO
    // Mantém o sistema rodando até usuário escolher sair
    // =============================================
    do {
        // Exibe o menu de opções para o usuário
        exibir_menu_produtora(); 
        
        // Solicita e lê a opção do usuário
        scanf("%d", &opcao); 

        // =============================================
        // PROCESSAMENTO DAS OPÇÕES DO MENU
        // =============================================
        switch (opcao) {
            // =============================================
            // CASO 1: CRIAR NOVA PRODUTORA
            // =============================================
            case 1: { 
                // Coleta dados da nova produtora
                temp = ler_dados_produtora(); 

                // Verifica se já existe produtora com o mesmo CNPJ
                if (buscar_produtora_por_cnpj(listaProdutora, temp.cnpj) != NULL) {
                    exibir_mensagem_produtora("ERRO: Já existe uma produtora com este CNPJ. Tente novamente");
                    break; // Sai do case sem criar duplicata
                } else {
                    // Adiciona nova produtora na lista
                    listaProdutora = adicionar_produtora_na_lista(listaProdutora, temp);
                    exibir_mensagem_produtora("Produtora criada com sucesso");
                }
                break;
            }

            // =============================================
            // CASO 2: ATUALIZAR PRODUTORA EXISTENTE
            // =============================================
            case 2: { 
                // Solicita CNPJ da produtora a ser atualizada
                cnpj_busca = ler_cnpj_para_operacao("atualizar"); 
                
                // Busca produtora pelo CNPJ
                Produtora *produtora_encontrado = buscar_produtora_por_cnpj(listaProdutora, cnpj_busca);

                if (produtora_encontrado == NULL) {
                    exibir_mensagem_produtora("Nenhuma produtora cadastrada com este CNPJ");
                } else {
                    // Buffers para armazenar os novos dados
                    char cnpj[14], nome_fantasia[50], razao_social[100], inscricao_estadual[9], 
                         email[50], endereco_completo[300], telefone[11], nome_do_responsavel[50], 
                         telefone_do_responsavel[11], margem_de_lucro_padrao[6];

                    // Coleta os novos dados do usuário
                    // CORREÇÃO: Parâmetros na ordem correta da função
                    ler_dados_atualizacao_produtora(cnpj, nome_fantasia, razao_social,  
                                                   inscricao_estadual, email, endereco_completo, 
                                                   telefone, nome_do_responsavel, 
                                                   telefone_do_responsavel, margem_de_lucro_padrao);

                    // Atualiza os dados da produtora
                    atualizar_produtora_por_cnpj(listaProdutora, cnpj_busca,  
                                                nome_fantasia, razao_social, inscricao_estadual,    
                                                email, endereco_completo, telefone, nome_do_responsavel,  
                                                telefone_do_responsavel, margem_de_lucro_padrao);
                    
                    exibir_mensagem_produtora("Produtora atualizada com sucesso");
                }
                break;
            }

            // =============================================
            // CASO 3: EXIBIR PRODUTORA ESPECÍFICA
            // =============================================
            case 3: { 
                // Solicita CNPJ da produtora a ser exibida
                cnpj_busca = ler_cnpj_para_operacao("exibir"); 
                
                // Busca produtora pelo CNPJ
                Produtora *produtora_encontrada = buscar_produtora_por_cnpj(listaProdutora, cnpj_busca); 
                
                if (produtora_encontrada != NULL) {
                    exibir_produtora(produtora_encontrada); // Exibe dados formatados
                } else {
                    exibir_mensagem_produtora("Produtora não encontrada");
                }
                break;
            }

            // =============================================
            // CASO 4: DELETAR PRODUTORA
            // =============================================
            case 4: { 
                // Solicita CNPJ da produtora a ser deletada
                cnpj_busca = ler_cnpj_para_operacao("deletar"); 

                // Verifica se a produtora existe antes de tentar deletar
                if (buscar_produtora_por_cnpj(listaProdutora, cnpj_busca) == NULL) {
                    exibir_mensagem_produtora("Nenhuma produtora para deletar com este CNPJ");
                    break;
                }
                
                // Remove produtora da lista
                int sucesso = deletar_produtora_por_cnpj(listaProdutora, cnpj_busca);
                if (sucesso) {
                exibir_mensagem_produtora("Produtora deletada com sucesso");
                } else {
                    exibir_mensagem_produtora("Erro ao deletar ou Produtora não encontrada");
                }
                break;
            }

            // =============================================
            // CASO 5: LISTAR TODAS AS PRODUTORAS
            // =============================================
            case 5: { 
                exibir_todas_produtoras(listaProdutora); // Exibe lista completa
                break;
            }

            // =============================================
            // CASO 0: SAIR DO SISTEMA
            // =============================================
            case 0:
                exibir_mensagem_produtora("Saindo do sistema de produtoras...");
                break;

            // =============================================
            // CASO PADRÃO: OPÇÃO INVÁLIDA
            // =============================================
            default:
                exibir_mensagem_produtora("Opção inválida! Tente novamente.");
        }

        // Pausa para usuário ver o resultado antes de continuar
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n'); // Espera usuário pressionar Enter
        }

    } while (opcao != 0); // Condição de saída: opção 0

    // =============================================
    // LIMPEZA FINAL - LIBERAÇÃO DE MEMÓRIA
    // =============================================
    desalocar_lista_produtoras(listaProdutora);
    exibir_mensagem_produtora("Memória liberada. Sistema encerrado.");
}