#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TXT_MAX 50

typedef enum{
    PENDIENTE,
    COMPLETADA
}Estado;

typedef enum{
    AGREGAR=1,
    MOSTRAR,
    MARCAR,
    SALIR
}opciones_t;

typedef struct nota{
    int id;
    char *descrip;
    Estado estado;              //variable dentro de la struct de estado
    struct nota *siguiente;    //esta tarea contiene la dirección hacia la prox tarea
} Tarea;

void agregar_tarea(Tarea **lista, int *contador); //arreglar el orden de ID
void mostrar_tareas(Tarea *lista); //tambien tiene que leer las del archivo
void imprimir_tarea(Tarea *tarea); 
void marcar_tarea(Tarea **lista);
void eliminar_tarea(Tarea **lista, int id); //agregar para borrar en el file
void mostrar_tareas_f(); //tareas que quedaron en el file
void guardar_tareas_f(); 


int main(){
    int eleccion;    
    int contador_id = 1;
    Tarea *lista = NULL; 
    mostrar_tareas_f();
    do{
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Agregar una nueva tarea.\n");
        printf("2. Mostrar todas las tareas.\n");
        printf("3. Marcar tarea como completada.\n");
        printf("4. Salir.\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &eleccion);

        switch (eleccion){
        case AGREGAR:
            agregar_tarea(&lista, &contador_id);
            break;
        case MOSTRAR:
            mostrar_tareas(lista);
            break;
        case MARCAR:
            marcar_tarea(&lista);
            break; 
        case SALIR:
            printf("elegiste SALIR");
            //guardar_tareas()
            break;
        }  
    } while (eleccion != SALIR);
}

void agregar_tarea(Tarea **lista, int *contador){ 
    //se pasa contador como puntero para poder incrementarlo desde adentro de la funcion
    //Tarea *lista pasa una copia del puntero
    //Tarea **lista puede editar el puntero en main

    Tarea *nueva = (Tarea *) malloc(sizeof(Tarea));
    if (nueva == NULL){
        printf("Sin memoria.");
        exit(-1);
    }else{
        nueva->id = (*contador)++; //se usa como puntero para cambiar su valor
        //primero se asigna a la tarea el valor actual de *contador y despues se incrementa
        nueva->estado = PENDIENTE;
        nueva->siguiente = NULL; //como se esta creando una tarea, no hay prox aun, asi que se pone NULL

        nueva->descrip = (char *)malloc(TXT_MAX * sizeof(char));
        if (nueva->descrip == NULL) {
            printf("Sin memoria.");
            free(nueva); //aca si se necesita el free porque malloc para 'nueva' sí funcionó
            exit(-1);
        }
        printf("Ingrese la descripcion de la tarea: ");
        while (getchar() != '\n'); // limpia TODO el buffer para que fgets ande bien
        fgets(nueva->descrip, TXT_MAX, stdin); //lee toda una linea 
        //fgets(lugar donde se guarda, max de caracteres, indica que se lee desde el teclado)
        nueva->descrip[strcspn(nueva->descrip, "\n")] = '\0';
        /*ejemplo:
        se ingresa: estudiar matematica
        fgets       --> estudiar matematica\n\0
        strcspn     --> encuentra el \n y lo reemplaza con \0
        resultado   --> estudiar matematica\0 */

        if (*lista == NULL) {
            *lista = nueva;
        } else {
            Tarea *actual = *lista;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nueva;
        }
        
    }
}

void mostrar_tareas(Tarea *lista){
    if (lista == NULL) {
        printf("No hay tareas para mostrar.\n");
        return;
    }
    
    while (lista != NULL) {
        imprimir_tarea(lista);
        lista = lista->siguiente;
    }    
}

void imprimir_tarea(Tarea *tarea){
    printf("\n--------------------\n");
    printf("ID: %d\n", tarea->id);
    printf("Descripcion: %s\n", tarea->descrip);
    printf("Estado: %s\n", tarea->estado == PENDIENTE ? "Pendiente" : "Completada");
    //op ternario: (condición) ? (valor_si_verdadero) : (valor_si_falso)
    printf("--------------------\n");
}

void marcar_tarea(Tarea **lista){
    int id_tarea_completa = 0;
    int respuesta = 0;
    if (lista == NULL) {
        printf("No hay tareas cargadas.\n");
        return;
    }
    printf("Ingrese el ID de la tarea que desea marcar como completada: ");
    scanf("%d", &id_tarea_completa);

    Tarea *actual = *lista;
    //se crea una copia del puntero para recorrer sin perder los datos 
    while (actual != NULL){
        if (actual->id == id_tarea_completa) {
            if (actual->estado == COMPLETADA) {
                printf("La tarea ID %d ya estaba marcada como completada.\n", id_tarea_completa);
            } else {
                actual->estado = COMPLETADA;
                printf("Tarea ID %d, %s marcada como completada con exito.\n", id_tarea_completa, actual->descrip);
                
                printf("Queres eliminar esta tarea de la lista? 1 = Si, 0 = No");
                scanf("%d", &respuesta);
                if (respuesta == 1){
                    eliminar_tarea(lista, id_tarea_completa);
                }
            }
            return;
        }
        actual = actual->siguiente;
    }
    printf("No se encontró ninguna tarea con ID %d.\n", id_tarea_completa);
}

void eliminar_tarea(Tarea **lista, int id_marcar){
    if (*lista == NULL) { //si la COPIA del puntero es NULL
        printf("No hay tareas para eliminar.\n");
        return;
    }

    Tarea *actual = *lista;
    Tarea *anterior = NULL;

    while (actual != NULL) {
        if (actual->id == id_marcar) {
            if (anterior == NULL) {
                *lista = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente; //no es el primer nodo
            }
            free(actual->descrip);
            free(actual);
            printf("Tarea ID %d eliminada con exito.\n", id_marcar);
            return;
        }
        anterior = actual;          //apunta al anterior
        actual = actual->siguiente; //apunta al siguente del anterior
    }
    printf("No se encontro ninguna tarea con ID %d para eliminar.\n", id_marcar);
}

void mostrar_tareas_f(){
    FILE *archivo = fopen("pilar_tareas.txt", "r");
    char linea[TXT_MAX];

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("Tareas cargadas anteriormente: \n");
    while (fgets(linea, TXT_MAX, archivo)) {
        printf("%s", linea);
    }

    printf("\n");
    fclose(archivo);
}