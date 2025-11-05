#ifndef EQUIPE_H
#define EQUIPE_H

//=============================================
//ESTRUTURAS DE DADOS (MODEL)
//pra guardar os dados de cada membro da equipe interna
//=============================================

typedef struct {
    int codigo;
    char nome[50];
    char cpf [12];
    char funcao [50];
    float valor_diaria_hora;
    int status; //campo do soft delete
} MembroEquipe;


//nó da lista ligada p ter mais de um registro
typedef struct NoEquipe {
MembroEquipe dados;  //guarda os dados do funcionario
struct NoEquipe *proximo; //aponta para o proximo registro da lista
} NoEquipe;

//=============================================
//FUNÇÕES DE MANIPULAÇÃO (CRUD)
//operações do Model
//=============================================

//cria o nó copia os dados e retorna a nova cabeça da lista
NoEquipe* adicionar_membro_na_lista(NoEquipe* lista, MembroEquipe novo_membro);

//atualiza os dados de um membro q já existe pelo código
void atualizar_membro_por_codigo(NoEquipe* lista, int codigo_busca, const char* nome, const char* cpf, const char* funcao, float valor_diaria_hora);

//remove o nó libera a memoria e retorna a nova cabeça da lista
NoEquipe* deletar_membro_por_codigo(NoEquipe* lista, int codigo_busca);

//procura um membro pelo código e retorna o ponteiro pra struct MembroEquipe
MembroEquipe* buscar_membro_por_codigo(NoEquipe* lista, int codigo_busca);

//mt crítica: libera a memória de todos os nós da lista pra n dar memory leak
void desalocar_lista_equipe(NoEquipe* lista); 

//função pra mostrar todos os membros (pra view usar)
void exibir_todos_membros(NoEquipe* lista); 

#endif