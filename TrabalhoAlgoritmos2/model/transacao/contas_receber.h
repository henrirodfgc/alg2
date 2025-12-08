#ifndef CONTAS_RECEBER_H
#define CONTAS_RECEBER_H

typedef struct {
    int id;
    int id_evento;      //link com o evento gerador
    int id_cliente;     //quem tem que pagar
    float valor_total; 
    char data_vencimento[12]; //dd/mm/aaaa
    int status;         //0=pendente, 1=pago
} ContaReceber;

typedef struct NoContaReceber {
    ContaReceber dados;
    struct NoContaReceber *proximo;
} NoContaReceber;

//funcoes principais
NoContaReceber* gerar_nova_conta(NoContaReceber* lista, int id_evento, int id_cliente, float valor);
NoContaReceber* carregar_contas_receber(NoContaReceber* lista);
void listar_contas_receber(NoContaReceber* lista);
void desalocar_lista_contas(NoContaReceber* lista);

//funcao pra baixar(pagar) a conta - extra pra ficar bonito
void baixar_conta_receber(NoContaReceber* lista, int id_conta);

#endif