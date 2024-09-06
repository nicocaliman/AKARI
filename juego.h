//juego.h
#pragma once
#include "tablero.h"
#include "movimiento.h"

typedef enum tEstado { JUGANDO, GANADOR, BLOQUEO };

typedef struct tJuego
{
	int filaMeta, colMeta;
	tTablero tablero;
	tEstado estado;
};

//funciones publicas

/*cargar el juego a partir del fichero ya abierto*/
void cargarJuego(tJuego& juego, istream& entrada);

/*cierto si la posicion (f,c) es una posicion correcta del tablero y contiene una ficha*/
bool posicionValida(tJuego const& juego, int f, int c);

/*recibe mov y lo completa con las direcciones en las que se puede mover la ficha*/
void posiblesMovimientos(tJuego const& juego, tMovimiento& mov);

/*estado en el que se encuentra el juego*/
tEstado estado(tJuego const& juego);

/*modifica el juego realizando el movimiento descrito*/
void jugar(tJuego& juego, tMovimiento const& mov);

/*mostrar el tablero*/
void mostrar(tJuego const& juego);

/*generacion aleatoria de tableros*/
void genera(tJuego& juego, int pasos);	
