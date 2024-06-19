// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 26;

class Trie {
    int prefixes, words;
    vector<Trie *> child;

public:
    Trie() : prefixes(0), words(0), child(MAXN, nullptr) {}
    ~Trie() {
        for (int i = 0; i < MAXN; ++i)
            delete child[i];
    }

    void add(const char *s) {
        if (*s == '\0')
            ++words;
        else {
            Trie *t;
            int pos = *s - '0'; // assuming the input consists of '0' and '1'
            if (child[pos] == nullptr) {
                t = child[pos] = new Trie();
                t->prefixes = 1;
            } else {
                t = child[pos];
                t->prefixes++;
            }
            t->add(s + 1);
        }
    }

    pair<int, int> findOccurrences(const char *s) {
        int count = 0, len = strlen(s);

        for (int i = 0; i < MAXN; ++i) {
            Trie *t = child[i];
            if (t != nullptr) {
                count += t->findOccurrences(s, len, 0);
            }
        }

        return {count, len};
    }

private:
    int findOccurrences(const char *s, int len, int index) {
        if (index == len)
            return words;

        int pos = s[index] - '0';
        Trie *t = child[pos];

        if (t == nullptr)
            return 0;

        return t->findOccurrences(s, len, index + 1) + t->findOccurrences(s, len, index);
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int tx, ty; cin >> tx >> ty;
    if (!cin) return false;

    Trie trie;

    for (int i = 0; i < ty; ++i) {
        string fila; cin >> fila;
        trie.add(fila.c_str());
    }

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string palabra; cin >> palabra;
        pair<int, int> apariciones = trie.findOccurrences(palabra.c_str());
        if (apariciones.first > 0) 
            cout << palabra << " " << apariciones.second << "\n";
    }

    cout << "---\n";
    
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