#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursos.h"
#include "../../controller/saida.h" 

void copiar_dados_recurso(Equipamento *destino, const Equipamento *origem) {
    if (!origem || !destino) return; 
    destino->codigo = origem->codigo;
    destino->quantidade_estoque = origem->quantidade_estoque;
    destino->preco_custo = origem->preco_custo;
    destino->valor_locacao = origem->valor_locacao;
    destino->status = origem->status; 
    strncpy(destino->descricao, origem->descricao, sizeof(destino->descricao) - 1);
    destino->descricao[sizeof(destino->descricao) - 1] = '\0'; 
    strncpy(destino->categoria, origem->categoria, sizeof(destino->categoria) - 1);
    destino->categoria[sizeof(destino->categoria) - 1] = '\0'; 
}

NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso) {
    NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso)); 
    if (novo_no == NULL) return lista; 

    copiar_dados_recurso(&(novo_no->dados), &novo_recurso);
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/recursos/recursos.txt", "a"); 
        if (!file) file = fopen("../b_output/recursos/recursos.txt", "a"); 
        if (file) {
            fprintf(file, "codigo:%d,descricao:%s,categoria:%s,quantidade_estoque:%d,custo:%.2f,locacao:%.2f,status:%d\n",
                novo_recurso.codigo, novo_recurso.descricao, novo_recurso.categoria,
                novo_recurso.quantidade_estoque, novo_recurso.preco_custo,
                novo_recurso.valor_locacao, novo_recurso.status); 
            fclose(file);
        }
    } else if (verificar_tipo_saida() == 2) {
         FILE *file = fopen("b_output/recursos/recursos.bin", "ab");
         if (!file) file = fopen("../b_output/recursos/recursos.bin", "ab");
         if (file) {
            fwrite(&novo_recurso,sizeof(Equipamento),1,file);
            fclose(file);
        }
    }
    return novo_no; 
}

Equipamento* buscar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    NoRecurso *atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca && atual->dados.status == 1) return &(atual->dados); 
        atual = atual->proximo;
    }
    return NULL; 
}

void atualizar_recurso_por_codigo(NoRecurso* lista, int codigo_busca, const char* descricao, const char* categoria, int quantidade_estoque, float preco_custo, float valor_locacao) {
    Equipamento *recurso_existente = buscar_recurso_por_codigo(lista, codigo_busca);
    if (recurso_existente) {
        recurso_existente->quantidade_estoque = quantidade_estoque;
        recurso_existente->preco_custo = preco_custo;
        recurso_existente->valor_locacao = valor_locacao; 
        strncpy(recurso_existente->descricao, descricao, sizeof(recurso_existente->descricao) - 1);
        recurso_existente->descricao[sizeof(recurso_existente->descricao) - 1] = '\0';
        strncpy(recurso_existente->categoria, categoria, sizeof(recurso_existente->categoria) - 1);
        recurso_existente->categoria[sizeof(recurso_existente->categoria) - 1] = '\0';
    }
}

int deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/recursos/recursos.txt", "r+");
        if (!file) file = fopen("../b_output/recursos/recursos.txt", "r+");
        if (file == NULL) return 0;

        FILE *temp = fopen("b_output/recursos/temp.txt", "w+");
        if (!temp) temp = fopen("../b_output/recursos/temp.txt", "w+");
        if (temp == NULL) { fclose(file); return 0; }

        Equipamento c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file)) {
            if(sscanf(linha, "codigo:%d,descricao:%99[^,],categoria:%49[^,],quantidade_estoque:%d,custo:%f,locacao:%f,status:%d",
                   &c.codigo, c.descricao, c.categoria, &c.quantidade_estoque, &c.preco_custo, &c.valor_locacao, &c.status) != 7) {
                       fprintf(temp, "%s", linha); continue;
                   }
            if (c.codigo == codigo_busca) {
                c.status = 0; 
                encontrado = 1;
            }
            fprintf(temp, "codigo:%d,descricao:%s,categoria:%s,quantidade_estoque:%d,custo:%.2f,locacao:%.2f,status:%d\n",
                   c.codigo, c.descricao, c.categoria, c.quantidade_estoque, c.preco_custo, c.valor_locacao, c.status);
        }
        fclose(file);
        fclose(temp);
       
        remove("b_output/recursos/recursos.txt");
        remove("../b_output/recursos/recursos.txt");
        rename("b_output/recursos/temp.txt", "b_output/recursos/recursos.txt");
        rename("../b_output/recursos/temp.txt", "../b_output/recursos/recursos.txt");
        return encontrado;
    }
    else if (verificar_tipo_saida() == 3) {
        Equipamento *equipamento_existente = buscar_recurso_por_codigo(lista, codigo_busca);
        if (equipamento_existente && equipamento_existente->status == 1) {
            equipamento_existente->status = 0; 
            return 1; 
        }
        return 0;
    }
    return 0;
}

