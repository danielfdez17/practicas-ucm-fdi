#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Solución alternativa 2: utilizando fuerza bruta
int maxSubArraySum(vector<int> &arr)
{
  int maxSum = INT_MIN;
  for (int i = 0; i < arr.size(); ++i)
  {
    int current_sum = 0;
    for (int j = i; j < arr.size(); ++j)
    {
      current_sum += arr[j];
      maxSum = max(maxSum, current_sum);
    }
  }
  return maxSum;
}

bool resuelveCaso()
{
  int n;
  cin >> n;
  if (!cin)
    return false;
  vector<int> v(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> v[i];
  }
  cout << maxSubArraySum(v) << "\n";
  return true;
}

int main()
{
// Para la entrada por fichero.
// Comentar para acepta el reto
#ifndef DOMJUDGE
  std::ifstream in("input_statement.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
#endif

  while (resuelveCaso())
    ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif

  return 0;
}