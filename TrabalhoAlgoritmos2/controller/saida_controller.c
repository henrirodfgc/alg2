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


int troca_txt_bin(char troca){

    int atual = verificar_tipo_saida(); //verifica qual tipo atual escolhido -> 1=txt / 2=bin / 3=memoria. Dependendo de qual foi a saida da funao anterior
    
    if (atual == -1)
    {
        return 0; //erro para verificar
    }
    
    if ((atual == 1 && troca == 't') || (atual == 2 && troca == 'b'))
    {
        printf("Não é necessário trocar o formato, o arquivo já está selecionado neste formato.\n");
        return 0; // a troca nao é efetuada pois o usuario nao selecionou uma mudanca diferente da que ja estava selecionada.
    }

    // caso o valor da troca seja valido, abrir um arquivo txt para alterar. Como vai alterar informaçoes, seria "w"
    FILE* temp_file = fopen ("../b_output/tipo_file.txt", "w");
    
    if (temp_file==NULL)
    {
        printf("Erro ao criar arquivo.\n");
        return 0;
    }


    if (troca == 't')
    {
        fprintf (temp_file, "txt\n");
    }
    else if (troca == 'b')
    {
        fprintf (temp_file, "bin\n");
    }
    else if (troca == 'm')
    {
        fprintf (temp_file, "mem\n");
    }
    else 
    {
        printf("tipo de troca inválido. \n");
        fclose(temp_file);
        return 0;
    }

    fclose(temp_file);

    printf("sua troca foi realizada com sucesso!!");
    
}







void fecharArquivos(FILE *file) {
    if (file != NULL)
        fclose(file);
}
