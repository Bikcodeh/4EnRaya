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
	tab.dibujarTablero();
	mostrarGanador();

    return 0;
}

//Funcion la cual se encarga de pintar  el titulo que aparece encima del tablero
void pintarTitulo()
{
	gotoxy(63, 2);
	cout << "----------------- CUATRO EN RAYA -------------------";
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
}

//Funcion que se encarga de pintar en pantalla en posicion X, Y el elemento a imprimir
void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

//Funcion para pedir los nombres de los jugadores, luego se llamara a tirarDado 
//Para determinar cual usuario empezara de primero
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
	//Despues de decidir quien empezara de primero, se da el mensaje de bienvenida y empieza el juego

	cout << endl << endl << "Bienvenido al Cuatro en raya, empecemos! " << endl << endl << endl;
	pausaLimpiar();
}

//Funcion encargada de pedir la respuesta de la ecuacion para posteriormente
//Colocar la ficha en el tablero
void seleccionarColumna()
{
	int columna;

	cout << "Turno del jugador: " << tab.getJugadorActual().getNombre() << endl;
	cout << "Ficha del jugador: " << tab.getJugadorActual().getFicha().getSimbolo() << endl << endl;
	cout << "Ingrese la respuesta de la ecuacion: ";
	cin >> columna;

	//Si la respuesta dada, no abarca una columna valida, el usuario perdera el turno y se le indicara el error
	if(columna > 6 || columna <= 0){

		cout << "Respuesta incorrecta, pierdes el turno" << endl << endl;
		
		if(tab.getJugadorActual().getJugadorNum() == j1.getJugadorNum())
        	tab.setJugadorActual(j2);
		else
			tab.setJugadorActual(j1);
			
			
		pausaLimpiar();
		pintarTitulo();

	}else{
		//Si la respeusta si esta en el rango, se procede a colocar la ficha en el tablero
        colocarFicha(columna);
		tab.setColumnaAuxiliar(columna);
	}
}

//Funcion que se encarga de colocar la ficha en el tablero y a su vez, se verifica si hay un ganador
//Y tambien de paso se asigna el turno al jugador siguiente
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

//Funcion que se encarga de pausar la pantalla y despues limpia la pantalla
void pausaLimpiar()
{
	system("pause");
	system("cls");
}

//Funcion que se encarga de buscar si hay un ganador
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

//Funcion que pinta el cuadro en el cual se muestra en nombre de la persona ganadora
void mostrarGanador()
{
	gotoxy(72, 21);
	cout << "G    A    M    E       O    V    E    R";
	for(int i = 0; i < 52; i++ )
	{
        gotoxy(i + 65, 19);
        cout << "_";
        cout << endl << endl;
	}

	for(int i = 20; i <= 24; i++ )
	{

	    gotoxy(64, i);
	    cout << "|";
	    cout << endl << endl;
    }


    gotoxy(78, 23);
    cout << "FELICIDADES "<< tab.getJugadorActual().getNombre()<<", HAS GANADO";

    for(int i = 20; i <= 24; i++ )
	{

	    gotoxy(117, i);
	    cout << "|";
	    cout << endl << endl;
    }

	for(int i = 0; i <52; i++ ){

        gotoxy(i + 65, 24);
        cout << "_";
        cout << endl << endl;
    }

     juegoNuevo();


}

//Funcion que pinta el cuadro que dice "Hasta luego" cuando el usuario decide terminar la ejecucion del juego
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

//Funcion la cual se encarga de preguntar al usuario si desea jugar una partida nueva
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

//Funcion la cual contiene los 6 numeros que se pintan, simulando los numeros de un dado
void pintarDados(int numero)
{
    switch(numero)
    {
        case 1:
            gotoxy(42, 6);
            cout << "X";
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

//Funcion la cual se encarga de hacer el efecto de los numeros del dado cambiando
//Y a su vez, generara y retornara un numero aleatorio del 1 al 6
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

//Funcion la cual se encarga de pedirle al usuario que tire el dado
//Y posteriormete decide que usuario empezara de primero
//O en caso de empate de numero, se volvera a pedir que tire el dado
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
