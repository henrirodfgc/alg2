#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/fornece_e_parce.h"
#include "../../view/cadastro/fornece_e_parce_view.h"
#include "fornece_e_parce_controller.h"

//mantém os dados entre chamadas sem precisar do main
static NoFornecedores_e_parceiros *listaFornecedores_e_parceiros = NULL;

void iniciar_fornecedor_e_parceiro() {
    int opcao;
    int id_busca;
    Fornecedores_e_parceiros temp;

    do {
        exibir_menu_principal_fornece_parce(); 
        scanf("%d", &opcao); 
        getchar();

        switch (opcao) {
            case 1: { 
                temp = ler_dados_fornecedor(); 

                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, temp.id) != NULL) {
                    exibir_mensagem_fornece_e_parce("ERRO: Já existe um registro com este ID. Tente novamente");
                    break;
                } else {
                    listaFornecedores_e_parceiros = adicionar_fornecedor_na_lista(listaFornecedores_e_parceiros, temp);
                    exibir_mensagem_fornece_e_parce("Fornecedor cadastrado com sucesso");
                }
                break;
            }

            case 2: { 
                temp = ler_dados_parceiro(); 

                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, temp.id) != NULL) {
                    exibir_mensagem_fornece_e_parce("ERRO: Já existe um registro com este ID. Tente novamente");
                    break;
                } else {
                    listaFornecedores_e_parceiros = adicionar_parceiros_na_lista(listaFornecedores_e_parceiros, temp);
                    exibir_mensagem_fornece_e_parce("Parceiro cadastrado com sucesso");
                }
                break;
            }

            case 3: { 
                id_busca = ler_id_para_operacao_fornece_e_parce(); 
                
                Fornecedores_e_parceiros *registro_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca); 
                
                if (registro_encontrado != NULL) {
                    exibir_fornece_e_parce(registro_encontrado);
                } else {
                    exibir_mensagem_fornece_e_parce("Registro não encontrado");
                }
                break;
            }

            case 4: { 
                exibir_todas_fornece_e_parce(listaFornecedores_e_parceiros);
                break;
            }

            case 5: { 
                id_busca = ler_id_para_operacao_fornece_e_parce(); 
                
                Fornecedores_e_parceiros *fornecedor_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);

                if (fornecedor_encontrado == NULL) {
                    exibir_mensagem_fornece_e_parce("Nenhum fornecedor cadastrado com este ID");
                } else if (fornecedor_encontrado->tipo != TIPO_CNPJ) {
                    exibir_mensagem_fornece_e_parce("Este ID pertence a um parceiro, não a um fornecedor");
                } else {
                    char nome_fantasia[50], razao_social[100], endereco[256];
                    char cnpj[15], telefone[20];
                    TipoServico servico;

                    printf("Novo Nome Fantasia: ");
                    fgets(nome_fantasia, sizeof(nome_fantasia), stdin);
                    nome_fantasia[strcspn(nome_fantasia, "\n")] = 0;

                    printf("Nova Razão Social: ");
                    fgets(razao_social, sizeof(razao_social), stdin);
                    razao_social[strcspn(razao_social, "\n")] = 0;

                    printf("Novo Endereço: ");
                    fgets(endereco, sizeof(endereco), stdin);
                    endereco[strcspn(endereco, "\n")] = 0;

                    printf("Novo CNPJ: ");
                    fgets(cnpj, sizeof(cnpj), stdin);
                    cnpj[strcspn(cnpj, "\n")] = 0;

                    printf("Novo Telefone: ");
                    fgets(telefone, sizeof(telefone), stdin);
                    telefone[strcspn(telefone, "\n")] = 0;

                    int opcao_servico;
                    printf("\nNovo Serviço:\n");
                    printf("1 - Buffet\n");
                    printf("2 - Segurança\n");
                    printf("3 - Atração Musical\n");
                    printf("Escolha: ");
                    scanf("%d", &opcao_servico);
                    getchar();

                    switch(opcao_servico) {
                        case 1: servico = SERVICO_BUFFET; break;
                        case 2: servico = SERVICO_SEGURANCA; break;
                        case 3: servico = SERVICO_ATRACAO_MUSICAL; break;
                        default: 
                            printf("Opção inválida! Definindo como Buffet.\n");
                            servico = SERVICO_BUFFET;
                    }

                    atualizar_fornecedor_por_id(listaFornecedores_e_parceiros, id_busca,  
                                                nome_fantasia, razao_social, endereco,   
                                                cnpj, telefone, servico);
                    
                    exibir_mensagem_fornece_e_parce("Fornecedor atualizado com sucesso");
                }
                break;
            }

            case 6: { 
                id_busca = ler_id_para_operacao_fornece_e_parce(); 
                
                Fornecedores_e_parceiros *parceiro_encontrado = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);

                if (parceiro_encontrado == NULL) {
                    exibir_mensagem_fornece_e_parce("Nenhum parceiro cadastrado com este ID");
                } else if (parceiro_encontrado->tipo != TIPO_CPF) {
                    exibir_mensagem_fornece_e_parce("Este ID pertence a um fornecedor, não a um parceiro");
                } else {
                    char nome_fantasia[50], razao_social[100], endereco[256];
                    char cpf[12], telefone[20];
                    TipoServico servico;

                    printf("Novo Nome Fantasia: ");
                    fgets(nome_fantasia, sizeof(nome_fantasia), stdin);
                    nome_fantasia[strcspn(nome_fantasia, "\n")] = 0;

                    printf("Nova Razão Social: ");
                    fgets(razao_social, sizeof(razao_social), stdin);
                    razao_social[strcspn(razao_social, "\n")] = 0;

                    printf("Novo Endereço: ");
                    fgets(endereco, sizeof(endereco), stdin);
                    endereco[strcspn(endereco, "\n")] = 0;

                    printf("Novo CPF: ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = 0;

                    printf("Novo Telefone: ");
                    fgets(telefone, sizeof(telefone), stdin);
                    telefone[strcspn(telefone, "\n")] = 0;

                    // CORREÇÃO: Menu para seleção de serviço
                    int opcao_servico;
                    printf("\nNovo Serviço:\n");
                    printf("1 - Buffet\n");
                    printf("2 - Segurança\n");
                    printf("3 - Atração Musical\n");
                    printf("Escolha: ");
                    scanf("%d", &opcao_servico);
                    getchar();

                    switch(opcao_servico) {
                        case 1: servico = SERVICO_BUFFET; break;
                        case 2: servico = SERVICO_SEGURANCA; break;
                        case 3: servico = SERVICO_ATRACAO_MUSICAL; break;
                        default: 
                            printf("Opção inválida! Definindo como Buffet.\n");
                            servico = SERVICO_BUFFET;
                    }

                    atualizar_parceiro_por_id(listaFornecedores_e_parceiros, id_busca,  
                                              nome_fantasia, razao_social, endereco,   
                                              cpf, telefone, servico);
                    
                    exibir_mensagem_fornece_e_parce("Parceiro atualizado com sucesso");
                }
                break;
            }

            case 7: { 
                id_busca = ler_id_para_operacao_fornece_e_parce(); 

                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca) == NULL) {
                    exibir_mensagem_fornece_e_parce("Nenhum registro para deletar com este ID");
                    break;
                }
                
                listaFornecedores_e_parceiros = deletar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, id_busca);
                exibir_mensagem_fornece_e_parce("Registro deletado com sucesso");
                break;
            }

            case 0:
                exibir_mensagem_fornece_e_parce("Voltando ao menu principal...");
                break;

            default:
                exibir_mensagem_fornece_e_parce("Opção inválida! Tente novamente.");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
        }

    } while (opcao != 0);
}