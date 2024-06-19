
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
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

struct evento {
    string nombre;
    int gravedad;
    int llegada;
    evento(string n, int g, int l) : nombre(n), gravedad(g), llegada(l) {}

   //  bool operator<(evento const& e) {
   //      return gravedad > e.gravedad || gravedad == e.gravedad && llegada < e.llegada;
   //  }
};

bool operator<(evento const& i, evento const& d) {
      return i.gravedad < d.gravedad || i.gravedad == d.gravedad && i.llegada > d.llegada;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int n; cin >> n;
   if (n == 0) return false;
   
   priority_queue<evento>cola;
   char tipo; string nombre; int gravedad;

   for (int i = 0; i < n; i++) {
    cin >> tipo;
    if (tipo == 'I') {
        cin >> nombre >> gravedad;
        cola.push({nombre, gravedad, i});
    }
    else if (tipo == 'A') {
        cout << cola.top().nombre << "\n";
        cola.pop();
    }
   }
   cout << "---\n";

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
