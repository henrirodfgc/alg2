#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/cliente.h"
#include "../view/cliente_view.h"
#include "cliente_controller.h"

// Lista ligada q guarda todos os clients tá ligado
// No começo e nulo tipo lista vazia
NoCliente *listaClientes = NULL; 

// A função q lê o ID tá na view ent tô só dando um aviso aqui pro compilador
int ler_id_para_operacao(const char* operacao); 

// Função principal q inicia o trampo a parada roda aqui
void iniciar_sistema() {
    int opcao; // Pra ver o q o user escolheu no menu
    int id_busca; // Pra guardar o ID q a gente vai usar
    Cliente temp; // Client temporário pra ler os dados rapidão

    // [FUTURO]: Se for pra salvar em arquivo (persistência) o código pra CARREGAR
    // os dados do arquivo pra lista ligada entra aqui
    
    // Loop infinito até o cara digitar zero pra sair
    do {
        opcao = exibir_menu(); // Mostra o menu e pega a escolha na view
        switch (opcao) {
            case 1: { // CASO 1: CRIAR um client
                temp = ler_dados_cliente(); // View lê tudo pra mim

                // Confere se o ID já existe pq tem q ser único né
                if (buscar_cliente_por_id(listaClientes, temp.id) != NULL) {
                    exibir_mensagem("ERRO: Já existe um cliente com este ID Tente novamente");
                    break; // Vaza e volta pro menu
                }
                
                // Model cria o nó novo e eu atualizo a listaClientes
                listaClientes = adicionar_cliente_na_lista(listaClientes, temp);
                exibir_mensagem("Cliente criado com sucesso");
                break;
            }
            case 2: { // CASO 2: ATUALIZAR um client
                id_busca = ler_id_para_operacao("atualizar"); // Pergunta qual ID mudar
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca); // Vê se ele existe

                if (cliente_encontrado == NULL) {
                    exibir_mensagem("Nenhum cliente cadastrado com este ID");
                } else {
                    // Crio as variáveis rapidão pra pegar os dados novos da view
                    char nome[50], nome_razao[100], endereco[256], email[50], cpf[12], cnpj[15], telefone[20], nome_contato[50];
                    int idade;

                    // View preenche essas var aí com o q o user digitar
                    ler_dados_atualizacao(nome, &idade, endereco, nome_razao, email, cpf, cnpj, telefone, nome_contato); 

                    // Mando o Model atualizar a parada lá
                    // ORDEM MT IMPORTANTE: nome idade nome_razao CPF CNPJ endereco email telefone nome_contato
                    atualizar_cliente_por_id(listaClientes, id_busca, nome, idade, nome_razao, cpf, cnpj, endereco, email, telefone, nome_contato);
                    
                    exibir_mensagem("Cliente atualizado");
                }
                break;
            }
            case 3: { // CASO 3: Exibir SÓ UM client
                id_busca = ler_id_para_operacao("exibir"); // Pede o ID
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca); // Procura
                exibir_cliente(cliente_encontrado); // View q mostra ou avisa q n achou
                break;
            }
            case 4: { // CASO 4: Deletar um client
                id_busca = ler_id_para_operacao("deletar"); // Pede o ID pra apagar

                if (buscar_cliente_por_id(listaClientes, id_busca) == NULL) {
                     exibir_mensagem("Nenhum cliente para deletar com este ID");
                     break;
                }
                
                // Model deleta e libera a memória e eu atualizo a lista caso o primeiro tenha vazado
                listaClientes = deletar_cliente_por_id(listaClientes, id_busca);
                exibir_mensagem("Cliente deletado");
                break;
            }
            case 5: { // CASO 5: Lista todos os clients
                exibir_todos_clientes(listaClientes); // View mostra tudo
                break;
            }
            case 0:
                exibir_mensagem("Saindo");
                break;
            default:
                exibir_mensagem("Opção inválida");
        }
    } while (opcao != 0); // Fica aqui até o cara cansar e digitar zero

    // [FUTURO]: Se for pra salvar em arquivo o código pra SALVAR os dados
    // da lista ligada de volta pro arquivo entra aqui

    // CRÍTICO: Tem q desalocar a memória de todos os nós com free pra não dar memory leak 
    desalocar_lista_clientes(listaClientes);
}