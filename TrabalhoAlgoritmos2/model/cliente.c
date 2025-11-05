#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <errno.h>
#include <windows.h>
#include "cliente.h"
#include "../view/cliente_view.h"
#include "../controller/saida.h"

//--- funções auxiliares ---
// copia tudo de uma struct cliente pra outra de forma segura
void copiar_dados(Cliente *destino, const Cliente *origem)
{
    if (!origem || !destino)
        return; // se for null sai fora pra n dar bo

    destino->id = origem->id;
    destino->idade = origem->idade;
    destino->status = origem->status; // agora copia o status tbm!

    // cópia segura de todas as strings (strncpy é vida)
    strncpy(destino->nome_cliente, origem->nome_cliente, sizeof(destino->nome_cliente) - 1);
    destino->nome_cliente[sizeof(destino->nome_cliente) - 1] = '\0';
    strncpy(destino->nome_razao, origem->nome_razao, sizeof(destino->nome_razao) - 1);
    destino->nome_razao[sizeof(destino->nome_razao) - 1] = '\0';
    strncpy(destino->endereco, origem->endereco, sizeof(destino->endereco) - 1);
    destino->endereco[sizeof(destino->endereco) - 1] = '\0';
    strncpy(destino->cpf, origem->cpf, sizeof(destino->cpf) - 1);
    destino->cpf[sizeof(destino->cpf) - 1] = '\0';
    strncpy(destino->cnpj, origem->cnpj, sizeof(destino->cnpj) - 1);
    destino->cnpj[sizeof(destino->cnpj) - 1] = '\0';
    strncpy(destino->email, origem->email, sizeof(destino->email) - 1);
    destino->email[sizeof(destino->email) - 1] = '\0';
    strncpy(destino->telefone, origem->telefone, sizeof(destino->telefone) - 1);
    destino->telefone[sizeof(destino->telefone) - 1] = '\0';
    strncpy(destino->nome_contato, origem->nome_contato, sizeof(destino->nome_contato) - 1);
    destino->nome_contato[sizeof(destino->nome_contato) - 1] = '\0';
}

// procura um client pelo id e retorna o ponteiro pra struct cliente independente do status
// essa é auxiliar pra exclusão/restauração e nao é exportada no .h
Cliente *buscar_cliente_qualquer_status(NoCliente *lista, int id_busca)
{
    NoCliente *atual = lista;
    while (atual != NULL)
    {
        if (atual->dados.id == id_busca)
        {
            return &(atual->dados); // achou, não importa o status
        }
        atual = atual->proximo;
    }
    return NULL; // não achou
}

//--- funções de manipulação de lista ligada (crud) ---
// cria um novo nó e põe ele no começo da lista (create)
NoCliente *adicionar_cliente_na_lista(NoCliente *lista, Cliente novo_cliente)
{
    // Verifica se existe a pasta, se não existir, ele cria
    if (_mkdir("../b_output/clientes") == -1 && errno != EEXIST)
    {
        printf("Erro ao criar pasta clientes!\n");
    }

    // Salva no arquivo txt se o tipo saida for txt
    if (verificar_tipo_saida() == 1)
    {
        // Cria o arquivo
        FILE *file = fopen("../b_output/clientes/cliente.txt", "a");
        // Se der o erro ao abrir o arquivo
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo!\n");
            return lista;
        }
        // Define cliente ativo
        novo_cliente.status = 1;

        // Escreve struct no arquivo
        fprintf(file, "id:%d,nome_cliente:%s,nome_razao:%s,idade:%d,endereco:%s,cpf:%s,cnpj:%s,email:%s,telefone:%s,nome_contato:%s,status:%d\n",
                novo_cliente.id, novo_cliente.nome_cliente, novo_cliente.nome_razao,
                novo_cliente.idade, novo_cliente.endereco, novo_cliente.cpf, novo_cliente.cnpj,
                novo_cliente.email, novo_cliente.telefone, novo_cliente.nome_contato, novo_cliente.status);
        // Fecha o arquivo
        fclose(file);
        printf("Arquivo salvo com sucesso!\n");
    }
    // Salva no arquivo txt se o tipo saida for bin
    else if (verificar_tipo_saida() == 2)
    {
        FILE *file = fopen("../b_output/clientes/cliente.bin", "ab");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo!");
            return lista;
        }
        novo_cliente.status = 1;
        if (fwrite(&novo_cliente, sizeof(Cliente), 1, file) != 1)
            printf("Erro ao escrever a struct no arquivo.\n");
        else
            printf("Struct adicionada com sucesso ao final do arquivo.\n");
        fclose(file);
    }
    // Salva no arquivo txt se o tipo saida for mem
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *novo_no = (NoCliente *)malloc(sizeof(NoCliente));
        if (novo_no == NULL)
        {
            exibir_mensagem("erro: falha ao alocar nó da lista");
            return lista;
        }
        novo_cliente.status = 1;
        copiar_dados(&(novo_no->dados), &novo_cliente);
        novo_no->proximo = lista;
        return novo_no;
    }

    return lista;
}

