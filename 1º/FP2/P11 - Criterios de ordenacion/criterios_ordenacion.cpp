// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: P11 Criterios de ordenacion
// Comentario general sobre la solución: Numero de casos ilimitados


#include <iostream>
#include <fstream>
using namespace std;
// Constante que delimita el numero maximo de alojamientos
const int ALOJAMIENTOS = 100;
// Estructura que contiene la informacion de los alojamientos
struct tAlojamiento {
    string nombre;
    int puntuacion;
    int disancia;
    int precio;
};
// Array de alojamientos
typedef tAlojamiento tArrayAlojamientos[ALOJAMIENTOS];
// Estructura que almacena la lista de alojamientos
struct tLista {
    tArrayAlojamientos alojamientos;
    int contador = 0;
};


/*
Los datos de entrada se almacenan en un array que se ordenara siguiendo los criterios.
Se mostrara el array ordenado segun cada criterio
Se utilizara como criterio ppal la puntuacion sobrecargando el operador > y para la distancia
y el precio se utilizara funciones
*/

// Funcion que devuelve true si el alojamiento izq es mayor que el dcho y false en caso contrario
bool operator>(tAlojamiento al1, tAlojamiento al2);
// Procedimiento que ordena la lista de mayor a menor segun la puntuacion
void ordenarPuntuacion(tLista& lista);
// Procedimiento que ordena la lista de mayor a menor teniendo en cuenta la distancia
void ordenarDistancia(tLista& lista);
// Procedimiento que ordena la lista de mayor a menor teniendo en cuenta el precio
void ordenarPrecio(tLista& lista);
// Procedimiento que muestra la lista
void mostrar(const tLista& lista);

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("out.txt");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}

bool operator>(tAlojamiento al1, tAlojamiento al2) {
    return al1.puntuacion > al2.puntuacion;
}
void ordenarPuntuacion(tLista& lista) {
    bool intercambio = true;
    tAlojamiento aux;
    int i = 0; // Variable que representa el contador que recorre la lista
    while ((i < lista.contador - 1) && intercambio) {
        intercambio = false;
        for (int j = lista.contador - 1; j > i; j--) {
            if (lista.alojamientos[j] > lista.alojamientos[j - 1]) {
                intercambio = true;
                aux = lista.alojamientos[j];
                lista.alojamientos[j] = lista.alojamientos[j - 1];
                lista.alojamientos[j - 1] = aux;
            }
            else if (lista.alojamientos[j].puntuacion == lista.alojamientos[j - 1].puntuacion) {
                if (lista.alojamientos[j].nombre < lista.alojamientos[j - 1].nombre) {
                    intercambio = true;
                    aux = lista.alojamientos[j];
                    lista.alojamientos[j] = lista.alojamientos[j - 1];
                    lista.alojamientos[j - 1] = aux;
                }
            }
        }
        if (intercambio) {
            i++;
        }
    }
}

void ordenarDistancia(tLista& lista) {
    // Utilizando el metodo de la burbuja mejorado
    bool intercambio = true; // Variable que indica si se debe hacer intercambio o no
    int i = 0; // Variable que representa el contador con el que recorrer la lista
    tAlojamiento aux; // Variable auxiliar con la que poder hacer los intercambios
    // Desde el primer elemento hasta el penultimo si hay intercambios
    while ((i < lista.contador - 1) && intercambio) {
        intercambio = false;
        // Desde el ultimo elemento hasta el siguiente a i
        for (int j = lista.contador - 1; j > i; j--) {
            if (lista.alojamientos[j].disancia < lista.alojamientos[j - 1].disancia) {
                intercambio = true;
                aux = lista.alojamientos[j];
                lista.alojamientos[j] = lista.alojamientos[j - 1];
                lista.alojamientos[j - 1] = aux;
            }
            else if (lista.alojamientos[j].disancia == lista.alojamientos[j - 1].disancia) {
                if (lista.alojamientos[j].nombre < lista.alojamientos[j - 1].nombre) {
                    intercambio = true;
                    aux = lista.alojamientos[j];
                    lista.alojamientos[j] = lista.alojamientos[j - 1];
                    lista.alojamientos[j - 1] = aux;
                }
            }
        }
        if (intercambio) {
            i++;
        }
    }
}

void ordenarPrecio(tLista& lista) {
    // Utilizando el metodo de la burbuja mejorado
    bool intercambio = true; // Variable que indica si se debe hacer intercambio o no
    int i = 0; // Variable que representa el contador con el que recorrer la lista
    tAlojamiento aux; // Variable auxiliar con la que poder hacer los intercambios
    // Desde el primer elemento hasta el penultimo si hay intercambios
    while ((i < lista.contador - 1) && intercambio) {
        intercambio = false;
        // Desde el ultimo elemento hasta el siguiente a i
        for (int j = lista.contador - 1; j > i; j--) {
            if (lista.alojamientos[j].precio < lista.alojamientos[j - 1].precio) {
                intercambio = true;
                aux = lista.alojamientos[j];
                lista.alojamientos[j] = lista.alojamientos[j - 1];
                lista.alojamientos[j - 1] = aux;
            }
            else if (lista.alojamientos[j].precio == lista.alojamientos[j - 1].precio) {
                if (lista.alojamientos[j].nombre < lista.alojamientos[j - 1].nombre) {
                    intercambio = true;
                    aux = lista.alojamientos[j];
                    lista.alojamientos[j] = lista.alojamientos[j - 1];
                    lista.alojamientos[j - 1] = aux;
                }
            }
        }
        if (intercambio) {
            i++;
        }
    }
}

void mostrar(const tLista& lista) {
    for (int i = 0; i < lista.contador; i++) {
        cout << lista.alojamientos[i].nombre << " ";
    }
    cout << endl;
}

bool resuelveCaso() {
    tLista lista;
    int hoteles = 0; // Variable que guarda el numero de hoteles
    // leer los datos de la entrada
    cin >> hoteles;
    if (hoteles < ALOJAMIENTOS) {
        for (lista.contador = 0; lista.contador < hoteles; lista.contador++) {
            cin >> lista.alojamientos[lista.contador].nombre >>
                lista.alojamientos[lista.contador].puntuacion >>
                lista.alojamientos[lista.contador].disancia >>
                lista.alojamientos[lista.contador].precio;
        }
    }
    if (!std::cin)  // fin de la entrada
        return false;

    ordenarPuntuacion(lista);
    mostrar(lista);
    ordenarDistancia(lista);
    mostrar(lista);
    ordenarPrecio(lista);
    mostrar(lista);

    // escribir sol

    return true;
}
