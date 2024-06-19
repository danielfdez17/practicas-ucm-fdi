// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_SIZE 1e6

vector<int>parents, sizes;

void make_set(int v) {
    if (parents[v] == -1) {
        parents[v] = v;
        sizes[v] = 1;
    }
}

int get_parent(int v) {
    if (parents[v] == v) return v;
    return parents[v] = get_parent(parents[v]);
}

void merge(int i, int j) {
    i = get_parent(i); j = get_parent(j);
    if (i != j) {
        if (sizes[i] < sizes[j]) {
            int aux = i;
            i = j;
            j = aux;
        }
        parents[j] = i;
        sizes[i] += sizes[j];
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int a, b; cin >> a >> b;
    if (!cin) return false;
        
    int refusals = 0;
    parents.assign(MAX_SIZE, -1);
    sizes.assign(MAX_SIZE, 0);

    make_set(a);
    make_set(b);
    merge(a, b);

    while (cin >> a) {
        if (a == -1) break;
        cin >> b;
        
        make_set(a);
        make_set(b);

        a = get_parent(a);
        b = get_parent(b);
        if (a == b) refusals++;
        else merge(a, b);
    }
    cout << refusals << "\n";
    return true;    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
        std::ifstream in("datos.txt");
        auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
        #endif 


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
        #ifndef DOMJUDGE // para dejar todo como estaba al principio
        std::cin.rdbuf(cinbuf);
        system("PAUSE");
        #endif

    return 0;
}