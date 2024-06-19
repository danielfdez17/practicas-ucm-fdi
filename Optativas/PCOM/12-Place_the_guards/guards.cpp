// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
vvi adjList;
vb visited, guardsAssigned;
int V, E;

int dfs(int v, int guard)
{
  int guards = 1;
  visited[v] = true;
  guardsAssigned[guard] = true;

  for (int w : adjList[v])
  {
    if (!visited[w])
      guards +=dfs(w, guard);
    else if (guardsAssigned[w])
    {
      guardsAssigned[guard] = false;
      --guards; // Guard conflict
    }
  }
  return guards; // Guard successfully assigned
}

// void dfs(int v, int guard)
// {
//   visited[v] = true;
//   guardsAssigned[guard] = true;

//   for (int w : adjList[v])
//   {
//     if (!visited[w])
//       dfs(w, guard);
//   }
// }

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
  int vertex, edges;
  cin >> vertex >> edges;
  adjList.assign(vertex, vi());
  visited.assign(vertex, false);
  guardsAssigned.assign(vertex, false);
  for (int i = 0; i < edges; ++i)
  {
    int a, b;
    cin >> a >> b;
    adjList[a].push_back(b);
    adjList[b].push_back(a);
  }

  bool exit = false;
  int minGuards = 0;

  for (int i = 0; i < vertex && !exit; ++i)
  {
    if (!visited[i])
    {
      int res = dfs(i, i);
      if (res < 0)
      {
        exit = true;
        minGuards = -1;
      }
      else
      {
        minGuards += res;
      }
    }
  }
  cout << minGuards << '\n';
}

int main()
{
// Para la entrada por fichero.
// Comentar para acepta el reto
#ifndef DOMJUDGE
  std::ifstream in("input.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
#endif

  int numCasos;
  std::cin >> numCasos;
  for (int i = 0; i < numCasos; ++i)
    resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
  std::cin.rdbuf(cinbuf);
  // system("PAUSE");
#endif

  return 0;
}