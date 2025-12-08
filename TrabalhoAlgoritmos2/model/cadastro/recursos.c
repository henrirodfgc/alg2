#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursos.h"
#include "../../controller/saida.h" 
#include "../../view/cadastro/recursos_view.h" 

//copia tudo de um recurso pro outro 
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

//crud
//cria um novo no e poe ele no comeco da lista (c)
NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso) {
   
    NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso)); 
    
    if (novo_no == NULL) {
        exibir_mensagem_recursos("erro:falha ao alocar no de recurso na memoria.");
        return lista; 
    }

    copiar_dados_recurso(&(novo_no->dados), &novo_recurso);
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1)
    {
        FILE *file = fopen("b_output/recursos/recursos.txt", "a"); 
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo de recursos!\n");
            return lista;
        }

        fprintf(file,
            "codigo:%d,descricao:%s,categoria:%s,quantidade_estoque:%d,custo:%.2f,locacao:%.2f,status:%d\n",
            novo_recurso.codigo,
            novo_recurso.descricao,
            novo_recurso.categoria,
            novo_recurso.quantidade_estoque,
            novo_recurso.preco_custo,
            novo_recurso.valor_locacao,
            novo_recurso.status); 
        fclose(file);
        printf("recursos salvos com sucesso!!\n");
    }
    else if (verificar_tipo_saida() == 2)
    {
         FILE *file = fopen("b_output/recursos/recursos.bin", "ab");
        if (file == NULL) {
            printf("erro ao abrir o arquivo binario de recursos!\n");
            return lista;
        }

        if (fwrite(&novo_recurso,sizeof(Equipamento),1,file) != 1)
        {
            printf("erro ao escrever strcut em binario\n");
        } 
        else
        {
            printf("strucut de recursos salva com sucesso em recursos.bin!\n");
            fclose(file);
        }
    }
    
    return novo_no; 
}

//procura o recurso pelo codigo (r)
Equipamento* buscar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    NoRecurso *atual = lista;
    while (atual != NULL) {
        if (atual->dados.codigo == codigo_busca && atual->dados.status == 1) {
            return &(atual->dados); 
        }
        atual = atual->proximo;
    }
    return NULL; 
}

//atualiza os dados de quem ja existe na lista (u)
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
        
        if (verificar_tipo_saida() != 3) {
            exibir_mensagem_recursos("recurso atualizado em memoria");
        }
    }
}


//deleta o no da lista (d) 
int deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    if (verificar_tipo_saida() == 1) 
    {
        FILE *file = fopen("b_output/recursos/recursos.txt", "r+");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo original!\n");
            return 0;
        }

        FILE *temp = fopen("b_output/recursos/temp.txt", "w+");
        if (temp == NULL)
        {
            printf("erro ao criar arquivo temporario!\n");
            fclose(file);
            return 0;
        }

        Equipamento c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file))
        {
            sscanf(linha,
                   "codigo:%d,descricao:%99[^,],categoria:%49[^,],quantidade_estoque:%d,custo:%f,locacao:%f,status:%d",
                   &c.codigo,
                   c.descricao,
                   c.categoria,
                   &c.quantidade_estoque,
                   &c.preco_custo,
                   &c.valor_locacao,
                   &c.status);

            if (c.codigo == codigo_busca)
            {
                c.status = 0; 
                encontrado = 1;
            }
            
            //fprintf pode usar %.2f
            fprintf(temp,
                    "codigo:%d,descricao:%s,categoria:%s,quantidade_estoque:%d,custo:%.2f,locacao:%.2f,status:%d\n",
                   c.codigo,
                   c.descricao,
                   c.categoria,
                   c.quantidade_estoque,
                   c.preco_custo,
                   c.valor_locacao,
                   c.status);
        }

        fclose(file);
        fclose(temp);
       
        if (remove("b_output/recursos/recursos.txt") != 0)
        {
            perror("erro ao remover o arquivo original");
            return 0;
        }

        if (rename("b_output/recursos/temp.txt", "b_output/recursos/recursos.txt") != 0)
        {
            perror("erro ao renomear o arquivo temporario");
            return 0;
        }

        if (encontrado)
        {
            printf("recurso com id %d marcado como inativo (status = 0).\n", codigo_busca);
            return 1;
        }
        else
        {
            printf("recurso com id %d nao encontrado.\n", codigo_busca);
            return 0;
        }
    }
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem_recursos("erro: delecao em binario nao implementada.");
        return 0; 
    }
    else if (verificar_tipo_saida() == 3)
    {
        Equipamento *equipamento_existente = buscar_recurso_por_codigo(lista, codigo_busca);
        
        if (equipamento_existente && equipamento_existente->status == 1)
        {
            equipamento_existente->status = 0; 
            return 1; 
        }
        return 0;
    }
    return 0;
}

void desalocar_lista_recursos(NoRecurso* lista) {
    if (verificar_tipo_saida() != 3) {
        return; 
    }
    
    NoRecurso *atual = lista;
    NoRecurso *proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

void exibir_todos_recursos(NoRecurso* lista) {
    
    NoRecurso *atual = lista;
    int contador = 0; 

    exibir_cabecalho_lista_recursos(); 
    
    while (atual != NULL) {
        if (atual->dados.status == 1) { 
            exibir_recurso(&(atual->dados)); 
            contador++;
        }
        atual = atual->proximo;
    }

    if (contador == 0) {
        exibir_mensagem_recursos("nenhum recurso/equipamento cadastrado!");
    }
    exibir_rodape_lista_recursos(); 
}

NoRecurso* carregar_recursos(NoRecurso* lista) {
    if (lista != NULL) return lista; 

    int tipo = verificar_tipo_saida();

    if (tipo == 1) { //txt
        FILE *file = fopen("b_output/recursos/recursos.txt", "r");
        if (file == NULL) return lista; 

        Equipamento e;
        char linha[2048];

        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha, 
                "codigo:%d,descricao:%99[^,],categoria:%49[^,],quantidade_estoque:%d,custo:%f,locacao:%f,status:%d",
                &e.codigo, e.descricao, e.categoria, &e.quantidade_estoque, 
                &e.preco_custo, &e.valor_locacao, &e.status) == 7) {
                
                NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso));
                if (novo_no != NULL) {
                    copiar_dados_recurso(&(novo_no->dados), &e);
                    novo_no->proximo = lista;
                    lista = novo_no;
                }
            }
        }
        fclose(file);
    } 
    else if (tipo == 2) { //bin
        FILE *file = fopen("b_output/recursos/recursos.bin", "rb");
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