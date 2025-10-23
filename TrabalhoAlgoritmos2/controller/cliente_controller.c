#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/cliente.h"
#include "../view/cliente_view.h"
#include "cliente_controller.h"

//lista ligada q guarda todos os clients tá ligado
//no começo e nulo tipo lista vazia
NoCliente *listaClientes = NULL; 

//a função q lê o id tá na view ent tô só dando um aviso aqui pro compilador
int ler_id_para_operacao(const char* operacao); 

//função principal q inicia o trampo a parada roda aqui
void iniciar_sistema() {
    int opcao; //pra ver o q o user escolheu no menu
    int id_busca; //pra guardar o id q a gente vai usar
    Cliente temp; //client temporário pra ler os dados rapidão

    //[futuro]: se for pra salvar em arquivo (persistência) o código pra carregar
    //os dados do arquivo pra lista ligada entra aqui
    
    //loop infinito até o cara digitar zero pra sair
    do {
        //mudei o menu (tem que mudar no cliente_view.c tambem!)
        printf("\n==== menu cliente ====\n");
        printf("1 - criar cliente\n");
        printf("2 - atualizar cliente\n");
        printf("3 - exibir cliente\n");
        printf("4 - deletar cliente (inativar)\n");
        printf("5 - listar todos (ativos)\n"); 
        printf("6 - restaurar cliente (reativar)\n"); 
        printf("7 - listar SÓ clientes INATIVOS (deletados)\n"); // <<-- MENU CORRIGIDO!
        printf("0 - sair\n");
        printf("escolha: ");
        scanf("%d", &opcao); //pega a escolha
        
        //se quiser usar a funcao exibir_menu() do view, tem que atualizar ela la!
        //opcao = exibir_menu(); 
        
        switch (opcao) {
            case 1: { //caso 1: criar um cliente
                temp = ler_dados_cliente(); //view lê tudo pra mim

                //confere se o id já existe pq tem q ser único né
                //o buscar cliente so retorna se o cliente ja esta ativo (status 1)
                if (buscar_cliente_por_id(listaClientes, temp.id) != NULL) {
                    exibir_mensagem("erro: já existe um cliente ativo com este id tente novamente");
                    break; //vaza e volta pro menu
                }
                
                //model cria o nó novo e eu atualizo a listaClientes
                listaClientes = adicionar_cliente_na_lista(listaClientes, temp);
                exibir_mensagem("cliente criado com sucesso");
                break;
            }
            case 2: { //caso 2: atualizar um cliente
                id_busca = ler_id_para_operacao("atualizar"); //pergunta qual id mudar
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca); //vê se ele existe (e está ativo)

                if (cliente_encontrado == NULL) {
                    exibir_mensagem("nenhum cliente ativo cadastrado com este id");
                } else {
                    //crio as variáveis rapidão pra pegar os dados novos da view
                    char nome[50], nome_razao[100], endereco[256], email[50], cpf[12], cnpj[15], telefone[20], nome_contato[50];
                    int idade;

                    //view preenche essas var aí com o q o user digitar
                    ler_dados_atualizacao(nome, &idade, endereco, nome_razao, email, cpf, cnpj, telefone, nome_contato); 

                    //mando o model atualizar a parada lá
                    //ordem mt importante: nome idade nome_razao cpf cnpj endereco email telefone nome_contato
                    atualizar_cliente_por_id(listaClientes, id_busca, nome, idade, nome_razao, cpf, cnpj, endereco, email, telefone, nome_contato);
                    
                    exibir_mensagem("cliente atualizado");
                }
                break;
            }
            case 3: { //caso 3: exibir só um cliente
                id_busca = ler_id_para_operacao("exibir"); //pede o id
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca); //procura (só ativos)
                exibir_cliente(cliente_encontrado); //view q mostra ou avisa q n achou
                break;
            }
            case 4: { //caso 4: deletar um cliente (soft delete)
                id_busca = ler_id_para_operacao("deletar"); //pede o id pra 'apagar'

                //o buscar cliente so retorna se o status for 1 (ativo)
                if (buscar_cliente_por_id(listaClientes, id_busca) == NULL) {
                     exibir_mensagem("nenhum cliente ativo para deletar com este id");
                     break;
                }
                
                //model muda o status do cliente pra 0 (inativo) e pronto
                deletar_cliente_por_id_logico(listaClientes, id_busca);
                exibir_mensagem("cliente marcado como deletado/inativo");
                break;
            }
            case 5: { //caso 5: lista todos os clients
                exibir_todos_clientes(listaClientes); //view mostra tudo (só ativos)
                break;
            }
            case 6: { //novo caso 6: restaurar cliente (reativar) - LÓGICA CORRIGIDA!
                id_busca = ler_id_para_operacao("restaurar"); //pede o id pra 'reativar'
                
                // Tentamos restaurar. Se o cliente existir e estiver inativo (status 0), ele será reativado (status 1).
                restaurar_cliente_por_id(listaClientes, id_busca);
                
                // Verifica se o cliente está ATIVO AGORA para confirmar se a restauração funcionou.
                Cliente *cliente_checado = buscar_cliente_por_id(listaClientes, id_busca);
                
                if (cliente_checado != NULL) {
                    // Se achou E está ativo, a restauração funcionou!
                    exibir_mensagem("cliente restaurado para ativo");
                } else {
                    // Se não achou (porque o ID não existe ou já estava ativo antes)
                    exibir_mensagem("erro: nenhum cliente (inativo) encontrado com este id para restaurar");
                }
                
                break;
            }
            case 7: { //caso 7: listar SÓ inativos
                // A função já foi corrigida para FILTRAR por status 0
                exibir_todos_clientes_e_inativos(listaClientes); 
                break;
            }
            case 0:
                exibir_mensagem("saindo");
                break;
            default:
                exibir_mensagem("opção inválida");
        }
    } while (opcao != 0); //fica aqui até o cara cansar e digitar zero

    // [futuro]: se for pra salvar em arquivo o código pra salvar os dados
    // da lista ligada de volta pro arquivo entra aqui

    //crítico: tem q desalocar a memória de todos os nós com free pra não dar memory leak 
    desalocar_lista_clientes(listaClientes);
}