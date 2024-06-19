#include"Digrafo.h"
#include<queue>
using namespace std;

using Camino = deque<int>;

class BFSDirigido {
private:
    vector<bool>visit;
    vector<int>ant, dist;
    int s;
    void bfs(Digrafo const& grafo) {
        queue<int>q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : grafo.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
public:
    BFSDirigido(Digrafo const& grafo, int src) : visit(grafo.V(), false), ant(grafo.V()), dist(grafo.V()), s(src) {
        bfs(grafo);
    }
    bool hayCamino(int v) const { return visit[v]; }
    int distancia(int v) const { return dist[v]; }
    Camino camino(int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        Camino cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }
};