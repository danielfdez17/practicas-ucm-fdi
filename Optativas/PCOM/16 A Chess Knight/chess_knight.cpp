// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <map>
#include <queue>
using namespace std;

#define K 1
#define B 2
#define T 3
#define LIBRE 0
#define OBS -1
#define MAX_SIZE 40
#define KMOVS 8
#define BMOVS 4

struct movimiento {
    int fila, columna, tipo, pasos;
    movimiento(int f, int c, int t, int p) : fila(f), columna(c), tipo(t), pasos(p) {}
};

bool operator<(movimiento const& i, movimiento const& d) {
    return i.pasos < d.pasos;
}

int kmovs[KMOVS][2] = {{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2}};
int bmovs[BMOVS][2] = {{-2,2},{-2,-2},{2,-2},{2,2}};
int N;
int tablero[MAX_SIZE][MAX_SIZE];
map<pair<int, int>, int> visitados;
int fila_orgien, columna_origen, fila_destino, columna_destino;

bool ok(int f, int c, int pasos) {
    return 0 <= f && f < 2 * N &&
        0 <= c && c < 2 * N && 
        tablero[f][c] == 0 &&
        (visitados.find({f, c}) == visitados.end() || visitados[{f, c}] >= pasos);
}

bool fin(int f, int c) {
    return f == fila_destino && c == columna_destino;
}

int bfs() {
    movimiento sig = {fila_orgien, columna_origen, 0, 0};

    queue<movimiento>cola;
    cola.push(sig);

    while (!cola.empty()) {
        sig = cola.front(); cola.pop();

        if (fin(sig.fila, sig.columna)) return sig.pasos;

        if (sig.tipo != K) {
            for (int i = 0; i < KMOVS; i++) {
                int f = sig.fila + kmovs[i][0], c = sig.columna + kmovs[i][1];
                if (ok(f, c, sig.pasos + 1)) {
                    visitados[{f, c}] = sig.pasos + 1;
                    cola.push(movimiento(f, c, K, sig.pasos + 1));
                }
            }
        }

        if (sig.tipo != B) {
            for (int i = 0; i < BMOVS; i++) {
                int f = sig.fila + bmovs[i][0], c = sig.columna + bmovs[i][1];
                if (ok(f, c, sig.pasos + 1)) {
                    visitados[{f, c}] = sig.pasos + 1;
                    cola.push(movimiento(f, c, B, sig.pasos + 1));
                }
            }
        }

        if (sig.tipo != T) {
            int f = sig.fila, c = 2 * N - sig.columna - 1;

            if (ok(f, c, sig.pasos + 1)) {
                visitados[{f, c}] = sig.pasos + 1;
                cola.push(movimiento(f, c, T, sig.pasos + 1));
            }

            f = 2 * N - sig.fila - 1; c = sig.columna;

            if (ok(f, c, sig.pasos + 1)) {
                visitados[{f, c}] = sig.pasos + 1;
                cola.push(movimiento(f, c, T, sig.pasos + 1));
            }
        }
    }

    return -1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    cin >> N;
    if (N == 0) return false;

    cin >> fila_orgien >> columna_origen >> fila_destino >> columna_destino;
    fila_orgien--; columna_origen--; 
    fila_destino--; columna_destino--;

    memset(tablero, 0, sizeof(tablero));
    visitados.clear();

    int i, j;
    while (cin >> i >> j) {
        if (i == 0 && j == 0) break;
        tablero[i - 1][j - 1] = OBS;
    }

    int movimientos = bfs();

    // cout << (movimientos == -1 ? "Solution doesn't exist\n" : "Result : " + to_string(movimientos) + "\n");
    if (movimientos == -1) cout << "Solution doesn't exist\n";
    else cout << "Result : " << movimientos << "\n";

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