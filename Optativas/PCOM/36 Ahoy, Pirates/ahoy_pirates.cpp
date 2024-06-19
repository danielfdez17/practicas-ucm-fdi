// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define N 1024000
#define BARBARY 0
#define BUCCANER 1
#define INV 2
#define NOP 3

int casos = 1;

class SegmentTree {
private:
    vector<int>st, lazy;
    int tam;
    void updateRange(int vertex, int L, int R, int a, int b, int op) {
        pushLazyUpdate(vertex, L, R);

        if (b < L || R < a) return;

        if (a <= L && R <= b) {
            setLazyUpdate(vertex, op);
            pushLazyUpdate(vertex, L, R);
            return;
        }
        int m = (L + R) / 2;
        updateRange(2 * vertex, L, m, a, b, op);
        updateRange(2 * vertex + 1, m + 1, R, a, b, op);

        st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
    }
    int query(int vertex, int L, int R, int i, int j) {

        pushLazyUpdate(vertex, L, R);

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
    SegmentTree(int maxN) : lazy(maxN, NOP) {
        st.reserve(4 * maxN + 10);
    }
    void setLazyUpdate(int vertex, int value) {
        int op = lazy[vertex];
        if (op == NOP) {

        }
        else if (op == BUCCANER) {
            if (value == BARBARY || value == INV) {
                lazy[vertex] = BARBARY;
            }
        }
        else if (op == BARBARY) {
            if (value == BUCCANER || value == INV) {
                lazy[vertex] = BUCCANER;
            }
        }
        else if (op == INV) {
            if (value == INV) lazy[vertex] = NOP;
            // else if (value == BUCCANER) lazy[vertex] = 0;
            // else if (value == BARBARY) lazy[vertex] = 0; 
        }
        lazy[vertex] += value;
    }
    void pushLazyUpdate(int vertex, int L, int R) {
        st[vertex] += (R - L + 1) * lazy[vertex];

        if (L != R) {
            int m = (L + R) / 2;
            setLazyUpdate(2 * vertex, lazy[vertex]);
            setLazyUpdate(2 * vertex + 1, lazy[vertex]);
        }

        lazy[vertex] = 0;
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
void resuelveCaso() {

    cout << "Case " << casos << ":\n";

    int m; cin >> m;
    string pirates;

    for (int i = 0; i < m; i++) {
        int t; cin >> t >> pirates;
        string aux = pirates;
        for (int j = 0; j < t; j++) {
            pirates.append(aux);
        }
    }

    SegmentTree st(N);
    int values[N];
    for (int i = 0; i < pirates.size(); i++) {
        values[i] = atoi(&pirates[i]);
    }

    st.build(values, pirates.size());

    int q, queries = 1; cin >> q;
    for (int i = 0; i < q; i++) {
        
        char c; int a, b; cin >> c >> a >> b;
        switch(c) {
            case 'F':
            for (int j = a; j <= b; j++) st.setLazyUpdate(j, BUCCANER);
            break;
            case 'E':
            for (int j = a; j <= b; j++) st.setLazyUpdate(j, BARBARY);
            break;
            case 'I':
            for (int j = a; j <= b; j++) st.setLazyUpdate(j, INV);
            break;
            case 'S':
            cout << "Q" << queries << ": " << st.query(a, b) << "\n";
            // st.query(a, b);
            break;
        }
    }
    casos++;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}