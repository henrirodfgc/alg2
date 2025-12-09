#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xml_controller.h"
#include "../../view/xml/xml_view.h"
#include "../../model/cadastro/cliente.h"
#include "../../model/cadastro/recursos.h"
#include "../../model/orcamento/evento.h"
#include "../../model/cadastro/fornece_e_parce.h"
#include "../../model/cadastro/equipe.h"
#include "../../model/cadastro/produtora.h"

extern NoCliente *listaClientes;
extern NoCliente* carregar_clientes(NoCliente* lista);

extern NoRecurso *listaRecursos;
extern NoRecurso* carregar_recursos(NoRecurso* lista);

extern NoEvento *listaEventos;
extern NoEvento* carregar_eventos(NoEvento* lista);

extern NoFornecedores_e_parceiros *listaFornecedores_e_parceiros;
extern NoFornecedores_e_parceiros* carregar_fornecedores_e_parceiros(NoFornecedores_e_parceiros* lista);

extern NoEquipe *listaEquipe;
extern NoEquipe* carregar_equipe(NoEquipe* lista);

extern NoProdutora *listaProdutora;
extern NoProdutora* carregar_produtoras(NoProdutora* lista);


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
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

    listaClientes = carregar_clientes(listaClientes);
    listaRecursos = carregar_recursos(listaRecursos);
    listaEventos = carregar_eventos(listaEventos);
    listaFornecedores_e_parceiros = carregar_fornecedores_e_parceiros(listaFornecedores_e_parceiros);
    listaEquipe = carregar_equipe(listaEquipe);
    listaProdutora = carregar_produtoras(listaProdutora);

    fprintf(f, "<dados>\n");

    fprintf(f, "  <tabela-cliente>\n");
    NoCliente *atualCli = listaClientes;
    while(atualCli) {
        if(atualCli->dados.status == 1) {
            fprintf(f, "    <registro>\n");
            fprintf(f, "      <codigo>%d</codigo>\n", atualCli->dados.id);
            fprintf(f, "      <razao_social>%s</razao_social>\n", atualCli->dados.nome_razao); 
            fprintf(f, "      <nome_fantasia>%s</nome_fantasia>\n", atualCli->dados.nome_cliente);
            fprintf(f, "      <cpf_cnpj>%s</cpf_cnpj>\n", (strlen(atualCli->dados.cpf)>0 ? atualCli->dados.cpf : atualCli->dados.cnpj)); 
            fprintf(f, "      <telefone>%s</telefone>\n", atualCli->dados.telefone);
            fprintf(f, "      <email>%s</email>\n", atualCli->dados.email);
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
            fprintf(f, "      <categoria>%s</categoria>\n", atualRec->dados.categoria);
            fprintf(f, "      <quantidade_estoque>%d</quantidade_estoque>\n", atualRec->dados.quantidade_estoque);
            fprintf(f, "      <preco_custo>%.2f</preco_custo>\n", atualRec->dados.preco_custo);
            fprintf(f, "      <valor_locacao>%.2f</valor_locacao>\n", atualRec->dados.valor_locacao);
            fprintf(f, "    </registro>\n");
        }
        atualRec = atualRec->proximo;
    }
    fprintf(f, "  </tabela-equipamento>\n");
    
    fprintf(f, "  <tabela-evento>\n");
    NoEvento *atualEvt = listaEventos;
    while(atualEvt) {
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo_evento>%d</codigo_evento>\n", atualEvt->dados.codigo);
        fprintf(f, "      <nome_evento>%s</nome_evento>\n", atualEvt->dados.nome_evento);
        fprintf(f, "      <codigo_cliente>%d</codigo_cliente>\n", atualEvt->dados.codigo_cliente);
        char* st_str = "Orcamento";
        if(atualEvt->dados.status == 1) st_str = "Aprovado";
        else if(atualEvt->dados.status == 2) st_str = "Finalizado";
        fprintf(f, "      <status>%s</status>\n", st_str);
        fprintf(f, "    </registro>\n");
        atualEvt = atualEvt->proximo;
    }
    fprintf(f, "  </tabela-evento>\n");

    fprintf(f, "  <tabela-fornecedor>\n");
    NoFornecedores_e_parceiros *atualForn = listaFornecedores_e_parceiros;
    while(atualForn) {
        if(atualForn->dados.status == 1) {
            fprintf(f, "    <registro>\n");
            fprintf(f, "      <id>%d</id>\n", atualForn->dados.id);
            fprintf(f, "      <nome>%s</nome>\n", atualForn->dados.nome_fantasia);
            fprintf(f, "      <tipo>%d</tipo>\n", atualForn->dados.tipo); // 0=CPF, 1=CNPJ
            fprintf(f, "      <doc>%s</doc>\n", (atualForn->dados.tipo==0 ? atualForn->dados.cpf : atualForn->dados.cnpj));
            fprintf(f, "    </registro>\n");
        }
        atualForn = atualForn->proximo;
    }
    fprintf(f, "  </tabela-fornecedor>\n");

    fprintf(f, "  <tabela-equipe>\n");
    NoEquipe *atualEq = listaEquipe;
    while(atualEq) {
        if(atualEq->dados.status == 1) {
            fprintf(f, "    <registro>\n");
            fprintf(f, "      <codigo>%d</codigo>\n", atualEq->dados.codigo);
            fprintf(f, "      <nome>%s</nome>\n", atualEq->dados.nome);
            fprintf(f, "      <funcao>%s</funcao>\n", atualEq->dados.funcao);
            fprintf(f, "      <valor_hora>%.2f</valor_hora>\n", atualEq->dados.valor_diaria_hora);
            fprintf(f, "    </registro>\n");
        }
        atualEq = atualEq->proximo;
    }
    fprintf(f, "  </tabela-equipe>\n");

    fprintf(f, "  <tabela-produtora>\n");
    NoProdutora *atualProd = listaProdutora;
    while(atualProd) {
        if(atualProd->dados.status == 1) {
            fprintf(f, "    <registro>\n");
            fprintf(f, "      <cnpj>%s</cnpj>\n", atualProd->dados.cnpj);
            fprintf(f, "      <nome>%s</nome>\n", atualProd->dados.nome_fantasia);
            fprintf(f, "      <email>%s</email>\n", atualProd->dados.email);
            fprintf(f, "    </registro>\n");
        }
        atualProd = atualProd->proximo;
    }
    fprintf(f, "  </tabela-produtora>\n");

    fprintf(f, "</dados>\n");
    fclose(f);
    exibir_mensagem_xml("exportacao concluida: b_output/dados.xml");
}

