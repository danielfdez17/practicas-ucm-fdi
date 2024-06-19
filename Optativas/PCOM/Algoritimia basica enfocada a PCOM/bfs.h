#include <vector>
#include <queue>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;

vvi adjList;
vb visited;
vi dist;
int V, E;

void bfs(int s)
{
  queue<int> q;
  dist[s] = 0;
  visited[s] = true;
  q.push(s);
  while (!q.empty())
  {
    int v = q.front();
    q.pop();
    for (int w : adjList[v])
      if (!visited[w])
      {
        dist[w] = dist[v] + 1;
        visited[w] = true;
        q.push(w);
      }
  }
}