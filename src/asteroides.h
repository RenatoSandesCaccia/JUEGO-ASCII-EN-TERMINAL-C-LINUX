#pragma once
#include <iostream>
#include <ncurses.h>
#include "aventurere.h"

using namespace std;

class Asteroide
{
public:
  Asteroide(int x, int y,char dir);
  void update(int ancho,int alto);
  void draw(int altoTerminal,int anchoTerminal);
  void setX(int x);
  void setY(int y);
  int getX();
  int getY();
  int getAlto();
  int getAncho();
  bool colision(Aventurere &rAventurere);

private:
  float m_x, m_y;
  int alto, ancho;
  char direccion;
  int altoPantalla,anchoPantalla;
};