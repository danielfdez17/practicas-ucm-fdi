// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <vector> 
using namespace std;

#define MAX_N 100000

int getOne(int x) {
    if (x > 0) return 0;
    else if (x < 0) return 1;
    return -MAX_N;
}

void showOne(int x) {
    if (x >= 0) 
        if (x == 0 || x % 2 == 0) cout << "+";
        else cout << "-";
    else cout << "0";
}

class FenwickTree {
private:
    vector<int> ft;
public:
    FenwickTree(int n) { ft.assign(n + 1, 0); }
    int getSum(int b) {
        int ret = 0;
        while (b) {
            ret += ft[b]; b -= (b & -b);
        }
        return ret;
    }
    void add(int pos, int val) {
        while (pos < ft.size()) {
            ft[pos] += val; pos += (pos & - pos);
        }
    }
    int getSum(int a, int b) {
        return getSum(b) - getSum(a - 1);
    }
    int getValue(int pos) {
        return getSum(pos) - getSum(pos - 1);
    }
    void setValue(int pos, int val) {
        add(pos, val - getValue(pos));
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, k; cin >> n >> k;
    if (!cin) return false;

    FenwickTree fenwick(n);

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        fenwick.add(i + 1, getOne(x));
    }    

    for (int i = 0; i < k; i++) {
        string op; cin >> op;
        if (op == "C") {
            int I, V; cin >> I >> V;
            fenwick.setValue(I, getOne(V));
        }
        else {
            int I, J; cin >> I >> J;
            showOne(fenwick.getSum(I, J));
        }
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