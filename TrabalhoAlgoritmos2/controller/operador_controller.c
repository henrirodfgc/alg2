#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/operador.h"
#include "../view/operador_view.h"
#include "operador_controller.h"

void iniciar_operador(){

    NoOperador *listaOperador = NULL;
    int opcao;
    int codigo_busca;
    Operador temp;

    do
    {
        exibir_menu_operador();

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:{

            temp = ler_dados_operador();

            if (buscar_operador_por_codigo(listaOperador, temp.codigo) != NULL)
            {
                exibir_mensagem_operador("Erro: Já existe um operador com este código. Tente novamente");
                break;
            }else{

                listaOperador = adicionar_operador_na_lista(listaOperador, temp);
                exibir_mensagem_operador("Operador criado com sucesso");
            }
            break;
        }
       
       
        case 2:{

            int codigo_busca = ler_codigo_para_a_operacao("atualizar");

            Operador *operador_encontrado = buscar_operador_por_codigo(listaOperador, codigo_busca);

            if (operador_encontrado == NULL)
            {
                exibir_mensagem_operador("Nenhum operador cadastrado com este código");

                
            }else {

                int codigo;

                char nome[50], usuario[60], senha[20];

                ler_dados_atualizacao_operador(&codigo, nome, usuario, senha);

                atualizar_operador_por_codigo(listaOperador, codigo_busca, nome, usuario, senha);

                exibir_mensagem_operador("Operador atualizada com sucesso");
            }
            break;
        }

        case 3: {

            codigo_busca = ler_codigo_para_a_operacao("exibir");

            Operador *operador_encontrado = buscar_operador_por_codigo(listaOperador, codigo_busca);

            if (operador_encontrado != NULL)
            {
                exibir_operador(operador_encontrado);

            }else{ 
                exibir_mensagem_operador("Operador não encontrado");
            }
            break;
            
        }

        case 4: {

            codigo_busca = ler_codigo_para_a_operacao("deletar");

            if (buscar_operador_por_codigo(listaOperador, codigo_busca) == NULL)
            {
                exibir_mensagem_operador("Nenhum operador para deletar com este código");
                break;
            }

            listaOperador = deletar_operador_por_codigo(listaOperador, codigo_busca);
            exibir_mensagem_operador("Operador deletado com sucesso");
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

            exibir_mensagem_operador("Opção inválida! Tente novamente.");
            break;
        }

        if (opcao != 0)
        {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
        }
        
    } while (opcao !=0);

    deslocar_lista_operador(listaOperador);
    exibir_mensagem_operador("Memória liberada. Sistema encerrado");
    
}