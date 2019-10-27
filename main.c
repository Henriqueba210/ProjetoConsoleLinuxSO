/*
Integrantes:
Henrique Barros de Almeida
Lucas Abrahão
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct diretorio {
    char nomeDiretorio[8];
    char hora[9];
    char data[9];
    int diretorioAnterior;
};
struct Diretorio diretorio[1024];
char LinhaDeComando[80];
char *comando, *parametro, *nomeAtual;
int posicao_atual = 0, cod_dir = 1, ultimosDiretorios[1024], contadorDiretorios;

int executarRmdir(char *parametro){
    if(validarValorDoParametro(parametro) == 1){
        for(int i = 0; i < cod_dir; i++){
            if(diretorio[i].pai == posicao_atual && strcmp(diretorio[i].nome, parametro) == 0){
                diretorio[i].pai = 9999;
            }
        }
    }
    return 0;
}
int executarHelp(){
    int tipoDuvida;
    scanf("%i", &tipoDuvida);
    printf("digite o numero referente ao artigo desejado:\n 1->cd\n 2->ls/ls-l\n 3->pwd\n 4->cls\n 5->mkdir\n 6->rmdir\n  ");
    switch (tipoDuvida)
    {
        case 1:
            printf("O comando cd serve para acessar e mudar de diret�rio corrente. Ele � utilizado para a navega��o entre as pastas do computador. Exemplo: cd /home/baixaki/Desktop ? Acessa a pasta correspondente � �rea de trabalho do usu�rio baixaki.");
            break;
        case 2:
            printf("Exibe os arquivos que est�o dentro da pasta na qual o usu�rio est� no momento.Para us�-lo basta digitar ls. Existem varia��es, tais como ls -l, com a qual � poss�vel obter informa��es mais detalhadas sobre os arquivos, como permiss�es e tamanho.");
            break;
        case 3:
            printf("Exibe a pasta atual na qual o usu�rio se encontra. Exemplo: Se o usu�rio baixaki digitar cd ~/ e em seguida digitar pwd, o retorno ser� /home/baixaki .");
            break;
        case 4:
            printf("O cls serve para limpar a tela do terminal. O mesmo ocorre quando se pressiona");
            break;
        case 5:
            printf("Enquanto o rmdir remove, este comando cria diret�rios. Exemplo: mkdir DIRETORIO ? A pasta DIRETORIO foi criada no local onde o usu�rio se encontrava.");
            break;
        case 6:
            printf("Este comando tem a fun��o de  remover diret�rios vazios. Exemplo: rmdir TESTE ? Neste exemplo, o diret�rio vazio TESTE foi removido do local onde o usu�rio se encontrava.");
            break;
        default:
            break;
    }
    return 0;
}

int validarValorDoParametro(char *parametro){
    if(parametro == NULL){
        printf("Erro parametro nao informado \n");
        return 0;
    }else{
        if(strlen(parametro)>8){
            printf("Erro parametro informado e maior que 8 caracteres\n");
            return 0;
        }else{
            return 1;
        }
    }
}

int cd(char *parametro){
    int realizarNavegacao = 0;
    if(validarValorDoParametro(parametro) == 1){
        if(strcmp(parametro, "../") == 0){
            ultimosDiretorios[sizeof(ultimosDiretorios)-1] = 0;
            contadorDiretorios--;
            posicao_atual = ultimosDiretorios[contadorDiretorios];
            realizarNavegacao = 1;
        }else{
            for(int i=0; i < cod_dir; i++){
                if(diretorio[i].pai == posicao_atual && strcmp(diretorio[i].nome, parametro) == 0){
                    ultimosDiretorios[contadorDiretorios] += posicao_atual;
                    contadorDiretorios++;
                    posicao_atual = i;
                    realizarNavegacao = 1;
                }
            }
        }
    }
    if(realizarNavegacao != 1){
        printf("um erro ocorreu ao navegar\n");
    }
    return 0;
}

void ls(char *parametro){
    char *hora = "";
    char *data = "";
    for(int i=0; i < cod_dir; i++){
        if(parametro != NULL){
            if(strcmp(parametro, "-l") != 0){
                printf("sintaxe do comando ls esta errada\n");
                break;
            }
            data = diretorio[i].data;
            hora = diretorio[i].hora;
        }
        if(diretorio[i].pai == posicao_atual){
            printf("-rw-----: %s %s %s \n", diretorio[i].nome, data, hora);
        }
    }
}

int validaSePastaExistePeloPai(char *parametro) {
    int validadorNomeIgual = 0;
    for (int i = 0; i < cod_dir; i++) {
        if (diretorio[i].pai == posicao_atual && strcmp(diretorio[i].nome, parametro) == 0) {
            validadorNomeIgual++;
        }
    }
    if (validadorNomeIgual == 1) {
        printf("Ja existe uma pasta com esse nome\n");
        return 0;
    } else {
        return 1;
    }
}

void mkdir(char *parameter) {
    if (parameter) {
        if (validaSePastaExistePeloPai(parameter) == 1) {
            fflush(stdin);
            strcpy(diretorio[cod_dir].nome, parameter);
            _strdate(diretorio[cod_dir].data);
            _strtime(diretorio[cod_dir].hora);
            diretorio[cod_dir].pai = posicao_atual;
            cod_dir++;
        }
    }
}


void comandos(char *funcao, char *parametro) {
    if (!strcmp(funcao, "mkdir")) {
        mkdir(parametro);

    } else if (!strcmp(funcao, "ls")) {

    } else if(!strcmp(funcao,"cd")){

    }else if(!strcmp(funcao,"rmdir")){

    }else if(!strcmp(funcao,"pwd")){

    }


}


int main() {

    system("clear");
    printf("$ ");
    gets(LinhaDeComando);
    while (strcmp(comando,"poweroff"))
    comando = strtok(LinhaDeComando, "");
    parametro = strtok(NULL, "\0");
    comandos(comando, parametro);


    return 0;

}