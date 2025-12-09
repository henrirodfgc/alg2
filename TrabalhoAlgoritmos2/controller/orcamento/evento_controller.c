#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/cliente.h"
#include "../../model/orcamento/evento.h"
#include "../../view/orcamento/evento_view.h"
#include "evento_controller.h"
#include "item_orcamento_controller.h"
#include "../../model/transacao/contas_receber.h"
#include "../../model/cadastro/recursos.h"
#include "../../model/orcamento/item_orcamento.h"

extern NoCliente * listaClientes;
extern NoCliente* carregar_clientes(NoCliente* lista);

extern NoRecurso *listaRecursos;
extern NoRecurso* carregar_recursos(NoRecurso* lista);
extern NoItemOrcamento* carregar_itens_orcamento(NoItemOrcamento* lista);

NoEvento *listaEventos = NULL;
static NoContaReceber *listaContas = NULL;

long data_para_num_evt(const char* data) {
    int d, m, a;
    if (sscanf(data, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    return (long)a * 10000 + m * 100 + d;
}

int datas_colidem(const char* i1, const char* f1, const char* i2, const char* f2) {
    long ini1 = data_para_num_evt(i1);
    long fim1 = data_para_num_evt(f1);
    long ini2 = data_para_num_evt(i2);
    long fim2 = data_para_num_evt(f2);
    
    return (ini1 <= fim2 && ini2 <= fim1);
}

// ----------------------------------

void iniciar_eventos() {
    int opcao;
    listaEventos = carregar_eventos(listaEventos); 
    listaClientes = carregar_clientes(listaClientes);
    listaContas = carregar_contas_receber(listaContas);
    
    do {
        opcao = exibir_menu_eventos();
        
        switch(opcao) {
            case 1: {
                Evento novo = ler_dados_evento();
                
                Cliente *cliente_valido = buscar_cliente_por_id(listaClientes, novo.codigo_cliente);
                
                if (cliente_valido == NULL) {
                    exibir_mensagem_evento("erro:cliente nao encontrado. orcamento cancelado.");
                    break;
                }
                
                int maior_id = 0;
                NoEvento* aux = listaEventos;
                while(aux){ if(aux->dados.codigo > maior_id) maior_id = aux->dados.codigo; aux=aux->proximo; }
                novo.codigo = maior_id + 1;
                printf(">> Evento gerado com Codigo: %d\n", novo.codigo);

                listaEventos = adicionar_evento_na_lista(listaEventos, novo);
                exibir_mensagem_evento("orcamento criado com sucesso!");
                
                exibir_mensagem_evento("abrindo gerenciador de itens...");
                gerenciar_itens_de_um_evento(novo.codigo);
                break;
            }
            case 2: { 
                NoEvento *atual = listaEventos;
                if(!atual) exibir_mensagem_evento("nenhum evento cadastrado.");
                while(atual) {
                    exibir_evento(&(atual->dados));
                    atual = atual->proximo;
                }
                break;
            }
            case 3: { 
                int id_evento = ler_id_evento_view("digite o id do evento para aprovar");
                
                NoEvento *evento_alvo = NULL;
                NoEvento *aux = listaEventos;
                while(aux) { if(aux->dados.codigo == id_evento) { evento_alvo = aux; break; } aux = aux->proximo; }

                if(evento_alvo == NULL) {
                    exibir_mensagem_evento("evento nao encontrado.");
                    break;
                }

                if(evento_alvo->dados.status == 1) {
                    exibir_mensagem_evento("este evento ja esta aprovado!");
                    break;
                }

                NoItemOrcamento* listaTodosItens = NULL;
                listaTodosItens = carregar_itens_orcamento(listaTodosItens);
                listaRecursos = carregar_recursos(listaRecursos);
                
                int pode_aprovar = 1;
                
                NoItemOrcamento *meu_item = listaTodosItens;
                while(meu_item != NULL) {
                    if(meu_item->dados.id_evento == id_evento && meu_item->dados.tipo_item == 1) {
                        
                        int id_equip = meu_item->dados.id_estrangeiro;
                        int qtd_eu_quero = meu_item->dados.quantidade;
                        
                        Equipamento* eq_original = buscar_recurso_por_codigo(listaRecursos, id_equip);
                        if(!eq_original) {
                            printf("Erro: Equipamento ID %d nao existe no cadastro.\n", id_equip);
                            pode_aprovar = 0; break;
                        }

                        int estoque_total = eq_original->quantidade_estoque;
                        int estoque_ocupado = 0;

                        NoEvento *evt_outro = listaEventos;
                        while(evt_outro != NULL) {

                            if(evt_outro->dados.status == 1 && evt_outro->dados.codigo != id_evento) {

                                if(datas_colidem(evento_alvo->dados.data_inicio, evento_alvo->dados.data_fim,
                                                 evt_outro->dados.data_inicio, evt_outro->dados.data_fim)) {

                                    NoItemOrcamento *item_outro = listaTodosItens;
                                    while(item_outro != NULL) {
                                        if(item_outro->dados.id_evento == evt_outro->dados.codigo &&
                                           item_outro->dados.tipo_item == 1 &&
                                           item_outro->dados.id_estrangeiro == id_equip) {
                                            
                                            estoque_ocupado += item_outro->dados.quantidade;
                                        }
                                        item_outro = item_outro->proximo;
                                    }
                                }
                            }
                            evt_outro = evt_outro->proximo;
                        }

                        if (estoque_total - estoque_ocupado < qtd_eu_quero) {
                            printf("CONFLITO DE DATA! Equip: %s\n", eq_original->descricao);
                            printf("   Total na empresa: %d\n", estoque_total);
                            printf("   Ocupado em outros eventos nessa data: %d\n", estoque_ocupado);
                            printf("   Voce precisa de: %d. (Disponivel: %d)\n", qtd_eu_quero, (estoque_total - estoque_ocupado));
                            pode_aprovar = 0;
                            break;
                        }
                    }
                    meu_item = meu_item->proximo;
                }

                
                if (pode_aprovar) {
                    int confirmar = confirmar_aprovacao_view();
                    if(confirmar == 1) {
                        evento_alvo->dados.status = 1; // 1 = Aprovado
                        reescrever_arquivo_eventos(listaEventos);
                        
                        listaContas = gerar_nova_conta(listaContas, 
                                         evento_alvo->dados.codigo, 
                                         evento_alvo->dados.codigo_cliente, 
                                         evento_alvo->dados.valor_total);
                        
                        exibir_mensagem_evento("Evento APROVADO! Agenda bloqueada para esses itens.");
                    }
                } else {
                    exibir_mensagem_evento("Aprovacao negada por falta de disponibilidade na data.");
                }
                break;
            }
            case 4: { 
                int id_evento = ler_id_evento_view("Digite o ID do evento para FINALIZAR");
                NoEvento *aux = listaEventos;
                int encontrou = 0;

                while(aux != NULL) {
                    if(aux->dados.codigo == id_evento) {
                        exibir_evento(&(aux->dados));
                        
                        if(aux->dados.status != 1) {
                            exibir_mensagem_evento("Erro: Apenas eventos APROVADOS podem ser finalizados.");
                            encontrou = 1; break;
                        }

                        exibir_mensagem_evento("Confirma finalizacao? (1-Sim, 0-Nao): ");
                        int confirmar;
                        scanf("%d", &confirmar);
                        
                        if(confirmar == 1) {
                            aux->dados.status = 2; 
                            reescrever_arquivo_eventos(listaEventos);
                            exibir_mensagem_evento("Evento FINALIZADO. Itens liberados na agenda.");
                        }
                        encontrou = 1;
                        break;
                    }
                    aux = aux->proximo;
                }
                if(!encontrou) exibir_mensagem_evento("Evento nao encontrado.");
                break;
            }
            case 0:
                exibir_mensagem_evento("saindo de eventos...");
                break;
            default:
                exibir_mensagem_evento("opcao invalida");
        }
        
        if(opcao!=0) pausar_tela_evento(); 
        
    } while (opcao != 0);
    
    desalocar_lista_eventos(listaEventos);
    desalocar_lista_contas(listaContas);
}