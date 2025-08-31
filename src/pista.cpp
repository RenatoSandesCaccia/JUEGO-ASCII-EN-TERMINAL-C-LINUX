#include "pista.h"
#include <ctime>
const int PAR_PISTA = 2; 
void Pista :: setup()
{

    pista_x = 60;
    pista_y = 20;
    alto = 1;
    ancho = 1;

 
}

//---------------------------------------------------------------------------------------------------------------------
void Pista :: draw()
{
    init_pair(PAR_PISTA, COLOR_RED, COLOR_BLACK);
 
    attron(COLOR_PAIR(PAR_PISTA));
	mvaddch(pista_y, pista_x, ACS_DIAMOND); 
    attroff(COLOR_PAIR(PAR_PISTA));
    
}
//---------------------------------------------------------------------------------------------------------------------
void Pista :: setX(int x) {pista_x = x;}
void Pista :: setY(int y) {pista_y = y;}
int Pista :: getY(){return pista_y;}
int Pista :: getX(){return pista_x;}
int Pista :: getAlto(){return alto;}
int Pista :: getAncho(){return ancho;}
void Pista :: mover(int ANCHO,int ALTO){
    srand(time(NULL));
    pista_x = (rand() % (ANCHO - 3)) + 2;
	pista_y = (rand() % (ALTO - 3)) + 2;
}
bool Pista :: colision(Aventurere &rAventurere){
    
    int Ax1 = rAventurere.getX();
    int Ax2 = rAventurere.getX() + rAventurere.getAncho();
    int Ay1 = rAventurere.getY();
    int Ay2 = rAventurere.getY() + rAventurere.getAlto();
    int Px1 = getX();
    int Px2 = getX() + getAncho();
    int Py1 = getY();
    int Py2 = getY() + getAlto();

    bool condicionx = (Ax1 <= Px1 &&  Ax2 >= Px1) || (Ax1 <= Px2 &&  Ax2 >= Px2); 
    bool condiciony = (Ay1 <= Py1 &&  Ay2 >= Py1) || (Ay1 <= Py2 &&  Ay2 >= Py2); 

    if(condicionx && condiciony){

        return true;
    }
    return false;
}
   