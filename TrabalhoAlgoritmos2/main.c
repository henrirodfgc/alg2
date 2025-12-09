#include "controller/cadastro/cliente_controller.h"
#include "controller/cadastro/equipe_controller.h" 
#include "controller/cadastro/produtora_controller.h"
#include "controller/cadastro/fornece_e_parce_controller.h"
#include "controller/cadastro/recursos_controller.h" 
#include "controller/cadastro/operador_controller.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "controller/saida.h"
#include "controller/orcamento/evento_controller.h"
#include "controller/transacao/transacao_controller.h"
#include "controller/xml/xml_controller.h"
#include "controller/relatorio/relatorio_controller.h"
#include <time.h>
#include "ui_console.h" 


int main() {
    srand(time(NULL));
    system("chcp 65001");
    setlocale(LC_ALL, "pt-BR");
    
    char selec;
    char troca;
    
    if (verificar_tipo_saida() == 0) {
        ui_cabecalho("CONFIGURACAO INICIAL");
        printf("Escolha o tipo de armazenamento: \n");
        ui_menu_item(1, "[t] Arquivo Texto (TXT)");
        ui_menu_item(2, "[b] Arquivo Binario (BIN)");
        ui_menu_item(3, "[m] Memoria RAM (Volatil)");
        printf("\nEscolha a opcao: ");
        ui_input_style();
        
        char escolha;
        scanf(" %c", &escolha);

        FILE *file = fopen("../b_output/tipo_file.txt", "w");
        if(!file) file = fopen("b_output/tipo_file.txt", "w"); // Tenta local se falhar

        if (escolha == 't') {
            fprintf(file, "txt");
            ui_sucesso("Armazenamento definido como TXT.");
        } else if (escolha == 'b') {
            fprintf(file, "bin");
            ui_sucesso("Armazenamento definido como BINARIO.");
        } else if (escolha == 'm') {
            fprintf(file, "mem");
            ui_sucesso("Armazenamento definido como MEMORIA.");
        } else {
            ui_erro("Opcao invalida! Reinicie o sistema.");
            if(file) fclose(file);
            return 1;
        }
        if(file) fclose(file);
        system("pause");
    }
    else {

        ui_limpar_tela();
        ui_aviso("SISTEMA INICIADO");
        if(verificar_tipo_saida() == 1) printf("Armazenamento atual: ARQUIVO TXT\n");
        else if(verificar_tipo_saida() == 2) printf("Armazenamento atual: ARQUIVO BIN\n");
        else if(verificar_tipo_saida() == 3) printf("Armazenamento atual: MEMORIA RAM\n");

        do {
            printf("\nDeseja mudar o tipo de armazenamento?\n");
            printf("[s] Sim\n");
            printf("[n] Nao\n");
            ui_input_style();
            scanf(" %c", &selec);
            if (selec !='s' && selec != 'n') ui_erro("Opcao invalida");
        } while (selec !='s' && selec != 'n');

        if (selec == 's') {
            ui_cabecalho("TROCAR ARMAZENAMENTO");
            printf("[t] Para Txt\n");
            printf("[b] Para BIN\n");
            printf("[m] Para Memoria\n");
            printf("Escolha: ");
            ui_input_style();
            scanf(" %c", &troca);
            ui_aviso("Troca de armazenamento deve ser implementada no controller!");
        } else {
             ui_sucesso("Tipo mantido!");
        }
        system("pause");
    }

    int opcao_principal;
    do {
        ui_cabecalho("GESTAO DE EVENTOS - MENU PRINCIPAL");
        
        ui_menu_item(1, "Modulo Clientes");
        ui_menu_item(2, "Modulo Equipe");
        ui_menu_item(3, "Modulo Produtora");
        ui_menu_item(4, "Modulo Fornecedores e Parceiros");
        ui_menu_item(5, "Modulo Recursos e Equipamentos");
        ui_menu_item(6, "Modulo Operador");
        printf("----------------------------------------\n");
        ui_menu_item(7, "Modulo de Eventos e Orcamentos");
        ui_menu_item(8, "Modulo Financeiro");
        printf("----------------------------------------\n");
        ui_menu_item(9, "Modulo XML (Importar/Exportar)");
        ui_menu_item(10, "Relatorios Gerenciais (WEB/HTML)");
        printf("----------------------------------------\n");
        ui_menu_item(0, "Fechar Sistema");
        
        printf("\nEscolha o modulo: ");
        ui_input_style();
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1: iniciar_sistema(); break;
            case 2: iniciar_equipe(); break;
            case 3: iniciar_produtora(); break;
            case 4: iniciar_fornecedor_e_parceiro(); break; 
            case 5: iniciar_recursos(); break; 
            case 6: iniciar_operador(); break;    
            case 7: iniciar_eventos(); break;
            case 8: iniciar_modulo_financeiro(); break;
            case 9: iniciar_modulo_xml(); break;
            case 10: iniciar_modulo_relatorios(); break;
            case 0: ui_sucesso("Encerrando o sistema. Ate logo!"); break;
            default: ui_erro("Opcao invalida. Tente novamente."); system("pause");
        }
    } while (opcao_principal != 0);

    return 0;
}