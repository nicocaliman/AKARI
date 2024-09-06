//tablero.cpp
#include "tablero.h"

//funciones privadas
void setFilas(tTablero& tab, int f);	//modifica numfilas del tablero
void setColumnas(tTablero& tab, int c);	//modifica numcolumnas del tablero

//implementacion
void inicializa(tTablero& tab, int fil, int col, tCelda inicial)
{
	//crear un tablero con fil filas y col columnas
	setFilas(tab, fil);
	setColumnas(tab, col);

	//inicializar las casillas con el valor inicial ( NULA, VACIA, FICHA)
	for (int i = 0; i < numFilas(tab); i++)
	{
		for (int j = 0; j < numColumnas(tab); j++)
		{
			setCelda(tab, i, j, inicial);
		}
	}
}

void cargarTablero(tTablero& tab, istream& entrada)
{
	int tipo;

	//numero de filas & columnas del tablero
	entrada >> tab.numFilas >> tab.numColumnas;

	//leer valor( 0: NULA, 1: VACIA, 2: FICHA) de las celdas del tablero
	for (int i = 0; i < numFilas(tab); i++)
	{
		for (int j = 0; j < numColumnas(tab); j++)
		{
			entrada >> tipo;
			setCelda(tab, i, j, (tCelda)tipo);
		}
	}
}

int numFilas(tTablero const& tab)
{
	//numero de filas del tablero
	return tab.numFilas;
}

int numColumnas(tTablero const& tab)
{
	//numero de columnas del tablero
	return tab.numColumnas;
}

bool correcta(tTablero const& tab, int f, int c)
{
	//true si la posicion dada (f, c) es una posicion valida dentro del tablero
	return (f >= 0 && f < tab.numFilas) && (c >= 0 && c < tab.numColumnas);
}

tCelda getCelda(tTablero const& tab, int f, int c)
{
	//contenido de la posicion(f,c): NULA, VACIA, FICHA
	return tab.celdas[f][c];
}

void setCelda(tTablero& tab, int f, int c, tCelda valor)
{
	//asignar el valor ( NULA, VACIA, FICHA) a la posicion (f, c)
	tab.celdas[f][c] = valor;
}

void setFilas(tTablero& tab, int f)
{
	//modificar filas del tablero
	tab.numFilas = f;
}

void setColumnas(tTablero& tab, int c)
{
	//modificar columnas del tablero
	tab.numColumnas = c;
}