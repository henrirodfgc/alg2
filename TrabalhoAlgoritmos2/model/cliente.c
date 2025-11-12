#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> //pra criar pasta
#include <errno.h> //pra checar erro de pasta
#include <windows.h> //pra windows.h
#include "cliente.h"
#include "../view/cliente_view.h"
#include "../controller/saida.h" //pra checar o modo de saida

//--- funcoes auxiliares ---
//copia tudo de uma struct cliente pra outra de forma segura
void copiar_dados(Cliente *destino, const Cliente *origem)
{
    if (!origem || !destino) return; //se for null sai fora pra n dar bo

    destino->id = origem->id;
    destino->idade = origem->idade;
    destino->status = origem->status; //agora copia o status tbm!

    //cópia segura de todas as strings (strncpy é vida)
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

//procura um client pelo id e retorna o ponteiro pra struct cliente independente do status
//essa é auxiliar pra exclusão/restauração e nao é exportada no .h
Cliente *buscar_cliente_qualquer_status(NoCliente *lista, int id_busca)
{
    NoCliente *atual = lista;
    while (atual != NULL)
    {
        if (atual->dados.id == id_busca)
        {
            return &(atual->dados); //achou, não importa o status
        }
        atual = atual->proximo;
    }
    return NULL; //não achou
}

//--- funcoes de manipulacao de lista ligada (crud) ---
//cria um novo nó e põe ele no começo da lista (create)
NoCliente *adicionar_cliente_na_lista(NoCliente *lista, Cliente novo_cliente)
{
    //verifica se existe a pasta, se não existir ele cria (logica do colega)
    if (_mkdir("../b_output/clientes") == -1 && errno != EEXIST)
    {
        printf("erro ao criar pasta clientes!\n");
    }

    //salva no arquivo txt se o tipo saida for txt (logica do colega)
    if (verificar_tipo_saida() == 1)
    {
        //cria o arquivo
        FILE *file = fopen("../b_output/clientes/cliente.txt", "a");
        //se der o erro ao abrir o arquivo
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo!\n");
            return lista;
        }
        //define cliente ativo
        novo_cliente.status = 1;

        //escreve struct no arquivo
        fprintf(file, "id:%d,nome_cliente:%s,nome_razao:%s,idade:%d,endereco:%s,cpf:%s,cnpj:%s,email:%s,telefone:%s,nome_contato:%s,status:%d\n",
                novo_cliente.id, novo_cliente.nome_cliente, novo_cliente.nome_razao,
                novo_cliente.idade, novo_cliente.endereco, novo_cliente.cpf, novo_cliente.cnpj,
                novo_cliente.email, novo_cliente.telefone, novo_cliente.nome_contato, novo_cliente.status);
        //fecha o arquivo
        fclose(file);
        printf("arquivo salvo com sucesso!\n");
    }
    //salva no arquivo bin se o tipo saida for bin (logica do colega)
    else if (verificar_tipo_saida() == 2)
    {
        FILE *file = fopen("../b_output/clientes/cliente.bin", "ab");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo!");
            return lista;
        }
        novo_cliente.status = 1;
        if (fwrite(&novo_cliente, sizeof(Cliente), 1, file) != 1)
            printf("erro ao escrever a struct no arquivo.\n");
        else
            printf("struct adicionada com sucesso ao final do arquivo.\n");
        fclose(file);
    }
    //salva no arquivo txt se o tipo saida for mem (sua parte)
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *novo_no = (NoCliente *)malloc(sizeof(NoCliente));
        if (novo_no == NULL)
        {
            exibir_mensagem("erro:falha ao alocar nó da lista");
            return lista;
        }
        novo_cliente.status = 1;
        copiar_dados(&(novo_no->dados), &novo_cliente);
        novo_no->proximo = lista;
        return novo_no;
    }

    return lista;
}

//procura um client pelo id e retorna o ponteiro pra struct cliente
//agora só retorna se o status for 1 (ativo)
Cliente *buscar_cliente_por_id(NoCliente *lista, int id_busca)
{
    NoCliente *atual = lista;
    //percorre a lista
    while (atual != NULL)
    {
        //checa se o id bate e se o status é 1
        if (atual->dados.id == id_busca && atual->dados.status == 1)
        {
            return &(atual->dados); //achou e tá ativo
        }
        atual = atual->proximo;
    }
    return NULL; //não achou ou tá inativo
}

