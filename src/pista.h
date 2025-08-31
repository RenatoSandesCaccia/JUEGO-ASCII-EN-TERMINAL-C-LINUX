#pragma once
#include <iostream>
#include <ncurses.h>
#include "aventurere.h"

class Pista
{
public:
 void setup();
 void draw ();

 void setX(int x);
 void setY(int y);
 int getX();
 int getY();
 int getAlto();
 int getAncho();
 void mover(int ANCHO, int ALTO);
 bool colision(Aventurere &rAventurere);

private:
 int pista_x, pista_y;
 int alto, ancho;
 

};