
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la soluci�n.
 * Luis Rebollo Cocera: TAIS 53
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <string>
#include <fstream>
#include"Matriz.h"
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 canciones(i, j) = numero de canciones comunes que hay hasta la cancion i de la lista 1 y hasta la cancion j de la lista 2

 canciones(0, j) = canciones(i, 0) = 0
 canciones(i, j) = 1 si lista1[i] == lista2[j]
 canciones(i, j) = 0 en otro caso

 COSTE EN ESPACIO: Sea n el numero de filas y m el numero de columnas, el coste en espacio adicional esta en O(n*m), ya que se utiliza una tabla que almacena en numero de canciones que coinciden para cualquier posicion i,j dada
 COSTE EN TIEMPO: Sea n el numero de filas y m el numero de columnas, el coste en tiempo pertenece a O(n*m)
    int canciones(i, j, dp, lista1, lista2): O(lista1.size() * lista2.size()), ya que se recorren todos los elementos de la matriz
    void reconstruir(dp, canciones, sol, lista1, lista2): O(lista1.size() + lista2.size()) en el caso peor, ya que se recorreria la matriz por los laterales hasta llegar a la posicion dp[lista1.size() - 1][lista2.size() - 1]
        // => Avanza primero la i desde 0 a lista1.size(), y despues avanza la j desde 0 hasta lista2.size(), o viceversa
 TIPO DE PROGRAMACION DINAMICA: descendente porque baja del problema original hasta llegar a los casos base

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

 
 /*
 int caso(vector<vector<int>>& m, int i, int j, const vector<string>& luno,const vector<string>& ldos) {

    if (i < 0 || j < 0) { return 0; }
    
    if (i == 0 && j == 0) {
        if (luno[i] == ldos[j]) {
            m[i][j] = 1;
            return 1;
        }
        else {   
            m[i][j] = 0;
            return 0;
        }
    }

    if (m[i][j] == -1) {
        if (luno[i] == ldos[j]) {
            m[i][j] = caso(m, i-1, j-1, luno, ldos) + 1;
        }
        else {
            m[i][j] = max(caso(m, i-1, j, luno, ldos), caso(m, i, j-1, luno, ldos));
        }
    }

    return m[i][j];
}
 */

int canciones(int i, int j, Matriz<int>& dp, vector<string>const&lista1, vector<string>const&lista2) {
    // CB
    if (i < 0 || j < 0) 
        return 0;
    if (dp[i][j] != -1) 
        return dp[i][j];
    // CB
    if (i == 0 && j == 0) {
        if (lista1[i] == lista2[j]) {
            return dp[i][j] = 1;
        }
        return dp[i][j] = 0;
    }
    // CB
    if (lista1[i] == lista2[j]) {
        return dp[i][j] = canciones(i - 1, j - 1, dp,  lista1, lista2) + 1;
    }
    return dp[i][j] = max(canciones(i - 1, j, dp,  lista1, lista2), canciones(i, j - 1, dp,  lista1, lista2));
}

/*
int rec(const vector<string>& l1, const vector<string>& l2, vector<string>& sol, const vector<vector<int>>& m, int i, int j, int c) {

    if (c == 0) { return 0; }

    if (i == 0 && j == 0) {

        if (l1[i] == l2[j]) {
            sol.push_back(l1[i]);
            c--;
            return 0;
        }
    }
    
    if (i == 0 && j > 0) {
        if (l1[i] == l2[j]) {
            sol.push_back(l1[i]);
            c--;
            return 0;
        }
        rec(l1, l2, sol, m, i, j - 1, c);
    
    }
    else if (j == 0 && i > 0) {
        if (l1[i] == l2[j]) {
            sol.push_back(l1[i]);
            c--;
            return 0;
        }
        rec(l1, l2, sol, m, i -1, j, c);
    }
    else {
    
        if (l1[i] == l2[j]) {
            sol.push_back(l1[i]);
            c--;
            rec(l1, l2, sol, m, i - 1, j -1, c);
        }
        else {
        
            if (m[i][j] == m[i][j - 1]) {
                rec(l1, l2, sol, m, i, j - 1, c);
            }
            else {
                rec(l1, l2, sol, m, i - 1, j, c);
            }
        }

    }
    return 0;
}
*/