//muda o status pra 0 (soft delete)
int deletar_cliente_por_id_logico(NoCliente *lista, int id_busca)
{
    //implementação do colega para TXT
    if (verificar_tipo_saida() == 1) //lógica de deleção txt complexa do colega
    {
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r+");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo original!\n");
            
            return 0;
        }

        FILE *temp = fopen("../b_output/clientes/temp.txt", "w+");
        if (temp == NULL)
        {
            printf("erro ao criar arquivo temporario!\n");
            fclose(file);
            return 0;
        }

        Cliente c;
        char linha[2048];
        int encontrado = 0;

        while (fgets(linha, sizeof(linha), file))
        {
            //lê os campos
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
                c.status = 0; //marca como inativo
                encontrado = 1;
            }
            //reescreve a linha (atualizada ou não)
            fprintf(temp,
                    "id:%d,nome_cliente:%s,nome_razao:%s,idade:%d,endereco:%s,cpf:%s,cnpj:%s,email:%s,telefone:%s,nome_contato:%s,status:%d\n",
                    c.id, c.nome_cliente, c.nome_razao, c.idade, c.endereco,
                    c.cpf, c.cnpj, c.email, c.telefone, c.nome_contato, c.status);
        }

        fclose(file);
        fclose(temp);
       
        //substitui o original pelo temporário
        if (remove("../b_output/clientes/cliente.txt") != 0)
        {
            perror("erro ao remover o arquivo original");
            return 0;
        }

        if (rename("../b_output/clientes/temp.txt", "../b_output/clientes/cliente.txt") != 0)
        {
            perror("erro ao renomear o arquivo temporario");
            return 0;
        }

        if (encontrado)
        {
            printf("cliente com id %d marcado como inativo (status = 0).\n", id_busca);
            return 1;
        }
        else
        {
            printf("cliente com id %d nao encontrado.\n", id_busca);
            return 0;
        }
    }
    //implementação do colega para BIN
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem("aviso:delecao binaria. responsa do colega.");
        return 0; //aqui deveria ter a implementacao dele
    }
    //sua versão para memoria (modo 3)
    else if (verificar_tipo_saida() == 3)
    {
        //busca ele com qualquer status para checar se existe
        Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca);
        
        //se a busca encontrar e ele estiver ativo (status 1), muda o status
        if (cliente_existente && cliente_existente->status == 1)
        {
            cliente_existente->status = 0; //seta pra inativo/deletado
            return 1; //sucesso
        }
        //se nao achou ou ja estava inativo, retorna falha
        return 0;
    }
    return 0;
}

//novo: muda o status de 0 pra 1 (restauração)
void restaurar_cliente_por_id(NoCliente *lista, int id_busca)
{
    //implementação do colega para TXT/BIN
    if (verificar_tipo_saida() == 1 || verificar_tipo_saida() == 2)
    {
        exibir_mensagem("aviso:restauracao em arquivo. responsa do colega.");
        return; //aqui deveria ter a implementacao dele
    }
    
    //sua versão para memoria (modo 3)
    Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca);

    //se encontrou e ele estava inativo (status 0), reativa
    if (cliente_existente && cliente_existente->status == 0)
    {
        cliente_existente->status = 1; //seta pra ativo
    }
}

//atualiza os dados de um client q já existe pelo id
void atualizar_cliente_por_id(NoCliente *lista, int id_busca, const char *nome_cliente, int idade, const char *nome_razao, const char *cpf, const char *cnpj, const char *endereco, const char *email, const char *telefone, const char *nome_contato)
{
    Cliente *cliente_existente = buscar_cliente_por_id(lista, id_busca);

    if (cliente_existente)
    {
        //o status continua 1, a gente só atualiza os outros campos
        cliente_existente->idade = idade;

        //atualiza os campos string com cópia segura (strncpy)
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

        //avisa se nao for modo memoria
        if (verificar_tipo_saida() != 3)
        {
            exibir_mensagem("aviso:atualizacao em arquivo. responsa do colega.");
        }
    }
}

