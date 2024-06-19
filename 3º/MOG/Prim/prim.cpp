#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
using namespace std;
struct conexion {
	int nodo1, nodo2, valor;
	bool operator<(const conexion& otro) const {
		return (valor < otro.valor);
	}
};
void resizeMatriz(vector<vector<int>> &mat, const int &tam) {
	mat.resize(tam);
	for (int i = 0; i < tam; i++) {
		mat[i].resize(tam);
	}
}
void añadeConexiones(multiset<conexion> &conex, const vector<vector<int>> &nods, int pos, const int &siz) {
	for (int i = 0; i < siz; i++) {
		if (nods[pos][i] != 0) {
			conex.insert({ pos, i, nods[pos][i] });
		}
	}
}


vector<vector<int>> prim(const vector<vector<int>> &matriz_nodos) {
	// variable resultado
	vector<vector<int>> res;
	resizeMatriz(res, matriz_nodos.size());
	// Lista de nodos conectados en el resultado
	vector<bool> conexo;
	conexo.resize(matriz_nodos.size());
	// Lista de conexiones disponibles ordenadas por valor
	multiset<conexion> conexiones;
	// Usamos el primer nodo como base para empezar
	conexo[0] = true;
	añadeConexiones(conexiones, matriz_nodos, 0, res.size());
	// Aplicamos la conexión más pequeña posible cada vez (a no ser que ambos nodos en la conexión ya  estén explorados o ninguno lo esté), 
	// añadiendo el nuevo nodo a la lista y añadiendo sus posibles conexiones a la lista
	int nodos_restantes = conexo.size() - 1;
	while (nodos_restantes != 0 && conexiones.size() > 0) {
		conexion conexion_a_explorar = *conexiones.begin();
		if ((!conexo[conexion_a_explorar.nodo1] && conexo[conexion_a_explorar.nodo2]) || (conexo[conexion_a_explorar.nodo1] && !conexo[conexion_a_explorar.nodo2])){
			nodos_restantes--;
			if (!conexo[conexion_a_explorar.nodo1]) {
				conexo[conexion_a_explorar.nodo1] = true;
				añadeConexiones(conexiones, matriz_nodos, conexion_a_explorar.nodo1, res.size());
			}
			else {
				conexo[conexion_a_explorar.nodo2] = true;
				añadeConexiones(conexiones, matriz_nodos, conexion_a_explorar.nodo2, res.size());
			}
			res[conexion_a_explorar.nodo1][conexion_a_explorar.nodo2] = matriz_nodos[conexion_a_explorar.nodo1][conexion_a_explorar.nodo2];
		}
		else
			conexiones.erase(conexiones.find(conexion_a_explorar));
	}
	return res;
}


int main() {
	const char* nombreArchivo = "datos.txt";
	ifstream archivo(nombreArchivo);
	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
		return 1; // Salir del programa con un código de error
	}
	int num_nodos;
	vector<vector<int>> matriz_nodos;
	// Estructuramos la matriz de nodos
	archivo >> num_nodos;
	resizeMatriz(matriz_nodos, num_nodos);
	// Introducimos los datos en la mitad superior derecha de la matriz, no necesitamos simetría con la otra mitad.
	int nodo1, nodo2, valor;
	archivo >> nodo1 >> nodo2 >> valor;
	while (archivo) {
		nodo1--; nodo2--;
		matriz_nodos[nodo1][nodo2] = valor;
		matriz_nodos[nodo2][nodo1] = valor;
		archivo >> nodo1 >> nodo2 >> valor;
	}
	archivo.close();
	// Aplicamos algoritmo prim sobre nuestra matriz de nodos
	vector<vector<int>> result = prim(matriz_nodos);
	// Mostramos el resultado
	for (int i = 0; i < num_nodos; i++) {
		for (int j = 0; j < num_nodos; j++) {
			if (result[i][j] != 0)
				cout << "nodos " << i + 1 << ", " << j + 1 << " -> " << result[i][j] << "\n";
		}
	}
