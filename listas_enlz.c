
/*punteros no pueden apuntar a nada
antes de cerrar el programa se debe eliminar la memoria*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    //int *p = NULL;
    int *p = (int *) malloc(sizeof(int));
    //int *p = (int *) calloc(5, sizeof(int)); pide 5 enteros

    if (p == NULL){
        printf("Sin memoria.");
        exit(-1);
    }else{
        *p = 54232;
        printf("%d", *p);
        free(p); //liberar memoria
    }

    return 0;
}

//void *malloc (size_t size); 
//recibe en bits lo que se pide, 
//devuelve un puntero a void para que se pueda adaptar a cualquier tipo que le pidamos (char, int, etc)/*