// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
using namespace std;

#define MAX_VALUE 100
#define MAX_MOVES 8

struct position
{
  int x, y, moves;
};

char map[MAX_VALUE][MAX_VALUE];
bool visited[MAX_VALUE][MAX_VALUE];

queue<pair<int, int>> horsesPosition;

pair<int, int> origin;

int m, n, steps;
int kingMoves[8][2] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
int horseMoves[8][2] = {{-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}};

char getSymbol(int i, int j)
{
  return map[i][j];
}

bool ok(int i, int j)
{
  return 0 <= i && i < m && 0 <= j && j < n;
}

void updateMap()
{
  while (!horsesPosition.empty())
  {
    pair<int, int> front = horsesPosition.front();
    for (int i = 0; i < MAX_MOVES; ++i)
    {
      int newX = front.first + horseMoves[i][0], newY = front.second + horseMoves[i][1];
      if (ok(newX, newY) && getSymbol(newX, newY) == '.')
        map[newX][newY] = '#';
    }
    horsesPosition.pop();
  }
}

void showMap()
{
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
      cout << map[i][j] << ' ';
    cout << '\n';
  }
}

bool destinationReachable()
{
  queue<position> q;
  q.push({origin.first, origin.second, 0});
  while (!q.empty())
  {
    position front = q.front();
    q.pop();
    if (getSymbol(front.x, front.y) == 'B')
    {
      steps = front.moves;
      return true;
    }
    for (int i = 0; i < MAX_MOVES; ++i)
    {
      int newX = front.x + kingMoves[i][0], newY = front.y + kingMoves[i][1];
      if (ok(newX, newY) && !visited[newX][newY] && (getSymbol(newX, newY) == '.' || getSymbol(newX, newY) == 'B'))
      {
        visited[newX][newY] = true;
        q.push({newX, newY, front.moves + 1});
      }
    }
  }
  return false;
}

void resuelveCaso()
{
  steps = 0;
  cin >> m >> n;
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      char c;
      cin >> c;
      if (c == 'Z')
        horsesPosition.push({i, j});
      if (c == 'A')
        origin = {i, j};
      map[i][j] = c;
      visited[i][j] = false;
    }
  }
  // showMap();
  updateMap();
  // showMap();
  if (destinationReachable())
    cout << "Minimal possible length of a trip is " << steps << '\n';
  else
    cout << "King Peter, you can't go now!\n";
}

int main()
{

#ifndef DOMJUDGE
  std::ifstream in("input.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  int numCasos;
  std::cin >> numCasos;
  for (int i = 0; i < numCasos; ++i)
    resuelveCaso();

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // system("PAUSE");
#endif

  return 0;
}