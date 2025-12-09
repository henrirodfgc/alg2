#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "ui_console.h"

void _set_cor(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

void ui_limpar_tela() {
    system("cls");
}

void ui_cabecalho(const char* titulo) {
    ui_limpar_tela();
    _set_cor(COR_CIANO);
    printf("========================================\n");
    printf("   %s\n", titulo);
    printf("========================================\n");
    _set_cor(COR_PADRAO);
    printf("\n");
}

void ui_sucesso(const char* msg) {
    _set_cor(COR_VERDE);
    printf("[SUCESSO] %s\n", msg);
    _set_cor(COR_PADRAO);
}

void ui_erro(const char* msg) {
    _set_cor(COR_VERMELHO);
    printf("[ERRO] %s\n", msg);
    _set_cor(COR_PADRAO);
}

void ui_aviso(const char* msg) {
    _set_cor(COR_AMARELO);
    printf("[!] %s\n", msg);
    _set_cor(COR_PADRAO);
}

void ui_menu_item(int opcao, const char* texto) {
    _set_cor(COR_BRANCO);
    printf("  %d", opcao);
    _set_cor(COR_PADRAO);
    printf(" - %s\n", texto);
}

void ui_input_style() {
    _set_cor(COR_AZUL);
    printf(">> ");
    _set_cor(COR_PADRAO);
}