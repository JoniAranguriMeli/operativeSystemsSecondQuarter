#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

int validarParametros(int arg, char *args[]){
    if(arg!=3){
        return 1;
    }

    struct stat myFile;
    if (stat(args[1], &myFile) < 0) {
        printf("\nno se encontro el archivo: %s\n", args[1]);
        return 1;
    }
     if (stat(args[2], &myFile) < 0) {
        printf("\nno se encontro el fifo: %s \n", args[1]);
        printf("\n Debe ejecutar el proceso demonio primero\n");
        return 1;
    }
    

    return 0;

}
void mostrarAyuda(){
    printf("\n Ejemplo de Ejecucion: ./consumir ./articulos.txt ./fifoResultado \n");
    return ;
}
int obtenerCantidadDeRegistros(char *path[]){
    FILE *pf;
    int cantfilas=0;
    pf=fopen(*path,"r");
    if(!pf){
        printf ("no se encuentra el archivo");
        exit(0);
    }
    char fila[100];
    while(!feof(pf)){
        fscanf(pf," %[^\n]",fila);
      	cantfilas++;
	}
    fclose(pf);
    return cantfilas;

}
int main (int arg , char * args[]){
 if(arg== 2 && (strcmp(args[1],"-h")==0 ||strcmp(args[1],"-?")==0 || strcmp(args[1],"-help")==0)  ){
      
        mostrarAyuda();
        
        return 0;
    }
    if(validarParametros(arg, args)==1)
    return 1;
    

    int fd= open(args[1],O_RDONLY); // abrir fifo para lectura
        
        
        int registros=obtenerCantidadDeRegistros(&args[1]);
       
    char entrada[registros*500];
    int bytes=-1;
     bytes= read(fd,entrada,sizeof(entrada));   // leer fifo
        printf("\n************SALIDA****\n");
  //  close(fd);
            //  printf("soy el hijo y  es %d ", num);
         printf("\n %s\n ",entrada); 

return 0;
}