#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
#include <cctype>

using namespace std;

struct Cancion {
    string nombre;
    string artista;
    string duracion;
    Cancion* siguiente;
    Cancion* anterior;
};

Cancion* primero = nullptr;
Cancion* ultimo = nullptr;

// VALIDAR FORMATO 00:00
bool validarDuracion(string duracion) {

    if (duracion.length() != 5)
        return false;

    if (duracion[2] != ':')
        return false;

    if (!isdigit(duracion[0]) ||
        !isdigit(duracion[1]) ||
        !isdigit(duracion[3]) ||
        !isdigit(duracion[4]))
        return false;

    int minutos = stoi(duracion.substr(0, 2));
    int segundos = stoi(duracion.substr(3, 2));

    if (segundos > 59)
        return false;

    return true;
}

void agregarCancion() {

    Cancion* nuevo = new Cancion();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n--- AGREGAR CANCION ---\n";

    cout << "Nombre: ";
    getline(cin, nuevo->nombre);

    cout << "Artista: ";
    getline(cin, nuevo->artista);

    // VALIDAR DURACION
    do {

        cout << "Duracion (00:00): ";
        getline(cin, nuevo->duracion);

        if (!validarDuracion(nuevo->duracion)) {
            cout << "Formato invalido. \nEjemplo correcto: 03:45\n";
        }

    } while (!validarDuracion(nuevo->duracion));

    // INSERTAR EN LISTA CIRCULAR
    if (primero == nullptr) {

        primero = nuevo;
        ultimo = nuevo;

        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;

    } else {

        nuevo->siguiente = primero;
        nuevo->anterior = ultimo;

        ultimo->siguiente = nuevo;
        primero->anterior = nuevo;

        ultimo = nuevo;
    }

    cout << "\nCancion agregada correctamente.\n";
}

void mostrarListaCompleta() {

    if (primero == nullptr) {
        cout << "\nLa playlist esta vacia.\n";
        return;
    }

    Cancion* actual = primero;

    int contador = 1;

    cout << "\n===== PLAYLIST =====\n";

    do {

        cout << contador << ". "
             << actual->nombre
             << " - "
             << actual->artista
             << " ["
             << actual->duracion
             << "]\n";

        actual = actual->siguiente;
        contador++;

    } while (actual != primero);
}

void mostrarCancion(Cancion* actual) {

    system("cls");

    cout << "=============================\n";
    cout << "     REPRODUCTOR MUSICAL     \n";
    cout << "=============================\n\n";

    cout << "Reproduciendo:\n\n";

    cout << "Nombre   : " << actual->nombre << endl;
    cout << "Artista  : " << actual->artista << endl;
    cout << "Duracion : " << actual->duracion << endl;

    cout << "\n=============================\n";
    cout << "Flecha derecha  -> Siguiente\n";
    cout << "Flecha izquierda -> Anterior\n";
    cout << "ESC -> Salir\n";
    cout << "=============================\n";
}

void reproducirPlaylist() {

    if (primero == nullptr) {
        cout << "\nNo hay canciones en la playlist.\n";
        return;
    }

    Cancion* actual = primero;

    mostrarCancion(actual);

    while (true) {

        int tecla = _getch();

        // ESC
        if (tecla == 27) {
            break;
        }

        // FLECHAS
        if (tecla == 0 || tecla == 224) {

            tecla = _getch();

            // DERECHA
            if (tecla == 77) {

                actual = actual->siguiente;
                mostrarCancion(actual);

            }
            // IZQUIERDA
            else if (tecla == 75) {

                actual = actual->anterior;
                mostrarCancion(actual);
            }
        }
    }
}

int main() {

    int opcion;

    do {

        cout << "\n===== MENU =====\n";
        cout << "1. Agregar cancion\n";
        cout << "2. Mostrar lista completa\n";
        cout << "3. Reproducir playlist\n";
        cout << "4. Salir\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1:
                agregarCancion();
                break;

            case 2:
                mostrarListaCompleta();
                break;

            case 3:
                reproducirPlaylist();
                break;

            case 4:
                cout << "\nSaliendo del programa...\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 4);

    return 0;
}