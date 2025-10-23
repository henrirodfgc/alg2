#include "controller/cliente_controller.h"
#include "controller/equipe_controller.h" // <<-- NOVO: Include da Equipe (Para que a função 'iniciar_equipe' funcione)
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
    
    // Funcao em saida_controller (bloco de escolha de persistência)
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
    } else {
        if(verificar_tipo_saida() == 1) {
            printf("Armazenamento tipo: TXT\n");
        } else if(verificar_tipo_saida() == 2) {
            printf("Armazenamento tipo: BIN\n");
        } else if(verificar_tipo_saida() == 3) {
            printf("Armazenamento tipo: Memória\n");
        }
    }

    // =============================
    // MENU PRINCIPAL (NOVO)
    // =============================
    int opcao_principal;
    do {
        printf("\n================================\n");
        printf("       MENU PRINCIPAL\n");
        printf("================================\n");
        printf("1 - Módulo Clientes\n");
        printf("2 - Módulo Equipe\n"); // <<-- NOVO: Chama a nova funcionalidade
        printf("0 - Fechar Sistema\n");
        printf("Escolha o módulo: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1:
                iniciar_sistema(); // Chama o controlador de Clientes
                break;
            case 2:
                iniciar_equipe(); // <<-- CHAMA O NOVO CONTROLLER DA EQUIPE
                break;
            case 0:
                printf("Encerrando o sistema. Tchau!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao_principal != 0);

    // Linha original 'iniciar_sistema();' é substituída pelo novo loop do menu.

    return 0;
}
