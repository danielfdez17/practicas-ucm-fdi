
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include "ConjuntosDisjuntos.h"
using namespace std;

#define MAX 1000
#define ADJACENT 8

int movements[8][2] = {{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}};

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class solve {
private:
   ConjuntosDisjuntos cd;
   int maxTam;
public:
   solve(int N) : cd(N), maxTam(1) {}
   void join(int a, int b) {
      cd.unir(a, b);
      maxTam = max(maxTam, max(cd.cardinal(a), cd.cardinal(b)));
   }
   int getMaxTam() const { return maxTam; }
};

bool ok(int i, int j, int F, int C) {
   return 0 <= i && i < F && 0 <= j && j < C;
}

bool resuelveCaso() {

   int C, F; cin >> C >> F;
   if (!cin) return false;

   vector<string>board(F);
   solve s(C * F);
   // ConjuntosDisjuntos cd(C * F + 1);
   cin.ignore(1, '\n');
   for (int i = 0; i < F; i++) {
      getline(cin, board[i]);
      // for (int j = 0; j < C; j++) {
      //    char c; cin >> c; 
      //    board[i][j] = c;
      // }
   }

   for (int i = 0; i < F; ++i) {
      for (int j = 0; j < C; ++j) {
         for (int m = 0; m < ADJACENT; ++m) {
            int newi = i + movements[m][0], newj = j + movements[m][1];
            if (ok(newi, newj, F, C)) {
               if (board[i][j] == board[newi][newj] && board[i][j] == '#') {
                  s.join(i * C + j, newi * C + newj);
               }
            }
         }
      }
   }

   cout << s.getMaxTam() << " ";

   int manchas; cin >> manchas;
   for (int i = 0; i < manchas; i++) {
      int fila, columna; cin >> fila >> columna;
      --fila; --columna;
      board[fila][columna] = '#';
      for (int m = 0; m < ADJACENT; ++m) {
         int newi = fila + movements[m][0], newj = columna + movements[m][1];
         if (ok(newi, newj, F, C)) {
            if (board[fila][columna] == '#' && 
                  board[newi][newj] == '#') {
               // if (board[fila][columna] == '#')
                  s.join(fila * C + columna, newi * C + newj);
            }
            // if (board[fila][columna] == board[newi][newj] && board[fila][columna] == '#') {
            //    cd.unir(fila * C + columna, newi * C + newj);
            // }
         }
      }

      cout << s.getMaxTam() << " ";

   }
   cout << "\n";

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
