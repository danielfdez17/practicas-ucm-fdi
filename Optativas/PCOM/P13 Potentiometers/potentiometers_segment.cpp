// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 200000

int cases = 1;

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

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N; cin >> N;
    if (N == 0) return false;
    
    cout << "Case " << cases << ":\n";
    SegmentTree segment(N);
    int v[MAX_N];
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    segment.build(v, N);

    string op; cin >> op;
    while (op != "END") {
        int first, second; cin >> first >> second;
        if (op == "M") {
            cout << segment.query(first - 1, second - 1) << "\n";
        } 
        else {
            segment.update(first - 1, second);
        }
        cin >> op;
    }

    cases++;
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
