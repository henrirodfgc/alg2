#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xml_controller.h"
#include "../../view/xml/xml_view.h"
#include "../../model/cadastro/cliente.h"
#include "../../model/cadastro/recursos.h"
#include "../../model/orcamento/evento.h"

extern NoCliente *listaClientes;
extern NoCliente* carregar_clientes(NoCliente* lista);
extern NoRecurso *listaRecursos;
extern NoRecurso* carregar_recursos(NoRecurso* lista);
extern NoEvento *listaEventos;
extern NoEvento* carregar_eventos(NoEvento* lista);

void extrair_tag_xml(const char* linha, const char* tag, char* destino) {
    char tag_ini[50], tag_fim[50];
    sprintf(tag_ini, "<%s>", tag);
    sprintf(tag_fim, "</%s>", tag);

    char* inicio = strstr(linha, tag_ini);
    char* fim = strstr(linha, tag_fim);

    if (inicio && fim) {
        inicio += strlen(tag_ini); 
        int tamanho = fim - inicio;
        if (tamanho > 199) tamanho = 199; 
        strncpy(destino, inicio, tamanho);
        destino[tamanho] = '\0';
    } else {
        strcpy(destino, "");
    }
}

void exportar_xml() {
    FILE *f = fopen("b_output/dados.xml", "w");
    if (!f) f = fopen("../b_output/dados.xml", "w");
    
    if (!f) {
        exibir_mensagem_xml("erro ao criar arquivo xml.");
        return;
    }

    listaClientes = carregar_clientes(listaClientes);
    listaRecursos = carregar_recursos(listaRecursos);
    listaEventos = carregar_eventos(listaEventos);

    fprintf(f, "<dados>\n");

    fprintf(f, "  <tabela-cliente>\n");
    NoCliente *atualCli = listaClientes;
    while(atualCli) {
        if(atualCli->dados.status == 1) {
            fprintf(f, "    <registro>\n");
            fprintf(f, "      <codigo>%d</codigo>\n", atualCli->dados.id);
            fprintf(f, "      <nome>%s</nome>\n", atualCli->dados.nome_cliente);
            fprintf(f, "      <cpf_cnpj>%s</cpf_cnpj>\n", atualCli->dados.cpf); 
            fprintf(f, "    </registro>\n");
        }
        atualCli = atualCli->proximo;
    }
    fprintf(f, "  </tabela-cliente>\n");

    fprintf(f, "  <tabela-equipamento>\n");
    NoRecurso *atualRec = listaRecursos;
    while(atualRec) {
        if(atualRec->dados.status == 1) {
            fprintf(f, "    <registro>\n");
            fprintf(f, "      <codigo>%d</codigo>\n", atualRec->dados.codigo);
            fprintf(f, "      <descricao>%s</descricao>\n", atualRec->dados.descricao);
            fprintf(f, "      <estoque>%d</estoque>\n", atualRec->dados.quantidade_estoque);
            fprintf(f, "      <preco>%.2f</preco>\n", atualRec->dados.valor_locacao);
            fprintf(f, "    </registro>\n");
        }
        atualRec = atualRec->proximo;
    }
    fprintf(f, "  </tabela-equipamento>\n");
    
    fprintf(f, "  <tabela-evento>\n");
    NoEvento *atualEvt = listaEventos;
    while(atualEvt) {
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo>%d</codigo>\n", atualEvt->dados.codigo);
        fprintf(f, "      <nome>%s</nome>\n", atualEvt->dados.nome_evento);
        fprintf(f, "      <status>%d</status>\n", atualEvt->dados.status);
        fprintf(f, "    </registro>\n");
        atualEvt = atualEvt->proximo;
    }
    fprintf(f, "  </tabela-evento>\n");

    fprintf(f, "</dados>\n");
    fclose(f);
    exibir_mensagem_xml("exportacao concluida: b_output/dados.xml");
}

void importar_xml() {
    FILE *f = fopen("b_output/dados.xml", "r");
    if (!f) f = fopen("../b_output/dados.xml", "r");
    
    if (!f) {
        exibir_mensagem_xml("arquivo dados.xml nao encontrado para importacao.");
        return;
    }

    char linha[1024];
    char valor[200];
    int importados = 0;
    
    exibir_cabecalho_importacao();
    while (fgets(linha, sizeof(linha), f)) {
        if (strstr(linha, "<tabela-cliente>")) exibir_progresso_xml("lendo tabela de clientes...");
        if (strstr(linha, "<tabela-equipamento>")) exibir_progresso_xml("lendo tabela de equipamentos...");
        
        if (strstr(linha, "<nome>")) {
            extrair_tag_xml(linha, "nome", valor);
            exibir_detalhe_importacao("registro", valor);
            importados++;
        }
        else if (strstr(linha, "<descricao>")) {
            extrair_tag_xml(linha, "descricao", valor);
            exibir_detalhe_importacao("equipamento", valor);
            importados++;
        }
    }
    fclose(f);
    
    char final_msg[100];
    sprintf(final_msg, "leitura finalizada. %d registros identificados.", importados);
    exibir_mensagem_xml(final_msg);
}

void iniciar_modulo_xml() {
    int op;
    do {
        op = exibir_menu_xml();
        switch(op) {
            case 1: exportar_xml(); break;
            case 2: importar_xml(); break;
            case 0: exibir_mensagem_xml("voltando..."); break;
            default: exibir_mensagem_xml("opcao invalida");
        }
        if(op!=0) pausar_tela_xml();
    } while(op != 0);
}