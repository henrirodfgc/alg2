#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/equipe.h"
#include "../view/equipe_view.h"
#include "equipe_controller.h"
#include "../controller/saida.h"

//lista ligada p guardar a equipe
NoEquipe *listaEquipe = NULL; 

//funcao q vai ter o menu e a logica principal da Equipe
void iniciar_equipe() {
    int opcao; //p guardar o que o user escolher
    int codigo_busca; //p achar o membro
    MembroEquipe temp; //membro temporário p leitura

    //o carregar recursos vai ser implementado pelo seu colega
    //listaEquipe = carregar_equipe(listaEquipe); 
    
    //loop principal da Equipe
    do {
        //chamam a função da View p exibir o menu
        opcao = exibir_menu_equipe(); //

        switch (opcao) {
            case 1: { //c: criar membro
                temp = ler_dados_membro(); //view lê todos os dados

                //confere se o código já existe (precisa ser único)
                if (buscar_membro_por_codigo(listaEquipe, temp.codigo) != NULL) {
                    exibir_mensagem_equipe("erro:ja existe um membro da equipe com este codigo.");
                    break;
                }
                
                //model cria o nó novo
                listaEquipe = adicionar_membro_na_lista(listaEquipe, temp);
                exibir_mensagem_equipe("membro da equipe criado com sucesso!");
                break;
            }
            case 2: { //u: atualizar membro
                codigo_busca = ler_codigo_para_operacao("atualizar"); //pede o código
                MembroEquipe *membro_encontrado = buscar_membro_por_codigo(listaEquipe, codigo_busca); //busca (Model)

                if (membro_encontrado == NULL) {
                    exibir_mensagem_equipe("erro:membro nao encontrado ou codigo invalido.");
                } else {
                    //variaveis temporárias p pegar os dados novos
                    char nome[50], cpf[12], funcao[50];
                    float valor_diaria_hora;

                    //view preenche essas variáveis
                    ler_dados_atualizacao_membro(nome, cpf, funcao, &valor_diaria_hora); //

                    //model atualiza a parada lá
                    atualizar_membro_por_codigo(listaEquipe, codigo_busca, nome, cpf, funcao, valor_diaria_hora);
                    
                    exibir_mensagem_equipe("membro da equipe atualizado com sucesso!");
                }
                break;
            }
            case 3: { //r: exibir um membro
                codigo_busca = ler_codigo_para_operacao("exibir"); //pede o código
                MembroEquipe *membro_encontrado = buscar_membro_por_codigo(listaEquipe, codigo_busca); //busca (Model)
                
                //view exibe ou avisa que não achou
                exibir_membro(membro_encontrado); //
                break;
            }
            case 4: { //d: inativar membro (soft delete) <--- MUDANCA AQUI!
                codigo_busca = ler_codigo_para_operacao("inativar"); //pede o código

                if (deletar_membro_por_codigo_logico(listaEquipe, codigo_busca)) {
                    exibir_mensagem_equipe("membro inativado com sucesso.");
                } else {
                    exibir_mensagem_equipe("erro:membro nao encontrado ou ja estava inativo.");
                }
                break;
            }
            case 5: { //r: listar todos (ativos)
                exibir_todos_membros(listaEquipe);
                break;
            }
            case 6: { //restaurar membro (reativar) <--- NOVO CASE!
                codigo_busca = ler_codigo_para_operacao("restaurar");
                
                restaurar_membro_por_codigo(listaEquipe, codigo_busca);
                
                //checa se deu certo buscando (agora como ativo)
                if (buscar_membro_por_codigo(listaEquipe, codigo_busca) != NULL) {
                    exibir_mensagem_equipe("membro restaurado para ativo.");
                } else {
                    exibir_mensagem_equipe("erro:membro nao encontrado ou ja estava ativo.");
                }
                break;
            }
            case 7: { //listar so inativos <--- NOVO CASE!
                exibir_membros_inativos(listaEquipe);
                break;
            }
            case 0:
                exibir_mensagem_equipe("saindo do modulo equipe. tchau!");
                break;
            default:
                exibir_mensagem_equipe("opcao invalida. tente novamente.");
        }
    } while (opcao != 0);

    //libera a memória no final do uso
    desalocar_lista_equipe(listaEquipe); 
}