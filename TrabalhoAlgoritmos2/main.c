#include "controller/cliente_controller.h"
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
    
    //Funcao em saida_controller
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
}else
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

        }
            
            

       
        

    
     iniciar_sistema();

    return 0;
}
