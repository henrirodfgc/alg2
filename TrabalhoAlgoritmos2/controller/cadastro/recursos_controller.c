#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/recursos.h"
#include "../../view/cadastro/recursos_view.h"
#include "recursos_controller.h"

//lista ligada q guarda os equipamentos
NoRecurso *listaRecursos = NULL; 

//funcao principal q inicia o trampo dos recursos
void iniciar_recursos() {
    int opcao; //pra ver o q o user escolheu no menu
    int codigo_busca; //pra guardar o codigo q a gente vai usar
    Equipamento temp; //equipamento temporario pra ler os dados rapidao
    
    //carrega os dados (so funciona se o outro implementar pra txt/bin)
    listaRecursos = carregar_recursos(listaRecursos); 
    
    //loop infinito ate o cara digitar zero pra sair
    do {
        //view exibe e pega a escolha
        opcao = exibir_menu_recursos(); 
        
        switch (opcao) {
            case 1: { //caso 1:criar um equipamento
                temp = ler_dados_recurso(); //view le tudo pra mim

                //confere se o codigo ja existe (so busca ativos)
                if (buscar_recurso_por_codigo(listaRecursos, temp.codigo) != NULL) {
                    exibir_mensagem_recursos("erro:ja existe um equipamento ativo com este codigo.");
                    break; //vaza e volta pro menu
                }
                
                //model cria o no novo e eu atualizo a lista (so em memoria)
                listaRecursos = adicionar_recurso_na_lista(listaRecursos, temp);
                exibir_mensagem_recursos("equipamento criado com sucesso.");
                break;
            }
            case 2: { //caso 2:atualizar um equipamento
                codigo_busca = ler_codigo_para_operacao_recursos("atualizar"); //pergunta qual codigo mudar
                Equipamento *recurso_encontrado = buscar_recurso_por_codigo(listaRecursos, codigo_busca); //ve se ele existe
                
                if (recurso_encontrado == NULL) {
                    exibir_mensagem_recursos("nenhum equipamento ativo cadastrado com este codigo.");
                } else {
                    //crio as variaveis rapidao pra pegar os dados novos da view
                    char descricao[100], categoria[50];
                    int quantidade_estoque;
                    float preco_custo, valor_locacao;

                    //view preenche essas var ai com o q o user digitar
                    ler_dados_atualizacao_recurso(descricao, categoria, &quantidade_estoque, &preco_custo, &valor_locacao); 

                    //mando o model atualizar a parada la (so atualiza em memoria)
                    atualizar_recurso_por_codigo(listaRecursos, codigo_busca, descricao, categoria, quantidade_estoque, preco_custo, valor_locacao);
                    
                    exibir_mensagem_recursos("equipamento atualizado.");
                }
                break;
            }
            case 3: { //caso 3:exibir so um equipamento
                codigo_busca = ler_codigo_para_operacao_recursos("exibir"); //pede o codigo
                Equipamento *recurso_encontrado = buscar_recurso_por_codigo(listaRecursos, codigo_busca); //procura (so ativos)
                exibir_recurso(recurso_encontrado); //view q mostra ou avisa q n achou
                break;
            }
            case 4: { //caso 4:deletar um equipamento (fisico)
                codigo_busca = ler_codigo_para_operacao_recursos("deletar"); //pede o codigo pra 'apagar'
                
                //tenta deletar o no e atualiza a cabeca da lista (so deleta em memoria)
                NoRecurso *antiga_lista = listaRecursos;
                listaRecursos = deletar_recurso_por_codigo(listaRecursos, codigo_busca);
                
                if (antiga_lista == listaRecursos) {
                    exibir_mensagem_recursos("erro:nenhum equipamento encontrado para deletar.");
                } else {
                    exibir_mensagem_recursos("equipamento deletado com sucesso.");
                }
                break;
            }
            case 5: { //caso 5:lista todos os equipamentos
                exibir_todos_recursos(listaRecursos); //model mostra tudo (so ativos em memoria)
                break;
            }
            case 0:
                exibir_mensagem_recursos("saindo do modulo de recursos.");
                break;
            default:
                exibir_mensagem_recursos("opcao invalida. tente novamente.");
        }
    } while (opcao != 0); //digitar 0 p sair 

    //critico:tem q desalocar a memoria se estiver em modo memoria
    desalocar_lista_recursos(listaRecursos);
}