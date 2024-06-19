#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;

vector<vii> adjList;
int V, E;

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
        pq.push({dist[a.second], a.second});
      }
    }
  }
}

vvi invertir()
{
  vvi inverso(V);
  for (int v = 0; v < V; ++v)
    for (ii w : adjList[v])
      inverso[w.second].push_back(v);
  return inverso;
}