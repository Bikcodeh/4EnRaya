#include <iostream>

using namespace std;

class Ficha
{
    private:
        bool estado;
        string simbolo;

    public:
        Ficha(){}
        Ficha( string simbolo,bool estado)
        {
            this->simbolo = simbolo;
            this->estado = estado;
        }

		//Setters
        void setEstado(bool x){ this->estado = x; }
        void setSimbolo(string x ) { this->simbolo = x; }

		//Getters
        bool getEstado(){ return this->estado; }
        string getSimbolo() { return this->simbolo; }
};
