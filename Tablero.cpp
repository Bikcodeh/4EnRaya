#include <iostream>
#include<stdlib.h>
#include <windows.h>
#include "Jugador.cpp"

using namespace std;

class Tablero
{
    private:
    	Jugador jugadorActual;
        Ficha tableroFichas[6][6];
        bool enJuego;
        int fila;
        int columnaAuxiliar;

    public:
        Tablero()
        {
        	this->fila = 6;
        	
        	//Inicializamos cada posicion con la O y en true
        	//True significa que esta disponible para el usuario colocar la ficha
        	//False significa que ya no esta disponible
        	
            for(int i = 0; i < 6; i++){
                for(int j = 0; j < 6; j++){
                    this->tableroFichas[i][j] = Ficha(" O ", true);
                }
            }
        }
		
		//Setters
	    void setEnJuego(bool x){ this->enJuego = x; }
	    void setJugadorActual(Jugador x){ this->jugadorActual = x; }
	    void setColumnaAuxiliar(int x) { this->columnaAuxiliar = x; }

		//Getters
	    bool getEnJuego(){ return this->enJuego; }
	    Jugador getJugadorActual(){ return this->jugadorActual; }
	    int getColumnaAuxiliar() { return this->columnaAuxiliar; }
	    
		
		//Funcion para colocar elementos en posicion X, Y
	    void gotoxy(int x, int y)
	    {
	        HANDLE hCon;
	        hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	        COORD dwPos;
	        dwPos.X = x;
	        dwPos.Y = y;

	        SetConsoleCursorPosition(hCon, dwPos);
	    }

		//Funcion la cual se encarga de dibujar toooodooo el tablero junto con las ecuaciones 
	    void dibujarTablero()
	    {
	    	
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			
			int contY = 7;
			int contX = 32;

	        for(int i = 0; i < 112; i++ ){

	            gotoxy(i + 33, 5);
	            cout << "_";
	            cout << endl << endl;
	        }

	        gotoxy(27, 7);
	        cout << "X = 1";

	        gotoxy(27, 9);
	        cout << "X = 2";

	        gotoxy(27, 11);
	        cout << "X = 3";

	        gotoxy(27, 13);
	        cout << "X = 4";

	        gotoxy(27, 15);
	        cout << "X = 5";
	        
	        gotoxy(27, 17);
	        cout << "X = 6";

			//1
	        gotoxy(40, 4);
	        cout << "X^2-0";

			//2
	        gotoxy(57, 4);
	        cout << "2X^2-3X";

			//3
	        gotoxy(77, 4);
	        cout << "X^2-6";

			//4
	        gotoxy(94, 4);
	        cout << "2X^2-5X-8";

			//5
	        gotoxy(114, 4);
	        cout << "X^2+2X-30";

			//6
	        gotoxy(133, 4);
	        cout << "6X^2-35x";


	        for(int i = 0; i < 6; i++)
	        {
	        	gotoxy(contX, contY);
	        	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	            for(int j = 0; j < 6; j++)
	            {
	            	if(this->tableroFichas[i][j].getSimbolo() == " * "){
	            		
	            		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_GREEN));
	            		cout <<" |      " <<this->tableroFichas[i][j].getSimbolo() << "      | ";
	            		
					}else if(this->tableroFichas[i][j].getSimbolo() == " - "){
						
						SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN));
						cout <<" |      " <<this->tableroFichas[i][j].getSimbolo() << "      | ";
						
					}else{
						
						SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
						cout <<" |      " <<this->tableroFichas[i][j].getSimbolo() << "      | ";
						
					}
	            }
	            contY += 2;
	            cout << endl << endl << endl << endl;
	            SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	        }

	        for(int i = 0; i < 112; i++ ){

	            gotoxy(i + 33, 18);
	            cout << "_";
	            cout << endl << endl;
	        }
	    }

		//Funcion la cual se encarga de pintar la ficha en la posicion dada
		//Si la pudo colocar en el tablero, retornara true
		//Si no la pudo colocar, retornara false
	    bool pintarFicha(int columna, Jugador jugador)
	    {
			bool agregoFicha = false;

			if(this->columnaAuxiliar != columna){
				this->fila = 6;
			}

			if(this->tableroFichas[0][columna - 1].getEstado()){

				while(this->fila > 0 && agregoFicha==false){
					if(validarPosicion(columna)){
						
                        this->tableroFichas[this->fila - 1][columna - 1].setSimbolo(jugador.getFicha().getSimbolo());
						this->tableroFichas[this->fila - 1][columna - 1].setEstado(false);
						agregoFicha = true;
					}else{
						this->fila -= 1;
					}
				}
			}else{
				cout << endl << "Columna no disponible" << endl << endl;
				pausaLimpiarPantalla();
			}

			return agregoFicha;
		}

		//Funcion la cual se encarga de validar si en la posicion que el jugador quiere
		//Colocar la ficha es valida o no
		//Si esta disponible para pintar la ficha, retornara true
		//Si no esta disponible, retornara false
		bool validarPosicion(int col)
		{
			if(this->tableroFichas[this->fila - 1][col - 1].getEstado())
				return true;
			else
				return false;
		}
	
		//Funcion la cual se encarga de validar si el tablero ya esta lleno
		//En caso de que haya al menos 1 solo espacio disponible, retornara false
		//Si el tablero ya esta lleno, retornara true
		bool tableroLleno()
		{
			//Si la tabla ya esta llena, retornara true
			bool estado = true;

			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++)
				{
					//Validamos que haya al menos un espacio disponible, si lo hay, entonces estado es false y rompo el ciclo
					if(this->tableroFichas[i][j].getEstado()){
						estado = false;
						break;
					}
				}
			}
			return estado;
		}

		//Funcion para pausar y luego limpiar la pantalla
		void pausaLimpiarPantalla()
		{
			system("pause");
			system("cls");
		}

		//Funcion la cual se encarga de verificar que haya un ganador
		bool verificarGanador(){
            //Verificar horizontal
            for(int i=0;i<6;i++){
                for(int j=0;j<6;j++){
                    string  simboloFichaActual = tableroFichas[i][j].getSimbolo();

					//Verificar horizontal
                    if(!tableroFichas[i][j].getEstado() && j <= 2 &&
                       simboloFichaActual==tableroFichas[i][j+1].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i][j+2].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i][j+3].getSimbolo())
                    {
                        return true;
                    }

					//Verificar vertical
					if(!tableroFichas[i][j].getEstado() && i <= 2 &&
					   simboloFichaActual==tableroFichas[i+1][j].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+2][j].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+3][j].getSimbolo())
                    {
                        return true;
                    }

					//Verificar diagonal ( arriba izquierdo y abajo derecho)
					if(!tableroFichas[i][j].getEstado() && i <= 2 && j <= 2  &&
                       simboloFichaActual==tableroFichas[i+1][j+1].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+2][j+2].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+3][j+3].getSimbolo())
                    {
                        return true;
                    }

		            //Verificar diagonal ( arriba derecho y abajo izquierdo )
					if(!tableroFichas[i][j].getEstado() && i <= 2 && j >= 2  &&
                       simboloFichaActual==tableroFichas[i+1][j-1].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+2][j-2].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+3][j-3].getSimbolo())
                    {
                        return true;
                    }
                }
            }

            return false;
        }
        	
        //Funcion la cual se encarga de reiniciar el tablero para volver a empezar a jugar
        void reiniciarTablero()
        {
        	for(int i = 0; i < 6; i++){
                for(int j = 0; j < 6; j++){
                    this->tableroFichas[i][j] = Ficha(" O ", true);
                }
            }
		}	
};
