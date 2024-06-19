// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<algorithm>
using namespace std;

string T, P;
vector<int>b; // back table
int n, m;//tamaño de T, tamaño de P
int t;//posicion del patron desde vamos a mostrar 
/* Otra aplicacion del KMP:
Dada una cadena, encontrar la longitud minima de una subcadena que se repite N veces
para formar la cadena.

- Si alguna cadena se repite, su longitud debe ser: l = cadena.size() - b[b.size() - 1]
- Si (cadena.size() % l == 0) es la cadena que queremos
- Else la longitud minima es la longitud de la cadena
*/
// O(pattern size) === O(m)
void kmpPreprocess() { // before calling kmpSearch
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        ++i; ++j;
        b[i] = j;
     }
}

// (O(text size) === O(n)) + O(m)
void kmpSearch() {
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && T[i] != P[j])
            j = b[j]; // different reset j using b
        ++i;++j;
        /*
        if (j == m) {
            printf("P si found at index %d in T\n", i - j);
            //j = b[j];
        }
        */
        
    }
    t = j;
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    cin >> T;
    if (!cin) return false;
    n = T.size();
    P = T;
    reverse(P.begin(), P.end());
    m = P.size();
    b.resize(m + 1);
    //cout << T << "\n";
    //cout << P << "\n";
    kmpPreprocess();
    /*
    for (int i = 0; i < b.size(); i++) {
        cout << b[i];
    }
    cout << endl;
    */
    kmpSearch();
    cout << T;
    //cout <<t<<endl;
    if (t != T.size()) {
        for (int i = t; i < P.size(); i++) {
            cout << P[i];
        }
    }
    cout<<endl;

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