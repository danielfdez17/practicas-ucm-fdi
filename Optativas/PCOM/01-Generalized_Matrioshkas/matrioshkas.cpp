// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct doll
{
  int value, sumOfInnerDolls;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
  string matrioshka;
  if (!getline(cin, matrioshka))
    return false;

  stringstream ss(matrioshka);
  bool exit = false;
  int num;
  deque<doll> dq;
  while (ss >> num && !exit)
  {
    if (num < 0)
    {
      if (dq.size() >= 1)
      {
        doll aux = dq.back();
        if (abs(aux.value) < abs(num))
          exit = true;
        // dq.pop_back();
        if (abs(aux.value) <= abs(aux.sumOfInnerDolls + num))
          exit = true;
        // dq.push_back({aux.value, aux.sumOfInnerDolls + num});
        dq[dq.size() - 1] = {aux.value, aux.sumOfInnerDolls + num};
      }
      dq.push_back({num, 0});
    }
    else
    {
      if (dq.empty())
        exit = true;
      else
      {
        doll aux = dq.back();
        if (abs(aux.value) == num)
          dq.pop_back();
        else
          exit = true;
      }
    }
  }

  cout << (exit ? ":-( Try again." : ":-) Matrioshka!") << '\n';

  return true;
}

int main()
{
// Para la entrada por fichero.
// Comentar para acepta el reto
#ifndef DOMJUDGE
  std::ifstream in("input.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
#endif

  while (resuelveCaso())
    ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
  std::cin.rdbuf(cinbuf);
  // system("PAUSE");
#endif

  return 0;
}