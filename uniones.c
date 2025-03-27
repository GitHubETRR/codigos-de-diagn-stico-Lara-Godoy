#include <stdio.h>

#define CANT_VEC 4
//las variables comparten la misma direccion de inicio en la union

union{
    float valor;
    unsigned char bytes[CANT_VEC];
}var;

void impr_bin(unsigned char byte);

int main(){
    printf("En Decimal: ");
    scanf("%f", &var.valor);

    printf("En Hexadecimal (IEEE 754): 0x");
    for (int i = CANT_VEC - 1; i >= 0; i--){
        printf("%02x",var.bytes[i]);
    }

    printf("\nEn Binario (IEEE 754): ");
    for (int i = CANT_VEC - 1; i >= 0; i--){
        impr_bin(var.bytes[i]);
    }

    printf("\n    Signo:      "); 
    impr_bin(var.bytes[3] >> 7);
    //bytes[3] tiene el signo y parte del exp, se desplazan 7 bits para que quede el MSB (el signo)

    printf("\n    Exponente:  ");
    for (int i = 6; i >= 0; i--) { printf("%d", (var.bytes[3] >> i) & 1); }
    //los otros 6 bits (LSB) de bytes[3] 
    for (int i = 7; i >= 4; i--) { printf("%d", (var.bytes[2] >> i) & 1); }
    //bytes[2] tiene los otros 4 bits del exp y los 4 bits MSB de la mantisa

    printf("\n    Mantisa:    ");
    for (int i = 3; i >= 0; i--) { printf("%d", (var.bytes[2] >> i) & 1); }
    //imprime los primeros 4 bits de la mantisa
    for (int i = 1; i >= 0; i--) { impr_bin(var.bytes[i]); }
    //imprime los dos ultimos 2 bits de la mantisa
    printf("\n");

    return 0; 
}

void impr_bin(unsigned char byte){
    //empieza con MSB
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1); //mueve los bits a la derecha
    }
}