#include <stdlib.h>
#include <stdio.h>
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
                
                NoEvento *atual = listaEventos;
                int encontrou = 0;
                
                while(atual != NULL) {
                    if(atual->dados.codigo == id_evento) {
                        exibir_evento(&(atual->dados)); 
                        
                        if(atual->dados.status == 1) {
                            exibir_mensagem_evento("este evento ja esta aprovado!");
                            encontrou = 1;
                            break;
                        }

                        NoItemOrcamento* listaItensTemp = NULL;
                        listaItensTemp = carregar_itens_orcamento(listaItensTemp);
                        listaRecursos = carregar_recursos(listaRecursos);
                        
                        int estoque_ok = 1;
                        NoItemOrcamento *it = listaItensTemp;
                        
                        while(it != NULL) {
                            if(it->dados.id_evento == id_evento && it->dados.tipo_item == 1) { // 1 = recurso
                                Equipamento* eq = buscar_recurso_por_codigo(listaRecursos, it->dados.id_estrangeiro);
                                if(eq == NULL || eq->quantidade_estoque < it->dados.quantidade) {
                                    estoque_ok = 0;
                                    char msg[200];
                                    sprintf(msg, "Erro: Estoque insuficiente para o item ID %d (%s).", 
                                            it->dados.id_estrangeiro, (eq ? eq->descricao : "desc."));
                                    exibir_mensagem_evento(msg);
                                    break;
                                }
                            }
                            it = it->proximo;
                        }

                        if (!estoque_ok) {
                            exibir_mensagem_evento("Nao foi possivel aprovar por falta de estoque.");
                            encontrou = 1;
                            
                            break;
                        }
                        

                        int confirmar = confirmar_aprovacao_view();
                        
                        if(confirmar == 1) {
                            it = listaItensTemp;
                            while(it != NULL) {
                                if(it->dados.id_evento == id_evento && it->dados.tipo_item == 1) {
                                    Equipamento* eq = buscar_recurso_por_codigo(listaRecursos, it->dados.id_estrangeiro);
                                    if(eq) {
                                        eq->quantidade_estoque -= it->dados.quantidade;
                                    }
                                }
                                it = it->proximo;
                            }
                            reescrever_arquivo_recursos(listaRecursos);
                            atual->dados.status = 1; 
                            reescrever_arquivo_eventos(listaEventos);
                            
                            listaContas = gerar_nova_conta(listaContas, 
                                             atual->dados.codigo, 
                                             atual->dados.codigo_cliente, 
                                             atual->dados.valor_total);
                            
                            exibir_mensagem_evento("evento aprovado, estoque alocado e fatura gerada!");
                        }
                        encontrou = 1;
                        break;
                    }
                    
                    atual = atual->proximo;
                }
                
                if(!encontrou && id_evento != 0) exibir_mensagem_evento("evento nao encontrado.");
                break;
            }
            case 4: { //finalizar evento
                int id_evento = ler_id_evento_view("Digite o ID do evento para FINALIZAR");
                NoEvento *atual = listaEventos;
                int encontrou = 0;

                while(atual != NULL) {
                    if(atual->dados.codigo == id_evento) {
                        exibir_evento(&(atual->dados));
                        
                        //finaliza so se for aprovado
                        if(atual->dados.status != 1) {
                            exibir_mensagem_evento("Erro: Apenas eventos APROVADOS podem ser finalizados.");
                            encontrou = 1; break;
                        }

                        exibir_mensagem_evento("Confirma finalizacao e devolucao do estoque? (1-Sim, 0-Nao): ");
                        int confirmar;
                        scanf("%d", &confirmar);
                        
                        if(confirmar == 1) {
                            //devolve estoque
                            estornar_estoque_evento(id_evento);

                            //muda status pra finalizado
                            atual->dados.status = 2; 
                            reescrever_arquivo_eventos(listaEventos);
                            
                            exibir_mensagem_evento("Evento FINALIZADO com sucesso! Estoque liberado.");
                        }
                        encontrou = 1;
                        break;
                    }
                    atual = atual->proximo;
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
        
        if(opcao!=0) {
            pausar_tela_evento(); 
        }
        
    } while (opcao != 0);
    
    desalocar_lista_eventos(listaEventos);
    desalocar_lista_contas(listaContas);
}