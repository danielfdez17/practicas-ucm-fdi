#include"Digrafo.h"
#include<deque>
using namespace std;



class OrdenTopologico {
private:
    vector<bool>visit;
    deque<int>_orden;

    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        for (int w : g.ady(v)) 
            if (!visit[w])
                dfs(g, w);
        _orden.push_front(v);
    }
public:
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
        for (int v = 0; v < g.V(); v++) {
            if (!visit[v])
                dfs(g, v);
        }
    }
    deque<int> const& orden() const { return _orden; }
};