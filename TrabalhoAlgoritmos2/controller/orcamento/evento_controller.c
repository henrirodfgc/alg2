#include <stdlib.h>
#include <stdio.h>
#include "../../model/cadastro/cliente.h"
#include "../../model/orcamento/evento.h"
#include "../../view/orcamento/evento_view.h"
#include "evento_controller.h"
#include "item_orcamento_controller.h"
#include "../../model/transacao/contas_receber.h"

extern NoCliente * listaClientes;
extern NoCliente* carregar_clientes(NoCliente* lista);

static NoEvento *listaEventos = NULL;
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
                        exibir_evento(&(atual->dados)); //Mostra o evento pra confirmar
                        
                        if(atual->dados.status == 1) {
                            exibir_mensagem_evento("este evento ja esta aprovado!");
                            encontrou = 1;
                            break;
                        }

                        int confirmar = confirmar_aprovacao_view();
                        
                        if(confirmar == 1) {
                            atual->dados.status = 1; 
                            reescrever_arquivo_eventos(listaEventos);
                            
                            listaContas = gerar_nova_conta(listaContas, 
                                             atual->dados.codigo, 
                                             atual->dados.codigo_cliente, 
                                             atual->dados.valor_total);
                            
                            exibir_mensagem_evento("evento aprovado e fatura gerada com sucesso!");
                        }
                        encontrou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                
                if(!encontrou && id_evento != 0) exibir_mensagem_evento("evento nao encontrado.");
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