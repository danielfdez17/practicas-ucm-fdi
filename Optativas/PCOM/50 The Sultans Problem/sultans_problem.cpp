// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
using namespace std;

int cases = 1;

const double EPS = 1e-9;
const double PI = acos(-1);

using T = double;
//bool lt(double a, double b) { return a - EPS < b; };
//bool eq(double a, double b) { return fabs(a - b) < EPS; }

//using T = int;
//bool lt(int a, int b) { return a < b; }
//bool eq(int a, int b) { return a == b; }

struct pt {
    T x,y;
    pt operator+(pt p) const { return {x+p.x, y+p.y}; }
    pt operator-(pt p) const { return {x-p.x, y-p.y}; }
    pt operator*(T d) const { return {x*d, y*d}; }
    pt operator/(T d) const { return {x/d, y/d}; } // only for floating-point
    
    bool operator==(pt o) const { return x == o.x && y == o.y; }
    bool operator!=(pt o) const { return !(*this == o); }

    bool operator<(pt o) const { // sort points lexicographically
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
    // bool operator<(pt o) const {
    //     if (fabs(x - o.x) < EPS) return y < o.y;
    //     return x < o.x;
    // }
};


// Devuelve el cuadrado del vector
T sq(pt v) {return v.x*v.x + v.y*v.y;}
// Devuelve el tamanio y magnitud del vector
double abs(pt v) {return sqrt(sq(v));}

ostream& operator<<(ostream& os, pt p) {
    return os << "("<< p.x << "," << p.y << ")";
}

// Producto vectorial
T cross(pt v, pt w) { return v.x*w.y - v.y*w.x; }

// rotate 90º counterclockwise
pt perp(pt p) { return {-p.y, p.x}; }


// LINEAS

struct line {
    pt v; T c;
    // from direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}
    // from equation ax + by = c
    line(T a, T b, T c) : v({b,-a}), c(c) {}
    // from points p and q
    line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
    // dice a que lado de la recta se encuentra p
    // > 0, izq
    // < 0, der
    // == 0, en la recta
    T side(pt p) { return cross(v,p) - c; }
    // distancia minima entre un punto y la recta
    double dist(pt p) { return abs(side(p)) / abs(v); }
    // 
    line translate(pt t) { return {v, c + cross(v,t)}; }
    // devuelve la proyeccion del punto p con la recta this
    pt proj(pt p) { return p - perp(v)*side(p)/sq(v); }
};

// interseccion entre dos lineas
bool inter(line l1, line l2, pt & out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
    return true;
}


// POLIGONOS, el primer y último puntos coinciden

double areaPolygon(vector<pt> const& p) {
    double area = 0.0;
    for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
        area += cross(p[i], p[i+1]);
    }
    return abs(area) / 2.0;
}

// DIVISIÓN DE UN POLÍGONO
vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
    vector<pt> R; pt c;
    for (int i = 0; i < int(P.size()) - 1; i++) {
        double left1 = cross(b - a, P[i] - a),
                left2 = cross(b - a, P[i + 1] - a);
        if (left1 >= 0) R.push_back(P[i]);  // P[i] is on the left of ab
        if (left1 * left2 < 0) {  // edge (P[i], P[i+1]) crosses line ab
            inter({P[i], P[i+1]}, {a,b}, c);
            R.push_back(c);
        }
    }
    if (!R.empty())
        R.push_back(R[0]); // make R's first point = R's last point
    return R;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    double N, W, H, x, y; cin >> N >> W >> H >> x >> y;
    if (!cin) return false;
    pt font = {x,y};
    vector<pt>poligono;
    pt v1 = {0,0}, v2 = {W,0}, v3 = {W,H}, v4 = {0,H};
    // Se guardan en un vector de puntos lo puntos que conforman el poligono 
    poligono.push_back(v1);
    poligono.push_back(v2);
    poligono.push_back(v3);
    poligono.push_back(v4);
    poligono.push_back(v1);
    // Se guardan todas las rectas
    for (int i = 0; i < N; ++i) {
        double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        pt p1 = {x1,y1}, p2 = {x2,y2};
        // Se guardan en la estructura de tipo linea
        line l(p1, p2);
        // Y se comprueba donde esta la fuente con respecto a la linea
        // Si la fuente esta a la izquierda de la linea
        if (l.side(font) > 0) {
            // El poligono se corta con la direccion del vector de la recta, 
            // para que devuelva el poligono que contiene a la fuente
            poligono = cutPolygon(p1, p2, poligono);
        }
        // En cambio, si la fuente esta a la derecha de la linea
        else if (l.side(font) < 0) {
            // Se corta el poligono con la direccion opuesa a la recta dada
            // Si no se hace asi, el poligono resultado devolveria el poligono en el que no se encuentra la fuente
            poligono = cutPolygon(p2, p1, poligono);
        }
    }
    // Al final se calcula el area del poligono resultado
    double area = areaPolygon(poligono);
    // Y se muestra como pide el enunciado
    cout << "Case #" << cases << ": " << fixed << setprecision(3) << area << "\n";
    ++cases;
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