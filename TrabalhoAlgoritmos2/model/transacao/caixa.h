#ifndef CAIXA_H
#define CAIXA_H

typedef struct {
    int id;
    char data[12];       //dd/mm/aaaa
    char descricao[100]; //ex: recebimento evento 10
    float valor;         
    int tipo;            //1=entrada, 0=saida
    float saldo_final;   //quanto sobrou no caixa depois disso
} LancamentoCaixa;

typedef struct NoCaixa {
    LancamentoCaixa dados;
    struct NoCaixa *proximo;
} NoCaixa;

//funcoes
void lancar_no_caixa(float valor, int tipo, const char* descricao);
void exibir_extrato_caixa();
float obter_saldo_atual();
NoCaixa* carregar_extrato_caixa(NoCaixa* lista);
void desalocar_lista_caixa(NoCaixa* lista);

#endif