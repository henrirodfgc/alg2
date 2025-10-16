#include "controller/cliente_controller.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

// =============================
// PONTO DE ENTRADA DO SISTEMA
// Onde tudo começa
// =============================

int main() {
    system("chcp 65001"); // Pra funcionar acento no Windows (UTF-8)
    setlocale(LC_ALL, "pt-BR"); // Pra data e hora (n vai usar agr mas é bom ter)
    iniciar_sistema(); // Chama o Controller pra começar o menu

    return 0; // Finaliza o programa de boa
}