#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> 

using namespace std;

#define TXT_MAX 50

enum perfiles{
    COMPRADOR,
    PROPIETARIO
};

enum op_prop{
    ACTUALIZAR_STOCK=1,               //actualizar stock usando un archivo
    VER_INVENTARIO,                 //ver inventario
    SALIR_PROG
};

enum op_comprador{
    AGREGAR_COMIC=1,                //agregar al carrito un nuevo comic
    MOSTRAR_INVENTARIO,             //mostrar stock
    MOSTRAR_CARRITO,                //mostrar carrito
    ELIMINAR_COMIC,                 //eliminar del carrito un comic
    SALIR
};

class Comic {
public:
    string titulo;
    int precio;
    int id;
    int cant_stock;

    void imprimir_comic() const;            //imprime los comics pero no la lista de comics
    void imprimir_comic_carrito() const;    
};

class Tienda{
private:
    int presupuesto;
    string nombre_comprador;
    vector<Comic> inventario;
    vector<Comic> carrito;
public:
    void inicio_comprador();              //pide datos al usuario (el nuevo cliente)
    void menu_comprador();

    void menu_prop();
    void prop_cargar_stock();

    void mostrar_inventario_f();        //muestra la lista de comics con todos sus datos
    void mostrar_carrito();

    void eliminar_comic_carrito();

    void agregar_comic_carrito();       

    void actualizar_stock_f();          //actualiza el stock despues de que alguien haya comprado
    void actualizar_clientes_f();       //actualiza los clientes despues de que alguien haya comprado
    void actualizar_carrito_f();
};

int main() {
    Tienda tienda;
    int eleccion = 0;
    int perfil = 0;
    tienda.mostrar_inventario_f();

    cout << "Es comprador o propetario (Comprador = 0, Propietario = 1): ";
    cin >> perfil;

    if (perfil == COMPRADOR){
        tienda.inicio_comprador();
        tienda.menu_comprador();
    }else{
        tienda.menu_prop();
    }
    return 0;
}

void Comic::imprimir_comic() const{
    cout << "\n    Numero de ID: " << id << endl;
    cout << "Nombre del comic: " << titulo << endl;
    cout << "Precio: " << precio << endl;
    cout << "Stock: " << cant_stock << endl;
}

void Comic::imprimir_comic_carrito() const{
    cout << "\n    Numero de ID: " << id  << endl;
    cout << "Nombre del comic: " << titulo  << endl;
    cout << "Precio: " << precio  << endl;
    cout << "Cantidad comprada: " << cant_stock  << endl;
}

void Tienda::inicio_comprador(){
    cout << "Ingrese su nombre: ";
    cin >> nombre_comprador;
    cout << "Ingrese su presupuesto: ";
    cin >> presupuesto;
}

