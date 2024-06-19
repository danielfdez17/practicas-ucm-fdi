// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include<fstream>
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
const double EPS = 1e-9;
const double PI = acos(-1);

using T = double;
vector<int, pair<int, int>>v;

struct pt {
    T x, y;
    pt operator+(pt p) const { return { x + p.x, y + p.y }; }
    pt operator-(pt p) const { return { x - p.x, y - p.y }; }
    pt operator*(T d) const { return { x * d, y * d }; }
    pt operator/(T d) const { return { x / d, y / d }; } // only for floating-point

    bool operator==(pt o) const { return x == o.x && y == o.y; }
    bool operator!=(pt o) const { return !(*this == o); }

    bool operator<(pt o) const { // sort points lexicographically
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
    bool operator<(pt o) const {
        if (fabs(x - o.x) < EPS) return y < o.y;
        return x < o.x;
    }
};


// Devuelve el cuadrado del vector
T sq(pt v) { return v.x * v.x + v.y * v.y; }
// Devuelve el tamanio y magnitud del vector
double abs(pt v) { return sqrt(sq(v)); }

ostream& operator<<(ostream& os, pt p) {
    return os << "(" << p.x << "," << p.y << ")";
}

double dist(pt a, pt b) { // Euclidean distance
    return hypot(a.x - b.x, a.y - b.y);
}
T dist2(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// PRODUCTOS

// Producto escalar
T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }

bool isPerp(pt v, pt w) { return dot(v, w) == 0; }

// Producto escalar entre el tamanio de los vectores
double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

// Producto vectorial
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }

// positivo/cero/negativo: c a la izquieda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    else
        return 2 * PI - angle(b - a, c - a);
}


// ORDENACIÓN POLAR

bool half(pt p) { // true if in blue half
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

// ordena los puntos por cjtos colineales
void polarSort(vector<pt>& v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
        });
}


// TRANSFORMACIONES

// el objeto se mueve en la dir del vector tanto como su tamanio
pt translate(pt v, pt p) { return p + v; }

// scale p by a certain factor around a center c
// factor > 0 => grande, factor < 0 => pequenio
pt scale(pt c, double factor, pt p) {
    return c + (p - c) * factor;
}

// rotate p by a certain angle a counter-clockwise around origin
// rotar en sentido anti horario
pt rotate(pt p, double a) {
    return { p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a) };
}

// rotate 90º counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }


// LINEAS

struct line {
    pt v; T c;
    // from direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}
    // from equation ax + by = c
    line(T a, T b, T c) : v({ b,-a }), c(c) {}
    // from points p and q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
    // dice a que lado de la recta se encuentra p
    // > 0, izq
    // < 0, der
    // == 0, en la recta
    T side(pt p) { return cross(v, p) - c; }
    // distancia minima entre un punto y la recta
    double dist(pt p) { return abs(side(p)) / abs(v); }
    // 
    line translate(pt t) { return { v, c + cross(v,t) }; }
    // devuelve la proyeccion del punto p con la recta this
    pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
};

// interseccion entre dos lineas
bool inter(line l1, line l2, pt& out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}


// POLIGONOS, el primer y último puntos coinciden

double areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> const& p) {
    double area = 0.0;
    for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
        area += cross(p[i], p[i + 1]);
    }
    return abs(area) / 2.0;
}

bool isConvex(vector<pt> const& p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = (int)p.size(); i < n; ++i) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}


// ENVOLVENTE CONVEXA

// para aceptar puntos colineales cambia a >=
// returns true if point r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
    return orient(p, q, r) > 0;
}

// devuelve un polígono con la envolvente convexa de una nube de puntos P.
vector<pt> convexHull(vector<pt>& P) {
    int n = int(P.size()), k = 0;
    vector<pt> H(2 * n);
    sort(P.begin(), P.end());
    // build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && !ccw(H[k - 2], H[k - 1], P[i])) --k;
        H[k++] = P[i];
    }
    // build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && !ccw(H[k - 2], H[k - 1], P[i])) --k;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}


// DIVISIÓN DE UN POLÍGONO

vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
    vector<pt> R; pt c;
    for (int i = 0; i < int(P.size()) - 1; i++) {
        double left1 = cross(b - a, P[i] - a),
            left2 = cross(b - a, P[i + 1] - a);
        if (left1 >= 0) R.push_back(P[i]);  // P[i] is on the left of ab
        if (left1 * left2 < 0) {  // edge (P[i], P[i+1]) crosses line ab
            inter({ P[i], P[i + 1] }, { a,b }, c);
            R.push_back(c);
        }
    }
    if (!R.empty())
        R.push_back(R[0]); // make R's first point = R's last point
    return R;
}

struct torre {
    double x, y;
    int p;
};
vector<torre>torres;
vector<torre>tFree;
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
int M, N; // M parte izq, N parte der
vector<vector<int>>grafo(1000);
vector<int>match, vis;

void montarGrafo(vector<torre>P, vector<torre>G, int& r) {
    int n = P.size() + G.size();
    int t = P.size();
    //grafo.resize(n);
    for (int i = 0; i < P.size(); i++) {
        for (int j = 0; j < G.size(); j++) {
            if (dist2({ P[i].x,P[i].y }, { G[j].x, G[j].y }) <= r * r && P[i].p > G[j].p) {
                grafo[i].push_back(t + j);
            }
            if (dist2({ P[i].x,P[i].y }, { G[j].x, G[j].y }) <= r * r && P[i].p < G[j].p) {
                grafo[t + j].push_back(i);
            }
        }

    }


}

int aug(int l) {
    // devuelve 1 si encuentra un augmenting path para el matching M representado en match
    if (vis[l]) return 0;
    vis[l] = 1;
    for (auto r : grafo[l]) {
        if (match[r] == -1 || aug(match[r])) {
            match[r] = l;
            return 1;
        }
    }
    return 0;
}


int merge_mcbm() {
    int mcbm = 0;
    match.assign(N + M, -1);
    for (int l = 0; l < M; l++) {
        vis.assign(M, 0);
        mcbm += aug(l);
    }
    return mcbm;
}
bool resuelveCaso() {
    int n, p, c;
    double x, y;
    int a, b, r;
    cin >> n;

    if (n == 0) return false;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> p;
        torres.push_back({ x, y, p });
    }
    cin >> a >> b >> r;
    line l = line({ torres[a - 1].x,torres[a - 1].y }, { torres[b - 1].x,torres[b - 1].y });
    vector<torre> tladoI, tladoD;
    for (int i = 0; i < torres.size(); i++) {
        if (torres[i].p == 0)continue;
        if (l.side({ torres[i].x , torres[i].y }) > 0) {
            tladoD.push_back({ torres[i].x , torres[i].y });
        }
        else
            tladoI.push_back({ torres[i].x , torres[i].y });
    }
    int batlesWins = 0;
    if (tladoD.size() < tladoI.size()) {
        montarGrafo(tladoD, tladoI, r);
        M = tladoD.size();
        N = tladoI.size();
    }
    else {
        montarGrafo(tladoI, tladoD, r);
        N = tladoD.size();
        M = tladoI.size();
    }

    batlesWins = merge_mcbm();
    cout << "Case " << c << ": " << batlesWins << "\n";
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