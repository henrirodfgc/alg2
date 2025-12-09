#include <stdlib.h>
#include <stdio.h> //pra getchar
#include "transacao_controller.h"
#include "../../model/transacao/contas_receber.h"
#include "../../model/transacao/caixa.h"
#include "../../view/transacao/transacao_view.h"
#include "../../model/transacao/contas_pagar.h"

//listas locais para visualizacao
static NoContaReceber *listaContasView = NULL;
static NoCaixa *listaCaixaView = NULL;
static NoContaPagar *listaPagarView = NULL;

void iniciar_modulo_financeiro() {
    int opcao;
    
    do {
        opcao = exibir_menu_financeiro();
        
        switch(opcao) {
            case 1:
                listaContasView = carregar_contas_receber(NULL); //recarrega sempre pra ver atualizado
                exibir_lista_contas_receber(listaContasView);
                desalocar_lista_contas(listaContasView); //limpa da memoria dps de mostrar
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
                listaPagarView = carregar_contas_pagar(NULL);
                exibir_lista_contas_pagar(listaPagarView);
                desalocar_lista_contas_pagar(listaPagarView);
                break;
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
}