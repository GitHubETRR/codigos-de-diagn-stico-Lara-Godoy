#include <stdio.h>

int main() {
    FILE *archivo = fopen("archivos_simp_ejem.txt", "r");
    char linea[100];

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    while (fgets(linea, 100, archivo)) {
        printf("Linea: %s", linea);
    }

    fclose(archivo);
    return 0;
}
