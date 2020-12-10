#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_Juego.h"

class SokobanTest : public testing::Test {
protected:
    Coordenada pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos6O, pos7, pos8, pos8S, pos9, posN, posE, posS, posO;
    set<Coordenada> posiciones123, posiciones456, posiciones0456, posiciones789, posiciones5789;
    aed2_Nivel n1, n2;

    void SetUp() {
        pos0 = {1, 0};
        posN = {1, 1};
        posE = {2, 0};
        posS = {1, -1};
        posO = {0, 0};
        pos1 = {2, 1};
        pos2 = {-1, 1};
        pos3 = {0, -1};
        pos4 = {3, -1};
        pos5 = {3, -2};
        pos6 = {0, 2};
        pos6O = {-1, 2};
        pos7 = {2, -1};
        pos8 = {2, -2};
        pos8S = {2, -3};
        pos9 = {0, 1};
        posiciones123 = {pos1, pos2, pos3};
        posiciones456 = {pos4, pos5, pos6};
        posiciones0456 = {pos0, pos4, pos5, pos6};
        posiciones789 = {pos7, pos8, pos9};
        posiciones5789 = {pos5, pos7, pos8, pos9};
        n1 = {posiciones123, posiciones456, posiciones789, pos0, 2};
        // Nivel n1:
        //
        // -D---
        // PC-P-
        // --I--
        // -P-CD
        // ---CD
        n2 = {posiciones123, posiciones0456, posiciones5789, pos0, 0};
    }
};

TEST_F(SokobanTest, empezar_sokoban) {
    Sokoban s(n1);

    EXPECT_TRUE(s.hayUnaPared(pos1));
    EXPECT_TRUE(s.hayUnaPared(pos2));
    EXPECT_TRUE(s.hayUnaPared(pos3));
    EXPECT_TRUE(s.hayDeposito(pos4));
    EXPECT_TRUE(s.hayDeposito(pos5));
    EXPECT_TRUE(s.hayDeposito(pos6));
    EXPECT_TRUE(s.hayCaja(pos7));
    EXPECT_TRUE(s.hayCaja(pos8));
    EXPECT_TRUE(s.hayCaja(pos9));
    EXPECT_EQ(s.posicion(), pos0);
    EXPECT_EQ(s.cantidadBombas(), 2);
}

TEST_F(SokobanTest, empezar_sokoban_con_solapamientos) {
    Sokoban s(n2);

    EXPECT_TRUE(s.hayUnaPared(pos1));
    EXPECT_TRUE(s.hayUnaPared(pos2));
    EXPECT_TRUE(s.hayUnaPared(pos3));
    EXPECT_TRUE(s.hayDeposito(pos0));
    EXPECT_TRUE(s.hayDeposito(pos4));
    EXPECT_TRUE(s.hayDeposito(pos5));
    EXPECT_TRUE(s.hayDeposito(pos6));
    EXPECT_TRUE(s.hayCaja(pos5));
    EXPECT_TRUE(s.hayCaja(pos7));
    EXPECT_TRUE(s.hayCaja(pos8));
    EXPECT_TRUE(s.hayCaja(pos9));
    EXPECT_EQ(s.posicion(), pos0);
    EXPECT_EQ(s.cantidadBombas(), 0);
}

TEST_F(SokobanTest, se_puede_mover) {
    Sokoban s(n1);

    EXPECT_TRUE(s.sePuedeMover(0, 1));
    EXPECT_TRUE(s.sePuedeMover(1, 0));
    EXPECT_TRUE(s.sePuedeMover(0, -1));
    EXPECT_TRUE(s.sePuedeMover(-1, 0));
    s.mover(0, 1);
    EXPECT_FALSE(s.sePuedeMover(1, 0));
    EXPECT_FALSE(s.sePuedeMover(-1, 0));
    s.mover(0, -1);
    s.mover(1, 0);
    EXPECT_FALSE(s.sePuedeMover(0, -1));
}

TEST_F(SokobanTest, mover) {
    Sokoban s(n1);

    EXPECT_FALSE(s.mover(0, 1));
    EXPECT_EQ(s.posicion(), posN);
    EXPECT_FALSE(s.mover(0, -1));
    EXPECT_FALSE(s.mover(0, -1));
    EXPECT_EQ(s.posicion(), posS);
    EXPECT_FALSE(s.mover(0, 1));
    EXPECT_FALSE(s.mover(1, 0));
    EXPECT_EQ(s.posicion(), posE);
    EXPECT_FALSE(s.mover(-1, 0));
    EXPECT_FALSE(s.mover(-1, 0));
    EXPECT_EQ(s.posicion(), posO);
}

TEST_F(SokobanTest, tirar_bomba) {
    Sokoban s(n1);

    s.mover(0, 1);
    EXPECT_FALSE(s.sePuedeMover(1, 0));
    EXPECT_FALSE(s.sePuedeMover(-1, 0));

    EXPECT_TRUE(s.hayUnaPared(pos1));
    EXPECT_TRUE(s.hayUnaPared(pos2));
    EXPECT_TRUE(s.hayCaja(pos9));

    s.arrojarBomba();

    // Las paredes se deben romper, y las cajas no
    EXPECT_EQ(1, s.cantidadBombas());
    EXPECT_TRUE(s.hayCaja(pos9));
    EXPECT_FALSE(s.hayUnaPared(pos1));
    EXPECT_FALSE(s.hayUnaPared(pos2));

    // Ahora puede moverse
    EXPECT_TRUE(s.sePuedeMover(1, 0));
    EXPECT_TRUE(s.sePuedeMover(-1, 0));
}

TEST_F(SokobanTest, ganar_nivel) {
    Sokoban s(n1);
    EXPECT_FALSE(s.mover(-1, 0));
    EXPECT_FALSE(s.mover(0, 1));
    EXPECT_FALSE(s.mover(1, 0));
    EXPECT_FALSE(s.mover(0, -1));
    EXPECT_FALSE(s.mover(0, -1));
    EXPECT_FALSE(s.mover(1, 0));
    EXPECT_FALSE(s.mover(-1, 0));
    EXPECT_FALSE(s.mover(0, -1));

    // Gana
    EXPECT_TRUE(s.mover(1, 0));
}

TEST_F(SokobanTest, deshacerMovimiento) {
    Sokoban s({n1});

    // MOV_JUG
    s.mover(0, 1);
    EXPECT_EQ(s.posicion(), posN);
    s.deshacerUltimoMovimiento();
    EXPECT_EQ(s.posicion(), pos0);

    // TIRAR_BOMBA
    s.mover(0, -1);
    s.arrojarBomba();
    EXPECT_FALSE(s.hayUnaPared(pos3));
    s.deshacerUltimoMovimiento();
    EXPECT_TRUE(s.hayUnaPared(pos3));

    // MOV_JUG_Y_CAJA
    for(int i=0; i < 6; i++) {
        EXPECT_FALSE(s.mover(1, 0));
        EXPECT_TRUE(s.hayCaja(pos4));
        s.deshacerUltimoMovimiento();
        EXPECT_TRUE(s.hayCaja(pos7));
        EXPECT_FALSE(s.hayCaja(pos4));
    }
}

