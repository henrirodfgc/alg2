#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> 
#include <errno.h> 
#include <windows.h> 
#include "cliente.h"
#include "../../view/cadastro/cliente_view.h"
#include "../../controller/saida.h" 

//copia tudo de uma struct cliente pra outra de forma segura
void copiar_dados(Cliente *destino, const Cliente *origem)
{
    if (!origem || !destino) return; //se for null n funciona

    destino->id = origem->id;
    destino->idade = origem->idade;
    destino->status = origem->status; 

    //cópia segura de todas as strings
    //o -1 serve pra reservar um espaço pro terminador nulo (\0)
    //\0 serve pra indicar q a string acabou
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

//crud
//cria um novo nó e põe ele no começo da lista (create)
NoCliente *adicionar_cliente_na_lista(NoCliente *lista, Cliente novo_cliente)
{
    //verifica se existe a pasta, se não existir ele cria
    if (_mkdir("../b_output/clientes") == -1 && errno != EEXIST)
    {
        exibir_mensagem("erro ao criar pasta clientes!\n");
    }

    //salva no arquivo txt se o tipo saida for txt
    if (verificar_tipo_saida() == 1)
    {
        //cria o arquivo
        FILE *file = fopen("../b_output/clientes/cliente.txt", "a");
        //se der o erro ao abrir o arquivo
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo!\n");
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
        exibir_mensagem("arquivo salvo com sucesso!\n");
    }
    //salva no arquivo bin se o tipo saida for bin 
    else if (verificar_tipo_saida() == 2)
    {
        FILE *file = fopen("../b_output/clientes/cliente.bin", "ab");
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo!");
            return lista;
        }
        novo_cliente.status = 1;
        if (fwrite(&novo_cliente, sizeof(Cliente), 1, file) != 1)
            exibir_mensagem("erro ao escrever a struct no arquivo.\n");
        else
            exibir_mensagem("struct adicionada com sucesso ao final do arquivo.\n");
        fclose(file);
    }
    //salva no arquivo txt se o tipo saida for mem
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
    if (verificar_tipo_saida() == 1) 
    {
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r+");
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo original!\n");
            
            return 0;
        }

        FILE *temp = fopen("../b_output/clientes/temp.txt", "w+");
        if (temp == NULL)
        {
            exibir_mensagem("erro ao criar arquivo temporario!\n");
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
            exibir_mensagem("cliente com id: ");
            exibir_numero(id_busca);
            exibir_mensagem("marcado como inativo (status = 0).\n");
            return 1;
        }
        else
        {
            exibir_mensagem("cliente com id :");
            exibir_numero(id_busca);
            exibir_mensagem("nao foi encontrado\n");
            return 0;
        }
    }
    //implementação BIN
    else if (verificar_tipo_saida() == 2)
    {
            // Abrir o arquivo BINÁRIO (leitura e escrita - r+b)
    FILE *file = fopen("../b_output/clientes/cliente.bin", "r+b"); 

    if (file == NULL) {
        exibir_mensagem("Erro ao abrir o arquivo binário para atualização!\n");
        return 0;
    }

    Cliente c; // Estrutura do cliente

    // Procurar o registro
    int encontrado = 0;
    long posicao_do_registro = 0;

    // Loop que lê um registro por vez
    while (fread(&c, sizeof(Cliente), 1, file) == 1) {
        
        // Guarda a posição inicial do registro atual no arquivo.
        // O fseek anterior moveu o ponteiro, então voltamos para o início
        // do registro recém-lido, que será o ponto de escrita se precisarmos.
        posicao_do_registro = ftell(file) - sizeof(Cliente);
        
        // Verificar se é o ID buscado
        if (c.id == id_busca) {
            
            // Verifica se o cliente já está inativo
            if (c.status == 0) {
                // Não faz nada, apenas informa
                encontrado = 1; 
                break; 
            }
            
            // Se for o ID, atualiza o status para 0 (inativação lógica)
            c.status = 0; 
            encontrado = 1;
            
            // Voltar o ponteiro para o início do registro (onde estava antes do fread)
            fseek(file, posicao_do_registro, SEEK_SET);
            
            // Reescrever o registro atualizado sobre o registro antigo
            if (fwrite(&c, sizeof(Cliente), 1, file) != 1) {
                exibir_mensagem("Erro ao reescrever o registro no arquivo binário.\n");
                fclose(file);
                return 0; 
            }

            // O registro foi atualizado. Sair do loop.
            break; 
        }
    }

    //  Fechar o arquivo
    fclose(file); 

    // Retornar o resultado
    if (encontrado) {
        exibir_mensagem("cliente com id: ");
        exibir_numero(id_busca);
        exibir_mensagem("marcado como inativo (status = 0).\n");;
        return 1;
    } else {
        exibir_mensagem("cliente com id :");
        exibir_numero(id_busca);
        exibir_mensagem("nao foi encontrado\n");
        return 0;
    }
    }
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

