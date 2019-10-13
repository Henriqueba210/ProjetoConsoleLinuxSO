/*
Integrantes:
Henrique Barros de Almeida
Lucas Abrahão
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char LinhaDeComando[80];
char *comando, *parametro;

void teste(char *funcao)
{
    if(strcmp(funcao, "mkdir") == 0)
    {
        printf("teste4");
    }else{

    }


}

int main()
{

    system("clear");
    printf("$ ");
    gets(LinhaDeComando);
    printf("Linha de Comando : %s \n", LinhaDeComando);

    comando = strtok(LinhaDeComando, "");
    parametro = strtok(NULL, "\0");
    teste(parametro);
    printf("Comando = %s \n", comando);
    printf("Parametro = %s \n", parametro);



    return 0;

}

