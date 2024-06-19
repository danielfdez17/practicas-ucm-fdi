// ALEX BONILLA y DANIEL FERNANDEZ
// PC03


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX_T = 1001;
char tablero[MAX_T][MAX_T];

//true si la casilla es . y false si # o F
bool transitable[MAX_T][MAX_T];

const int MOVS = 4;
int movs[4][2] = { {0,1},{-1,0},{0,-1},{1,0} };
int r, c;
bool ok(int x, int y) {
    return 0 <= x && x < r && 0 <= y && y < c;
}

struct tcasilla {
    int fila, columna;
    tcasilla() : fila(0), columna(0) {}
    tcasilla(int f, int c) : fila(f), columna(c) {}
    
};

queue<tcasilla>joe, fire;
        //cola temporal para almacenar las posiciones de fuego y joe en un cierto turno 
queue<tcasilla>qTem;


// función que resuelve el problema
/*
*funcion que recibe dos colas, joe y fire
*/
int GetTime(queue<tcasilla>&fire, queue<tcasilla>& joe) {
    int turn = 1;
    //bucle  en la que joe se va moviendo turno a turno por las casillas transitables hasta escapar  
    //en cada iteracion a la cola de joe se le añade las casillas reales que puede moverse sin ser quemado en el siguiente turno
    while (!joe.empty()) {
        // en cada turno se propaga primero el fuego
        // y encolamos temporalmente en qTem las casillas transitables en el siguiente turno, en las que se propagara el fuego
        //salimos del bucle siempre despues de encolar dichas casillas y marcarlas como no transitables
        while (!fire.empty()){
            tcasilla casilla=fire.front();
            fire.pop();
            for (int i = 0; i < MOVS; i++) {
                int nf = casilla.fila + movs[i][0], nc = casilla.columna + movs[i][1];
                if (ok(nf, nc) && transitable[nf][nc])
                {
                    transitable[nf][nc] = false;
                    qTem.push({ nf, nc });
                }
            }
            

        }
        //encolamos en fire (cola vacia) las casillas de la cola temporal 
        //para que en el siguiente turno vuelva a entrar en el bucle la cola de fire y recorra las nuevas casillas con fuego
        fire.swap(qTem);
        

        //bucle en el que miramos si joe puede moverse a alguna posicion donde no se haya propagado el fuego antes
        //si consigue moverse, encolamos temporalmente en qTem las posiciones siguientes transitables.
        //en el caso que la siguiente casilla sea transitable y ademas se casilla limite del tablero, retornamos el turno
        //salimos del bucle cuando hemos terminado de vaciar la cola de joe que contiene las casillas transitables por joe
        while (!joe.empty())
        {
            tcasilla pos=joe.front(); joe.pop();
            for (int i = 0; i < MOVS; i++) {
                int nf = pos.fila + movs[i][0], nc = pos.columna + movs[i][1];
                if (!ok(nf, nc)) {
                    return turn;
                }
                if (transitable[nf][nc]) {
                   // transitable[nf][nc] = false;
                    qTem.push({ nf, nc });
                }

            }
        }

        //encolamos en joe (cola vacia) las casillas de la cola temporal 
        //para que en el siguiente turno vuelva a entrar en el bucle la cola de joe y recorra las nuevas casillas transitables
        joe.swap(qTem);
        
        //avanzamos al siguiente turno
        ++turn;
    }
    return -1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
   
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            char letra;
            cin >> letra;
            tablero[i][j] = letra;
            transitable[i][j] = false;
            if (tablero[i][j] == 'J') {
                joe.push({ i,j });
                transitable[i][j] = true;
            }
            else if (tablero[i][j] == 'F') {
                fire.push({ i, j });
            }
            else if (tablero[i][j] == '.') transitable[i][j] = true;
        }

    }

    
    // escribir sol
    int time = GetTime(fire,joe);
    if (time == -1)
        cout << "IMPOSSIBLE\n";
    else
        cout << time << '\n';

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}