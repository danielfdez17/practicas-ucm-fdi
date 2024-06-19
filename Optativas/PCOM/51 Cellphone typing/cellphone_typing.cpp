// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

const int MAXN = 26;

class Trie {
    int prefixes, words, pulsaciones, size;
    vector<Trie *>child;
public:
    Trie() : prefixes(0), words(0), pulsaciones(0), size(0), child(MAXN, nullptr) {}
    ~Trie() {
        for (int i = 0; i < MAXN; ++i) 
            delete child[i];
    }
    void add(const char *s) {
        if (*s == '\0') ++words;
        else {
            Trie * t;
            int pos = *s - 'a';
            if (child[pos] == nullptr) {
                t = child[pos] = new Trie();
                t->prefixes = 1;
                t->size = 1;
                t->pulsaciones = 1;
            }
            else {
                t = child[pos];
                t->prefixes++;
                t->size++;
            }
            t->add(s+1);
        }
    }
    double getResult() const {
        return (words / (pulsaciones * 1.0)) * 100;
    }
    // int getWords() const {
    //     int res = 0;
    //     for (int i = 0; i < MAXN; ++i) {
    //         if (child[i] != nullptr) {
    //             res += child[i]->getWords();
    //         }
    //     }
    //     res += words;
    //     return res;
    // }
    int getPulsaciones() const {
        int res = 0;        
        for (int i = 0; i < MAXN; ++i) {
            if (child[i] != nullptr) {
                if (child[i]->size > 1) {
                    res += child[i]->getPulsaciones() + 1;
                }
            }
        }
        res += pulsaciones;
        return res;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N; cin >> N;
    if (!cin) return false;
    
    Trie trie;

    for (int i = 0; i < N; ++i) {
        string word; cin >> word;
        // word.push_back('\0');
        trie.add(word.c_str());
    }

    // int words = trie.getWords();
    int pulsaciones = trie.getPulsaciones();

    double res = ((pulsaciones * 1.0) / N) * 100;

    cout << fixed << setprecision(2) << round(res) / 100 << "\n";

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