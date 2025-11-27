#ifndef OPERADOR_H
#define OPERADOR_H

typedef struct Operador{
    int codigo;
    char nome[50];
    char usuario[60];
    char senha[20];
    int status;
}Operador;

typedef struct NoOperador
{
    Operador dados;
    struct NoOperador *proximo;
}NoOperador;


NoOperador* adicionar_operador_na_lista(NoOperador* lista, Operador novo_operador);

void atualizar_operador_por_codigo(NoOperador* lista, int codigo_busca, const char* nome, const char* usuario, const char* senha);

int deletar_operador_por_codigo(NoOperador* lista, int codigo_busca);

void restaurar_operador_por_codigo(NoOperador* lista, int codigo_busca);

Operador* buscar_operador_por_codigo(NoOperador* lista, int codigo_busca);

void deslocar_lista_operador(NoOperador* lista);

void exibir_todos_operadores(NoOperador* lista);

void exibir_mensagem_operador(const char* msg);

NoOperador* carregar_operadores(NoOperador* lista);

#endif
