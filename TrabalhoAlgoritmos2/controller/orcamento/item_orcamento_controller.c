#include <stdlib.h>
#include <stdio.h>
#include "item_orcamento_controller.h"
#include "../../model/orcamento/item_orcamento.h"
#include "../../view/orcamento/item_orcamento_view.h"
#include "../../model/cadastro/recursos.h"
#include "../../model/cadastro/equipe.h"       
#include "../../model/cadastro/fornece_e_parce.h" 

extern NoRecurso *listaRecursos;
extern NoEquipe *listaEquipe; 
extern NoFornecedores_e_parceiros *listaFornecedores_e_parceiros; 
extern NoEquipe* carregar_equipe(NoEquipe* lista);
extern NoFornecedores_e_parceiros* carregar_fornecedores_e_parceiros(NoFornecedores_e_parceiros* lista);

static NoItemOrcamento *listaItens = NULL;

int obter_proximo_id_item(NoItemOrcamento* lista) {
    int maior = 0;
    NoItemOrcamento* atual = lista;
    while (atual != NULL) {
        if (atual->dados.id > maior) maior = atual->dados.id;
        atual = atual->proximo;
    }
    return maior + 1;
}

void gerenciar_itens_de_um_evento(int id_evento) {
    int opcao;
    listaItens = carregar_itens_orcamento(listaItens);
    listaEquipe = carregar_equipe(listaEquipe);
    listaFornecedores_e_parceiros = carregar_fornecedores_e_parceiros(listaFornecedores_e_parceiros);
    
    do {
        opcao = exibir_menu_itens();
        
        ItemOrcamento novo;
        int sucesso = 0;

        switch(opcao) {
            case 1: { 
                novo = ler_dados_item_orcamento(id_evento, 1);
                Equipamento *equip = buscar_recurso_por_codigo(listaRecursos, novo.id_estrangeiro);
                if (equip == NULL) {
                    exibir_mensagem_item("erro:equipamento nao encontrado.");
                } else {
                    novo.valor_unitario = equip->valor_locacao;
                    exibir_mensagem_item("Equipamento adicionado (Disponibilidade sera checada na aprovacao).");
                    sucesso = 1;
                }
                break;
            }
            case 2: { 
                novo = ler_dados_item_orcamento(id_evento, 2);
                MembroEquipe *membro = buscar_membro_por_codigo(listaEquipe, novo.id_estrangeiro);
                if (membro == NULL) {
                    exibir_mensagem_item("erro:funcionario nao encontrado.");
                } else {
                    novo.valor_unitario = membro->valor_diaria_hora;
                    exibir_mensagem_item("membro da equipe adicionado!");
                    sucesso = 1;
                }
                break;
            }
            case 3: { 
                novo = ler_dados_item_orcamento(id_evento, 3);
                Fornecedores_e_parceiros *parceiro = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, novo.id_estrangeiro);
                if (parceiro == NULL) {
                    exibir_mensagem_item("erro:parceiro nao encontrado.");
                } else {
                    exibir_mensagem_item("servico adicionado!");
                    sucesso = 1;
                }
                break;
            }
            case 4: { 
                exibir_lista_itens_evento(listaItens, id_evento);
                float total = calcular_total_evento(listaItens, id_evento);
                exibir_mensagem_item_formatada(">> total atual: r$ %.2f", total);
                break;
            }
            case 0: break;
            default: exibir_mensagem_item("opcao invalida.");
        }

        if (sucesso) {
            novo.id = obter_proximo_id_item(listaItens);
            listaItens = adicionar_item_na_lista(listaItens, novo);
        }

        if (opcao != 0 && opcao != 4) { 
             pausar_tela_itens();
        }
    } while (opcao != 0);
}

void estornar_estoque_evento(int id_evento) {
    exibir_mensagem_item(">> Finalizacao: Liberando agenda dos recursos deste evento...");
}