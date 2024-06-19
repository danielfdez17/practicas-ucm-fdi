#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Tarea {
    double t, p, c;
};

struct Nodo {
    vector<bool> sol;
    int k;
    double tiempo; // tiempo ocupado
    double coste; // coste acumulado
    double coste_estimado; // estimación, prioridad
    bool operator<(Nodo const& otro) const {
        return otro.coste_estimado < coste_estimado;
    }
};
double calculo_estimacion(vector<Tarea> const& tareas, Nodo const& X) {
    double estimacion = X.coste;
    for (int i = X.k + 1; i < tareas.size(); ++i) {
        if (X.tiempo + tareas[i].t > tareas[i].p) {
            estimacion += tareas[i].c;
        }
    }
    return estimacion;
}
// tareas ordenadas de menor a mayor plazo
void tareas_rp(vector<Tarea> const& tareas, vector<bool> & sol_mejor, double & coste_mejor) {
    int N = tareas.size();
    // se genera la raíz
    Nodo Y;
    Y.sol = vector<bool>(N, false);
    Y.k = -1;
    Y.tiempo = Y.coste = 0;
    Y.coste_estimado = calculo_estimacion(tareas, Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    coste_mejor = numeric_limits<double>::infinity();
    // búsqueda mientras pueda haber algo mejor
    while (!cola.empty() && cola.top().coste_estimado < coste_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;
        // hijo izquierdo, realizar la tarea
        if (Y.tiempo + tareas[X.k].t <= tareas[X.k].p) {
            X.sol[X.k] = true;
            X.tiempo = Y.tiempo + tareas[X.k].t; X.coste = Y.coste;
            X.coste_estimado = calculo_estimacion(tareas, X);
            if (X.coste_estimado < coste_mejor)
            if (X.k == N-1) {
                sol_mejor = X.sol; coste_mejor = X.coste;
            }
            else 
                cola.push(X);
        }
        // hijo derecho, no realizar la tarea
        X.sol[X.k] = false;
        X.tiempo = Y.tiempo; X.coste = Y.coste + tareas[X.k].c;
        X.coste_estimado = calculo_estimacion(tareas, X);
        if (X.coste_estimado < coste_mejor) {
            if (X.k == N-1) {
                sol_mejor = X.sol; coste_mejor = X.coste;
            }
            else
                cola.push(X);
        }
    }
}