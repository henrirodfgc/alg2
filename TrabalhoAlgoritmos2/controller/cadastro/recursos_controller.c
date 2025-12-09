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

int obter_proximo_codigo_recurso(NoRecurso* lista) {
    int maior = 0;
    NoRecurso* atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo > maior) {
            maior = atual->dados.codigo;
        }
        atual = atual->proximo;
    }
    return maior + 1;
}

void processar_entrada_nota_fiscal() {
    float frete_total, imposto_total, margem_lucro_padrao;
    int qtd_itens_nf = 0;
    
    typedef struct {
        Equipamento equip;
    } ItemTemp;
    ItemTemp itens[50]; 
    
    exibir_mensagem_recursos("\n--- Nova Nota Fiscal de Entrada ---");
    printf("Valor TOTAL do Frete na Nota: "); scanf("%f", &frete_total);
    printf("Valor TOTAL de Impostos na Nota: "); scanf("%f", &imposto_total);
    printf("Margem de Lucro Padrao (%%) para estes itens: "); scanf("%f", &margem_lucro_padrao);
    
    int continuar = 1;
    while(continuar && qtd_itens_nf < 50) {
        Equipamento *e = &itens[qtd_itens_nf].equip;
        
        printf("\nItem #%d da Nota:\n", qtd_itens_nf + 1);
        printf("Codigo: "); scanf("%d", &e->codigo);
        if(buscar_recurso_por_codigo(listaRecursos, e->codigo) != NULL) {
            printf("Erro: Codigo %d ja existe! Use outro.\n", e->codigo);
            continue;
        }
        
        int ch; while ((ch = getchar()) != '\n' && ch != EOF); 
        printf("Descricao: "); scanf("%99[^\n]", e->descricao);
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Categoria: "); scanf("%49[^\n]", e->categoria);
        printf("Qtd Comprada: "); scanf("%d", &e->quantidade_estoque);
        printf("Preco Custo Unitario: "); scanf("%f", &e->preco_custo);
        
        e->status = 1;
        qtd_itens_nf++;
        
        printf("Adicionar outro item? (1-Sim / 0-Nao): ");
        scanf("%d", &continuar);
    }
    
    if (qtd_itens_nf > 0) {
        int soma_quantidades = 0;
        float valor_total_nota = frete_total + imposto_total; // Começa com as taxas
        
        for(int i=0; i<qtd_itens_nf; i++) {
            soma_quantidades += itens[i].equip.quantidade_estoque;
            valor_total_nota += (itens[i].equip.preco_custo * itens[i].equip.quantidade_estoque);
        }
        
        float frete_por_unidade = frete_total / soma_quantidades;
        float imposto_por_unidade = imposto_total / soma_quantidades;
        
        printf("\n>> Processando Entrada...\n");
        printf(">> Rateio: Frete/unid = %.2f | Imposto/unid = %.2f\n", frete_por_unidade, imposto_por_unidade);
        
        for(int i=0; i<qtd_itens_nf; i++) {
            Equipamento *e = &itens[i].equip;
            
            float custo_final_unitario = e->preco_custo + frete_por_unidade + imposto_por_unidade;
            
            e->valor_locacao = custo_final_unitario * (margem_lucro_padrao / 100.0);
            
            listaRecursos = adicionar_recurso_na_lista(listaRecursos, *e);
            printf("   Salvo: %s (Locacao: %.2f)\n", e->descricao, e->valor_locacao);
        }
        
        listaContasPagar = gerar_nova_conta_pagar(listaContasPagar, itens[0].equip.codigo, valor_total_nota);
        exibir_mensagem_recursos(">> Nota Fiscal lancada e Conta a Pagar gerada com sucesso!");
    }
}

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

                temp.codigo = obter_proximo_codigo_recurso(listaRecursos);
                printf(">> Codigo gerado automaticamente: %d\n", temp.codigo);
                
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
            case 2: { 
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
            case 3: { 
                codigo_busca = ler_codigo_para_operacao_recursos("exibir");
                Equipamento *recurso_encontrado = buscar_recurso_por_codigo(listaRecursos, codigo_busca);
                exibir_recurso(recurso_encontrado);
                break;
            }
            case 4: { 
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
            case 5: { 
                exibir_todos_recursos(listaRecursos);
                break;
            }
            case 6: 
                processar_entrada_nota_fiscal();
                break;
            case 0:
                exibir_mensagem_recursos("saindo do modulo de recursos.");
                break;
            default:
                exibir_mensagem_recursos("opcao invalida. tente novamente.");
        }
        

    } while (opcao != 0);

    desalocar_lista_recursos(listaRecursos);
    //libera memoria
    desalocar_lista_contas_pagar(listaContasPagar);
}
