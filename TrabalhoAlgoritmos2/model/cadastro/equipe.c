#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipe.h"
#include "../../controller/saida.h"
#include "../../view/cadastro/equipe_view.h" //pra exibir mensagem de erro

//--- funcoes auxiliares ---
//copia tudo de um membro pro outro
void copiar_dados_equipe(MembroEquipe *destino, const MembroEquipe *origem) {
    if (!origem || !destino) return; //se for null sai fora pra n dar bo
    
    destino->codigo = origem->codigo;
    destino->valor_diaria_hora = origem->valor_diaria_hora; //copia o valor da diaria/hora
    destino->status = origem->status; //copia o status tbm
    
    //cópia segura de todas as strings
    strncpy(destino->nome, origem->nome, sizeof(destino->nome) - 1);
    destino->nome[sizeof(destino->nome) - 1] = '\0';
    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';
    strncpy(destino->funcao, origem->funcao, sizeof(destino->funcao) - 1);
    destino->funcao[sizeof(destino->funcao) - 1] = '\0';
}

//procura um membro pelo código independente do status (auxiliar pra inativar/restaurar)
MembroEquipe *buscar_membro_qualquer_status(NoEquipe *lista, int codigo_busca) {
    NoEquipe *atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca) {
            return &(atual->dados); //achou, nao importa o status
        }
        atual = atual->proximo;
    }
    return NULL; //nao achou
}

//--- funcoes de manipulacao de lista ligada (crud) ---
//cria um novo no e poe ele no comeco da lista (create)
NoEquipe* adicionar_membro_na_lista(NoEquipe* lista, MembroEquipe novo_membro) {
    
    
    NoEquipe *novo_no = (NoEquipe*) malloc(sizeof(NoEquipe)); //pede memoria pra esse no novo
    
    if (novo_no == NULL) {
        return lista; //se n der pra alocar a gente so retorna a lista antiga
    }

    
    copiar_dados_equipe(&(novo_no->dados), &novo_membro);

    novo_no->proximo = lista;

     if (verificar_tipo_saida() == 1)
    {
        FILE *file = fopen("../b_output/membro/membros.txt", "a");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo de membros!\n");
            // free(novo_no); //
            return lista;
        }

        novo_membro.status == 1;

        fprintf(file,
            "id:%d,nome:%s,cpf:%s,funcao:%s,valor_diaria_hora:%.2f,status:%d\n",
            novo_membro.codigo,
            novo_membro.nome,
            novo_membro.cpf,
            novo_membro.funcao,
            novo_membro.valor_diaria_hora,
            novo_membro.status);
        fclose(file);
        printf("Membro salvo com sucesso!!\n");
    }

    else if (verificar_tipo_saida() == 2)
    {
        FILE *file = fopen("../b_output/membro/membros.bin", "ab");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo binário de membros!\n");
            // free(novo_no); // Descomente se 'novo_no' foi alocado antes
            return lista;
        }

        novo_membro.status = 1;

        if (fwrite(&novo_membro,sizeof(MembroEquipe),1,file) != 1)
        {
            printf("Erro ao escrever strcut em binario\n");
        } 
        else
        {
            printf("Strucut de fornecedor salva com sucesso em membros.bin!\n");
            fclose(file);
        }

        
    }

    return novo_no; //devolve a nova cabeca da lista
}

//procura o membro pelo código (read)
//agora so retorna se o status for 1 (ativo)
MembroEquipe* buscar_membro_por_codigo(NoEquipe* lista, int codigo_busca) {
    NoEquipe *atual = lista;
    //percorre a lista ate achar o código ou a lista acabar
    while (atual != NULL) {
        //achou e ta ativo? devolve os dados
        if (atual->dados.codigo == codigo_busca && atual->dados.status == 1) { 
            return &(atual->dados); 
        }
        atual = atual->proximo;
    }
    return NULL; //não achou, termina
}

