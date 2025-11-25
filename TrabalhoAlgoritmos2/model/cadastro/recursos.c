#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursos.h"
#include "../../controller/saida.h" //pra saber se ta em modo memoria (critico!)
#include "../../view/cadastro/recursos_view.h" //p exibir mensagem de erro

//--- funcoes auxiliares ---
//copia tudo de um recurso pro outro na moral
void copiar_dados_recurso(Equipamento *destino, const Equipamento *origem) {
    //verifica se eh nulo se for vaza
    if (!origem || !destino) return; 

    //copia os int e float direto
    destino->codigo = origem->codigo;
    destino->quantidade_estoque = origem->quantidade_estoque;
    destino->preco_custo = origem->preco_custo;
    destino->valor_locacao = origem->valor_locacao;
    destino->status = origem->status; //copia o status tbm
    
    //copia segura das strings (strncpy pra n dar errado)
    strncpy(destino->descricao, origem->descricao, sizeof(destino->descricao) - 1);
    destino->descricao[sizeof(destino->descricao) - 1] = '\0'; //garante o fim da string
    strncpy(destino->categoria, origem->categoria, sizeof(destino->categoria) - 1);
    destino->categoria[sizeof(destino->categoria) - 1] = '\0'; //garante o fim da string
}

//funcoes de manipulacao de lista ligada (crud)
//cria um novo no e poe ele no comeco da lista (c)
NoRecurso* adicionar_recurso_na_lista(NoRecurso* lista, Equipamento novo_recurso) {
    //avisa se nao for modo memoria, a responsabilidade nao eh sua
   
    NoRecurso *novo_no = (NoRecurso*) malloc(sizeof(NoRecurso)); //pede memoria pro no novo
    
    if (novo_no == NULL) {
        //se n deu pra alocar a gente so retorna a lista antiga
        exibir_mensagem_recursos("erro:falha ao alocar no de recurso na memoria.");
        return lista; 
    }
    
   

    //copia os dados pro no q a gente criou
    copiar_dados_recurso(&(novo_no->dados), &novo_recurso);

    //o no novo sempre vira a cabeca da lista
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1)
    {
        FILE *file = fopen("../b_output/recursos/recursos.txt", "a");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo de recursos!\n");
            // free(novo_no); //
            return lista;
        }

        fprintf(file,
            "codigo:%d,descricao:%s,categoria:%s,quantidade_estoque:%d,custo:%.2f,locacao:%.2f\n",
            novo_recurso.codigo,
            novo_recurso.descricao,
            novo_recurso.categoria,
            novo_recurso.quantidade_estoque,
            novo_recurso.preco_custo,
            novo_recurso.valor_locacao);
        fclose(file);
        printf("Recursos salvos com sucesso!!\n");
    }
    else if (verificar_tipo_saida() == 2)
    {
         FILE *file = fopen("../b_output/recursos/recursos.bin", "ab");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo binário de recursos!\n");
            // free(novo_no); // Descomente se 'novo_no' foi alocado antes
            return lista;
        }

      

        if (fwrite(&novo_recurso,sizeof(Equipamento),1,file) != 1)
        {
            printf("Erro ao escrever strcut em binario\n");
        } 
        else
        {
            printf("Strucut de recursos salva com sucesso em recursos.bin!\n");
            fclose(file);
        }

        
    }
    


    return novo_no; //devolve a nova cabeca
}

//procura o recurso pelo codigo (r)
Equipamento* buscar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    NoRecurso *atual = lista;
    //percorre a lista ate achar o codigo ou a lista acabar
    while (atual != NULL) {
        //so retorna se o status for 1 (ativo)
        if (atual->dados.codigo == codigo_busca && atual->dados.status == 1) {
            return &(atual->dados); //achou! devolve o ponteiro pros dados do equip
        }
        atual = atual->proximo;
    }
    return NULL; //nao achou
}

//atualiza os dados de quem ja existe na lista (u)
void atualizar_recurso_por_codigo(NoRecurso* lista, int codigo_busca, const char* descricao, const char* categoria, int quantidade_estoque, float preco_custo, float valor_locacao) {
    //busca o recurso ativo na lista em memoria
    Equipamento *recurso_existente = buscar_recurso_por_codigo(lista, codigo_busca);
    
    if (recurso_existente) {
        //atualiza os floats e ints
        recurso_existente->quantidade_estoque = quantidade_estoque;
        recurso_existente->preco_custo = preco_custo;
        recurso_existente->valor_locacao = valor_locacao; 
        
        //atualiza as strings com copia segura
        strncpy(recurso_existente->descricao, descricao, sizeof(recurso_existente->descricao) - 1);
        recurso_existente->descricao[sizeof(recurso_existente->descricao) - 1] = '\0';
        strncpy(recurso_existente->categoria, categoria, sizeof(recurso_existente->categoria) - 1);
        recurso_existente->categoria[sizeof(recurso_existente->categoria) - 1] = '\0';
        
        //avisa se nao for memoria (a responsa do arquivo nao eh sua)
        if (verificar_tipo_saida() != 3) {
            exibir_mensagem_recursos("");
        }
    }
}


