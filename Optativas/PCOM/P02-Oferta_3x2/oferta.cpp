// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
using namespace std;

bool resuelveCaso()
{
  int books;
  cin >> books;
  if (!cin)
    return false;
  map<int, int> prices; // * <price, times>
  while (books--)
  {
    int x;
    cin >> x;
    map<int, int>::iterator it = prices.find(x);
    if (it == prices.end())
      prices.insert({x, 1});
    else
      it->second++;
  }
  int discount = 0, count = 0;
  for (map<int, int>::reverse_iterator rit = prices.rbegin(); rit != prices.rend(); rit++)
  {
    while (rit->second--)
    {
      if (count == 2)
      {
        discount += rit->first;
        count = -1;
      }
      ++count;
    }
  }
  cout << discount << "\n";

  return true;
}

int main()
{

#ifndef DOMJUDGE
  std::ifstream in("input.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (resuelveCaso())
    ;

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif

  return 0;
}