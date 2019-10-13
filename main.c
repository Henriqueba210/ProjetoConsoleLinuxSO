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

void mkdir(char *parameter) {
    if (parameter) {

    }
}

void comandos(char *funcao, char *parametro)
{
    if(strcmp(funcao, "mkdir") == 0)
    {
        mkdir(parametro);

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
    printf("Comando = %s \n", comando);
    printf("Parametro = %s \n", parametro);
    comandos(comando, parametro);



    return 0;

}

