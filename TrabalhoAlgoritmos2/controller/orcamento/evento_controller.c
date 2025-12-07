#include <stdlib.h>
#include <stdio.h>
#include "../../model/cadastro/cliente.h"
#include "../../model/orcamento/evento.h"
#include "../../view/orcamento/evento_view.h"
#include "evento_controller.h"

extern NoCliente * listaClientes;
NoCliente* carregar_clientes(NoCliente* lista);

static NoEvento *listaEventos = NULL;

void iniciar_eventos() {
    int opcao;
    listaEventos = carregar_eventos(listaEventos); //carrega pra n ter amnesia
    listaClientes = carregar_clientes(listaClientes);
    
    do {
        opcao = exibir_menu_eventos();
        
        switch(opcao) {
            case 1: { //criar orcamento
                Evento novo = ler_dados_evento();
                
                //novo: validacao de chave estrangeira (cliente deve existir e estar ativo)
                Cliente *cliente_valido = buscar_cliente_por_id(listaClientes, novo.codigo_cliente);
                
                if (cliente_valido == NULL) {
                    exibir_mensagem_evento("erro:cliente com este id nao foi encontrado. orcamento cancelado.");
                    break;
                }
                
                //aqui poderiamos verificar se o cliente existe, mas n da tempo agora
                listaEventos = adicionar_evento_na_lista(listaEventos, novo);
                exibir_mensagem_evento("orcamento criado com sucesso!");
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
                        //achou o evento
                        printf("evento: %s | status atual: %d\n", atual->dados.nome_evento, atual->dados.status);
                        printf("deseja aprovar? (1-sim, 0-nao): ");
                        int confirmar;
                        scanf("%d", &confirmar);
                        
                        if(confirmar == 1) {
                            atual->dados.status = 1; //muda pra aprovado na ram
                            
                            //salva a alteracao no arquivo
                            reescrever_arquivo_eventos(listaEventos);
                            
                            exibir_mensagem_evento("evento aprovado com sucesso!");
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
        
        //pause pra ler
        if(opcao!=0) {
            printf("Enter para continuar...");
            getchar(); getchar(); 
        }
        
    } while (opcao != 0);
    
    desalocar_lista_eventos(listaEventos);
}