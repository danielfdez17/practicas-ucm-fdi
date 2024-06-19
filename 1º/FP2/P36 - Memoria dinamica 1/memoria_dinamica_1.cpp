// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: P36-MEMORIA DINÁMICA 1
// Comentario general sobre la solución: Número de casos delimitado por un valor centinela


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int TAMAÑO = 50; // Constante que delimita el tamaño de la matriz
const int IMAGENES = 200; // Constante que delimita el número máximo de fotos

typedef int tMatriz[TAMAÑO][TAMAÑO]; // Matriz que contiene la imagen de la fotografía

struct tFoto { // Estructura que contiene la información de una foto
    string titulo;
    string tema;
    tMatriz matriz{};
};

typedef tFoto* tFotoPtr; 
typedef tFotoPtr tArrayTitulos[IMAGENES]; // Array de datos dinámicos que almacena los titulos de las fotos
typedef tFotoPtr tArrayTemas[IMAGENES]; // Array de datos dinámicos que almacena los temas de las fotos

struct tListaFotos { // Estructura que contiene la lista de las imágenes
    tArrayTitulos lista_titulos;
    tArrayTemas lista_temas;
    int contador = 0;
};

// Función que recibe la lista de fotos y una foto y devuelve true si la inserta en la lista de fotos y false en caso contrario
bool insertarFoto(tListaFotos& lista, tFoto foto);
// Procedimiento que recibe la lista de fotos y libera la memoria dinámica usada
void liberar(tListaFotos& lista);

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
//void resolver

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



bool insertarFoto(tListaFotos& lista, tFoto foto) {
    bool ok = true;
    if (lista.contador == IMAGENES) {
        ok = false;
    }
    else {
        for (int i = 0; i < TAMAÑO; i++) {
            for (int j = 0; j < TAMAÑO; j++) {
                lista.lista_temas[lista.contador]->matriz[i][j] = lista.contador;
            }
        }
        for (int i = 0; i < TAMAÑO; i++) {
            for (int j = 0; j < TAMAÑO; j++) {
                lista.lista_titulos[lista.contador]->matriz[i][j] = lista.contador;
            }
        }
        lista.lista_titulos[lista.contador] = new tFoto(foto);
        lista.lista_temas[lista.contador] = new tFoto(foto);
        lista.contador++;
    }
    return ok;
}

void liberar(tListaFotos& lista) {
    for (int i = 0; i < lista.contador; i++) {
        delete lista.lista_temas[i];
        delete lista.lista_titulos[i];
    }
    lista.contador = 0;
}

bool resuelveCaso () {
    int fotos;
    // leer los datos de la entrada
    cin >> fotos;
    if (fotos == 0)
        return false;

    

    // escribir sol

    return true;
}
