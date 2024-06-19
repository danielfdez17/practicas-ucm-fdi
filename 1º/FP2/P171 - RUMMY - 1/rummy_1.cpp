// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: PR01 RummyKub
// Comentario general sobre la solución: Numero de casos ilimitados


#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

const int NumJugadores = 4; // Determina el numero maximo de jugadores (entre 2 y 4)
const int NumFichas = 13; // Determina el numero maximo de fichas de cada color (entre 8 y 13)
const int IniFichas = 14; // Determina el numero maximo de fichas iniciales que se reparten a cada jugador (entre 6 y 14)
const int MaxFichas = 50; // Determina el numero maximo de fichas que puede tener cada jugador
const int MaxJugadas = NumFichas * 2; // Determina el numero maximo de jugadas por jugador
const int NumColores = 8; // Determina el numero de colores que hay en la bolsa (2 de cada color)

// TIPOS DE DATOS DEFINIDOS DE LA VERSION 1

// Enumerado que almacena los colores disponibles para el transcurso del juego
typedef enum { rojo, verde, azul, amarillo, blanco, libre }tColor;
// Estructura que contiene la informacion de una ficha
struct tFicha {
	tColor color;
	int valor;
};
// Array de fichas
typedef tFicha tArrayFichas[MaxFichas];
// Estructura que contiene la lista de longitud variable de las fichas
struct tSoporte {
	tArrayFichas fichas;
	int contador = 0;
};
// Array de soportes en funcion del numero de jugadores que estan jugando
typedef tSoporte tSoportes[NumJugadores];
// Array bidimiensional donde hay 8 filas y NumFichas columnas
typedef tFicha tMatriz[NumColores][NumFichas];
// Estructura que almacena la informacion de la bolsa
struct tBolsa {
	tMatriz matriz;
	int fichas_dispo = 0;
};
// Array que representa las jugadas
typedef tFicha tJugada[NumFichas + 1];
// Estructura que almacena la lista de longitud variable o tablero del juego
struct tTablero {
	tJugada jugada;
	int contador = 0;
};

