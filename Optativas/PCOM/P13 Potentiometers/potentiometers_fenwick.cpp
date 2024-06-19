// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 200000

int cases = 1;

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
    int N; cin >> N;
    if (N == 0) return false;
    
    cout << "Case " << cases << ":\n";
    FenwickTree fenwick(N);

    for (int i = 0; i < N; i++) {
        int ohms; cin >> ohms;
        fenwick.add(i + 1, ohms);
    }

    string op; cin >> op;
    while (op != "END") {
        int first, second; cin >> first >> second;
        if (op == "M") {
            cout << fenwick.getSum(first, second) << "\n";
        } 
        else {
            fenwick.setValue(first, second);
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
