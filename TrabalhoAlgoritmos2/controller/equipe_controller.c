#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Se for usar strncpy futuramente para segurança
#include "../model/equipe.h"
#include "../view/equipe_view.h" // Precisa estar funcional!
#include "equipe_controller.h"

//lista ligada p guardar a equipe
NoEquipe *listaEquipe = NULL; 

//função q vai ter o menu e a lógica principal da Equipe
void iniciar_equipe() {
    int opcao; //p guardar o que o user escolher
    int codigo_busca; //p achar o membro
    MembroEquipe temp; //membro temporário p leitura

    // [FUTURO]: Código de CARREGAMENTO de persistência (TXT/BIN) entra aqui
    
    //loop principal da Equipe
    do {
        //chamam a função da View p exibir o menu
        opcao = exibir_menu_equipe(); //

        switch (opcao) {
            case 1: { //c: criar membro
                temp = ler_dados_membro(); //view lê todos os dados

                //confere se o código já existe (precisa ser único)
                if (buscar_membro_por_codigo(listaEquipe, temp.codigo) != NULL) {
                    exibir_mensagem_equipe("erro: ja existe um membro da equipe com este codigo.");
                    break;
                }
                
                //model cria o nó novo
                listaEquipe = adicionar_membro_na_lista(listaEquipe, temp);
                exibir_mensagem_equipe("membro da equipe criado com sucesso!");
                break;
            }
            case 2: { //u: Atualizar membro
                codigo_busca = ler_codigo_para_operacao("atualizar"); //pede o código
                MembroEquipe *membro_encontrado = buscar_membro_por_codigo(listaEquipe, codigo_busca); //busca (Model)

                if (membro_encontrado == NULL) {
                    exibir_mensagem_equipe("erro: membro nao encontrado ou codigo invalido.");
                } else {
                    //variáveis temporárias p pegar os dados novos
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
            case 3: { //r: Exibir Um membro
                codigo_busca = ler_codigo_para_operacao("exibir"); //pede o código
                MembroEquipe *membro_encontrado = buscar_membro_por_codigo(listaEquipe, codigo_busca); //busca (Model)
                
                //view exibe ou avisa que não achou
                exibir_membro(membro_encontrado); //
                break;
            }
            case 4: { //d: deletar membro 
                codigo_busca = ler_codigo_para_operacao("deletar"); //pede o código

                if (buscar_membro_por_codigo(listaEquipe, codigo_busca) == NULL) {
                    exibir_mensagem_equipe("erro: membro nao encontrado para deletar.");
                    break;
                }
                
                //model remove o nó e libera a memória
                listaEquipe = deletar_membro_por_codigo(listaEquipe, codigo_busca);
                exibir_mensagem_equipe("membro da equipe deletado (removido fisicamente).");
                break;
            }
            case 5: { //r: listar Todos
                exibir_todos_membros(listaEquipe); // model faz a iteração, mas usa o printf simples (ou a View se for implementada)
                break;
            }
            case 0:
                exibir_mensagem_equipe("saindo do modulo equipe. Tchau!");
                break;
            default:
                exibir_mensagem_equipe("opcao invalida. Tente novamente.");
        }
    } while (opcao != 0);

    // [FUTURO]: Código de SALVAMENTO de persistência (TXT/BIN) entra aqui

    //libera a memória no final do uso
    desalocar_lista_equipe(listaEquipe); 
}