#ifndef TRANSACAO_VIEW_H
#define TRANSACAO_VIEW_H

#include "../../model/transacao/contas_receber.h"
#include "../../model/transacao/caixa.h"
#include "../../model/transacao/contas_pagar.h"

void exibir_lista_contas_receber(NoContaReceber* lista);
void exibir_extrato_caixa_view(NoCaixa* lista);
void exibir_mensagem_transacao(const char* msg);
int exibir_menu_financeiro();
void exibir_lista_contas_pagar(NoContaPagar* lista);


#endif