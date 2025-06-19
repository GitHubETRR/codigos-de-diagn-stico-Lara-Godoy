#include <iostream>
using namespace std;

class Libro{
public:
    string titulo;
    string autor;
    int publi_year;
    int precio;
    int id;

    void mostrar_info(){
        cout << "\n    Numero de ID: " << id << endl;
        cout << "Nombre del libro: " << titulo << endl;
        cout << "Autor del libro: " << autor << endl;
        cout << "Precio: " << precio << endl;
        cout << "Year de publicacion: " << publi_year << endl;
    }
};

int main() {
    Libro l1;
    l1.id = 1;
    l1.precio = 400;
    l1.publi_year = 2007;
    l1.autor = "Hanna Salazar";
    l1.titulo = "Como ser pro en C: 10 sencillos pasos.";
    l1.mostrar_info(); 

    Libro l2;
    l2.id = l1.id + 1;
    l2.precio = l1.precio / 2;
    l2.publi_year = 2008;
    l2.autor = "Lara Godoy";
    l2.titulo = "Art Attack recipies.";
    l2.mostrar_info(); 
    return 0;
}