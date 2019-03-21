#include <iostream>
#include "Ficha.cpp"
using namespace std;

class Jugador
{
    private:
        string nombre;
        Ficha ficha;
        string jugadorNum;

    public:
    	Jugador(){}
    	Jugador(string n, Ficha f, string j){
    		this->nombre = n;
    		this->ficha = f;
    		this->jugadorNum = j;
		}
		
		//Setters
        void setNombre(string x){ this->nombre = x; }
        void setFicha(Ficha x){ this->ficha = x; }
        void setJugadorNum(string x){ this->jugadorNum = x; }

		//Getters
        string getNombre(){ return this->nombre; }
        string getJugadorNum(){ return this->jugadorNum; }
        Ficha getFicha() { return this->ficha; }
};
