#ifndef ITEM_ORCAMENTO_H
#define ITEM_ORCAMENTO_H

//definicoes de tipos de item
#define TIPO_RECURSO 1
#define TIPO_EQUIPE 2
#define TIPO_SERVICO 3

typedef struct {
    int id;
    int id_evento;      
    int tipo_item;      //1=recurso, 2=equipe, 3=servico
    int id_estrangeiro; //id do recurso OU id da equipe OU id do fornecedor
    int quantidade;     //qtd ou horas (se for equipe)
    float valor_unitario; 
    float valor_total_item; 
    int status;         //1=ativo
} ItemOrcamento;

typedef struct NoItemOrcamento {
    ItemOrcamento dados;
    struct NoItemOrcamento *proximo;
} NoItemOrcamento;

//funcoes do model
NoItemOrcamento* adicionar_item_na_lista(NoItemOrcamento* lista, ItemOrcamento novo_item);
NoItemOrcamento* carregar_itens_orcamento(NoItemOrcamento* lista);
void desalocar_lista_itens(NoItemOrcamento* lista);

//funcoes de busca/calculo
NoItemOrcamento* buscar_itens_por_evento(NoItemOrcamento* lista, int id_evento); 
float calcular_total_evento(NoItemOrcamento* lista, int id_evento); 

#endif