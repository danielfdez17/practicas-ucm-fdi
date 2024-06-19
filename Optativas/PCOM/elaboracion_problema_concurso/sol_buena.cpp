#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Solución oficial
int maxSubArraySum(vector<int> &v)
{
  int maxLongitud = v[0], maxLongitudActual = v[0];
  // Se recorre todo el vector en busca de la suma máxima de sub arrays ascendentes/descendentes
  for (int i = 1; i < v.size(); ++i)
  {
    maxLongitudActual = max(v[i], maxLongitudActual + v[i]);
    maxLongitud = max(maxLongitud, maxLongitudActual);
  }
  return maxLongitud;
}

bool resuelveCaso()
{
  int n;
  cin >> n;
  if (!cin)
    return false;
  vector<int> v(n);
  for (int i = 0; i < n; ++i)
    cin >> v[i];

  cout << maxSubArraySum(v) << "\n";
  return true;
}

int main()
{
// Para la entrada por fichero.
// Comentar para acepta el reto
#ifndef DOMJUDGE
  std::ifstream in("extended_input.txt");
  std::ofstream out("extended_expected_output.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
  auto coutbuf = std::cout.rdbuf(out.rdbuf()); // save old buf and redirect std::cout to casos.txt
#endif

  while (resuelveCaso())
    ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
  std::cin.rdbuf(cinbuf);
  std::cout.rdbuf(coutbuf);
  system("PAUSE");
#endif

  return 0;
}