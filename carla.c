#include <stdio.h>

#define MAX_VEC 5

void intercambio(int *vector[]);

int main(){
    int vector[MAX_VEC];

    for (int i = 0; i < MAX_VEC; i++){
        printf("Ingresa el numero %d: ", i + 1);
        scanf("%d", &vector[i]);
        //printf("Valor: %d\n", vector[i]);
    }

    intercambio(&vector);

    printf("Vector modificado: ");
    for (int i = 0; i < MAX_VEC; i++) {
        printf("%d ", *(vector + i));  // Equivalente a vector[i]
    }
    printf("\n");
}

void intercambio(int *vector[]){
    int temp = *vector[0];
    for (int i = 0; i < MAX_VEC - 1; i++) {
        *(vector + i) = *(vector + i + 1); 
        //*(vector + i) es igual a vector[i], y *(vector + i + 1) es vector[i + 1]
    }
    *(vector + MAX_VEC - 1) = temp;
}
