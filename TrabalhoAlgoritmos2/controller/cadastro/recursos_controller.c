#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/recursos.h"
#include "../../view/cadastro/recursos_view.h"
#include "recursos_controller.h"

//lista dos recursos/equipamentos
NoRecurso *listaRecursos = NULL; 

void iniciar_recursos() {
    int opcao; //pra ver o q o usuario escolheu no menu
    int codigo_busca; //pra guardar o codigo q a gente vai usar
    Equipamento temp; //variavel temporaria dos r/e 
    
    //carrega os dados
    listaRecursos = carregar_recursos(listaRecursos); 
    
    do {
        //view exibe e pega a escolha
        opcao = exibir_menu_recursos(); 
        
        switch (opcao) {
            case 1: { //criar um equipamento
                temp = ler_dados_recurso();

                //confere se o codigo ja existe
                if (buscar_recurso_por_codigo(listaRecursos, temp.codigo) != NULL) {
                    exibir_mensagem_recursos("erro:ja existe um equipamento ativo com este codigo.");
                    break; 
                }
                
                //model cria o nó novo e atualiza a lista
                listaRecursos = adicionar_recurso_na_lista(listaRecursos, temp);
                exibir_mensagem_recursos("equipamento criado com sucesso.");
                break;
            }
            case 2: { //atualizar um equipamento
                codigo_busca = ler_codigo_para_operacao_recursos("atualizar"); //pergunta qual codigo mudar
                Equipamento *recurso_encontrado = buscar_recurso_por_codigo(listaRecursos, codigo_busca); //ve se ele existe
                
                if (recurso_encontrado == NULL) {
                    exibir_mensagem_recursos("nenhum equipamento ativo cadastrado com este codigo.");
                } else {
                    //cria variaveis temporarias 
                    char descricao[100], categoria[50];
                    int quantidade_estoque;
                    float preco_custo, valor_locacao;

                    //view preenche essas var com os dados digitados
                    ler_dados_atualizacao_recurso(descricao, categoria, &quantidade_estoque, &preco_custo, &valor_locacao); 

                    //atualiza
                    atualizar_recurso_por_codigo(listaRecursos, codigo_busca, descricao, categoria, quantidade_estoque, preco_custo, valor_locacao);
                    
                    exibir_mensagem_recursos("equipamento atualizado.");
                }
                break;
            }
            case 3: { //exibir so um equipamento
                codigo_busca = ler_codigo_para_operacao_recursos("exibir"); //pede o codigo
                Equipamento *recurso_encontrado = buscar_recurso_por_codigo(listaRecursos, codigo_busca); //procura
                exibir_recurso(recurso_encontrado); //view q mostra ou avisa q n achou
                break;
            }
            case 4: { //caso 4:deletar um equipamento
                codigo_busca = ler_codigo_para_operacao_recursos("deletar");
                if (codigo_busca == -1)
                {
                    exibir_mensagem_recursos("erro:id invalido ou entrada mal formatada");
                    break;
                }
                 
                //tenta deletar o no e atualiza a cabeca da lista
                if(deletar_recurso_por_codigo(listaRecursos, codigo_busca)){
                    exibir_mensagem_recursos("recurso deletado com sucesso!");
                }else{
                    exibir_mensagem_recursos("erro ao deletar recurso, talvez ja esteja inativo ou nao exista.");
                }
                break;
            }
            case 0:
                exibir_mensagem_recursos("saindo do modulo de recursos.");
                break;
            default:
                exibir_mensagem_recursos("opcao invalida. tente novamente.");
        }
    } while (opcao != 0);

    //tem q desalocar a memoria se estiver em modo memoria
    desalocar_lista_recursos(listaRecursos);
}