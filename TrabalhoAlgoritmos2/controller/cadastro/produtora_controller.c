#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../model/cadastro/produtora.h"
#include "../../view/cadastro/produtora_view.h"
#include "produtora_controller.h"

// Lista global
NoProdutora *listaProdutora = NULL;

void iniciar_produtora() {
    int opcao;
    char cnpj_busca[20];
    Produtora temp;

    listaProdutora = carregar_produtoras(listaProdutora);

    do {
        opcao = exibir_menu_produtora();

        switch(opcao) {
            case 1: // Criar
                temp = ler_dados_produtora();
                if (buscar_produtora_por_cnpj(listaProdutora, temp.cnpj) != NULL) {
                    exibir_mensagem_produtora("ERRO: Ja existe uma produtora com este CNPJ.");
                } else {
                    listaProdutora = adicionar_produtora_na_lista(listaProdutora, temp);
                    exibir_mensagem_produtora("Produtora criada com sucesso");
                }
                break;

            case 2: {
 
                printf("Digite o CNPJ da produtora para atualizar: ");
                scanf("%s", cnpj_busca);
                
                Produtora* p = buscar_produtora_por_cnpj(listaProdutora, cnpj_busca);
                
                if (p) {
   
                    char nome_fantasia[50], razao_social[100], inscricao[20];
                    char endereco[256], telefone[20], email[50];
                    char responsavel[50], tel_resp[20], margem[10];


                    ler_dados_atualizacao_produtora(nome_fantasia, razao_social, inscricao, 
                                                  endereco, telefone, email, 
                                                  responsavel, tel_resp, margem);

                    atualizar_produtora_por_cnpj(listaProdutora, cnpj_busca, 
                                                nome_fantasia, razao_social, inscricao, 
                                                endereco, telefone, email, 
                                                responsavel, margem, tel_resp);
                    
                    exibir_mensagem_produtora("Produtora atualizada com sucesso");
                } else {
                    exibir_mensagem_produtora("Nenhuma produtora cadastrada com este CNPJ");
                }
                break;
            }

            case 3: 
                printf("Digite o CNPJ para exibir: ");
                scanf("%s", cnpj_busca);
                Produtora* p = buscar_produtora_por_cnpj(listaProdutora, cnpj_busca);
                exibir_produtora(p);
                break;

            case 4: 
                printf("Digite o CNPJ para deletar: ");
                scanf("%s", cnpj_busca);
                if (deletar_produtora_por_cnpj(listaProdutora, cnpj_busca)) {
                    exibir_mensagem_produtora("Produtora deletada com sucesso");
                } else {
                    exibir_mensagem_produtora("Erro ao deletar ou Produtora nao encontrada");
                }
                break;

            case 5: 
                exibir_todas_produtoras(listaProdutora);
                break;

            case 0:
                exibir_mensagem_produtora("Saindo...");
                break;

            default:
                exibir_mensagem_produtora("Opcao invalida!");
        }
    } while (opcao != 0);
    
    desalocar_lista_produtoras(listaProdutora);
}