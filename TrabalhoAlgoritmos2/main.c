#include "controller/cliente_controller.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

// =============================
// PONTO DE ENTRADA DO SISTEMA
// =============================

int main() {
    system("chcp 65001");
    setlocale(LC_ALL, "pt-BR");
    iniciar_sistema();

    return 0;
}
