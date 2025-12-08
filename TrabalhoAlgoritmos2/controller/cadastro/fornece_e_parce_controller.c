#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/fornece_e_parce.h"
#include "../../view/cadastro/fornece_e_parce_view.h"
#include "fornece_e_parce_controller.h"

// mantem os dados entre chamadas sem precisar do main
NoFornecedores_e_parceiros *listaFornecedores_e_parceiros = NULL;

void iniciar_fornecedor_e_parceiro() {
    int opcao;
    int id_busca;
    Fornecedores_e_parceiros temp;

    // carrega dados ao iniciar
    listaFornecedores_e_parceiros = carregar_fornecedores_e_parceiros(listaFornecedores_e_parceiros);

    do {
        exibir_menu_principal_fornece_parce(); 
        scanf("%d", &opcao); 
        getchar();

        switch (opcao) {
            case 1: { // cadastrar fornecedor
                temp = ler_dados_fornecedor(); 

                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, temp.id) != NULL) {
                    exibir_mensagem_fornece_e_parce("erro: ja existe um registro com este id. tente novamente");
                } else {
                    listaFornecedores_e_parceiros = adicionar_fornecedor_na_lista(listaFornecedores_e_parceiros, temp);
                    exibir_mensagem_fornece_e_parce("fornecedor cadastrado com sucesso");
                }
                break;
            }

            case 2: { // cadastrar parceiro
                temp = ler_dados_parceiro(); 

                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, temp.id) != NULL) {
                    exibir_mensagem_fornece_e_parce("erro: ja existe um registro com este id. tente novamente");
                } else {
                    listaFornecedores_e_parceiros = adicionar_parceiros_na_lista(listaFornecedores_e_parceiros, temp);
                    exibir_mensagem_fornece_e_parce("parceiro cadastrado com sucesso");
                }
                break;
            }

            case 3: { // buscar por id
                id_busca = ler_id_para_operacao_fornece_e_parce(); 
                
                Fornecedores_e_parceiros *registro_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca); 
                
                if (registro_encontrado != NULL) {
                    exibir_fornece_e_parce(registro_encontrado);
                } else {
                    exibir_mensagem_fornece_e_parce("registro nao encontrado");
                }
                break;
            }

            case 4: { // listar todos
                exibir_todas_fornece_e_parce(listaFornecedores_e_parceiros);
                break;
            }

            case 5: { // atualizar fornecedor
                id_busca = ler_id_para_operacao_fornece_e_parce(); 
                
                Fornecedores_e_parceiros *fornecedor_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);

                if (fornecedor_encontrado == NULL) {
                    exibir_mensagem_fornece_e_parce("nenhum fornecedor cadastrado com este id");
                } else if (fornecedor_encontrado->tipo != TIPO_CNPJ) {
                    exibir_mensagem_fornece_e_parce("este id pertence a um parceiro, nao a um fornecedor");
                } else {
                    //variaveis para receber os dados novos da view
                    char nome_fantasia[50], razao_social[100], endereco[256];
                    char cnpj[15], telefone[20];
                    TipoServico servico;

                    //chama a view passando o registro atual pra preencher as variaveis
                    ler_dados_atualizacao_fornecedor(fornecedor_encontrado, nome_fantasia, razao_social, endereco, cnpj, telefone, &servico);

                    // agora chama o model com os dados PREENCHIDOS 
                    atualizar_fornecedor_por_id(listaFornecedores_e_parceiros, id_busca,  
                                                nome_fantasia, razao_social, endereco,   
                                                cnpj, telefone, servico);
                    
                    exibir_mensagem_fornece_e_parce("fornecedor atualizado com sucesso");
                }
                break;
            }

            case 6: { // atualizar parceiro
                id_busca = ler_id_para_operacao_fornece_e_parce(); 
                
                Fornecedores_e_parceiros *parceiro_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);

                if (parceiro_encontrado == NULL) {
                    exibir_mensagem_fornece_e_parce("nenhum parceiro cadastrado com este id");
                } else if (parceiro_encontrado->tipo != TIPO_CPF) {
                    exibir_mensagem_fornece_e_parce("este id pertence a um fornecedor, nao a um parceiro");
                } else {
                    //variaveis para receber os dados
                    char nome_fantasia[50], razao_social[100], endereco[256];
                    char cpf[12], telefone[20];
                    TipoServico servico;

                    // chama a view para preencher as variaveis
                    ler_dados_atualizacao_parceiro(parceiro_encontrado, nome_fantasia, razao_social, endereco, cpf, telefone, &servico);

                    // chama o model com os dados 
                    atualizar_parceiro_por_id(listaFornecedores_e_parceiros, id_busca,  
                                              nome_fantasia, razao_social, endereco,   
                                              cpf, telefone, servico);
                    
                    exibir_mensagem_fornece_e_parce("parceiro atualizado com sucesso");
                }
                break;
            }

            case 7: { // deletar
                id_busca = ler_id_para_operacao_fornece_e_parce(); 

                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca) == NULL) {
                    exibir_mensagem_fornece_e_parce("nenhum registro para deletar com este id");
                    break;
                }
                
                listaFornecedores_e_parceiros = deletar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);
                exibir_mensagem_fornece_e_parce("registro deletado com sucesso");
                break;
            }

            case 0:
                exibir_mensagem_fornece_e_parce("voltando ao menu principal...");
                break;

            default:
                exibir_mensagem_fornece_e_parce("opcao invalida! tente novamente.");
        }

        // pausa se nao for sair
        if (opcao != 0) {
            printf("\npressione enter para continuar...");
            while (getchar() != '\n');
        }

    } while (opcao != 0);
}