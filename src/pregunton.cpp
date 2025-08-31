#include "pregunton.h"
#include <ctime>
#include <string>
#include <vector>

const int PAR_PREGUNTON = 2; 
void Pregunton :: setup()
{
    x = 60;
    y = 20;
    alto = 2;
    ancho = 2;
   
}

//---------------------------------------------------------------------------------------------------------------------
void Pregunton :: draw(int ALTO,int ANCHO)
{
    erase();
   
	mvprintw(ALTO /2 - 5, 27, "Lo único que no tenes que ser, es lo que fuiste cuando no eras"); 

    mvprintw(ALTO/2  , 40, "Presione enter para continuar...");
}
//---------------------------------------------------------------------------------------------------------------------
void Pregunton :: setX(int xp) {xp = x;}
void Pregunton :: setY(int yp) {yp = y;}
int Pregunton :: getY(){return y;}
int Pregunton :: getX(){return x;}
int Pregunton :: getAncho(){return ancho;} 