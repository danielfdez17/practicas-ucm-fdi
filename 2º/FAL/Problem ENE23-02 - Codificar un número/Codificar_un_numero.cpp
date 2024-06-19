#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//FUNCION RECURSIVA: con los parametros adicionales que necesites
void codificar(int n, int contador, int& c, int& mayorIzqquierda, int menorDerecha) {
    if (n < 10) {
        mayorIzqquierda = n;
        c = mayorIzqquierda * 3 + menorDerecha;
    }
    else {
        int modulo = n % 10;
        codificar(n / 10, contador + 1, c, mayorIzqquierda, std::min(menorDerecha, modulo));
        if (contador % 2 == 0) { // Digito en posicion par
            c = c + modulo * 2 + mayorIzqquierda;
        }
        else { // Digito en posicion impar
            c = c + modulo * 3 + menorDerecha;
        }
        mayorIzqquierda = std::max(mayorIzqquierda, modulo);
    }
}

//ANALISIS DEL COSTE
//RECURRENCIA: Sea m el numero de digitos del numero n
// T(m) = k si 0 <= m <= 1
// T(m) = T(m - 1) + k si m > 1
//COSTE ASINTOTICO: El coste del algoritmo es lineal en el numero de digitos que tiene el numero n: O(m)
// OTRA FORMA DE VERLO: Sea el numero n
// T(n) = k si 0 <= n < 10
// T(n) = T(n/10) + k si n >= 10
//COSTE ASINTOTICO: El coste del algoritmo es logaritmico en el numero n: O(log(n))


int resolver(int n) {
    int c, mayorIzquierda;
    //LLAMADA INICIAL A TU FUNCION
    codificar(n, 0, c, mayorIzquierda, std::numeric_limits<int>::max());
    return c;
}

void resuelveCaso() {
    int n;
    cin >> n;
    cout << resolver(n) << endl;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos = 0;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
