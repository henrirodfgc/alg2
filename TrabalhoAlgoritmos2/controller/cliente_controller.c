#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/cliente.h"
#include "../view/cliente_view.h"
#include "cliente_controller.h"

//cabeça da lista ligada 
//substitui o antigo 'Cliente* cliente = NULL;' e armazena os registros
NoCliente *listaClientes = NULL; 

//botei a função 'ler_id_para_operacao' na view
int ler_id_para_operacao(const char* operacao); 

void iniciar_sistema() {
    int opcao;
    int id_busca;
    Cliente temp; 

    // [INTEGRAÇÃO PERSISTÊNCIA FUTURA]: Chamada para CARREGAR dados do arquivo (Texto/Binário) virá aqui.
    
    do {
        opcao = exibir_menu(); 
        switch (opcao) {
            case 1: { //CRIAR
                temp = ler_dados_cliente(); //view le todos os campos

                //verifica se o id é unico antes de criar
                if (buscar_cliente_por_id(listaClientes, temp.id) != NULL) {
                    exibir_mensagem("ERRO: Já existe um cliente com este ID. Tente novamente.");
                    break;
                }
                
                //adiciona o nó e o controller atualiza a cabeça da lista
                listaClientes = adicionar_cliente_na_lista(listaClientes, temp);
                exibir_mensagem("Cliente criado com sucesso!");
                break;
            }
            case 2: { //ATUALIZAR
                id_busca = ler_id_para_operacao("atualizar");
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca);

                if (cliente_encontrado == NULL) {
                    exibir_mensagem("Nenhum cliente cadastrado com este ID!");
                } else {
                    //variáveis para receber os campos da view
                    char nome[50], nome_razao[100], endereco[256], email[50], cpf[12], cnpj[15], telefone[20], nome_contato[50];
                    int idade;

                    //view preenche as variáveis
                    ler_dados_atualizacao(nome, &idade, endereco, nome_razao, email, cpf, cnpj, telefone, nome_contato); 

                    //model localiza o nó pelo id e copia os novos parametros
                    atualizar_cliente_por_id(listaClientes, id_busca, nome, idade, nome_razao, email, cpf, cnpj, endereco, telefone, nome_contato);
                    
                    exibir_mensagem("Cliente atualizado!");
                }
                break;
            }
            case 3: { //exibir 1
                id_busca = ler_id_para_operacao("exibir");
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca);
                exibir_cliente(cliente_encontrado); // Se for NULL, a View exibe a mensagem de erro.
                break;
            }
            case 4: { //deletar
                id_busca = ler_id_para_operacao("deletar");

                if (buscar_cliente_por_id(listaClientes, id_busca) == NULL) {
                     exibir_mensagem("Nenhum cliente para deletar com este ID!");
                     break;
                }
                
                //model deleta e controller atualiza
                listaClientes = deletar_cliente_por_id(listaClientes, id_busca);
                exibir_mensagem("Cliente deletado!");
                break;
            }
            case 5: { //lista todos os clientes
                exibir_todos_clientes(listaClientes);
                break;
            }
            case 0:
                exibir_mensagem("Saindo...");
                break;
            default:
                exibir_mensagem("Opção inválida!");
        }
    } while (opcao != 0);

    // [INTEGRAÇÃO PERSISTÊNCIA FUTURA]: Chamada para SALVAR dados no arquivo virá aqui.

    //libera a memoria dos nós antes de encerrar
    desalocar_lista_clientes(listaClientes);
}