// FUNCIONA
void inicializarBolsa(tBolsa& bolsa, int numF);
// FUNCIONA
void repartir(tBolsa& bolsa, tSoportes& soportes, int numJ, int iniF, int numF);
// FUNCIONA
tFicha robar(tBolsa& bolsa, int numF);
// FUNCIONA
void mostrar(const tBolsa& bolsa, int numF);
// FUNCIONA a medias
void mostrar(const tSoporte& soporte);


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	//std::ifstream in("in.txt");
	std::ifstream in("in2.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("out.txt");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif
	/*
	in1.txt=in2.txt:
	numFichas
	iniFichas
	numJugadores
	numJugadores lineas con iniFichas*2 nºs (color-valor)
	*/
	srand(time(NULL)); // <-- Solucion al problema
	//tBolsa bolsa;
	//tSoporte soporte;
	//tSoportes soportes;
	//inicializarBolsa(bolsa);
	//repartir(bolsa, soportes);
	//mostrar(bolsa);
	//cout << endl;
	//mostrar(soportes[0]);
	//cout << endl;
	//mostrar(soportes[1]);
	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

void inicializarBolsa(tBolsa& bolsa, int numF) {
	// Se recorren las filas de la bolsa
	for (int i = 0; i < NumColores; i++) {
		// Se recorren las columnas de la bolsa
		for (int j = 0; j < numF; j++) {
			// En fucion de la fila (i) las fichas seran de un color u otro
			switch (i) {
			case 0:
			case 4:
				bolsa.matriz[i][j].color = rojo;
				break;
			case 1:
			case 5:
				bolsa.matriz[i][j].color = verde;
				break;
			case 2:
			case 6:
				bolsa.matriz[i][j].color = azul;
				break;
			case 3:
			case 7:
				bolsa.matriz[i][j].color = amarillo;
				break;
			}
			// Se asigna el valor siguiente a j para que lo entienda cualquier usuario
			bolsa.matriz[i][j].valor = j + 1;
			// Y se incrementa el contador de las fichas disponibles
			bolsa.fichas_dispo++;
		}
	}
}

void repartir(tBolsa& bolsa, tSoportes& soportes, int numJ, int iniF, int numF) {
	/*
	Obtiene iniFichas de la bolsa para cada jugador colocandolas en sus soportes
	bolsa: matriz y contador de fichas disponibles
	soportes: array de tSoporte (array de fichas(color y contador) y contador)
	*/
	// Mal planteado para este problema
	cout << "Repartir fichas" << endl << endl;
	// Es muy posible que no este bien
	// Se recorre la bolsa
	// Paso a paso obtiene las que tiene que obtener pero sin punto de parada obtiene menos de las que debe
	for (int i = 0; i < numJ; i++) {
		for (int j = 0; j < iniF; j++) {
			soportes[i].fichas[j] = robar(bolsa, numF);
			soportes[i].contador++;
		}
		mostrar(bolsa, numF);
		cout << endl;
		mostrar(soportes[i]);
		cout << endl;
	}
}
// Paso a paso funciona bien, sin puntos de parada no funciona bien
tFicha robar(tBolsa& bolsa, int numF) {
	tFicha ficha;
	bool encontrada = false;
	// Se seleccionan la fila y la columna de manera aleatoria
	/*int fila = rand() % (NumColores - 1);
	int columna = rand() % (NumFichas - 1);*/
	int fila, columna;
	cin >> fila;
	cin >> columna;
	// Se guardan esos valores por si no se encuentra una ficha disponible
	int i = fila, j = columna;
	// Se recorre la matriz desde la posicion fila,columna generada aleatoriamente hasta el final
	// Se recorren las filas de la bolsa
	while ((i < NumColores) && !encontrada) {
		//j = 0;
		// Se recorren las columnas de la bolsa
		while ((j < numF) && !encontrada) {
			// Hasta encontrar una ficha que este disponible
			if (bolsa.matriz[i][j].color != libre) {
				encontrada = true;
				// Se guarda la ficha
				ficha = bolsa.matriz[i][j];
				// Se iniciliza la posicion donde estaba la ficha en la bolsa a color libre y valor -1
				bolsa.matriz[i][j].color = libre;
				bolsa.matriz[i][j].valor = -1;
				// Y se decrementa el contador de las fichas disponibles
				bolsa.fichas_dispo--;
			}
			// Si no se encuentra en la columna j, se busca en la siguiente columna
			if (!encontrada) {
				j++;
			}
		}
		// Si no se encuentra en la fila i, se busca en la siguiente fila
		if (!encontrada) {
			i++;
			j = 0;
		}
	}
	// Si a partir de la posicion fila,columna no se ha encontrado
	if (!encontrada) {
		i = 0, j = 0;
		// Se recorre la matriz desde la posicion 0,0 hasta la posicion fila,columna
		while ((i < fila) && !encontrada) {
			while ((j < columna) && !encontrada) {
				// Hasta encontrar una ficha que este disponible
				if (bolsa.matriz[i][j].color != libre) {
					encontrada = true;
					// Se guarda la ficha
					ficha = bolsa.matriz[i][j];
					// Se inicializa la posicion donde estaba en la bolsa a color libre y valor -1
					bolsa.matriz[i][j].color = libre;
					bolsa.matriz[i][j].valor = -1;
					// Y se decrementa el contador de las fichas disponibles
					bolsa.fichas_dispo--;
				}
				// Si no se encuentra en la columna j, se busca en la siguiente columna
				if (!encontrada) {
					j++;
				}
			}
			// Si no se encuentra en la fila i, se busca en la siguient fila
			if (!encontrada) {
				i++;
			}
		}
	}
	// Si despues de haber recorrido toda la matriz no se ha encontrado una ficha para robar
	if (!encontrada) {
		// Se devuelve una ficha con valor -1 (y con color blanco(decision mia))
		ficha.color = blanco;
		ficha.valor = -1;
	}
	return ficha;
}
// Se debe mejorar en estilo
void mostrar(const tBolsa& bolsa, int numF) {
	/*
	Muestra el estado de la bolsa
	bolsa: matriz de fichas y contador de fichas disponibles
	Si se muestra asi, preguntar si hace falta mostrar los indeces de las filas y de las columnas
	*/
	cout << "Bolsa..." << endl;
	// Recorro las filas de la bolsa
	for (int i = 0; i < NumColores; i++) {
		// Recorro las columnas de la bolsa
		for (int j = 0; j < numF; j++) {
			if (bolsa.matriz[i][j].valor == -1) {
				cout << "    " << bolsa.matriz[i][j].valor << "  ";
			}
			else {
				switch (bolsa.matriz[i][j].color) {
				case 0:
				case 4:
					cout << "rojo";
					break;
				case 1:
				case 5:
					cout << "verd";
					break;
				case 2:
				case 6:
					cout << "azul";
					break;
				case 3:
				case 7:
					cout << "amar";
					break;
				default:
					cout << "    ";
				}
				cout << " " << bolsa.matriz[i][j].valor << "  ";
			}
		}
		cout << endl;
	}
}

void mostrar(const tSoporte& soporte) {
	cout << "Soporte: ";
	for (int i = 0; i < soporte.contador; i++) {
		cout << colorACad(soporte.fichas[i].color) << " " << soporte.fichas[i].valor << "  ";
	}
	cout << endl;
}

bool resuelveCaso() {
	int numF, iniF, numJ;
	tBolsa bolsa;
	//tSoporte soporte;
	tSoportes soportes;
	// leer los datos de la entrada
	cin >> numF;
	cin >> iniF;
	cin >> numJ;
	if (!std::cin)  // fin de la entrada
		return false;
	// escribir sol
	inicializarBolsa(bolsa, numF);
	mostrar(bolsa, numF);
	cout << endl;
	repartir(bolsa, soportes, numJ, iniF, numF);
	return true;
}