void reconstruir(int i, int j, Matriz<int>const&dp, int&canciones, vector<string>&sol, vector<string>const&lista1, vector<string>const&lista2) {
    if (canciones == 0) return;
    if (i == 0 && j == 0) {
        if (lista1[i] == lista2[j]) {
            sol.push_back(lista1[i]);
            --canciones;
            return;
        }
    }
    if (i == 0 && j > 0) {
        if (lista1[i] == lista2[j]) {
            sol.push_back(lista1[i]);
            --canciones;
            return;
        }
        reconstruir(i, j - 1, dp, canciones, sol, lista1, lista2);
    }
    if (j == 0 && i > 0) {
        if (lista1[i] == lista2[j]) {
            sol.push_back(lista1[i]);
            --canciones;
            return;
            reconstruir(i - 1, j, dp, canciones, sol, lista1, lista2);
        }
    }
    if (lista1[i] == lista2[j]) {
        sol.push_back(lista1[i]);
        --canciones;
        reconstruir(i - 1, j - 1, dp, canciones, sol, lista1, lista2);
        return;
    }
    if (dp[i][j] == dp[i][j - 1]) {
        reconstruir(i, j - 1, dp, canciones, sol, lista1, lista2);
        return;
    }
    if (dp[i][j] == dp[i - 1][j]) {
        reconstruir(i - 1, j, dp, canciones, sol, lista1, lista2);
        return;
    }
}

// void reconstruir(Matriz<int>const&dp, int canciones, vector<string>&sol, vector<string>const&lista1, vector<string>const&lista2) {
//     // cout << dp << "\n";
//     int i = dp.numfils() - 1, j = dp.numcols() - 1;
//     while (i >= 0 && canciones != 0) {
//         j = dp.numcols() - 1;
//         while (j >= 0 && canciones != 0) {
//             if (lista2[i] == lista1[j]) {
//                 --canciones;
//                 sol.push_back(lista2[i]);
//                 --i; --j;
//             }
//             else {
//                 // Si se puede avanzar en las filas
//                 if ((i - 1 > 0 || j == 0 && i > 0) && dp[i][j] == dp[i - 1][j]) {
//                     --i;
//                 }
//                 // Si se puede avanzar en las columnas
//                 else if ((j - 1 > 0 || i == 0 && j > 0) && dp[i][j] == dp[i][j - 1]) {
//                     --j;
//                 }
//                 // Si solo se puede avanzar en las filas
//                 // else if (j == 0 && i > 0 && dp[i][j] == dp[i - 1][j]) {
                    
//                 // }
//                 // // Si solo se puede avanzar en las columnas
//                 // else if (i == 0 && j > 0 && dp[i][j] == dp[i][j - 1]) {

//                 // }
//             }
//         }
//     }

//     // while (i < filas && canciones != 0) {
//     //     j = 0;
//     //     while (j < columnas && canciones != 0) {
//     //         if (lista1[i] == lista2[j]) {
//     //             --canciones;
//     //             sol.push_back(lista1[i]);
//     //             ++i; ++j;
//     //         }
//     //         else {
//     //             if (i + 1 < filas && dp[i][j] == dp[i + 1][j]) {
//     //                 i++;
//     //             }
//     //             else if (j + 1 < columnas && dp[i][j] == dp[i][j + 1]) {
//     //                 j++;
//     //             }
//     //         }
//     //     }
//     // }
// }

vector<string> canciones(vector<string>const& lista1, vector<string>const& lista2) {
    int filas = lista1.size(), columnas = lista2.size();
    Matriz<int>dp(columnas, filas, -1);
    vector<string>sol;
    int c = canciones(columnas - 1, filas - 1, dp, lista2, lista1);
    reconstruir(columnas - 1, filas - 1, dp, c, sol, lista2, lista1);
    return sol;
}

 bool resuelveCaso() {

    string s; cin >> s;
    if (!std::cin) return false;
    vector<string>lista1, lista2;
    lista1.push_back(s);
    while (cin.peek() != '\n') {
        cin >> s; 
        lista1.push_back(s);
    }
    cin.ignore();
    while (cin.peek() != '\n') {
        cin >> s; 
        lista2.push_back(s);
    }
    vector<string>sol = canciones(lista1, lista2);

    int size = sol.size();

    for (int i = size - 1; i >= 0; --i) 
        cout << sol[i] << " ";

    // for (string s : sol)
    //     cout << s << " ";

    cout << "\n";



    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