//função essencial: libera a memória
void desalocar_lista_clientes(NoCliente *lista)
{
    if (verificar_tipo_saida() != 3) return; //so desaloca se for modo memoria

    NoCliente *atual = lista;
    NoCliente *proximo_no;
    //roda a lista toda dando free em cada nó
    while (atual != NULL)
    {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
}

//função pra mostrar todos (read all)
//so mostra quem tem status 1
void exibir_todos_clientes(NoCliente *lista)
{
    //Logica para TXT (do colega)
    if (verificar_tipo_saida() == 1)
    {
        printf("\n==== lista de clientes cadastrados ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo txt!\n");
            return;
        }
        Cliente c;
        char linha[2048]; //linha completa do arquivo

        while (fgets(linha, sizeof(linha), file))
        {
            //lê e extrai os valores da linha conforme os rótulos
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

            if (c.status == 1)
            {
                //exibe formatado
                exibir_cliente(&c); //chama a view para exibir
            }
        }
        fclose(file);
        printf("=======================================\n");
    }
    //Logica para BIN (do colega)
    else if (verificar_tipo_saida() == 2)
    {
        printf("\n==== lista de clientes cadastrados ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.bin", "rb");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo bin!\n");
            return;
        }

        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, file) == 1)
        {
            if (c.status == 1)
            {
                exibir_cliente(&c);
            }
        }
        fclose(file);
        printf("=======================================\n");
    }
    //sua logica para MEMORIA
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *atual = lista;
        int contador_ativos = 0;

        printf("\n==== lista de clientes cadastrados ====\n");
        while (atual != NULL)
        {
            //so mostra se o cliente tiver ativo
            if (atual->dados.status == 1)
            {
                exibir_cliente(&(atual->dados)); //chama a view pra mostrar cada cliente
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

//novo: função pra mostrar só os clientes inativos (status 0)
void exibir_todos_clientes_e_inativos(NoCliente *lista)
{
    //Logica para TXT (do colega)
    if (verificar_tipo_saida() == 1)
    {
        printf("\n==== lista de clientes inativos (deletados) ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo txt!\n");
            return;
        }
        Cliente c;
        char linha[2048];

        while (fgets(linha, sizeof(linha), file))
        {
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

            if (c.status == 0)
            {
                exibir_cliente(&c);
            }
        }
        fclose(file);
        printf("=======================================\n");
    }
    //Logica para BIN (do colega)
    else if (verificar_tipo_saida() == 2)
    {
        printf("\n==== lista de clientes inativos (deletados) ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.bin", "rb");
        if (file == NULL)
        {
            printf("erro ao abrir o arquivo bin!\n");
            return;
        }

        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, file) == 1)
        {
            if (c.status == 0)
            {
                exibir_cliente(&c);
            }
        }
        fclose(file);
        printf("=======================================\n");
    }
    //sua logica para MEMORIA
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *atual = lista;
        int contador_inativos = 0; //pra contar quantos clientes achou

        printf("\n==== lista de clientes inativos (deletados) ====\n");
        while (atual != NULL)
        {
            //agora o filtro só mostra se o status for 0 (inativo)
            if (atual->dados.status == 0)
            {
                exibir_cliente(&(atual->dados)); //chama a view pra mostrar cada cliente
                contador_inativos++;
            }

            atual = atual->proximo;
        }

        if (contador_inativos == 0)
        {
            printf("+--------------------------+\n");
            printf("| nenhum cliente inativo encontrado! |\n"); //mensagem mais específica
            printf("+--------------------------+\n");
        }
        printf("=======================================\n");
    }
}

//novo: função que carrega os dados do arquivo/binario/memoria para a lista (logica critica de inicializacao)
NoCliente* carregar_clientes(NoCliente* lista) {
    //se a lista ja tem dados (se nao eh a primeira vez q chama) sai fora
    if (lista != NULL) return lista; 
    
    int tipo_saida = verificar_tipo_saida();
    
    //logica do colega para carregar TXT
    if (tipo_saida == 1) { 
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r");
        if (file == NULL) return lista; //se o arquivo nao existe, retorna lista vazia

        Cliente c;
        char linha[2048]; //buffer pra ler a linha

        while (fgets(linha, sizeof(linha), file)) {
            //tenta extrair os dados da linha
            if (sscanf(linha,
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
                   &c.status) == 11) { //se leu 11 campos, deu bom
                
                //cria um novo no na lista
                NoCliente *novo_no = (NoCliente*) malloc(sizeof(NoCliente));
                if (novo_no != NULL) {
                    copiar_dados(&(novo_no->dados), &c);
                    novo_no->proximo = lista;
                    lista = novo_no; //a lista agora aponta pro novo no
                }
            }
        }
        fclose(file);
    } 
    //logica do colega para carregar BIN
    else if (tipo_saida == 2) { 
        FILE *file = fopen("../b_output/clientes/cliente.bin", "rb");
        if (file == NULL) return lista; //se o arquivo nao existe, retorna lista vazia
        
        Cliente c;
        
        //le struct por struct do binario
        while (fread(&c, sizeof(Cliente), 1, file) == 1) {
             //cria um novo no na lista
            NoCliente *novo_no = (NoCliente*) malloc(sizeof(NoCliente));
            if (novo_no != NULL) {
                copiar_dados(&(novo_no->dados), &c);
                novo_no->proximo = lista;
                lista = novo_no; //a lista agora aponta pro novo no
            }
        }
        fclose(file);
    }
    
    return lista; //retorna a lista carregada
}