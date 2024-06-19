#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Solución alternativa 1: utilizar la técnica divide y vencerás
int maxCrossingSum(vector<int> &v, int l, int m, int h)
{
  int sum = 0, leftSum = INT_MIN;
  for (int i = m; i >= l; --i)
  {
    sum += v[i];
    if (sum > leftSum)
      leftSum = sum;
  }

  sum = 0;
  int rightSum = INT_MIN;
  for (int i = m + 1; i <= h; ++i)
  {
    sum += v[i];
    if (sum > rightSum)
      rightSum = sum;
  }

  return max(leftSum + rightSum, max(leftSum, rightSum));
}

int maxSubArraySum(vector<int> &arr, int l, int h)
{
  if (l == h)
    return arr[l];

  int m = (l + h) / 2;

  return max({maxSubArraySum(arr, l, m),
              maxSubArraySum(arr, m + 1, h),
              maxCrossingSum(arr, l, m, h)});
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
  cout << maxSubArraySum(v, 0, n - 1) << "\n";
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