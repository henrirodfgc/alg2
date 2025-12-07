#ifndef ITEM_ORCAMENTO_VIEW_H
#define ITEM_ORCAMENTO_VIEW_H

#include "../../model/orcamento/item_orcamento.h"

//pede os dados de um item(produto) pra por no evento
ItemOrcamento ler_dados_item_orcamento(int id_evento, int tipo);

//mostra a lista de itens de um evento
void exibir_lista_itens_evento(NoItemOrcamento* lista, int id_evento);

//menu especifico de itens
int exibir_menu_itens();

#endif