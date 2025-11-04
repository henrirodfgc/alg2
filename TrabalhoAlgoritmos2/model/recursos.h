#ifndef RECURSOS_H
#define RECURSOS_H

//=============================================
//ESTRUTURAS DE DADOS (MODEL)
//o molde dos equipamentos
//=============================================

typedef struct {
    int codigo;
    char descricao[100];      //tipo "caixa de som" ou "projetor"
    char categoria[50];       //tipo "sonorização" ou "iluminação"
    int quantidade_estoque;   //qtos a gente tem na firma
    float preco_custo;        //o q custou pra comprar (vai mudar na compra)
    float valor_locacao;      //o q a gente cobra por dia (vai ser calculado)
} Equipamento;

//no da lista ligada p ter varios equips
typedef struct NoRecurso {
    Equipamento dados;
    struct NoRecurso *proximo;
} NoRecurso;

//=============================================
//FUNÇÕES DE MANIPULAÇÃO (CRUD)
//as paradas que o controller chama
//=============================================

//c: cria o no novo e bota na lista
NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso);

//r: acha o equip pelo codigo
Equipamento* buscar_recurso_por_codigo(NoRecurso* lista, int codigo_busca);

//u: troca os dados do equip q ja existe
void atualizar_recurso_por_codigo(NoRecurso* lista, int codigo_busca, const char* descricao, const char* categoria, int quantidade_estoque, float preco_custo, float valor_locacao);

//d: deleta o no (fisicamente msm)
NoRecurso* deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca);

//mt critica: libera a memoria p n dar memory leak
void desalocar_lista_recursos(NoRecurso* lista); 

//pra mostrar geral (o controller chama)
void exibir_todos_recursos(NoRecurso* lista); 

//=============================================
//FUTURO: PERSISTENCIA (CRITICA P/ 1A ENTREGA)
//lembrar q tem q fazer pra txt e binario
//=============================================
// void salvar_recursos_txt(NoRecurso* lista);
// NoRecurso* carregar_recursos_txt();
// void salvar_recursos_bin(NoRecurso* lista);
// NoRecurso* carregar_recursos_bin();

#endif