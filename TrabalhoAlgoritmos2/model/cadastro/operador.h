#ifndef OPERADOR_H
#define OPERADOR_H

typedef struct Operador {
    int codigo;
    char nome[50];
    char usuario[60];
    char senha[20];
    int status;
} Operador;

typedef struct NoOperador {
    Operador dados;
    struct NoOperador *proximo;
} NoOperador;

void copiar_dados_operador(Operador *destino, const Operador *origem);
NoOperador* adicionar_operador_na_lista(NoOperador* lista, Operador novo_operador);
void atualizar_operador_por_codigo(NoOperador* lista, int codigo, const char* nome, const char* usuario, const char* senha);
int deletar_operador_por_codigo(NoOperador* lista, int codigo);
Operador* buscar_operador_por_codigo(NoOperador* lista, int codigo);
void desalocar_lista_operador(NoOperador* lista);
NoOperador* carregar_operadores(NoOperador* lista);

#endif