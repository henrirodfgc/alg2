#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "relatorio_controller.h"
#include "../../view/relatorio/relatorio_view.h"
#include "../../model/cadastro/cliente.h"
#include "../../model/orcamento/evento.h"
#include "../../model/cadastro/recursos.h"
#include "../../model/transacao/caixa.h"
#include "../../model/transacao/contas_pagar.h"
#include "../../model/transacao/contas_receber.h"
#include "../../model/orcamento/item_orcamento.h"

extern NoCliente *listaClientes;
extern NoCliente* carregar_clientes(NoCliente* lista);

extern NoEvento *listaEventos;
extern NoEvento* carregar_eventos(NoEvento* lista);

extern NoRecurso *listaRecursos;
extern NoRecurso* carregar_recursos(NoRecurso* lista);

extern NoContaReceber *listaContasReceber;
extern NoContaReceber* carregar_contas_receber(NoContaReceber* lista);

extern NoContaPagar *listaContasPagar;
extern NoContaPagar* carregar_contas_pagar(NoContaPagar* lista);

extern NoCaixa *listaCaixa;
extern NoCaixa* carregar_extrato_caixa(NoCaixa* lista);

extern NoItemOrcamento *listaItensOrcamento;
extern NoItemOrcamento* carregar_itens_orcamento(NoItemOrcamento* lista);


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
    fprintf(f, "<style>body{font-family:sans-serif;} table{width:100%%;border-collapse:collapse;} th,td{border:1px solid #ddd;padding:8px;} th{background-color:#4CAF50;color:white;} tr:nth-child(even){background-color:#f2f2f2;} .entrada{color:green;} .saida{color:red;}</style>");
    fprintf(f, "</head><body>");
    fprintf(f, "<h1>%s</h1><p>Gerado em: %s</p>", titulo, data);
}

void abrir_arquivo_html(char* caminho) {
    char comando[300];
    #ifdef _WIN32
        sprintf(comando, "start %s", caminho);
    #else
        sprintf(comando, "xdg-open %s", caminho);
    #endif
    system(comando);
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
    if (!f) f = fopen("../b_output/relatorios/clientes.html", "w");
    if (!f) { exibir_mensagem_relatorio("Erro critico: nao foi possivel criar HTML."); return; }

    listaClientes = carregar_clientes(listaClientes);
    
    int ordenar;
    printf("Ordenar por nome? (1-Sim / 0-Nao): ");
    scanf("%d", &ordenar);
    if(ordenar == 1) ordenar_lista_clientes(listaClientes);

    escrever_cabecalho_html(f, "Relatorio de Clientes");
    fprintf(f, "<table><tr><th>ID</th><th>Nome/Razao</th><th>CPF/CNPJ</th><th>Telefone</th><th>Email</th></tr>");

    NoCliente *atual = listaClientes;
    while(atual != NULL) {
        if(atual->dados.status == 1) { 
            fprintf(f, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>", 
                atual->dados.id, atual->dados.nome_cliente, 
                (strlen(atual->dados.cpf)>0 ? atual->dados.cpf : atual->dados.cnpj), 
                atual->dados.telefone, atual->dados.email);
        }
        atual = atual->proximo;
    }
    fprintf(f, "</table></body></html>");
    fclose(f);
    abrir_arquivo_html(caminho_final);
}

