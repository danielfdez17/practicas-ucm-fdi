// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: P37-MEMORIA DINAMICA 2
// Comentario general sobre la solución: Número de casos delimitado por un valor centinela


#include <iostream>
#include <fstream>
using namespace std;

// Constante que delimita el tamaño inicial de todos los objetos
const int TAMANIO = 3;

struct tObjeto { // Estructura que contiene la información de un objeto
    string nombre;
    int unidades = 0;
};
// Puntero a objeto
typedef tObjeto* tPtrObjeto;
// Se declara un vector dinamico, con info sobre su tamaño y sobre el nº de elementos que tiene
struct tLista { // Estructura que contiene la lista de objetos
    tPtrObjeto objetos{};
    int mem_reservada = TAMANIO;
    int contador = 0;
};

// Procedimiento que aumenta la cantidad de unidades de un objeto existente
void aumentar(tLista& lista, string nombre, int unidades);
// Procedimiento que disminuye la cantidad de unidades de un objeto existente
void restar(tLista& lista, string nombre, int unidades);
// Procedimiento que muestra una lista con el objeto y sus unidades
void listar(const tLista& lista);
// Función que busca un objeto en la lista de objetos
int buscar(const tLista& lista, string nombre);
// Procedimiento que libera la memoria dinámica usada por la lista
void liberar(tLista& lista);

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    char op;
    tLista lista{};
    string nombre;
    int unidades;
    // leer los datos de la entrada
    cin >> op;
    lista.objetos = new tObjeto[TAMANIO];
    while (op != 'F') {
        switch (op) {
        case 'A':
            cin >> nombre >> unidades;
            aumentar(lista, nombre, unidades);
            break;
        case 'R':
            cin >> nombre >> unidades;
            restar(lista, nombre, unidades);
            break;
        case 'L':
            listar(lista);
            break;
        }
        cin >> op;
    }
    // escribir sol
    if (op == 'F') {
        liberar(lista);
        return false;
    }
    liberar(lista);
    return true;
}

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

// Si la lista se llena, aumentar al doble
void aumentar(tLista& lista, string nombre, int unidades) {
    if (lista.contador == lista.mem_reservada) { // Si la lista está llena
        tLista aux; // Lista auxiliar
        aux.mem_reservada = lista.mem_reservada * 2; // Aumenta capacidad
        aux.contador = lista.contador; // Se copia el contador
        aux.objetos = new tObjeto[aux.mem_reservada]; // Se reserva la memoria
        for (int i = 0; i < lista.contador; i++) { // Se copian los datos
            aux.objetos[i] = lista.objetos[i];
        }
        delete[]lista.objetos; // Se libera la memoria obsoleta
        lista.objetos = NULL;
        lista = aux; // Se asigna la nueva dirección de memoria
    }
    int i = buscar(lista, nombre);
    if (i != -1) {
        lista.objetos[i].unidades += unidades;
    }
    else {
        lista.objetos[lista.contador].nombre = nombre;
        lista.objetos[lista.contador].unidades = unidades;
        lista.contador++;
    }
}
// Si no existe el objeto del que se quieren restar unidades, no se hace nada
// Si se restan más unidades de las que hay, se queda a 0
void restar(tLista& lista, string nombre, int unidades) {
    int i = buscar(lista, nombre);
    if (i != -1) {
        lista.objetos[i].unidades -= unidades;
        if (lista.objetos[i].unidades < 0) {
            lista.objetos[i].unidades = 0;
        }
    }
}
// Ni idea de como empezar
void listar(const tLista& lista) {
    for (int i = 0; i < lista.contador; i++) {
        cout << lista.objetos[i].nombre << " " << lista.objetos[i].unidades << endl;
    }
    cout << "---" << endl;
}

int buscar(const tLista& lista, string nombre) {
    int i = 0, pos = -1;
    bool encontrado = false;
    while ((i < lista.contador) && !encontrado) {
        if (nombre == lista.objetos[i].nombre) {
            encontrado = true;
            pos = i;
        }
        if (!encontrado) {
            i++;
        }
    }
    return pos;
}

void liberar(tLista& lista) {
    delete[]lista.objetos;
    lista.objetos = NULL;
    lista.contador = 0;
    lista.mem_reservada = 0;
}
