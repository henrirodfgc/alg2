#include <stdlib.h>
#include <stdio.h> //pra getchar
#include "transacao_controller.h"
#include "../../model/transacao/contas_receber.h"
#include "../../model/transacao/caixa.h"
#include "../../view/transacao/transacao_view.h"
#include "../../model/transacao/contas_pagar.h"

static NoContaReceber *listaContasView = NULL;
static NoCaixa *listaCaixaView = NULL;
static NoContaPagar *listaPagarView = NULL;

extern void baixar_conta_receber(NoContaReceber* lista, int id_conta);
extern void baixar_conta_pagar(NoContaPagar* lista, int id_conta);

void iniciar_modulo_financeiro() {
    int opcao;
    
    listaContasView = carregar_contas_receber(listaContasView);
    listaPagarView = carregar_contas_pagar(listaPagarView);

    do {
        opcao = exibir_menu_financeiro();
        
        switch(opcao) {
            case 1:
                desalocar_lista_contas(listaContasView); listaContasView = NULL;
                listaContasView = carregar_contas_receber(NULL);
                exibir_lista_contas_receber(listaContasView);
                break;
            case 2: {
                listaCaixaView = carregar_extrato_caixa(NULL);
                
                printf("Deseja filtrar por data? (1-Sim / 0-Nao [Ver tudo]): ");
                int filtrar;
                scanf("%d", &filtrar);
                
                if (filtrar == 1) {
                    char inicio[12], fim[12];
                    printf("Data inicial (dd/mm/aaaa): "); scanf("%s", inicio);
                    printf("Data final (dd/mm/aaaa): "); scanf("%s", fim);
                    exibir_extrato_caixa_filtrado(listaCaixaView, inicio, fim);
                } else {
                    exibir_extrato_caixa_view(listaCaixaView);
                }
                
                desalocar_lista_caixa(listaCaixaView);
                break;
            }
            case 3: 
                desalocar_lista_contas_pagar(listaPagarView); listaPagarView = NULL;
                listaPagarView = carregar_contas_pagar(NULL);
                exibir_lista_contas_pagar(listaPagarView);
                break;
            case 4: { 
                printf("Digite o ID da conta a receber (pagamento do cliente): ");
                int id; scanf("%d", &id);
                baixar_conta_receber(listaContasView, id);
                break;
            }
            case 5: { 
                printf("Digite o ID da conta a pagar (fornecedor): ");
                int id; scanf("%d", &id);
                baixar_conta_pagar(listaPagarView, id);
                break;
            }
            case 0:
                exibir_mensagem_transacao("voltando...");
                break;
            default:
                exibir_mensagem_transacao("opcao invalida");
        }
        
        if(opcao != 0) {
            exibir_mensagem_transacao("pressione enter...");
            getchar(); getchar();
        }
        
    } while (opcao != 0);
    
    desalocar_lista_contas(listaContasView);
    desalocar_lista_contas_pagar(listaPagarView);
}