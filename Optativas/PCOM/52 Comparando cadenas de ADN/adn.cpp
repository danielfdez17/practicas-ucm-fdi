// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include<vector>
#include<string>
#include<cstring>
#include <unordered_map>
using namespace std;

const int MAXN =5;//numero de componentes que tiene el alfabeto del diccionario

class Trie {
    int prefixes;//numero de palabras al que es prefijo ese nodo 
    int words;//numero de palabras que contiene ese nodo
    vector<Trie*>child;
public:
    Trie() : prefixes(0), words(0), child(MAXN, nullptr) {}
    unordered_map<char ,int>dic;
    
    //destructor que va a borrar todo el vector de los hijos
    ~Trie() {
        for (int i = 0; i < MAXN; ++i)
            delete child[i];
    } 
    //contructor para añadir una palabra al diccionario
    void add(const char* s) {
        if (*s == '\0') ++words;
        else {
            
            Trie* t;
            int pos = dic[*s] - dic['A'];
            /* 
            if (*s == '-') {
                Trie* t;
                for (int i = 0; i < child.size(); i++) {
                    if (child[pos] != nullptr) {
                        t = child[i];
                        t->prefixes++;
                    }
                }

            }
            */
            if (child[pos] == nullptr ) {
                t = child[pos] = new Trie();
                t->prefixes = 1;

            }
            else {
                t = child[pos];
                t->prefixes++;
                
            }
            
            t->add(s + 1);
            
            
            
        }
    }
    void creatDic() {
        dic['A'] = 1;
        dic['C'] = 2;
        dic['G'] = 3;
        dic['T'] = 4;
        dic['-'] = 5;
   
    }

    int getWordsWithPrefix(const char* s) {
        Trie* t = this;
        while (*s != '\0' && t != nullptr) {
            int pos = dic[*s] - dic['A']; 
            t = t->child[pos];
            ++s;
        }
        return (t != nullptr) ? t->words : 0;
    }

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N; cin >> N;
    if (!cin) return false;
    vector<string>s(N);
    Trie trie;
    trie.creatDic();
    for (int i = 0; i < N; i++) {
        cin >> s[i];
        trie.add(s[i].c_str());
    }
   
    for (int i = 0; i < N; i++) {
        int palabrasIguales = trie.getWordsWithPrefix(s[i].c_str()) - 1;
        cout << palabrasIguales << " ";
    }
    cout << '\n';

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