void gerar_relatorio_eventos_html(int filtro_status) {
    char caminho_final[200] = "b_output/relatorios/eventos.html";
    FILE *f = fopen(caminho_final, "w");
    if (!f) f = fopen("../b_output/relatorios/eventos.html", "w");
    if (!f) return;

    listaEventos = carregar_eventos(listaEventos);
    
    int filtrar_data = 0;
    long data_ini_num = 0, data_fim_num = 0;
    printf("Filtrar por periodo? (1-Sim / 0-Nao): ");
    scanf("%d", &filtrar_data);
    if (filtrar_data == 1) {
        char di[12], df[12];
        printf("Data Ini: "); scanf("%s", di);
        printf("Data Fim: "); scanf("%s", df);
        data_ini_num = data_para_num(di);
        data_fim_num = data_para_num(df);
    }

    escrever_cabecalho_html(f, "Relatorio de Eventos");
    fprintf(f, "<table><tr><th>Cod</th><th>Evento</th><th>Cliente ID</th><th>Inicio</th><th>Fim</th><th>Valor</th><th>Status</th></tr>");

    NoEvento *atual = listaEventos;
    while(atual != NULL) {
        int status_ok = (filtro_status == -1 || atual->dados.status == filtro_status);
        int data_ok = 1;
        if(filtrar_data) {
            long data_evt = data_para_num(atual->dados.data_inicio);
            if (data_evt < data_ini_num || data_evt > data_fim_num) data_ok = 0;
        }

        if(status_ok && data_ok && atual->dados.status != 3) { 
            char* st = "Orcamento";
            if(atual->dados.status == 1) st = "<b style='color:green'>Aprovado</b>";
            else if(atual->dados.status == 2) st = "<b style='color:blue'>Finalizado</b>";
            
            fprintf(f, "<tr><td>%d</td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>R$ %.2f</td><td>%s</td></tr>",
                atual->dados.codigo, atual->dados.nome_evento, atual->dados.codigo_cliente,
                atual->dados.data_inicio, atual->dados.data_fim, atual->dados.valor_total, st);
        }
        atual = atual->proximo;
    }
    fprintf(f, "</table></body></html>");
    fclose(f);
    abrir_arquivo_html(caminho_final);
}

void gerar_relatorio_equipamentos_html() {
    char caminho_final[200] = "b_output/relatorios/equipamentos.html";
    FILE *f = fopen(caminho_final, "w");
    if (!f) f = fopen("../b_output/relatorios/equipamentos.html", "w");
    if (!f) return;

    listaRecursos = carregar_recursos(listaRecursos);

    escrever_cabecalho_html(f, "Listagem de Recursos e Equipamentos");
    fprintf(f, "<table><tr><th>Cod</th><th>Descricao</th><th>Categoria</th><th>Estoque</th><th>Custo</th><th>Locacao Diaria</th></tr>");

    NoRecurso *atual = listaRecursos;
    while(atual != NULL) {
        if(atual->dados.status == 1) {
            fprintf(f, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>R$ %.2f</td><td>R$ %.2f</td></tr>",
                atual->dados.codigo, atual->dados.descricao, atual->dados.categoria,
                atual->dados.quantidade_estoque, atual->dados.preco_custo, atual->dados.valor_locacao);
        }
        atual = atual->proximo;
    }
    fprintf(f, "</table></body></html>");
    fclose(f);
    abrir_arquivo_html(caminho_final);
    exibir_mensagem_relatorio("Relatorio de Equipamentos gerado!");
}

void gerar_cronograma_alocacao_html() {
    char caminho_final[200] = "b_output/relatorios/cronograma.html";
    FILE *f = fopen(caminho_final, "w");
    if (!f) f = fopen("../b_output/relatorios/cronograma.html", "w");
    if (!f) return;

    listaEventos = carregar_eventos(listaEventos);
    listaItensOrcamento = carregar_itens_orcamento(listaItensOrcamento);
    listaRecursos = carregar_recursos(listaRecursos);

    escrever_cabecalho_html(f, "Cronograma de Alocacao de Recursos");
    fprintf(f, "<table><tr><th>Data Inicio</th><th>Data Fim</th><th>Equipamento</th><th>Qtd</th><th>Evento</th><th>Status</th></tr>");

    NoItemOrcamento *atualItem = listaItensOrcamento;
    while(atualItem != NULL) {
        if(atualItem->dados.tipo_item == 1 && atualItem->dados.status == 1) {
            
            Evento* evt = buscar_evento_por_codigo(listaEventos, atualItem->dados.id_evento);
            Equipamento* rec = buscar_recurso_por_codigo(listaRecursos, atualItem->dados.id_estrangeiro);

            if(evt != NULL && rec != NULL && evt->status != 3) {
                char* st_evt = (evt->status == 0) ? "Orcamento" : ((evt->status == 1) ? "Aprovado" : "Finalizado");
                
                fprintf(f, "<tr><td>%s</td><td>%s</td><td>%s</td><td>%d</td><td>%s</td><td>%s</td></tr>",
                    evt->data_inicio, evt->data_fim, rec->descricao, 
                    atualItem->dados.quantidade, evt->nome_evento, st_evt);
            }
        }
        atualItem = atualItem->proximo;
    }
    fprintf(f, "</table></body></html>");
    fclose(f);
    abrir_arquivo_html(caminho_final);
    exibir_mensagem_relatorio("Cronograma gerado!");
}

