#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
#include <cctype>

using namespace std;

// ESTRUCTURA
struct Cancion {

    string nombre;
    string artista;
    string duracion;
    Cancion* siguiente;
    Cancion* anterior;
};

Cancion* inicio = NULL;
Cancion* fin = NULL;

// VALIDAR DURACION 00:00
bool validarDuracion(string duracion) {

    if (duracion.length() != 5)
        return false;

    if (duracion[2] != ':')
        return false;

    for (int i = 0; i < 5; i++) {

        if (i == 2)
            continue;

        if (!isdigit(duracion[i]))
            return false;
    }

    int segundos =
        (duracion[3] - '0') * 10 +
        (duracion[4] - '0');

    if (segundos > 59)
        return false;

    return true;
}

// AGREGAR CANCION
void agregarCancion() {

    Cancion* nueva = new Cancion();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n========== AGREGAR CANCION ==========\n";
    cout << "Nombre: ";
    getline(cin, nueva->nombre);
    cout << "Artista: ";
    getline(cin, nueva->artista);

    // VALIDAR FORMATO
    do {

        cout << "Duracion (00:00): ";
        getline(cin, nueva->duracion);

        if (!validarDuracion(nueva->duracion)) {

            cout << "Formato invalido.\n";
        }

    } while (!validarDuracion(nueva->duracion));


    // INSERTAR EN LISTA CIRCULAR
    if (inicio == NULL) {

        inicio = nueva;
        fin = nueva;

        nueva->siguiente = nueva;
        nueva->anterior = nueva;

    }
    else {

        fin->siguiente = nueva;
        nueva->anterior = fin;

        nueva->siguiente = inicio;
        inicio->anterior = nueva;

        fin = nueva;
    }

    cout << "\nCancion agregada correctamente.\n";
}

// MOSTRAR LISTA CiRCULAR
void mostrarLista() {

    if (inicio == NULL) {
        cout << "\nNo hay canciones.\n";
        return;
    }

    Cancion* aux = inicio;
    cout << "\n========================================\n";
    cout << "         PLAYLIST CIRCULAR              \n";
    cout << "========================================\n\n";

    do {

        cout << "[ "
             << aux->nombre
             << " - "
             << aux->artista
             << " ("
             << aux->duracion
             << ") ]";

        aux = aux->siguiente;
        if (aux != inicio) {
            cout << " <-> ";
        }

    } while (aux != inicio);
    cout<<"\n";

}
// MOSTRAR TODAS LAS CANCIONES
void mostrarListaCompleta() {

    if (inicio == NULL) {

        cout << "\nNo hay canciones registradas.\n";
        return;
    }

    Cancion* aux = inicio;
    int contador = 1;
    cout << "\n========================================\n";
    cout << "        LISTA COMPLETA DE CANCIONES     \n";
    cout << "========================================\n";

    do {

        cout << "\nCancion: " << contador << endl;
        cout << "Nombre: " << aux->nombre << endl;
        cout << "Artista: " << aux->artista << endl;
        cout << "Duracion: " << aux->duracion << endl;
        cout << "----------------------------------------\n";
        aux = aux->siguiente;
        contador++;
    } while (aux != inicio);
}

// REPRODUCTOR
void mostrarCancion(Cancion* actual) {

    system("cls");

    cout << "========================================\n";
    cout << "         REPRODUCTOR MUSICAL            \n";
    cout << "========================================\n\n";

    cout << "Reproduciendo:\n\n";

    cout << "Nombre: " << actual->nombre << endl;
    cout << "Artista: " << actual->artista << endl;
    cout << "Duracion: " << actual->duracion << endl;

    cout << "\n========================================\n";
    cout << "Flecha derecha  -> Siguiente\n";
    cout << "Flecha izquierda -> Anterior\n";
    cout << "ESC -> Menu principal\n";
    cout << "========================================\n";
}

// REPRODUCIR PLAYLIST
void reproducirPlaylist() {
    if (inicio == NULL) {
        cout << "\nNo hay canciones.\n";
        return;
    }

    Cancion* actual = inicio;
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

// LIBERAR MEMORIA
void liberarMemoria() {

    if (inicio == NULL)
        return;

    Cancion* actual = inicio;
    Cancion* siguiente;

    do {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;

    } while (actual != inicio);

    inicio = NULL;
    fin = NULL;
}

// MAIN
int main() {
    int opcion;
    do {

        cout << "\n========================================\n";
        cout << "      REPRODUCTOR DE MUSICA             \n";
        cout << "========================================\n";

        cout << "1. Agregar cancion\n";
        cout << "2. Mostrar lista completa\n";
        cout << "3. Mostrar playlist circular\n";
        cout << "4. Reproducir playlist\n";
        cout << "5. Salir\n";
        cout << "\nSeleccione una opcion: ";
            while (!(cin >> opcion)) {
            cout << "\nError: debe ingresar un numero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nSeleccione una opcion: ";
        }

        switch (opcion) {

            case 1:
                agregarCancion();
                break;
            case 2:
                mostrarListaCompleta();
                break;
            case 3:
                mostrarLista();
                break;
            case 4:
                reproducirPlaylist();
                break;
            case 5:
                liberarMemoria();
                cout << "\nMemoria liberada correctamente.\n";
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}



