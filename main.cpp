#include <iostream>
#include "Tablero.cpp"

using namespace std;

void turno(){
    Ficha ficha1 = Ficha("*", true);
    Ficha ficha2 = Ficha("-", true);

    Jugador j1 = Jugador("Victor", ficha1);
    Jugador j2 = Jugador("Victor", ficha2);


}

int main()
{

    Tablero tab = Tablero();
    tab.dibujarTablero();
    tab.pintarFicha(2, 3, j1);
    return 0;
}
