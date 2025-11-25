#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtora.h"
#include "../../view/cadastro/produtora_view.h"
#include "../../controller/saida.h"

// =============================================
// FUNÇÃO: copiar_dados_produtora
// OBJETIVO: Copia todos os campos de uma estrutura Produtora para outra
// PARÂMETROS:
//   - destino: Ponteiro para estrutura de destino
//   - origem: Ponteiro para estrutura de origem
// =============================================
void copiar_dados_produtora(Produtora *destino, const Produtora *origem) {
    // Verifica se os ponteiros são válidos
    if (!origem || !destino) return;

    
    // Copia CNPJ (identificador único)
    strncpy(destino->cnpj, origem->cnpj, sizeof(destino->cnpj) - 1);
    destino->cnpj[sizeof(destino->cnpj) - 1] = '\0';
    
    
    // Copia nome fantasia com proteção contra overflow
    strncpy(destino->nome_fantasia, origem->nome_fantasia, sizeof(destino->nome_fantasia) - 1);
    destino->nome_fantasia[sizeof(destino->nome_fantasia) - 1] = '\0'; // Garante terminação nula
        
    // Copia razão social (nome jurídico)
    strncpy(destino->razao_social, origem->razao_social, sizeof(destino->razao_social) - 1);
    destino->razao_social[sizeof(destino->razao_social) - 1] = '\0';
    
    // Copia inscrição estadual
    strncpy(destino->inscricao_estadual, origem->inscricao_estadual, sizeof(destino->inscricao_estadual) - 1);
    destino->inscricao_estadual[sizeof(destino->inscricao_estadual) - 1] = '\0';
   
    // Copia e-mail de contato
    strncpy(destino->email, origem->email, sizeof(destino->email) - 1);
    destino->email[sizeof(destino->email) - 1] = '\0';
   
    // Copia endereço completo
    strncpy(destino->endereco_completo, origem->endereco_completo, sizeof(destino->endereco_completo) - 1);
    destino->endereco_completo[sizeof(destino->endereco_completo) - 1] = '\0';
    
    // Copia telefone da empresa
    strncpy(destino->telefone, origem->telefone, sizeof(destino->telefone) - 1);
    destino->telefone[sizeof(destino->telefone) - 1] = '\0';  
    
    // Copia nome do responsável legal
    strncpy(destino->nome_do_responsavel, origem->nome_do_responsavel, sizeof(destino->nome_do_responsavel) - 1);
    destino->nome_do_responsavel[sizeof(destino->nome_do_responsavel) - 1] = '\0';
    
    // Copia telefone do responsável
    strncpy(destino->telefone_do_responsavel, origem->telefone_do_responsavel, sizeof(destino->telefone_do_responsavel) - 1);
    destino->telefone_do_responsavel[sizeof(destino->telefone_do_responsavel) - 1] = '\0'; 

    // Copia margem de lucro padrão
    strncpy(destino->margem_de_lucro_padrao, origem->margem_de_lucro_padrao, sizeof(destino->margem_de_lucro_padrao) - 1);
    destino->margem_de_lucro_padrao[sizeof(destino->margem_de_lucro_padrao) - 1] = '\0';
}

