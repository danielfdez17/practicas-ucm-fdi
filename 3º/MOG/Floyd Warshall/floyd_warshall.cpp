#include<iostream>
#include<vector>
#include<limits>
using namespace std;

const int MAX = 100000000;

// Código de mostrar matriz en código C++:
void mostrarMatriz(vector<vector<int>> matriz) {
    cout << endl;
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
           
            if (matriz[i][j] == MAX) {
                cout << "INF ";
            }
            else {
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Obteniendo esta matriz y número de nodos / vértices podemos aplicar el algoritmo de Floyd-Warshall.
// Código Floyd-Warshall en lenguaje C++:
void FloydWarshall(vector<vector<int>>& MatrizDistancia, const int& NumDeNodos) {


    cout << "Cambios" << endl << endl;


    for (int k = 0; k < NumDeNodos; k++) { // Vamos seleccionando cada nodo/vertice como nodo/vertice intermedio
   
        for (int i = 0; i < NumDeNodos; i++) {  // Seleccion de origen
       
            for (int j = 0; j < NumDeNodos; j++) {  // Seleccion de destino




                // Pasamos del nodo i al k , despues del nodo k al j para conseguir pasa de i a j
                // Coste = MatrizDistancia[i][k] + MatrizDistancia[k][j]
                // Comparamos con el coste actual de i a j
                // Si es menor lo sustituimos, ya que esto significa que hemos encontrado un camino menos costoso.




                if (MatrizDistancia[i][j] > MatrizDistancia[i][k] + MatrizDistancia[k][j]) {
                 
                    cout << "De " << i << " al " << j << " -> coste antiguo: ";


                    if (MatrizDistancia[i][j] == MAX) {
                        cout << "INF";
                    }
                    else {
                        cout << MatrizDistancia[i][j];
                    }
                           
                    cout << " , nuevo coste: " << MatrizDistancia[i][k] + MatrizDistancia[k][j] << " , camino: " << i << " " <<  k << " " << j <<  endl;


                    MatrizDistancia[i][j] = MatrizDistancia[i][k] + MatrizDistancia[k][j];
                }
            }
        }
    }


    cout << endl;
}





// Como se observa en el código el algoritmo tiene un coste de O (n ^ 3) siendo n, número de nodos/vértices.
// Para la ejecución se usará el mismo código, pero añadiendo unos mensajes para una mejor vista de lo que está pasando.
void FloydWarshall(vector<vector<int>>& MatrizDistancia, const int& NumDeNodos) {


    cout << "Cambios" << endl << endl;


    for (int k = 0; k < NumDeNodos; k++) { // Vamos seleccionando cada nodo/vertice como nodo/vertice intermedio
   
        for (int i = 0; i < NumDeNodos; i++) {  // Seleccion de origen
       
            for (int j = 0; j < NumDeNodos; j++) {  // Seleccion de destino




                // Pasamos del nodo i al k , despues del nodo k al j para conseguir pasa de i a j
                // Coste = MatrizDistancia[i][k] + MatrizDistancia[k][j]
                // Comparamos con el coste actual de i a j
                // Si es menor lo sustituimos, ya que esto significa que hemos encontrado un camino menos costoso.




                if (MatrizDistancia[i][j] > MatrizDistancia[i][k] + MatrizDistancia[k][j]) {
                 
                    cout << "De " << i << " al " << j << " -> coste antiguo: ";


                    if (MatrizDistancia[i][j] == MAX) {
                        cout << "INF";
                    }
                    else {
                        cout << MatrizDistancia[i][j];
                    }
                           
                    cout << " , nuevo coste: " << MatrizDistancia[i][k] + MatrizDistancia[k][j] << " , camino: " << i << " " <<  k << " " << j <<  endl;


                    MatrizDistancia[i][j] = MatrizDistancia[i][k] + MatrizDistancia[k][j];
                }
            }
        }
    }


    cout << endl;
}

int main() {


    ifstream abrir("datos.txt"); // Abrimos el archivo donde estan los datos


    if (!abrir.is_open()) { // En caso de que no se pueda abrir se mustra un mensaje de error
        cout << "Error en archivo" << endl;
    }
    else { // Archivo abrierto


        int NumDeNodos;
        int origen, destino, valor;


        abrir >> NumDeNodos; // Primer dato numero de nodos/vertices


        if (NumDeNodos >= 2) { // Minimo tiene que existir 2 nodos/vertices


            vector<int> tmp(NumDeNodos, MAX);
            vector<vector<int>> MatrizDistancia(NumDeNodos, tmp); // Creamos la Matriz inicial


            for (int i = 0; i < NumDeNodos; i++) { // Ponemos el diagonal en 0
                MatrizDistancia[i][i] = 0;
            }


            abrir >> origen >> destino >> valor;


            while (abrir) { // Leemos las aristas
                origen--;
                destino--;
                MatrizDistancia[origen][destino] = valor;
                abrir >> origen >> destino >> valor;
            }


            cout << "Matriz INICIAL" << endl;
            mostrarMatriz(MatrizDistancia); // Mostramos la Matriz inicial


            FloydWarshall(MatrizDistancia, NumDeNodos);


            cout << "Matriz FINAL" << endl;
            mostrarMatriz(MatrizDistancia); // Mostramos la Matriz final
        }


        abrir.close(); // Cierre del archivo
    }


    std::system("pause");
    return 0;
}


