// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

#define MAX_MOVES 4
#define MAX_SIZE 1000

struct position
{
  int x, y, moves;
};

const int moves[MAX_MOVES][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int R, C;
char map[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
queue<position> fire;
position joe;

bool ok(int i, int j)
{
  return 0 <= i && i < R && 0 <= j && j < C;
}

bool joeCanExit(int i, int j)
{
  return i == R || i == C;
}

void showMap()
{
  for (int i = 0; i < R; ++i)
  {
    for (int j = 0; j < C; ++j)
    {
      cout << map[i][j];
    }
    cout << '\n';
  }
}
bool canJoeMove(int i, int j)
{
  return ok(i, j) && !visited[i][j] && map[i][j] != '#' && map[i][j] != 'F';
}

bool canFireAdvance(int i, int j)
{
  return ok(i, j) && map[i][j] == '.';
}

void updateFire()
{
  while (!fire.empty())
  {
    position front = fire.front();
    fire.pop();
    for (int i = 0; i < MAX_MOVES; ++i)
    {
      int newX = front.x + moves[i][0], newY = front.y + moves[i][1];
      if (canFireAdvance(newX, newY))
      {
        // visited[newX][newY] = true;
        fire.push({newX, newY, front.moves + 1});
        map[newX][newY] = char(front.moves + 1) + '0';
      }
    }
  }
}

int updateJoe()
{
  int minMoves = -1;
  queue<position> q;
  q.push(joe);
  visited[joe.x][joe.y] = true;
  while (!q.empty())
  {
    position front = q.front();
    q.pop();
    for (int i = 0; i < MAX_MOVES; ++i)
    {
      int newX = front.x + moves[i][0], newY = front.y + moves[i][1];
      if (canJoeMove(newX, newY) && front.moves + 1 < int(map[newX][newY]) - '0')
      {
        visited[newX][newY] = true;
        q.push({newX, newY, front.moves + 1});
      }
      if (joeCanExit(newX, newY))
        return front.moves + 1;
    }
  }
  return minMoves;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
  cin >> R >> C;
  for (int i = 0; i < R; ++i)
  {
    for (int j = 0; j < C; ++j)
    {
      char c;
      cin >> c;
      map[i][j] = c;
      visited[i][j] = false;

      if (c == 'F')
        fire.push({i, j, 0});
      else if (c == 'J')
        joe = {i, j, 0};
    }
  }
  updateFire();
  int minMoves = updateJoe();
  cout << (minMoves == -1 ? "IMPOSSIBLE" : to_string(minMoves)) << '\n';
  // showMap();
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