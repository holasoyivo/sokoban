#include "aed2_Juego.h"

std::pair<int, int> pcToPair(PuntoCardinal pc){
    switch (pc) {
        case Norte:
            return make_pair(0,1);
        case Este:
            return make_pair(1,0);
        case Sur:
            return make_pair(0,-1);
        case Oeste:
            return make_pair(-1,0);
    }
}

aed2_Juego::aed2_Juego(vector<aed2_Nivel> ns) : actual(ns.at(0)){
    for (int i = 1; i < ns.size(); ++i) {
        niveles.push_back(ns[i]);
    }
}

bool aed2_Juego::hayPared(Coordenada c) const {
    return actual.hayUnaPared(c);
}

bool aed2_Juego::hayDeposito(Coordenada c) const {
    return actual.hayDeposito(c);
}

bool aed2_Juego::hayCaja(Coordenada c) const {
    return actual.hayCaja(c);
}

Coordenada aed2_Juego::posicionActual() const {
    return actual.posicion();
}

Nat aed2_Juego::cantidadBombas() const {
    return actual.cantidadBombas();
}

bool aed2_Juego::sePuedeMover(PuntoCardinal pc) const {
    std::pair<int,int> p = pcToPair(pc);
    return actual.sePuedeMover(p.first, p.second);
}

// IMPORTANTE: Debe devolver:
// - true si al mover se completa el nivel actual
// - false en caso contrario.
bool aed2_Juego::mover(PuntoCardinal pc) {
    std::pair<int,int> p = pcToPair(pc);
    bool res = actual.mover(p.first, p.second);
    if(res && !niveles.empty()){
        actual = Sokoban(niveles.front());
        niveles.pop_front();
    }
    return res;
}

void aed2_Juego::tirarBomba() {
    Sokoban &s = actual;
    return s.arrojarBomba();
}

void aed2_Juego::deshacer() {
    return actual.deshacerUltimoMovimiento();
}

