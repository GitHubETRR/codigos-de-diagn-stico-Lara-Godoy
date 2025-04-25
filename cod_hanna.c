#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT 30

typedef struct alum {
	char nombre[CANT];
	char apellido[CANT];
	int promedio;
	struct alum *next;
} alum_t;

void imprimir(alum_t *);
alum_t * agregar_alumno(alum_t *lista);
alum_t * mayor(alum_t *lista);
alum_t * menor(alum_t *lista);
float promgen(alum_t *lista);
alum_t * buscar(alum_t *lista, char *nombre, char *apellido);
void liberar (alum_t *lista);


int main() {
	alum_t *_6TEL=NULL;
	int opcion, accion, res;
	/*Inicialmente se veia asi
	alum_t *alu_ptr=(alum_t *) malloc(sizeof(alum_t));
	_6TEL=alu_ptr;
	alu_ptr->next=NULL;
	strcpy((*alu_ptr).nombre, "Haa"); //o usamos el operador ->
	strcpy(alu_ptr->apellido, "hoo");
	//alum_t alum1={"Haaa","hoo"}; esto era como lo haciamos antes*/
	do {
	    do{
            printf("Que desea hacer?\n1. Agregar alumno\n2. Imprimir lista\n3. Ver mayor promedio\n");
            printf("4. Ver menor promedio\n5. Promedio general\n6. Buscar por nombre y apellido\n-->");
            scanf("%d",&accion);
            if(accion>6 || accion<1){
                printf("¡¡Accion invalida!!\n\n");
                while (getchar() != '\n');
            }
	    } while(accion>6 || accion<1);
		switch(accion) {
		case 1:
			do {
                printf("\nAgrege alumno:\n");
				_6TEL = agregar_alumno(_6TEL);
				printf("Desea agregar otro alumno? (1: Si, 0: No): ");
				scanf("%d", &opcion);
			} while (opcion == 1);
			break;
		case 2:
			printf("\nLista de alumnos:\n");
			imprimir(_6TEL);
			break;
		case 3:
			alum_t *promayor=mayor(_6TEL);
			printf("\nMayor promedio: %d", promayor->promedio);
			printf("\nNombre: %s \nApellido: %s\n", promayor->nombre, promayor->apellido);
			break;
		case 4:
			alum_t *promenor=menor(_6TEL);
			printf("\nMenor promedio: %d", promenor->promedio);
			printf("\nNombre: %s \nApellido: %s\n", promenor->nombre, promenor->apellido);
			break;
		case 5:
			float genpro=promgen(_6TEL);
			printf("\nPromedio general: %.2f", genpro);
			break;
		case 6:
            char nom_bus[CANT], ap_bus[CANT];
            printf("\nNombre a buscar--> ");
            scanf("%s", &nom_bus);
            printf("Apellido a buscar--> ");
            scanf("%s", &ap_bus);
            alum_t *encontrado=buscar(_6TEL, nom_bus, ap_bus);
            if(encontrado){
                printf("\n¡¡Alumno encontrado!!");
                printf("\nNombre: %s \nApellido: %s\nPromedio: %d", encontrado->nombre, encontrado->apellido, encontrado->promedio);
            }
            else printf("\n¡¡Alumno no encontrado!!\n");
            break;
		default:
			printf("\nNumero ingresado incorrecto");
		}
		printf("\nDesea seguir operando? (0: No): ");
		scanf("%d", &res);
	} while(res!=0);
	liberar(_6TEL);
	return 0;
}

void imprimir(alum_t *lista) {
	while(lista!=NULL) {
		printf("---------------------\n");
		printf("Nombre: %s\n", (*lista).nombre);
		printf("Apellido: %s\n", lista->apellido);
		printf("Promedio: %d\n", lista->promedio);
        printf("---------------------\n");
		lista=lista->next;
	}
}

alum_t *agregar_alumno(alum_t *lista) {
	alum_t *alu_ptr=(alum_t *) malloc(sizeof(alum_t));
	alu_ptr->next=lista;
	printf("Nombre: ");
	scanf("%s", alu_ptr->nombre);
	printf("Apellido: ");
	scanf("%s", alu_ptr->apellido);
	printf("Promedio: ");
	scanf("%d", &alu_ptr->promedio);
	lista=alu_ptr;
	printf("Alumno creado exitosamente\n");
	return lista;
}

alum_t *mayor(alum_t *lista) {
	if(lista==NULL) return NULL;
	alum_t *max=lista;
	while(lista!=NULL) {
		if(lista->promedio>max->promedio) max=lista;
		lista=lista->next;
	}
	return max;
}
alum_t *menor(alum_t *lista) {
	if(lista==NULL) return NULL;
	alum_t *men=lista;
	while(lista!=NULL) {
		if(lista->promedio<men->promedio) men=lista;
		lista=lista->next;
	}
	return men;
}

float promgen(alum_t *lista) {
	if(lista==NULL) return 0;
	int suma=0, cantidad=0;
	while(lista!=NULL) {
		suma+=lista->promedio;
		cantidad++;
		lista=lista->next;
	}
	return (float) suma/cantidad;
}

void liberar (alum_t *lista) {
	alum_t *aux;
	while(lista!=NULL) {
		aux=lista;
		lista=lista->next;
		free(aux);
	}
}

alum_t *buscar(alum_t *lista, char *nombre, char *apellido){
    while(lista!=NULL){
        if(strcasecmp(lista->nombre, nombre)==0 && strcasecmp(lista->apellido, apellido)==0) return lista; 
        //string compare ignorando mauysculas si son iguales los string de nombre y el nombre a buscar, devuelve el alumno
        //el original es strcmp en donde si importan las mayus pero, se puede usar strcasecmp algunas veces
        lista=lista->next;
    }
    return NULL;
}

