#include<iostream>
using namespace std;
jugada Jugador::juega(Juego const& EJ) {
    jugada mejorC;
    int mejorV = ;
    for (jugada c : EJ.jugadasDesde()) {
        int v = valoraMin(EJ.aplica(c), EJ.turno(), nivel - 1);
        if (v > mejorV) {
            mejorV = v;
            mejorC = c;
        }
    }
    return mejorC;
}
int Jugador::valoraMin(Juego const& EJ, Turno t_orig, int n) {
    if (EJ.terminal() || n == 0)
        return Heuristica(EJ, t_orig);
    else {
        int mejorV = ;
        for (jugada c : EJ.jugadasDesde())
            mejorV = min(valoraMax(EJ.aplica(c), t_orig, n - 1), mejorV);
        return mejorV;
    }
}
int Jugador::valoraMax(Juego const& EJ, Turno t_orig, int n) {
// igual que valoraMin pero calculando un máximo
}

// MiniMax con podas alpha y beta
jugada Jugador::juega(Juego const& EJ) {
    jugada mejorC;
    int mejorV = ;
    for (jugada c : EJ.jugadasDesde()) {
        int v = valoraMin(EJ.aplica(c), EJ.turno(), nivel-1, mejorV, );
        if (v > mejorV) {
            mejorV = v;
            mejorC = c;
        }
    }
    return mejorC;
}
int Jugador::valoraMin(Juego const& EJ, Turno t, int n, int 𝛼, int 𝛽) {
    if (EJ.terminal() || n == 0)
        return Heuristica(EJ, t)
    else {
        for (jugada c : EJ.jugadasDesde()) {
            𝛽 = min(valoraMax(EJ.aplica(c), t, n - 1, 𝛼, 𝛽), 𝛽);
            if (𝛼 >= 𝛽) break;
        }
        return 𝛽;
    }
}
int Jugador::valoraMax(Juego const& EJ, Turno t, int n, int 𝛼, int 𝛽) {
    if (EJ.terminal() || n == 0)
        return Heuristica(EJ, t)
    else {
        for (jugada c : EJ.jugadasDesde()) {
            𝛼 = max(valoraMin(EJ.aplica(c), t, n - 1, 𝛼, 𝛽), 𝛼);
            if (𝛼 >= 𝛽) break;
        }
        return 𝛼;
    }
}