void gerar_relatorio_financeiro_html() {
    char caminho_final[200] = "b_output/relatorios/financeiro.html";
    FILE *f = fopen(caminho_final, "w");
    if (!f) f = fopen("../b_output/relatorios/financeiro.html", "w");
    if (!f) return;

    listaContasReceber = carregar_contas_receber(listaContasReceber);
    listaContasPagar = carregar_contas_pagar(listaContasPagar);
    listaCaixa = carregar_extrato_caixa(listaCaixa);

    escrever_cabecalho_html(f, "Relatorio Financeiro Completo");

    fprintf(f, "<h2>Contas a Receber (Clientes)</h2>");
    fprintf(f, "<table><tr><th>ID</th><th>Cliente ID</th><th>Evento ID</th><th>Vencimento</th><th>Valor</th><th>Status</th></tr>");
    NoContaReceber *cr = listaContasReceber;
    while(cr != NULL) {
        char* st = (cr->dados.status == 1) ? "<span class='entrada'>Pago</span>" : "Pendente";
        fprintf(f, "<tr><td>%d</td><td>%d</td><td>%d</td><td>%s</td><td>R$ %.2f</td><td>%s</td></tr>",
            cr->dados.id, cr->dados.id_cliente, cr->dados.id_evento, cr->dados.data_vencimento, cr->dados.valor_total, st);
        cr = cr->proximo;
    }
    fprintf(f, "</table>");

    fprintf(f, "<h2>Contas a Pagar (Fornecedores/Compras)</h2>");
    fprintf(f, "<table><tr><th>ID</th><th>Recurso ID</th><th>Vencimento</th><th>Valor</th><th>Status</th></tr>");
    NoContaPagar *cp = listaContasPagar;
    while(cp != NULL) {
        char* st = (cp->dados.status == 1) ? "<span class='entrada'>Pago</span>" : "Pendente";
        fprintf(f, "<tr><td>%d</td><td>%d</td><td>%s</td><td>R$ %.2f</td><td>%s</td></tr>",
            cp->dados.id, cp->dados.id_recurso_compra, cp->dados.data_vencimento, cp->dados.valor_total, st);
        cp = cp->proximo;
    }
    fprintf(f, "</table>");

    fprintf(f, "<h2>Fluxo de Caixa</h2>");
    fprintf(f, "<table><tr><th>Data</th><th>Descricao</th><th>Entrada/Saida</th><th>Valor</th><th>Saldo Apos</th></tr>");
    NoCaixa *cx = listaCaixa;
    while(cx != NULL) {
    fprintf(f, "<tr><td>%s</td><td>%s</td><td class='%s'>%s</td><td>R$ %.2f</td><td>R$ %.2f</td></tr>",
        cx->dados.data, 
        cx->dados.descricao, 
        (cx->dados.tipo == 1 ? "entrada" : "saida"), 
        (cx->dados.tipo == 1 ? "Entrada" : "Saida"), 
        cx->dados.valor, 
        cx->dados.saldo_final);
    cx = cx->proximo;
}
    fprintf(f, "</table>");

    fprintf(f, "</body></html>");
    fclose(f);
    abrir_arquivo_html(caminho_final);
    exibir_mensagem_relatorio("Relatorio Financeiro gerado!");
}


void iniciar_modulo_relatorios() {
    int op;
    do {
        printf("\n--- MENU RELATORIOS ---\n");
        printf("1. Lista de Clientes (HTML)\n");
        printf("2. Lista de Eventos (HTML)\n");
        printf("3. Lista de Equipamentos (HTML)\n");
        printf("4. Cronograma de Alocacao (HTML)\n");
        printf("5. Relatorio Financeiro Completo (HTML)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op) {
            case 1: gerar_relatorio_clientes_html(); break;
            case 2: {
                int st;
                printf("Filtrar Status? (-1=Todos, 0=Orc, 1=Aprov, 2=Fim): ");
                scanf("%d", &st);
                gerar_relatorio_eventos_html(st); 
                break;
            }
            case 3: gerar_relatorio_equipamentos_html(); break;
            case 4: gerar_cronograma_alocacao_html(); break;
            case 5: gerar_relatorio_financeiro_html(); break;
            case 0: exibir_mensagem_relatorio("Voltando..."); break;
            default: exibir_mensagem_relatorio("Opcao invalida");
        }
        if(op!=0) {
            printf("\nPressione Enter...");
            getchar(); getchar();
        }
    } while(op != 0);
}