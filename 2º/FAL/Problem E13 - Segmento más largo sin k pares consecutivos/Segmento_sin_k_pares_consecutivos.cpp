#include<iostream>
#include<fstream>
#include<vector>
using namespace std;


/*
* A) todosPares(v,p,q) = forall j : p <= j <= q : v[j] % 2 == 0
* B) noMas(v,p,q,k) = todosPares(v,p,q) <=> q - p <= k
* 
* ESPECIFICACION: fun resolver(vector<int>const&v, int size, int k) ret int (maxSeg)
*
* PRECONDICION: {
* size >= 0
* &&
* forall u : 0 <= u < size : v[u] > 0
* &&
* k >= 0
* }
*
* POSTCONDICION: {
* maxSeg = max p,q : 0 <= p <= q < size : noMas(v,p,q,k) : q - p
* &&
* pares = p,q : 0 <= p <= q < size : todosPares(v,p,q) : q - p
* &&
* seg = p,q : 0 <= p <= q < size : noMas(v,p,q,k) : q - p
* }
*
* INVARIANTE: {
* 0 <= i <= size
* &&
* maxSeg = max p,q : 0 <= p <= q < i : noMas(v,p,q,k) : q - p
* &&
* pares = p,q : 0 <= p <= q < i : todosPares(v,p,q) : q - p
* &&
* seg = p,q : 0 <= p <= q < i : noMas(v,p,q,k) : q - p
* }
*
* FUNCION DE COTA: size - i
* ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre size veces.
*   Por tanto, el coste del algoritmo pertenece a O(1) * size = O(size)
*/

int resolver(vector<int>const& v, int size, int k) {
    // Si el numero maximo de elementos pares consecutivos es mayor o igual a la longitud del vector, se devuelve la longitud del vector
    if (k >= size) return size;
    int seg = 0, maxSeg = 0, pares = 0;
    for (int i = 0; i < size; i++) {
        if (v[i] % 2 == 0)
            pares++;
        else 
            pares = 0;
        if (pares > k) {
            pares = k;
            seg = k;
        }
        else
            seg++;
        maxSeg = max(seg, maxSeg);
    }
    return maxSeg;
}


bool resuelveCaso() {
    int size, k; cin >> size >> k;
    vector<int> v(size);
    for (int& i : v)cin >> i;
    cout << resolver(v, size, k) << "\n";
    return true;
}



int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
