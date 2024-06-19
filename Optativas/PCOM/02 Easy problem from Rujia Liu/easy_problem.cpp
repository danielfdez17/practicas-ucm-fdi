// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
using namespace std;


// función que resuelve el problema

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m; cin >> n >> m;
    if (!cin) return false;
    
    map<int, vector<int>> vec; // guarda para cada valor del vector un vector de sus apariciones
    
    for (int i = 0; i < n; i++) {
        int aux; cin >> aux;
        vec[aux].push_back(i + 1);
    }

    int k, v;
    for (int i = 0; i < m; i++) {
        cin >> k >> v;
        map<int, vector<int>>::iterator it = vec.find(v);
        // si el numero de apariciones de v es mayor o igual que k
        if (it != vec.end() && k <= (*it).second.size()) cout << (*it).second[k - 1] << "\n";
        else cout << "0\n";
    }
    
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     ifstream in("datos.txt");
     auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}