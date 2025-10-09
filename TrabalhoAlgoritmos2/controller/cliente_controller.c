#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/cliente.h"
#include "../view/cliente_view.h"
#include "cliente_controller.h"

//VARIÁVEL PRINCIPAL: A LISTA LIGADA (Memória RAM)
NoCliente *listaClientes = NULL; 

void iniciar_sistema() {
    int opcao;
    int id_busca;
    Cliente temp; 

    //O ponteiro 'cliente' que existia antes foi substituído por listaClientes.
    //O ponteiro temp é usado para capturar a struct preenchida da View.
    //********** PONTO DE ENTRADA DA PERSISTÊNCIA **********
    //Lógica para CARREGAR dados do arquivo (Texto/Binário) virá aqui.

    do {
        opcao = exibir_menu(); 
        switch (opcao) {
            case 1: { //CRIAR
                temp = ler_dados_cliente(); //Lendo TUDO

                if (buscar_cliente_por_id(listaClientes, temp.id) != NULL) {
                    exibir_mensagem("ERRO: Já existe um cliente com este ID. Tente novamente.");
                    break;
                }
                
                //O Model adiciona o nó e retorna a nova cabeça da lista.
                listaClientes = adicionar_cliente_na_lista(listaClientes, temp);
                exibir_mensagem("Cliente criado com sucesso!");
                break;
            }
            case 2: { //ATUALIZAR
                //1.LER ID e BUSCAR
                id_busca = ler_id_para_operacao("atualizar");
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca);

                if (cliente_encontrado == NULL) {
                    exibir_mensagem("Nenhum cliente cadastrado com este ID!");
                } else {
                    //2.LER NOVOS DADOS NA VIEW 
                    char nome[50], nome_razao[100], endereco[256], email[50], cpf[12], cnpj[15];
                    char telefone[20], nome_contato[50]; 
                    int idade;

                    //A View preenche as variáveis:
                    ler_dados_atualizacao(nome, &idade, endereco, nome_razao, email, cpf, cnpj, telefone, nome_contato); 

                    //3.ATUALIZAR: O Model usa os parâmetros para atualizar o registro na lista.
                    atualizar_cliente_por_id(listaClientes, id_busca, nome, idade, nome_razao, cpf, cnpj, endereco, email, telefone, nome_contato);
                    
                    exibir_mensagem("Cliente atualizado!");
                }
                break;
            }
            case 3: { //EXIBIR (APENAS UM)
                id_busca = ler_id_para_operacao("exibir");
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca);
                exibir_cliente(cliente_encontrado);
                break;
            }
            case 4: { //DELETAR
                id_busca = ler_id_para_operacao("deletar");

                if (buscar_cliente_por_id(listaClientes, id_busca) == NULL) {
                     exibir_mensagem("Nenhum cliente para deletar com este ID!");
                     break;
                }
                
                //O Model deleta e retorna a nova cabeça da lista
                listaClientes = deletar_cliente_por_id(listaClientes, id_busca);
                exibir_mensagem("Cliente deletado!");
                break;
            }
            case 5: { //NOVO: LISTAR TODOS
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

    // ********** PONTO DE SAÍDA DA PERSISTÊNCIA **********
    // Lógica para SALVAR dados do arquivo (Texto/Binário) virá aqui.
    // Libera a memória antes de encerrar
    desalocar_lista_clientes(listaClientes);
}