// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: PR03 RummyKub
// Comentario general sobre la solución: Numero de casos delimitados por un valor centinela


#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;

const int NumJugadores = 4; // Determina el numero maximo de jugadores (entre 2 y 4)
const int NumFichas = 13; // Determina el numero maximo de fichas de cada color (entre 8 y 13)
const int IniFichas = 14; // Determina el numero maximo de fichas iniciales que se reparten a cada jugador (entre 6 y 14)
const int MaxFichas = 50; // Determina el numero maximo de fichas que puede tener cada jugador
const int MaxJugadas = NumFichas * 2; // Determina el numero maximo de jugadas por jugador
const int NumColores = 8; // Determina el numero de colores que hay en la bolsa (2 de cada color) (No esta en el enunciado)

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
// El tablero sera una lista de longitud variable de jugadas
// Cada tJugada sera un array de NumFichas + 1 fichas donde una ficha con valor -1 actua como centinela
// Array que guarda una jugada
typedef tFicha tJugada[NumFichas + 1];
// Array que gaurda todas las jugadas
typedef tJugada tArrayJugadas[MaxJugadas];
// Estructura que almacena la lista de longitud variable o tablero del juego
struct tTablero {
	tArrayJugadas jugadas;
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
// FUNCIONA
void mostrar(const tSoporte& soporte);
// Recibe un color y devuelve su cadena correspondiente
string colorACad(tColor color);
// FUNCIONA
void ordenarPorNum(tSoporte& soporte);
// FUNCIONA
void ordenarPorColor(tSoporte& soporte);
// FUNCIONA
int menu();
// Procedimiento que recibe el turno y el numuero de jugadores y cambia el turno al siguiente jugador
void cambiaTurno(int& turno, int numJ);

void mostrarSeries(tSoporte soporte);

void mostrarEscaleras(tSoporte soporte);

void mostrar(tFicha ficha);

void mostrar(const tJugada jugada);

void mostrar(const tTablero& tablero);

void mostrarIndices(int num);

bool operator==(tFicha izq, tFicha der);

void eliminaFichas(tSoporte& soporte, const tJugada jugada);

int nuevaJugada(tSoporte soporte, tJugada jugada);

void nuevaJugada(tTablero& tablero, tJugada jugada);

void iniJugada(tJugada jugada);

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("in1.txt");
	//std::ifstream in("in2.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("out1.txt");
	//std::ofstream out("out2.txt");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif
	/*
	in1.txt=in2.txt:
	numFichas
	iniFichas
	numJugadores
	numJugadores lineas con iniFichas*2 nºs (color-valor)
	turnoJugador
	opMenu
	nº_fichas jugada 0
	0 fila columna
	opMenu
	nº_fichas jugada 0 (jugada invalida)
	nº_fichas jugada 0 (jugada valida)
	0
	...
	-1
	Lo primero que se debe hacer es inicializar la bolsa teniendo en cuenta
	que de cada color hay NumFichas. Despues de reparten las fichas, es decir, cada jugador
	roba IniFichas de la bolsa y las coloca en su soporte. Luego se elige que jugador juega
	el primero y se simula la iteracion con el menu.
	La opcion 3 nos sugiere posibles series o escaleras que se pueden formar. Una serie es un
	cjto de 3 o 4 fichas del mismo nº y != colores. Una escalera es un cjto entre 3 y 13 fichas
	del mismo color y de nºs en seucencia.
	Con la opcion 4 se forma una jugada indicando la posicion en las cuales se encuentrar las
	fichas del soporte.
	*/
	srand(time(NULL)); // <-- Solucion al problema
	while (resuelveCaso());
	//tSoporte soporte;
	//for (soporte.contador = 0; soporte.contador < 13; soporte.contador++) {
	//	soporte.fichas[soporte.contador].color = rojo;
	//	soporte.fichas[soporte.contador].valor = soporte.contador + 1;
	//}
	//mostrarEscaleras(soporte);
	//system("pause");
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}
// FUNCIONA
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
// FUNCIONA
void repartir(tBolsa& bolsa, tSoportes& soportes, int numJ, int iniF, int numF) {
	/*
	Obtiene iniFichas de la bolsa para cada jugador colocandolas en sus soportes
	bolsa: matriz y contador de fichas disponibles
	soportes: array de tSoporte (array de fichas(color y contador) y contador)
	*/
	// Recorre los soportes de los jugadores
	for (int i = 0; i < numJ; i++) {
		for (int j = 0; j < iniF; j++) { // Recorre las fichas de los soportes
			// Añade las fichas que roba a los soportes
			soportes[i].fichas[j] = robar(bolsa, numF);
			soportes[i].contador++;
		}
	}
	cout << "Fichas de la bolsa con todas las fichas repartidas" << endl << endl;
}
// FUNCIONA
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
// FUNCIONA
void mostrar(const tBolsa& bolsa, int numF) {
	/*
	Muestra el estado de la bolsa
	bolsa: matriz de fichas y contador de fichas disponibles
	Si se muestra asi, preguntar si hace falta mostrar los indeces de las filas y de las columnas
	*/
	cout << "Bolsa..." << endl;
	// Recorre las filas de la bolsa
	for (int i = 0; i < NumColores; i++) {
		// Recorre las columnas de la bolsa
		for (int j = 0; j < numF; j++) {
			// Si encuentra una posicion sin ficha
			if (bolsa.matriz[i][j].valor == -1) {
				// Muestra la posicion vacia
				cout << "    " << bolsa.matriz[i][j].valor << "  ";
			}
			// Si encuentra una posicion con ficha
			else {
				// Muestra la ficha
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
// FUNCIONA
void mostrar(const tSoporte& soporte) {
	cout << "Soporte: ";
	// Recorre los soportes
	for (int i = 0; i < soporte.contador; i++) {
		// Para ir mostrando las fichas de los soportes
		cout << colorACad(soporte.fichas[i].color) << " " << soporte.fichas[i].valor << "  ";
	}
	cout << endl;
}
// FUNCIONA
string colorACad(tColor color) {
	string col;
	switch (color) {
	case rojo:
		col = "rojo";
		break;
	case verde:
		col = "verd";
		break;
	case azul:
		col = "azul";
		break;
	case amarillo:
		col = "amar";
		break;
	case libre:
		col = "    ";
		break;
	}
	return col;
}
// FUNCIONA
void ordenarPorNum(tSoporte& soporte) {
	// Utilizando del metodo de la burbuja mejorado
	bool intercambio = true; // Variable que indica si se ha hecho o no intercambio
	int i = 0; // Variable con la que recorrer el soporte
	tFicha aux; // Variable auxiliar con la que poder hacer los intercambios
	// Desde la primera ficha hasta la penultima si hay intercambios
	while ((i < soporte.contador - 1) && intercambio) {
		intercambio = false;
		// Desde la ultima ficha hasta la siguiente a i
		for (int j = soporte.contador - 1; j > i; j--) {
			// Si la ficha de la posicion j es menor que la anterior a j, se intercambian
			if (soporte.fichas[j].valor < soporte.fichas[j - 1].valor) {
				intercambio = true;
				aux = soporte.fichas[j];
				soporte.fichas[j] = soporte.fichas[j - 1];
				soporte.fichas[j - 1] = aux;
			}
			// Si la ficha de la posicon j tiene el mismo valor que la anterior a j
			else if (soporte.fichas[j].valor == soporte.fichas[j - 1].valor) {
				// Se ordenan segun el color de las fichas
				if (soporte.fichas[j].color < soporte.fichas[j - 1].color) {
					intercambio = true;
					aux = soporte.fichas[j];
					soporte.fichas[j] = soporte.fichas[j - 1];
					soporte.fichas[j - 1] = aux;
				}
			}
		}
		// Si hay intercambio, se pasa a la siguiente ficha del soporte
		if (intercambio) {
			i++;
		}
	}
}
// FUNCIONA
void ordenarPorColor(tSoporte& soporte) {
	// Utilizando el metodo de la burbuja mejorado
	bool intercambio = true; // Variable que indica si se ha hecho o no intercambio
	int i = 0; // Variable con la que recorrer el soporte
	tFicha aux; // Variable auxiliar con la que poder hacer los intercambios
	// Desde la primera ficha hasta la penultima si hay intercambios
	while ((i < soporte.contador - 1) && intercambio) {
		intercambio = false;
		// Desde la ultima ficha hasta la siguiente a i
		for (int j = soporte.contador - 1; j > i; j--) {
			// Si la ficha de la posicion j es menor que la anterior, se intercambian
			if (soporte.fichas[j].color < soporte.fichas[j - 1].color) {
				intercambio = true;
				aux = soporte.fichas[j];
				soporte.fichas[j] = soporte.fichas[j - 1];
				soporte.fichas[j - 1] = aux;
			}
			// Si la ficha de la posicion j tiene el mismo color que la de la posicion anterior
			else if (soporte.fichas[j].color == soporte.fichas[j - 1].color) {
				// Se ordenan segun el valor de las fichas
				if (soporte.fichas[j].valor < soporte.fichas[j - 1].valor) {
					intercambio = true;
					aux = soporte.fichas[j];
					soporte.fichas[j] = soporte.fichas[j - 1];
					soporte.fichas[j - 1] = aux;
				}
			}
		}
		// Si hay intercambio, se pasa a la siguiente ficha del soporte
		if (intercambio) {
			i++;
		}
	}
}
// FUNCIONA
int menu() {
	int op = -1;
	do {
		cin >> op;
		if (op != -1) {
			// Como en el enunciado
			cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>>  ";
			/*cout << "1: Ordenar por numero de ficha" << endl;
			cout << "2: Ordenar por color de ficha" << endl;
			cout << "3: Sugerir jugada" << endl;
			cout << "4: Poner ficha(s)" << endl;
			cout << "0: Fin" << endl;
			cout << "Introduzca una opcion: ";*/
			cout << op << endl;
		}
	} while ((op < -10) && (op > 4));
	return op;
}
// FUNCIONA
void cambiaTurno(int& turno, int numJ) {
	switch (numJ) {
	case 2: // Si hay dos jugadores
		switch (turno) { // Se intercambia el turno entre ellos
		case 1:
			turno = 2;
			break;
		case 2:
			turno = 1;
			break;
		}
		break;
	case 3: // Si hay tres jugadores
		switch (turno) { // Se intercambian el turno entre ellos
		case 1:
			turno = 2;
			break;
		case 2:
			turno = 3;
			break;
		case 3:
			turno = 1;
			break;
		}
		break;
	case 4: // Si hay cuatro jugadores
		switch (turno) { // Se intercambia el turno entre ellos
		case 1:
			turno = 2;
			break;
		case 2:
			turno = 3;
			break;
		case 3:
			turno = 4;
			break;
		case 4:
			turno = 1;
			break;
		}
		break;
	}
	cout << "Turno para el jugador " << turno << " ..." << endl;
}
// FUNCIONA CREO QUE LAS FICHAS DE LAS SERIES DEBEN SER DE != COLOR TODAS ENTRE SI
void mostrarSeries(tSoporte soporte) {
	/*
	Muestra las posibles series que se pueden crear con las fichas del soporte
	Se recorre el soporte en busca de fichas con el mismo valor
	NO SE PUEDE SUPONER QUE EL SOPORTE YA ESTA ORDENADO AUNQUE EN LOS EJEMPLOS PARECE QUE EL SOPORTE SE ORDENA ANTES DE MOSTRAR LAS SERIES Y ESCALERAS
	soporte: array de fichas(color y contador) y contador
	Serie: cjto de 3 o 4 fichas con el mismo valor y distintos colores
	*/
	tJugada jugada; // Jugada en la que guardar las series
	iniJugada(jugada); // Se inicializan todas las fichas de la jugada a -1
	bool mostrado = false; // Variable que indica si se ha mostrado un valor o no
	int array[NumFichas] = { 0 }; // Array en el que guardar los valores ya mostrados
	bool guardado = false;
	int pos = 0; // Variable donde guardar el valor de i
	int fichas = 1; // Contador que determina cuanta fichas de igual valor y de distinto color hay
	for (int i = 0; i < soporte.contador; i++) { // Se recorren las fichas del soporte
		fichas = 1;
		for (int j = i; j < soporte.contador; j++) { // Se recorren las fichas del soporte desde la posicion i
			// Comprobando que formen una serie (mismo valor y distinto color)
			if ((soporte.fichas[i].color != soporte.fichas[j].color) && (soporte.fichas[i].valor == soporte.fichas[j].valor)) {
				jugada[fichas] = soporte.fichas[j];
				fichas++;
				pos = i;
				guardado = true;
			}
		}
		if (guardado && (fichas >= 3)) {
			jugada[0] = soporte.fichas[pos];
			for (int i = 0; i < fichas; i++) {
				mostrar(jugada[i]); // mostrar(ficha)
			}
			cout << endl;
		}
	}
}
// FUNCIONA
void mostrarEscaleras(tSoporte soporte) {
	/*
	Muestra las posibles escaleras que se pueden crear con las fichas del soporte
	Escalera: cjto de entre 3 y 13 fichas del mismo color y numeros en secuencia
	*/
	tJugada jug_roja, jug_verde, jug_azul, jug_amarilla; // Jugadas que almacenan las fichas que forman escalera de su color
	iniJugada(jug_roja); // Inicializo las fichas de la jugada
	iniJugada(jug_verde); // Inicializo las fichas de la jugada
	iniJugada(jug_azul); // Inicializo las fichas de la jugada
	iniJugada(jug_amarilla); // Inicializo las fichas de la jugada
	int rojas = 0, verdes = 0, azules = 0, amarillas = 0; // Variables que guardan cuantas fichas del mismo color y en secuencia hay
	int p_roja = 0, p_verde = 0, p_azul = 0, p_amarilla = 0;
	for (int i = 0; i < soporte.contador; i++) { // Se recorren todas las fichas del soporte
		for (int j = i + 1; j < soporte.contador - 1; j++) { // Se recorren todas las fichas del soporte a partir de la siguiente a i
			// Si se encuentran dos fichas del mismo color y de valores consecutivos
			if ((soporte.fichas[i].color == soporte.fichas[j].color) && (soporte.fichas[i].valor == (soporte.fichas[j].valor - 1)) && (soporte.fichas[i].valor == (soporte.fichas[j + 1].valor - 2))) {
				// Esto solo guarda (fichas-1) fichas en la jugada, y tiene que guardar fichas fichas
				switch (soporte.fichas[i].color) {
				case rojo:
					jug_roja[rojas] = soporte.fichas[i];
					rojas++;
					p_roja = i;
					break;
				case verde:
					jug_verde[verdes] = soporte.fichas[i];
					verdes++;
					p_verde = i;
					break;
				case azul:
					jug_azul[azules] = soporte.fichas[i];
					azules++;
					p_azul = i;
					break;
				case amarillo:
					jug_amarilla[amarillas] = soporte.fichas[i];
					amarillas++;
					p_amarilla = i;
					break;
				}
			}
		}
	}
	// Si se ha encontrado una jugada con mas de 3 fichas
	if (rojas >= 1) {
		jug_roja[rojas] = soporte.fichas[p_roja + 1];
		rojas++;
		jug_roja[rojas] = soporte.fichas[p_roja + 2];
		rojas++;
		for (int r = 0; r < rojas; r++) {
			mostrar(jug_roja[r]); // mostrar(ficha)
		}
		cout << endl;
	}
	if (verdes >= 1) {
		jug_verde[verdes] = soporte.fichas[p_verde + 1];
		verdes++;
		jug_verde[verdes] = soporte.fichas[p_verde + 2];
		verdes++;
		for (int v = 0; v < verdes; v++) {
			mostrar(jug_verde[v]); // mostrar(ficha)
		}
		cout << endl;
	}
	if (azules >= 1) {
		jug_azul[azules] = soporte.fichas[p_azul + 1];
		azules++;
		jug_azul[azules] = soporte.fichas[p_azul + 2];
		azules++;
		for (int az = 0; az < azules; az++) {
			mostrar(jug_azul[az]); // mostrar(ficha)
		}
		cout << endl;
	}
	if (amarillas >= 1) {
		jug_amarilla[amarillas] = soporte.fichas[p_amarilla + 1];
		amarillas++;
		jug_amarilla[amarillas] = soporte.fichas[p_amarilla + 2];
		amarillas++;
		for (int am = 0; am < amarillas; am++) {
			mostrar(jug_amarilla[am]); // mostrar(ficha)
		}
		cout << endl;
	}
}
// FUNCIONA
void mostrar(tFicha ficha) {
	cout << setw(2) << colorACad(ficha.color) << " " << ficha.valor << "  ";
}
// FUNCIONA
void mostrar(const tJugada jugada) {
	int serie = 0, escalera = 0; // Variables que indican si hay o no serie o escalera respectivamente
	int i = 0; // Contador con el que recorrer la jugada
	if (jugada[0].valor != -1) { // Si hay fichas
		cout << "Jugada: ";
		// Mientras que no llegue al final y que no se encuentre un -1
		while ((i < NumFichas + 1) && (jugada[i].valor != -1)) {
			mostrar(jugada[i]); // mostrar(ficha);
			//cout << " ";
			// Si no he llegado al valor centinela, paso a la siguiente posicion
			if (jugada[i].valor != -1) {
				i++;
			}
		}
	}
}
// FUNCIONA
void mostrar(const tTablero& tablero) {
	cout << "Tablero:";
	if (tablero.contador == 0) { // Si no hay jugadas en el tablero
		cout << " No hay jugadas" << endl;
	}
	else { // Si las hay, se muestran
		cout << endl;
		int j = 0; // Variable con la que recorrer las fichas de la jugada
		for (int i = 0; i < tablero.contador; i++) { // Se recorren las jugadas del tablero
			j = 0;
			cout << setw(2) << i + 1 << ": ";
			while ((j < NumFichas + 1) && (tablero.jugadas[i][j].valor != -1)) { // Mientras que el valor de la ficha de la jugada sea distinto de -1
				mostrar(tablero.jugadas[i][j]); // mostrar(ficha)
				if (tablero.jugadas[i][j].valor != -1) {
					j++;
				}
			}
			cout << endl;
		}
	}
}
// FUNCIONA
void mostrarIndices(int num) {
	cout << setw(15);
	for (int i = 0; i < num; i++) {
		cout << i + 1 << setw(8);
	}
	cout << endl;
}
// FUNCIONA
bool operator==(tFicha izq, tFicha der) {
	bool igual = false;
	if ((izq.color == der.color) && (izq.valor == der.valor)) {
		igual = true;
	}
	return igual;
}
// FUNCIONA
void eliminaFichas(tSoporte& soporte, const tJugada jugada) {
	int pos = -1;
	int i = 0;
	while ((i < NumFichas + 1) && (jugada[i].valor != -1)) {
		for (int j = 0; j < soporte.contador; j++) {
			if (jugada[i] == soporte.fichas[j]) {
				for (int k = j; k < soporte.contador - 1; k++) {
					soporte.fichas[k] = soporte.fichas[k + 1];
				}
				soporte.contador--;
			}
		}
		if (jugada[i].valor != -1) {
			i++;
		}

	}
}
// FUNCIONA
int nuevaJugada(tSoporte soporte, tJugada jugada) {
	/*
	Permite crear al usuario una jugada con las fichas que haya en su soporte
	soporte: array de fichas(color y contador) y contador
	jugada: array de fichas(color y contador)
	devuelve numfichas de la jugada o -1 si no hay jugada
	*/
	cout << "\tFichas (0 al final): ";
	int posicion; // Variable en la que guardar la posicion de una ficha para crear una nueva jugada
	int i = 0; // Variable con la que recorrer las fichas de la jugada
	int n_fichas = 0; // Variable que indica cuantas fichas hay en la nueva jugada o -1 si no se ha podido crear la jugada 
	int serie = 0, escalera = 0; // Variables que indican si hay una seire o una escalera respectivamente
	// Se lee la posicion
	cin >> posicion;
	// Se muestra solo para los ejemplos del juez
	cout << posicion << " ";
	// Mientras que no se lea la posicion 0
	while (posicion != 0) {
		// Se guardan en la jugada la ficha del soporte de la posicion posicion
		jugada[i] = soporte.fichas[posicion - 1];
		i++;
		n_fichas++;
		cin >> posicion;
		cout << posicion << " ";
	}
	cout << endl;
	mostrar(jugada);
	for (int j = 0; j < i - 1; j++) { // Se recorre el soporte hasta la posicion i - 1 para que no se compare con una posicion fuera del soporte
		if (jugada[j].valor == jugada[j + 1].valor) { // Si dos fichas consecutivas tienen el mismo valor, aumenta el contador de series
			serie++;
		}
		else if ((jugada[j].valor == (jugada[j + 1].valor - 1)) && (jugada[j]).color == jugada[j + 1].color) { // Si dos fichas tienen el mismo color y valores en secuencia, aumenta el contador de escaleras
			escalera++;
		}
	}
	if (serie >= 2) {
		cout << " - Serie correcta!" << endl;
	}
	else if (escalera >= 2) {
		cout << " - Escalera correcta!" << endl;
	}
	else {
		cout << " - No es una jugada correcta! Prueba de nuevo..." << endl;
		n_fichas = -1;
	}
	cout << endl;
	return n_fichas;
}
// FUNCIONA
void nuevaJugada(tTablero& tablero, tJugada jugada) {
	// Si el tablero esta lleno, no se pueden añadir mas jugadas
	if (tablero.contador == NumFichas + 1) {
		cout << "No se puede aniadir la jugada porque el tablero esta lleno!!!" << endl;
	}
	// Pero si tiene espacio, se añade la jugada
	else {
		int j = 0;
		while (jugada[j].valor != -1) {
			tablero.jugadas[tablero.contador][j] = jugada[j];
			if (jugada[j].valor != -1) {
				j++;
			}
		}
		tablero.contador++;
	}
}
// FUNCIONA
void iniJugada(tJugada jugada) {
	// Se recorren todas las fichas de la jugada
	for (int i = 0; i < NumFichas + 1; i++) {
		// Asignandoles el valor -1
		jugada[i].valor = -1;
		// En el ejemplo de ejecucion del campus las incializa a libre
		jugada[i].color = libre;
	}
}

bool resuelveCaso() {
	int numF, iniF, numJ;
	int opMenu, turno, n_fichas = -1;
	tBolsa bolsa;
	tSoportes soportes;
	tTablero tablero;
	tJugada jugada;
	tFicha ficha;
	// leer los datos de la entrada
	cin >> numF;
	cin >> iniF;
	cin >> numJ;
	// escribir sol
	// Se inicializa la bolsa y se muestra
	inicializarBolsa(bolsa, numF);
	mostrar(bolsa, numF);
	cout << endl;
	// Se reparten las fichas y se muestra la bolsa
	repartir(bolsa, soportes, numJ, iniF, numF);
	mostrar(bolsa, numF);
	cout << endl;
	// Se decide qué jugador empieza a jugar
	cin >> turno;
	cout << "Turno para el jugador " << turno << " ..." << endl;
	// Y se muestra el soporte de quien empieza
	mostrar(soportes[turno - 1]);
	cout << endl;
	for (int i = 0; i < MaxJugadas; i++) {
		iniJugada(tablero.jugadas[i]);
	}
	iniJugada(jugada);
	do {
		// Se guarda la opcion devuelta por menu()
		opMenu = menu();
		switch (opMenu) {
		case -1: // Se acaba el juego (para los ejercicios del juez)
			break;
		case 0: // SE CAMBIA EL TURNO Y SE ROBA SI NO SE HA PODIDO JUGAR
			if (n_fichas == -1) {
				soportes[turno - 1].fichas[soportes[turno - 1].contador] = robar(bolsa, numF);
				soportes[turno - 1].contador++;
				mostrar(soportes[turno - 1]);
			}
			cout << endl;
			cambiaTurno(turno, numJ);
			n_fichas = -1;
			mostrar(soportes[turno - 1]);
			cout << endl;
			break;
		case 1: // Se ordena el soporte del jugador que tiene el turno segun los valores de las fichas y se muestra el soporte
			ordenarPorNum(soportes[turno - 1]);
			mostrar(soportes[turno - 1]);
			cout << endl;
			break;
		case 2: // Se ordena el soporte del jugador que tiene el turno segun los colores de las fichas y se muestra el soporte
			ordenarPorColor(soportes[turno - 1]);
			mostrar(soportes[turno - 1]);
			cout << endl;
			break;
		case 3: // Se ordena el soporte por color segun los ejemplos del juez y se muestran las series y escaleras, si las hay
			ordenarPorColor(soportes[turno - 1]);
			mostrarSeries(soportes[turno - 1]);
			mostrarEscaleras(soportes[turno - 1]);
			mostrar(soportes[turno - 1]);
			cout << endl;
			break;
		case 4: // Se ordena el soporte por color segun los ejemplos del juez y permite crear una nueva jugada
			// Segun los ejemplos de ejecucion se ordenan los soportes sin usar las opciones que ordenan los soportes
			mostrar(soportes[turno - 1]);
			mostrarIndices(soportes[turno - 1].contador);
			cout << endl;
			n_fichas = nuevaJugada(soportes[turno - 1], jugada);
			if (n_fichas != -1) {
				nuevaJugada(tablero, jugada);
				mostrar(tablero);
				cout << endl << endl;
				eliminaFichas(soportes[turno - 1], jugada);
			}
			mostrar(soportes[turno - 1]);
			cout << endl;
			break;
		}

	} while (opMenu != -1);

	if (opMenu == -1)  // fin de la entrada
		return false;

	return true;
}
