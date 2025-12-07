#ifndef EVENTO_H
#define EVENTO_H

//estrutura basica do evento
typedef struct {
    int codigo;
    int codigo_cliente; //quem contratou
    char nome_evento[100];
    char data_inicio[12]; //formato dd/mm/aaaa
    char data_fim[12];
    int quantidade_convidados;
    float valor_total; //soma dos recursos + servicos
    int status; //0=orcamento, 1=aprovado, 2=finalizado, 3=cancelado(deletado)
} Evento;

//no da lista ligada
typedef struct NoEvento {
    Evento dados;
    struct NoEvento *proximo;
} NoEvento;

//funcoes do model
NoEvento* adicionar_evento_na_lista(NoEvento* lista, Evento novo_evento);
NoEvento* carregar_eventos(NoEvento* lista);
void exibir_todos_eventos(NoEvento* lista);
void desalocar_lista_eventos(NoEvento* lista);

//buscar evento
Evento* buscar_evento_por_codigo(NoEvento* lista, int codigo);

#endif