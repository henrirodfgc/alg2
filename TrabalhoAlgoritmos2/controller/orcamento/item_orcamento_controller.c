#include <stdlib.h>
#include <stdio.h>
#include "item_orcamento_controller.h"
#include "../../model/orcamento/item_orcamento.h"
#include "../../view/orcamento/item_orcamento_view.h"
#include "../../model/cadastro/recursos.h"
#include "../../model/cadastro/equipe.h"       //novo
#include "../../model/cadastro/fornece_e_parce.h" //novo

//acesso as listas globais
extern NoRecurso *listaRecursos;
extern NoEquipe *listaEquipe; //precisa expor isso no equipe_controller.c (tirar static)
extern NoFornecedores_e_parceiros *listaFornecedores_e_parceiros; //precisa expor no fornece_controller (tirar static)

//funcoes de carregar pra garantir q nao ta vazio
extern NoEquipe* carregar_equipe(NoEquipe* lista);
extern NoFornecedores_e_parceiros* carregar_fornecedores_e_parceiros(NoFornecedores_e_parceiros* lista);

static NoItemOrcamento *listaItens = NULL;

void gerenciar_itens_de_um_evento(int id_evento) {
    int opcao;
    
    listaItens = carregar_itens_orcamento(listaItens);
    
    //garante q as outras listas estao na memoria pra validar
    listaEquipe = carregar_equipe(listaEquipe);
    listaFornecedores_e_parceiros = carregar_fornecedores_e_parceiros(listaFornecedores_e_parceiros);
    
    do {
        opcao = exibir_menu_itens();
        
        switch(opcao) {
            case 1: { //equipamento
                ItemOrcamento novo = ler_dados_item_orcamento(id_evento, 1);
                Equipamento *equip = buscar_recurso_por_codigo(listaRecursos, novo.id_estrangeiro);
                
                if (equip == NULL) {
                    printf("erro:equipamento nao encontrado.\n");
                } else if (equip->quantidade_estoque < novo.quantidade) {
                    printf("erro:estoque insuficiente.\n");
                } else {
                    novo.valor_unitario = equip->valor_locacao;
                    novo.id = rand() % 10000;
                    listaItens = adicionar_item_na_lista(listaItens, novo);
                    equip->quantidade_estoque -= novo.quantidade;
                    printf("equipamento adicionado!\n");
                }
                break;
            }
            case 2: { //equipe
                ItemOrcamento novo = ler_dados_item_orcamento(id_evento, 2);
                MembroEquipe *membro = buscar_membro_por_codigo(listaEquipe, novo.id_estrangeiro);
                
                if (membro == NULL) {
                    printf("erro:funcionario nao encontrado.\n");
                } else {
                    novo.valor_unitario = membro->valor_diaria_hora;
                    novo.id = rand() % 10000;
                    listaItens = adicionar_item_na_lista(listaItens, novo);
                    printf("membro da equipe adicionado!\n");
                }
                break;
            }
            case 3: { //servico/parceiro
                ItemOrcamento novo = ler_dados_item_orcamento(id_evento, 3);
                Fornecedores_e_parceiros *parceiro = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, novo.id_estrangeiro);
                
                if (parceiro == NULL) {
                    printf("erro:parceiro nao encontrado.\n");
                } else {
                    //preco foi digitado na view pq parceiro n tem preco fixo
                    novo.id = rand() % 10000;
                    listaItens = adicionar_item_na_lista(listaItens, novo);
                    printf("servico adicionado!\n");
                }
                break;
            }
            case 4: { //listar
                exibir_lista_itens_evento(listaItens, id_evento);
                float total = calcular_total_evento(listaItens, id_evento);
                printf(">> total atual: r$ %.2f\n", total);
                break;
            }
            case 0: break;
            default: printf("opcao invalida.\n");
        }
        if (opcao != 0 && opcao != 4) { //pausa
             printf("pressione enter..."); getchar(); getchar();
        }
    } while (opcao != 0);
}