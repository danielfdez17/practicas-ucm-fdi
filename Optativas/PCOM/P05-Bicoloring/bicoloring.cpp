// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_NODES 200

using vi = vector<int>;
using vvi = vector<vi>;
using vbi = vector<pair<bool, int>>;

vvi adjList;
vbi visited;
int nodes, edges;

bool dfs(int v, int color)
{
  visited[v] = {true, color};
  for (int w : adjList[v])
  {
    if (!visited[w].first)
    {
      if (!dfs(w, (color + 1) % 2))
        return false;
    }
    else
    {
      if (color == visited[w].second)
        return false;
    }
  }
  return true;
}

bool isBicolorable()
{
  for (int i = 0; i < nodes; ++i)
  {
    if (!visited[i].first)
      if (!dfs(i, (i % 2) + 1))
        return false;
  }
  return true;
}

bool resuelveCaso()
{
  cin >> nodes;
  if (nodes == 0)
    return false;
  cin >> edges;

  adjList.assign(nodes, vector<int>());
  visited.assign(nodes, pair<bool, int>(false, -1));

  for (int i = 0; i < edges; ++i)
  {
    int a, b;
    cin >> a >> b;
    adjList[a].push_back(b);
    adjList[b].push_back(a);
  }

  cout << (isBicolorable() ? "" : "NOT ") << "BICOLORABLE.\n";

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
  // system("PAUSE");
#endif

  return 0;
}