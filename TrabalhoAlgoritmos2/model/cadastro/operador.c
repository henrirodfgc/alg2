#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <errno.h>
#include <windows.h>
#include "operador.h"
#include "../../view/cadastro/operador_view.h"
#include "../../controller/saida.h"

void copiar_dados_operador(Operador *destino, const Operador *origem){

    if (!origem || !destino) return;
    
    destino->codigo = origem->codigo;

    strncpy(destino->nome, origem->nome, sizeof(destino->nome) - 1);
    destino->nome[sizeof(destino->nome) -1]= '\0';
    
    strncpy(destino->usuario, origem->usuario, sizeof(destino->usuario) - 1);
    destino->usuario[sizeof(destino->usuario) -1]= '\0';
    
    strncpy(destino->senha, origem->senha, sizeof(destino->senha) - 1);
    destino->senha[sizeof(destino->senha) -1]= '\0';
}

NoOperador* adicionar_operador_na_lista(NoOperador* lista, Operador novo_operador){

    NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));

    if(novo_no == NULL){
        exibir_mensagem_operador("ERRO: Falha ao alocar nó da lista");
        return lista;
    }

    copiar_dados_operador(&(novo_no->dados), &novo_operador);

    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1)
    {
        FILE *file = fopen("../b_output/operador/operadores.txt", "a");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo de operador!\n");
            // free(novo_no); //
            return lista;
        }

        
        novo_operador.status = 1;
        printf ("status ativado");

        fprintf(file,
            "id:%d,nome:%s,usuario:%s,senha:%s,status:%d\n",
            novo_operador.codigo,
            novo_operador.nome,
            novo_operador.usuario,
            novo_operador.senha,
            novo_operador.status);
            
        fclose(file);
        printf("Operador salvo com sucesso!!\n");
    }

    else if (verificar_tipo_saida() == 2)
    {
        FILE *file = fopen("../b_output/operador/operadores.bin", "ab");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo binário de operador!\n");
            // free(novo_no); // Descomente se 'novo_no' foi alocado antes
            return lista;
        }

        novo_operador.status = 1;

        if (fwrite(&novo_operador,sizeof(Operador),1,file) != 1)
        {
            printf("Erro ao escrever strcut em binario\n");
        } 
        else
        {
            printf("Strucut de operador salva com sucesso em operadores.bin!\n");
            fclose(file);
        }

        
    }

    

    return novo_no;
}

Operador* buscar_operador_por_codigo(NoOperador* lista, int codigo_busca){
    NoOperador *atual = lista;

    while (atual != NULL){
        
        if (atual-> dados.codigo == codigo_busca)
        {
            return &(atual->dados);
        }
        
        atual = atual->proximo;
    }
    return NULL;
    
}

int atualizar_operador_por_codigo(NoOperador* lista, int codigo_busca, const char* nome, const char* usuario, const char* senha){

    Operador *operador_existente = buscar_operador_por_codigo(lista, codigo_busca);

    if (operador_existente != NULL)
    {
        strncpy(operador_existente->nome, nome, sizeof(operador_existente-> nome) -1);
        operador_existente->nome[sizeof(operador_existente->nome)-1] = '\0';

        strncpy(operador_existente->usuario, usuario, sizeof(operador_existente-> usuario) -1);
        operador_existente->usuario[sizeof(operador_existente->usuario)-1] = '\0';

        strncpy(operador_existente->senha, senha, sizeof(operador_existente-> senha) -1);
        operador_existente->senha[sizeof(operador_existente->senha)-1] = '\0';
    
         if (verificar_tipo_saida() == 1)
        {
            FILE *file = fopen("../b_output/operador/operadores.txt", "r+");
            if (file==NULL)
            {
                printf("erro ao abrir o arquivo original!\n");
            
                return 0;
            }

            FILE *temp = fopen("../b_output/operador/temp.txt", "w+");
            if (temp == NULL)
            {
                printf("erro ao criar arquivo temporario!\n");
                fclose(file);
                return 0;
            }

            Operador c;
            char linha[2048];
            int encontrado = 0;



            while (fgets(linha, sizeof(linha), file))
         {
            //lê os campos
            sscanf(linha,
                   "id:%d,nome:%49[^,],usuario:%59[^,],senha:%19[^,],status:%d",
                   &c.codigo,
                   c.nome,
                   c.usuario,
                   c.senha,
                   &c.status);
                   
                   

            if (c.codigo == operador_existente->codigo)
            {
                fprintf(temp,
                    "id:%d,nome:%s,usuario:%s,senha:%s,status:%d",
                    operador_existente->codigo,
                    operador_existente->nome,
                    operador_existente->usuario,
                    operador_existente->senha,
                    operador_existente->status);
                    

                    encontrado = 1;
            
            } else {
                fprintf(temp, "%s", linha);
             }
            
            
         }

            fclose(file);
            fclose(temp);


            //substitui o original pelo temporário
            if (remove("../b_output/operador/operadores.txt") != 0)
            {
                perror("erro ao remover o arquivo original");
                return 0;
            }

            if (rename("../b_output/operador/temp.txt", "../b_output/operador/operadores.txt") != 0)
            {
                perror("erro ao renomear o arquivo temporario");
                return 0;
            }

            if (encontrado)
            {
                printf("operador com id %d atualizado.\n", codigo_busca);
                return 1;
            }
            else
            {
                printf("operador com id %d nao encontrado.\n", codigo_busca);
                return 0;
            }

        }
        
    }
    return 1;
    
}
    
    
    
    
    
    


