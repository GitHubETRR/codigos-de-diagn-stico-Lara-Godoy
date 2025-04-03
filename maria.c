#include <stdio.h>

void duplicar (int *num);

int main(){
    int valor;

    printf("Ingrese un numero: ");
    scanf("%d", &valor);

    duplicar(&valor); // pasa la dirección de memoria de valor

    printf("El valor duplicado es: %d", valor);
}

void duplicar (int *num){
    *num *= 2;
}