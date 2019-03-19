#include <iostream>
#include<stdlib.h>
#include <windows.h>
#include "Jugador.cpp"

using namespace std;

class Tablero
{
    private:
        Ficha tableroFichas[7][7];

    public:
        Tablero()
        {
            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 7; j++){
                    this->tableroFichas[i][j] = Ficha();
                    this->tableroFichas[i][j].setEstado(false);
                    this->tableroFichas[i][j].setSimbolo(" O ");
                }
            }
        }

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

        for(int i = 0; i <61; i++ ){

            gotoxy(i + 1, 2);
            cout << "_";
            cout << endl << endl;
        }

        for(int i = 0; i < 7; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(!this->tableroFichas[i][j].getEstado())
                {
                    cout <<" | " <<this->tableroFichas[i][j].getSimbolo() << " | ";
                }
            }
            cout << endl << endl;
        }

        for(int i = 0; i <61; i++ ){

            gotoxy(i + 1, 17);
            cout << "_";
            cout << endl << endl;
        }
    }

    void pintarFicha(int fila, int columna, Jugador jugador)
    {
        this->tableroFichas[fila - 1][columna - 1].setSimbolo(jugador.getFicha().getSimbolo());
    }
};
