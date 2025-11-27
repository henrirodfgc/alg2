#ifndef FORNECE_E_PARCE_H
#define FORNECE_E_PARCE_H

// =============================================
// estruturas de dados (model)
// onde fica o molde dos dados
// =============================================

typedef enum {
    TIPO_CPF,
    TIPO_CNPJ
} TipoDocumento;

// NOVO: Enum para os tipos de serviço
typedef enum {
    SERVICO_BUFFET,
    SERVICO_SEGURANCA,
    SERVICO_ATRACAO_MUSICAL
} TipoServico;

typedef struct {
    int id;
    char nome_fantasia[50];
    char nome_razao[100];
    char endereco[256];
    TipoDocumento tipo;
    char cpf[12]; 
    char cnpj[15]; 
    char telefone[20];
    TipoServico servico;
    int status;  // ALTERADO: agora é enum
} Fornecedores_e_parceiros;

//o nó da lista ligada pra dar pra ter vários clients ao mesmo tempo
typedef struct NoFornecedores_e_parceiros {
    Fornecedores_e_parceiros dados;              //guarda os dados do client mesmo
    struct NoFornecedores_e_parceiros *proximo;  //ponteiro pro proximo registro da lista
} NoFornecedores_e_parceiros;

// =============================================
// FUNÇÃO: copiar_dados_fornece_e_parce
// OBJETIVO: Copiar dados de uma estrutura para outra
// PARÂMETROS:
//   - destino: Ponteiro para estrutura de destino
//   - origem: Ponteiro para estrutura de origem
// =============================================
void copiar_dados_fornece_e_parce(Fornecedores_e_parceiros *destino, const Fornecedores_e_parceiros *origem);

// =============================================
// FUNÇÃO: adicionar_fornecedor_na_lista
// OBJETIVO: Adicionar novo fornecedor no início da lista encadeada
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - novo_fornecedor: Dados do novo fornecedor a ser adicionado
// RETORNO: Ponteiro para o novo início da lista
// =============================================
NoFornecedores_e_parceiros* adicionar_fornecedor_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_fornecedor);

// =============================================
// FUNÇÃO: adicionar_parceiros_na_lista
// OBJETIVO: Adicionar novo parceiro no início da lista encadeada
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - novo_parceiro: Dados do novo parceiro a ser adicionado
// RETORNO: Ponteiro para o novo início da lista
// =============================================
NoFornecedores_e_parceiros* adicionar_parceiros_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_parceiro);

// =============================================
// FUNÇÃO: atualizar_fornecedor_por_id
// OBJETIVO: Atualizar dados de um fornecedor existente baseado no ID
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - id_busca: ID do fornecedor a ser atualizado
//   - demais parâmetros: Novos dados para atualização
// =============================================
void atualizar_fornecedor_por_id(NoFornecedores_e_parceiros* lista, int id_busca, 
                                 const char* nome_fantasia, const char* razao_social, 
                                 const char* endereco, const char* cnpj, const char* telefone, 
                                 TipoServico servico);

// =============================================
// FUNÇÃO: atualizar_parceiro_por_id
// OBJETIVO: Atualizar dados de um parceiro existente baseado no ID
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - id_busca: ID do parceiro a ser atualizado
//   - demais parâmetros: Novos dados para atualização
// =============================================
void atualizar_parceiro_por_id(NoFornecedores_e_parceiros* lista, int id_busca, 
                                 const char* nome_fantasia, const char* razao_social, 
                                 const char* endereco, const char* cpf, const char* telefone, 
                                 TipoServico servico);                                 

// =============================================
// FUNÇÃO: deletar_fornece_e_parce_por_id
// OBJETIVO: Remover um registro da lista baseado no ID
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - id_busca: ID do registro a ser removido
// RETORNO: Ponteiro para o novo início da lista
// =============================================
NoFornecedores_e_parceiros* deletar_fornece_e_parce_por_id(NoFornecedores_e_parceiros* lista, int id_busca);

// =============================================
// FUNÇÃO: buscar_fornece_e_parce_por_id
// OBJETIVO: Buscar um registro na lista pelo ID
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - id_busca: ID do registro a ser encontrado
// RETORNO: Ponteiro para os dados do registro encontrado ou NULL
// =============================================
Fornecedores_e_parceiros* buscar_fornece_e_parce_por_id(NoFornecedores_e_parceiros* lista, int id_busca);

// =============================================
// FUNÇÃO: desalocar_lista_fornece_e_parce
// OBJETIVO: Liberar toda a memória alocada para a lista encadeada
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista a ser desalocada
// =============================================
void desalocar_lista_fornece_e_parce(NoFornecedores_e_parceiros* lista);

// =============================================
// FUNÇÃO: exibir_todas_fornece_e_parce
// OBJETIVO: Exibir no console todos os dados de todos os registros da lista
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
// =============================================
void exibir_todas_fornece_e_parce(NoFornecedores_e_parceiros* lista);

// =============================================
// FUNÇÃO: exibir_registro_por_id
// OBJETIVO: Exibir um registro específico baseado no ID
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - id: ID do registro a ser exibido
// =============================================
void exibir_registro_por_id(NoFornecedores_e_parceiros* lista, int id);

NoFornecedores_e_parceiros* carregar_fornecedores_e_parceiros(NoFornecedores_e_parceiros* lista);

#endif