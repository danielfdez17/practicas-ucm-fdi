#include<fstream>
#include<iostream>
#include <stdio.h>
#include <queue>
using namespace std;

#define MAX 110

char tablero[MAX][MAX];
int E[MAX][MAX], P[MAX][MAX];
int W, H, dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
int x, y;
struct pt {
    int x, y;
};
pt posFrancesco, posJorge, posProfesor;
queue<pt> q;

void sol() {
    int i, j;
    while (!q.empty())   q.pop();
    pt tn, tx;

    q.push(posProfesor);
    P[posProfesor.x][posProfesor.y] = 1;
    while (!q.empty()) {
        tn = q.front();
        q.pop();
        for (i = 0; i < 4; i++) {
            tx.x = tn.x + dir[i][0];
            tx.y = tn.y + dir[i][1];
            if (tx.x < 0 || tx.x >= W || tx.y < 0 || tx.y >= H)
                continue;
            if (P[tx.x][tx.y] == 0) {
                P[tx.x][tx.y] = P[tn.x][tn.y] + 1;
                q.push(tx);
            }
        }
    }
    q.push(posFrancesco), E[posFrancesco.x][posFrancesco.y] = 1;
    while (!q.empty()) {
        tn = q.front();
        q.pop();
        if (tn.x == posJorge.x && tn.y == posJorge.y ) {
            cout << "IMPOSIBLE QUE LO PILLEN\n";
            return;
        }
        for (i = 0; i < 4; i++) {
            tx.x = tn.x + dir[i][0];
            tx.y = tn.y + dir[i][1];
            if (tx.x < 0 || tx.x >= W || tx.y < 0 || tx.y >= H)
                continue;
            if (tablero[tx.x][tx.y] == 'O')
                continue;
            if (E[tx.x][tx.y] == 0 && (E[tn.x][tn.y] + 1 < P[tx.x][tx.y] || P[tx.x][tx.y] == 0)) {
                E[tx.x][tx.y] = E[tn.x][tn.y] + 1;
                q.push(tx);
            }
        }
    }
    cout <<"PUEDEN PILLARTE FRANCESCO\n";
}
bool resuelveCaso() {
    cin >> W >> H;
    if (!cin) return false;
    int numCasos; cin >> numCasos;
    while (numCasos--) {
        int t, i, j;
        char c;
        cin >> x >> y;
        posProfesor.x = x; posProfesor.y = y;
        for (i = 0; i < W; i++) {
            for (j = 0; j < H; j++) {
                cin >> tablero[i][j];
                if (tablero[i][j] == 'F')
                    posFrancesco.x = i, posFrancesco.y = j;
                if (tablero[i][j] == 'J')
                    posJorge.x = i, posJorge.y = j;
                E[i][j] = 0, P[i][j] = 0;
            }
        }
        sol();
    }
    cout << "\n";
    return true;
}
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to datos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}