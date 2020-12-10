//
// Created by matias on 24/11/20.
//

#include "Sokoban.h"

using namespace std;

template<class T>
bool busquedaBinaria(vector<T> v, T item){
    int low=0, high=v.size();
    while (low+1 < high) {
        int mid = (low + high)/ 2;

        if (v[mid] <= item)
            low = mid;
        else
            high = mid;
    }

    return v[low]==item;
}

pair<int, int> operator+(pair<int, int>p1, pair<int, int> p2){
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

pair<int, int> operator-(pair<int, int> p1, pair<int, int> p2) {
    return make_pair(p1.first - p2.first, p1.second - p2.second);
}

vector<Coordenada> ordenar(vector<Coordenada> v){
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size()-i-1; ++j) {
            if(v[j] > v[j+1]){
                Coordenada aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
    return v;
}

vector<Coordenada> setToVect(set<Coordenada> s){
    vector<Coordenada> v(s.size());
    int i = 0;
    for (Coordenada coord: s) {
        v[i] = coord;
        i++;
    }
    return v;
}


Sokoban::Sokoban(aed2_Nivel nivel) :
    bombasTiradas(),
    jugadas(),
    jugador(nivel.posicionInicial),
    cantBombas(nivel.cantidadBombas) {

    Nat depositosOcupados = 0;

    for (Coordenada depo : nivel.depositos) {
        for (Coordenada caja : nivel.cajas) {
            if(caja==depo) {
                depositosOcupados++;
                break;
            }
        }
    }

    cajas = setToVect(nivel.cajas);
    paredes = ordenar(setToVect(nivel.paredes));
    depositos = ordenar(setToVect(nivel.depositos));
    this->depositosOcupados = depositosOcupados;
}

Coordenada Sokoban::posicion() const{
    return jugador;
}

Nat Sokoban::cantidadBombas() const{
    return cantBombas;
}

bool Sokoban::hayCaja(Coordenada p) const{
    bool res = false;
    for (Coordenada caja : cajas) {
        if (caja == p) {
            res = true;
        }
    }
    return res;
}

bool Sokoban::hayUnaPared(Coordenada p) const{
    bool res;
    if (busquedaBinaria(paredes, p)) {
        res = true;
        for (Coordenada bomb : bombasTiradas) {
            res = res && (bomb.first != p.first && bomb.second != p.second);
        }
    } else {
        res = false;
    }
    return res;
}

bool Sokoban::hayDeposito(Coordenada p) const{
    if (depositos.size() == 1) {
        return depositos[0] == p;
    } else if (p < depositos[0]) {
        return false;
    } else if (p >= depositos[depositos.size() - 1]) {
        return depositos[depositos.size() - 1] == p;
    } else {
        return busquedaBinaria(depositos, p);
    }
}

bool Sokoban::mover(int x, int y){
    assert(sePuedeMover(x, y));
    jugador = jugador + make_pair(x, y);
    if(!hayCaja(jugador )){
        jugadas.push_back(jugada(Key::MOV_JUG, make_pair(x, y), 0));
        return false;
    }

    pair<int, int> cajaVieja = jugador;
    pair<int, int> cajaNueva = jugador + make_pair(x, y);
    Nat indiceCaja = reemplazarCaja(cajaVieja, cajaNueva);

    jugadas.push_back(jugada(Key::MOV_JUG_Y_CAJA, make_pair(x, y), indiceCaja));

    if(hayDeposito(cajaVieja)) {
        depositosOcupados--;
        jugadas.back().cambioPuntuacion--;
    }
    if(hayDeposito(cajaNueva)){
        depositosOcupados++;
        jugadas.back().cambioPuntuacion++;
    }

    return depositosOcupados == depositos.size();
}

bool Sokoban::sePuedeMover(int x, int y)const{
    if(!hayUnaPared(jugador+make_pair(x,y)) && !hayCaja(jugador+make_pair(x,y)))
        return true;
    if(hayCaja(jugador+make_pair(x,y)) && (
        !hayUnaPared(jugador+make_pair(x*2,y*2)) && !hayCaja(jugador+make_pair(x*2,y*2))))
        return true;
    return false;
}


void Sokoban::arrojarBomba(){
    cantBombas--;
    bombasTiradas.push_front(jugador);
    jugadas.push_back(jugada(Key::TIRAR_BOMBA));
}

void Sokoban::deshacerUltimoMovimiento(){
    if(jugadas.empty()) return;

    if (jugadas.back().key == TIRAR_BOMBA) {
        bombasTiradas.pop_front();
        cantBombas++;
    }
    else if (jugadas.back().key == MOV_JUG_Y_CAJA) {
        cajas[jugadas.back().indiceCaja] = jugador;
        jugador = jugador - jugadas.back().direcc;
        depositosOcupados -= jugadas.back().cambioPuntuacion;
    }
    else {
        jugador = jugador - jugadas.back().direcc;
    }
    jugadas.pop_back();
}

Nat Sokoban::reemplazarCaja(Coordenada c1, Coordenada c2){
    for (Nat i = 0; i < cajas.size(); i++) {
        if(cajas[i] == c1){
            cajas[i] = c2;
            return i;
        }
    }
}
