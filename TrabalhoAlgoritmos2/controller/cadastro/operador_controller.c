#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/operador.h"
#include "../../view/cadastro/operador_view.h"
#include "operador_controller.h"

NoOperador *listaOperador = NULL;

int obter_proximo_codigo_operador(NoOperador* lista) {
    int maior = 0;
    NoOperador* atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo > maior) {
            maior = atual->dados.codigo;
        }
        atual = atual->proximo;
    }
    return maior + 1;
}

void iniciar_operador() {
    int opcao;
    Operador temp;
    int codigo_busca;

    listaOperador = carregar_operadores(listaOperador);

    do {
        opcao = exibir_menu_operador();

        switch(opcao) {
            case 1: { 
                temp = ler_dados_operador();
                
                temp.codigo = obter_proximo_codigo_operador(listaOperador);
                printf(">> Codigo gerado automaticamente: %d\n", temp.codigo);

                if (buscar_operador_por_codigo(listaOperador, temp.codigo) != NULL) {
                    exibir_mensagem_operador("Erro: Ja existe um operador com este codigo.");
                } else {
                    listaOperador = adicionar_operador_na_lista(listaOperador, temp);
                    exibir_mensagem_operador("Operador criado com sucesso");
                }
                break;
            }
            case 2: { // Atualizar
                codigo_busca = ler_codigo_para_a_operacao("atualizar");
                Operador* op = buscar_operador_por_codigo(listaOperador, codigo_busca);
                
                if (op) {
                    char nome[50], usuario[50], senha[20];
                    ler_dados_atualizacao_operador(nome, usuario, senha);
                    atualizar_operador_por_codigo(listaOperador, codigo_busca, nome, usuario, senha);
                    exibir_mensagem_operador("Operador atualizado com sucesso");
                } else {
                    exibir_mensagem_operador("Nenhum operador cadastrado com este codigo");
                }
                break;
            }
            case 3: {
                codigo_busca = ler_codigo_para_a_operacao("exibir");
                Operador* op = buscar_operador_por_codigo(listaOperador, codigo_busca);
                if (op) exibir_operador(op);
                else exibir_mensagem_operador("Operador nao encontrado");
                break;
            }
            case 4: {
                codigo_busca = ler_codigo_para_a_operacao("deletar");
                if (deletar_operador_por_codigo(listaOperador, codigo_busca)) {
                    exibir_mensagem_operador("operador deletado com sucesso");
                } else {
                    exibir_mensagem_operador("Erro ao deletar ou Operador nao encontrado");
                }
                break;
            }
            case 5: {
                exibir_todos_operadores(listaOperador);
                break;
            }
            case 0:
                exibir_mensagem_operador("Saindo dos sistema de operadores...");
                break;
            default:
                exibir_mensagem_operador("Opcao invalida! Tente novamente.");
        }
    } while(opcao != 0);
}