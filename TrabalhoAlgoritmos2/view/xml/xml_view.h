#ifndef XML_VIEW_H
#define XML_VIEW_H

int exibir_menu_xml();
void exibir_mensagem_xml(const char* msg);
void exibir_cabecalho_importacao();
void exibir_progresso_xml(const char* msg);
void exibir_detalhe_importacao(const char* tipo, const char* valor);
void pausar_tela_xml();

#endif