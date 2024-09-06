/*
*	FACULTAD DE INFORMATICA UCM
* 
*	Nicolae Gabriel Caliman y Iulian Nicolae Marian 
* 
*	1º A
* 
*	Version 1 
*/

#include <iostream>
#include <fstream>
#include "juego.h"
#include <iomanip>
#include "colores.h"
using namespace std;

int main()
{
	system("cls");	//borrar consola

	ifstream archivo;
	tJuego senku;
	int fila = -1, columna = -1, pasos = 0;
	char seguir = '-';

	do
	{
		//apertura archivo
		archivo.open("tablero.txt");

		//comprobacion apertura
		if (archivo.is_open())
		{
			//cargar juego
			cargarJuego(senku, archivo);

			cout << setw(20) << "Numero de pasos: ";
			cin >> pasos;

			//generacion aleatoria del tablero
			genera(senku, pasos);

			//mostrar tablero
			mostrar(senku);

			do
			{
				//ficha seleccionada por el usuario
				cout << "\n";
				cout << setw(42) << "Selecciona una FICHA (fila y columna): ";
				cin >> fila >> columna;
				cout << "\n";

				//comprobar posicion
				if (posicionValida(senku, fila - 1, columna - 1))
				{
					//inicializar movimiento
					tMovimiento mov = inicializaMov(fila - 1, columna - 1);

					//posibles movimientos
					posiblesMovimientos(senku, mov);

					//jugar
					jugar(senku, mov);

					//mostrar tablero
					mostrar(senku);
				}

				else
					cout << setw(28) << "ERROR: No es una ficha." << endl;	//mensaje de error

			} while (estado(senku) == JUGANDO);

			if (estado(senku) == GANADOR)
			{
				cout << endl;
				cout << RED << setw(34) << "!! HAS GANADO !!" << RESET << endl;
			}

			else if (estado(senku) == BLOQUEO)
			{
				cout << endl;
				cout << RED << setw(44) << "NO PUEDES MOVER FICHAS. HAS PERDIDO" << RESET << endl;
			}

			cout << "\n";
			cout << setw(40) << "Quieres volver a jugar [S/N]? ";
			cin >> seguir;
			cout << "\n";

			//cierre archivo
			archivo.close();	
		}

		else
			cout << "ERROR: El archivo no se pudo abrir.\n";	//mensaje de error
	}
	while (seguir == 'S' || seguir == 's');

	//el juego termina
	cout << "\n";
	cout << GREEN << setw(30) << "GAME OVER" << RESET << endl;

	return 0;
}