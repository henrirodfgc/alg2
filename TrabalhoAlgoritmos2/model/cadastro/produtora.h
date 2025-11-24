#ifndef PRODUTORA_H
#define PRODUTORA_H

// =============================================
// ESTRUTURA: Produtora
// OBJETIVO: Armazenar os dados básicos de uma produtora
// =============================================
typedef struct Produtora{
    char nome_fantasia[50];           // Nome comercial/fantasia da produtora
    char razao_social[100];           // Razão social oficial (registro jurídico)
    char inscricao_estadual[9];       // Número de inscrição estadual (8 dígitos + \0)
    char cnpj[14];                    // CNPJ (13 dígitos + \0) - identificador único
    char endereco_completo[256];      // Endereço completo (rua, número, cidade, etc.)
    char telefone[11];                // Telefone da empresa (10 dígitos + \0)
    char email[50];                   // E-mail de contato
    char nome_do_responsavel[50];     // Nome do responsável legal
    char telefone_do_responsavel[11]; // Telefone do responsável
    char margem_de_lucro_padrao[6];// Margem de lucro padrão em formato string
    int status;  
} Produtora;


// =============================================
// ESTRUTURA: NoProdutora
// OBJETIVO: Nó para lista encadeada de produtoras
// =============================================
typedef struct NoProdutora {
    Produtora dados;                 // Dados da produtora
    struct NoProdutora *proximo;     // Ponteiro para o próximo nó da lista
} NoProdutora;

// =============================================
// FUNÇÃO: copiar_dados_produtora
// OBJETIVO: Copiar dados de uma estrutura Produtora para outra
// PARÂMETROS:
//   - destino: Ponteiro para estrutura de destino
//   - origem: Ponteiro para estrutura de origem
// =============================================
void copiar_dados_produtora(Produtora *destino, const Produtora *origem);

// =============================================
// FUNÇÃO: adicionar_produtora_na_lista
// OBJETIVO: Adicionar nova produtora no início da lista encadeada
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - nova_produtora: Dados da nova produtora a ser adicionada
// RETORNO: Ponteiro para o novo início da lista
// =============================================
NoProdutora* adicionar_produtora_na_lista(NoProdutora* lista, Produtora nova_produtora);

// =============================================
// FUNÇÃO: atualizar_produtora_por_cnpj
// OBJETIVO: Atualizar dados de uma produtora existente baseado no CNPJ
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - cnpj_busca: CNPJ da produtora a ser atualizada
//   - demais parâmetros: Novos dados para atualização
// =============================================
void atualizar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca, 
                                 const char* nome_fantasia, const char* razao_social, 
                                 const char* inscricao_estadual, 
                                 const char* endereco_completo, const char* telefone, 
                                 const char* email, const char* nome_do_responsavel, 
                                 const char* margem_de_lucro_padrao, 
                                 const char* telefone_do_responsavel);

// =============================================
// FUNÇÃO: deletar_produtora_por_cnpj
// OBJETIVO: Remover uma produtora da lista baseado no CNPJ
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - cnpj_busca: CNPJ da produtora a ser removida
// RETORNO: Ponteiro para o novo início da lista
// =============================================
NoProdutora* deletar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca);

// =============================================
// FUNÇÃO: buscar_produtora_por_cnpj
// OBJETIVO: Buscar uma produtora na lista pelo CNPJ
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - cnpj_busca: CNPJ da produtora a ser encontrada
// RETORNO: Ponteiro para os dados da produtora encontrada ou NULL
// =============================================
Produtora* buscar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca);

// =============================================
// FUNÇÃO: desalocar_lista_produtoras
// OBJETIVO: Liberar toda a memória alocada para a lista encadeada
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista a ser desalocada
// =============================================
void desalocar_lista_produtoras(NoProdutora* lista);

// =============================================
// FUNÇÃO: exibir_todas_produtoras
// OBJETIVO: Exibir no console todos os dados de todas as produtoras da lista
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
// =============================================
void exibir_todas_produtoras(NoProdutora* lista);

#endif
