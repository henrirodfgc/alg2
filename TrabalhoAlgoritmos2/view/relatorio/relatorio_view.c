#include <stdio.h>
#include <stdlib.h>
#include "relatorio_view.h"

int exibir_menu_relatorios() {
    int op;
    printf("\n=== MODULO DE RELATORIOS ===\n");
    printf("1 - Clientes (HTML / Navegador)\n");
    printf("2 - Clientes (CSV / Excel)\n");
    printf("3 - Eventos (HTML / Navegador)\n");
    printf("4 - Eventos (CSV / Excel)\n");
    printf("----------------------------------\n");
    printf("5 - Listagem de Equipamentos (HTML)\n"); 
    printf("6 - Cronograma de Alocacao de Recursos (HTML)\n"); 
    printf("7 - Relatorio Financeiro Completo (HTML)\n"); 
    printf("0 - Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

void exibir_mensagem_relatorio(const char* msg) {
    printf("%s\n", msg);
}

void pausar_tela_relatorio() {
    printf("Pressione ENTER para continuar...");
    while (getchar() != '\n'); 
    getchar();
}

void ler_filtro_na_view(const char* msg) {
    printf("%s", msg);
}