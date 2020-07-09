#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

/*Felipe de Almeida Florencio 201110006160*/


void chamadaSistema (char** parametros){
    int flagEstado;


    if(strcmp(parametros[0], "cd") == 0){

        flagEstado = chdir(parametros[1]);
        if(flagEstado == -1)
            printf("cd: %s: Arquivo ou diretorio nao encontrado\n", parametros[1]);
    }
    else{
        if(fork() == 0){
            flagEstado = execvp(parametros[0], parametros);  //processo filho
            if(flagEstado != 0){
                printf("%s: comando nao encontrado\n", parametros[0]);
                exit(1);
             }
        }
        else
            wait(NULL);  //aguarda fim do processo pai
    }
}

void separarString (char** parametros, char* entrada){
    int j=0; int i=0;
    for (int iEntrada=0; entrada[iEntrada] !='\0' && j<4; iEntrada++){
       if (entrada[iEntrada] == 32){  /* quando encontrar um espaço, muda o parametro alterando o j*/
          parametros[j][i]='\0';
          j++;
          i=0;
       }
       else {
         parametros[j][i] = entrada [iEntrada];
         i++;
       }
    }

    while (j<4){
      j++;
      parametros[j]=0;
    }


}

int main(void)
{
    char* entrada= (char*) malloc(50 * sizeof(char));
    char** parametros = (char**) malloc(4 * sizeof(char*));

    for(int iParametro=0; iParametro<4; iParametro++){
      parametros[iParametro] = (char*) malloc(50*sizeof(char));
    }
    while (strcmp(entrada, "exit")!=0){
        printf("> ");
        scanf("%[^\n]s", entrada);
        setbuf(stdin, NULL);
        if (strcmp(entrada, "exit")==0)
            return 0;
        separarString(parametros, entrada);
        chamadaSistema(parametros);
    }
    return 0;
}

