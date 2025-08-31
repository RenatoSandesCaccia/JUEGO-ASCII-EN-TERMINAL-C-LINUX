#include "aventurere.h"
const int PAR_AVENTURERE = 1;
void Aventurere :: setup()
{
    aventurere_x = numMenu[0];
    aventurere_y = numMenu[1];
    alto = 3;
    ancho = 5;
    m_vidas = 3;
 
}

//---------------------------------------------------------------------------------------------------------------------

void Aventurere :: draw()
{
    init_pair(PAR_AVENTURERE, COLOR_BLACK, COLOR_BLUE);

    attron(COLOR_PAIR(PAR_AVENTURERE));

    mvaddch(aventurere_y , aventurere_x, 'L');
    mvaddch(aventurere_y, aventurere_x + 1, 'L');
    mvaddch(aventurere_y , aventurere_x + 2, 'L');
    mvaddch(aventurere_y , aventurere_x + 3, 'L');
    mvaddch(aventurere_y , aventurere_x + 4, 'L');

    mvaddch(aventurere_y + 1 , aventurere_x, '|');
    mvaddch(aventurere_y + 1 , aventurere_x + 1, '0');
    mvaddch(aventurere_y + 1, aventurere_x + 2, '-');
    mvaddch(aventurere_y + 1 , aventurere_x + 3, '0');
    mvaddch(aventurere_y + 1 , aventurere_x + 4, '|');

	mvaddch(aventurere_y + 2, aventurere_x, '(');
    mvaddch(aventurere_y + 2, aventurere_x + 1, ' ');
    mvaddch(aventurere_y + 2, aventurere_x + 2, 'O');
    mvaddch(aventurere_y + 2 , aventurere_x + 3, ' ');
    mvaddch(aventurere_y + 2, aventurere_x + 4, ')');

    

    attroff(COLOR_PAIR(PAR_AVENTURERE));

}

//---------------------------------------------------------------------------------------------------------------------
void Aventurere :: setX(int x) {aventurere_x = x;}
void Aventurere :: setY(int y) {aventurere_y = y;}
int Aventurere :: getY(){return aventurere_y;}
int Aventurere :: getX(){return aventurere_x;}
int Aventurere :: getAlto(){return alto;}
int Aventurere :: getAncho(){return ancho;}
void Aventurere::setVidas(int vidas) { m_vidas = vidas; }
int Aventurere :: getVidas() { return m_vidas; }
bool Aventurere :: pierdeVida() { 
    m_vidas-- ; 
    if (m_vidas <= 0){
        return false;
    }
    return true;
}