// Daniel Fernandez Ortiz y Alex Bonilla Taco
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

const int MOVS = 4, MAX = 50;

struct tprioridad {
    char tipo;
    int tam;
    tprioridad(char t, int ta) : tipo(t), tam(ta) {}
};

bool operator<(tprioridad const&pi, tprioridad const&pd) {
    if (pi.tam == pd.tam) return pi.tipo > pd.tipo;
    return pi.tam < pd.tam;

}

int movimientos[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};
int cont = 1, x, y;
priority_queue<tprioridad>cola;
char tablero[MAX][MAX];
bool visitados[MAX][MAX];

bool ok(int f, int c) {
    return 0 <= f && f < x && 0 <= c && c < y;
}

int dfs(int f, int c) {
    int tam = 1; visitados[f][c] = true;
    for (int i = 0; i < MOVS; i++) {
        int nf = f + movimientos[i][0], nc = c + movimientos[i][1];
        if (ok(nf, nc) && tablero[nf][nc] == tablero[f][c] && !visitados[nf][nc]) 
            tam += dfs(nf, nc);
    }
    return tam;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    cin >> x >> y;//x filas, y columnas
    if (x == 0 && y == 0) return false;

    for (int i = 0; i < x; i++) { //i fila
        for (int j = 0; j < y; j++) { //j columna
            cin >> tablero[i][j];
            if (tablero[i][j] == '.') {
                visitados[i][j] = true;
            }else
            visitados[i][j] = false;
        }
    }
    

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (!visitados[i][j]) {
                cola.push({tablero[i][j], dfs(i, j)});
            }
        }
    }

    // escribir sol
    cout << "Problem " << cont << ":\n";
    while (!cola.empty()) {
        tprioridad p = cola.top(); cola.pop();
        cout << p.tipo << " " << p.tam << "\n";
    }
    cout << "\n";
    cont++;

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
