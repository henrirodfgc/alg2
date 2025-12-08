#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipe.h"
#include "../../controller/saida.h"
#include "../../view/cadastro/equipe_view.h" 

void copiar_dados_equipe(MembroEquipe *destino, const MembroEquipe *origem) {
    if (!origem || !destino) return; 
    
    destino->codigo = origem->codigo;
    destino->valor_diaria_hora = origem->valor_diaria_hora; 
    destino->status = origem->status; 
    
    strncpy(destino->nome, origem->nome, sizeof(destino->nome) - 1);
    destino->nome[sizeof(destino->nome) - 1] = '\0';
    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';
    strncpy(destino->funcao, origem->funcao, sizeof(destino->funcao) - 1);
    destino->funcao[sizeof(destino->funcao) - 1] = '\0';
}

MembroEquipe *buscar_membro_qualquer_status(NoEquipe *lista, int codigo_busca) {
    NoEquipe *atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca) {
            return &(atual->dados); 
        }
        atual = atual->proximo;
    }
    return NULL; 
}

NoEquipe* adicionar_membro_na_lista(NoEquipe* lista, MembroEquipe novo_membro) {
    NoEquipe *novo_no = (NoEquipe*) malloc(sizeof(NoEquipe)); 
    if (novo_no == NULL) return lista; 

    copiar_dados_equipe(&(novo_no->dados), &novo_membro);
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/membro/membros.txt", "a");
        if (!file) file = fopen("../b_output/membro/membros.txt", "a");

        if (file) {
            novo_membro.status = 1;
            fprintf(file,
                "id:%d,nome:%s,cpf:%s,funcao:%s,valor_diaria_hora:%.2f,status:%d\n",
                novo_membro.codigo, novo_membro.nome, novo_membro.cpf,
                novo_membro.funcao, novo_membro.valor_diaria_hora, novo_membro.status);
            fclose(file);
        }
    }
    else if (verificar_tipo_saida() == 2) {
        FILE *file = fopen("b_output/membro/membros.bin", "ab");
        if (!file) file = fopen("../b_output/membro/membros.bin", "ab");

        if (file) {
            novo_membro.status = 1;
            fwrite(&novo_membro,sizeof(MembroEquipe),1,file);
            fclose(file);
        }
    }
    return novo_no; 
}

MembroEquipe* buscar_membro_por_codigo(NoEquipe* lista, int codigo_busca) {
    NoEquipe *atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca && atual->dados.status == 1) { 
            return &(atual->dados); 
        }
        atual = atual->proximo;
    }
    return NULL; 
}

void atualizar_membro_por_codigo(NoEquipe* lista, int codigo_busca, const char* nome, const char* cpf, const char* funcao, float valor_diaria_hora) {
    MembroEquipe *membro_existente = buscar_membro_por_codigo(lista, codigo_busca);
    
    if (membro_existente) {
        membro_existente->valor_diaria_hora = valor_diaria_hora;
        strncpy(membro_existente->nome, nome, sizeof(membro_existente->nome) - 1);
        membro_existente->nome[sizeof(membro_existente->nome) - 1] = '\0';
        strncpy(membro_existente->cpf, cpf, sizeof(membro_existente->cpf) - 1);
        membro_existente->cpf[sizeof(membro_existente->cpf) - 1] = '\0';
        strncpy(membro_existente->funcao, funcao, sizeof(membro_existente->funcao) - 1);
        membro_existente->funcao[sizeof(membro_existente->funcao) - 1] = '\0';
    }
}

