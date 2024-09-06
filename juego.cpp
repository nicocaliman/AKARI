	//juego.cpp
	#include "juego.h"
	#include "colores.h"
	#include <iostream>
	#include <string>
	#include <iomanip>
	#include <ctime>
	#include <cstdlib>
	using namespace std;

	const int DEFAULT_COLOR = -1;

	//funciones privadas
	void ejecutarMovimiento(tJuego& juego, tMovimiento const& mov);
	void nuevoEstado(tJuego& juego);
	bool hayGanador(tJuego const& juego);
	bool hayMovimientos(tJuego const& juego);
	void pintaCabecera(tJuego const& juego);
	void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, tJuego const& juego);
	void pintaBordeCelda(int fila, tJuego const& juego);
	void pintaCentroCelda(int fila, tJuego const& juego);
	void colorFondo(int color);
	int numFichas(tJuego const& juego);
	void setEstado(tJuego& juego, tEstado estado);
	bool fichaMovible(tJuego const& juego, tMovimiento& mov);
	bool celdasContiguasValidas(tJuego const& juego, tMovimiento& mov);
	void ejecutarMovimientoInverso(tJuego& juego, tMovimiento const& mov);

	void cargarJuego(tJuego& juego, istream& entrada)
	{
		//construir tablero
		cargarTablero(juego.tablero, entrada);

		//leer posicion de la meta
		entrada >> juego.filaMeta >> juego.colMeta;

		//estado inicial del juego
		juego.estado = JUGANDO;
	}

	bool posicionValida(tJuego const& juego, int f, int c)
	{
		//true si la posicion (f,c) es una posicion correcta y contiene una ficha(para comprobar si el usuario ha introducido una posicion correcta)
		return correcta(juego.tablero, f, c) && getCelda(juego.tablero, f, c) == FICHA;
	}

	void posiblesMovimientos(tJuego const& juego, tMovimiento& mov)
	{	
		int i = 0;
		int opcion;

		//recorrer las posibles direcciones de movimiento( ARRIBA, ABAJO, DERECHA, IZQUIERDA )
		while (i < NUM_DIR)
		{
			tDireccion dir = (tDireccion)i;

			//si la posicion a la que se quiere mover la ficha se encuentra en el rango de fil-col del tablero & el movimiento de la ficha es hacia una posicion vacia del tablero & la celda que se salta es una ficha
			if (correcta(juego.tablero, fila(mov) + 2*getIncrFil(dir), columna(mov) + 2*getIncrCol(dir)) && getCelda(juego.tablero, fila(mov)+2*getIncrFil(dir), columna(mov)+2*getIncrCol(dir)) == VACIA && getCelda(juego.tablero, fila(mov)+getIncrFil(dir), columna(mov)+getIncrCol(dir)) == FICHA)
			{
				//insertar direccion en el array de posibles direcciones
				insertarDireccion(mov, dir);
			}
			i++;	//actualizacion contador
		}	

		//mensaje de error si la ficha no se puede mover
		if (numDirs(mov) == 0)
			cout << setw(20) << "ERROR: La ficha (" << fila(mov) + 1 << "," << columna(mov) + 1 << ") no se puede mover en ninguna direccion.\n" << endl;

		//si hay 1 direccion posible
		else if (numDirs(mov) == 1)
			fijarDireccionActiva(mov, direccion(mov, 0));

		//si hay mas de 1 direccion posible
		else if(numDirs(mov) > 1)
		{
			//monstramos al usuario las opciones que tiene para mover la ficha
			cout << setw(26) << "Selecciona direccion: \n";
			for (int i = 0; i < numDirs(mov); i++)
				cout << setw(12) << i+1 << " - " << dirToString(direccion(mov, i)) << endl;
			cin >> opcion;

			//fijamos la direccion en la que se va a mover la ficha, elegida por el usuario
			fijarDireccionActiva(mov, direccion(mov, opcion - 1));
		}
	}

	tEstado estado(tJuego const& juego)
	{
		//estado en el que se encuentra el juego
		return juego.estado;
	}

	void jugar(tJuego& juego, tMovimiento const& mov)
	{
		//modifica el juego dependiendo del movimiento elegido
		ejecutarMovimiento(juego, mov);

		//modificar el estado del juego
		nuevoEstado(juego);
	}

	void mostrar(tJuego const& juego)
	{
		cout << RESET;

		//borde superior
		pintaCabecera(juego);
		pintaLinea(char(218), char(194), char(191), juego);

		//para cada fila
		for (int fil = 0; fil < numFilas(juego.tablero); fil++)
		{
			//primera linea
			pintaBordeCelda(fil, juego);
			//segunda linea, con la meta posiblemente
			pintaCentroCelda(fil, juego);
			//tercera linea
			pintaBordeCelda(fil, juego);
			//separacion entre filas
			if (fil < numFilas(juego.tablero) - 1)
				pintaLinea(char(195), char(197), char(180), juego);
			else
				pintaLinea(char(192), char(193), char(217), juego);
		}
	}

	void genera(tJuego& juego, int pasos)
	{
		int dir = -1, i = 1;

		srand(time(NULL));

		//crear tablero vacio(todas las celdas nulas)
		inicializa(juego.tablero, numFilas(juego.tablero), numColumnas(juego.tablero), NULA);

		//coordenadas celda meta
		int fila = rand() % numFilas(juego.tablero);	//numero aleatorio de 0 - (numFilas-1)
		int col = rand() % numColumnas(juego.tablero);	//numero aleatorio de 0 - (numColumnas-1)

		juego.filaMeta = fila;
		juego.colMeta = col;

		//modificamos el tipo de la celda
		setCelda(juego.tablero, fila, col, FICHA);

		while (i <= pasos)
		{
			//escoger de forma aleatoria una ficha ya colocada
			while (getCelda(juego.tablero, fila, col) != FICHA && numFichas(juego) > 1)
			{
				fila = rand() % numFilas(juego.tablero);
				col = rand() % numColumnas(juego.tablero);
			}

			//inicializar movimiento
			tMovimiento mov = inicializaMov(fila, col);

			//si la ficha elegida es capaz de realizar el movimiento inverso
			if (celdasContiguasValidas(juego, mov))
			{
				//elegimos direccion aleatoriamente
				dir = rand() % numDirs(mov);

				//fijamos el movimiento que realizara la ficha
				fijarDireccionActiva(mov, direccion(mov, dir));

				//ejecutar movimiento inverso
				ejecutarMovimientoInverso(juego, mov);
			}

			i++;
		}
	}

	void ejecutarMovimiento(tJuego& juego, tMovimiento const& mov)
	{
		//establecer celda origen a VACIA
		setCelda(juego.tablero, fila(mov), columna(mov), VACIA);

		//eliminar FICHA sobre la que se ha saltado
		setCelda(juego.tablero, fila(mov)+getIncrFil(direccionActiva(mov)), columna(mov)+getIncrCol(direccionActiva(mov)), VACIA);

		//poner la FICHA en la celda
		setCelda(juego.tablero, fila(mov)+2*getIncrFil(direccionActiva(mov)), columna(mov)+2*getIncrCol(direccionActiva(mov)), FICHA);
	}

	void nuevoEstado(tJuego& juego)
	{
		//si la ultima ficha esta en la posicion META
		if (hayGanador(juego))
			setEstado(juego, GANADOR);	//modificar estado

		//si no se puede mover ninguna ficha
		else if (!hayMovimientos(juego))
			setEstado(juego, BLOQUEO);	//modificar estado
	}

	bool hayGanador(tJuego const& juego)
	{
		//true si queda solo una ficha en el tablero y si esta se encuentra en la posicion (filaMeta, colMeta)
		return numFichas(juego) == 1 && getCelda(juego.tablero, juego.filaMeta, juego.colMeta) == FICHA;
	}

	bool hayMovimientos(tJuego const& juego)
	{
		bool movimientos = false;
		int i = 0, j;

		while (i < numFilas(juego.tablero) && !movimientos)
		{
			j = 0;
		
			while (j < numColumnas(juego.tablero) && !movimientos)
			{				
				tMovimiento mov = inicializaMov(i,j);

				if (getCelda(juego.tablero, i, j) == FICHA && fichaMovible(juego, mov))
				{
					movimientos = true;
				}

				else
					j++;
			}

			if (!movimientos)
				i++;
		}

		return movimientos;
	}

	void pintaCabecera(tJuego const& juego)
	{
		cout << setw(2) << "    "; // margen inicial
		cout << setw(5) << 1;

		for (int i = 2; i <= numColumnas(juego.tablero); i++)
			cout << setw(7) << i;
		cout << endl;
	}

	void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, tJuego const& juego)
	{
		cout << "    "; // margen inicial
		cout << esquinaIzda;
		for (int i = 0; i < numColumnas(juego.tablero) - 1; i++)
			cout << string(6, char(196)) << cruce;
		cout << string(6, char(196)) << esquinaDer << endl;
	}

	void pintaBordeCelda(int fila, tJuego const& juego)
	{
		cout << "    "; // margen inicial
	
		for (int k = 0; k < numColumnas(juego.tablero); k++)
		{
			//cada columna
			cout << char(179);      
			colorFondo(juego.tablero.celdas[fila][k]);
			cout << "      ";
			colorFondo(DEFAULT_COLOR);
		}
		cout << char(179) << endl; // lateral derecho		
	}

	void pintaCentroCelda(int fila, tJuego const& juego)
	{
		cout << "  " << setw(2) << fila + 1; // margen inicial
		for (int k = 0; k < numColumnas(juego.tablero); k++)
		{ // cada columna
			cout << char(179);
			// el color de fondo depende del contenido
			colorFondo(juego.tablero.celdas[fila] [k] );
			if (fila == juego.filaMeta && k == juego.colMeta)
			{ // meta
				cout << YELLOW;
				cout << "  " << char(219) << char(219) << "  ";
			}
			else
				cout << "      ";
			colorFondo(DEFAULT_COLOR);
		}
		cout << char(179) << endl; // lateral derecho
	}

	void colorFondo(int color)
	{
		if (color == DEFAULT_COLOR)
			cout << RESET;
		else if (color == NULA)
			cout << BG_BLACK;
		else if (color == FICHA)
			cout << BG_LBLUE;
		else	//color = VACIA
			cout << BG_ORANGE;
	}

	int numFichas(tJuego const& juego)
	{
		int cont = 0;

		for (int i = 0; i < numFilas(juego.tablero); i++)
		{
			for (int j = 0; j < numColumnas(juego.tablero); j++)
			{
				if (getCelda(juego.tablero, i, j) == FICHA)
					cont++;
			}
		}

		return cont;
	}

	void setEstado(tJuego& juego, tEstado estado)
	{
		juego.estado = estado;
	}

	bool fichaMovible(tJuego const& juego, tMovimiento& mov)
	{
		int i = 0;
		bool movible = false;

		//recorrer las posibles direcciones de movimiento( ARRIBA, ABAJO, DERECHA, IZQUIERDA )
		while (i < NUM_DIR)
		{
			tDireccion dir = (tDireccion)i;

			//si la posicion a la que se quiere mover la ficha se encuentra en el rango de fil-col del tablero & el movimiento de la ficha es hacia una posicion vacia del tablero & la celda que se salta es una ficha
			if (correcta(juego.tablero, fila(mov) + 2 * getIncrFil(dir), columna(mov) + 2 * getIncrCol(dir)) && getCelda(juego.tablero, fila(mov) + 2 * getIncrFil(dir), columna(mov) + 2 * getIncrCol(dir)) == VACIA && getCelda(juego.tablero, fila(mov) + getIncrFil(dir), columna(mov) + getIncrCol(dir)) == FICHA)
			{
				//insertar direccion en el array de posibles direcciones
				insertarDireccion(mov, dir);
			}
			i++;	//actualizacion contador
		}

		if (numDirs(mov) > 0)
		{
			movible = true;
		}

		return movible;
	}

	bool celdasContiguasValidas(tJuego const& juego, tMovimiento& mov)
	{
		int i = 0;
		bool validas = false;

		//recorrer las posibles direcciones de movimiento( ARRIBA, ABAJO, DERECHA, IZQUIERDA )
		while (i < NUM_DIR)
		{
			tDireccion dir = (tDireccion)i;

			//si la posicion a la que se quiere mover la ficha se encuentra en el rango de fil-col del tablero & el movimiento de la ficha es hacia una posicion vacia del tablero & la celda que se salta es una ficha
			if (correcta(juego.tablero, fila(mov) + 2 * getIncrFil(dir), columna(mov) + 2 * getIncrCol(dir)) && (getCelda(juego.tablero, fila(mov) + 2 * getIncrFil(dir), columna(mov) + 2 * getIncrCol(dir)) == VACIA || getCelda(juego.tablero, fila(mov) + 2 * getIncrFil(dir), columna(mov) + 2 * getIncrCol(dir)) == NULA) && (getCelda(juego.tablero, fila(mov) + getIncrFil(dir), columna(mov) + getIncrCol(dir)) == VACIA || getCelda(juego.tablero, fila(mov) + getIncrFil(dir), columna(mov) + getIncrCol(dir)) == NULA))
			{
				//insertar direccion en el array de posibles direcciones
				insertarDireccion(mov, dir);
			}
			i++;	//actualizacion contador
		}

		if (numDirs(mov) > 0)
		{
			validas = true;
		}

		return validas;
	}

	void ejecutarMovimientoInverso(tJuego& juego, tMovimiento const& mov)
	{
		//vaciar celda donde se encuentra la ficha que realiza el movimiento inverso
		setCelda(juego.tablero, fila(mov), columna(mov), VACIA);

		//colocar la supuesta ficha que se deberia de eliminar del tablero
		setCelda(juego.tablero, fila(mov) + getIncrFil(direccionActiva(mov)), columna(mov) + getIncrCol(direccionActiva(mov)), FICHA);

		//colocar la ficha desde la celda real desde la que realiza su movimiento
		setCelda(juego.tablero, fila(mov) + 2 * getIncrFil(direccionActiva(mov)), columna(mov) + 2 * getIncrCol(direccionActiva(mov)), FICHA);
	}
