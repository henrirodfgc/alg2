#ifndef EVENTO_VIEW_H
#define EVENTO_VIEW_H

#include "../../model/orcamento/evento.h"

int exibir_menu_eventos();
Evento ler_dados_evento();
void exibir_evento(const Evento* e);
void exibir_mensagem_evento(const char* msg);

#endif