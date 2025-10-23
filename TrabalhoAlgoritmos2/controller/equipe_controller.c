#include <stdlib.h>
#include <stdio.h>
#include "../model/equipe.h"
// #include "../view/equipe_view.h" // A gente cria essa View já já
#include "equipe_controller.h"

// Lista ligada para guardar a equipe (o mestre de obras)
NoEquipe *listaEquipe = NULL; 

// A função que vai ter o menu e a lógica principal da Equipe
void iniciar_equipe() {
    int opcao; // pra guardar o que o user escolher
    int codigo_busca; // pra achar o membro
    MembroEquipe temp; // membro temporário

    // [FUTURO]: Código de persistência entra aqui
    
    // Loop principal da Equipe
    do {
        printf("\n==== menu equipe ====\n");
        printf("1 - criar membro\n");
        printf("2 - atualizar membro\n");
        printf("3 - exibir membro\n");
        printf("4 - deletar membro\n");
        printf("5 - listar todos\n"); 
        printf("0 - sair do modulo\n");
        printf("escolha: ");
        scanf("%d", &opcao); // pega a escolha

        switch (opcao) {
            case 1: { // C: Criar
                // [FALTA]: Chamar a função da View para ler os dados do novo membro
                // temp = ler_dados_membro();
                
                // [FALTA]: Implementar a lógica de verificação de ID/Código
                
                // [FALTA]: Chamar a Model para adicionar
                // listaEquipe = adicionar_membro_na_lista(listaEquipe, temp);
                // exibir_mensagem("membro criado com sucesso");
                printf("funcionalidade 1 (criar) em construcao...\n"); 
                break;
            }
            case 2: { // U: Atualizar
                // [FALTA]: Implementar a lógica de busca e atualização
                printf("funcionalidade 2 (atualizar) em construcao...\n"); 
                break;
            }
            case 3: { // R: Exibir Um
                // [FALTA]: Implementar a lógica de busca e exibição
                printf("funcionalidade 3 (exibir) em construcao...\n"); 
                break;
            }
            case 4: { // D: Deletar
                // [FALTA]: Implementar a lógica de deleção
                printf("funcionalidade 4 (deletar) em construcao...\n"); 
                break;
            }
            case 5: { // R: Listar Todos
                // A gente já implementou no Model, agora é só chamar!
                exibir_todos_membros(listaEquipe); 
                break;
            }
            case 0:
                printf("saindo do modulo equipe.\n");
                break;
            default:
                printf("opção inválida.\n");
        }
    } while (opcao != 0);

    // CRÍTICO: Libera a memória no final do uso do módulo!
    desalocar_lista_equipe(listaEquipe);
}