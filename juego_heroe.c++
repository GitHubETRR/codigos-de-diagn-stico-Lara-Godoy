#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <limits>

using namespace std;

#define TXT_MAX 120
#define VIDA_MAX 100
#define CANT_HAB 4 // fuerza, vida, reflejos y velocidad
#define CANT_PUNTOS 4 // 5, 10, 15, 20
#define OCUPADO 1
#define LIBRE 0

enum resultados{
    CONTINUA,
    H_GANA,
    V_GANA,
    TERMINAR
};

enum turnos{
    TURNO_VILLANO,
    TURNO_HEROE
};

enum habilidades{
    FUERZA=1,
    REFLEJOS,
    VELOCIDAD,
    VIDA
};

//hace el enum de todo lo que puede hacer un heroe
enum acciones_heroe{
    ATACAR=1,
    DEFENDER,
    ATAQUE_ESPECIAL,
    DEFENSA_ESPECIAL,
    CURARSE,
    SALIR_JUEGO
};

enum acciones_villano{
    V_ATACAR=1,
    V_ATAQUE_ESPECIAL,
    V_DEFENSA_ESPECIAL,
    V_CURARSE
};

enum elementos{
    CERO,
    UNO,
    DOS,
    TRES,
};

class Personaje{
private:
    //atributos: solo la clase de como cambian 
public: 
    // metodos: cualquier otra clase puede acceder a ellos 
    bool levelear(int &habilidad, int puntos_usados[], int habilidades_mejoradas[]);
    int indice(int puntos_a_sumar);
    bool verificar_hab_libres(int habilidades_mejoradas[]);
    void mostrar_habilidades(int habilidades_mejoradas[], int puntos_usados[]);

    Personaje() = default; //vacio para que despues los valores que se usan son los del txt

    // GETS
    string get_nombre() const { return nombre_str; }
    int get_numero() const { return numero; }

    int get_fuerza() const { return fuerza; }
    int get_reflejos() const { return reflejos; }
    int get_velocidad() const { return velocidad; }
    int get_vida() const { return vida; }

    int get_ataque_int() const { return ataque_int; }
    string get_ataque_str() const { return ataque_str; }
    int get_defensa_int() const { return defensa_int; }
    string get_defensa_str() const { return defensa_str; }

    // SETS
    void set_fuerza(int f) { fuerza = f; }
    void set_reflejos(int r) { reflejos = r; }
    void set_vel(int vel) { velocidad = vel; }
    void set_vida(int v) { vida = max(0, v); }

    void set_numero(int num) { numero = num; }
    void set_nombre_str(const string &nom) { nombre_str = nom; }

    void set_ataque_str(const string &atk) { ataque_str = atk; }
    void set_ataque_int(int atk_int) { ataque_int = atk_int; }
    void set_defensa_str(const string &def) { defensa_str = def; }
    void set_defensa_int(int def_int) { defensa_int = def_int; }

protected: // atributos y metodos que solo las clases derivadas pueden acceder
    int numero; 
    int fuerza, reflejos, velocidad, vida;
    string ataque_str, defensa_str, nombre_str;
    int ataque_int, defensa_int;
};

class Heroe : public Personaje{
    public:
        void imprimir_heroe() const; //cambiar x heredar la funcion imp personaje
};

class Villano : public Personaje{
    public:
        void imprimir_villano() const; 
};

class Combate{
private:
    
public:
    turnos turno_actual;
    resultados valor_resultado(Heroe &heroe, Villano &villano);
    turnos determinar_turno_actual(const Personaje& heroe, const Personaje& villano);
    bool chance_esquivar(int reflejos_atacante, int reflejos_defensor);
    resultados menu_combate(Heroe &heroe, Villano &villano);
    void menu_turno_villano(Heroe &heroe, Villano &villano, bool &defendiendo_heroe, bool &v_uso_def_especial, bool &v_uso_ataque_especial,
    bool &heroe_uso_ataque_especial, bool &heroe_uso_defensa_especial, int vida_heroe_inicial, int vida_villano_inicial);

    //las referencias permiten que el objeto no se copie, sino que se use el original
    //Heroe& jugador y Villano& oponente no puede existir sin apuntar a algo
    Heroe& jugador;
    Villano& oponente;

