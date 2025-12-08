#include <stdio.h>
#include <stdlib.h>
#include "xml_view.h"

int exibir_menu_xml() {
    int op;
    printf("\n=== modulo de integracao xml ===\n");
    printf("1 - exportar tudo para xml (backup)\n");
    printf("2 - importar de xml (restaurar)\n");
    printf("0 - voltar\n");
    printf("escolha: ");
    scanf("%d", &op);
    return op;
}

void exibir_mensagem_xml(const char* msg) {
    printf(">> %s\n", msg);
}

void exibir_cabecalho_importacao() {
    printf("\n--- simulando importacao de dados ---\n");
}

void exibir_progresso_xml(const char* msg) {
    printf(">> %s\n", msg);
}

void exibir_detalhe_importacao(const char* tipo, const char* valor) {
    printf("   importado %s: %s\n", tipo, valor);
}

void pausar_tela_xml() {
    printf("pressione enter...");
    while (getchar() != '\n'); 
    getchar();
}