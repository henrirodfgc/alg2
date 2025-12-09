#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H

#define COR_PADRAO 7
#define COR_AZUL 9
#define COR_VERDE 10
#define COR_CIANO 11
#define COR_VERMELHO 12
#define COR_AMARELO 14
#define COR_BRANCO 15

void ui_limpar_tela();
void ui_cabecalho(const char* titulo);
void ui_sucesso(const char* msg);
void ui_erro(const char* msg);
void ui_aviso(const char* msg);
void ui_menu_item(int opcao, const char* texto);
void ui_input_style();

#endif