// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;

vector<vii> adjList;
int nodes, cases = 1;
vi previous;

void dijkstra(int s, vi &dist)
{
  dist.assign(adjList.size(), INT_MAX);
  dist[s] = 0;
  priority_queue<ii, vii, greater<ii>> pq;
  pq.push({0, s});
  while (!pq.empty())
  {
    ii front = pq.top();
    pq.pop();
    int d = front.first, u = front.second;
    if (d > dist[u])
      continue;
    for (auto a : adjList[u])
    {
      if (dist[u] + a.first < dist[a.second])
      {
        dist[a.second] = dist[u] + a.first;
        previous[a.second] = u;
        pq.push({dist[a.second], a.second});
      }
    }
  }
}

void showPath(int destination)
{
  vi path;
  stack<int> s;
  for (int d = destination; d != -1; d = previous[d])
    // path.push_back(d);
    s.push(d);
  while (!s.empty())
  {
    cout << " " << s.top() + 1;
    s.pop();
  }
  // reverse(path.begin(), path.end());
  // for (auto v : path)
  //   cout << " " << v + 1;
}

bool resuelveCaso()
{
  cin >> nodes;
  if (nodes == 0)
    return false;

  adjList.assign(nodes, vii());
  previous.assign(nodes, -1);

  for (int i = 0; i < nodes; ++i)
  {
    int edges;
    cin >> edges;
    while (edges--)
    {
      int vertex, value;
      cin >> vertex >> value;
      adjList[i].push_back({value, vertex - 1});
    }
  }
  int origin, destination;
  cin >> origin >> destination;
  vi dist;
  dijkstra(origin - 1, dist);

  cout << "Case " << cases << ": Path =";
  showPath(destination - 1);
  cout << "; " << dist[destination - 1] << " second delay\n";
  ++cases;
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