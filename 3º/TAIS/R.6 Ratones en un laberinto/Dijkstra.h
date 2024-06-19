#include"DigrafoValorado.h"
#include"IndexPQ.h"
#include<deque>
#include<limits>
using namespace std;

using Camino = deque<int>;

template<typename Valor>
class Dijkstra {
private:
    const Valor INF = numeric_limits<Valor>::max();
    int origen;
    vector<Valor>dist;
    vector<AristaDirigida<Valor>>ulti;
    IndexPQ<Valor>pq;
    void relajar(AristaDirigida<Valor>a) {
    int v = a.desde(), w = a.hasta();
    if (dist[w] > dist[v] + a.valor()) {
        dist[w] = dist[v] + a.valor();
        ulti[w] = a;
        pq.update(w, dist[w]);
    }
}
public:
    Dijkstra(DigrafoValorado<Valor> const&g, int orig) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }

    // Camino<Valor> camino(int v) const {
    //     Camino<valor> cam;
    //     AristaDirigida<Valor>a;
    //     for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
    //         cam.push_front(a);
    //     cam.push_front(a);
    //     return cam;
    // }
};