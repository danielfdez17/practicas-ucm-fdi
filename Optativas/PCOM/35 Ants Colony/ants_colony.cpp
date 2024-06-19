// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

#define MAX_ANTHILLS 100000

class SegmentTree {
private:
    vector<int>st;
    int tam;
    int query(int vertex, int L, int R, int i, int j) {
        if (i > R || j < L) return 0;
        if (L >= i && R <= j) return st[vertex];
        int mitad = (L + R) / 2;
        return query(vertex * 2, L, mitad, i, j) + query(vertex * 2 + 1, mitad + 1, R, i, j);
    }
    void update(int vertex, int l, int r, int pos, int newVal) {
        if (pos < l || r < pos) return;
        if (l == r) {
            st[vertex] = newVal;
            return;
        }
        int m = (l + r) / 2;
        if (l <= pos && pos <= m)
            update(vertex * 2, l, m, pos, newVal);
        else
            update(vertex * 2 + 1, m + 1, r, pos, newVal);
        st[vertex] = st[vertex * 2] + st[vertex * 2 + 1];
    }
    void build(int *values, int p, int l, int r) {
        if (l == r) {
            st[p] = values[l];
            return;
        }
        int m = (l + r) / 2;
        build(values, 2 * p, l, m);
        build(values, 2 * p + 1, m + 1, r);
        st[p] = st[p * 2] + st[p * 2 + 1];
    }
public:
    SegmentTree(int maxN) {
        st.reserve(4 * maxN + 10);
    }
    int query(int a, int b) {
        return query(1, 0, tam - 1, a, b);
    }
    void update(int pos, int newVal) {
        update(1, 0, tam - 1, pos, newVal);
    }
    void build(int *values, int n) {
        tam = n;
        build(values, 1, 0, n - 1);
    }
};

using vi = vector<int>;

vi adj[MAX_ANTHILLS];

int idx;
int euler[2 * MAX_ANTHILLS - 1];
int prof[2 * MAX_ANTHILLS - 1];
int first[MAX_ANTHILLS];
SegmentTree st(MAX_ANTHILLS);


void eulerTour(int u, int parent, int d) {

    first[u] = idx; euler[idx] = u; prof[idx] = d; idx++;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == parent) continue;

        eulerTour(v, u, d + 1);
        euler[idx] = u; prof[idx] = d; idx++;
    }
}

int lca(int u, int v) {
    return euler[st.query(first[u], first[v])];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n; cin >> n;
    if (n == 0) return false;

    vector<pair<int, int>>v(1); // pos i conected to .first with length .second

    idx = 1;

    int values[MAX_ANTHILLS];

    for (int i = 1; i < n; i++) {
        int a, l; cin >> a >> l;
        v.push_back({a, l});
        values[i - 1] = l;
    }

    st.build(values, n);

    eulerTour(1, 0, 1);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int s, t; cin >> s >> t;
        cout << lca(s, t) << " ";
    }

    cout << "\n";

    return true;    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
        std::ifstream in("datos.txt");
        auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
        #endif 


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
        #ifndef DOMJUDGE // para dejar todo como estaba al principio
        std::cin.rdbuf(cinbuf);
        system("PAUSE");
        #endif

    return 0;
}
