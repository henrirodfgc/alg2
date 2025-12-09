#include <stdio.h>
#include <stdlib.h>
#include "../../model/cadastro/produtora.h"
#include "produtora_view.h"


char* ler_cnpj_para_operacao(const char* operacao) {
    static char cnpj[15]; // Buffer estático para armazenar CNPJ (14 dígitos + \0)
    
    // Solicita CNPJ ao usuário
    printf("\nDigite o cnpj do produtora para %s: \n", operacao);
    
    // Lê CNPJ com limite de 14 caracteres
    if (scanf("%14s", cnpj) != 1) {
        // Limpa buffer de entrada em caso de erro
        while (getchar() != '\n'); 
        return NULL; // Retorna NULL indicando falha na leitura
    }
    return cnpj; // Retorna ponteiro para o CNPJ lido
}


void exibir_produtora(const Produtora* produtora) {
    // Verifica se a produtora existe
    if (!produtora) {
        printf("+--------------------------+\n");
        printf("| Produtora inexistente!   |\n");
        printf("+--------------------------+\n");
        return;
    }
    
    // Exibe dados formatados da produtora
    printf("\n+---------------------------------+\n");
    printf("| CNPJ                    : %s\n", produtora->cnpj);
    printf("| Nome Fantasia           : %s\n", produtora->nome_fantasia);
    printf("| Razao Social            : %s\n", produtora->razao_social);
    printf("| Iscrição Estadual       : %s\n", produtora->inscricao_estadual);
    printf("| Endereco                : %s\n", produtora->endereco_completo);
    printf("| Telefone                : %s\n", produtora->telefone);
    printf("| Email                   : %s\n", produtora->email);
    printf("| Nome do Responsável     : %s\n", produtora->nome_do_responsavel);
    printf("| Telefone do Responsavel : %s\n", produtora->telefone_do_responsavel);
    printf("| Margem de Lucro Padrão  : %s\n", produtora->margem_de_lucro_padrao);
    printf("+---------------------------------+\n");
}


void exibir_menu_produtora() {
    
    
    printf("\n==== MENU PRODUTORA ====\n");
    
    
    printf("1 - Criar produtora\n");
    printf("2 - Atualizar produtora\n");
    printf("3 - Exibir produtora\n");
    printf("4 - Deletar produtora\n");
    printf("5 - Listar todas\n"); 
    printf("0 - Sair\n");
    printf("Escolha: ");    
   
}


Produtora ler_dados_produtora() {
    Produtora c; // Estrutura temporária para armazenar dados
     int ch;
    
    // Limpa buffer ANTES do primeiro campo, se necessário
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    // Coleta dados da produtora campo a campo
    printf("CNPJ: "); 
    scanf("%14[^\n]", c.cnpj); // Limita a 14 caracteres
    while ((ch = getchar()) != '\n' && ch != EOF); // Limpa após cada leitura

    printf("Nome Fantasia: "); 
    scanf(" %50[^\n]", c.nome_fantasia); // Espaço antes para consumir quebra de linha
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Razão Social: "); 
    scanf("%100[^\n]", c.razao_social);
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Inscrição Estadual: "); 
    scanf("%9[^\n]", c.inscricao_estadual); // Limita a 9 caracteres
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Endereco: "); 
    scanf(" %256[^\n]", c.endereco_completo);
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Telefone: "); 
    scanf(" %11[^\n]", c.telefone);
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Email: "); 
    scanf(" %50[^\n]", c.email);
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Nome do Responsável: "); 
    scanf(" %50[^\n]", c.nome_do_responsavel);
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Telefone do Responsável: "); 
    scanf(" %11[^\n]", c.telefone_do_responsavel); 
    while ((ch = getchar()) != '\n' && ch != EOF); 

    printf("Margem de Lucro Padrão: "); 
    scanf(" %6[^\n]", c.margem_de_lucro_padrao);
    while ((ch = getchar()) != '\n' && ch != EOF); 

    return c; // Retorna estrutura preenchida
}


void ler_dados_atualizacao_produtora( char* cnpj, char* nome_fantasia, 
                                     char* razao_social, char* incricao_estadual,
                                     char* endereco_completo, char* telefone, 
                                     char* email, char* nome_do_responsavel,  
                                     char* telefone_do_responsavel,char* margem_de_lucro_padrao) {
    
    
   
   
    printf("Nova cnpj(14 digitos): "); 
    scanf(" %14[^\n]", cnpj);
   
    printf("Novo nome fantasia: "); 
    scanf(" %50[^\n]", nome_fantasia);
    
    printf("Nova razao social: "); 
    scanf(" %100[^\n]", razao_social);
    
    printf("Nova inscrição estadual: "); 
    scanf(" %9[^\n]", incricao_estadual); 
    
    printf("Novo endereco: "); 
    scanf(" %256[^\n]", endereco_completo);
    
    printf("Novo telefone: "); 
    scanf(" %11[^\n]", telefone); 
    
    printf("Novo email: "); 
    scanf(" %50[^\n]", email);    
    
    printf("Novo nome do responsável: "); 
    scanf(" %50[^\n]", nome_do_responsavel);
    
    printf("Novo telefone do responsável: "); 
    scanf(" %11[^\n]", telefone_do_responsavel);
        
    printf("Nova margem de lucro: "); 
    scanf(" %6[^\n]", margem_de_lucro_padrao);
        
}


void exibir_mensagem_produtora(const char* msg) {
    printf("%s\n", msg);
}

void exibir_todas_produtoras(NoProdutora* lista) {
    NoProdutora *atual = lista;
    int cont = 0;
    printf("\n==== lista de produtoras ====\n");
    while (atual != NULL) {
        if (atual->dados.status == 1) {
            exibir_produtora(&(atual->dados));
            cont++;
        }
        atual = atual->proximo;
    }
    if (cont == 0) printf("nenhuma produtora ativa.\n");
    printf("=============================\n");
}