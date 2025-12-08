#ifndef CONTAS_PAGAR_H
#define CONTAS_PAGAR_H

typedef struct {
    int id;
    int id_recurso_compra; //link com o equipamento comprado
    float valor_total; 
    char data_vencimento[12]; 
    int status;            //0=pendente, 1=pago
} ContaPagar;

typedef struct NoContaPagar {
    ContaPagar dados;
    struct NoContaPagar *proximo;
} NoContaPagar;

NoContaPagar* gerar_nova_conta_pagar(NoContaPagar* lista, int id_recurso, float valor);
NoContaPagar* carregar_contas_pagar(NoContaPagar* lista);
void desalocar_lista_contas_pagar(NoContaPagar* lista);

#endif