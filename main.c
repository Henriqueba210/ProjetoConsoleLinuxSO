/*
Integrantes:
Henrique Barros de Almeida
Lucas Abrahão
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

struct Diretorio {
    char nome[8];
    char hora[9];
    char data[9];
    int pai;

};
struct Diretorio diretorio[1023];
char comandoInserido[80] = "";
char *comando = "", *parametro = "";
int posicaoAtual = 0, codDir = 1;
int const rmConst = 9999;

int checaDiretorioJaExistente(char *parametro) {
    int validadorNomeIgual = 0;
    for (int i = 0; i < codDir; i++) {
        if (diretorio[i].pai == posicaoAtual && !strcmp(diretorio[i].nome, parametro)) {
            validadorNomeIgual++;
        }
    }
    if (validadorNomeIgual == 1) {
        printf("Ja existe um diretorio com esse nome\n");
        return 0;
    } else {
        return 1;
    }
}

void mkdir(char *parameter) {
    if (checaDiretorioJaExistente(parametro)) {
        fflush(stdin);
        strcpy(diretorio[codDir].nome, parameter);
        struct tm *tm;
        time_t t;
        time(&t);
        tm = localtime(&t);
        strftime(diretorio[codDir].data, 100, "%m/%d/%Y", tm);
        strftime(diretorio[codDir].hora, 100, "%H:%M:%S", tm);
        diretorio[codDir].pai = posicaoAtual;
        codDir++;
    }
}

void rmdir(char *parameter) {

    bool found = false;
    for (int i = 1; i <= codDir; i++) {
        if (!strcmp(diretorio[i].nome, parameter) && diretorio[i].pai == posicaoAtual) {
            bool diretorioPossuiFilhos = false;

            for (int j = 1; j <= codDir; j++) {
                if (diretorio[j].pai == posicaoAtual + 1 && (posicaoAtual + 1) == i) {
                    diretorioPossuiFilhos = true;
                }
            }

            if (diretorioPossuiFilhos) {
                printf("falha ao remover %s: Diretório não vazio\n", parameter);
                return;
            }

            diretorio[i].pai = rmConst;
            found = true;
        }
    }

    if (!found) {
        printf("Diretório inexistente.\n");
    }
}

void help(int funcao) {
    switch (funcao) {
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
            printf("Uso: rmdir [DIRETÓRIO]\nRemove o DIRETÓRIO desejado.\n");
            break;
        case 7:
            printf("Mostra na tela o nome dos integrantes desta tarefa especial.\n");
            break;
        default:
            break;
    }
}

void cd(char *param) {
    if (!strcmp(param, "..") || !strcmp(param, "../")) {
        if (posicaoAtual > 0) {
            posicaoAtual--;
        }
    } else if (!strcmp(param, "/")) {
        posicaoAtual = 0;
    } else {
        if (codDir == 0) {
            printf("Diretório inexistente.\n");
            return;
        }

        bool found = false;

        for (int i = 1; i <= codDir; i++) {
            if (strcmp(diretorio[i].nome, param) == 0 && diretorio[i].pai == posicaoAtual) {
                if (diretorio[i].pai != rmConst) {
                    posicaoAtual = diretorio[i].pai + 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("Diretório inexistente.\n");
        }
    }
}

void ls(const char *parameter) {
    char *hora = "";
    char *data = "";
    for (int i = 1; i <= codDir; i++) {
        if (!strcmp(parameter, "") && diretorio[i].pai == posicaoAtual) {
            printf("%s \n", diretorio[i].nome);
        } else if (!strcmp(parameter, "-l") && diretorio[i].pai == posicaoAtual) {
            data = diretorio[i].data;
            hora = diretorio[i].hora;
            printf("%s %s %s \n", diretorio[i].nome, data, hora);
        }
    }
}


void pwd() {
    if (posicaoAtual > 0) {
        int indexDir = diretorio[posicaoAtual].pai;
        for (int i = 0; i < codDir; i++) {
            if (indexDir != 0) {
                printf("/%s", diretorio[indexDir].nome);
                indexDir = diretorio[indexDir].pai;
            }
        }
        printf("/%s$ ", diretorio[posicaoAtual].nome);
    }
}

void clear() {
    system("clear");
}

void about() {
    printf("-Tarefa especial -\n-Integrantes-\n-Henrique Barros de Almeida-\n-Lucas Abrahão-\n");
}


void comandos(char *funcao, char *parameter) {
    if (!strcmp(funcao, "mkdir")) {
        if (!strcmp(parameter, "")) {
            printf("nome do diretorio não pode ser vazio\n");
        } else {
            mkdir(parameter);
        }
    } else if (!strcmp(funcao, "ls")) {
        ls(parameter);
    } else if (!strcmp(funcao, "cd")) {
        if (!strcmp(parameter, "")) {
            printf("nome do diretorio não pode ser vazio\n");
        } else {
            cd(parameter);
        }
    } else if (!strcmp(funcao, "rmdir")) {
        if (!strcmp(parameter, "")) {
            printf("nome do diretorio não pode ser vazio\n");
        } else {
            rmdir(parameter);
        }
    } else if (!strcmp(funcao, "pwd") && !strcmp(parameter, "")) {
        pwd();
    } else if (!strcmp(funcao, "clear") && !strcmp(parameter, "")) {
        clear();
    } else if (!strcmp(funcao, "about") && !strcmp(parameter, "")) {
        about();
    } else if (!strcmp(funcao, "mkdir") && !strcmp(parameter, "--help")) {
        help(5);
    } else if (!strcmp(funcao, "ls") && !strcmp(parameter, "--help")) {
        help(2);
    } else if (!strcmp(funcao, "cd") && !strcmp(parameter, "--help")) {
        help(1);
    } else if (!strcmp(funcao, "rmdir") && !strcmp(parameter, "--help")) {
        help(6);
    } else if (!strcmp(funcao, "pwd") && !strcmp(parameter, "--help")) {
        help(3);
    } else if (!strcmp(funcao, "clear") && !strcmp(parameter, "--help")) {
        help(4);
    } else if (!strcmp(funcao, "about") && !strcmp(parameter, "--help")) {
        help(7);
    } else if (strcmp(funcao, "poweroff")) {
        printf("comando ou parametro não encontrado\n");
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    diretorio[0].nome[0] = '/';
    struct tm *tm;
    time_t t;
    time(&t);
    tm = localtime(&t);
    strftime(diretorio[0].data, 100, "%m/%d/%Y", tm);
    strftime(diretorio[0].hora, 100, "%H:%M:%S", tm);
    diretorio[0].pai = 0;
    posicaoAtual = 0;
    system("clear");
    while (strcmp(comando, "poweroff")) {
        printf("$ ");
        gets(comandoInserido);
        comando = strtok(comandoInserido, " ");
        parametro = strtok(NULL, "\0");
        if (parametro == NULL) {
            parametro = "";
        }
        comandos(comando, parametro);
    }
    return 0;
}