#include <iostream>
using namespace std;

#define MAX_V 100

int camino[INT_MAX][INT_MAX];
int V;

int adjMat[MAX_V][MAX_V];

void floyd()
{
  for (int k = 0; k < V; ++k)
    for (int i = 0; i < V; ++i)
      for (int j = 0; j < V; ++j)
        if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j])
        {
          adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
          camino[i][j] = k;
        }
}