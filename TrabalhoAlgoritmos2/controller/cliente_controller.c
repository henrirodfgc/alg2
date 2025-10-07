#include <stdlib.h>
#include "../model/cliente.h"
#include "../view/cliente_view.h"
#include "cliente_controller.h"

void iniciar_sistema() {
    Cliente* cliente = NULL;
    int opcao;

    do {
        opcao = exibir_menu();
        switch (opcao) {
            case 1: {
                // Usamos a função com retorno
                Cliente temp = ler_dados_cliente();

                if (cliente) {
                    exibir_mensagem("Já existe um cliente. Delete-o antes de criar outro.");
                } else {
                    
                    cliente = criar_cliente(temp.id, temp.nome_cliente, temp.idade, temp.nome_razao, temp.cpf, temp.cnpj, temp.endereco, temp.email);
                    exibir_mensagem("Cliente criado com sucesso!");
                }
                break;
            }
            case 2: {
                if (!cliente) {
                    exibir_mensagem("Nenhum cliente cadastrado!");
                } else {
                    
                    char nome[50];
                    int idade;
                    char endereco[256]; 
                    char nome_razao[100];
                    char email[50]; 
                    char cpf[12]; 
                    char cnpj[15]; 

                    
                    ler_dados_atualizacao(nome, &idade, endereco, nome_razao, email, cpf, cnpj);
                    
                    
                    atualizar_cliente(cliente, nome, idade, nome_razao, cpf, cnpj, endereco, email);
                    exibir_mensagem("Cliente atualizado!");
                }
                break;
            }
            case 3:
                exibir_cliente(cliente);
                break;
            case 4:
                if (!cliente) {
                    exibir_mensagem("Nenhum cliente para deletar!");
                } else {
                    deletar_cliente(cliente);
                    cliente = NULL;
                    exibir_mensagem("Cliente deletado!");
                }
                break;
            case 0:
                exibir_mensagem("Saindo...");
                break;
            default:
                exibir_mensagem("Opção inválida!");
        }
    } while (opcao != 0);

    if (cliente) deletar_cliente(cliente);
}