int deletar_membro_por_codigo_logico(NoEquipe* lista, int codigo_busca) {
    if (verificar_tipo_saida() == 1) {
        FILE *file = fopen("b_output/membro/membros.txt", "r+");
        if (!file) file = fopen("../b_output/membro/membros.txt", "r+");
        if (file == NULL) return 0;

        FILE *temp = fopen("b_output/membro/temp.txt", "w+");
        if (!temp) temp = fopen("../b_output/membro/temp.txt", "w+");
        if (temp == NULL) { fclose(file); return 0; }

        MembroEquipe c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file)) {
            sscanf(linha,
                   "id:%d,nome:%49[^,],cpf:%11[^,],funcao:%49[^,],valor_diaria_hora:%f,status:%d",
                   &c.codigo, c.nome, c.cpf, c.funcao, &c.valor_diaria_hora, &c.status);
                   
            if (c.codigo == codigo_busca) {
                c.status = 0; 
                encontrado = 1;
            }
            fprintf(temp,
                     "id:%d,nome:%s,cpf:%s,funcao:%s,valor_diaria_hora:%.2f,status:%d\n",
                     c.codigo, c.nome, c.cpf, c.funcao, c.valor_diaria_hora, c.status);
        }
        fclose(file);
        fclose(temp);
       
        remove("b_output/membro/membros.txt");
        remove("../b_output/membro/membros.txt");
        rename("b_output/membro/temp.txt", "b_output/membro/membros.txt");
        rename("../b_output/membro/temp.txt", "../b_output/membro/membros.txt");

        return encontrado;
    }
    else if (verificar_tipo_saida() == 3) {
        MembroEquipe *membro_existente = buscar_membro_por_codigo(lista, codigo_busca);
        if (membro_existente && membro_existente->status == 1) {
            membro_existente->status = 0; 
            return 1; 
        }
        return 0;
    }
    return 0;
}

void restaurar_membro_por_codigo(NoEquipe* lista, int codigo_busca) {
    if (verificar_tipo_saida() != 3) return;
    MembroEquipe *membro_existente = buscar_membro_qualquer_status(lista, codigo_busca); 
    if (membro_existente && membro_existente->status == 0) {
        membro_existente->status = 1; 
    }
}

void desalocar_lista_equipe(NoEquipe* lista) {
    NoEquipe *atual = lista;
    while (atual != NULL) {
        NoEquipe *prox = atual->proximo; 
        free(atual);
        atual = prox;
    }
}

void exibir_todos_membros(NoEquipe* lista) {
    NoEquipe *atual = lista;
    int contador = 0;
    printf("\n==== lista de membros da equipe (ativos) ====\n");
    while (atual != NULL) {
        if (atual->dados.status == 1) { 
            exibir_membro(&(atual->dados)); 
            contador++;
        }
        atual = atual->proximo;
    }
    if (contador == 0) printf("nenhum membro ativo cadastrado!\n");
    printf("======================================\n");
}

void exibir_membros_inativos(NoEquipe* lista) {
    NoEquipe *atual = lista;
    int contador = 0;
    printf("\n==== lista de membros inativos ====\n");
    while (atual != NULL) {
        if (atual->dados.status == 0) { 
            exibir_membro(&(atual->dados)); 
            contador++;
        }
        atual = atual->proximo;
    }
    if (contador == 0) printf("nenhum membro inativo encontrado!\n");
    printf("======================================\n");
}

NoEquipe* carregar_equipe(NoEquipe* lista) {
    if (lista != NULL) return lista;
    int tipo = verificar_tipo_saida();

    if (tipo == 1) { 
        FILE *file = fopen("b_output/membro/membros.txt", "r");
        if (!file) file = fopen("../b_output/membro/membros.txt", "r");
        if (file == NULL) return lista;

        MembroEquipe m;
        char linha[2048];
        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha,
                "id:%d,nome:%49[^,],cpf:%11[^,],funcao:%49[^,],valor_diaria_hora:%f,status:%d",
                &m.codigo, m.nome, m.cpf, m.funcao, &m.valor_diaria_hora, &m.status) == 6) {
                
                NoEquipe *novo_no = (NoEquipe*) malloc(sizeof(NoEquipe));
                if (novo_no != NULL) {
                    copiar_dados_equipe(&(novo_no->dados), &m);
                    novo_no->dados.status = m.status;
                    novo_no->proximo = lista;
                    lista = novo_no;
                }
            }
        }
        fclose(file);
    } 
    else if (tipo == 2) { 
        FILE *file = fopen("b_output/membro/membros.bin", "rb");
        if (!file) file = fopen("../b_output/membro/membros.bin", "rb");
        if (file == NULL) return lista;

        MembroEquipe m;
        while (fread(&m, sizeof(MembroEquipe), 1, file) == 1) {
            NoEquipe *novo_no = (NoEquipe*) malloc(sizeof(NoEquipe));
            if (novo_no != NULL) {
                copiar_dados_equipe(&(novo_no->dados), &m);
                novo_no->dados.status = m.status;
                novo_no->proximo = lista;
                lista = novo_no;
            }
        }
        fclose(file);
    }
    return lista;
}