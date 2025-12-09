#ifndef PRODUTORA_H
#define PRODUTORA_H

typedef struct Produtora{
    char nome_fantasia[50];
    char razao_social[100];
    char inscricao_estadual[9];
    char cnpj[14];
    char endereco_completo[256];
    char telefone[11];
    char email[50];
    char nome_do_responsavel[50];
    char telefone_do_responsavel[11];
    char margem_de_lucro_padrao[6]; 
    int status;  
} Produtora;

typedef struct NoProdutora {
    Produtora dados;
    struct NoProdutora *proximo;
} NoProdutora;

void copiar_dados_produtora(Produtora *destino, const Produtora *origem);
NoProdutora* adicionar_produtora_na_lista(NoProdutora* lista, Produtora nova_produtora);

void atualizar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca, 
                                 const char* nome_fantasia, const char* razao_social, 
                                 const char* inscricao_estadual, 
                                 const char* endereco_completo, const char* telefone, 
                                 const char* email, const char* nome_do_responsavel, 
                                 const char* margem_de_lucro_padrao, // CHAR*
                                 const char* telefone_do_responsavel);

int deletar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca);
Produtora* buscar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca);
void desalocar_lista_produtoras(NoProdutora* lista);
void exibir_todas_produtoras(NoProdutora* lista);
NoProdutora* carregar_produtoras(NoProdutora* lista);

#endif