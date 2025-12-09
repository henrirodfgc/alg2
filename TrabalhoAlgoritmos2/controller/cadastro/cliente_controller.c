

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../model/cadastro/cliente.h"
#include "../../view/cadastro/cliente_view.h"
#include "cliente_controller.h"

//lista ligada *
NoCliente * listaClientes = NULL; 

//função da view
int ler_id_para_operacao(const char* operacao); 
int verificar_tipo_saida(); // Declaração da função auxiliar

//RECARREGA A LISTA (PARA MODOS TXT/BIN)
void recarregar_lista_se_necessario() {
    if (verificar_tipo_saida() != 3) {
        //libera a memória RAM
        desalocar_lista_clientes(listaClientes);
        //garante que a lista comece nula
        listaClientes = NULL;
        //recarrega a lista do arquivo (TXT ou BIN)
        listaClientes = carregar_clientes(listaClientes); 
    }
}

int obter_proximo_id_cliente(NoCliente* lista) {
    int maior_id = 0;
    NoCliente* atual = lista;
    while (atual != NULL) {
        if (atual->dados.id > maior_id) {
            maior_id = atual->dados.id;
        }
        atual = atual->proximo;
    }
    return maior_id + 1;
}

//função inicia módulo
void iniciar_sistema() {
    int opcao; 
    int id_busca; 
    Cliente temp; 

    //tentativa inicial de carregar (para preencher a lista na primeira vez)
    //se for modo memória, carrega o que foi salvo pra RAM
    //se for modo arquivo, carrega a versão do arquivo pra RAM
    listaClientes = carregar_clientes(listaClientes); 
    
    do {
        //exibe o menu e pega a opção do usuario
        opcao = exibir_menu(); 
        
        //sempre recarrega pra garantir que a lista na RAM esteja atualizada com o disco
        recarregar_lista_se_necessario();
        
        switch (opcao) {
            case 1: { //criar um cliente
                temp = ler_dados_cliente(); //view lê os dados

                temp.id = obter_proximo_id_cliente(listaClientes);
                    printf(">> ID gerado automaticamente: %d\n", temp.id);

                //validação de unicidade
                if (buscar_cliente_por_id(listaClientes, temp.id) != NULL) {
                    exibir_mensagem("erro:ja existe um cliente ativo com este id tente novamente");
                    break;
                }
                
                //model cria o nó novo e eu atualizo a listaClientes
                //no Modo Memória, o Model já insere na listaClientes
                //no Modo Arquivo, o Model escreve no disco e retorna a listaClientes inalterada
                listaClientes = adicionar_cliente_na_lista(listaClientes, temp);
                exibir_mensagem("cliente criado com sucesso");

                //se está no Modo Arquivo, precisamos atualizar a listaClientes na RAM
                recarregar_lista_se_necessario();
                break;
            }
            case 2: { //atualizar um cliente
                id_busca = ler_id_para_operacao("atualizar"); //pergunta qual id mudar
                if (id_busca == -1) { 
                    exibir_mensagem("erro:id invalido ou entrada mal formatada");
                    break;
                }
                
                Cliente *cliente_encontrado = buscar_cliente_por_id(listaClientes, id_busca); //vê se ele existe (e está ativo)

                if (cliente_encontrado == NULL) {
                    exibir_mensagem("nenhum cliente ativo cadastrado com este id");
                } else {
                    //crio as variáveis temporárias para pegar os dados novos da view
                    char nome[50], nome_razao[100], endereco[256], email[50], cpf[12], cnpj[15], telefone[20], nome_contato[50];
                    int idade;

                    //view preenche essas var aí com o que o user digitar
                    ler_dados_atualizacao(nome, &idade, endereco, nome_razao, email, cpf, cnpj, telefone, nome_contato); 

                    //mando o model atualizar a parada lá
                    atualizar_cliente_por_id(listaClientes, id_busca, nome, idade, nome_razao, cpf, cnpj, endereco, email, telefone, nome_contato);
                    
                    exibir_mensagem("cliente atualizado");
                    
                    //se a atualização envolveu o arquivo, recarregamos a lista da RAM
                    recarregar_lista_se_necessario();
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
                exibir_cliente(cliente_encontrado); //view que mostra ou avisa que não achou
                break;
            }
            case 4: { //deletar um cliente (soft delete)
                id_busca = ler_id_para_operacao("deletar"); 
                if (id_busca == -1) {
                    exibir_mensagem("erro:id invalido ou entrada mal formatada");
                    break;
                }
                
                if(deletar_cliente_por_id_logico(listaClientes, id_busca)){
                    exibir_mensagem("cliente deletado com sucesso!");
                }else{
                    exibir_mensagem("erro ao deletar cliente, talvez ja esteja inativo ou nao exista.");
                }
                
                recarregar_lista_se_necessario();
                break;
            }
            case 5: { //lista todos os clients ativos
                exibir_todos_clientes(listaClientes); //view mostra tudo
                break;
            }
            case 6: { //restaurar cliente (reativar)
                id_busca = ler_id_para_operacao("restaurar"); //pede o id para 'reativar'
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
                
                recarregar_lista_se_necessario();
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

    //desaloca a memória da listaClientes se estiver no Modo Memória (ou se não foi desalocada antes)
    desalocar_lista_clientes(listaClientes);
}