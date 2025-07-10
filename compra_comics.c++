#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define TXT_MAX 50

typedef enum{
    AGREGAR=1,  //agregar al carrito un nuevo comic
    INVENTARIO, //mostrar stock
    MOSTRAR,    //mostrar carrito
    ELIMINAR,   //eliminar del carrito un comic
    SALIR
}opciones_t;

class Comic {
public:
    string titulo;
    int precio;
    int id;
    int cant_stock;

    void imprimir_comic() const; //imprime los comics pero no la lista de comics
};

class Tienda{
private:
    int presupuesto;
    string nombre_usuario;
    vector<Comic> inventario;
    vector<Comic> carrito;
public:
    void inicio_usuario();              //pide datos al usuario (el nuevo cliente)
    //void salida_usuario();

    void mostrar_inventario_f();        //muestra la lista de comics con todos sus datos
    void mostrar_carrito();

    void agregar_comic_carrito();       

    void actualizar_stock_f();          //actualiza el stock despues de que alguien haya comprado
    void actualizar_clientes_f();       //actualiza los clientes despues de que alguien haya comprado
    void actualizar_carrito_f();
};

/*
Todas las que muestran: mostrar_...
Todas las que actualizan archivos: guardar_...
Todas las que cambian datos del programa: agregar_..., eliminar_...
*/

int main() {
    Tienda tienda;
    int eleccion;
    tienda.inicio_usuario();
    tienda.mostrar_inventario_f();

    do{
        printf("\n--- TIENDA DE COMICS ---\n");
        printf("1. Agregar un comic al carrito.\n");
        printf("2. Ver inventario.\n");
        printf("3. Mostrar carrito.\n");
        printf("4. Eliminar un comic del carrito.\n");
        printf("5. Salir.\n\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &eleccion);

        switch (eleccion){ //todas los casos deben actualizar el file para que no haya errores
        case AGREGAR:
            tienda.agregar_comic_carrito();
            tienda.actualizar_stock_f();
            break;
        case INVENTARIO:
            tienda.mostrar_inventario_f();
            break;
        case MOSTRAR:
            tienda.mostrar_carrito();
            break;
        case ELIMINAR:
            //eliminar_comic();
            //actualizar_carrito_f();
            break; 
        case SALIR:
            //actualizar_stock_f();
            tienda.mostrar_inventario_f();
            //actualizar_clientes_f();
            //liberar();
            //salida_usuario();
            printf("Chau.");
            break;
        }  
    } while (eleccion != SALIR);
    return 0;
}

void Comic::imprimir_comic() const{
    cout << "\n    Numero de ID: " << id << endl;
    cout << "Nombre del comic: " << titulo << endl;
    cout << "Precio: " << precio << endl;
    cout << "Stock: " << cant_stock << endl;
}

void Tienda::inicio_usuario(){
    cout << "Ingrese su nombre: ";
    cin >> nombre_usuario;
    cout << "Ingrese su presupuesto: ";
    cin >> presupuesto;
}

void Tienda::mostrar_inventario_f(){
    inventario.clear();
    FILE *archivo = fopen("stock_comics.txt", "r");
    char linea[TXT_MAX];

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Comic c;
    printf("\n--- INVENTARIO --- \n");

    while (fgets(linea, TXT_MAX, archivo)) {
        if (sscanf(linea, "Numero de ID: %d", &c.id) == 1) {        //si lo puede leer avanza
            fgets(linea, TXT_MAX, archivo);
            sscanf(linea, "Nombre del comic: %[^\n]", linea); 
            c.titulo = linea;

            fgets(linea, TXT_MAX, archivo);
            sscanf(linea, "Precio: %d", &c.precio);

            fgets(linea, TXT_MAX, archivo);
            sscanf(linea, "Stock: %d", &c.cant_stock);

            inventario.push_back(c);
            c.imprimir_comic();

            fgets(linea, TXT_MAX, archivo);
        }
    }
    printf("\n");
    fclose(archivo);
}

void Tienda::agregar_comic_carrito(){
    bool encontrado = false;
    int cant_deseada;
    int id_buscado;

    cout << "Ingrese el ID del comic que desea agregar al carrito: ";
    cin >> id_buscado;

    /*for (Tipo &variable : contenedor) {
    //la variable esta para acceder a cada elemento del contenedor
    }*/
    
    for (Comic &c : inventario){
        if (c.id == id_buscado){
            encontrado = true;

            cout << "Cuantos comics queres?: ";
            cin >> cant_deseada;

            if (c.cant_stock == 0 || c.cant_stock < cant_deseada){
                cout << "No hay stock.\n";
                return;
            }

            if (presupuesto < c.precio * cant_deseada){
                cout << "\nNo hay suficiente presupuesto.";
                cout << "\nPrecio x Unidad: " << c.precio << endl;
                cout << "\nPresupuesto: " << presupuesto << endl;
                return;
            }

            Comic copia = c;
            copia.cant_stock = cant_deseada; 
            carrito.push_back(copia);
            //push_back agrega un nuevo elemento al final del vector

            presupuesto -= c.precio * cant_deseada;
            c.cant_stock -= cant_deseada;

            cout << "\nComic agregado al carrito.";
            cout << "\nPresupuesto restante: " << presupuesto << endl;
            return;
        }
    }
    if (!encontrado){
        cout << "ID no encontrado en el inventario.\n";
    }
}

void Tienda::actualizar_stock_f(){
    FILE *archivo = fopen("stock_comics.txt", "w");
    char linea[TXT_MAX];

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    /*for (Tipo &variable : contenedor) {
    //la variable esta para acceder a cada elemento del contenedor
    }*/
    for (Comic &c : inventario) {
        fprintf(archivo, "Numero de ID: %d\n", c.id);
        fprintf(archivo, "Nombre del comic: %s\n", c.titulo.c_str());
        fprintf(archivo, "Precio: %d\n", c.precio);
        fprintf(archivo, "Stock: %d\n\n", c.cant_stock);
    }

    fclose(archivo);
    printf("Stock actualizado correctamente.\n");
}

void Tienda::mostrar_carrito(){
    int gasto_total = 0;

    if (carrito.empty()) { //si el vector carrito esta vacio
        cout << "\nEl carrito esta vacio.\n";
        return;
    }

    printf("\n--- CARRITO --- \n");
    for (const Comic &c : carrito) { //se usa const Comic para no modificar los datos
        c.imprimir_comic();
        gasto_total += c.precio * c.cant_stock;
    }

    cout << "\nTotal gastado hasta ahora: " << gasto_total << endl;
    cout << "Presupuesto restante: " << presupuesto << endl;
}