//deleta o no da lista (d) - so funciona em modo memoria
int deletar_recurso_por_codigo(NoRecurso* lista, int codigo_busca) {
    //avisa se nao for modo memoria, a responsa nao eh sua
    if (verificar_tipo_saida() == 1) //lógica de deleção txt complexa do colega
    {
        FILE *file = fopen("../b_output/recursos/recursos.txt", "r+");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo original!\n");
            
            return 0;
        }

        FILE *temp = fopen("../b_output/recursos/temp.txt", "w+");
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
            //lê os campos
            sscanf(linha,
                   "codigo:%d,descricaco:%99[^,],categoria:%49[^,],estoque:%d,preco_custo:%.2f,valor_locacao:%.2f,status:%d",
                   &c.codigo,
                   c.descricao,
                   c.categoria,
                   c.quantidade_estoque,
                   c.preco_custo,
                   c.valor_locacao,
                   &c.status);
                
                   

            if (c.codigo == codigo_busca)
            {
                c.status = 0; //marca como inativo
                encontrado = 1;
            }
            //reescreve a linha (atualizada ou não)
            fprintf(temp,
                    "codigo:%d,descricaco:%s,categoria:%s,estoque:%d,preco_custo:%.2f,valor_locacao:%.2f,status:%d",
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
       
        //substitui o original pelo temporário
        if (remove("../b_output/recursos/recursos.txt") != 0)
        {
            perror("erro ao remover o arquivo original");
            return 0;
        }

        if (rename("../b_output/recursos/temp.txt", "../b_output/recursos/recursos.txt") != 0)
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
    //implementação do colega para BIN
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem_recursos("aviso:delecao binaria. responsa do colega.");
        return 0; //aqui deveria ter a implementacao dele
    }
    //sua versão para memoria (modo 3)
    else if (verificar_tipo_saida() == 3)
    {
        //busca ele com qualquer status para checar se existe
        Equipamento *equipamento_existente = buscar_recurso_por_codigo(lista, codigo_busca);
        
        //se a busca encontrar e ele estiver ativo (status 1), muda o status
        if (equipamento_existente && equipamento_existente->status == 1)
        {
            equipamento_existente->status = 0; //seta pra inativo/deletado
            return 1; //sucesso
        }
        //se nao achou ou ja estava inativo, retorna falha
        return 0;
    }
    return 0;
}

//mt critica: libera a memoria p n dar memory leak (so em memoria)
void desalocar_lista_recursos(NoRecurso* lista) {
    //so faz se tiver em modo memoria
    if (verificar_tipo_saida() != 3) {
        return; //nao desaloca se nao eh modo memoria
    }
    
    NoRecurso *atual = lista;
    NoRecurso *proximo_no;
    //roda a lista toda dando free em cada no
    while (atual != NULL) {
        proximo_no = atual->proximo; 
        free(atual);
        atual = proximo_no;
    }
}

//pra mostrar geral (so os ativos em memoria)
void exibir_todos_recursos(NoRecurso* lista) {
    //so exibe se estiver em modo memoria
    if (verificar_tipo_saida() != 3) {
        exibir_mensagem_recursos("");
        return;
    }
    
    NoRecurso *atual = lista;
    int contador = 0; //pra saber se a lista ta vazia

    exibir_cabecalho_lista_recursos(); //chama a view pra mostrar o cabecalho
    
    while (atual != NULL) {
        //filtra por status ativo
        if (atual->dados.status == 1) { 
            exibir_recurso(&(atual->dados)); //chama a view pra mostrar cada um
            contador++;
        }
        atual = atual->proximo;
    }

    if (contador == 0) {
        exibir_mensagem_recursos("nenhum recurso/equipamento cadastrado!");
    }
    exibir_rodape_lista_recursos(); //chama a view pra mostrar o rodape
}

//funcao auxiliar que so retorna a lista no modo memoria
NoRecurso* carregar_recursos(NoRecurso* lista) {
    return lista; //a lista ja ta no escopo global ent so retorna ela
}