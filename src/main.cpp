//Sandes Caccia Renato Felice
#include <iostream>
#include <ncurses.h>
#include "aventurere.h"
#include "pista.h"
#include "pregunton.h" 
#include "asteroides.h" 
#include <ctime>
#include <string>
#include <vector>

using namespace std;
//---------------------------------------------------------------------------------------------------------------------

const int ANCHO = 120;
const int ALTO = 40;
const int DELAY = 30;

const int PAR_FONDO = 1;
const int PAR_CABECERA = 2;
const int PAR_MENU = 3;
const int PAR_COLORMENU = 4;
const int PAR_PISTA = 5;

const int cantidadAsteroides = 6;
const int cantidadPreguntas = 7;

//---------------------------------------------------------------------------------------------------------------------

bool game_over;
int puntaje;
bool salir;
bool jugando;
bool enMenu;
bool preguntar;

string textSalida = "Definitivamente has salido.";

vector<Asteroide> Asteroidesx;
vector<Asteroide> Asteroidesy;


Aventurere miAventurere;
Pista miPista;
Pregunton miPreguntando;
//---------------------------------------------------------------------------------------------------------------------
void menu();
void setup();
void input();
void update();
void draw();
void gameover();
void mostrarInstrucciones();
void juego();
void imprimirCabecera();
void colorBox();
void colorPista();

//---------------------------------------------------------------------------------------------------------------------

int main()
{
	initscr();
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	
  	if (LINES < ALTO || COLS > ANCHO)
	{
		endwin();
		printf("La terminal tiene que tener como mínimo %dx%d\n\n", ANCHO, ALTO);
		exit(1);
	}   
  
	
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Tu terminal no soporta color\n\n");
		exit(1);
	} 

	start_color();

	setup();

	salir = false;
	jugando = false;
	enMenu = true;
	preguntar = false;			

	while(!salir){
		if(jugando){
			while(!game_over){
				juego();
			}
			gameover();
		}else{
			if(enMenu){
				menu();
			}
			if(!enMenu && !jugando){
				mostrarInstrucciones();
			}
		}
	
	}   

	endwin();

	cout << endl;
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------
void setup()
{

	game_over = false;
	puntaje = 0;

	Asteroidesx.clear();
	Asteroidesy.clear();

	for (int i = 0; i < cantidadAsteroides; i++){
		Asteroidesx.push_back(Asteroide(rand() % ANCHO + 1, 1,'x'));
		Asteroidesy.push_back(Asteroide(39, rand() % ALTO + 1,'y'));
	}
	
	

	miAventurere.setup();
	miPista.setup();
	miPista.mover(ANCHO,ALTO);
}

//---------------------------------------------------------------------------------------------------------------------

void input()
{
	int tecla = getch();

		if(!preguntar){
			switch (tecla){
				case KEY_UP:
				if(miAventurere.getY() > 1) miAventurere.setY(miAventurere.getY() - 1.0f);
				break;

				case KEY_DOWN:
				if(miAventurere.getY() < ALTO - miAventurere.getAlto() - 1) miAventurere.setY(miAventurere.getY() + 1.0f);
				break;

				case KEY_LEFT:
				if(miAventurere.getX() > 1) miAventurere.setX (miAventurere.getX() - 1.0f);
				break;

				case KEY_RIGHT:
				if(miAventurere.getX() < ANCHO - miAventurere.getAncho() -1 ) miAventurere.setX (miAventurere.getX() + 1.0f);
				break;

				case 27:
				game_over = true;
				break;

				default:
				break;
			}
		}else{
			switch (tecla){
				case '\n':
					preguntar = false;
				break;

				default:
				break;
			}
		}
}
//---------------------------------------------------------------------------------------------------------------------

void update()
{
	for (int i = 0; i < Asteroidesx.size(); i++){
		Asteroidesx[i].update(ANCHO,ALTO);
		Asteroidesy[i].update(ANCHO,ALTO);
	}
	
	if(miPista.colision(miAventurere)){
		preguntar = true;
		miPista.mover(ANCHO,ALTO);
		puntaje += 5;
	}

	for (int i = 0; i < Asteroidesx.size(); i++){
		if(Asteroidesx[i].colision(miAventurere)){
			if(!miAventurere.pierdeVida()){
				game_over = true;
				return;
			}
		}
		if(Asteroidesy[i].colision(miAventurere)){
			if(!miAventurere.pierdeVida()){
				game_over = true;
				return;
			}
		}	
	} 
	

}

//---------------------------------------------------------------------------------------------------------------------

