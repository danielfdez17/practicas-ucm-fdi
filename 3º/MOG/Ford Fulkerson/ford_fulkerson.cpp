#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <string.h>
#include <string>
using namespace std;


#define V 6


// Indica si hay un camino desde el vertice s hasta el vertice t en el grafo residual
// Si existe dicho camino, se almacena en el vector camino
bool bfs(int grafoResidual[V][V], int fuente, int destino, int camino[]) {


    vector<bool>visitados(V, false);
    queue<int> cola;
    cola.push(fuente);
    visitados[fuente] = true;
    camino[fuente] = -1;


    while (!cola.empty()) {
        int u = cola.front(); cola.pop();
        for (int v = 0; v < V; v++) {
            if (visitados[v] == false && grafoResidual[u][v] > 0) {
                // En el momento en el que se alcance el vertice destino del grafo residual,
                if (v == destino) {
                    // se deja de buscar porque se ha encontrado el camino que conecta los nodos s y t
                    camino[v] = u;
                    return true;
                }
                cola.push(v);
                camino[v] = u;
                visitados[v] = true;
            }
        }
    }
    return false;
}


// Calcula el flujo maximo posible que se puede mandar desde el vertice s hasta el vertice destino
int fordFulkerson(int digrafoValorado[V][V], int fuente, int destino) {
   
    // Se crea e inicializa el grafo residual
    int grafoResidual[V][V];
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            grafoResidual[i][j] = digrafoValorado[i][j];


    // En la busqueda en anchura (llamada a la funcion bfs) se rellena el camino que une el vertice fuente con el destino
    int camino[V], flujoMaximo = 0;
    while (bfs(grafoResidual, fuente, destino, camino)) {
        // Despues de cada llamada a la funcion bfs
        // Se calcula el menor flujo del grafo residual del camino que conecta el nodo fuente con el nodo destino
        int i, j, flujoResidual = INT_MAX;
        for (j = destino; j != fuente; j = camino[j]) {
            i = camino[j];
            flujoResidual = min(flujoResidual, grafoResidual[i][j]);
        }
        // Despues se actualizar los valores de las aristas en ambos sentidos
        // con el valor minimo de las aristas que forman parte del camino
        for (j = destino; j != fuente; j = camino[j]) {
            i = camino[j];
            grafoResidual[i][j] -= flujoResidual;
            grafoResidual[j][i] += flujoResidual;
        }
        // Y por ultimo se actualiza el flujo maximo
        flujoMaximo += flujoResidual;
    }


    return flujoMaximo;
}


void mostrar(int grafo[V][V]) {
    cout << "Dado el siguiente grafo (arista == (nodo, valor)): \n";
    for (int i = 0; i < V; ++i) {
        cout << "Adyacentes del vertice " << i + 1 << ": ";
        for (int j = 0; j < V; ++j) {
            if (grafo[i][j] != 0) {
                cout << "(" << j + 1 << "," << grafo[i][j] << ") ";
            }
        }
        cout << "\n";
    }
    int fuente, destino;
    cout << "Introduce el valor del nodo s y del valor t (valores entre 1 y " << V << " ambos inclusive)\n";
    try {
        cout << "Valor para s: "; cin >> fuente;
        cout << "Valor para t: "; cin >> destino;
        while (fuente <= 0 || fuente > V || destino <= 0 || destino > V) {
            cout << "Introduce valores validos entre 0 y " << V << ":\n";
            cout << "Valor para s: "; cin >> fuente;
            cout << "Valor para t: "; cin >> destino;
            cout << '\n';
        }
        cout << "El flujo maximo que se puede mandar desde el nodo " << fuente << " hasta el nodo " << destino << " es: " << fordFulkerson(grafo, fuente - 1, destino - 1) << "\n";
    } catch (std::exception e) {
        cout << "El algoritmo solo funciona con numeros, no con caracteres!";
    }
    cout << '\n';
}


int main() {
    // Si quieres modificar el grafo ajusta el numero de vertices del grafo (V)
    // y rellena el grafo como desees
    // Ejemplo 1
    int digrafoValorado1[V][V] = {
            //0, 1, 2, 3, 4, 5
            { 0, 16, 13, 0, 0, 0 }, // 0
            { 0, 0, 10, 12, 0, 0 }, // 1
            { 0, 4, 0, 0, 14, 0 },  // 2
            { 0, 0, 9, 0, 0, 20 },  // 3
            { 0, 0, 0, 7, 0, 4 },   // 4
            { 0, 0, 0, 0, 0, 0 }    // 5
        },
        // Ejemplo 2
        digrafoValorado2[V][V] = {
            { 0, 1, 5, 0, 0, 0 },
            { 0, 0, 0, 0, 7, 0 },
            { 0, 0, 0, 11, 0, 0 },
            { 0, 0, 0, 15, 0, 0 },
            { 0, 0, 0, 15, 0, 5 },
            { 0, 0, 0, 0, 0, 0 }
        },
        // Ejemplo 3
        digrafoValorado3[V][V] = {
            { 0, 1, 0, 0, 0, 0 },
            { 0, 0, 2, 0, 0, 0 },
            { 0, 0, 0, 3, 0, 0 },
            { 0, 0, 0, 0, 4, 0 },
            { 0, 0, 0, 0, 0, 5 },
            { 0, 0, 0, 0, 0, 0 }
        };
        mostrar(digrafoValorado1);
        mostrar(digrafoValorado2);
        mostrar(digrafoValorado3);
    return 0;
}
