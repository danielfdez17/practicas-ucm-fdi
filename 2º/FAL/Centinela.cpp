#include <iostream>
#include <fstream>
using namespace std;

bool resuelveCaso() {

	if (caso especial) return false;

	return true;
}


int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}