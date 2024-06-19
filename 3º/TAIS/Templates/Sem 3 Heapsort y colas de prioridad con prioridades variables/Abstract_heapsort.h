#include<iostream>
#include<vector>
#include "IndexPQ.h"
using namespace std;

template<typename T>
void heapsor_abstracto(vector<T>&v) { //O(N log N) y O(N) en espacio adicional
    PriorityQueue<T>colap;
    for (auto const&e : v) 
        colap.push(e);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = colap.top();
        colap.pop();
    }
}

template <typename T, typename Comparador = std::less<T>>
void heapsort(std::vector<T> & v, Comparador cmp = Comparador()) {
    // monticulizar
    for (int i = (v.size() - 1) / 2; i >= 0; --i)
        hundir_max(v, v.size(), i, cmp);
    // ordenar
    for (int i = v.size() - 1; i > 0; --i) {
        std::swap(v[i], v[0]);
        hundir_max(v, i, 0, cmp);
    }
}

template <typename T, typename Comparador>
void hundir_max(std::vector<T> & v, int N, int j, Comparador cmp) {
    // montículo en v en posiciones de 0 a N-1
    T elem = v[j];
    int hueco = j;
    int hijo = 2 * hueco + 1; // hijo izquierdo, si existe
    while (hijo < N) {
        // cambiar al hijo derecho si existe y va antes que el izquierdo
        if (hijo + 1 < N && cmp(v[hijo], v[hijo + 1]))
            ++hijo;
        // flotar el hijo mayor si va antes que el elemento hundiéndose
        if (cmp(elem, v[hijo])) {
            v[hueco] = v[hijo];
            hueco = hijo; 
            hijo = 2 * hueco + 1;
        } else break;
    }
    v[hueco] = elem;
}

// Llamada: heapsort(datos, ComparaString());
// Ejemplo
class ComparaString { public:
bool operator()(std::string const& a, std::string const& b) {
    int i = 0;
    while (i != a.length()) {
        if (i == b.length() || tolower(b[i]) < tolower(a[i])) return false;
        else if (tolower(a[i]) < tolower(b[i])) return true;
        ++i;
    }
    return i != b.length();
    }
};
