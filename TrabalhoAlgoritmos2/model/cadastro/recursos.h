#ifndef RECURSOS_H
#define RECURSOS_H

typedef struct {
    int codigo;
    char descricao[100];       
    char categoria[50];        
    int quantidade_estoque;    
    float preco_custo;         
    float valor_locacao;       
    int status;                
} Equipamento;

typedef struct NoRecurso {
    Equipamento dados;
    struct NoRecurso *proximo;
} NoRecurso;

NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso);

Equipamento* buscar_recurso_por_codigo(NoRecurso* lista, int codigo_busca);

void atualizar_recurso_por_codigo(NoRecurso* lista, int codigo_busca, const char* descricao, const char* categoria, int quantidade_estoque, float preco_custo, float valor_locacao);

int deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca);

void desalocar_lista_recursos(NoRecurso* lista);

void exibir_todos_recursos(NoRecurso* lista);

void exibir_mensagem_recursos(const char* msg);

NoRecurso* carregar_recursos(NoRecurso* lista);

void reescrever_arquivo_recursos(NoRecurso* lista);

#endif