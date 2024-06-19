
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
using namespace std;

#define REST_TIME 10
#define SIXTY_MIN 60
#define TWELVE_MINUTES 1440


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// class Film {
// private:
//     int hours, minutes, duration, finish_hour, finish_minute;
// public:
//     Film() : hours(0), minutes(0), duration(0), finish_hour(0), finish_minute(0) {}
//     Film(int h, int m, int d) : hours(h), minutes(m), duration(d) {
//         int total_minutes = duration + minutes;
//         int count_hours = 0;
//         while (total_minutes > SIXTY_MIN) {
//             ++count_hours;
//             total_minutes -= SIXTY_MIN;
//         }
//         finish_hour = hours + count_hours;
//         finish_minute = total_minutes;
//     }
//     int gethours() const { return hours; }
//     int getMinutes() const { return minutes; }
//     int getDuration() const { return duration; }
//     pair<int, int> getFinishTime() const { return {finish_hour, finish_minute}; }
// };

// bool operator<(Film const& left, Film const& right) {
//     if (left.gethours() > right.gethours()) return false;
//     if (left.gethours() == right.gethours()) {
//         if (left.getMinutes() > right.getMinutes()) return false;
//         if (left.getMinutes() == right.getMinutes()) {
//             if (left.getDuration() >= right.getDuration()) return false;
//         }
//     }
//     return true;
// }

struct Film {
    int begin, end; // in minutes
};

bool operator<(Film const& left, Film const& right) {
    return left.end < right.end;
}

bool resuelveCaso() {
    int n; cin >> n;
    if (n == 0) return false;

    vector<Film> films(n);

    for (int i = 0; i < n; i++) {
        int hours, minutes, duration; char c;
        cin >> hours >> c >> minutes >> duration;
        films[i] = {hours * SIXTY_MIN + minutes, hours * SIXTY_MIN + minutes + duration};
    }

    sort(films.begin(), films.end());

    int film_counter = 0, last_film_end = -REST_TIME;
    for (int i = 0; i < n; i++) {
        if (films[i].end <= TWELVE_MINUTES) {
            if (last_film_end + REST_TIME <= films[i].begin) {
                ++film_counter;
                last_film_end = films[i].end;
            }
        }
        // Film i_film = films[i];
        // if (i_film.getFinishTime().first < 24) {
        //     if (last_film_time.first < i_film.gethours()) {
        //         film_counter++;
        //         last_film_time = i_film.getFinishTime();
        //     }
        //     else if (last_film_time.first == i_film.gethours()) {
        //         if (last_film_time.second <= i_film.getMinutes()) {
        //             film_counter++;
        //             last_film_time = i_film.getFinishTime();
        //         }
        //     }
        // }
    }

    cout << film_counter << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