//muda o status de 0 pra 1 (restauração)
void restaurar_cliente_por_id(NoCliente *lista, int id_busca)
{
    //implementação TXT/BIN
    if (verificar_tipo_saida() == 1 || verificar_tipo_saida() == 2)
    {
        exibir_mensagem("aviso:restauracao em arquivo.");
        return; 
    }
    
    //memoria
    Cliente *cliente_existente = buscar_cliente_qualquer_status(lista, id_busca);

    //se encontrou e ele estava inativo (status 0), reativa
    if (cliente_existente && cliente_existente->status == 0)
    {
        cliente_existente->status = 1; //seta pra ativo
    }
}

//atualiza os dados de um client q já existe pelo id
int atualizar_cliente_por_id(NoCliente *lista, int id_busca, const char *nome_cliente, int idade, const char *nome_razao, const char *cpf, const char *cnpj, const char *endereco, const char *email, const char *telefone, const char *nome_contato)
{
    Cliente *cliente_existente = buscar_cliente_por_id(lista, id_busca);

    if (cliente_existente)
    {
        //o status continua 1, a gente só atualiza os outros campos
        cliente_existente->idade = idade;

        //atualiza os campos string
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
        if (verificar_tipo_saida() == 1)
        {
            FILE *file = fopen("../b_output/clientes/cliente.txt", "r+");
            if (file==NULL)
            {
                exibir_mensagem("erro ao abrir o arquivo original!\n");
            
                return 0;
            }

            FILE *temp = fopen("../b_output/clientes/temp.txt", "w+");
            if (temp == NULL)
            {
                exibir_mensagem("erro ao criar arquivo temporario!\n");
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

            if (c.id == cliente_existente->id)
            {
                fprintf(temp,
                    "id:%d,nome_cliente:%s,nome_razao:%s,idade:%d,endereco:%s,cpf:%s,cnpj:%s,email:%s,telefone:%s,nome_contato:%s,status:%d\n",
                    cliente_existente->id,
                    cliente_existente->nome_cliente,
                    cliente_existente->nome_razao,
                    cliente_existente->idade,
                    cliente_existente->endereco,
                    cliente_existente->cpf,
                    cliente_existente->cnpj,
                    cliente_existente->email,
                    cliente_existente->telefone,
                    cliente_existente->nome_contato,
                    cliente_existente->status);

                    encontrado = 1;
            
            } else {
                fprintf(temp, "%s", linha);
             }
            
            
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
                exibir_mensagem("cliente com id: ");
                exibir_numero(id_busca);
                exibir_mensagem("nao encontrado.\n");
                return 1;
            }
            else
            {
                exibir_mensagem("cliente com id: ");
                exibir_numero(id_busca);
                exibir_mensagem("nao encontrado.\n");
                return 0;
            }


            
        }
    }
    else if (verificar_tipo_saida() == 2) {
        if (!cliente_existente) {
                exibir_mensagem("cliente com id: ");
                exibir_numero(id_busca);
                exibir_mensagem("nao encontrado na lista para atualizar.\n");
            return 0;
        }

        //Abrir o arquivo BINÁRIO (leitura e escrita - r+b)
        FILE *file = fopen("../b_output/clientes/cliente.bin", "r+b"); 

        if (file == NULL) {
            exibir_mensagem("Erro ao abrir o arquivo binário para atualização!\n");
            return 0;
        }

        Cliente c; 
        int encontrado = 0;
        long posicao_do_registro = 0;

        // Loop que lê um registro por vez para encontrar a posição
        while (fread(&c, sizeof(Cliente), 1, file) == 1) {
            
            // Guarda a posição inicial do registro
            posicao_do_registro = ftell(file) - sizeof(Cliente);
            
            // Verificar se é o ID que queremos atualizar
            if (c.id == id_busca) { 
                encontrado = 1;
                
                // Voltar o ponteiro para o início do registro
                fseek(file, posicao_do_registro, SEEK_SET);
                
                // Reescrever o registro atualizado (da memória) sobre o registro antigo
                
                if (fwrite(cliente_existente, sizeof(Cliente), 1, file) != 1) {
                    exibir_mensagem("Erro ao reescrever o registro atualizado no arquivo binário.\n");
                    fclose(file);
                    return 0; 
                }

                // O registro foi atualizado. Sair do loop.
                break; 
            }
        }

        fclose(file); 

        if (encontrado) {
                exibir_mensagem("cliente com id: ");
                exibir_numero(id_busca);
                exibir_mensagem("atualizado com sucesso no arquivo binario.\n");
            return 1;
        } else {
                exibir_mensagem("cliente com id: ");
                exibir_numero(id_busca);
                exibir_mensagem("nao encontrado no arquivo para atualizacao.\n");
            return 0;
        }
    }
    
    
    // garantindo que o retorno seja 1 (sucesso) após a operação.
    return 1;




            
}

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
    //logica para TXT
    if (verificar_tipo_saida() == 1)
    {
        exibir_mensagem("\n==== lista de clientes cadastrados ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r");
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo txt!\n");
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
        exibir_mensagem("=======================================\n");
    }
    //Logica para BIN
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem("\n==== lista de clientes cadastrados ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.bin", "rb");
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo bin!\n");
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
        exibir_mensagem("=======================================\n");
    }
    //MEMORIA
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *atual = lista;
        int contador_ativos = 0;

        exibir_mensagem("\n==== lista de clientes cadastrados ====\n");
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
            exibir_mensagem("+--------------------------+\n");
            exibir_mensagem("| nenhum cliente cadastrado! |\n");
            exibir_mensagem("+--------------------------+\n");
        }
        exibir_mensagem("=======================================\n");
    }
}