// =============================================
// FUNÇÃO: adicionar_produtora_na_lista
// OBJETIVO: Adiciona nova produtora no início da lista encadeada (CREATE)
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - nova_produtora: Dados da nova produtora a ser adicionada
// RETORNO: Ponteiro para o novo início da lista
// =============================================
NoProdutora* adicionar_produtora_na_lista(NoProdutora* lista, Produtora nova_produtora) {
    // Aloca memória para o novo nó
    NoProdutora *novo_no = (NoProdutora*) malloc(sizeof(NoProdutora));
    
    // Verifica se a alocação foi bem sucedida
    if (novo_no == NULL) {
        exibir_mensagem_produtora("ERRO: Falha ao alocar nó da lista");
        return lista; // Retorna lista original em caso de falha
    }


    // Copia os dados da nova produtora para o nó
    copiar_dados_produtora(&(novo_no->dados), &nova_produtora);

    // Configura o próximo ponteiro (insere no início)
    novo_no->proximo = lista;

    if (verificar_tipo_saida() == 1)
    {
        FILE *file = fopen("../b_output/produtora/produtora.txt", "a");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo de produtora!\n");
            // free(novo_no); //
            return lista;
        }

        nova_produtora.status = 1;

        fprintf(file,
            "nome_fantasia:%s,razao_social:%s,inscricao_estadual:%s,cnpj:%s,endereco_completo:%s,telefone:%s,enail:%s,responsavel:%s,telefone_responsavel:%s,margem_lucro:%s,status:%d\n",
            nova_produtora.nome_fantasia,
            nova_produtora.razao_social,
            nova_produtora.inscricao_estadual,
            nova_produtora.cnpj,
            nova_produtora.endereco_completo,
            nova_produtora.telefone,
            nova_produtora.email,
            nova_produtora.nome_do_responsavel,
            nova_produtora.telefone_do_responsavel,
            nova_produtora.margem_de_lucro_padrao,
            nova_produtora.status);
        fclose(file);
        printf("Produtora salvo com sucesso!!\n");
    } 
    
    else if (verificar_tipo_saida() == 2)
    {
         FILE *file = fopen("../b_output/produtora/produtora.bin", "ab");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo binario de produtora!\n");
            // free(novo_no); //
            return lista;
        }

        nova_produtora.status == 1;

        if (fwrite(&nova_produtora,sizeof(Produtora),1,file) != 1)
        {
            printf("Erro ao escrever strcut em binario\n");
        } 
        else
        {
            printf("Strucut de produtora salva com sucesso em produtora.bin!\n");
            fclose(file);
        }


    }
    
    
    
    

    // Retorna o novo nó como início da lista
    return novo_no;
}

// =============================================
// FUNÇÃO: buscar_produtora_por_cnpj
// OBJETIVO: Busca uma produtora na lista pelo CNPJ (READ)
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - cnpj_busca: CNPJ da produtora a ser encontrada
// RETORNO: Ponteiro para os dados da produtora encontrada ou NULL
// =============================================
Produtora* buscar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca) {
    NoProdutora *atual = lista;
    
    // Percorre a lista até encontrar o CNPJ ou chegar ao final
    while (atual != NULL) {
        // CORREÇÃO: usar strcmp para comparar strings em vez de ==
        if (strcmp(atual->dados.cnpj, cnpj_busca) == 0) {
            return &(atual->dados); // Retorna ponteiro para os dados encontrados
        }
        atual = atual->proximo; // Avança para o próximo nó
    }
    return NULL; // Retorna NULL se não encontrou
}