// procura um client pelo id e retorna o ponteiro pra struct cliente
// agora só retorna se o status for 1 (ativo)
Cliente *buscar_cliente_por_id(NoCliente *lista, int id_busca)
{
    NoCliente *atual = lista;
    // percorre a lista
    while (atual != NULL)
    {
        // checa se o id bate e se o status é 1
        if (atual->dados.id == id_busca && atual->dados.status == 1)
        {
            return &(atual->dados); // achou e tá ativo
        }
        atual = atual->proximo;
    }
    return NULL; // não achou ou tá inativo
}

// muda o status pra 0 (soft delete)
int deletar_cliente_por_id_logico(NoCliente *lista, int id_busca)
{
    if (verificar_tipo_saida() == 1)
    {
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r+");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo original!\n");
            fclose(file);
            return 0;
        }

        FILE *temp = fopen("../b_output/clientes/temp.txt", "w");
        if (temp == NULL)
        {
            printf("Erro ao criar arquivo temporário!\n");
            fclose(temp);
            return 0;
        }

        Cliente c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file))
        {
            // Lê os campos
            sscanf(linha,
                   "id:%d,nome_cliente:%49[^,],nome_razao:%99[^,],idade:%d,endereco:%255[^,],cpf:%11[^,],cnpj:%14[^,],email:%49[^,],telefone:%19[^,],nome_contato:%49[^,],status:%d",
                   &c.id,
                   c.nome_cliente,
                   c.nome_razao,
                   &c.idade,
                   c.endereco,
                   c.cpf,
                   c.cnpj,
                   c.email,
                   c.telefone,
                   c.nome_contato,
                   &c.status);

            if (c.id == id_busca)
            {
                c.status = 0; // marca como inativo
                encontrado = 1;
            }
            // Reescreve a linha (atualizada ou não)
            fprintf(temp,
                    "id:%d,nome_cliente:%s,nome_razao:%s,idade:%d,endereco:%s,cpf:%s,cnpj:%s,email:%s,telefone:%s,nome_contato:%s,status:%d\n",
                    c.id, c.nome_cliente, c.nome_razao, c.idade, c.endereco,
                    c.cpf, c.cnpj, c.email, c.telefone, c.nome_contato, c.status);
        }

        fclose(file);
        fclose(temp);
        Sleep(10);

        // Substitui o original pelo temporário
        if (remove("../b_output/clientes/cliente.txt") != 0)
        {
            perror("Erro ao remover o arquivo original");
            return 0;
        }

        if (rename("../b_output/clientes/temp.txt", "../b_output/clientes/cliente.txt") != 0)
        {
            perror("Erro ao renomear o arquivo temporário");
            return 0;
        }

        if (encontrado)
        {
            printf("Cliente com ID %d marcado como inativo (status = 0).\n", id_busca);
            return 1;
        }
        else
        {
            printf("Cliente com ID %d não encontrado.\n", id_busca);
            return 0;
        }
        return 0;

    }
    else if (verificar_tipo_saida() == 3)
    {
        // aqui a gente busca ele mesmo se tiver inativo pra n criar duplicidade na restauração
        Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca);
        // se a busca encontrar o cliente, muda o status
        if (cliente_existente)
        {
            cliente_existente->status = 0; // seta pra inativo/deletado
            return 1;
        }
        return 0;
    }
    return 0;
}

