
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int n, a, b; cin >> n >> a >> b;
   if (!cin) return false;
   
   priority_queue<int>cola_A, cola_B;
   
   int x;
   for (int i = 0; i < a; i++) {
    cin >> x; cola_A.push(x);
   }
   for (int i = 0; i < b; i++) {
    cin >> x; cola_B.push(x);
   }
   vector<int>sol;
   while (!cola_A.empty() && !cola_B.empty()) {
    int i = 0, horas = 0, topA, topB;
    vector<int>A_restantes, B_restantes; 

    while (i < n && !cola_A.empty() && ! cola_B.empty()) {
        topA = cola_A.top(); cola_A.pop();
        topB = cola_B.top(); cola_B.pop();
        horas += min(topA, topB);

        if (topA > topB) A_restantes.push_back(topA - topB);
        else if (topB > topA) B_restantes.push_back(topB - topA);

        i++;
    }

    sol.push_back(horas);
    for (int &a : A_restantes) cola_A.push(a);
    for (int &b : B_restantes) cola_B.push(b);

   }

    for (int &i : sol) cout << i << " "; cout << "\n";
   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
