#include <stdio.h>
#include <stdbool.h>

#define TAM_TXT 15
#define LIBRE 0
#define VENDIDO 1
#define CANT_ASIENTOS (COLUMNAS*FILAS)
#define COLUMNAS 4
#define FILAS 2
#define OCUPADO 'x'
#define DESOCUPADO ' '
#define PRECIO_ASIENTO 1000

typedef struct {
    int dia;
    int mes;
    int anio;
} fecha_venta_t;

typedef struct {
    char nombre[TAM_TXT];
    char apellido[TAM_TXT];
    fecha_venta_t fecha_venta;
    bool estado;  		// Estado: DISPONIBLE (0) o VENDIDO (1)	
} reservas_t;      

int mostrar_disponibles(int avion[FILAS][COLUMNAS]);
void graficar_matrix(int mat[FILAS][COLUMNAS]);
int elegir_asiento(reservas_t asientos[FILAS][COLUMNAS], int avion[FILAS][COLUMNAS]);
int pedir_datos_fila();
int pedir_datos_columna();

int total_recaudado = 0;

int main(){
    int avion[FILAS][COLUMNAS];
    reservas_t asientos[FILAS][COLUMNAS] = {0};
    reservas_t asiento;
    fecha_venta_t vendido;
    int resp, respuesta, eleccion;
    int disponibles = 0;

    for(int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            avion[i][j] = DESOCUPADO;
        }
    }

    do{
        printf("\nBienvenido. Que deseas hacer?: \n");
        printf("1. Ver disponibles. \n");
        printf("2. Elegir un asiento. \n");
        printf("3. Saber sobre los asientos ya vendidos. \n");
        printf("4. Salir (Cerrar ventas). \n");
        scanf("%d", &eleccion);
        switch(eleccion){
        case 1: 
            disponibles = mostrar_disponibles(avion); 
            printf("Hay %d de %d asientos libres.\n", disponibles, CANT_ASIENTOS);
            graficar_matrix(avion);
            break;
        case 2: 
            elegir_asiento(asientos, avion); 
            disponibles = mostrar_disponibles(avion);  
            printf("Ahora hay %d de %d asientos libres.\n", disponibles, CANT_ASIENTOS);
            graficar_matrix(avion);
            break;
        case 3:
            printf("\nAsientos reservados:\n"); //ARREGLAR
            for (int i = 0; i < FILAS; i++) {
                for (int j = 0; j < COLUMNAS; j++) {
                    if (asientos[i][j].estado == VENDIDO) {
                        printf("Asientos reservados por %s %s. ",
                        asientos[i][j].nombre, asientos[i][j].apellido);
                        printf("Fecha de compra: %02d/%02d/%d.\n",
                        asientos[i][j].fecha_venta.dia, asientos[i][j].fecha_venta.mes, asientos[i][j].fecha_venta.anio);
                    }
                }
            }
            break;
        case 4:
            printf("Recaudado total: %d$\n", total_recaudado);
            break;
        default:
            break;
        }
    } while (eleccion != 4);
    return 0;
    }

int mostrar_disponibles(int avion[FILAS][COLUMNAS]){
    int disp = 0;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (avion[i][j] == DESOCUPADO) {
                disp++;
            }
        }
    }
    return disp;
}

void graficar_matrix(int mat[FILAS][COLUMNAS]){
    printf("\n ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");
    for (int i = 0; i < FILAS; i++) {
        printf("%2d", i + 1);
        for (int j = 0; j < COLUMNAS; j++) {
            printf("|%c|", mat[i][j]);
        }
        printf("\n");
    }
}

int pedir_datos_fila(){
    int fila;
    do {
        printf("Fila: ");
        scanf("%d", &fila);
        fila--;
    } while (fila < 0 || fila >= FILAS);
    return fila;
}

int pedir_datos_columna(){
    int columna;
    do {
        printf("Columna: ");
        scanf("%d", &columna);
        columna--;
    } while (columna < 0 || columna >= COLUMNAS);
    return columna;
}

int elegir_asiento(reservas_t asientos[FILAS][COLUMNAS], int avion[FILAS][COLUMNAS]) {
    int asientos_requeridos, fila = 0, columna = 0;
    char nombre[TAM_TXT];
    char apellido[TAM_TXT];
    fecha_venta_t fecha;

    printf("Cuantos asientos quieres reservar?: ");
    scanf("%d", &asientos_requeridos);

    if (asientos_requeridos > 0 && asientos_requeridos <= CANT_ASIENTOS) {
        int gasto = asientos_requeridos * PRECIO_ASIENTO;

        while (asientos_requeridos > 0){
            graficar_matrix(avion);
            fila = pedir_datos_fila();
            columna = pedir_datos_columna();

            if (avion[fila][columna] == DESOCUPADO) {
                avion[fila][columna] = OCUPADO;
                asientos[fila][columna].estado = VENDIDO;

                // Copiar datos del asiento [0][0] al nuevo asiento elegido
                //snprintf(destino, tamaño, "formato", fuente);
                //snprintf(asientos[fila][columna].nombre, TAM_TXT, "%s", asientos[0][0].nombre);
                //snprintf(asientos[fila][columna].apellido, TAM_TXT, "%s", asientos[0][0].apellido);
                
                printf("Ingrese su nombre: ");
                scanf("%s", asientos[fila][columna].nombre);
                printf("Ingrese su apellido: ");
                scanf("%s", asientos[fila][columna].apellido);
                printf("Ingrese el dia de la venta: ");
                scanf("%d", &asientos[fila][columna].fecha_venta.dia);
                printf("Ingrese el mes de la venta: ");
                scanf("%d", &asientos[fila][columna].fecha_venta.mes);
                printf("Ingrese el anio de la venta: ");
                scanf("%d", &asientos[fila][columna].fecha_venta.anio);

                asientos_requeridos--;
                printf("Asiento [%d, %d] reservado con exito.\n", fila + 1, columna + 1);
                graficar_matrix(avion);
            } else {
                printf("Ocupado. Intenta de nuevo.\n");
            }
        }
        printf("Gasto total de esta compra: %d\n", gasto);
        total_recaudado += gasto;
    } else {
        printf("No hay tanta cantidad de asientos.\n");
    }
    return 0;
}

