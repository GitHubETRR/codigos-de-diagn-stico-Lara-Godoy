#include <stdio.h>
#include <string.h>

#define LIMITE 50
#define MAX_LETRAS 15
#define MAX_PLATOS 3

struct menu_resto{
    char nombre[MAX_PLATOS][LIMITE];
    int precio[MAX_PLATOS];
    int total_platos;
}carnes, ensaladas, pescados, postres;

struct menu_resto parrilla = {{"Lomo", "Vacio"}, {23000, 22800}, 2};
struct menu_resto ensaladas = {{"Cesar", "Nicoise"}, {10800, 8900}, 2};
struct menu_resto pescados = {{"Lenguado", "Bacalao"}, {21800, 19780}, 2};
struct menu_resto postres = {{"Lemonpie", "Ensalada de frutas"}, {11000, 6700}, 2};

//"Choripanes", 19800, "Hamburguesas", 25670
//, "Jardinera", 12300, "Rusa", 7800
//, "Dorado", 20400, "Róbalo", 23450
//, "Helado", 7800, "Brownie", 10000

//promo del 45% en postres
//promo del 15% en parrilla

void imprimir(struct menu_resto plato);
void anadir_plato(char nombre[MAX_LETRAS], int precio, struct menu_resto* seccion);
void eliminar_plato(char nombre[MAX_LETRAS], struct menu_resto* seccion);

int main(){
    int eleccion, seccion, respuesta;
    char nombre[MAX_LETRAS];
    int precio;
    printf("El menu del restaurante: \n");
    printf("\nPlatos de la parrilla: \n");
    imprimir(parrilla);
    printf("\nEnsaladas: \n");
    imprimir(ensaladas);
    printf("\nPescados: \n");
    imprimir(pescados);
    printf("\nPostres: \n");
    imprimir(postres);

    printf("\nBienvenido. Que deseas hacer?: \n");
    printf("1. Anadir un plato. \n");
    printf("2. Eliminar un plato. \n");
    printf("3. Modificar un plato. \n");
    printf("4. Pedir comida. \n");
    printf("5. Resetear archivo. \n");
    printf("6. Salir. \n");
    scanf("%d", &eleccion);
    getchar();

    switch(eleccion){
    case 1:
        printf("A que seccion queres sumarle otro plato?\n");
        printf("1. Parrilla. \n");
        printf("2. Ensaladas. \n");
        printf("3. Pescados. \n");
        printf("4. Postres. \n");
        scanf("%d", &seccion);
        switch(seccion){
        case 1:
            anadir_plato(nombre, precio, &parrilla);
            break;
        case 2:
            anadir_plato(nombre, precio, &ensaladas);
            break;  
        case 3:
            anadir_plato(nombre, precio, &pescados);
            break;
        case 4:
            anadir_plato(nombre, precio, &postres);
            break;
        default:
            printf("No hay tal seccion.");
            break;
        }
        break;

    case 2:
    printf("A que seccion queres eliminarle un plato?\n");
    printf("1. Parrilla.\n");
    printf("2. Ensaladas.\n");
    printf("3. Pescados.\n");
    printf("4. Postres.\n");
    scanf("%d", &seccion);
    getchar();
    printf("Nombre del plato a eliminar: (Escribir tal cual)");
    fgets(nombre, MAX_LETRAS, stdin);
    size_t len = strlen(nombre);
    if (len > 0 && nombre[len - 1] == '\n'){
        nombre[len - 1] = '\0'; 
    }
        switch(seccion){
        case 1:
            eliminar_plato(nombre, &parrilla);
            break;
        case 2:
            eliminar_plato(nombre, &ensaladas);
            break;  
        case 3:
            eliminar_plato(nombre, &pescados);
            break;
        case 4:
            eliminar_plato(nombre, &postres);
            break;
        default:
            printf("No hay tal sección.\n");
            break;
    }
    break;

    case 3:
    printf("Que queres modificar? \nNombre: 1, Precio: 2.");
    scanf("%d", &respuesta);
    if(respuesta==1){
        
    }
    
    default:
        break;
    }
    return 0;
}

void imprimir(struct menu_resto plato){
    for(int i = 0; i < plato.total_platos; i++){
        printf("\n\n    Nombre: %s", plato.nombre[i]);
        printf("\n    Precio: %d", plato.precio[i]);
    }
    printf("\n");
}

void anadir_plato(char nombre[MAX_LETRAS], int precio, struct menu_resto* seccion){
    precio = 0;
    if(seccion->total_platos < MAX_PLATOS){
        printf("Nombre del nuevo plato: ");
        fflush(stdin);
        fgets(nombre, MAX_LETRAS, stdin);
        size_t len = strlen(nombre);
        if (len > 0 && nombre[len - 1] == '\n'){
        nombre[len - 1] = '\0';
        }
        printf("Precio del nuevo plato: ");
        scanf("%d", &precio);

        strcpy(seccion->nombre[seccion->total_platos], nombre);
        seccion->precio[seccion->total_platos] = precio;
        seccion->total_platos++;

        printf("\nEl plato ha sido anadido con exito.\n");
        printf("El nuevo menu del restaurante: \n");
        printf("\nPlatos de la parrilla: \n");
        imprimir(parrilla);
        printf("\nEnsaladas: \n");
        imprimir(ensaladas);
        printf("\nPescados: \n");
        imprimir(pescados);
        printf("\nPostres: \n");
        imprimir(postres);
    }else{
        printf("\nNo se pueden anadir más platos en esta seccion.\n");
    }
}

void eliminar_plato(char nombre[MAX_LETRAS], struct menu_resto* seccion){
    int found = -1;
    // Buscar el plato en la sección
    for(int i = 0; i < seccion->total_platos; i++){ //recorre todos los platos en la seccion
        //Si el nombre del plato actual coincide con el nombre que se quiere eliminar
        if (strcmp(seccion->nombre[i], nombre) == 0){ 
            found = i;
            break;
        }
    }

    if (found != -1){ //si el plato no se encuentra
        for (int i = found; i < seccion->total_platos - 1; i++){ //desplaza los platos una posicion hacia atras
            strcpy(seccion->nombre[i], seccion->nombre[i + 1]);
            seccion->precio[i] = seccion->precio[i + 1];
        }
        seccion->total_platos--; //baja la cantidad de platos
        printf("\nEl plato ha sido eliminado con exito.\n");
    } else {
        printf("\nEl plato no se ha encontrado en la seccion.\n");
    }
}