// =============================================
// FUNÇÃO: atualizar_produtora_por_cnpj
// OBJETIVO: Atualiza dados de uma produtora existente baseado no CNPJ (UPDATE)
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - cnpj_busca: CNPJ da produtora a ser atualizada
//   - demais parâmetros: Novos dados para atualização
// =============================================
void atualizar_produtora_por_cnpj(NoProdutora* lista, const char* cnpj_busca, 
                                 const char* nome_fantasia, 
                                 const char* razao_social, const char* inscricao_estadual,    
                                 const char* email, const char* endereco_completo,  
                                 const char* telefone, const char* nome_do_responsavel,  
                                 const char* telefone_do_responsavel, const char* margem_de_lucro_padrao) {
    
    // Busca a produtora pelo CNPJ
    Produtora *produtora_existente = buscar_produtora_por_cnpj(lista, cnpj_busca);
    
    // Se encontrou, atualiza todos os campos
    if (produtora_existente != NULL) {
        

        // Atualiza nome fantasia
        strncpy(produtora_existente->nome_fantasia, nome_fantasia, sizeof(produtora_existente->nome_fantasia) - 1);
        produtora_existente->nome_fantasia[sizeof(produtora_existente->nome_fantasia) - 1] = '\0';
        
        // Atualiza razão social
        strncpy(produtora_existente->razao_social, razao_social, sizeof(produtora_existente->razao_social) - 1);
        produtora_existente->razao_social[sizeof(produtora_existente->razao_social) - 1] = '\0';
        
        // Atualiza inscrição estadual
        strncpy(produtora_existente->inscricao_estadual, inscricao_estadual, sizeof(produtora_existente->inscricao_estadual) - 1);
        produtora_existente->inscricao_estadual[sizeof(produtora_existente->inscricao_estadual) - 1] = '\0';
                
        // Atualiza e-mail
        strncpy(produtora_existente->email, email, sizeof(produtora_existente->email) - 1);
        produtora_existente->email[sizeof(produtora_existente->email) - 1] = '\0';       
        
        // Atualiza endereço completo
        strncpy(produtora_existente->endereco_completo, endereco_completo, sizeof(produtora_existente->endereco_completo) - 1);
        produtora_existente->endereco_completo[sizeof(produtora_existente->endereco_completo) - 1] = '\0';        
        
        // Atualiza telefone
        strncpy(produtora_existente->telefone, telefone, sizeof(produtora_existente->telefone) - 1);
        produtora_existente->telefone[sizeof(produtora_existente->telefone) - 1] = '\0';
        
        // Atualiza nome do responsável
        strncpy(produtora_existente->nome_do_responsavel, nome_do_responsavel, sizeof(produtora_existente->nome_do_responsavel) - 1);
        produtora_existente->nome_do_responsavel[sizeof(produtora_existente->nome_do_responsavel) - 1] = '\0';
        
        // Atualiza telefone do responsável
        strncpy(produtora_existente->telefone_do_responsavel, telefone_do_responsavel, sizeof(produtora_existente->telefone_do_responsavel) - 1);
        produtora_existente->telefone_do_responsavel[sizeof(produtora_existente->telefone_do_responsavel) - 1] = '\0';

        // Atualiza margem de lucro padrão
        strncpy(produtora_existente->margem_de_lucro_padrao, margem_de_lucro_padrao, sizeof(produtora_existente->margem_de_lucro_padrao) - 1);
        produtora_existente->margem_de_lucro_padrao[sizeof(produtora_existente->margem_de_lucro_padrao) - 1] = '\0';
    }
}

