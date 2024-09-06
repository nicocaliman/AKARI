//movimiento.h
#pragma once
#include <string>
using namespace std;

const int NUM_DIR = 4;	//posibles direcciones del movimiento

typedef struct tIncr { int incFila, incCol; };
const tIncr INCR[] = { {-1,0}, {1,0}, {0,-1}, {0,1} };	//array de incrementos de fila y columna

typedef enum tDireccion { ARRIBA, ABAJO, IZQUIERDA, DERECHA, INDETERMINADA };

typedef struct tMovimiento
{
	int fila, columna;	//casilla origen del movimiento
	tDireccion activa;	//direccion en la que se va a ejecutar el movimiento
	int cont;	//numero de direcciones a las que se puede mover
	tDireccion direcciones[NUM_DIR];	//direcciones a las que se puede mover
};

//funciones publicas 

/*creacion del movimiento*/
tMovimiento inicializaMov(int f, int c);

/*fila origen del movimiento*/
int fila(tMovimiento const& m);

/*columna origen del movimiento*/
int columna(tMovimiento const& m);

/*covertir a string la direccion a la que se puede mover la ficha*/
string dirToString(tDireccion d);

/*incremento a aplicar a la fila segun la direccion d*/
int getIncrFil(tDireccion d);

/*incremento a aplicar a la columna segun la direccion d*/
int getIncrCol(tDireccion d);

/*direccion a la que se va a mover la ficha*/
tDireccion direccionActiva(tMovimiento const& m);

/*numero de direcciones a las que se puede mover la ficha*/
int numDirs(tMovimiento const& m);

/*direccion que se encuentra en la posicion i del array direcciones[]*/
tDireccion direccion(tMovimiento const& m, int i);

/*fijar el movimiento de la ficha*/
void fijarDireccionActiva(tMovimiento& m, tDireccion d);

/*insertar direccion en el array direcciones[]*/
void insertarDireccion(tMovimiento& m, tDireccion d);
