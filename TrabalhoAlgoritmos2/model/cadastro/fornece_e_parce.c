#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornece_e_parce.h"
#include "../../view/cadastro/fornece_e_parce_view.h"
#include "../../controller/saida.h"

void copiar_dados_fornece_e_parce(Fornecedores_e_parceiros *destino, const Fornecedores_e_parceiros *origem){
    if (!origem || !destino) return;
    destino->id = origem->id;
    destino->tipo = origem->tipo; 
    destino->servico = origem->servico;
    strncpy(destino->nome_fantasia, origem->nome_fantasia, sizeof(destino->nome_fantasia) - 1);
    destino->nome_fantasia[sizeof(destino->nome_fantasia) - 1] = '\0';
    strncpy(destino->nome_razao, origem->nome_razao, sizeof(destino->nome_razao) - 1);
    destino->nome_razao[sizeof(destino->nome_razao) - 1] = '\0';
    strncpy(destino->endereco, origem->endereco, sizeof(destino->endereco) - 1);
    destino->endereco[sizeof(destino->endereco) - 1] = '\0';
    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';
    strncpy(destino->cnpj, origem->cnpj, sizeof(destino->cnpj) - 1);
    destino->cnpj[sizeof(destino->cnpj) - 1] = '\0';
    strncpy(destino->telefone, origem->telefone, sizeof(destino->telefone) - 1);
    destino->telefone[sizeof(destino->telefone) - 1] = '\0';
    destino->status = origem->status;
}

NoFornecedores_e_parceiros* adicionar_fornecedor_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_fornecedor){
    NoFornecedores_e_parceiros *novo_no = (NoFornecedores_e_parceiros*) malloc(sizeof(NoFornecedores_e_parceiros));
    if(novo_no == NULL) return lista;

    novo_fornecedor.status = 1;
    copiar_dados_fornece_e_parce(&(novo_no->dados), &novo_fornecedor);
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/forne_parce/fornecedor.txt", "a");
        if (!file) file = fopen("../b_output/forne_parce/fornecedor.txt", "a");
        if (file != NULL) {
            fprintf(file, "id:%d,nome_fantasia:%s,nome_razao:%s,endereco:%s,tipo:%d,cpf:%s,cnpj:%s,telefone:%s,servico:%d,status:%d\n",
                novo_fornecedor.id, novo_fornecedor.nome_fantasia, novo_fornecedor.nome_razao,
                novo_fornecedor.endereco, novo_fornecedor.tipo, novo_fornecedor.cpf,
                novo_fornecedor.cnpj, novo_fornecedor.telefone, novo_fornecedor.servico, novo_fornecedor.status);
            fclose(file);
        }
    } else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/forne_parce/fornecedores.bin", "ab");
        if (!file) file = fopen("../b_output/forne_parce/fornecedores.bin", "ab");
        if (file != NULL) {
            fwrite(&novo_fornecedor, sizeof(Fornecedores_e_parceiros), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

NoFornecedores_e_parceiros* adicionar_parceiros_na_lista(NoFornecedores_e_parceiros* lista, Fornecedores_e_parceiros novo_parceiro){
    NoFornecedores_e_parceiros *novo_no = (NoFornecedores_e_parceiros*) malloc(sizeof(NoFornecedores_e_parceiros));
    if(novo_no == NULL) return lista;
    novo_parceiro.status = 1;
    copiar_dados_fornece_e_parce(&(novo_no->dados), &novo_parceiro);
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/forne_parce/parceiro.txt", "a");
        if (!file) file = fopen("../b_output/forne_parce/parceiro.txt", "a");
        if (file != NULL) {
            fprintf(file, "id:%d,nome_fantasia:%s,nome_razao:%s,endereco:%s,tipo:%d,cpf:%s,cnpj:%s,telefone:%s,servico:%d,status:%d\n",
                novo_parceiro.id, novo_parceiro.nome_fantasia, novo_parceiro.nome_razao,
                novo_parceiro.endereco, novo_parceiro.tipo, novo_parceiro.cpf,
                novo_parceiro.cnpj, novo_parceiro.telefone, novo_parceiro.servico, novo_parceiro.status);
            fclose(file);
        }
    } else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/forne_parce/parceiros.bin", "ab");
        if (!file) file = fopen("../b_output/forne_parce/parceiros.bin", "ab");
        if (file != NULL) {
            fwrite(&novo_parceiro, sizeof(Fornecedores_e_parceiros), 1, file);
            fclose(file);
        }
    }
    return novo_no;
}

Fornecedores_e_parceiros* buscar_fornece_e_parce_por_id(NoFornecedores_e_parceiros* lista, int id_busca){
    NoFornecedores_e_parceiros *atual = lista;
    while(atual != NULL){
        if(atual->dados.id == id_busca && atual->dados.status == 1){
            return &(atual->dados);
        }
        atual = atual->proximo;
    }
    return NULL;
}

