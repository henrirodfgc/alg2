#ifndef EQUIPE_H
#define EQUIPE_H

typedef struct {
    int codigo;
    char nome[50];
    char cpf [12];
    char funcao [50];
    float valor_diaria_hora;
    int status; 
} MembroEquipe;

typedef struct NoEquipe {
    MembroEquipe dados; 
    struct NoEquipe *proximo; 
} NoEquipe;

//operacoes do model
NoEquipe* adicionar_membro_na_lista(NoEquipe* lista, MembroEquipe novo_membro);

void atualizar_membro_por_codigo(NoEquipe* lista, int codigo_busca, const char* nome, const char* cpf, const char* funcao, float valor_diaria_hora);

//deletar fisico e logico
NoEquipe* deletar_membro_por_codigo(NoEquipe* lista, int codigo_busca);
int deletar_membro_por_codigo_logico(NoEquipe* lista, int codigo_busca);

void restaurar_membro_por_codigo(NoEquipe* lista, int codigo_busca);
void exibir_membros_inativos(NoEquipe* lista);

MembroEquipe* buscar_membro_por_codigo(NoEquipe* lista, int codigo_busca);
MembroEquipe* buscar_membro_qualquer_status(NoEquipe* lista, int codigo_busca);

void desalocar_lista_equipe(NoEquipe* lista); 
void exibir_todos_membros(NoEquipe* lista); 
NoEquipe* carregar_equipe(NoEquipe* lista);

#endif