#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "relatorio_controller.h"
#include "../../view/relatorio/relatorio_view.h"
#include "../../model/cadastro/cliente.h"
#include "../../model/orcamento/evento.h"
#include "../../model/transacao/caixa.h"

extern NoCliente *listaClientes;
extern NoCliente* carregar_clientes(NoCliente* lista);
extern NoEvento *listaEventos;
extern NoEvento* carregar_eventos(NoEvento* lista);

long data_para_num(const char* data) {
    int d, m, a;
    if (sscanf(data, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    return (a * 10000) + (m * 100) + d;
}

void pegar_data_hora(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

void escrever_cabecalho_html(FILE* f, char* titulo) {
    char data[30];
    pegar_data_hora(data);
    fprintf(f, "<html><head><title>%s</title>", titulo);
    fprintf(f, "<style>body{font-family:sans-serif;} table{width:100%%;border-collapse:collapse;} th,td{border:1px solid #ddd;padding:8px;} th{background-color:#4CAF50;color:white;} tr:nth-child(even){background-color:#f2f2f2;}</style>");
    fprintf(f, "</head><body>");
    fprintf(f, "<h1>%s</h1><p>Gerado em: %s</p>", titulo, data);
}

void ordenar_lista_clientes(NoCliente* lista) {
    if (!lista) return;
    int trocou;
    NoCliente *ptr1;
    NoCliente *lptr = NULL;

    do {
        trocou = 0;
        ptr1 = lista;

        while (ptr1->proximo != lptr) {
            if (strcmp(ptr1->dados.nome_cliente, ptr1->proximo->dados.nome_cliente) > 0) {
                Cliente temp = ptr1->dados;
                ptr1->dados = ptr1->proximo->dados;
                ptr1->proximo->dados = temp;
                trocou = 1;
            }
            ptr1 = ptr1->proximo;
        }
        lptr = ptr1;
    } while (trocou);
}



void gerar_relatorio_clientes_html() {

    char caminho_final[200] = "b_output/relatorios/clientes.html";
    FILE *f = fopen(caminho_final, "w");
    

    if (!f) {
        strcpy(caminho_final, "../b_output/relatorios/clientes.html");
        f = fopen(caminho_final, "w");
    }
    
    if (!f) {
        exibir_mensagem_relatorio("Erro critico: nao foi possivel criar o arquivo HTML.");
        return;
    }

    listaClientes = carregar_clientes(listaClientes);

    int ordenar;
    printf("Deseja ordenar por nome alfabetico? (1-Sim / 0-Nao): ");
    scanf("%d", &ordenar);
    if(ordenar == 1) {
        ordenar_lista_clientes(listaClientes);
    }

    escrever_cabecalho_html(f, "Relatorio de Clientes");
    fprintf(f, "<table><tr><th>ID</th><th>Nome/Razao</th><th>CPF/CNPJ</th><th>Telefone</th><th>Status</th></tr>");

    NoCliente *atual = listaClientes;
    while(atual != NULL) {
        if(atual->dados.status == 1) { 
            fprintf(f, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>", 
                atual->dados.id, atual->dados.nome_cliente, 
                (strlen(atual->dados.cpf)>0 ? atual->dados.cpf : atual->dados.cnpj), 
                atual->dados.telefone, "Ativo");
        }
        atual = atual->proximo;
    }
    fprintf(f, "</table></body></html>");
    fclose(f);
    
    char comando[300];
    #ifdef _WIN32
        sprintf(comando, "start %s", caminho_final);
    #else
        sprintf(comando, "xdg-open %s", caminho_final);
    #endif
    system(comando);
    
    char msg[300];
    sprintf(msg, "Relatorio gerado em: %s", caminho_final);
    exibir_mensagem_relatorio(msg);
}

void gerar_relatorio_eventos_html(int filtro_status) {

    char caminho_final[200] = "b_output/relatorios/eventos.html";
    FILE *f = fopen(caminho_final, "w");
    
    if (!f) {
        strcpy(caminho_final, "../b_output/relatorios/eventos.html");
        f = fopen(caminho_final, "w");
    }

    if (!f) {
        exibir_mensagem_relatorio("Erro critico: nao foi possivel criar o arquivo HTML de eventos.");
        return;
    }

    listaEventos = carregar_eventos(listaEventos);
    
    int filtrar_data = 0;
    long data_ini_num = 0, data_fim_num = 0;
    
    printf("Filtrar por periodo de data? (1-Sim / 0-Nao): ");
    scanf("%d", &filtrar_data);
    
    if (filtrar_data == 1) {
        char di[12], df[12];
        printf("Data Inicial (dd/mm/aaaa): "); scanf("%s", di);
        printf("Data Final (dd/mm/aaaa): "); scanf("%s", df);
        data_ini_num = data_para_num(di);
        data_fim_num = data_para_num(df);
    }

    escrever_cabecalho_html(f, "Relatorio de Eventos");
    fprintf(f, "<table><tr><th>Cod</th><th>Evento</th><th>Cliente</th><th>Inicio</th><th>Fim</th><th>Valor</th><th>Status</th></tr>");

    NoEvento *atual = listaEventos;
    while(atual != NULL) {
        int status_ok = (filtro_status == -1 || atual->dados.status == filtro_status);
        
        int data_ok = 1;
        if(filtrar_data) {
            long data_evt = data_para_num(atual->dados.data_inicio);
            if (data_evt < data_ini_num || data_evt > data_fim_num) {
                data_ok = 0;
            }
        }

        if(status_ok && data_ok) {
            char* st = "Orcamento";
            if(atual->dados.status == 1) st = "<span style='color:green'>Aprovado</span>";
            else if(atual->dados.status == 2) st = "<span style='color:blue'>Finalizado</span>";
            else if(atual->dados.status == 0) st = "Orcamento";
            
            fprintf(f, "<tr><td>%d</td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.2f</td><td>%s</td></tr>",
                atual->dados.codigo, atual->dados.nome_evento, atual->dados.codigo_cliente,
                atual->dados.data_inicio, atual->dados.data_fim, atual->dados.valor_total, st);
        }
        atual = atual->proximo;
    }
    fprintf(f, "</table></body></html>");
    fclose(f);
    
    char comando[300];
    #ifdef _WIN32
        sprintf(comando, "start %s", caminho_final);
    #else
        sprintf(comando, "xdg-open %s", caminho_final);
    #endif
    system(comando);
}

void gerar_relatorio_clientes_csv() {
    char caminho_final[200] = "b_output/relatorios/clientes.csv";
    FILE *f = fopen(caminho_final, "w");
    
    if (!f) {
        strcpy(caminho_final, "../b_output/relatorios/clientes.csv");
        f = fopen(caminho_final, "w");
    }
    
    if (!f) { exibir_mensagem_relatorio("erro ao criar arquivo csv."); return; }

    fprintf(f, "ID;Nome/Razao;CPF/CNPJ;Telefone;Email;Status\n");
    listaClientes = carregar_clientes(listaClientes);
    NoCliente *atual = listaClientes;
    
    while (atual != NULL) {
        if (atual->dados.status == 1) {
            fprintf(f, "%d;%s;%s;%s;%s;%s\n", 
                    atual->dados.id, atual->dados.nome_cliente, 
                    (strlen(atual->dados.cpf) > 0 ? atual->dados.cpf : atual->dados.cnpj), 
                    atual->dados.telefone, atual->dados.email, "Ativo");
        }
        atual = atual->proximo;
    }
    fclose(f);
    char msg[300];
    sprintf(msg, "CSV gerado em: %s", caminho_final);
    exibir_mensagem_relatorio(msg);
}

void gerar_relatorio_eventos_csv(int filtro_status) {
    char caminho_final[200] = "b_output/relatorios/eventos.csv";
    FILE *f = fopen(caminho_final, "w");
    
    if (!f) {
        strcpy(caminho_final, "../b_output/relatorios/eventos.csv");
        f = fopen(caminho_final, "w");
    }
    
    if (!f) return;

    fprintf(f, "Codigo;Evento;ID Cliente;Data Inicio;Data Fim;Convidados;Valor Total;Status\n");
    listaEventos = carregar_eventos(listaEventos);
    NoEvento *atual = listaEventos;
    
    while (atual != NULL) {
        if (filtro_status == -1 || atual->dados.status == filtro_status) {
            char* status_str = (atual->dados.status == 1 ? "Aprovado" : (atual->dados.status == 2 ? "Finalizado" : "Orcamento"));
            fprintf(f, "%d;%s;%d;%s;%s;%d;%.2f;%s\n", 
                    atual->dados.codigo, atual->dados.nome_evento, atual->dados.codigo_cliente,
                    atual->dados.data_inicio, atual->dados.data_fim,
                    atual->dados.quantidade_convidados, atual->dados.valor_total, status_str);
        }
        atual = atual->proximo;
    }
    fclose(f);
    char msg[300];
    sprintf(msg, "CSV gerado em: %s", caminho_final);
    exibir_mensagem_relatorio(msg);
}

void iniciar_modulo_relatorios() {
    int op;
    do {
        op = exibir_menu_relatorios(); 
        switch(op) {
            case 1: gerar_relatorio_clientes_html(); break;
            case 2: gerar_relatorio_clientes_csv(); break;
            case 3: {
                int st;
                ler_filtro_na_view("filtrar status? (-1=todos, 0=orc, 1=aprov, 2=fim): ");
                scanf("%d", &st);
                gerar_relatorio_eventos_html(st); 
                break;
            }
            case 4: {
                int st;
                ler_filtro_na_view("filtrar status? (-1=todos, 0=orc, 1=aprov, 2=fim): ");
                scanf("%d", &st);
                gerar_relatorio_eventos_csv(st); 
                break;
            }
            case 0: exibir_mensagem_relatorio("voltando..."); break;
            default: exibir_mensagem_relatorio("opcao invalida");
        }
        if(op!=0) pausar_tela_relatorio();
    } while(op != 0);
}