NoFornecedores_e_parceiros* deletar_fornece_e_parce_por_id(NoFornecedores_e_parceiros *lista, int id_busca){
    if (verificar_tipo_saida() == 3) {
        Fornecedores_e_parceiros *encontrado = buscar_fornece_e_parce_por_id(lista, id_busca);
        if(encontrado){
            encontrado->status = 0; 
        }
        return lista;
    }
    return lista;
}

void atualizar_fornecedor_por_id(NoFornecedores_e_parceiros* lista, int id_busca, char *nome_fantasia, char *razao_social, char *endereco, char *cnpj, char *telefone, TipoServico servico){
    Fornecedores_e_parceiros *f = buscar_fornece_e_parce_por_id(lista, id_busca);
    if(f){
        strncpy(f->nome_fantasia, nome_fantasia, 49);
        strncpy(f->nome_razao, razao_social, 99);
        strncpy(f->endereco, endereco, 255);
        strncpy(f->cnpj, cnpj, 14);
        strncpy(f->telefone, telefone, 19);
        f->servico = servico;
    }
}

void atualizar_parceiro_por_id(NoFornecedores_e_parceiros* lista, int id_busca, char *nome_fantasia, char *razao_social, char *endereco, char *cpf, char *telefone, TipoServico servico){
    Fornecedores_e_parceiros *p = buscar_fornece_e_parce_por_id(lista, id_busca);
    if(p){
        strncpy(p->nome_fantasia, nome_fantasia, 49);
        strncpy(p->nome_razao, razao_social, 99);
        strncpy(p->endereco, endereco, 255);
        strncpy(p->cpf, cpf, 11);
        strncpy(p->telefone, telefone, 19);
        p->servico = servico;
    }
}

NoFornecedores_e_parceiros* carregar_fornecedores_e_parceiros(NoFornecedores_e_parceiros* lista) {
    if (lista != NULL) return lista;

    int tipo = verificar_tipo_saida();

    if (tipo == 1) { 
        FILE *fileF = fopen("b_output/forne_parce/fornecedor.txt", "r");
        if (!fileF) fileF = fopen("../b_output/forne_parce/fornecedor.txt", "r");
        
        if (fileF != NULL) {
            Fornecedores_e_parceiros f;
            char linha[2048];
            while (fgets(linha, sizeof(linha), fileF)) {
                if (sscanf(linha, 
                    "id:%d,nome_fantasia:%49[^,],nome_razao:%99[^,],endereco:%255[^,],tipo:%d,cpf:%11[^,],cnpj:%14[^,],telefone:%19[^,],servico:%d,status:%d",
                    &f.id, f.nome_fantasia, f.nome_razao, f.endereco, 
                    (int*)&f.tipo, f.cpf, f.cnpj, f.telefone, (int*)&f.servico, &f.status) == 10) {
                    
                    NoFornecedores_e_parceiros *novo_no = (NoFornecedores_e_parceiros*) malloc(sizeof(NoFornecedores_e_parceiros));
                    if (novo_no != NULL) {
                        copiar_dados_fornece_e_parce(&(novo_no->dados), &f);
                        novo_no->dados.status = f.status;
                        novo_no->proximo = lista;
                        lista = novo_no;
                    }
                }
            }
            fclose(fileF);
        }

        FILE *fileP = fopen("b_output/forne_parce/parceiro.txt", "r");
        if (!fileP) fileP = fopen("../b_output/forne_parce/parceiro.txt", "r");

        if (fileP != NULL) {
            Fornecedores_e_parceiros p;
            char linha[2048];
            while (fgets(linha, sizeof(linha), fileP)) {
                if (sscanf(linha, 
                    "id:%d,nome_fantasia:%49[^,],nome_razao:%99[^,],endereco:%255[^,],tipo:%d,cpf:%11[^,],cnpj:%14[^,],telefone:%19[^,],servico:%d,status:%d",
                    &p.id, p.nome_fantasia, p.nome_razao, p.endereco, 
                    (int*)&p.tipo, p.cpf, p.cnpj, p.telefone, (int*)&p.servico, &p.status) == 10) {
                    
                    NoFornecedores_e_parceiros *novo_no = (NoFornecedores_e_parceiros*) malloc(sizeof(NoFornecedores_e_parceiros));
                    if (novo_no != NULL) {
                        copiar_dados_fornece_e_parce(&(novo_no->dados), &p);
                        novo_no->dados.status = p.status;
                        novo_no->proximo = lista;
                        lista = novo_no;
                    }
                }
            }
            fclose(fileP);
        }
    } 
    return lista;
}

void desalocar_lista_fornece_e_parce(NoFornecedores_e_parceiros* lista){
    NoFornecedores_e_parceiros *atual = lista;
    while(atual != NULL){
        NoFornecedores_e_parceiros *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}