// novo: muda o status de 0 pra 1 (restauração)
void restaurar_cliente_por_id(NoCliente *lista, int id_busca)
{
    // aqui a gente busca ele com qualquer status, já que ele tá "escondido"
    Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca);

    // se encontrou e ele estava inativo, reativa
    if (cliente_existente && cliente_existente->status == 0)
    {
        cliente_existente->status = 1; // seta pra ativo
    }
}

// atualiza os dados de um client q já existe pelo id
void atualizar_cliente_por_id(NoCliente *lista, int id_busca, const char *nome_cliente, int idade, const char *nome_razao, const char *cpf, const char *cnpj, const char *endereco, const char *email, const char *telefone, const char *nome_contato)
{
    Cliente *cliente_existente = buscar_cliente_por_id(lista, id_busca);

    if (cliente_existente)
    {
        // o status continua 1, a gente só atualiza os outros campos
        cliente_existente->idade = idade;

        // atualiza os campos string com cópia segura (strncpy)
        strncpy(cliente_existente->nome_cliente, nome_cliente, sizeof(cliente_existente->nome_cliente) - 1);
        cliente_existente->nome_cliente[sizeof(cliente_existente->nome_cliente) - 1] = '\0';
        strncpy(cliente_existente->nome_razao, nome_razao, sizeof(cliente_existente->nome_razao) - 1);
        cliente_existente->nome_razao[sizeof(cliente_existente->nome_razao) - 1] = '\0';
        strncpy(cliente_existente->endereco, endereco, sizeof(cliente_existente->endereco) - 1);
        cliente_existente->endereco[sizeof(cliente_existente->endereco) - 1] = '\0';
        strncpy(cliente_existente->cpf, cpf, sizeof(cliente_existente->cpf) - 1);
        cliente_existente->cpf[sizeof(cliente_existente->cpf) - 1] = '\0';
        strncpy(cliente_existente->cnpj, cnpj, sizeof(cliente_existente->cnpj) - 1);
        cliente_existente->cnpj[sizeof(cliente_existente->cnpj) - 1] = '\0';
        strncpy(cliente_existente->email, email, sizeof(cliente_existente->email) - 1);
        cliente_existente->email[sizeof(cliente_existente->email) - 1] = '\0';
        strncpy(cliente_existente->telefone, telefone, sizeof(cliente_existente->telefone) - 1);
        cliente_existente->telefone[sizeof(cliente_existente->telefone) - 1] = '\0';
        strncpy(cliente_existente->nome_contato, nome_contato, sizeof(cliente_existente->nome_contato) - 1);
        cliente_existente->nome_contato[sizeof(cliente_existente->nome_contato) - 1] = '\0';
    }
}

