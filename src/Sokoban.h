#ifndef TP4_SOKOBAN_SOKOBAN_H
#define TP4_SOKOBAN_SOKOBAN_H

#include "Tipos.h"
#include <vector>
#include <list>

class Sokoban {
public:
    Sokoban(aed2_Nivel);

    Coordenada posicion() const ;

    Nat cantidadBombas() const;

    bool hayCaja(Coordenada p) const;

    bool hayUnaPared(Coordenada p) const;

    bool hayDeposito(Coordenada p) const;

    bool mover(int x, int y);

    bool sePuedeMover(int x, int y) const;

    void arrojarBomba();

    void deshacerUltimoMovimiento();


private:

    enum Key{
        MOV_JUG, MOV_JUG_Y_CAJA, TIRAR_BOMBA
    };
    typedef struct jugada{
        Key key;
        std::pair<int, int> direcc;
        Nat indiceCaja;
        int cambioPuntuacion;
        jugada(Key k, std::pair<int, int> dir = make_pair(0,0), Nat i = -1, int cambioPuntuacion=0):
            key(k), direcc(dir), indiceCaja(i), cambioPuntuacion(cambioPuntuacion){}
    } jugada;

    Coordenada jugador;
    int cantBombas;
    std::vector<Coordenada> cajas;
    std::vector<Coordenada> paredes;
    std::vector<Coordenada> depositos;
    Nat depositosOcupados;
    std::list<Coordenada> bombasTiradas;
    std::list<jugada> jugadas;

    Nat reemplazarCaja(Coordenada c1, Coordenada c2);

};


#endif //TP4_SOKOBAN_SOKOBAN_H
