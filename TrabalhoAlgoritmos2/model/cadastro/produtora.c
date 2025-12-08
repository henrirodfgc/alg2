#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtora.h"
#include "../../view/cadastro/produtora_view.h"
#include "../../controller/saida.h"

void extrair_valor(char* destino, const char* token, int tamanho_max) {
    char* dois_pontos = strchr(token, ':');
    if (dois_pontos) {
        strncpy(destino, dois_pontos + 1, tamanho_max - 1);
        destino[tamanho_max - 1] = '\0';
    } else {
        strcpy(destino, "");
    }
}

void copiar_dados_produtora(Produtora *destino, const Produtora *origem) {
    if (!origem || !destino) return;
    strncpy(destino->cnpj, origem->cnpj, sizeof(destino->cnpj) - 1);
    destino->cnpj[sizeof(destino->cnpj) - 1] = '\0';
    strncpy(destino->nome_fantasia, origem->nome_fantasia, sizeof(destino->nome_fantasia) - 1);
    destino->nome_fantasia[sizeof(destino->nome_fantasia) - 1] = '\0';
    strncpy(destino->razao_social, origem->razao_social, sizeof(destino->razao_social) - 1);
    destino->razao_social[sizeof(destino->razao_social) - 1] = '\0';
    strncpy(destino->inscricao_estadual, origem->inscricao_estadual, sizeof(destino->inscricao_estadual) - 1);
    destino->inscricao_estadual[sizeof(destino->inscricao_estadual) - 1] = '\0';
    strncpy(destino->endereco_completo, origem->endereco_completo, sizeof(destino->endereco_completo) - 1);
    destino->endereco_completo[sizeof(destino->endereco_completo) - 1] = '\0';
    strncpy(destino->telefone, origem->telefone, sizeof(destino->telefone) - 1);
    destino->telefone[sizeof(destino->telefone) - 1] = '\0';
    strncpy(destino->email, origem->email, sizeof(destino->email) - 1);
    destino->email[sizeof(destino->email) - 1] = '\0';
    strncpy(destino->nome_do_responsavel, origem->nome_do_responsavel, sizeof(destino->nome_do_responsavel) - 1);
    destino->nome_do_responsavel[sizeof(destino->nome_do_responsavel) - 1] = '\0';
    strncpy(destino->telefone_do_responsavel, origem->telefone_do_responsavel, sizeof(destino->telefone_do_responsavel) - 1);
    destino->telefone_do_responsavel[sizeof(destino->telefone_do_responsavel) - 1] = '\0';
    strncpy(destino->margem_de_lucro_padrao, origem->margem_de_lucro_padrao, sizeof(destino->margem_de_lucro_padrao) - 1);
    destino->margem_de_lucro_padrao[sizeof(destino->margem_de_lucro_padrao) - 1] = '\0';
    destino->status = origem->status;
}

NoProdutora* adicionar_produtora_na_lista(NoProdutora* lista, Produtora nova_produtora) {
    NoProdutora *novo_no = (NoProdutora*) malloc(sizeof(NoProdutora));
    if (novo_no == NULL) return lista;
    nova_produtora.status = 1;
    copiar_dados_produtora(&(novo_no->dados), &nova_produtora);
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/produtora/produtora.txt", "a");
        if (!file) file = fopen("../b_output/produtora/produtora.txt", "a");
        if (file) {
            fprintf(file, "nome_fantasia:%s,razao_social:%s,inscricao_estadual:%s,cnpj:%s,endereco:%s,telefone:%s,email:%s,responsavel:%s,telefone_responsavel:%s,margem_lucro:%s,status:%d\n",
                nova_produtora.nome_fantasia, nova_produtora.razao_social, nova_produtora.inscricao_estadual,
                nova_produtora.cnpj, nova_produtora.endereco_completo, nova_produtora.telefone,
                nova_produtora.email, nova_produtora.nome_do_responsavel, nova_produtora.telefone_do_responsavel,
                nova_produtora.margem_de_lucro_padrao, nova_produtora.status);
            fclose(file);
        }
    } else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/produtora/produtora.bin", "ab");
        if (!file) file = fopen("../b_output/produtora/produtora.bin", "ab");
        if (file) {
            fwrite(&nova_produtora, sizeof(Produtora), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

Produtora* buscar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca) {
    NoProdutora *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->dados.cnpj, cnpj_busca) == 0 && atual->dados.status == 1) {
            return &(atual->dados);
        }
        atual = atual->proximo;
    }
    return NULL;
}

