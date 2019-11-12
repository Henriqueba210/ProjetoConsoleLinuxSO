#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

const rmConst = 9999;

char nome[8][1023];
char data[10][1023];
char hora[8][1023];
int pai[1023];

int posicaoAtual = 0;
int codDir = 0;

void setup() {
    setlocale(NULL, "Portuguese");

    nome[0][0] = '/';
    data[0][0] = 'XX';
    hora[0][0] = 'XX';
    pai[0] = 0;

    printf("========================> Trabalho Especial S.O <========================\n\n");
    printf("Bem vindo ao trabalho especial da matéria de\nSistemas Operacionais, Fatec Americana - 2º Semestre 2019.\n");
    printf("\nPara saber as funcionalidades e os comandos disponíveis digite 'help'.\n");
    printf("\n========================> Trabalho Especial S.O <========================\n");
}

void pwd() {
    for (int i = 0; i < posicaoAtual + 1; i++) {
        printf("%s", nome[i]);

        if (i > 0)
            printf("/");
    }
    printf("\n");
}

void mkdir(char nomeP[8]) {

    for (int i = 1; i <= codDir; i++) {
        if (strcmp(nomeP, nome[codDir]) == 0 && pai[i] == posicaoAtual + 1) {
            printf("(!) Não é possível criar o diretório indicado. Causa: O diretório já existe.\n");
            return;
        }
    }

    codDir++;

    for (int i = 0; i < 8; i++) {
        nome[codDir][i] = nomeP[i];
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

void rmdir(char param[8]) {
    if (codDir == 0) {
        printf("(!) Diretório informado não encontrado.\n");
        return;
    }

    bool found = false;

    for (int i = 1; i <= codDir; i++) {
        if (strcmp(nome[i], param) == 0 && pai[i] == posicaoAtual + 1) {
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
            found = true;
        }
    }

    if (!found) {
        printf("(!) Diretório informado não encontrado.\n");
    }
    codDir--;
}

void ls(bool lParam) {
    if (lParam) {
        for (int i = 1; i <= codDir; i++) {
            if (pai[i] != rmConst && pai[i] == posicaoAtual + 1) {
                printf("%s %s %s\n", nome[i], data[i], hora[i]);
            }
        }
    } else {
        for (int i = 1; i <= codDir; i++) {
            if (pai[i] != rmConst && pai[i] == posicaoAtual + 1) {
                printf("%s\n", nome[i]);
            }
        }
    }
}

void cd(char param[8]) {
    if (strcmp(param, "..") == 0) {
        if (posicaoAtual > 0) {
            posicaoAtual--;
        }
    } else if (strcmp(param, "/") == 0) {
        posicaoAtual = 0;
    } else {
        if (codDir == 0) {
            printf("(!) Diretório informado não encontrado.\n");
            return;
        }

        bool found = false;

        for (int i = 1; i <= codDir; i++) {
            if (strcmp(nome[i], param) == 0 && pai[i] == posicaoAtual + 1) {
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

void clear() {
    system("cls");
}

void copyright () {
    printf("\n=-=-=-=-= Trabalho Especial S.O =-=-=-=-=\n");
    printf("\nTrabalho da matéria de S.0 I,\nda Fatec Americana - 2º Semestre 2019.");
    printf("\n\nEquipe: \n");
    printf("- André Nicola Nunes \n");
    printf("- Gustavo Rolim dos Santos \n");
    printf("- Maicon Gabriel de Sá \n");
    printf("- Vinicius Penachioni Tenomaro \n\n");
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void help() {
    printf("\n===============================> AJUDA <===============================\n\n");
    printf("pwd - Exibe o caminho de diretórios atual.\n");
    printf("mkdir - Cria um diretório. <Use: mkdir nome_do_diretório>\n");
    printf("ls - Lista os diretórios no caminho atual.\n");
    printf("rmdir - Remove um diretório. <Use: rmdir nome_do_diretório>\n");
    printf("ls -l - Lista os diretórios do caminho atual com informações de data e hora.\n");
    printf("cd - Vai para o diretório indicado. <Use: cd nome_do_diretório>.\n");
    printf("cd .. - Volta para o diretório anterior.\n");
    printf("cd / - Volta para o diretório raiz.\n");
    printf("clear - Limpa o prompt.\n");
    printf("copyright - Exibe os créditos dos desenvolvedores.\n");
    printf("date - Exibe data e hora.\n");
    printf("poweroff - Desliga a máquina.\n");
    printf("\n===========================> COMANDOS DO S.O <===========================\n");
}

void date() {
    char data5[100];

    struct tm * tm;
    time_t t;

    time(&t);
    tm = localtime(&t);
    strftime(data5, 100, "%m/%d/%Y %H:%M:%S", tm);

    printf("\n%s", data5);
}

int main() {
    setup();

    char line[80];
    char *command, *param;

    bool off = false;

    while(!off) {
        printf("\n$ ");
        gets(line);
        command = strtok(line, " ");
        param = strtok(NULL, "\0");

        if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "mkdir") == 0 && param == NULL) {
            printf("\n(!) Use: mkdir <nome_do_diretório>");
        } else if (strcmp(command, "rmdir") == 0 && param == NULL) {
            printf("\n(!) Use: rmdir <nome_do_diretório>");
        } else if (strcmp(command, "mkdir") == 0 && strlen(param) > 8) {
            printf("(!) Nome muito grande. (Máximo 8 caracteres)\n");
        } else if (strcmp(command, "mkdir") == 0) {
            mkdir(param);
        } else if (strcmp(command, "ls") == 0 && param == NULL) {
            ls(false);
        } else if (strcmp(command, "ls") == 0 && param != NULL) {
            if (strcmp(param, "-l") == 0) {
                ls(true);
            }
        } else if (strcmp(command, "cd") == 0 && param == NULL) {
            printf("\n(!) Use: cd <nome_do_diretório>");
        } else if (strcmp(command, "cd") == 0 && param != NULL) {
            cd(param);
        } else if (strcmp(command, "rmdir") == 0) {
            rmdir(param);
        } else if (strcmp(command, "clear") == 0) {
            clear();
        } else if (strcmp(command, "copyright") == 0) {
            copyright();
        } else if (strcmp(command, "help") == 0) {
            help();
        } else if (strcmp(command, "date") == 0) {
            date();
        } else if (strcmp(command, "poweroff") == 0) {
            printf("\nPrograma finalizado com sucesso!\n");
            off = true;
        } else {
            printf("\nOpção inválida! Digite help para ver os comandos.");
        }
    }

    return 0;
}