#include <iostream>
#include<stdlib.h>
#include <windows.h>
#include "Jugador.cpp"

using namespace std;

class Tablero
{
    private:
    	Jugador jugadorActual;
        Ficha tableroFichas[5][6];
        bool enJuego;
        int fila;
        int columnaAuxiliar;

    public:
        Tablero()
        {
        	this->fila = 5;
        	
        	//Inicializamos cada posicion con la 0 y en true
        	//True significa que esta disponible para el usuario colocar la ficha
        	//False significa que ya no esta disponible
        	
            for(int i = 0; i < 5; i++){
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

	    void dibujarTablero()
	    {
	    	
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			
			int contY = 7;
			int contX = 32;

	        for(int i = 0; i < 52; i++ ){

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

	        gotoxy(36, 4);
	        cout << "1";

	        gotoxy(45, 4);
	        cout << "2";

	        gotoxy(54, 4);
	        cout << "3";

	        gotoxy(63, 4);
	        cout << "4";

	        gotoxy(72, 4);
	        cout << "5";

	        gotoxy(81, 4);
	        cout << "6";


	        for(int i = 0; i < 5; i++)
	        {
	        	gotoxy(contX, contY);
	        	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	            for(int j = 0; j < 6; j++)
	            {
	            	if(this->tableroFichas[i][j].getSimbolo() == " * "){
	            		
	            		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_GREEN));
	            		cout <<" | " <<this->tableroFichas[i][j].getSimbolo() << " | ";
	            		
					}else if(this->tableroFichas[i][j].getSimbolo() == " - "){
						
						SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN));
						cout <<" | " <<this->tableroFichas[i][j].getSimbolo() << " | ";
						
					}else{
						
						SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
						cout <<" | " <<this->tableroFichas[i][j].getSimbolo() << " | ";
						
					}
	            }
	            contY += 2;
	            cout << endl << endl;
	            SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	        }

	        for(int i = 0; i <52; i++ ){

	            gotoxy(i + 33, 16);
	            cout << "_";
	            cout << endl << endl;
	        }
	    }

	    bool pintarFicha(int columna, Jugador jugador)
	    {
			bool agregoFicha = false;

			if(this->columnaAuxiliar != columna){
				this->fila = 5;
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

		bool validarPosicion(int col)
		{
			if(this->tableroFichas[this->fila - 1][col - 1].getEstado())
				return true;
			else
				return false;
		}

		bool tableroLleno()
		{
			//Si la tabla ya esta llena, retornara true
			bool estado = true;

			for(int i = 0; i < 5; i++)
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

		void pausaLimpiarPantalla()
		{
			system("pause");
			system("cls");
		}

		bool verificarGanador(){
            //Verificar horizontal
            for(int i=0;i<5;i++){
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
					if(!tableroFichas[i][j].getEstado() && i <= 1 &&
					   simboloFichaActual==tableroFichas[i+1][j].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+2][j].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+3][j].getSimbolo())
                    {
                        return true;
                    }

					//Verificar diagonal ( arriba izquierdo y abajo derecho)
					if(!tableroFichas[i][j].getEstado() && i <= 1 && j <= 2  &&
                       simboloFichaActual==tableroFichas[i+1][j+1].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+2][j+2].getSimbolo() &&
                       simboloFichaActual==tableroFichas[i+3][j+3].getSimbolo())
                    {
                        return true;
                    }

		            //Verificar diagonal ( arriba derecho y abajo izquierdo )
					if(!tableroFichas[i][j].getEstado() && i <= 1 && j >= 2  &&
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
        
        void reiniciarTablero()
        {
        	for(int i = 0; i < 5; i++){
                for(int j = 0; j < 6; j++){
                    this->tableroFichas[i][j] = Ficha(" O ", true);
                }
            }
		}	
};
