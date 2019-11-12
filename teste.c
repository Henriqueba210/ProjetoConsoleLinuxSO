/*
Integrantes:
Henrique Barros de Almeida
Lucas Abrahão
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int const rmConst = 9999;

char nome[8][1023];
char data[10][1023];
char hora[8][1023];
int *pai[1023];

int posicaoAtual = 0;
int codDir = 0;
char LinhaDeComando[80];
char *comando = "", *parametro;

void mkdir(char parameter[8]) {
    for (int i = 1; i <= codDir; i++) {
        if (strcmp(parameter, nome[codDir]) == 0 && pai[i] == posicaoAtual + 1) {
            printf("(!) Não é possível criar o diretório indicado. Causa: O diretório já existe.\n");
            return;
        }
    }

    codDir++;

    for (int i = 0; i < 8; i++) {
        nome[codDir][i] = parameter[i];
    }

    struct tm * tm;
    time_t t;

    time(&t);
    tm = localtime(&t);
    strftime(data[codDir], 10, "%d-%m-%y", tm);

    time(&t);
    tm = localtime(&t);
    strftime(hora[codDir], 100, "%H:%M:%S", tm);

    pai[codDir] = codDir;
}

void rmdir(char parameter[8]){
    if (codDir == 0) {
        printf("(!) Diretório informado não encontrado.\n");
        return;
    }

    bool diretorioEncontrado = false;

    for (int i = 1; i <= codDir; i++) {
        if (!strcmp(nome[i], parameter) && pai[i] == posicaoAtual + 1) {
            bool hasSon = false;

            for (int j = 1; j <= codDir; j++) {
                if ((pai[i]+1) == pai[j]) {
                    hasSon = true;
                }
            }

            if (hasSon) {
                printf("(!) Não é possível remover o diretório indicado. Causa: O diretório não está vazio.\n");
                return;
            }

            pai[i] = rmConst;
            diretorioEncontrado = true;
        }
    }

    if (!diretorioEncontrado) {
        printf("(!) Diretório informado não encontrado.\n");
    }
    codDir--;
}
int help(int funcao){
    switch (funcao)
    {
        case 1:
            printf("Uso: cd [DIRETÓRIO]\n Vai até o diretório indicado caso ele exista.\n");
            break;
        case 2:
            printf("Uso: ls [OPÇÃO]\nLista os Diretórios no diretório atual (caso não seja uitlizada a opção -l, neste caso ele irá mostrar as informaçes sobre os diretoórios também).\n");
            break;
        case 3:
            printf("Mostra o nome do diretório de trabalho atual.");
            break;
        case 4:
            printf("Limpa a tela do terminal.\n");
            break;
        case 5:
            printf("Uso: mkdir [DIRETÓRIO]\nCria o DIRETÓRIO desejado, se ele já não existir.\n");
            break;
        case 6:
            printf("Uso: rmdir [OPÇÃO]... DIRETÓRIO...\nRemove o DIRETÓRIO.\n");
            break;
        default:
            break;
    }
    return 0;
}

void cd(char parameter[8]){
    if (strcmp(parameter, "..") == 0) {
        if (posicaoAtual > 0) {
            posicaoAtual--;
        }
    } else if (strcmp(parameter, "/") == 0) {
        posicaoAtual = 0;
    } else {
        if (codDir == 0) {
            printf("(!) Diretório informado não encontrado.\n");
            return;
        }

        bool found = false;

        for (int i = 1; i <= codDir; i++) {
            if (strcmp(nome[i], parameter) == 0 && pai[i] == posicaoAtual + 1) {
                if (pai[i] != rmConst) {
                    posicaoAtual = pai[i];
                    found = true;
                }
            }
        }

        if (!found) {
            printf("(!) Diretório informado não encontrado.\n");
        }
    }
}

void ls(char parameter[8]){
    if (NULL == parameter){
        for (int i = 1; i <= codDir; i++) {
            if (pai[i] != rmConst && pai[i] == posicaoAtual + 1) {
                printf("%s\n", nome[i]);
            }
        }

    }else if (!strcmp(parameter,"-l")) {
        for (int i = 1; i <= codDir; i++) {
            if (pai[i] != rmConst && pai[i] == posicaoAtual + 1) {
                printf("%s %s %s\n", nome[i], data[i], hora[i]);
            }
        }
    } else{
        printf("Opção inválida %s",parameter);
    }
}



void pwd() {
    for (int i = 0; i < posicaoAtual + 1; i++) {
        printf("%s", nome[i]);

        if (i > 0)
            printf("/");
    }
    printf("\n");
}

void clear() {
    system("clear");
}


void comandos(char *funcao, char *parameter) {
    if (!strcmp(funcao, "mkdir")) {
        mkdir(parameter);

    } else if (!strcmp(funcao, "ls")) {
        ls(parameter);

    } else if(!strcmp(funcao,"cd")){
        cd(parameter);

    }else if(!strcmp(funcao,"rmdir")){
        rmdir(parameter);

    }else if(!strcmp(funcao,"pwd")){
        pwd();
    }
    else if(!strcmp(funcao,"clear")){
        clear();
    }else if(!strcmp(funcao, "mkdir") && !strcmp(parameter, "--help")){
        help(5);
    }else if(!strcmp(funcao, "ls") && !strcmp(parameter, "--help")){
        help(2);
    }else if(!strcmp(funcao, "cd") && !strcmp(parameter, "--help")){
        help(1);
    }else if(!strcmp(funcao, "rmdir") && !strcmp(parameter, "--help")){
        help(6);
    }else if(!strcmp(funcao, "pwd") && !strcmp(parameter, "--help")){
        help(3);
    }else if(!strcmp(funcao, "clear") && !strcmp(parameter, "--help")){
        help(4);
    }else{
        printf("comando ou parametro não encontrado\n");
    }
}


int main() {
    nome[0][0] = '/';
    data[0][0] = '11/11/2019';
    hora[0][0] = '08:24';
    pai[0] = 0;
    system("clear");
    while (strcmp(comando,"poweroff")) {
        printf("$ ");
        gets(LinhaDeComando);
        comando = strtok(LinhaDeComando, " ");
        parametro = strtok(NULL, "\0");
        comandos(comando, parametro);
    }
    return 0;
}