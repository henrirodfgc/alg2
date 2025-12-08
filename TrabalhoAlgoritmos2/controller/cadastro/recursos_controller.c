#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/recursos.h"
#include "../../view/cadastro/recursos_view.h"
#include "recursos_controller.h"
#include "../../model/transacao/contas_pagar.h"

//lista dos recursos/equipamentos
NoRecurso *listaRecursos = NULL; 

//lista de contas a pagar (tem q tar aqui em cima)
static NoContaPagar *listaContasPagar = NULL;

void iniciar_recursos() {
    int opcao; 
    int codigo_busca; 
    Equipamento temp; 
    
    //carrega os dados
    listaRecursos = carregar_recursos(listaRecursos); 
    listaContasPagar = carregar_contas_pagar(listaContasPagar);
    
    do {
        opcao = exibir_menu_recursos(); 
        
        switch (opcao) {
            case 1: { //criar um equipamento
                temp = ler_dados_recurso();

                if (buscar_recurso_por_codigo(listaRecursos, temp.codigo) != NULL) {
                    exibir_mensagem_recursos("erro:ja existe um equipamento ativo com este codigo.");
                    break; 
                }
                
                //model cria o no novo
                listaRecursos = adicionar_recurso_na_lista(listaRecursos, temp);
                
                //calcula o custo total da compra
                float custo_aquisicao = temp.preco_custo * temp.quantidade_estoque;
                
                //gera a conta a pagar automatico
                listaContasPagar = gerar_nova_conta_pagar(listaContasPagar, temp.codigo, custo_aquisicao);
                
                exibir_mensagem_recursos("equipamento criado e conta a pagar gerada no financeiro!");
                break;
            }
            case 2: { //atualizar
                char descricao[100]; 
                char categoria[50]; 
                int quantidade_estoque; 
                float preco_custo; 
                float valor_locacao;
                
                codigo_busca = ler_codigo_para_operacao_recursos("atualizar");
                
                if (buscar_recurso_por_codigo(listaRecursos, codigo_busca) == NULL) {
                    exibir_mensagem_recursos("erro:recurso nao encontrado.");
                    break;
                }
                
                ler_dados_atualizacao_recurso(descricao, categoria, &quantidade_estoque, &preco_custo, &valor_locacao);
                
                atualizar_recurso_por_codigo(listaRecursos, codigo_busca, descricao, categoria, quantidade_estoque, preco_custo, valor_locacao);
                exibir_mensagem_recursos("recurso atualizado com sucesso.");
                break;
            }
            case 3: { //exibir
                codigo_busca = ler_codigo_para_operacao_recursos("exibir");
                Equipamento *recurso_encontrado = buscar_recurso_por_codigo(listaRecursos, codigo_busca);
                exibir_recurso(recurso_encontrado);
                break;
            }
            case 4: { //deletar
                codigo_busca = ler_codigo_para_operacao_recursos("deletar");
                if (codigo_busca == -1) {
                    exibir_mensagem_recursos("erro:id invalido ou entrada mal formatada");
                    break;
                }
                 
                if(deletar_recurso_por_codigo(listaRecursos, codigo_busca)){
                    exibir_mensagem_recursos("recurso deletado com sucesso!");
                }else{
                    exibir_mensagem_recursos("erro ao deletar recurso, talvez ja esteja inativo ou nao exista.");
                }
                break;
            }
            case 5: { //listar
                exibir_todos_recursos(listaRecursos);
                break;
            }
            case 0:
                exibir_mensagem_recursos("saindo do modulo de recursos.");
                break;
            default:
                exibir_mensagem_recursos("opcao invalida. tente novamente.");
        }
        
        if (opcao != 0) {
            printf("\npressione enter para continuar...");
            while (getchar() != '\n');
        }

    } while (opcao != 0);

    desalocar_lista_recursos(listaRecursos);
    //libera memoria
    desalocar_lista_contas_pagar(listaContasPagar);
}