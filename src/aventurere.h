#pragma once
#include <iostream>
#include <ncurses.h>

class Aventurere
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
 void setVidas(int vidas);
 int getVidas();
 bool pierdeVida();
 void setPuntaje();
 int getPuntaje();
 

private:
int aventurere_x, aventurere_y;
int alto, ancho;
int m_x, m_y;
int m_vidas;
int numMenu[2] = {80,20};

};