NoProdutora* carregar_produtoras(NoProdutora* lista) {
    if (lista != NULL) return lista;
    int tipo = verificar_tipo_saida();
    if (tipo == 1) { 
        FILE *file = fopen("b_output/produtora/produtora.txt", "r");
        if (!file) file = fopen("../b_output/produtora/produtora.txt", "r");
        if (!file) return lista;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            linha[strcspn(linha, "\n")] = 0;
            Produtora p;
            strcpy(p.nome_fantasia, ""); strcpy(p.razao_social, "");
            strcpy(p.inscricao_estadual, ""); strcpy(p.cnpj, "");
            strcpy(p.endereco_completo, ""); strcpy(p.telefone, "");
            strcpy(p.email, ""); strcpy(p.nome_do_responsavel, "");
            strcpy(p.telefone_do_responsavel, ""); strcpy(p.margem_de_lucro_padrao, "");
            p.status = 0;

            char *token = strtok(linha, ",");
            if(token) extrair_valor(p.nome_fantasia, token, 50);
            token = strtok(NULL, ","); if(token) extrair_valor(p.razao_social, token, 100);
            token = strtok(NULL, ","); if(token) extrair_valor(p.inscricao_estadual, token, 9);
            token = strtok(NULL, ","); if(token) extrair_valor(p.cnpj, token, 14);
            token = strtok(NULL, ","); if(token) extrair_valor(p.endereco_completo, token, 256);
            token = strtok(NULL, ","); if(token) extrair_valor(p.telefone, token, 11);
            token = strtok(NULL, ","); if(token) extrair_valor(p.email, token, 50);
            token = strtok(NULL, ","); if(token) extrair_valor(p.nome_do_responsavel, token, 50);
            token = strtok(NULL, ","); if(token) extrair_valor(p.telefone_do_responsavel, token, 11);
            token = strtok(NULL, ","); if(token) extrair_valor(p.margem_de_lucro_padrao, token, 6);
            token = strtok(NULL, ","); 
            if(token) {
                char temp_st[10];
                extrair_valor(temp_st, token, 10);
                p.status = atoi(temp_st);
            }
            if (strlen(p.cnpj) > 0) {
                NoProdutora *novo_no = (NoProdutora*) malloc(sizeof(NoProdutora));
                if (novo_no != NULL) {
                    copiar_dados_produtora(&(novo_no->dados), &p);
                    novo_no->dados.status = p.status; 
                    novo_no->proximo = lista;
                    lista = novo_no;
                }
            }
        }
        fclose(file);
    } else if (tipo == 2) { 
        FILE *file = fopen("b_output/produtora/produtora.bin", "rb");
        if (!file) file = fopen("../b_output/produtora/produtora.bin", "rb");
        if (!file) return lista;
        Produtora p;
        while (fread(&p, sizeof(Produtora), 1, file) == 1) {
            NoProdutora *novo_no = (NoProdutora*) malloc(sizeof(NoProdutora));
            if (novo_no != NULL) {
                copiar_dados_produtora(&(novo_no->dados), &p);
                novo_no->dados.status = p.status;
                novo_no->proximo = lista;
                lista = novo_no;
            }
        }
        fclose(file);
    }
    return lista;
}

void atualizar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca, const char* nome_fantasia, const char* razao_social, const char* inscricao_estadual, const char* endereco_completo, const char* telefone, const char* email, const char* nome_do_responsavel, const char* margem_de_lucro_padrao, const char* telefone_do_responsavel) {
    Produtora *p = buscar_produtora_por_cnpj(lista, cnpj_busca);
    if (p) {
        strncpy(p->nome_fantasia, nome_fantasia, 49);
        strncpy(p->razao_social, razao_social, 99);
        strncpy(p->endereco_completo, endereco_completo, 255);
        strncpy(p->inscricao_estadual, inscricao_estadual, 8);
        strncpy(p->email, email, 49);
        strncpy(p->telefone, telefone, 10);
        strncpy(p->nome_do_responsavel, nome_do_responsavel, 49);
        strncpy(p->telefone_do_responsavel, telefone_do_responsavel, 10);
        strncpy(p->margem_de_lucro_padrao, margem_de_lucro_padrao, 5);
    }
}

int deletar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca) {
    Produtora *p = buscar_produtora_por_cnpj(lista, cnpj_busca);
    if (p) {
        p->status = 0; 
        return 1;
    }
    return 0;
}

void desalocar_lista_produtoras(NoProdutora* lista) {
    NoProdutora *atual = lista;
    while (atual != NULL) {
        NoProdutora *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}