#include"Digrafo.h"
using namespace std;


class DFSDirigido {
public:
    DFSDirigido(Digrafo const& grafo, int s) : visit(grafo.V(), false) {
        dfs(grafo, s);
    }
    bool alcanzable(int v) const { return visit[v]; }
private:
    vector<bool>visit;
    void dfs(Digrafo const& grafo, int v) {
        visit[v] = true;
        for (int w : grafo.ady(v)) 
            if (!visit[w])
                dfs(grafo, v);
    }
};