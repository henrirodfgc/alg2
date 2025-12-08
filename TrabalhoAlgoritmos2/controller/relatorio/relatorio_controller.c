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

void pegar_data_hora(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%d as %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

void escrever_cabecalho_html(FILE* f, char* titulo) {
    fprintf(f, "<!DOCTYPE html><html><head><meta charset='UTF-8'>");
    fprintf(f, "<title>%s</title>", titulo);
    fprintf(f, "<style>");
    fprintf(f, "body { font-family: Arial, sans-serif; background-color: #f4f4f9; color: #333; margin: 20px; }");
    fprintf(f, "h1 { color: #0056b3; border-bottom: 2px solid #0056b3; padding-bottom: 10px; }");
    fprintf(f, "table { width: 100%%; border-collapse: collapse; margin-top: 20px; box-shadow: 0 0 20px rgba(0,0,0,0.1); }");
    fprintf(f, "th, td { padding: 12px 15px; text-align: left; border-bottom: 1px solid #ddd; }");
    fprintf(f, "th { background-color: #0056b3; color: #ffffff; }");
    fprintf(f, "tr:hover { background-color: #f1f1f1; }");
    fprintf(f, ".footer { margin-top: 30px; font-size: 0.8em; color: #777; text-align: right; }");
    fprintf(f, "</style></head><body>");
    
    char data[50];
    pegar_data_hora(data);
    fprintf(f, "<h1>%s</h1>", titulo);
    fprintf(f, "<p>relatorio gerado automaticamente pelo sistema de gestao em: %s</p>", data);
}

void gerar_relatorio_clientes_html() {
    char* caminho = "b_output/relatorios/clientes.html";
    FILE *f = fopen(caminho, "w");
    
    if (!f) {
        caminho = "../b_output/relatorios/clientes.html";
        f = fopen(caminho, "w");
    }
    
    if (!f) {
        exibir_mensagem_relatorio("erro critico: nao foi possivel criar o arquivo html. verifique se a pasta 'b_output/relatorios' existe.");
        return;
    }

    escrever_cabecalho_html(f, "relatorio geral de clientes");

    fprintf(f, "<table>");
    fprintf(f, "<thead><tr><th>id</th><th>nome</th><th>cpf/cnpj</th><th>telefone</th><th>status</th></tr></thead>");
    fprintf(f, "<tbody>");

    listaClientes = carregar_clientes(listaClientes);
    NoCliente *atual = listaClientes;
    
    while (atual != NULL) {
        char* cor = (atual->dados.status == 1) ? "#000" : "#ff0000";
        char* status_txt = (atual->dados.status == 1) ? "ativo" : "inativo";
        
        fprintf(f, "<tr style='color: %s'>", cor);
        fprintf(f, "<td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td>", 
                atual->dados.id, atual->dados.nome_cliente, atual->dados.cpf, 
                atual->dados.telefone, status_txt);
        fprintf(f, "</tr>");
        atual = atual->proximo;
    }

    fprintf(f, "</tbody></table>");
    fprintf(f, "<div class='footer'>sistema de eventos v1.0</div>");
    fprintf(f, "</body></html>");
    fclose(f);

    exibir_mensagem_relatorio(">> relatorio gerado com sucesso!");
    
    char comando[300];
    sprintf(comando, "start \"\" \"%s\"", caminho);
    system(comando); 
}

void gerar_relatorio_eventos_html() {
    char* caminho = "b_output/relatorios/eventos.html";
    FILE *f = fopen(caminho, "w");
    
    if (!f) {
        caminho = "../b_output/relatorios/eventos.html";
        f = fopen(caminho, "w");
    }
    
    if (!f) {
        exibir_mensagem_relatorio("erro critico: nao foi possivel criar o arquivo html.");
        return;
    }

    escrever_cabecalho_html(f, "relatorio de eventos e orcamentos");

    fprintf(f, "<table>");
    fprintf(f, "<thead><tr><th>cod</th><th>evento</th><th>cliente (id)</th><th>data</th><th>convidados</th><th>valor total</th><th>status</th></tr></thead>");
    fprintf(f, "<tbody>");

    listaEventos = carregar_eventos(listaEventos);
    NoEvento *atual = listaEventos;
    
    while (atual != NULL) {
        char* status_str = (atual->dados.status == 1) ? "<b>aprovado</b>" : "orcamento";
        char* cor_linha = (atual->dados.status == 1) ? "#d4edda" : "#fff3cd";

        fprintf(f, "<tr style='background-color: %s'>", cor_linha);
        fprintf(f, "<td>%d</td><td>%s</td><td>%d</td><td>%s</td><td>%d</td><td>r$ %.2f</td><td>%s</td>", 
                atual->dados.codigo, atual->dados.nome_evento, atual->dados.codigo_cliente,
                atual->dados.data_inicio, atual->dados.quantidade_convidados,
                atual->dados.valor_total, status_str);
        fprintf(f, "</tr>");
        atual = atual->proximo;
    }

    fprintf(f, "</tbody></table>");
    fprintf(f, "</body></html>");
    fclose(f);

    exibir_mensagem_relatorio(">> relatorio gerado com sucesso!");
    
    char comando[300];
    sprintf(comando, "start \"\" \"%s\"", caminho);
    system(comando);
}

void iniciar_modulo_relatorios() {
    int op;
    do {
        op = exibir_menu_relatorios();
        switch(op) {
            case 1: gerar_relatorio_clientes_html(); break;
            case 2: gerar_relatorio_eventos_html(); break;
            case 0: exibir_mensagem_relatorio("voltando..."); break;
            default: exibir_mensagem_relatorio("opcao invalida");
        }
        if(op!=0) pausar_tela_relatorio();
    } while(op != 0);
}