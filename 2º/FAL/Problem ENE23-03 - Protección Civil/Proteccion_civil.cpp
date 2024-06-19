#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_SALARIO = std::numeric_limits<int>::max();


struct tsol {
	int ciudades;
	int patrullas;
	int sueldo_reserva;
	vector<int>min_personas_por_ciudad;
	vector<int>max_personas_por_ciudad;
	vector<int>salarios_por_ciudad;
	vector<int>personas_por_patrulla;
	int salarioMinimo;
	int personas_restantes;
	int salarioMejor;
	int salarioActual;
	int ciudades_satisfechas;
	vector<int>personas_por_ciudad;
};

//DESCRIPCION DEL ESPACIO DE SOLUCIONES
// Ramificacion: ciudades; Nivel: patrullas

//MARCADORES UTILIZADOS
// vector<int>personas_por_ciudad
// ciudades_satisfechas
// personas_restantes (las que quedan por asignar a una ciudad o no)
// salarioMinimo (entre todos los sueldos que ofrecen las ciudades y el de reserva)

//PODA DE OPTIMALIDAD
// Si el salario actual + el salario minimo * en numero de personas que quedan por asignarles un sueldo < salario mejor: se hace la siguiente llamada recursiva


//ALGORITMO DE VUELTA ATRÁS
void proteccionCivil(tsol& sol, int k, bool& sepuede) {
	// ASIGNAR LA PATRULLA DE NIVEL 'k' A ALGUNA CIUDAD
	for (int i = 0; i < sol.ciudades; i++) {
		// Marcaje
		sol.personas_por_ciudad[i] += sol.personas_por_patrulla[k];
		sol.salarioActual += (sol.salarios_por_ciudad[i] * sol.personas_por_patrulla[k]);

		// esValida()
		if (sol.personas_por_ciudad[i] <= sol.max_personas_por_ciudad[i]) {
			// Se comprueba si la ciudad 'i' esta satisfecha
			if (sol.personas_por_ciudad[i] >= sol.min_personas_por_ciudad[i]
				&& sol.personas_por_ciudad[i] - sol.personas_por_patrulla[k] < sol.min_personas_por_ciudad[i]) {
				sol.ciudades_satisfechas++;
			}

			// esSolucion()
			if (k == sol.patrullas - 1) {
				if (sol.ciudades == sol.ciudades_satisfechas) {
					if (sol.salarioActual < sol.salarioMejor) {
						sepuede = true;
						sol.salarioMejor = sol.salarioActual;
					}
				}
			}
			else {
				// esSolucionPrometedora()
				if (sol.salarioActual + sol.salarioMinimo * (sol.personas_restantes - sol.personas_por_patrulla[k]) < sol.salarioMejor) {
					sol.personas_restantes -= sol.personas_por_patrulla[k];
					proteccionCivil(sol, k + 1, sepuede);
				}
			}

			// Si la ciudad estava satisfecha
			if (sol.personas_por_ciudad[i] >= sol.min_personas_por_ciudad[i] &&
				sol.personas_por_ciudad[i] - sol.personas_por_patrulla[k] < sol.min_personas_por_ciudad[i]) {
				sol.ciudades_satisfechas--;
			}

		}

		// Desmarcaje
		sol.personas_por_ciudad[i] -= sol.personas_por_patrulla[k];
		sol.salarioActual -= (sol.salarios_por_ciudad[i] * sol.personas_por_patrulla[k]);
	}

	// NO ASIGNAR A LA PATRULLA DE NIVEL 'k' A NINGUNA CIUDAD
	// Marcaje
	sol.salarioActual += (sol.sueldo_reserva * sol.personas_por_patrulla[k]);

	// esSolucion()
	if (k == sol.patrullas - 1) {
		if (sol.ciudades == sol.ciudades_satisfechas) {
			if (sol.salarioActual < sol.salarioMejor) {
				sepuede = true;
				sol.salarioMejor = sol.salarioActual;
			}
		}
	}
	else {
		// esSolucionPrometedora()
		if (sol.salarioActual + sol.salarioMinimo * (sol.personas_restantes - sol.personas_por_patrulla[k]) < sol.salarioMejor) {
			sol.personas_restantes -= sol.personas_por_patrulla[k];
			proteccionCivil(sol, k + 1, sepuede);
		}
	}

	// Desmarcaje
	sol.salarioActual -= (sol.sueldo_reserva * sol.personas_por_patrulla[k]);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
void resuelveCaso() {
	int n, m, r; //ciudades, patrullas y sueldo de reserva
	cin >> n >> m >> r;
	vector<int> L(n), G(n), S(n); //minimo, maximo de personas admitidas en la ciudad y salarios por ciudad
	vector<int> P(m); //personas por patrulla
	int salarioMinimo = MAX_SALARIO, personas_restantes = 0;
	for (int i = 0; i < n; ++i)
		cin >> L[i];
	for (int i = 0; i < n; ++i)
		cin >> G[i];
	for (int i = 0; i < n; ++i) {
		cin >> S[i];
		salarioMinimo = std::min(salarioMinimo, std::min(S[i], r));
	}
	for (int i = 0; i < m; ++i) {
		cin >> P[i];
		personas_restantes += P[i];
	}


	int salarioMejor = MAX_SALARIO; bool sepuede = false;
	int salarioActual = 0, ciudadesSatisfechas = 0;
	vector<int>personas_por_ciudad(n, 0);

	//LLamada inicial al algoritmo de vuelta atras
	tsol sol = { n,m,r,L,G,S,P,salarioMinimo,personas_restantes,salarioMejor,salarioActual,ciudadesSatisfechas,personas_por_ciudad };
	proteccionCivil(sol, 0, sepuede);
	if (sepuede)
		cout << sol.salarioMejor << "\n";
	else
		cout << "NO\n";
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
