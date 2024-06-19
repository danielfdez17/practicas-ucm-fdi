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
int n, m;

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
        ++i; ++j;
        if (j == m) {
            printf("P si found at index %d in T\n", i - j);
            j = b[j];
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    cin >> T;
    if (!cin) return false;
    n = T.size();

    string str = T;
    reverse(str.begin(), str.end());
    if (T == str) {
        cout << T << "\n";
    }
    else {
        P = "";
        int i = 1; 
        char last = T[n - 1];
        P.push_back(last);
        while (i < n && str[i] != last) {
            P.push_back(str[i]);
            i++;
        }
        P.push_back(last);
        int psize = P.size(), tsize = T.size();
        string to_append = "";
        if (psize > tsize) {
            to_append =     
        }
        int strsize = tsize - psize;
        to_append = str.substr(tsize - strsize, tsize);
        cout << T << to_append << "\n";
    }


    // string str = T;
    // reverse(str.begin(), str.end());
    // P = "";
    // char first = str[0];
    // int i = 1, j = str.size();
    // P.push_back(first);
    // j -= 2;
    // while (i < str.size() && j >= 0 && str[i] == T[j]) {
    //     P.push_back(str[i]);
    //     ++i; --j;
    // }
    // if (i != str.size() && j != 0) 
    //     cout << T.append(str) << "\n";
    // else
    //     cout << T << "\n";
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