//atualiza os dados de quem já existe na lista (update)
void atualizar_membro_por_codigo(NoEquipe* lista, int codigo_busca, const char* nome, const char* cpf, const char* funcao, float valor_diaria_hora) {
    MembroEquipe *membro_existente = buscar_membro_por_codigo(lista, codigo_busca);
    
    if (membro_existente) {
        //atualiza o float (valor)
        membro_existente->valor_diaria_hora = valor_diaria_hora;
        
        //atualiza as strings com cópia segura
        strncpy(membro_existente->nome, nome, sizeof(membro_existente->nome) - 1);
        membro_existente->nome[sizeof(membro_existente->nome) - 1] = '\0';
        strncpy(membro_existente->cpf, cpf, sizeof(membro_existente->cpf) - 1);
        membro_existente->cpf[sizeof(membro_existente->cpf) - 1] = '\0';
        strncpy(membro_existente->funcao, funcao, sizeof(membro_existente->funcao) - 1);
        membro_existente->funcao[sizeof(membro_existente->funcao) - 1] = '\0';
        
        //avisa se nao for modo memoria
        if (verificar_tipo_saida() != 3) {
            exibir_mensagem_equipe("");
        }
    }
}

//deleta o nó da lista vira INATIVAR (soft delete)
//agora so muda o status pra 0 (soft delete)
int deletar_membro_por_codigo_logico(NoEquipe* lista, int codigo_busca) {
    //se nao for modo memoria a responsa nao eh sua
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_equipe("");
        return 0;
    }
    
    //busca o membro pra mudar o status (qualquer status)
    MembroEquipe *membro_existente = buscar_membro_qualquer_status(lista, codigo_busca);
    
    //se a busca encontrar o cliente, muda o status
    if (membro_existente) {
        membro_existente->status = 0; //seta pra inativo/deletado
        return 1; //sucesso!
    }
    return 0; //falha
}

//novo: muda o status de 0 pra 1 (restauração)
void restaurar_membro_por_codigo(NoEquipe* lista, int codigo_busca) {
    //so faz se estiver em modo memoria
    if (verificar_tipo_saida() != 3) return;
    
    //busca o no independente do status
    MembroEquipe *membro_existente = buscar_membro_qualquer_status(lista, codigo_busca); 

    //se encontrou e ele estava inativo, reativa
    if (membro_existente && membro_existente->status == 0) {
        membro_existente->status = 1; //seta pra ativo
    }
}

//função essencial: libera a memória de geral
void desalocar_lista_equipe(NoEquipe* lista) {
    //so faz se estiver em modo memoria
    if (verificar_tipo_saida() != 3) return;
    
    NoEquipe *atual = lista;
    NoEquipe *proximo_no;
    //roda a lista toda dando free em cada nó
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

//função pra mostrar todos (so os ativos)
void exibir_todos_membros(NoEquipe* lista) {
    //so exibe se estiver em modo memoria
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_equipe("");
        return;
    }
    
    NoEquipe *atual = lista;
    int contador = 0;

    printf("\n==== lista de membros da equipe (ativos) ====\n");
    while (atual != NULL) {
        if (atual->dados.status == 1) { //filtro por status ativo
            exibir_membro(&(atual->dados)); 
            contador++;
        }
        atual = atual->proximo;
    }

    if (contador == 0) {
        exibir_mensagem_equipe("nenhum membro ativo cadastrado!");
    }
    printf("======================================\n");
}

//função pra mostrar só os inativos
void exibir_membros_inativos(NoEquipe* lista) {
    //so exibe se estiver em modo memoria
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_equipe("");
        return;
    }
    
    NoEquipe *atual = lista;
    int contador = 0;

    printf("\n==== lista de membros inativos ====\n");
    while (atual != NULL) {
        if (atual->dados.status == 0) { //filtro por status inativo
            exibir_membro(&(atual->dados)); 
            contador++;
        }
        atual = atual->proximo;
    }

    if (contador == 0) {
        exibir_mensagem_equipe("nenhum membro inativo encontrado!");
    }
    printf("======================================\n");
}