    Combate(Heroe& h, Villano& v) : jugador(h), oponente(v), turno_actual(TURNO_HEROE) {}
    /*construtor:
    el constructor inicializa las referencias (h y v) y el turno actual
    el constructor funciona hasta que se crea el objeto Combate
    */
    /*: lista de inicialización: 
    se usa para inicializar atributos que son referencias o constantes
    antes de que se ejecute el cuerpo del constructor
    */
    //jugador(h) --> el miembro jugador de Combate se inicializa apuntando a h que llegó al constructor.
    //{} esta vacio porque no hay código que ejecutar al crear el objeto Combate.
};

class Juego{
private:
    Heroe jugador;
    Villano oponente;
    Combate combate;

    vector<Heroe> heroes;
    vector<Villano> villanos;
public:
    Juego() : jugador(), oponente(), combate(jugador, oponente) {}
    //combate(jugador, oponente) inicializa pasandole las referencias a los miembros jugador y oponente recien creados.

    void mostrar_heroes();
    void mostrar_villanos();
    Heroe menu_mejoras(Heroe heroe);

    Heroe seleccionar_heroe();
    Villano crear_villano();
};

int main() {
    srand(time(NULL));
    resultados result;
    Juego juego;
    Personaje personaje;
    Villano villano;
    Heroe heroe;

    cout << "Bienvenido al juego de combate entre heroes y villanos.\n";
    cout << "Elige un heroe y mejora sus habilidades para enfrentarte a un villano en un combate por turnos.\n";

    juego.mostrar_heroes();
    heroe = juego.seleccionar_heroe();

    heroe = juego.menu_mejoras(heroe);

    juego.mostrar_villanos();
    villano = juego.crear_villano();
    cout << "\n--- VILLANO ALEATORIO ---\n";
    villano.imprimir_villano();

    Combate combate(heroe, villano);
    result = combate.menu_combate(heroe, villano);

    if (result == TERMINAR) return 0;
}

void Combate::menu_turno_villano(Heroe &heroe, Villano &villano, bool &defendiendo_heroe, bool &v_uso_def_especial, bool &v_uso_ataque_especial,
    bool &heroe_uso_ataque_especial, bool &heroe_uso_defensa_especial, int vida_heroe_inicial, int vida_villano_inicial){

    int accion_villano = rand() % 5;
    int puntos_vida_curacion = 5 + rand() % 15;
    bool accion_valida = false;
    
    int danio_temp;

    do{
        accion_villano = rand () % 5;

        if ((vida_heroe_inicial == heroe.get_vida()) && (vida_villano_inicial == villano.get_vida())){
            accion_villano = V_ATACAR;
        }
        if ((defendiendo_heroe || heroe_uso_defensa_especial) && accion_villano != V_ATACAR) {
            accion_villano = V_ATACAR;
        }
        switch (accion_villano){
        case V_ATACAR:
            cout << "El villano ataca!\n";
            if (defendiendo_heroe == true){
                heroe.set_vida(heroe.get_vida() - villano.get_ataque_int() / 4);
                cout << "El heroe se ha defendido!\n";
                cout << "Dano del ataque del villano: " << villano.get_ataque_int() / 4 << endl;
                if (heroe.get_vida() < 0) heroe.set_vida(0);
                cout << "Vida del heroe: " << heroe.get_vida() << "\n";
                defendiendo_heroe = false;
            } else if (heroe_uso_defensa_especial == true) {
                cout << "El heroe se ha defendido!\n";
                danio_temp = villano.get_ataque_int() - heroe.get_defensa_int();
                if (danio_temp < 0) danio_temp = 0;
                heroe.set_vida(heroe.get_vida() - danio_temp);
                cout << "El heroe ha recibido " << danio_temp << " de danio!\n";
                if (heroe.get_vida() < 0) heroe.set_vida(0);
                cout << "Vida del heroe: " << heroe.get_vida() << "\n";
                heroe_uso_defensa_especial = false;
            } else if (chance_esquivar(villano.get_reflejos(), heroe.get_reflejos())){
                cout << "El heroe ha esquivado el ataque!\n";
                cout << "Vida del heroe: " << heroe.get_vida() << "\n";
            }else{
                heroe.set_vida(heroe.get_vida() - villano.get_ataque_int());
                cout << "El heroe ha recibido " << villano.get_ataque_int() << " de danio!\n";
                if (heroe.get_vida() < 0) heroe.set_vida(0);
                cout << "Vida del heroe: " << heroe.get_vida() << "\n";
            }
            accion_valida = true;
            break;
        case V_ATAQUE_ESPECIAL:
            if (v_uso_ataque_especial == false){
                    cout << "El villano ataca con su ataque especial!\n";
                    heroe.set_vida(heroe.get_vida() - villano.get_ataque_int());
                    cout << "El heroe ha recibido " << villano.get_ataque_int() << " de danio!\n";
                    if (heroe.get_vida() < 0) heroe.set_vida(0);
                cout << "Vida del heroe: " << heroe.get_vida() << "\n";
                    v_uso_ataque_especial = true;
                    accion_valida = true;
                }else{
                    accion_valida = false;
                }
            break;
        case V_DEFENSA_ESPECIAL:
            if (v_uso_def_especial == false){
                cout << "El villano se defiende con su defensa especial!\n";
                cout << "El proximo ataque de " << heroe.get_nombre() << " hara menos dano.\n";
                v_uso_def_especial = true;
                accion_valida = true;
            }else{
                accion_valida = false;
            }
            break;
        case V_CURARSE:
            if (villano.get_vida() == vida_villano_inicial){
                accion_valida = false;
            }else{
                if (villano.get_vida() + puntos_vida_curacion >= vida_villano_inicial){
                    villano.set_vida(vida_villano_inicial);
                    cout << "\nEl villano decidio curarse.";
                    cout << "\nVida del villano: " << villano.get_vida() << "\n";
                    accion_valida = true;
                }else{
                    cout << "\nEl villano decidio curarse.";
                    villano.set_vida(villano.get_vida() + puntos_vida_curacion);
                    cout << "\nVida del villano: " << villano.get_vida() << "\n";
                    accion_valida = true;
                }
            }
            break;
        }
    } while (accion_valida == false);
}

