	//movimiento.cpp
	#include "movimiento.h"

	//funciones privadas
	void setMovFila(tMovimiento& m, int f);	//modifica la fila origen del movimiento
	void setMovCol(tMovimiento& m, int c);	//modifica la columna origen del movimiento
	void setCont(tMovimiento& m, int cont); //modifica el numero de direcciones a las que se puede mover

	tMovimiento inicializaMov(int f, int c)
	{
		tMovimiento mov;

		//posicion de origen del movimiento
		setMovFila(mov, f);
		setMovCol(mov, c);

		//numero de posiciones a las que se puede mover
		setCont(mov, 0);

		//direccion en la que se va a ejecutar el movimiento
		fijarDireccionActiva(mov, INDETERMINADA);

		return mov;
	}

	int fila(tMovimiento const& m)
	{
		//fila origen del movimiento
		return m.fila;
	}

	int columna(tMovimiento const& m)
	{
		//columna origen del movimiento
		return m.columna;
	}

	string dirToString(tDireccion d)
	{
		string dir;

		//convertir a string el valor d del enumerado (ARRIBA, ABAJO, IZQUIERDA, DERECHA, INDETERMINADA)
		switch (d)
		{
		case ARRIBA:
			dir = "ARRIBA";
			break;
		case ABAJO:
			dir = "ABAJO";
			break;
		case IZQUIERDA:
			dir = "IZQUIERDA";
			break;
		case DERECHA:
			dir = "DERECHA";
			break;
		default:
			dir = "INDETERMINADA";
			break;
		}

		return dir;
	}

	int getIncrFil(tDireccion d)
	{
		//incremento de fila (d = ARRIBA(0){-1,0}, ABAJO(1){1,0}, IZQUIERDA(2){0,-1}, DERECHA(3){0,1})
		return INCR[d].incFila;
	}

	int getIncrCol(tDireccion d)
	{
		//incremento de columna	(d = ARRIBA{-1,0}, ABAJO{1,0}, IZQUIERDA{0,-1}, DERECHA{0,1})
		return INCR[d].incCol;
	}

	tDireccion direccionActiva(tMovimiento const& m)
	{
		//direccion en la que se va a ejecutar el movimiento
		return m.activa;
	}

	int numDirs(tMovimiento const& m)
	{
		//numero de direcciones a las que se puede mover
		return m.cont;
	}

	tDireccion direccion(tMovimiento const& m, int i)
	{
		//direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA, INDETERMINADA) almacenada en la posicion i del array direcciones
		return m.direcciones[i];
	}

	void fijarDireccionActiva(tMovimiento& m, tDireccion d)
	{
		//asignar d como direccion en la que se va a ejecutar el movimiento
		m.activa = d;
	}

	void insertarDireccion(tMovimiento& m, tDireccion d)
	{
		m.direcciones[m.cont++] = d;	//agregar las direcciones posibles en las que una ficha puede moverse	
	}

	void setMovFila(tMovimiento& m, int f)
	{
		//asignar f como fila origen del movimiento
		m.fila = f;
	}

	void setMovCol(tMovimiento& m, int c)
	{
		//asignar c como columna origen del movimiento
		m.columna = c;
	}

	void setCont(tMovimiento& m, int cont)
	{
		//asignar cont como  el numero de direcciones a las que se puede mover
		m.cont = cont;
	}