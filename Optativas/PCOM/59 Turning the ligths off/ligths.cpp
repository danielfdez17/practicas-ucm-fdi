// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define SIZE 10
#define OPTIONS 4

char board[SIZE][SIZE], boardAux[SIZE][SIZE];
int ligths;
int movs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

bool ok(int i, int j) {
    return 0 <= i && i < SIZE && 0 <= j && j < SIZE;
}

bool isOn(int x, int y) {
    return boardAux[x][y] == 'O';
}

void changeState(int x, int y) {
    if (isOn(x, y)) 
        boardAux[x][y] = '#';
    else
        boardAux[x][y] = 'O';
}

void turn(int x, int y) {
    changeState(x, y);
    for (int i = 0; i < OPTIONS; ++i) {
        int newx = x + movs[i][0], newy = y + movs[i][1];
        if (ok(newx, newy)) {
            changeState(newx, newy);
        }
    }
}

void show() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
        }
        cout << "\n";
    }
}

void turnOff() {

}

bool areAllOff() {
    int i = 0; bool exit = false;
    while (i < SIZE && !isOn(SIZE - 1, i)) {
        ++i;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string word; cin >> word;
    if (word == "end") return false;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            char c; cin >> c;
            board[i][j] = c;
            boardAux[i][j] = c;
        }
    }
    if (word == "all_off") {
        cout << word << " 0\n";
    }
    else {
        ligths = 0;
        int k = 0; bool areAllOff = false;
        while (k < SIZE && areAllOff) {
            turnOff();
        }
        // for (int i = 0; i < SIZE; ++i) {
        //     for (int j = 0; j < SIZE; ++j) {
        //         if (isOn(i, j)) {
        //             turn(i + 1, j);
        //             ++ligths;
        //         }
        //     }
        // }
        if (ligths > 100) ligths = -1;
        cout << word << " " << ligths << "\n";
    }
    

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
