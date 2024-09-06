//tablero.h
#pragma once
#include <iostream>
using namespace std;

typedef enum tCelda { NULA, VACIA, FICHA };

const int MAXDIM = 10;

typedef struct tTablero
{
	int numFilas, numColumnas;
	tCelda celdas[MAXDIM][MAXDIM];
};

//funciones publicas

/*crea un tablero con fil filas y col columnas, con casillas inicializadas con valor inicial*/
void inicializa(tTablero& tab, int fil, int col, tCelda inicial);	

/*carga un tablero desde fichero entrada*/
void cargarTablero(tTablero& tab, istream& entrada);

/*numero de filas del tablero*/
int numFilas(tTablero const& tab);

/*numero de columnas del tablero*/
int numColumnas(tTablero const& tab);

/*cierto si la posicion (f,c) es valida dentro del tablero*/
bool correcta(tTablero const& tab, int f, int c);

/*tipo de celda: NULA, VACIA, FICHA*/
tCelda getCelda(tTablero const& tab, int f, int c);	

/*asignar el tipo de celda: NULA, VACIA, FICHA*/
void setCelda(tTablero& tab, int f, int c, tCelda valor);
