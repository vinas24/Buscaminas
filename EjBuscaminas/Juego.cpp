#include "juego.h"
//#include <cstdlib> // For rand() and srand()
//#include <ctime>   // For time()


void descubrirCelda(tJuego& j, tListaPosiciones& lp, int fil, int col);
void aumentarNum(tJuego& j, int fil, int col);
void asignarMinas(tJuego& j);

void inicializar(tJuego& j) {
	inicializar(j.tablero);	
	j.num_descubiertas = 0;
	j.num_jugadas = 0;
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
int dame_num_descubiertas(const tJuego& j) {
	return j.num_descubiertas;
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
	return ((dame_num_columnas(j) * dame_num_filas(j) - dame_num_minas(j)) == dame_num_descubiertas(j));
}

bool mina_explotada(tJuego& j) {
	return j.mina_explotada;
}

bool esta_terminado(tJuego& j) {
	// si se cumplen esta completo o mina explotada
	return mina_explotada(j) || esta_completo(j);
}

void poner_mina(tJuego& j, int fila, int columna) {
	//Para poner la mina, la pos tiene que ser valida y no tener una mina
	if (es_valida(j.tablero, fila, columna) && !contiene_mina(j, fila, columna)) {
		//Ponemos la mina
		tCelda c = dame_celda(j.tablero, fila, columna);
		poner_mina(c);
		poner_celda(j.tablero, fila, columna, c);
		j.num_minas++;
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
		j.num_jugadas++;
	}
}

void ocultar(tJuego& j, int fila, int columna) {

	if (es_valida(j.tablero, fila, columna)) {
		tCelda c = dame_celda(j.tablero, fila, columna);
		if (es_visible(j, fila, columna)) ocultar_celda(c);
		poner_celda(j.tablero, fila, columna, c);
		j.num_descubiertas--;
	}
}

void juega(tJuego& j, int fila, int columna, tListaPosiciones& lp) {

	descubrirCelda(j, lp, fila, columna);
	j.num_jugadas++;
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
	if (es_valida(j.tablero, fil, col) && !esta_marcada(j, fil, col)) {
		if (!es_visible(j, fil, col) ) {
			//la pone visible y actualiza lista pos
			tCelda c = dame_celda(j.tablero, fil, col);
			descubrir_celda(c);
			poner_celda(j.tablero, fil, col, c);
			//Añadimos a la lista de posiciones
			insertar_final(lp, col, fil);
			j.num_descubiertas++;
			if (es_mina(c)) j.mina_explotada = true;
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


//Vestigios de cuando me apeteció hacer la asignación al azar
//void asignarMinas(tJuego& j) {
//	int nMinas = 0;
//
//	//Esto es para que rand() si sea random y no se repita
//	srand(static_cast<unsigned int>(time(0))); 
//	//
//	
//	//Repetiremos esto para tantas minas como tengamos especificado en el juego
//	while (nMinas < j.num_minas) {
//		//Escogemos una casilla (fila,col) al azar
//		int filaRandom = rand() % dame_num_filas(j);
//		int columnaRandom = rand() % dame_num_columnas(j);
//		//Si no contiene ya una mina, la ponemos.
//		if (!contiene_mina(j, filaRandom, columnaRandom)) {
//			poner_mina(j, filaRandom, columnaRandom);
//			nMinas++;
//		}
//	}
//
//}