// função essencial: libera a memória
void desalocar_lista_clientes(NoCliente *lista)
{
    NoCliente *atual = lista;
    NoCliente *proximo_no;
    // roda a lista toda dando free em cada nó
    while (atual != NULL)
    {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
}

// função pra mostrar todos (read all)
// so mostra quem tem status 1
void exibir_todos_clientes(NoCliente *lista)
{
    if (verificar_tipo_saida() == 1)
    {
        printf("\n==== lista de clientes cadastrados ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo TXT!\n");
            return;
        }
        Cliente c;
        char linha[2048]; // linha completa do arquivo

        while (fgets(linha, sizeof(linha), file))
        {
            // lê e extrai os valores da linha conforme os rótulos
            sscanf(linha,
                   "id:%d,nome_cliente:%49[^,],nome_razao:%49[^,],idade:%d,endereco:%99[^,],cpf:%19[^,],cnpj:%19[^,],email:%49[^,],telefone:%19[^,],nome_contato:%49[^,],status:%d",
                   &c.id,
                   c.nome_cliente,
                   c.nome_razao,
                   &c.idade,
                   c.endereco,
                   c.cpf,
                   c.cnpj,
                   c.email,
                   c.telefone,
                   c.nome_contato,
                   &c.status);

            if (c.status == 1)
            {
                // exibe formatado
                printf("ID: %d\n", c.id);
                printf("Nome: %s\n", c.nome_cliente);
                printf("Razão Social: %s\n", c.nome_razao);
                printf("Idade: %d\n", c.idade);
                printf("Endereço: %s\n", c.endereco);
                printf("CPF: %s\n", c.cpf);
                printf("CNPJ: %s\n", c.cnpj);
                printf("Email: %s\n", c.email);
                printf("Telefone: %s\n", c.telefone);
                printf("Contato: %s\n", c.nome_contato);
                printf("Status: %d\n", c.status);
                printf("\n");
            }
        }
        printf("=======================================\n");
    }
    else if (verificar_tipo_saida() == 2)
    {
        printf("\n==== lista de clientes cadastrados ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.bin", "rb");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo BIN!\n");
            return;
        }

        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, file) == 1)
        {
            if (c.status == 1)
            {
                printf("ID: %d\n", c.id);
                printf("Nome: %s\n", c.nome_cliente);
                printf("Razão Social: %s\n", c.nome_razao);
                printf("Idade: %d\n", c.idade);
                printf("Endereço: %s\n", c.endereco);
                printf("CPF: %s\n", c.cpf);
                printf("CNPJ: %s\n", c.cnpj);
                printf("Email: %s\n", c.email);
                printf("Telefone: %s\n", c.telefone);
                printf("Contato: %s\n", c.nome_contato);
                printf("Status: %d\n\n", c.status);
            }
        }
        fclose(file);
        printf("=======================================\n");
    }
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *atual = lista;
        int contador_ativos = 0;

        printf("\n==== lista de clientes cadastrados ====\n");
        while (atual != NULL)
        {
            // so mostra se o cliente tiver ativo
            if (atual->dados.status == 1)
            {
                exibir_cliente(&(atual->dados)); // chama a view pra mostrar cada cliente
                contador_ativos++;
            }
            atual = atual->proximo;
        }

        if (contador_ativos == 0)
        {
            printf("+--------------------------+\n");
            printf("| nenhum cliente cadastrado! |\n");
            printf("+--------------------------+\n");
        }
        printf("=======================================\n");
    }
}
// novo: função pra mostrar SÓ os clientes inativos (status 0)
void exibir_todos_clientes_e_inativos(NoCliente *lista)
{
    NoCliente *atual = lista;
    int contador_inativos = 0; // pra contar quantos clientes achou

    printf("\n==== lista de clientes INATIVOS (deletados) ====\n");
    while (atual != NULL)
    {
        // AGORA O FILTRO SÓ MOSTRA SE O STATUS FOR 0 (INATIVO)
        if (atual->dados.status == 0)
        {
            exibir_cliente(&(atual->dados)); // chama a view pra mostrar cada cliente
            contador_inativos++;
        }

        atual = atual->proximo;
    }

    if (contador_inativos == 0)
    {
        printf("+--------------------------+\n");
        printf("| nenhum cliente inativo encontrado! |\n"); // Mensagem mais específica
        printf("+--------------------------+\n");
    }
    printf("=======================================\n");
}