void draw()
{

	erase();


	colorBox();

	imprimirCabecera();

	if(!preguntar){
		miPista.draw();
		miAventurere.draw();
		for (int i = 0; i < Asteroidesx.size(); i++){
			Asteroidesx[i].draw(ALTO,ANCHO);
			Asteroidesy[i].draw(ALTO,ANCHO);
		}   
	}else{
		miPreguntando.draw(ALTO,ANCHO);
	}

	
	refresh();
	delay_output(DELAY);
}

//---------------------------------------------------------------------------------------------------------------------

void gameover()
{
	refresh();
	
	for (int y = 10; y < 16; y++)
		mvhline(y, 40, ' ', 40);
	
	mvaddch(9, 39, ACS_ULCORNER);
	mvaddch(9, 80, ACS_URCORNER);
	mvaddch(16, 39, ACS_LLCORNER);
	mvaddch(16, 80, ACS_LRCORNER);
	
	mvhline(9, 40, ACS_HLINE, 40);
	mvhline(16, 40, ACS_HLINE, 40);

	mvvline(10, 39, ACS_VLINE, 6);
	mvvline(10, 80, ACS_VLINE, 6);

	mvprintw(12, 55, "GAME OVER");
	mvprintw(13, 50, "VOLVER A JUGAR? (S/N)");

	
	int opcion = getch();

	if (opcion == 's' || opcion == 'S')
	{
		game_over = false;
		setup(); 
		
	}
	else if (opcion == 'n' || opcion == 'N')
	{
		printf("Definitivamente has salido.");
		salir = true;
	}


}

//---------------------------------------------------------------------------------------------------------------------
void menu()
{
	erase();

	init_pair(PAR_MENU, COLOR_CYAN, COLOR_BLUE);

   	attron(COLOR_PAIR(PAR_MENU));

	for (int y = 0; y < ALTO ; y++)
	{
		mvhline(y, 0, ' ', ANCHO );
	}	

    attroff(COLOR_PAIR(PAR_MENU));

		init_pair(PAR_COLORMENU, COLOR_WHITE, COLOR_BLUE);

   	attron(COLOR_PAIR(PAR_COLORMENU));

	mvprintw(5,4, "                  ,0XXXXXXXXXX0, oNNXXKXXKOd'      ;0XXXd.      cXXXKo.  .kNK;  .:xKNXXXXX0:                          ");
	mvprintw(6,3, "                   .,;;c0MM0c;;,. dMMK,  lKMMk.    '0MWNWNl.     lWMMMWx. '0MX:  oNMXl'.,:d:                           ");
	mvprintw(7,3, "                       .kMMx.     dMM0,  ;0MWx.   .xWW  XMKk;    lWMKONW0,,0MN:  oWMNOoc:,.                             ");
	mvprintw(8,3, "                       .kMMx.     dMMWK0KNWKl.    lNMO  oWMMO.   lWMk'cXMKkKMN:  .ckKNMMMWXk;                           ");
	mvprintw(9,3, "                       .kMMx.     dMMXolOWW0;    ;KMMXkk0WMMWd.  lWMk. ;KMMMMX:  .  .';:oKMM0'                          ");
	mvprintw(10,3,"                       .kMMx.     dMMO' .oXMNd. .OMWO    dXMMNc  lWMk.  'OWMMX: .dkl:,',c0MWd.                          ");
	mvprintw(11,3,"                       .o00o.     c00d.   ;k00d,c00d.     c000x. :00o.   .o00O, .ck0KKKKK0x:.                           ");
	mvprintw(12,3,"                        ..        ..       .......         ...   ..       ...     ......                               ");
	mvprintw(13,0,"    .:cc:.    .;cc,      ,cc,  ,cccccccc:.  'ccc;.   .:c:. .,ccccccccccc' .:c:.    .cc:.  .ccccccc:;.        ,ccc,     ");
	mvprintw(14,0,"    .xWMMWx.   .oWMK;    :XMNc .kMMNK0000O,  dMMMWk.  ;XMK, .l000XWMWX000l :NMN:    lWMX;  cNMWKOOKWWXo.     :XMMMX;    ");
	mvprintw(15,0,"    lNW  MNl    .kWMk.  .OMWd. .kMMk'.....   dMMWWW0; ;XMK,   ...cNMNc...  :NMN:    cWMX;  cNMX:  .xWMX;    '0MX NMO'   ");
	mvprintw(16,0,"   ;XMK  XMX;    ,0MWo .dWMO.  .kMMN0OOOOl.  dMMkoKMXc:KMK,      :NMN:     :NMN:    cWMX;  cNMNd;;l0MNd.   .xWW   WWx.  ");
	mvprintw(17,0,"  'OMWk  kWMO'    cNMX:cNMK;   .kMMKollll,   dMMd.;0MNKNMK,      :NMN:     :NMN:    lWMX;  cNMWXXWMMKc     lNMK   XMNl  ");
	mvprintw(18,0," .xWMWXKKXWMWd.   .dWMXXMNc    .kMMx.        dMMd  'kWMMMK,      :NMN:     ;XMWo    dWMK,  cNMXc.cKMNk'   ;XMWNKKXNWMK; ");
	mvprintw(19,0," lNMKc''''cKMNl    .OMMMWx.    .kMMXOkkkkx'  dMMd   .dNMMK,      :NMN:     .lXWNkddONWKc   cWMX;  .xNMXl.'0MWd'''',kWMO.");
	mvprintw(20,0,".:oo,      ;oo:.    'oool.     .:ooooooool.  ,oo;     ;ooc.      .lol.       .codxxdo:.    'ool.    ;ooo,;ooc.     .loo'");




	mvprintw(25,50, "1-Jugar"); 
	mvprintw(26,50, "2-Instrucciones"); 
	mvprintw(27,50, "3-Salir"); 

    attroff(COLOR_PAIR(PAR_COLORMENU));
	
	

	int caracter = getch();
	
	
	switch (caracter)
	{
		case '1':
			jugando = true;
		break;
		
		case '2':
			enMenu = false;
		break;
	 	
		case '3':
			salir = true;
			cout << textSalida;
		break;

		default:
		break;
	}
		 

}

