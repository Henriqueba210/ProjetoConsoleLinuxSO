#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Diretorio{
    char nome[8];
    char hora[9];
    char data[9];
    int pai;

};
struct Diretorio diretorio[1024];
char linhaDeComando[80];
char *comando, *parametro, *nomeAtual;
int comandoExistente = 0, posicao_atual = 0, cod_dir = 1, ultimosDiretorios[1024], contadorDiretorios;

//Fun��es de segundo uso
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
int validarSeExisteOmesmoNomePeloPai(char* parametro){
    int validadorNomeIgual = 0;
    for(int i = 0; i < cod_dir; i++){
        if(diretorio[i].pai == posicao_atual && strcmp(diretorio[i].nome, parametro) == 0){
            validadorNomeIgual++;
        }
    }
    if(validadorNomeIgual == 1){
        printf("Ja existe um diretorio com esse nome\n");
        return 0;
    }else{
        return 1;
    }
}


// fun��es de primeiro uso
int inicializarPrograma(){
    printf("Bem vindo ao criador de Diretorios\n");
    comando = "";
    memcpy(diretorio[0].nome, "./", strlen("./")+1);
    _strdate(diretorio[0].data);
    _strtime(diretorio[0].hora);
    diretorio[0].pai = 0;
    return 0;
}
int executarMostragemDeDiretorio(){
    if(posicao_atual > 0){
        int indexDir = diretorio[posicao_atual].pai;
        for(int i = 0; i < cod_dir; i++){
            if(indexDir != 0){
                printf("/%s",diretorio[indexDir].nome);
                indexDir = diretorio[indexDir].pai;
            }
        }
        printf("/%s$ ",diretorio[posicao_atual].nome);
    }
    return 0;
}
int executarMkdir(char *parametro){
    if(validarValorDoParametro(parametro) == 1){
        if(validarSeExisteOmesmoNomePeloPai(parametro) == 1){
            fflush(stdin);
            strcpy(diretorio[cod_dir].nome, parametro);
            _strdate(diretorio[cod_dir].data);
            _strtime(diretorio[cod_dir].hora);
            diretorio[cod_dir].pai = posicao_atual;
            cod_dir++;
        }
    }
    return 0;
}
int executarLs(char *parametro){
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
    return 0;
}
int executarCd(char *parametro){
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

int main (){
    inicializarPrograma();
    while(strcmp(comando, "powerOff") != 0){
        printf("#root~");
        executarMostragemDeDiretorio();
        gets(linhaDeComando);
        comando = strtok(linhaDeComando, " ");
        parametro = strtok(NULL, "\0");
        if(strcmp(comando, "mkdir")==0){
            executarMkdir(parametro);
            comandoExistente = 1;
        }
        if(strcmp(comando, "ls")==0){
            executarLs(parametro);
            comandoExistente = 1;
        }        
        if(strcmp(comando, "cd")==0){
            executarCd(parametro);
            comandoExistente = 1;
        }
        if(strcmp(comando, "rmdir")==0){
            executarRmdir(parametro);
            comandoExistente = 1;
        }
        if(strcmp(comando, "pwd")==0){
            printf("Voce esta no diretorio %s\n", diretorio[posicao_atual].nome);
            comandoExistente = 1;
        }
        if(strcmp(comando, "help")==0){
            executarHelp();
            comandoExistente = 1;
        }
        if(strcmp(comando, "powerOff")==0){
            comandoExistente = 1;
        }
        if(strcmp(comando, "date")==0){
            char dataAgora[9];
            char horaAgora[9];
            _strdate(dataAgora);
            _strtime(horaAgora);
            printf("%s %s \n", dataAgora, horaAgora);
            comandoExistente = 1;
        }
        if(strcmp(comando, "cls")==0){
            system("cls");
            comandoExistente = 1;
        }
        if(comandoExistente == 0){
            printf("Comando %s Inexistente\n", comando);
        }
        comandoExistente = 0;
    }
    return 0;
}