void desalocar_lista_recursos(NoRecurso* lista) {
    if (verificar_tipo_saida() != 3) return; 
    NoRecurso *atual = lista;
    while (atual != NULL) {
        NoRecurso *prox = atual->proximo; 
        free(atual);
        atual = prox;
    }
}

NoRecurso* carregar_recursos(NoRecurso* lista) {
    if (lista != NULL) return lista; 
    int tipo = verificar_tipo_saida();
    if (tipo == 1) { 
        FILE *file = fopen("b_output/recursos/recursos.txt", "r");
        if (!file) file = fopen("../b_output/recursos/recursos.txt", "r");
        if (file == NULL) return lista; 
        Equipamento e;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha, "codigo:%d,descricao:%99[^,],categoria:%49[^,],quantidade_estoque:%d,custo:%f,locacao:%f,status:%d",
                &e.codigo, e.descricao, e.categoria, &e.quantidade_estoque, &e.preco_custo, &e.valor_locacao, &e.status) == 7) {
                NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso));
                if (novo_no != NULL) {
                    copiar_dados_recurso(&(novo_no->dados), &e);
                    novo_no->proximo = lista;
                    lista = novo_no;
                }
            }
        }
        fclose(file);
    } else if (tipo == 2) { 
        FILE *file = fopen("b_output/recursos/recursos.bin", "rb");
        if (!file) file = fopen("../b_output/recursos/recursos.bin", "rb");
        if (file == NULL) return lista;
        Equipamento e;
        while (fread(&e, sizeof(Equipamento), 1, file) == 1) {
            NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso));
            if (novo_no != NULL) {
                copiar_dados_recurso(&(novo_no->dados), &e);
                novo_no->proximo = lista;
                lista = novo_no;
            }
        }
        fclose(file);
    }
    return lista; 
}
void reescrever_arquivo_recursos(NoRecurso* lista) {
    int tipo = verificar_tipo_saida();
    if (tipo == 3) return;

    if (tipo == 1) { 
        FILE *file = fopen("b_output/recursos/recursos.txt", "w"); 
        if (!file) file = fopen("../b_output/recursos/recursos.txt", "w"); 
        if (!file) return;

        NoRecurso *atual = lista;
        while (atual != NULL) {
            fprintf(file, "codigo:%d,descricao:%s,categoria:%s,quantidade_estoque:%d,custo:%.2f,locacao:%.2f,status:%d\n",
                atual->dados.codigo, atual->dados.descricao, atual->dados.categoria,
                atual->dados.quantidade_estoque, atual->dados.preco_custo,
                atual->dados.valor_locacao, atual->dados.status); 
            atual = atual->proximo;
        }
        fclose(file);
    } else if (tipo == 2) {
         FILE *file = fopen("b_output/recursos/recursos.bin", "wb");
         if (!file) file = fopen("../b_output/recursos/recursos.bin", "wb");
         if (!file) return;
         
         NoRecurso *atual = lista;
         while (atual != NULL) {
            fwrite(&(atual->dados), sizeof(Equipamento), 1, file);
            atual = atual->proximo;
         }
         fclose(file);
    }
}