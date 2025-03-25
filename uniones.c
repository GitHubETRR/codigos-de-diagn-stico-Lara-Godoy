#include <stdio.h>

//union num{
    /*char byte1;
    char byte2;
    char byte3;
    char byte4;*/

    //short int intvar;
    //char charvar;
//}var;

//las variables comparten la misma direccion de inicio en la union

union{
    float valor;
    unsigned char bytes[4];
    }var;

//int main(){
    /*var.byte1=10
    var.byte2=20
    printf("%d", var.byte1);
    printf("%d", var.byte2);*/

    //var.intvar = 0x1234;
    //printf("0x%x", var.intvar);
    //return 0;
//}

int main(){
    var.valor=-15;
    printf("0x%x",var.bytes[0]);
    printf("0x%x",var.bytes[1]);
    printf("0x%x",var.bytes[2]);
    printf("0x%x",var.bytes[3]);
}
