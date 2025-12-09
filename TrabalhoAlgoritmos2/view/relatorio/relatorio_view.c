#include <stdio.h>
#include <stdlib.h>
#include "relatorio_view.h"

int exibir_menu_relatorios() {
    int op;
    printf("\n=== modulo de relatorios (web) ===\n");
    printf("1 - relatorio de clientes\n");
    printf("2 - relatorio de eventos\n");
    printf("0 - voltar\n");
    printf("escolha: ");
    scanf("%d", &op);
    return op;
}

void exibir_mensagem_relatorio(const char* msg) {
    printf("%s\n", msg);
}

void pausar_tela_relatorio() {
    printf("pressione enter...");
    while (getchar() != '\n'); 
    getchar();
}
void ler_filtro_na_view(const char* msg) {
    printf("%s", msg);
}
