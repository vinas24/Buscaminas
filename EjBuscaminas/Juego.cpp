#include "juego.h"

void descubrirCelda(tJuego& j, tListaPosiciones& lp, int fil, int col);
void aumentarNum(tJuego& j, int fil, int col);

void inicializar(tJuego& j) {

	inicializar(j.tablero);
	j.num_descubiertas = 0;
	j.num_minas = 0;
	j.num_descubiertas = 0;
	j.mina_explotada = false;
}

void inicializar(tJuego& j, int nfils, int ncols) {
	inicializar(j);
	inicializar_tablero(j.tablero, nfils, ncols);
}

int dame_num_jugadas(const tJuego& j) {
	return j.num_jugadas;
}

int dame_num_filas(const tJuego& j) {
	return num_filas(j.tablero);
}
int dame_num_columnas(const tJuego& j) {
	return num_columnas(j.tablero);
}

int dame_num_minas(const tJuego& j) {
	return j.num_minas;
}

bool contiene_mina(const tJuego& j, int fila, int columna) {
	return es_mina(dame_celda(j.tablero, fila, columna));
}

bool es_visible(const tJuego& j, int fila, int columna) {
	return es_visible(dame_celda(j.tablero, fila, columna));
}

bool esta_marcada(const tJuego& j, int fila, int columna) {
	return esta_marcada(dame_celda(j.tablero, fila, columna));
}

bool esta_vacia(const tJuego& j, int fila, int columna) {
	return esta_vacia(dame_celda(j.tablero, fila, columna));
}

bool contiene_numero(tJuego& j, int fila, int columna) {
	return contiene_numero(dame_celda(j.tablero, fila, columna));
}

int dame_numero(tJuego& j, int fila, int columna) {
	return dame_celda(j.tablero, fila, columna).numero;
}

bool esta_completo(tJuego& j) {
	//devuelve true si todas las celdas no mina están visibles
	bool completo = true;
	int f = dame_num_filas(j);
	int c = dame_num_columnas(j);
	int i = 0, k;

	while (completo && i < f) {
		k = 0;
		while (completo && k < c) {
			// a la que una celda no sea visible, saldrá del bucle
			if (!contiene_mina(j,i,k)) completo = es_visible(j,i,k);
			k++;
		}
		i++;
	}
	return completo;
}

void mina_explotada(tJuego& j) {
	int f = dame_num_filas(j);
	int c = dame_num_columnas(j);
	int i = 0, k;
	tCelda celda;
	while (!j.mina_explotada && i < f) {
		k = 0;
		while (!j.mina_explotada && k < c) {
			celda = dame_celda(j.tablero, f, c);
			// si alguna de las celdas tiene mina y es visible, esta explota
			if (contiene_mina(j, i, k)) j.mina_explotada = es_visible(j, i, k);
			k++;
		}
		i++;
	}
}

bool esta_terminado(tJuego& j) {
	// si se cumplen esta completo o mina explotada
	return j.mina_explotada || esta_completo;
}

void poner_mina(tJuego& j, int fila, int columna) {
	//Para poner la mina, la pos tiene que ser valida y no tener una mina
	if (es_valida(j.tablero, fila, columna) && !contiene_mina(j, fila, columna)) {
		//Ponemos la mina
		tCelda c = dame_celda(j.tablero, fila, columna);
		poner_mina(c);
		poner_celda(j.tablero, fila, columna, c);
		//actualizar posiciones adyacentes
		for (int k = 0; k < NUM_DIRECCIONES; k++) {
			 aumentarNum(j, fila + DIRECCIONES[k][0], columna + DIRECCIONES[k][1]);
		}
	}
}

void marcar_desmarcar(tJuego& j, int fila, int columna) {

	if (es_valida(j.tablero, fila, columna)) {
		tCelda c = dame_celda(j.tablero, fila, columna);
		if (esta_marcada(j, fila, columna)) {
			desmarcar_celda(c);
		}
		else {
			marcar_celda(c);
		}
		poner_celda(j.tablero, fila, columna, c);
	}
}

void ocultar(tJuego& j, int fila, int columna) {

	if (es_valida(j.tablero, fila, columna)) {
		tCelda c = dame_celda(j.tablero, fila, columna);
		if (!es_visible(j, fila, columna)) ocultar_celda(c);
		poner_celda(j.tablero, fila, columna, c);
	}
}

void juega(tJuego& j, int fila, int columna, tListaPosiciones& lp) {

	descubrirCelda(j, lp, fila, columna);

	if (es_valida(j.tablero, fila, columna)) {
		//Si la celda está vacia, mostar sus vecinas
		if (esta_vacia(j, fila, columna)) {
			//actualizar posiciones adyacentes
			for (int k = 0; k < NUM_DIRECCIONES; k++) {
				descubrirCelda(j, lp, fila + DIRECCIONES[k][0], columna + DIRECCIONES[k][1]);
			}
		}
	}
}

void descubrirCelda(tJuego& j, tListaPosiciones& lp, int fil, int col) {
	//comprueba valida, no visible y no marcada
	if (es_valida(j.tablero, fil, col)) {
		if (!es_visible(j, fil, col) && !esta_marcada(j, fil,col)) {
			//la pone visible y actualiza lista pos
			tCelda c = dame_celda(j.tablero, fil, col);
			descubrir_celda(c);
			poner_celda(j.tablero, fil, col, c);
			//Añadimos a la lista de posiciones
			insertar_final(lp, col, fil);
		}
	}
}

void aumentarNum(tJuego& j, int fil, int col) {
	//comprobar si la casilla existe y no es mina
	if (es_valida(j.tablero, fil, col) && !contiene_mina(j, fil, col)) {
		//aumentamos en 1 su numero
		tCelda c = dame_celda(j.tablero, fil, col);
		poner_numero(c, dame_numero(c)+1);
		poner_celda(j.tablero, fil, col, c);
	}
}