//função pra mostrar só os clientes inativos (status 0)
void exibir_todos_clientes_e_inativos(NoCliente *lista)
{
    //logica para TXT
    if (verificar_tipo_saida() == 1)
    {
        exibir_mensagem("\n==== lista de clientes inativos (deletados) ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.txt", "r");
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo txt!\n");
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
        exibir_mensagem("=======================================\n");
    }
    //logica para BIN
    else if (verificar_tipo_saida() == 2)
    {
        exibir_mensagem("\n==== lista de clientes inativos (deletados) ====\n");
        FILE *file = fopen("../b_output/clientes/cliente.bin", "rb");
        if (file == NULL)
        {
            exibir_mensagem("erro ao abrir o arquivo bin!\n");
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
        exibir_mensagem("=======================================\n");
    }
    //sua logica para MEMORIA
    else if (verificar_tipo_saida() == 3)
    {
        NoCliente *atual = lista;
        int contador_inativos = 0; //pra contar quantos clientes achou

        exibir_mensagem("\n==== lista de clientes inativos (deletados) ====\n");
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
            exibir_mensagem("+--------------------------+\n");
            exibir_mensagem("| nenhum cliente inativo encontrado! |\n"); 
            exibir_mensagem("+--------------------------+\n");
        }
        exibir_mensagem("=======================================\n");
    }
}

//novo: função que carrega os dados do arquivo/binario/memoria para a lista (logica critica de inicializacao)
NoCliente* carregar_clientes(NoCliente* lista) {
    //se a lista ja tem dados (se nao eh a primeira vez q chama) sai fora
    if (lista != NULL) return lista; 
    
    int tipo_saida = verificar_tipo_saida();
    
    //logica TXT
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
    //logica BIN
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