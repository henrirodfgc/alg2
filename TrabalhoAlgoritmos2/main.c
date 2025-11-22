#include "controller/cliente_controller.h"
#include "controller/equipe_controller.h" 
#include "controller/produtora_controller.h"
#include "controller/fornece_e_parce_controller.h"
#include "controller/operador_controller.h"
#include "controller/recursos_controller.h" // <<-- NOVO: INCLUDE PARA RECURSOS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "controller/saida.h"

// =============================
// PONTO DE ENTRADA DO SISTEMA
// =============================

int main() {
    system("chcp 65001");
    setlocale(LC_ALL, "pt-BR");
    char selec;
    char troca;
    //Funcao em saida_controller
   printf("bem-vindo\n");
    if (verificar_tipo_saida() == 0) {
    
    char escolha;
    printf("Escolha o tipo de armazenamento: \n");
    printf("[t] para Txt\n");
    printf("[b] para BIN\n");
    printf("[m] para Memória\n");
    printf("Escolha a opção: ");
    scanf(" %c", &escolha);

    FILE *file = fopen("../b_output/tipo_file.txt", "w");
    // salva a escolha no arquivo
    if (escolha == 't') {
        fprintf(file, "txt");
    } else if (escolha == 'b') {
        fprintf(file, "bin");
    } else if (escolha == 'm') {
        fprintf(file, "mem");
    } else {
        printf("Opção inválida!\n");
        fecharArquivos(file);
        return 1;
    }
    fecharArquivos(file);
    }
    else
        {
            if(verificar_tipo_saida() == 1)
            {
                printf("Armazenamento tipo: TXT\n");
            }else if(verificar_tipo_saida() == 2)
            {
                printf("Armazenamento tipo: BIN\n");
            }else if(verificar_tipo_saida() == 3)
            {
                printf("Armazenamento tipo: Memória\n");
            }

            do
            {
                printf("Deseja mudar o tipo armazenado ?\n");
                printf("[s] para sim\n");
                printf("[n] para nao\n");
                scanf(" %c", &selec);
                if (selec !='s' && selec != 'n')
                {
                    printf("opção inválida\n");
                }
                
            } while (selec !='s' && selec != 'n');
            

            if (selec=='s')
            {
                
                printf("Escolha o tipo de armazenamento: \n");
                printf("[t] para Txt\n");
                printf("[b] para BIN\n");
                printf("[m] para Memória\n");
                printf("Escolha a opção: ");
                scanf(" %c", &troca);
                
                int trocou = troca_txt_bin(troca);

                
            }
            else
            {
                 printf("tipo mantido!\n");
            }
        }

    // =============================
    // MENU PRINCIPAL (COMPLETO)
    // =============================
    int opcao_principal;
    do {
        printf("\n================================\n");
        printf("       MENU PRINCIPAL\n");
        printf("================================\n");
        printf("1 - Módulo Clientes\n");
        printf("2 - Módulo Equipe\n"); 
        printf("3 - Módulo Produtora\n");
        printf("4 - Módulo Fornecedores e Parceiros\n");
        printf("5 - Módulo Operador\n");
        printf("6 - Módulo Recursos e Equipamentos\n"); // <<-- NOVO AQUI!
        printf("0 - Fechar Sistema\n");
        printf("Escolha o módulo: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1:
                iniciar_sistema(); 
                break;
            case 2:
                iniciar_equipe(); 
                break;
            case 3:
                iniciar_produtora();
                break;
            case 4:
                iniciar_fornecedor_e_parceiro();
                break;
            case 5:
                iniciar_operador();
                break; // <-- BREAK MANTIDO AQUI
            case 6: // <<-- NOVO CASE!
                iniciar_recursos(); 
                break; 
            case 0:
                printf("Encerrando o sistema. Tchau!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao_principal != 0);

    return 0;
}