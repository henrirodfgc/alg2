#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ui_console.h"

int _get_largura_console() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void ui_set_cor(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

void ui_posicionar(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ui_limpar_tela() {
    system("cls");
}

void ui_moldura(int x, int y, int largura, int altura, int cor) {
    ui_set_cor(cor);
    
    // Topo
    ui_posicionar(x, y);
    printf("%c", 201); 
    for(int i=0; i<largura-2; i++) printf("%c", 205); 
    printf("%c", 187); 

    // Laterais
    for(int i=1; i<altura-1; i++) {
        ui_posicionar(x, y+i);
        printf("%c", 186); 
        ui_posicionar(x+largura-1, y+i);
        printf("%c", 186); 
    }

    ui_posicionar(x, y+altura-1);
    printf("%c", 200); 
    for(int i=0; i<largura-2; i++) printf("%c", 205); 
    printf("%c", 188); 
    
    ui_set_cor(COR_PADRAO);
}

void ui_texto_centralizado(int y, const char* texto, int cor) {
    int largura = _get_largura_console();
    int len = strlen(texto);
    int x = (largura - len) / 2;
    if (x < 0) x = 0;
    
    ui_posicionar(x, y);
    ui_set_cor(cor);
    printf("%s", texto);
    ui_set_cor(COR_PADRAO);
}

void ui_cabecalho(const char* titulo) {
    ui_limpar_tela();
    int largura = 60;
    int x_centro = (_get_largura_console() - largura) / 2;
    
    ui_moldura(x_centro, 1, largura, 3, COR_CIANO);
    ui_texto_centralizado(2, titulo, COR_BRANCO);
    
    ui_posicionar(0, 5);
}

void ui_barra_carregamento(const char* texto) {
    int largura_total = 40;
    int x_centro = (_get_largura_console() - largura_total) / 2;
    int y_centro = 10;

    ui_limpar_tela();
    ui_texto_centralizado(y_centro - 2, texto, COR_BRANCO);
    
    
    ui_posicionar(x_centro, y_centro);
    printf("[");
    ui_posicionar(x_centro + largura_total + 1, y_centro);
    printf("]");

    ui_set_cor(COR_VERDE);
    for(int i=0; i<=largura_total; i++) {
        ui_posicionar(x_centro + 1 + i, y_centro);
        printf("%c", 219); 
        Sleep(30); 
    }
    ui_set_cor(COR_PADRAO);
    Sleep(500); 
}

void ui_splash_logo() {
    ui_limpar_tela();
    int y = 5;
    int cor = COR_AZUL;
    
    // Logo simples em ASCII
    ui_texto_centralizado(y++, "  ___  ___  ___  ___  _____ ", cor);
    ui_texto_centralizado(y++, " / __||_ _|| __||  \\||_   _|", cor);
    ui_texto_centralizado(y++, " \\__ \\ | | | _| | |) |  | |  ", cor);
    ui_texto_centralizado(y++, " |___/|___||___||___/   |_|  ", cor);
    ui_texto_centralizado(y++, "                             ", cor);
    ui_texto_centralizado(y++, "   EVENT MANAGER 2025 PRO    ", COR_CIANO);
    
    ui_texto_centralizado(y+4, "Desenvolvido para Algoritmos II", COR_PADRAO);
    
    Sleep(1500);
}

void ui_sucesso(const char* msg) {
    ui_set_cor(COR_VERDE);
    printf("  [OK] %s\n", msg);
    ui_set_cor(COR_PADRAO);
}

void ui_erro(const char* msg) {
    ui_set_cor(COR_VERMELHO);
    printf("  [ERRO] %s\n", msg);
    ui_set_cor(COR_PADRAO);
}

void ui_aviso(const char* msg) {
    ui_set_cor(COR_AMARELO);
    printf("  [!] %s\n", msg);
    ui_set_cor(COR_PADRAO);
}

void ui_menu_item(int opcao, const char* texto) {
    ui_set_cor(COR_CIANO);
    printf("   %d", opcao);
    ui_set_cor(COR_PADRAO);
    printf(" - %s\n", texto);
}

void ui_input_style() {
    ui_set_cor(COR_VERDE);
    printf("  >> ");
    ui_set_cor(COR_PADRAO);
}