// =============================================
// FUNÇÃO: deletar_produtora_por_cnpj
// OBJETIVO: Remove uma produtora da lista baseado no CNPJ (DELETE)
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
//   - cnpj_busca: CNPJ da produtora a ser removida
// RETORNO: Ponteiro para o novo início da lista
// =============================================
int deletar_produtora_por_cnpj(NoProdutora *lista, const char* cnpj_busca) {
    if (verificar_tipo_saida() == 1) 
    {
        FILE *file = fopen("../b_output/produtora/produtora.txt", "r+");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo original!\n");
            
            return 0;
        }

        FILE *temp = fopen("../b_output/produtora/temp.txt", "w+");
        if (temp == NULL)
        {
            printf("erro ao criar arquivo temporario!\n");
            fclose(file);
            return 0;
        }

        Produtora c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file))
        {
            //lê os campos
            sscanf(linha,
                   "nome_fantasia:%49[^,],razao_social:%99[^,],inscricao_estadual:%8[^,],cnpj:%13[^,],endereco:%255[^,],telefone:%10[^,],email:%49[^,],responsavel:%49[^,],telefone_responsavel:%10[^,],margem_lucro:%5[^,],status:%d",
                    c.nome_fantasia,
                    c.razao_social,
                    c.inscricao_estadual,
                    c.cnpj,
                    c.endereco_completo,
                    c.telefone,
                    c.email,
                    c.nome_do_responsavel,
                    c.telefone_do_responsavel,
                    c.margem_de_lucro_padrao,
                    &c.status);
                
                   

            if (c.cnpj == cnpj_busca)
            {
                c.status = 0; //marca como inativo
                encontrado = 1;
            }
            //reescreve a linha (atualizada ou não)
            fprintf(temp,
                    "nome_fantasia:%s,razao_social:%s,inscricao_estadual:%s,cnpj:%s,endereco:%s,telefone:%s,email:%s,responsavel:%s,telefone_responsavel:%s,margem_lucro:%s,status:%d",
                    c.nome_fantasia,
                    c.razao_social,
                    c.inscricao_estadual,
                    c.cnpj,
                    c.endereco_completo,
                    c.telefone,
                    c.email,
                    c.nome_do_responsavel,
                    c.telefone_do_responsavel,
                    c.margem_de_lucro_padrao,
                    c.status);
        }

        fclose(file);
        fclose(temp);
       
        //substitui o original pelo temporário
        if (remove("../b_output/produtora/produtora.txt") != 0)
        {
            perror("erro ao remover o arquivo original");
            return 0;
        }

        if (rename("../b_output/produtora/temp.txt", "../b_output/produtora/produtora.txt") != 0)
        {
            perror("erro ao renomear o arquivo temporario");
            return 0;
        }

        if (encontrado)
        {
            printf("produtora com cnpj %s marcado como inativo (status = 0).\n", cnpj_busca);
            return 1;
        }
        else
        {
            printf("produtora com cnpj %s nao encontrado.\n", cnpj_busca);
            return 0;
        }
    }
    //implementação do colega para BIN
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem_produtora("aviso:delecao binaria. responsa do colega.");
        return 0; //aqui deveria ter a implementacao dele
    }
    //sua versão para memoria (modo 3)
    else if (verificar_tipo_saida() == 3)
    {
        //busca ele com qualquer status para checar se existe
        Produtora *produtora_existente = buscar_produtora_por_cnpj(lista, cnpj_busca);
        
        //se a busca encontrar e ele estiver ativo (status 1), muda o status
        if (produtora_existente && produtora_existente->status == 1)
        {
            produtora_existente->status = 0; //seta pra inativo/deletado
            return 1; //sucesso
        }
        //se nao achou ou ja estava inativo, retorna falha
        return 0;
    }
    return 0;
}

// =============================================
// FUNÇÃO: desalocar_lista_produtoras
// OBJETIVO: Libera toda a memória alocada para a lista encadeada
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista a ser desalocada
// =============================================
void desalocar_lista_produtoras(NoProdutora* lista) {
    NoProdutora *atual = lista;
    NoProdutora *proximo_no;
    
    // Percorre a lista liberando cada nó
    while (atual != NULL) {
        proximo_no = atual->proximo; // Guarda referência do próximo
        free(atual);                 // Libera nó atual
        atual = proximo_no;          // Avança para o próximo
    }
}

// =============================================
// FUNÇÃO: exibir_todas_produtoras
// OBJETIVO: Exibe no console todos os dados de todas as produtoras da lista
// PARÂMETROS:
//   - lista: Ponteiro para o início da lista
// =============================================
void exibir_todas_produtoras(NoProdutora* lista) {
    NoProdutora *atual = lista;
    
    // Verifica se a lista está vazia
    if (atual == NULL) {
        printf("+--------------------------+\n");
        printf("| Nenhuma produtora cadastrada! |\n");
        printf("+--------------------------+\n");
        return;
    }

    // Cabeçalho da lista
    printf("\n==== LISTA DE PRODUTORAS CADASTRADAS ====\n");
    
    // Percorre e exibe todas as produtoras
    while (atual != NULL) {
        exibir_produtora(&(atual->dados)); // Usa função da view para exibir
        atual = atual->proximo;
    }
    
    // Rodapé da lista
    printf("=======================================\n");
}
