#include <vector>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
vvi adjList;
vb visited;
int V, E;

int dfs(int v)
{
  int size = 1;
  visited[v] = true;
  for (int w : adjList[v])
    if (!visited[w])
      size += dfs(w);
  return size;
}