int deletar_operador_por_codigo(NoOperador* lista, int codigo_busca){
   if (verificar_tipo_saida() == 1) 
    {
        FILE *file = fopen("../b_output/operador/operadores.txt", "r+");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo original!\n");
            
            return 0;
        }

        FILE *temp = fopen("../b_output/operador/temp.txt", "w+");
        if (temp == NULL)
        {
            printf("erro ao criar arquivo temporario!\n");
            fclose(file);
            return 0;
        }

        Operador c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file))
        {
            //lê os campos
            sscanf(linha,
                   "codigo:%d,nome:%49[^,],usuario:%59[^,],senha:%19[^,],status:%d",
                   &c.codigo,
                   c.nome,
                   c.usuario,
                   c.senha,
                   &c.status);
                   
                
                   

            if (c.codigo == codigo_busca)
            {
                c.status = 0; //marca como inativo
                encontrado = 1;
            }
            //reescreve a linha (atualizada ou não)
            fprintf(temp,
                   "codigo:%d,nome:%s,usuario:%s,senha:%s,status:%d",
                   c.codigo,
                   c.nome,
                   c.usuario,
                   c.senha,
                   c.status);
        }

        fclose(file);
        fclose(temp);
       
        //substitui o original pelo temporário
        if (remove("../b_output/operador/operadores.txt") != 0)
        {
            perror("erro ao remover o arquivo original");
            return 0;
        }

        if (rename("../b_output/operador/temp.txt", "../b_output/operador/operadores.txt") != 0)
        {
            perror("erro ao renomear o arquivo temporario");
            return 0;
        }

        if (encontrado)
        {
            printf("operador com id %d marcado como inativo (status = 0).\n", codigo_busca);
            return 1;
        }
        else
        {
            printf("operador com id %d nao encontrado.\n", codigo_busca);
            return 0;
        }
    }
    //implementação BIN
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem_operador("ainda nao feito");
        return 0; //aqui deveria ter a implementacao dele
    }
    //sua versão para memoria (modo 3)
    else if (verificar_tipo_saida() == 3)
    {
        //busca ele com qualquer status para checar se existe
        Operador *operador_existente = buscar_operador_por_codigo(lista, codigo_busca);
        
        //se a busca encontrar e ele estiver ativo (status 1), muda o status
        if (operador_existente && operador_existente->status == 1)
        {
            operador_existente->status = 0; //seta pra inativo/deletado
            return 1; //sucesso
        }
        //se nao achou ou ja estava inativo, retorna falha
        return 0;
    }
    return 0;
}
    
void deslocar_lista_operador(NoOperador* lista){

    NoOperador *atual = lista;
    NoOperador *proximo_no;

    while (atual != NULL)
    {
        proximo_no = atual -> proximo;
        free(atual);
        atual = proximo_no;
    }
    
}

void exibir_todos_operadores(NoOperador* lista){
    NoOperador *atual = lista;

    if (atual == NULL)
    {
        printf("+-----------------------+");
        printf("|Nunhum operador cadastrado|");
        printf("+-------------------------+");
        return;

    }

    printf("\n===LISTA DE OPERADORES CADASTRADOS========\n");

    while (atual !=NULL)
    {
        exibir_operador(&(atual->dados));
        atual = atual-> proximo;
    }
    
    printf("=============================================\n");
}

NoOperador* carregar_operadores(NoOperador* lista){
    if (lista != NULL) return lista;

    int tipo = verificar_tipo_saida();

    if (tipo == 1) { //txt
        FILE *file = fopen("../b_output/operador/operadores.txt", "r");
        if (file == NULL) return lista;

        Operador op;
        char linha[2048];

        while (fgets(linha, sizeof(linha), file)) {
            if (sscanf(linha,
                   "id:%d,nome:%49[^,],usuario:%59[^,],senha:%19[^,],status:%d",
                   &op.codigo,
                   op.nome,
                   op.usuario,
                   op.senha,
                   &op.status) == 5) {
                
                NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));
                if (novo_no != NULL) {
                    copiar_dados_operador(&(novo_no->dados), &op);
                    novo_no->dados.status = op.status;
                    novo_no->proximo = lista;
                    lista = novo_no;
                }
            }
        }
        fclose(file);
    }
    else if (tipo == 2) { //bin
        FILE *file = fopen("../b_output/operador/operadores.bin", "rb");
        if (file == NULL) return lista;

        Operador op;
        while (fread(&op, sizeof(Operador), 1, file) == 1) {
            NoOperador *novo_no = (NoOperador*) malloc(sizeof(NoOperador));
            if (novo_no != NULL) {
                copiar_dados_operador(&(novo_no->dados), &op);
                novo_no->dados.status = op.status;
                novo_no->proximo = lista;
                lista = novo_no;
            }
        }
        fclose(file);
    }
    return lista;
}