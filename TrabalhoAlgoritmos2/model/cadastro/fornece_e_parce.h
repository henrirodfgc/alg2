#ifndef FORNECE_E_PARCE_H
#define FORNECE_E_PARCE_H

typedef enum {
    TIPO_CPF,
    TIPO_CNPJ
} TipoDocumento;

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
    int status; 
} Fornecedores_e_parceiros;

typedef struct NoFornecedores_e_parceiros {
    Fornecedores_e_parceiros dados;
    struct NoFornecedores_e_parceiros *proximo;
} NoFornecedores_e_parceiros;

NoFornecedores_e_parceiros* adicionar_fornecedor_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_fornecedor);
NoFornecedores_e_parceiros* adicionar_parceiros_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_parceiro);

void atualizar_fornecedor_por_id(NoFornecedores_e_parceiros* lista, int id_busca, char *nome_fantasia, char *razao_social, char *endereco, char *cnpj, char *telefone, TipoServico servico);
void atualizar_parceiro_por_id(NoFornecedores_e_parceiros* lista, int id_busca, char *nome_fantasia, char *razao_social, char *endereco, char *cpf, char *telefone, TipoServico servico);

NoFornecedores_e_parceiros* deletar_fornece_e_parce_por_id(NoFornecedores_e_parceiros *lista, int id_busca);
Fornecedores_e_parceiros* buscar_fornece_e_parce_por_id(NoFornecedores_e_parceiros* lista, int id_busca);
void desalocar_lista_fornece_e_parce(NoFornecedores_e_parceiros* lista);

//carregar dados
NoFornecedores_e_parceiros* carregar_fornecedores_e_parceiros(NoFornecedores_e_parceiros* lista);
int obter_proximo_id_fornece(NoFornecedores_e_parceiros* lista);

#endif