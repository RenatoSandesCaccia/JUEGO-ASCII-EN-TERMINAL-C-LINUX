#pragma once
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

class Pregunton
{
public:
 void setup();
 void draw (int ALTO,int ANCHO);

 void setX(int x);
 void setY(int y);
 int getX();
 int getY();
 int getAncho();
 void getPregunta();



private:
 int x, y;
 int alto, ancho;
 int vidas;
 int tiempo;
 
 
};