void limpar_cliente_temp(Cliente* c) {
    c->id = 0; strcpy(c->nome_cliente, ""); strcpy(c->nome_razao, ""); strcpy(c->cpf, ""); c->status = 1;
}
void limpar_recurso_temp(Equipamento* e) {
    e->codigo = 0; strcpy(e->descricao, ""); e->quantidade_estoque = 0; e->preco_custo = 0.0; e->status = 1;
}
void limpar_evento_temp(Evento* e) {
    e->codigo = 0; strcpy(e->nome_evento, ""); e->status = 0;
}
void limpar_fornecedor_temp(Fornecedores_e_parceiros* f) {
    f->id = 0; strcpy(f->nome_fantasia, ""); f->status = 1;
}
void limpar_equipe_temp(MembroEquipe* m) {
    m->codigo = 0; strcpy(m->nome, ""); m->status = 1;
}
void limpar_produtora_temp(Produtora* p) {
    strcpy(p->cnpj, ""); strcpy(p->nome_fantasia, ""); p->status = 1;
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
    
    int lendo_cliente = 0, lendo_equipamento = 0, lendo_evento = 0;
    int lendo_fornecedor = 0, lendo_equipe = 0, lendo_produtora = 0;
    
    Cliente tempCli; Equipamento tempRec; Evento tempEvt;
    Fornecedores_e_parceiros tempForn; MembroEquipe tempEq; Produtora tempProd;

    exibir_cabecalho_importacao();
    
    listaClientes = carregar_clientes(listaClientes);
    listaRecursos = carregar_recursos(listaRecursos);
    listaEventos = carregar_eventos(listaEventos);
    listaFornecedores_e_parceiros = carregar_fornecedores_e_parceiros(listaFornecedores_e_parceiros);
    listaEquipe = carregar_equipe(listaEquipe);
    listaProdutora = carregar_produtoras(listaProdutora);

    while (fgets(linha, sizeof(linha), f)) {
        
        if (strstr(linha, "<tabela-cliente>")) { lendo_cliente = 1; continue; }
        if (strstr(linha, "<tabela-equipamento>")) { lendo_equipamento = 1; continue; }
        if (strstr(linha, "<tabela-evento>")) { lendo_evento = 1; continue; }
        if (strstr(linha, "<tabela-fornecedor>")) { lendo_fornecedor = 1; continue; }
        if (strstr(linha, "<tabela-equipe>")) { lendo_equipe = 1; continue; }
        if (strstr(linha, "<tabela-produtora>")) { lendo_produtora = 1; continue; }

        if (strstr(linha, "</tabela-cliente>")) { lendo_cliente = 0; continue; }
        if (strstr(linha, "</tabela-equipamento>")) { lendo_equipamento = 0; continue; }
        if (strstr(linha, "</tabela-evento>")) { lendo_evento = 0; continue; }
        if (strstr(linha, "</tabela-fornecedor>")) { lendo_fornecedor = 0; continue; }
        if (strstr(linha, "</tabela-equipe>")) { lendo_equipe = 0; continue; }
        if (strstr(linha, "</tabela-produtora>")) { lendo_produtora = 0; continue; }

        // Novo Registro
        if (strstr(linha, "<registro>")) {
            if (lendo_cliente) limpar_cliente_temp(&tempCli);
            if (lendo_equipamento) limpar_recurso_temp(&tempRec);
            if (lendo_evento) limpar_evento_temp(&tempEvt);
            if (lendo_fornecedor) limpar_fornecedor_temp(&tempForn);
            if (lendo_equipe) limpar_equipe_temp(&tempEq);
            if (lendo_produtora) limpar_produtora_temp(&tempProd);
            continue;
        }

        // Fim de Registro -> Salvar
        if (strstr(linha, "</registro>")) {
            if (lendo_cliente && tempCli.id != 0) {
                if (buscar_cliente_por_id(listaClientes, tempCli.id) == NULL) {
                    listaClientes = adicionar_cliente_na_lista(listaClientes, tempCli);
                    exibir_detalhe_importacao("Cliente", tempCli.nome_cliente);
                    importados++;
                }
            }
            if (lendo_equipamento && tempRec.codigo != 0) {
                if (buscar_recurso_por_codigo(listaRecursos, tempRec.codigo) == NULL) {
                    listaRecursos = adicionar_recurso_na_lista(listaRecursos, tempRec);
                    exibir_detalhe_importacao("Equipamento", tempRec.descricao);
                    importados++;
                }
            }
            if (lendo_evento && tempEvt.codigo != 0) {
                if (buscar_evento_por_codigo(listaEventos, tempEvt.codigo) == NULL) {
                    listaEventos = adicionar_evento_na_lista(listaEventos, tempEvt);
                    exibir_detalhe_importacao("Evento", tempEvt.nome_evento);
                    importados++;
                }
            }
            if (lendo_fornecedor && tempForn.id != 0) {
                if (buscar_fornece_e_parce_por_id(listaFornecedores_e_parceiros, tempForn.id) == NULL) {
                    listaFornecedores_e_parceiros = adicionar_fornecedor_na_lista(listaFornecedores_e_parceiros, tempForn);
                    exibir_detalhe_importacao("Fornecedor/Parceiro", tempForn.nome_fantasia);
                    importados++;
                }
            }
            if (lendo_equipe && tempEq.codigo != 0) {
                if (buscar_membro_por_codigo(listaEquipe, tempEq.codigo) == NULL) {
                    listaEquipe = adicionar_membro_na_lista(listaEquipe, tempEq);
                    exibir_detalhe_importacao("Membro Equipe", tempEq.nome);
                    importados++;
                }
            }
            if (lendo_produtora && strlen(tempProd.cnpj) > 0) {
                if (buscar_produtora_por_cnpj(listaProdutora, tempProd.cnpj) == NULL) {
                    listaProdutora = adicionar_produtora_na_lista(listaProdutora, tempProd);
                    exibir_detalhe_importacao("Produtora", tempProd.nome_fantasia);
                    importados++;
                }
            }
            continue;
        }

        // Leitura dos Campos
        if (lendo_cliente) {
            if (strstr(linha, "<codigo>")) { extrair_tag_xml(linha, "codigo", valor); tempCli.id = atoi(valor); }
            else if (strstr(linha, "<nome_fantasia>")) { extrair_tag_xml(linha, "nome_fantasia", valor); strcpy(tempCli.nome_cliente, valor); }
            else if (strstr(linha, "<razao_social>")) { extrair_tag_xml(linha, "razao_social", valor); strcpy(tempCli.nome_razao, valor); }
            else if (strstr(linha, "<cpf_cnpj>")) { extrair_tag_xml(linha, "cpf_cnpj", valor); strcpy(tempCli.cpf, valor); } // Simplificado
        }
        else if (lendo_equipamento) {
            if (strstr(linha, "<codigo>")) { extrair_tag_xml(linha, "codigo", valor); tempRec.codigo = atoi(valor); }
            else if (strstr(linha, "<descricao>")) { extrair_tag_xml(linha, "descricao", valor); strcpy(tempRec.descricao, valor); }
        }
        else if (lendo_evento) {
            if (strstr(linha, "<codigo_evento>")) { extrair_tag_xml(linha, "codigo_evento", valor); tempEvt.codigo = atoi(valor); }
            else if (strstr(linha, "<nome_evento>")) { extrair_tag_xml(linha, "nome_evento", valor); strcpy(tempEvt.nome_evento, valor); }
        }
        else if (lendo_fornecedor) {
            if (strstr(linha, "<id>")) { extrair_tag_xml(linha, "id", valor); tempForn.id = atoi(valor); }
            else if (strstr(linha, "<nome>")) { extrair_tag_xml(linha, "nome", valor); strcpy(tempForn.nome_fantasia, valor); }
        }
        else if (lendo_equipe) {
            if (strstr(linha, "<codigo>")) { extrair_tag_xml(linha, "codigo", valor); tempEq.codigo = atoi(valor); }
            else if (strstr(linha, "<nome>")) { extrair_tag_xml(linha, "nome", valor); strcpy(tempEq.nome, valor); }
        }
        else if (lendo_produtora) {
            if (strstr(linha, "<cnpj>")) { extrair_tag_xml(linha, "cnpj", valor); strcpy(tempProd.cnpj, valor); }
            else if (strstr(linha, "<nome>")) { extrair_tag_xml(linha, "nome", valor); strcpy(tempProd.nome_fantasia, valor); }
        }
    }
    fclose(f);
    
    char final_msg[100];
    sprintf(final_msg, "Importacao finalizada. %d novos registros salvos.", importados);
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