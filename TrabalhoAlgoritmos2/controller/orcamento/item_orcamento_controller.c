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

void gerenciar_itens_de_um_evento(int id_evento) {
    int opcao;
    listaItens = carregar_itens_orcamento(listaItens);
    listaEquipe = carregar_equipe(listaEquipe);
    listaFornecedores_e_parceiros = carregar_fornecedores_e_parceiros(listaFornecedores_e_parceiros);
    
    do {
        opcao = exibir_menu_itens();
        switch(opcao) {
            case 1: { 
                ItemOrcamento novo = ler_dados_item_orcamento(id_evento, 1);
                Equipamento *equip = buscar_recurso_por_codigo(listaRecursos, novo.id_estrangeiro);
                if (equip == NULL) {
                    exibir_mensagem_item("erro:equipamento nao encontrado.");
                } else if (equip->quantidade_estoque < novo.quantidade) {
                    exibir_mensagem_item("erro:estoque insuficiente.");
                } else {
                    novo.valor_unitario = equip->valor_locacao;
                    novo.id = rand() % 10000;
                    listaItens = adicionar_item_na_lista(listaItens, novo);
                    equip->quantidade_estoque -= novo.quantidade;
                    exibir_mensagem_item("equipamento adicionado!");
                }
                break;
            }
            case 2: { 
                ItemOrcamento novo = ler_dados_item_orcamento(id_evento, 2);
                MembroEquipe *membro = buscar_membro_por_codigo(listaEquipe, novo.id_estrangeiro);
                if (membro == NULL) {
                    exibir_mensagem_item("erro:funcionario nao encontrado.");
                } else {
                    novo.valor_unitario = membro->valor_diaria_hora;
                    novo.id = rand() % 10000;
                    listaItens = adicionar_item_na_lista(listaItens, novo);
                    exibir_mensagem_item("membro da equipe adicionado!");
                }
                break;
            }
            case 3: { 
                ItemOrcamento novo = ler_dados_item_orcamento(id_evento, 3);
                Fornecedores_e_parceiros *parceiro = buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, novo.id_estrangeiro);
                if (parceiro == NULL) {
                    exibir_mensagem_item("erro:parceiro nao encontrado.");
                } else {
                    novo.id = rand() % 10000;
                    listaItens = adicionar_item_na_lista(listaItens, novo);
                    exibir_mensagem_item("servico adicionado!");
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
        if (opcao != 0 && opcao != 4) { 
             pausar_tela_itens();
        }
    } while (opcao != 0);
}

//devolve os itens pro estoque quando finaliza
void estornar_estoque_evento(int id_evento) {
    listaItens = carregar_itens_orcamento(listaItens);
    listaRecursos = carregar_recursos(listaRecursos);

    NoItemOrcamento *atual = listaItens;
    int devolvidos = 0;

    exibir_mensagem_recursos("\n>> Processando devolucao de estoque...\n");

    while (atual != NULL) {
    
        if (atual->dados.id_evento == id_evento && atual->dados.tipo_item == 1) {
            
            Equipamento *equip = buscar_recurso_por_codigo(listaRecursos, atual->dados.id_estrangeiro);
            
            if (equip != NULL) {
                //devolve a quantidade
                equip->quantidade_estoque += atual->dados.quantidade;
                printf("   + Unid. de '%s' devolvido:\n", equip->descricao);
                exibir_numero(atual->dados.quantidade);
                exibir_mensagem_item("(novo estoque: )");
                exibir_numero(equip->quantidade_estoque);
                devolvidos++;
            }
        }
        atual = atual->proximo;
    }
    if (devolvidos > 0) {
        exibir_mensagem_item(">>");
        exibir_numero(devolvidos);
        exibir_mensagem_item("tipos de equipamentos foram devolvidos ao estoque.\n");
    } else {
        exibir_mensagem_item(">> Nenhum equipamento fisico para devolver neste evento.\n");
    }
}