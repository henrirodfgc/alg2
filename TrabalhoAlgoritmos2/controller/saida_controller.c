#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int verificar_tipo_saida (){
    FILE* file = fopen ("../b_output/tipo_file.txt","r"); // "r" tenta abrir ficheiro em modo leitura
    //cria um arquivo txt por padrao
    if (file==NULL)
    {
        fclose(file);   //se o ficheiro nao existe, devolve NULL
        return 0;
    }
    
    char tipo[10]; //ler linha do ficheiro
    if (fgets(tipo, sizeof(tipo),file)==NULL)  //vai ler ate  sizeof(tipo) caracteres. Se falhar, retorna NULL, imprime o erro, fecha arquivo, retorna 0.
    {
        printf("Erro ao ler o arquivo tipo_file.txt.\n");
        fclose(file);
        return 0;
    }
    

     //retonra 1 para txt, 2 para BIN, 3 para memoria
     if (strncmp(tipo, "txt", 3) == 0) {
        fclose(file);
        int retorna = 1;
        return retorna;
    } else if (strncmp(tipo, "bin", 3) == 0) {
        fclose(file);
        int retorna = 2;
        return retorna;
    } else if (strncmp(tipo, "mem", 3) == 0) {
        fclose(file);
        int retorna = 3;
        return retorna;
    } else {
        printf("Tipo de arquivo inválido no tipo_file.txt.\n");
        return 0;
    }
}



void fecharArquivos(FILE *file) {
    if (file != NULL)
        fclose(file);
}