resultados Combate::menu_combate(Heroe &heroe, Villano &villano){
    bool salir = false;
    int eleccion;
    int puntos_vida_curacion; //el valor se declara en el case CURARSE
    int danio_temp;
    int vida_heroe_inicial;
    int vida_villano_inicial;

    bool accion_valida = false;
    bool defendiendo_heroe = false;
    bool heroe_uso_ataque_especial = false;
    bool heroe_uso_defensa_especial = false;
    bool v_uso_def_especial = false;
    bool v_uso_ataque_especial = false;

    cout << "\n--- COMBATE INICIADO ---\n";
    cout << heroe.get_nombre() << " VS " << villano.get_nombre() << "\n";
    
    cout << "Vida de " << heroe.get_nombre() << ": " << heroe.get_vida() << "\n";
    cout << "Vida de " << villano.get_nombre() << ": " << villano.get_vida() << "\n";

    vida_heroe_inicial = heroe.get_vida();
    vida_villano_inicial = villano.get_vida();

    turno_actual = determinar_turno_actual(heroe, villano);
    cout << "\n";

    do{
        if (turno_actual == TURNO_HEROE){
            do{
                cout << "\n--- TURNO DEL HEROE ---\n";
                cout << "1. Atacar\n";                  
                cout << "2. Defender\n";               
                cout << "3. Atacar especial\n";
                cout << "4. Defensa especial\n";
                cout << "5. Curarse\n";
                cout << "6. Salir\n";
                cout << "Ingrese una opcion: ";

                if (cin >> eleccion) {
                    if (eleccion >= 1 && eleccion <= 6) {
                        accion_valida = true;  // la entrada es correcta
                    } else {
                        cout << "Opcion invalida. Elige un numero entre 1 y 6.\n";
                        cin.clear(); // limpia el flag de error
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } else {
                    cout << "Entrada invalida. Debes ingresar un numero entre 1 y 6..\n";
                    cin.clear(); // limpia el flag de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta la basura
                }
                } while (!accion_valida);

            switch (eleccion){ 
            case ATACAR:
                cout << "\nEl heroe ataca!\n";

                if (v_uso_def_especial){
                    danio_temp = static_cast<int>(heroe.get_fuerza() * 0.7); //convierte la fuerza calculada a int
                    villano.set_vida(villano.get_vida() - danio_temp);
                    cout << "El villano ha recibido " << danio_temp << " de danio!\n";
                    if (villano.get_vida() < 0) villano.set_vida(0);
                    cout << "Vida del villano: " << villano.get_vida() << "\n";
                }else{
                    if (chance_esquivar(heroe.get_reflejos(), villano.get_reflejos())){
                        cout << "El villano ha esquivado el ataque!\n";
                        cout << "Vida del villano: " << villano.get_vida() << "\n";
                    } else {
                        villano.set_vida(villano.get_vida() - heroe.get_fuerza());
                        cout << "El villano ha recibido " << heroe.get_fuerza() << " de danio!\n";
                        if (villano.get_vida() < 0) villano.set_vida(0);
                        cout << "Vida del villano: " << villano.get_vida() << "\n";
                    }
                }
                accion_valida = true;
                break;
            case DEFENDER:
                cout << "\nEl heroe se defiende!\n";
                defendiendo_heroe = true;
                cout << heroe.get_nombre() << " se esta defendiendo.\n";
                cout << "El proximo ataque de " << villano.get_nombre() << " hara menos dano.\n";
                cout << "Vida del heroe: " << heroe.get_vida() << "\n";
                accion_valida = true;
                break;
            case ATAQUE_ESPECIAL:
                if (heroe_uso_ataque_especial == false){
                    cout << "\nEl heroe ataca con su ataque especial!\n";
                    if (v_uso_def_especial){
                        danio_temp = static_cast<int>(heroe.get_fuerza() * 0.7); //convierte la fuerza calculada a int
                        villano.set_vida(villano.get_vida() - danio_temp);
                        cout << "El villano ha recibido " << danio_temp << " de danio!\n";
                        if (villano.get_vida() < 0) villano.set_vida(0);
                        cout << "Vida del villano: " << villano.get_vida() << "\n";
                    }else{
                        villano.set_vida(villano.get_vida() - heroe.get_ataque_int());
                        cout << "El villano ha recibido " << heroe.get_ataque_int() << " de danio!\n";
                        if (villano.get_vida() < 0) villano.set_vida(0);
                        cout << "Vida del villano: " << villano.get_vida() << "\n";
                    }
                    heroe_uso_ataque_especial = true;
                }else{
                    cout << "Ya usaste el ataque especial. Elige otra accion.\n";
                    accion_valida = false;
                }
                break;
            case DEFENSA_ESPECIAL:
                if (heroe_uso_defensa_especial == false){
                    cout << "\nEl heroe se defiende con su defensa especial!\n";
                    cout << "El proximo ataque de " << villano.get_nombre() << " hara menos dano.\n";
                    accion_valida = true;
                    heroe_uso_defensa_especial = true;
                }else{
                    cout << "Ya usaste la defensa especial especial. Elige otra accion.\n";
                    accion_valida = false;
                }
                break; 
            case CURARSE:
                puntos_vida_curacion = 5 + rand() % 15;
                if (heroe.get_vida() == vida_heroe_inicial){
                    cout << "El heroe tiene la vida al maximo, no puede curarse. Elige otra accion.\n";
                    accion_valida = false;
                }else{
                    if (heroe.get_vida() + puntos_vida_curacion >= vida_heroe_inicial){
                        heroe.set_vida(vida_heroe_inicial);
                        cout << "\nEl heroe decidio curarse.";
                        cout << "\nVida del heroe: " << heroe.get_vida() << "\n";
                        accion_valida = true;
                    }else{
                        cout << "\nEl heroe decidio curarse.";
                        heroe.set_vida(heroe.get_vida() + puntos_vida_curacion);
                        cout << "\nVida del heroe: " << heroe.get_vida() << "\n";
                        accion_valida = true;
                    }
                }
                break;
            case SALIR_JUEGO:
                cout << "Elegiste salir del juego.\n";
                salir = true;
                break;
            default:
                cout << "Algo malio sal.\n";
                accion_valida = false;
                break;
            }

            if (salir == true) return TERMINAR;
            
            if (valor_resultado(heroe, villano) == H_GANA){
                cout << "\nEl villano ha muerto!\n";
                break;
            }
            turno_actual = accion_valida ? TURNO_VILLANO : TURNO_HEROE;
        }else{
            cout << "\n--- TURNO DEL VILLANO ---\n"; 

            menu_turno_villano(heroe, villano, defendiendo_heroe, v_uso_def_especial, v_uso_ataque_especial, heroe_uso_ataque_especial, heroe_uso_defensa_especial, vida_heroe_inicial, vida_villano_inicial);
            
            if (valor_resultado(heroe, villano) == V_GANA){
                cout << "\nEl heroe ha muerto!\n";
            }else{
                turno_actual = TURNO_HEROE;
            }
        }
    } while (valor_resultado(heroe, villano) == CONTINUA);
}

resultados Combate::valor_resultado(Heroe &heroe, Villano &villano){
    if (heroe.get_vida() <= 0) return V_GANA;
    if (villano.get_vida() <= 0) return H_GANA;
    return CONTINUA;
}

bool Combate::chance_esquivar(int reflejos_atacante, int reflejos_defensor) {
    int nro_random = rand() % 10;
    if ((reflejos_defensor + nro_random)> reflejos_atacante) return true;
    else return false;
}

Heroe Juego::menu_mejoras(Heroe heroe){
    bool accion_valida = false;
    bool todas_mejoradas;
    int idx = -1;
    int opcion, puntos_a_sumar;

    int fuerza = heroe.get_fuerza();
    int reflejos = heroe.get_reflejos();
    int velocidad = heroe.get_velocidad();
    int vida = heroe.get_vida();

    int habilidades_mejoradas[CANT_HAB] = {LIBRE, LIBRE, LIBRE, LIBRE}; 
    //habilidades_mejoradas[FUERZA, REFLEJOS, VELOCIDAD, VIDA]
    int puntos_usados[CANT_PUNTOS] = {LIBRE, LIBRE, LIBRE, LIBRE}; 
    //puntos_usados[5, 10, 15, 20]

    cout << "\n       Explicacion de las mejoras:\n";
    cout << "- Ahora puedes mejorar las habilidades de tu heroe.\n";
    cout << "- Cada habilidad puede ser mejorada una vez y cada mejora suma puntos.\n";
    cout << "- Cada cantidad de puntos solo puede ser usada una vez.\n";
    cout << "- Puedes mejorar las habilidades de tu heroe hasta que todas hayan sido mejoradas.\n";
    cout << "- Tienes 4 habilidades para mejorar: Fuerza, Reflejos, Velocidad y Vida.\n";
    cout << "- Cada habilidad puede ser mejorada con 5, 10, 15 o 20 puntos.\n";

    do{
        cout << "\n--- Habilidades iniciales ---\n";
        cout << "1. Fuerza: " << fuerza << "\n";
        cout << "2. Reflejos: " << reflejos << "\n";
        cout << "3. Velocidad: " << velocidad << "\n";
        cout << "4. Vida: " << vida << "\n";

        do{
            cout << "\nQue habilidad quieres mejorar?: ";
            if (cin >> opcion) {
                if (opcion >= 1 && opcion <= CANT_HAB) {
                    accion_valida = true;  // la entrada es correcta
                } else {
                    cout << "Opcion invalida. Elige un numero entre 1 y 4.\n";
                    cin.clear(); // limpia el flag de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } else {
                cout << "Entrada invalida. Debes ingresar un numero entre 1 y 4.\n";
                cin.clear(); // limpia el flag de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta la basura
            }
        } while (accion_valida == false);

        switch (opcion){
        case FUERZA:
            cout << "Elegiste Fuerza.\n";

            if (habilidades_mejoradas[FUERZA - 1] == OCUPADO) {
                cout << "Esa habilidad ya ha sido mejorada.\n";
                break;
            }

            //no se pasa el get de fuerza porque eso devuelve un valor, no una referencia
            if (heroe.levelear(fuerza, puntos_usados, habilidades_mejoradas)){
                habilidades_mejoradas[FUERZA - 1] = OCUPADO;
                cout << "Nueva Fuerza: " << fuerza << "\n";
                heroe.set_fuerza(fuerza);
            }
            break;
        case REFLEJOS:
            cout << "Elegiste Reflejos.\n";

            if (habilidades_mejoradas[REFLEJOS - 1] == OCUPADO) {
                cout << "Esa habilidad ya ha sido mejorada.\n";
                break;
            }

            if (heroe.levelear(reflejos, puntos_usados, habilidades_mejoradas)){
                habilidades_mejoradas[REFLEJOS - 1] = OCUPADO;
                cout << "Nueva reflejos: " << reflejos << "\n";
                heroe.set_reflejos(reflejos);
            }
            break;
        case VELOCIDAD:
            cout << "Elegiste Velocidad.\n";
            
            if (habilidades_mejoradas[VELOCIDAD - 1] == OCUPADO) {
                cout << "Esa habilidad ya ha sido mejorada.\n";
                break;
            }

            if (heroe.levelear(velocidad, puntos_usados, habilidades_mejoradas)){
                habilidades_mejoradas[VELOCIDAD - 1] = OCUPADO;
                cout << "Nueva velocidad: " << velocidad << "\n";
                heroe.set_vel(velocidad);
            }
            break;
        case VIDA:
            cout << "Elegiste Vida.\n";

            if (habilidades_mejoradas[VIDA - 1] == OCUPADO) {
                cout << "Esa habilidad ya ha sido mejorada.\n";
                break;
            }

            if (heroe.levelear(vida, puntos_usados, habilidades_mejoradas)){
                habilidades_mejoradas[VIDA - 1] = OCUPADO;
                cout << "Nueva vida: " << vida << "\n";
                heroe.set_vida(vida);
            }
            break;
        default:
            cout << "Opcion no valida. Intenta de nuevo.\n";
            break;
        }
    } while (heroe.verificar_hab_libres(habilidades_mejoradas));

    heroe.mostrar_habilidades(habilidades_mejoradas, puntos_usados); // --> Verificacion
    cout << "\nTodas las habilidades han sido mejoradas.\n";

    cout << "\n--- Habilidades mejoradas ---\n";
    cout << "1. Fuerza: " << fuerza << "\n";
    cout << "2. Reflejos: " << reflejos << "\n";
    cout << "3. Velocidad: " << velocidad << "\n";
    cout << "4. Vida: " << vida << "\n";
    return heroe;
}

turnos Combate::determinar_turno_actual(const Personaje& heroe, const Personaje& villano){
    //const: no modifica los argumentos que recibe
    //&: pasado por referencia, no por valor
    if (heroe.get_velocidad() > villano.get_velocidad())
        return TURNO_HEROE;
    else if (villano.get_velocidad() > heroe.get_velocidad())
        return TURNO_VILLANO;
    else
        return (rand() % 2 == 0) ? TURNO_HEROE : TURNO_VILLANO;
}

void Juego::mostrar_heroes(){
    //lea el file txt de personajes
    char temp_nombre[TXT_MAX];
    char temp_ataque[TXT_MAX];
    char temp_defensa[TXT_MAX];

    Heroe h{}; //crea un objeto Heroe para almacenar los datos leidos
    int numero;
    int fuerza, reflejos, velocidad, vida;
    string ataque, defensa, nombre;
    int ataque_int, defensa_int;

    ifstream archivo("heroes.txt");
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    cout << "\n--- HEROES A ELEGIR --- \n";

    while (getline(archivo, linea)) {
        if (linea.find("Nombre:") != std::string::npos) h.set_nombre_str(linea.substr(7));
        else if (linea.find("Numero:") != std::string::npos) h.set_numero(stoi(linea.substr(7)));
        else if (linea.find("Fuerza:") != std::string::npos) h.set_fuerza(stoi(linea.substr(7)));
        else if (linea.find("Reflejos:") != std::string::npos) h.set_reflejos(stoi(linea.substr(9)));
        else if (linea.find("Velocidad:") != std::string::npos) h.set_vel(stoi(linea.substr(10)));
        else if (linea.find("Vida:") != std::string::npos) h.set_vida(stoi(linea.substr(5)));
        else if (linea.find("Ataque:") != string::npos) {
            getline(archivo, linea);
            linea.erase(linea.find_last_not_of("\n\r")+1);
            h.set_ataque_str(linea);

            getline(archivo, linea);
            if (linea.find("Puntos de danio:") != string::npos)
                h.set_ataque_int(stoi(linea.substr(16)));
        }else if (linea.find("Defensa:") != string::npos) {
            getline(archivo, linea);
            linea.erase(linea.find_last_not_of("\n\r")+1);
            h.set_defensa_str(linea);

            getline(archivo, linea);
            if (linea.find("Puntos de defensa:") != string::npos)
                h.set_defensa_int(stoi(linea.substr(18)));
        }

        // AND enorme para verificar que todos los campos se hayan llenado
        if (!h.get_nombre().empty() && h.get_numero() && h.get_fuerza() && h.get_reflejos() && h.get_velocidad() && h.get_vida() && !h.get_ataque_str().empty() && h.get_ataque_int() && !h.get_defensa_str().empty() && h.get_defensa_int()) {
            heroes.push_back(h);
            h.imprimir_heroe();
            h = Heroe{}; // reiniciamos para el siguiente heroe
        }
    }
    cout << "\n";
    archivo.close();
}

void Heroe::imprimir_heroe() const {
    cout << "\n     Nombre: " << nombre_str << endl;
    cout << "Numero: " << numero << endl;
    cout << "Fuerza: " << fuerza << endl;
    cout << "Reflejos: " << reflejos << endl;
    cout << "Velocidad: " << velocidad << endl;
    cout << "Vida: " << vida << endl;
    cout << "   Ataque:" << endl;
    cout << ataque_str << endl;
    cout << "El ataque especial le saca " << ataque_int << " al enemigo" << endl;
    cout << "   Defensa:" << endl;
    cout << defensa_str << endl;
    cout << "La defensa especial le saca " << defensa_int << " al ataque del enemigo" << endl;
}

Heroe Juego::seleccionar_heroe() {
    Heroe heroe; 
    int num_heroe;
    bool num_valido = false;
    cout << "\n--- SELECCIONA UN HEROE ---\n";

    do{
        cout << "Selecciona el numero del heroe que quieres elegir: ";
        if (cin >> num_heroe){//si es numero
            if (num_heroe >= 1 && num_heroe <= heroes.size()) {
                num_valido = true; // entrada correcta
            } else {
                cout << "Numero de heroe no valido.\n";
                cout << "Debes ingresar un numero entre 1 y " << heroes.size() << endl;
            }
        }else{
            cout << "Entrada invalida.\n";
            cout << "Debes ingresar un numero entre 1 y " << heroes.size() << endl;
            cin.clear(); // limpia el flag de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!num_valido);

    heroe = heroes[num_heroe - 1]; // Asignar el heroe seleccionado al jugador
    cout << "Has seleccionado a: " << heroe.get_nombre() << endl;

    return heroe; 
}

void Personaje::mostrar_habilidades(int habilidades_mejoradas[], int puntos_usados[]) { //verificacion de buen funcionamiento
    cout << "\nFuerza: " << habilidades_mejoradas[FUERZA - 1];
    cout << "\nReflejos: " << habilidades_mejoradas[REFLEJOS - 1];
    cout << "\nVelocidad: " << habilidades_mejoradas[VELOCIDAD - 1];
    cout << "\nVida: " << habilidades_mejoradas[VIDA - 1] << "\n";

    cout << "\n5 puntos: " << puntos_usados[CERO];
    cout << "\n10 puntos: " << puntos_usados[UNO];
    cout << "\n15 puntos: " << puntos_usados[DOS];
    cout << "\n20 puntos: " << puntos_usados[TRES] << "\n";
}

int Personaje::indice(int puntos_a_sumar) {
    if (puntos_a_sumar == 5)   return CERO;
    if (puntos_a_sumar == 10)    return UNO;
    if (puntos_a_sumar == 15)  return DOS;
    if (puntos_a_sumar == 20)  return TRES;
    return -1;
}

bool Personaje::levelear(int &habilidad, int puntos_usados[], int habilidades_mejoradas[]) {
    int puntos_a_sumar;
    int idx;
    
    cout << "Elige el porcentaje de mejora (5, 10, 15 o 20): ";
    cin >> puntos_a_sumar;

    idx = indice(puntos_a_sumar);

    if (puntos_a_sumar != 5 && puntos_a_sumar != 10 && puntos_a_sumar != 15 && puntos_a_sumar != 20) {
        cout << "Cantidad de puntos no valida. Intenta de nuevo.\n";
        return false;
    }

    if (idx == -1) {
        cout << "Porcentaje no valido. Intenta de nuevo.\n";
        return false;
    }

    if (puntos_usados[idx] == OCUPADO) {
        cout << "Ese porcentaje ya ha sido utilizado.\n";
        return false;
    }

    habilidad += puntos_a_sumar;
    puntos_usados[idx] = OCUPADO;
    return true;
}

bool Personaje::verificar_hab_libres(int habilidades_mejoradas[]){
    for (int i = 0; i < CANT_HAB; i++){
        if (habilidades_mejoradas[i] == LIBRE) return true;
    }
    return false;
}

Villano Juego::crear_villano(){
    int numero_villano;
    if (villanos.empty()) {
        cout << "No hay villanos cargados!\n";
        return Villano();
    }
    numero_villano = rand() % villanos.size(); //selecciona un villano aleatorio
    return villanos[numero_villano];
}

void Villano::imprimir_villano() const {
    cout << "\n     Nombre: " << nombre_str << endl;
    cout << "Numero: " << numero << endl;
    cout << "Fuerza: " << fuerza << endl;
    cout << "Reflejos: " << reflejos << endl;
    cout << "Velocidad: " << velocidad << endl;
    cout << "Vida: " << vida << endl;
    cout << "   Ataque:" << endl;
    cout << ataque_str << endl;
    cout << "El ataque especial le saca " << ataque_int << " al enemigo" << endl;
    cout << "   Defensa:" << endl;
    cout << defensa_str << endl;
    cout << "La defensa especial le saca " << defensa_int << " al ataque del enemigo" << endl;
}

void Juego::mostrar_villanos(){
    //lea el file txt de personajes
    char temp_nombre[TXT_MAX];
    char temp_ataque[TXT_MAX];
    char temp_defensa[TXT_MAX];

    Villano v{};
    int numero;
    int fuerza = 0;
    int reflejos = 0;
    int velocidad = 0;
    int vida = 0;
    string ataque, defensa, nombre;
    int ataque_int = 0;
    int defensa_int = 0;

    ifstream archivo("villanos.txt");
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    cout << "\n--- VILLANOS DISPONIBLES --- \n";

    while (getline(archivo, linea)) {
        if (linea.find("Nombre:") != std::string::npos) v.set_nombre_str(linea.substr(7));
        else if (linea.find("Numero:") != std::string::npos) v.set_numero(stoi(linea.substr(7)));
        else if (linea.find("Fuerza:") != std::string::npos) v.set_fuerza(stoi(linea.substr(7)));
        else if (linea.find("Reflejos:") != std::string::npos) v.set_reflejos(stoi(linea.substr(9)));
        else if (linea.find("Velocidad:") != std::string::npos) v.set_vel(stoi(linea.substr(10)));
        else if (linea.find("Vida:") != std::string::npos) v.set_vida(stoi(linea.substr(5)));
        else if (linea.find("Ataque:") != string::npos) {
            getline(archivo, linea);
            linea.erase(linea.find_last_not_of("\n\r")+1);
            v.set_ataque_str(linea);

            getline(archivo, linea);
            if (linea.find("Puntos de danio:") != string::npos)
                v.set_ataque_int(stoi(linea.substr(16)));
        }else if (linea.find("Defensa:") != string::npos) {
            getline(archivo, linea);
            linea.erase(linea.find_last_not_of("\n\r")+1);
            v.set_defensa_str(linea);

            getline(archivo, linea);
            if (linea.find("Puntos de defensa:") != string::npos)
                v.set_defensa_int(stoi(linea.substr(18)));
        }

        // AND enorme para verificar que todos los campos se hayan llenado
        if (!v.get_nombre().empty() && v.get_numero() && v.get_fuerza() && v.get_reflejos() && v.get_velocidad() && v.get_vida() && !v.get_ataque_str().empty() && v.get_ataque_int() && !v.get_defensa_str().empty() && v.get_defensa_int()) {
            villanos.push_back(v);
            v.imprimir_villano();
            v = Villano{}; // reiniciamos para el siguiente heroe
        }
    }
    cout << "\n";
    archivo.close();
}