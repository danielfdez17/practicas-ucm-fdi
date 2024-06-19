#include"Digrafo.h"
#include<deque>
using namespace std;

using Camino = deque<int>;

class CicloDirigido {
private:
    vector<bool>visit, apilado;
    vector<int>ant;
    bool hayciclo;
    Camino _ciclo;
    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        apilado[v] = true;
        for (int w : g.ady(v)) {
            if (hayCiclo) return;
            if (!visit[w]) {
                ant[w] = v;
                dfs(g, w);
            }
            else if (apilado[w]) { // ciclo detectado
                // se recupera retrocediendo
                hayciclo = true;
                for (int x = v; x != w; x = ant[w]) 
                    _ciclo.push_front(x);
                _ciclo.push_front(w);
                _ciclo.push_front(v);
            }
        }
        apilado[v] = false;
    }
public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); v++) 
            if (!visit[v])
                dfs(g, v);
    }
    bool hayCiclo() const { return hayciclo; }
    Camino const& ciclo() const { return _ciclo; }
};