//---------------------------------------------------------------------------------------------------------------------
void mostrarInstrucciones(){
			erase();

			init_pair(PAR_MENU, COLOR_WHITE, COLOR_BLUE);
			init_pair(PAR_PISTA, COLOR_RED, COLOR_BLUE);

   	attron(COLOR_PAIR(PAR_MENU));

	for (int y = 0; y < ALTO ; y++)
	{
		mvhline(y, 0, ' ', ANCHO );
	}	
			mvprintw(3,40,"Bienvenide a Trans Aventura!!!");
			mvprintw(6,15, "Es un juego en la cual verás la cantidad de violencias y situaciones que tenemos que vivir ");
			mvprintw(7,15,"constrantemente las personas personas trans, mostrandolo desde la experiencia y perspectiva ");
			mvprintw(8,15,"del credor del juego.");
			mvprintw(11,15,"Estas situaciones nombradas anteriormente, estan representadas metafóricamente a través de");
			mvprintw(12,15,"asteorides y naves aparecen en la pantalla las cuales si te tocan te hacen daño, pero a su vez "); 
			mvprintw(13,15,"va a ir apareciendo un diamante rojo el cual te dice una frase clave y te suma 5 puntos.");
			mvprintw(15,15,"De ante mano te informo que va a haber muchos obstaculos, quizás no es facil, pero te aseguro ");
			mvprintw(16,15, "que siendo quien sos, con orgullo y pasión, nada es tan imposible.");

			mvprintw(18,15, "Modo e intrucciones de juego:");
			mvprintw(19,14, "-Para transladarte sobre la pantalla utilizá las flechitas.");
			mvprintw(20,14, "-Tenes 3 vidas, cada vez que una nave/asteroide te toque perderás una vida.");
			
			mvprintw(25,40,"Presione enter para continuar...");
			mvprintw(30,78,"Créditos: Renato Felice Sandes Caccia ;)"); 
		
		 
		 	attroff(COLOR_PAIR(PAR_COLORMENU)); 

			int caracter = getch();
	
	
		switch (caracter)
		{
			case '\n':
				enMenu = true;
			break;
			

			default:
			break;
		}

			refresh();
			
}

//---------------------------------------------------------------------------------------------------------------------
void juego(){
	input();
	update();
	draw();
}
//---------------------------------------------------------------------------------------------------------------------	

void imprimirCabecera(){
	
	init_pair(PAR_FONDO, COLOR_WHITE, COLOR_BLACK);

   	attron(COLOR_PAIR(PAR_FONDO));

	box(stdscr, 0, 0);

	mvprintw(0, 100, "[ VIDAS:     ]");
	for (int i = 0; i < miAventurere.getVidas(); i++)
	{
		mvaddch(0, 109 + i, ACS_DIAMOND);
	}

	mvprintw(0, 5, "[ PUNTOS:     ]");
	mvprintw(0, 15, "%d",puntaje);
	
   
    attroff(COLOR_PAIR(PAR_FONDO));
	

}

//---------------------------------------------------------------------------------------------------------------------	
void colorBox(){
 
    init_pair(PAR_CABECERA, COLOR_BLACK, COLOR_BLACK);


	 attron(COLOR_PAIR(PAR_CABECERA));
	
	for (int y = 1; y < ALTO - 1; y++)
	{
		mvhline(y, 1, ' ', ANCHO - 2);
	}	

    attroff(COLOR_PAIR(PAR_CABECERA)); 

	
}

//---------------------------------------------------------------------------------------------------------------------	