void Tienda::mostrar_inventario_f(){
    inventario.clear();
    FILE *archivo = fopen("stock_comics.txt", "r");
    char linea[TXT_MAX];

    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    Comic c;
    cout << "\n--- INVENTARIO --- \n";

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

    for (Comic &c : inventario){
        if (c.id == id_buscado){
            encontrado = true;

            if (c.cant_stock == 0){
                cout << "No hay stock.\n";
                return;
            }

            cout << "Cuantos comics queres?: ";
            cin >> cant_deseada;

            int max_por_presupuesto = presupuesto / c.precio;
            int max_comprables = min({cant_deseada, c.cant_stock, max_por_presupuesto});

            if (max_comprables == 0) {
                cout << "\nNo alcanza el presupuesto para comprar ninguno.\n";
                return;
            }

            if (max_comprables < cant_deseada) {
                cout << "\nSolo podes comprar " << max_comprables << " unidades por stock o presupuesto.\n";
            }

            Comic copia = c;
            copia.cant_stock = max_comprables;
            carrito.push_back(copia);

            presupuesto -= c.precio * max_comprables;
            c.cant_stock -= max_comprables;

            cout << "\nComic agregado al carrito.";
            cout << "\nCantidad: " << max_comprables;
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

    //agrupa los comics por ID
    //asigna un numero a cada comic
    map<int, Comic> carrito_agrupado;
    for (const Comic &c : carrito) {
        if (carrito_agrupado.count(c.id)) {
            carrito_agrupado[c.id].cant_stock += c.cant_stock;
        } else {
            carrito_agrupado[c.id] = c;
        }
    }

        cout << "\n--- CARRITO --- \n";
    for (const auto &par : carrito_agrupado) {
        const Comic &c = par.second;
        c.imprimir_comic_carrito();
        gasto_total += c.precio * c.cant_stock;
    }

    cout << "\nTotal gastado hasta ahora: " << gasto_total << endl;
    cout << "Presupuesto restante: " << presupuesto << endl;
}

void Tienda::eliminar_comic_carrito(){
    bool encontrado = false;
    int cant_a_eliminar;
    int id_buscado;

    cout << "Ingrese el ID del comic que desea eliminar del carrito: ";
    cin >> id_buscado;

    //for (Comic &c : inventario){ no deja eliminar elementos
    for (auto it = carrito.begin(); it != carrito.end(); ++it){
        if (it->id == id_buscado){
            encontrado = true;

            cout << "Cuantos comics queres eliminar?: ";
            cin >> cant_a_eliminar;

            if (cant_a_eliminar <= 0) {
                cout << "Cantidad invalida.\n";
                return;
            }

            if (cant_a_eliminar >= it->cant_stock){ //elimina la compra
                presupuesto += it->precio * it->cant_stock;

                for (Comic &c : inventario){ //devuelve la cantidad de stock
                    if (c.id == id_buscado){
                        c.cant_stock += it->cant_stock;
                        break;
                    }
                }
            
                cout << "\nSe eliminaron " << it->cant_stock << " unidades del comic ID = " << id_buscado << " del carrito.\n";
                cout << "Presupuesto devuelto: " << it->precio * it->cant_stock << endl;

                carrito.erase(it);
            }else{ //elimina un par de comics (cant_a_eliminar < cantidad comprada)
                it->cant_stock -= cant_a_eliminar;
                presupuesto += it->precio * cant_a_eliminar;

                for (Comic &c : inventario) {
                    if (c.id == id_buscado) {
                        c.cant_stock += cant_a_eliminar;
                        break;
                    }
                }

                cout << "\nSe eliminaron " << cant_a_eliminar << " unidades del comic ID = " << id_buscado << " del carrito.\n";
                cout << "Presupuesto: " << it->precio * cant_a_eliminar << endl;
            }

            return;

        if (!encontrado){
            cout << "ID no encontrado en el carrito.\n";
        }
        }
    }
}

void Tienda::menu_comprador(){
    int eleccion;

    do{
        cout << "\n--- MENU COMPRADOR ---\n";
        cout << "1. Agregar comic al carrito\n";
        cout << "2. Mostrar inventario\n";
        cout << "3. Mostrar carrito\n";
        cout << "4. Eliminar comic del carrito\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> eleccion;

        switch (eleccion){ //todas los casos deben actualizar el file para que no haya errores
        case AGREGAR_COMIC:
            agregar_comic_carrito();
            actualizar_stock_f();
            break;
        case MOSTRAR_INVENTARIO:
            mostrar_inventario_f();
            break;
        case MOSTRAR_CARRITO:
            mostrar_carrito();
            break;
        case ELIMINAR_COMIC:
            eliminar_comic_carrito();
            cout << "Elegiste eliminar.";
            break; 
        case SALIR:
            mostrar_inventario_f();
            cout << "Gracias por comprarnos :)";
            break;
        default:
            cout << "Algo malio sal.\n";
            break;
        }
    } while (eleccion != SALIR);
}

void Tienda::prop_cargar_stock(){
    FILE *archivo_origen = fopen("stock_og.txt", "r");
    FILE *archivo = fopen("stock_comics.txt", "w");
    char linea[TXT_MAX];

    if (archivo_origen == NULL) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    while (fgets(linea, TXT_MAX, archivo_origen)){
        fputs(linea, archivo);
    }
    
    fclose(archivo_origen);
    fclose(archivo);
    cout << "\nStock actualizado correctamente desde nuevo_stock.txt.\n";
}

void Tienda::menu_prop(){
    int eleccion;

    do{
        cout << "\n--- MENU PROPIETARIO ---\n";
        cout << "1. Actualizar inventario completo\n";
        cout << "2. Ver inventario\n";
        cout << "3. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> eleccion;

        switch (eleccion){ 
        case ACTUALIZAR_STOCK:
            prop_cargar_stock();
            break;
        case VER_INVENTARIO:
            mostrar_inventario_f();
            break; 
        case SALIR_PROG:
            cout << "Volve a trabajar.";
            break;
        default:
            cout << "Algo malio sal.\n";
            break;
        }
    } while (eleccion != SALIR_PROG);
}
