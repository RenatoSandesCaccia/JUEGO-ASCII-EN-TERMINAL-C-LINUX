#include "asteroides.h"

Asteroide::Asteroide(int x, int y,char dir)
{
  m_x = x;
  m_y = y;
  ancho = 4;
  alto = 3;
  direccion = dir;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Asteroide::update(int anchoTerminal,int altoTerminal)
{
 
    if(direccion == 'y'){
        m_y = m_y - 0.4f;
        if (m_y  <= 1){
            m_x = rand() % anchoTerminal - ancho - 1; 
            while(m_x <= 1 ){
                m_x = rand() % anchoTerminal - ancho - 1; 
            }
            m_y = 38;
        }
    }else{
        m_x = m_x + 0.8f;
        if (m_x + getAncho() >= anchoTerminal - 1){
            m_y = rand() % altoTerminal - alto -1; 
            while(m_y <= 1 ){
                m_y = rand() % altoTerminal - alto -1; 
            }
            m_x = 1;
        }
  
    }


}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Asteroide::draw(int altoTerminal,int anchoTerminal){

    if(direccion == 'y'){

        mvaddch(m_y, m_x + 2, '^');

        if(m_y + 1 < altoTerminal - 2){
            mvaddch(m_y + 1, m_x + 1 , '^');
            mvaddch(m_y + 1, m_x + 2, '^');
            mvaddch(m_y + 1, m_x + 3, '^');
        }
        
        if(m_y + 2 < altoTerminal - 2){
            mvaddch(m_y + 2, m_x, '(');
            mvaddch(m_y + 2, m_x + 1, ' ');
            mvaddch(m_y + 2, m_x + 2, ' ');
            mvaddch(m_y + 2, m_x + 3, ' ');
            mvaddch(m_y + 2, m_x + 4, ')');
        }

        
        if(m_y + 3 < altoTerminal - 2){  
            mvaddch(m_y + 3, m_x + 1, '*');
            mvaddch(m_y + 3, m_x + 2, '*');
            mvaddch(m_y + 3, m_x + 3, '*'); 
        }
            
        
    }else{
        mvaddch(m_y, m_x + 1, '#');
        mvaddch(m_y, m_x + 2, '-');
        mvaddch(m_y, m_x + 3, ACS_RARROW);
        mvaddch(m_y, m_x + 4, ' ');

        mvaddch(m_y + 1, m_x, '@');
        mvaddch(m_y + 1, m_x + 1, '#');
        mvaddch(m_y + 1, m_x + 2, '#');
        mvaddch(m_y + 1, m_x + 3, ACS_RARROW);
        mvaddch(m_y + 1, m_x + 4, ACS_RARROW);
   
        mvaddch(m_y + 2, m_x + 1, '#');
        mvaddch(m_y + 2, m_x + 2, '-');
        mvaddch(m_y + 2, m_x + 3, ACS_RARROW);
        mvaddch(m_y + 2, m_x + 4, ' ');
        
    }
   

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Asteroide :: setX(int x) {m_x = x;}
void Asteroide :: setY(int y) {m_y = y;}
int Asteroide :: getY(){return m_y;}
int Asteroide :: getX(){return m_x;}
int Asteroide :: getAlto(){return alto;}
int Asteroide :: getAncho(){return ancho;}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Asteroide :: colision(Aventurere &rAventurere){
    
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
            
        if(direccion == 'y'){
            setY(0);
        }else{
            setX(0);
        }
        return true;
    }
 
    return false;
}