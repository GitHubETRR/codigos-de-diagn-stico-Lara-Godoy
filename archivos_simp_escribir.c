#include <stdio.h>

int main() {
    FILE *archivo = fopen("archivos_simp_ejem.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    fprintf(archivo, "Hola lara!\n");
    fprintf(archivo, "Guardando datos en C\n");

    fclose(archivo);
    return 0;
}
