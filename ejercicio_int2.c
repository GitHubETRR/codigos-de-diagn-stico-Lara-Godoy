#include <stdio.h>
#include <string.h>

#define LIMITE_TXT 15
#define MAX_EMPLEADOS 5

typedef struct {
    char nombre[LIMITE_TXT];
    int edad;
    int salario;
} Empleado;

void mostrar_datos(Empleado empleados[], float cant_emp);
void ingresar_datos(Empleado empleados[], float cant_emp);
void procesar_datos(Empleado empleados[], float cant_emp);

int main() {
    int respuesta;
    int eleccion;
    float cant_emp = 0;
    Empleado empleados[MAX_EMPLEADOS] = {0};

    do {
        printf("Quieres usar el programa? (1=Si, 0=No): ");
        scanf("%d", &respuesta);
        if (respuesta != 1 && respuesta != 0) {
            printf("Opcion no valida. Intenta nuevamente.\n");
        }
    } while (respuesta != 1 && respuesta != 0);

    if (respuesta == 1) {
        do {
            printf("\n--- Menu ---\n");
            printf("1. Ingresar datos.\n");
            printf("2. Procesar y mostrar.\n");
            printf("3. Salir.\n");
            printf("Selecciona una opcion: ");
            scanf("%d", &eleccion);

            switch (eleccion) {
                case 1:
                    printf("Cuantos empleados quieres ingresar? (max. %d): ", MAX_EMPLEADOS);
                    scanf("%f", &cant_emp);
                    if (cant_emp > 0 && cant_emp <= MAX_EMPLEADOS) {
                        ingresar_datos(empleados, cant_emp);
                    } else {
                        printf("Numero invalido de empleados.\n");
                    }
                    break;

                case 2:
                    procesar_datos(empleados, cant_emp);
                    break;

                case 3:
                    printf("Hasta luego.\n");
                    respuesta = 0;
                    break;

                default:
                    printf("Opcion no valida. Intenta nuevamente.\n");
                    break;
            }
        } while (respuesta == 1);
    } else {
        printf("Programa terminado.\n");
    }
    return 0;
}

void mostrar_datos(Empleado empleados[], float cant_emp) {
    printf("\n--- Info de empleados ---\n");
    for (int i = 0; i < cant_emp; i++) {
        printf("Empleado: %d\n", i + 1);
        printf("Nombre: %s, ", empleados[i].nombre);
        printf("Edad: %d, ", empleados[i].edad);
        printf("Salario: %d\n", empleados[i].salario);
    }
}

void ingresar_datos(Empleado empleados[], float cant_emp) {
    for (int i = 0; i < cant_emp; i++) {
        printf("\nEmpleado %d:\n", i + 1);
        printf("Ingrese el nombre: ");
        while (getchar() != '\n');  
        fgets(empleados[i].nombre, LIMITE_TXT, stdin);
        empleados[i].nombre[strcspn(empleados[i].nombre, "\n")] = 0;  // sacar el salto de línea

        printf("Ingrese la edad: ");
        scanf("%d", &empleados[i].edad);
        printf("Ingrese el salario: ");
        scanf("%d", &empleados[i].salario);
    }
}

void procesar_datos(Empleado empleados[], float cant_emp){
    float salario_total = 0;
    int indice_mayor = 0;
    float promedio;
    for (int i = 0; i < cant_emp; i++){
        salario_total += empleados[i].salario;
    }
    promedio = salario_total / cant_emp;
    printf("\n\nPromedio de salarios: %.2f\n", promedio);

    for (int i = 1; i < cant_emp; i++) {
        if (empleados[i].salario > empleados[indice_mayor].salario) {
            indice_mayor = i; 
        }
    }
    printf("\nEl empleado con el mayor salario es %s con  %.2f $\n", empleados[indice_mayor].nombre, (float)empleados[indice_mayor].salario); 
    //(float) pasa de int a float
}
