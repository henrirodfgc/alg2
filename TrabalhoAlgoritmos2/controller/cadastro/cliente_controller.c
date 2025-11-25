#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/cliente.h"
#include "../../view/cadastro/cliente_view.h"
#include "cliente_controller.h"

//lista ligada q guarda todos os clients tá ligado
//no começo e nulo tipo lista vazia
NoCliente * listaClientes = NULL; 

//a função q lê o id tá na view ent tô só dando um aviso aqui pro compilador
int ler_id_para_operacao(const char* operacao); 

//função principal q inicia roda aqui
void iniciar_sistema() {
    int opcao; //pra ver o q o user escolheu no menu
    int id_busca; //pra guardar o id q a gente vai usar
    Cliente temp; //client temporário pra ler os dados

    //carrega os dados do arquivo/binario/memoria logo no inicio
    listaClientes = carregar_clientes(listaClientes); 
    
    do {
        printf("\n==== menu cliente ====\n");
        printf("1 - criar cliente\n");
        printf("2 - atualizar cliente\n");
        printf("3 - exibir cliente\n");
        printf("4 - deletar cliente (inativar)\n");
        printf("5 - listar todos (ativos)\n"); 
        printf("6 - restaurar cliente (reativar)\n"); 
        printf("7 - listar so clientes inativos (deletados)\n"); 
        printf("0 - sair\n");
        printf("escolha: ");
        scanf("%d", &opcao); 
        
        //limpa o buffer depois de ler a opção de menu
        while (getchar() != '\n');
        
        switch (opcao) {
            case 1: { //criar um cliente
                temp = ler_dados_cliente(); //view lê

                //confere se o id já existe pq tem q ser unico
                //o buscar cliente so retorna se o cliente ja esta ativo (status 1)
                if (buscar_cliente_por_id(listaClientes, temp.id) != NULL) {
                    exibir_mensagem("erro:ja existe um cliente ativo com este id tente novamente");
                    break;
                }
                
                //model cria o nó novo e eu atualizo a listaClientes
                listaClientes = adicionar_cliente_na_lista(listaClientes, temp);
                exibir_mensagem("cliente criado com sucesso");
                break;
            }
            case 2: { //atualizar um cliente
                id_busca = ler_id_para_operacao("atualizar"); //pergunta qual id mudar
                if (id_busca == -1) { // -1 é o valor de erro da view
                     exibir_mensagem("erro:id invalido ou entrada mal formatada");
                     break;
                }
                
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
                    atualizar_cliente_por_id(listaClientes, id_busca, nome, idade, nome_razao, cpf, cnpj, endereco, email, telefone, nome_contato);
                    
                    exibir_mensagem("cliente atualizado");
                }
                break;
            }
            case 3: { //exibir só um cliente
                id_busca = ler_id_para_operacao("exibir"); //pede o id
                if (id_busca == -1) {
                     exibir_mensagem("erro:id invalido ou entrada mal formatada");
                     break;
                }
                
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca); //procura (só ativos)
                exibir_cliente(cliente_encontrado); //view q mostra ou avisa q n achou
                break;
            }
            case 4: { //caso 4: deletar um cliente (soft delete)
                id_busca = ler_id_para_operacao("deletar"); //pede o id pra 'apagar'
                if (id_busca == -1) {
                     exibir_mensagem("erro:id invalido ou entrada mal formatada");
                     break;
                }
                
                //model muda o status do cliente pra 0 (inativar) e pronto
                if(deletar_cliente_por_id_logico(listaClientes, id_busca)){
                    printf("cliente deletado com sucesso!");
                }else{
                    printf("erro ao deletar cliente, talvez ja esteja inativo ou nao exista.");
                }
                break;
            }
            case 5: { //caso 5: lista todos os clients
                exibir_todos_clientes(listaClientes); //view mostra tudo
                break;
            }
            case 6: { //novo caso 6: restaurar cliente (reativar)
                id_busca = ler_id_para_operacao("restaurar"); //pede o id pra 'reativar'
                if (id_busca == -1) {
                     exibir_mensagem("erro:id invalido ou entrada mal formatada");
                     break;
                }
                
                //tentamos restaurar.
                restaurar_cliente_por_id(listaClientes, id_busca);
                
                //verifica se o cliente está ativo agora para confirmar se a restauração funcionou.
                Cliente *cliente_checado = buscar_cliente_por_id(listaClientes, id_busca);
                
                if (cliente_checado != NULL) {
                    //se achou e está ativo, a restauração funcionou!
                    exibir_mensagem("cliente restaurado para ativo");
                } else {
                    //se não achou (porque o id não existe ou já estava ativo antes)
                    exibir_mensagem("erro:nenhum cliente (inativo) encontrado com este id para restaurar");
                }
                
                break;
            }
            case 7: { //listar só inativos
                exibir_todos_clientes_e_inativos(listaClientes); 
                break;
            }
            case 0:
                exibir_mensagem("saindo");
                break;
            default:
                exibir_mensagem("opcao invalida");
        }
    } while (opcao != 0); 

    //desaloca a memória 
    desalocar_lista_clientes(listaClientes);
}