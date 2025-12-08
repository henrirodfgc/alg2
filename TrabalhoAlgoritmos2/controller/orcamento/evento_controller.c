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
//lista de contas
static NoContaReceber *listaContas = NULL;

void iniciar_eventos() {
    int opcao;
    listaEventos = carregar_eventos(listaEventos); 
    listaClientes = carregar_clientes(listaClientes);
    //carregar contas
    listaContas = carregar_contas_receber(listaContas);
    
    do {
        opcao = exibir_menu_eventos();
        
        switch(opcao) {
            case 1: { //criar orcamento
                Evento novo = ler_dados_evento();
                
                Cliente *cliente_valido = buscar_cliente_por_id(listaClientes, novo.codigo_cliente);
                
                if (cliente_valido == NULL) {
                    exibir_mensagem_evento("erro:cliente nao encontrado. orcamento cancelado.");
                    break;
                }
                
                listaEventos = adicionar_evento_na_lista(listaEventos, novo);
                exibir_mensagem_evento("orcamento criado com sucesso!");
                
                printf(">> abrindo gerenciador de itens...\n");
                gerenciar_itens_de_um_evento(novo.codigo);
                break;
            }
            case 2: { //listar
                NoEvento *atual = listaEventos;
                if(!atual) exibir_mensagem_evento("nenhum evento cadastrado.");
                while(atual) {
                    exibir_evento(&(atual->dados));
                    atual = atual->proximo;
                }
                break;
            }
            case 3: { //aprovar evento
                int id_evento;
                printf("digite o id do evento para aprovar: ");
                scanf("%d", &id_evento);
                
                NoEvento *atual = listaEventos;
                int encontrou = 0;
                
                while(atual != NULL) {
                    if(atual->dados.codigo == id_evento) {
                        printf("evento: %s | status atual: %d\n", atual->dados.nome_evento, atual->dados.status);
                        
                        if(atual->dados.status == 1) {
                            exibir_mensagem_evento("este evento ja esta aprovado!");
                            encontrou = 1;
                            break;
                        }

                        printf("deseja aprovar? (1-sim, 0-nao): ");
                        int confirmar;
                        scanf("%d", &confirmar);
                        
                        if(confirmar == 1) {
                            atual->dados.status = 1; //aprovado
                            reescrever_arquivo_eventos(listaEventos);
                            
                            //gera conta a receber automatico
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
                
                if(!encontrou) exibir_mensagem_evento("evento nao encontrado.");
                break;
            }
            case 0:
                exibir_mensagem_evento("saindo de eventos...");
                break;
            default:
                exibir_mensagem_evento("opcao invalida");
        }
        
        if(opcao!=0) {
            printf("pressione enter...");
            getchar(); getchar(); 
        }
        
    } while (opcao != 0);
    
    desalocar_lista_eventos(listaEventos);
    //desalocar contas
    desalocar_lista_contas(listaContas);
}