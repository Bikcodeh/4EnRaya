#include <iostream>
#include "Tablero.cpp"
#include<time.h>

using namespace std;

//Definicion de funciones
void colocarFicha(int co);
void seleccionarColumna();
void pausaLimpiar();
void verificarGanador();
void pintarTitulo();
void gotoxy(int x, int y);
void nombresJugadores();
void mostrarGanador();
void terminar();
void juegoNuevo();
void pintarDados(int numero);
int generarNumeroAleatorio();
void tirarDado();

//Variables generales
string nombreJugador;

//Establecemos las fichas con las que se jugara
Ficha ficha1 = Ficha(" * ", true);
Ficha ficha2 = Ficha(" - ", true);

//Creamos a los jugadores
Jugador j1;
Jugador j2;

//Iniciamos el tablero
Tablero tab = Tablero();

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("CUATRO EN RAYA");
	
	while(true){
        nombresJugadores();

        tab.dibujarTablero();
        tab.setEnJuego(true);

        while(tab.getEnJuego())
        {
            pintarTitulo();
            if(tab.tableroLleno()){
                cout << endl << endl << "JUEGO TERMINADO" << endl << endl;
                pausaLimpiar();
                tab.setEnJuego(false);
            }else{
                seleccionarColumna();
                tab.dibujarTablero();
            }
        }

	}

    return 0;
}

