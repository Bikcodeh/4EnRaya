#include <iostream>
#include "Ficha.cpp"
using namespace std;

class Jugador
{
    private:
        string nombre;
        Ficha ficha;

    public:
        void setNombre(string x){ this->nombre = x; }
        void setFicha(Ficha x){ this->ficha = x; }

        string getNombre(){ return this->nombre; }
        Ficha getFicha() { return this->ficha; }
};
