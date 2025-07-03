#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TXT_MAX 50
#define ID_CARAC 3
#define DESCRIP_CARAC 13
#define ESTADO_CARAC 7

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

//arreglar descripcion de tareas del file

void agregar_tarea(Tarea **lista, int *contador); 
void mostrar_tareas(Tarea *lista);
void imprimir_tarea(Tarea *tarea); 
void marcar_tarea(Tarea **lista);
void eliminar_tarea(Tarea **lista, int id); //agregar para borrar en el file
void mostrar_tareas_f(); //tareas que quedaron en el file
void guardar_tareas_f(); 
int id_archivo();
void cargar_tareas_f(Tarea **lista); //las carga antes de que se ponga el menu
void guardar_tareas_f(Tarea *lista); //las guarda en el file
void liberar_lista(Tarea *lista);


int main(){
    int eleccion;    
    int contador_id = id_archivo() + 1;
    Tarea *lista = NULL; 
    cargar_tareas_f(&lista);
    mostrar_tareas(lista);
    do{
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Agregar una nueva tarea.\n");
        printf("2. Mostrar todas las tareas.\n");
        printf("3. Marcar tarea como completada.\n");
        printf("4. Salir.\n\n");
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
            guardar_tareas_f(lista);
            liberar_lista(lista);
            printf("Chau.");
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
            free(nueva); //aca si se necesita el free porque malloc para 'nueva' si funciono
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
    printf("ID: %d\n", tarea->id);
    printf("Descripcion: %s\n", tarea->descrip);
    printf("Estado: %s\n", tarea->estado == PENDIENTE ? "Pendiente" : "Completada");
    //op ternario: (condición) ? (valor_si_verdadero) : (valor_si_falso)
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
            }
            printf("Queres eliminar esta tarea de la lista? 1 = Si, 0 = No: ");
                scanf("%d", &respuesta);
                if (respuesta == 1){
                    eliminar_tarea(lista, id_tarea_completa);
                }
            return;
        }
        actual = actual->siguiente;
    }
    printf("No se encontro ninguna tarea con ID %d.\n", id_tarea_completa);
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

int id_archivo(){
    FILE *archivo = fopen("pilar_tareas.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 0;
    }

    int max_id = 0;
    char linea[TXT_MAX];

    while (fgets(linea, TXT_MAX, archivo)) {
        if (strncmp(linea, "ID:", ID_CARAC) == 0) { 
            //compara los primeros 3 caracteres de la linea con "ID:"
            int id;
            sscanf(linea, "ID: %d", &id); //guarda el ID encontrado en id
            if (id > max_id) {
                max_id = id;
            }
        }
    }
    fclose(archivo);
    return max_id;
}

void cargar_tareas_f(Tarea **lista){
    FILE *archivo = fopen("pilar_tareas.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    char linea[TXT_MAX];
    int id = 0;
    char estado_str[TXT_MAX];
    char descripcion[TXT_MAX];
    descripcion[0] = '\0';  // limpio el buffer al inicio

    while (fgets(linea, TXT_MAX, archivo)) {
        if (strncmp(linea, "ID:", ID_CARAC) == 0) {
            sscanf(linea, "ID: %d", &id);
        } else if (strncmp(linea, "Descripcion:", 11) == 0) {
            char *ptr = strchr(linea, ':');
            //busca al : y devuelve un puntero a esa posicion, sino da NULL
            if (ptr != NULL && *(ptr + 1) != '\0') { //que : exista y que despues de : haya algo
                ptr++; //avanza después del :
                while (*ptr == ' ') ptr++; //salta espacios
                strncpy(descripcion, ptr, TXT_MAX - 1);
                //copia desde ptr hasta TXT_MAX - 1
                descripcion[TXT_MAX - 1] = '\0'; //deja la string terminada en \0
                descripcion[strcspn(descripcion, "\n")] = '\0';
                //strcspn busca la 1ra posicion donde aparece un salto de linea y devuelve donde esta
                //se iguala a \0 para evitar que queden saltos de linea ocultos al final de la descripcion
            } else {
                descripcion[0] = '\0'; //sino hay : o no hay nada despues, la descripcion queda vacia
            }
        } else if (strncmp(linea, "Estado:", ESTADO_CARAC) == 0) {
            sscanf(linea, "Estado: %s", estado_str);

            Tarea *nueva = (Tarea *)malloc(sizeof(Tarea));
            if (nueva == NULL) {
                printf("Sin memoria.\n");
                fclose(archivo);
                return;
            }

            nueva->id = id;
            nueva->descrip = strdup(descripcion);
            nueva->estado = strcmp(estado_str, "Pendiente") == 0 ? PENDIENTE : COMPLETADA;
            nueva->siguiente = NULL;

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
    fclose(archivo);
}

void guardar_tareas_f(Tarea *lista){
    FILE *archivo = fopen("pilar_tareas.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar.\n");
        return;
    }

    while (lista != NULL) {
        fprintf(archivo, "ID: %d\n", lista->id);
        fprintf(archivo, "Descripcion: %s\n", lista->descrip);
        fprintf(archivo, "Estado: %s\n\n", lista->estado == PENDIENTE ? "Pendiente" : "Completada");
        lista = lista->siguiente;
    }
    fclose(archivo);
}

void liberar_lista(Tarea *lista){
    Tarea *actual = lista;
    while (actual != NULL){
        Tarea *siguiente = actual->siguiente;
        free(actual->descrip);
        free(actual);
        actual = siguiente;
    }
}