void pintarTitulo()
{
	gotoxy(33, 2);
	cout << "----------------- CUATRO EN RAYA -------------------";
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
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

void nombresJugadores()
{
	cout << endl << endl;
	cout << " --------- Nombres de los jugadores ---------" << endl << endl;
	cout << "Ingresa tu nombre jugador 1: ";
	cin >> nombreJugador;

	j1 = Jugador(nombreJugador, ficha1, "1");

	cout << "Ingresa tu nombre jugador 2: ";
	cin >> nombreJugador;
	j2 = Jugador(nombreJugador, ficha2, "2");

	tirarDado();

	cout << endl << endl << "Bienvenido al Cuatro en raya, empecemos! " << endl << endl << endl;
	pausaLimpiar();
}

void seleccionarColumna()
{
	int columna;

	do{
		cout << "Turno del jugador: " << tab.getJugadorActual().getNombre() << endl;
		cout << "Ficha del jugador: " << tab.getJugadorActual().getFicha().getSimbolo() << endl << endl;
		cout << "Ingrese el numero de la columna: ";
		cin >> columna;

		if(columna > 6){

			cout << "Ingresa un numero de columna valido." << endl;
			pausaLimpiar();
			pintarTitulo();
			tab.dibujarTablero();

		}else{
            break;
		}
	}while(true);

	colocarFicha(columna);
	tab.setColumnaAuxiliar(columna);
}

void colocarFicha(int co)
{
	//Se mira si el que esta lanzando el turno es el jugador 1
	if(tab.getJugadorActual().getJugadorNum() == j1.getJugadorNum()){
		//tab.pintarFicha() retorna true si la ficha se coloco correctamente
		//Si entra al if entonces se procede a mirar si gano o no
		if(tab.pintarFicha(co, j1)) verificarGanador();
		//Si no ha ganado, entonces se establece que el siguiente en tirar sera el jugador 2
        tab.setJugadorActual(j2);
	}else{
		//Si entra al else, es porque esta tirando el jugador2
		//tab.pintarFicha() retorna true si la ficha se coloco correctamente
		//Si entra al if entonces se procede a mirar si gano o no
		if(tab.pintarFicha(co, j2)) verificarGanador();
		//Si no ha ganado, entonces se establece que el siguiente en tirar sera el jugador 1
		tab.setJugadorActual(j1);
	}

}

void pausaLimpiar()
{
	system("pause");
	system("cls");
}

void verificarGanador(){

	//Si gana
    if(tab.verificarGanador()){
    	//Entonces redibujamos el tablero para que alcance a pintar la ultima ficha
    	//Llamamos a la funcion para mostrar el nombre del ganador
    	system("cls");
    	tab.dibujarTablero();
        mostrarGanador();
        //Rompemos el ciclo para terminar el juego
        tab.setEnJuego(false);

    }
}

void mostrarGanador()
{
	gotoxy(40, 20);
	cout << "G    A    M    E       O    V    E    R";
	for(int i = 0; i < 52; i++ )
	{
        gotoxy(i + 33, 18);
        cout << "_";
        cout << endl << endl;
	}

	for(int i = 19; i <= 23; i++ )
	{

	    gotoxy(32, i);
	    cout << "|";
	    cout << endl << endl;
    }


    gotoxy(44, 22);
    cout << "FELICIDADES "<< tab.getJugadorActual().getNombre()<<", HAS GANADO";

    for(int i = 19; i <= 23; i++ )
	{

	    gotoxy(85, i);
	    cout << "|";
	    cout << endl << endl;
    }

	for(int i = 0; i <52; i++ ){

        gotoxy(i + 33, 23);
        cout << "_";
        cout << endl << endl;
    }

     juegoNuevo();


}

void terminar()
{
	system("cls");
	for(int i = 0; i < 52; i++ )
	{
        gotoxy(i + 33, 5);
        cout << "_";
        cout << endl << endl;
	}

	for(int i = 6; i <= 10; i++ )
	{

	    gotoxy(32, i);
	    cout << "|";
	    cout << endl << endl;
    }

    gotoxy(53, 8);
    cout << "HASTA PRONTO!";

    for(int i = 6; i <= 10; i++ )
	{

	    gotoxy(85, i);
	    cout << "|";
	    cout << endl << endl;
    }

	for(int i = 0; i <52; i++ ){

        gotoxy(i + 33, 10);
        cout << "_";
        cout << endl << endl;
    }

}

void juegoNuevo()
{
	int opcion;
	pausaLimpiar();
	cout << endl << endl << endl;
    gotoxy(40, 12);
    cout << "Deseas jugar de nuevo? (Ingrese numero)";
    gotoxy(40, 14);
    cout << "1). Si";
    gotoxy(40, 15);
	cout << "2). No / Terminar juego";
    gotoxy(40, 17);
    cout << "Opcion: ";
    cin >> opcion;

    if(opcion == 1){
    	system("cls");
    	tab.reiniciarTablero();
        main();
	}else{
		terminar();
		exit(0);
	}
}

void pintarDados(int numero)
{
    switch(numero)
    {
        case 1:
            gotoxy(40, 4);
            cout << "X";
            cout << endl << endl << endl;
        break;
        case 2:
            gotoxy(40, 4);
            cout << "X";
            gotoxy(45, 8);
            cout << "X";
        break;
        case 3:
            gotoxy(40, 4);
            cout << "X";
            gotoxy(43, 6);
            cout << "X";
            gotoxy(45, 8);
            cout << "X";
        break;
        case 4:
            gotoxy(40, 4);
            cout << "X";
            gotoxy(44, 4);
            cout << "X";
            gotoxy(40, 8);
            cout << "X";
            gotoxy(44, 8);
            cout << "X";
        break;
        case 5:
            gotoxy(40, 4);
            cout << "X";
            gotoxy(44, 4);
            cout << "X";
            gotoxy(42, 6);
            cout << "X";
            gotoxy(40, 8);
            cout << "X";
            gotoxy(44, 8);
            cout << "X";
        break;
        case 6:
            gotoxy(40, 4);
            cout << "X";
            gotoxy(40, 6);
            cout << "X";
            gotoxy(40, 8);
            cout << "X";
            gotoxy(44, 4);
            cout << "X";
            gotoxy(44, 6);
            cout << "X";
            gotoxy(44, 8);
            cout << "X";
        break;
    }
}

int generarNumeroAleatorio()
{
    srand(time(NULL));
    int numAleatorio;

    for(int i = 1; i <= 20; i++)
    {
        numAleatorio = 1 + rand() % (7 - 1);

        pintarDados(numAleatorio);
        if(i == 20)
            Sleep(1000);
        else
            Sleep(100);

        system("cls");
    }
    return numAleatorio;
}

void tirarDado()
{
	system("cls");
    string opcion;
    int dado1, dado2;
    
    do{
    	cout << endl << endl;
	    cout << "Jugador " << j1.getNombre() << " ingrese P para tirar el dado." << endl;
	    cout << "Ingrese: ";
	    cin >> opcion;
	
	    if(opcion == "p" || opcion == "P")
	    {
	        dado1 = generarNumeroAleatorio();
	    }
	
	    cout << "El jugador " << j1.getNombre() << " tiene el numero: " << dado1 << endl << endl;
	
	    pausaLimpiar();
	
	    cout << endl << endl;
	    cout << "Jugador " << j2.getNombre() << " ingrese P para tirar el dado." << endl;
		cout << "Ingrese: ";
	    cin >> opcion;
	
	
	    if(opcion == "p" || opcion == "P")
	    {
	        dado2 = generarNumeroAleatorio();
	    }
	    cout << "El jugador " << j1.getNombre() << " tiene el numero: " << dado1 << endl << endl;
	    cout << "El jugador " << j2.getNombre() <<  " tiene el numero: " << dado2 << endl << endl << endl;
	    
	    if(dado1 > dado2){
	    	cout << "Empezara el jugador numero 1, " << j1.getNombre() << endl << endl;
	    	tab.setJugadorActual(j1);
	    	break;
		}else if(dado1 == dado2){
			
			cout << endl << " --- ---- -- DADOS IGUALES -- --- ---" << endl << endl << endl;
			pausaLimpiar();
		}else{
			tab.setJugadorActual(j2);
			cout << "Empezara el jugador numero 2, " << j2.getNombre() << endl << endl;
	    	break;
		}
	    	
	    	
	}while(true);

    
}
