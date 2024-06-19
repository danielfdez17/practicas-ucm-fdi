
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

struct registro {
    int id;
    int periodo;
    int turno;
    registro(int i, int p) : id(i), periodo(p), turno(p) {}
};
bool operator<(registro const& a, registro const& b) {
    return a.turno > b.turno || (a.turno == b.turno && a.id > b.id);
}
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int usuarios; cin >> usuarios;
   
   if (usuarios == 0) return false;

    priority_queue<registro>cola;
    for (int i = 0; i < usuarios; i++) {
        int id, periodo; cin >> id >> periodo;
        cola.push({id, periodo});
    }
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        registro r = cola.top();
        cout << r.id << "\n";
        cola.pop();
        r.turno += r.periodo;
        cola.push(r);
    }
    cout << "---\n";

   // resolver el caso posiblemente llamando a otras funciones
   
   // escribir la solución

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