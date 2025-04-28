#include "juego.h"

void descubrirRecursivo(tJuego& j, tListaPosiciones& lp, int fila, int columna);
void descubrirCelda(tJuego& j, tListaPosiciones& lp, int fil, int col);
void aumentarNum(tJuego& j, int fil, int col);

void inicializar(tJuego& j) {
	inicializar(j.tablero);	
	j.num_jugadas = 0;
	j.num_minas = 0;
	j.num_descubiertas = 0;
	j.mina_explotada = false;
}

void inicializar(tJuego& j, int nfils, int ncols) {
	inicializar(j);
	inicializar_tablero(j.tablero, nfils, ncols);
}
bool operator< (const tJuego& j1, const tJuego &j2) {
	return calcula_nivel(j1) < calcula_nivel(j2);
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

bool contiene_numero(const tJuego& j, int fila, int columna) {
	return contiene_numero(dame_celda(j.tablero, fila, columna));
}

int dame_numero(const tJuego& j, int fila, int columna) {
	return dame_celda(j.tablero, fila, columna).numero;
}

bool esta_completo(const tJuego& j) {
	//devuelve true si todas las celdas no mina están visibles
	return ((dame_num_columnas(j) * dame_num_filas(j) - dame_num_minas(j)) == dame_num_descubiertas(j));
}

bool mina_explotada(const tJuego& j) {
	return j.mina_explotada;
}

bool esta_terminado(const tJuego& j) {
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
	if (es_valida(j.tablero, fila, columna)) {
		j.num_jugadas++;
		descubrirRecursivo(j, lp, fila, columna);
	}
}

void descubrirRecursivo(tJuego& j, tListaPosiciones &lp, int fila, int columna) {
	if (!es_valida(j.tablero, fila, columna) || es_visible(j, fila, columna) || esta_marcada(j, fila, columna)) return;

	descubrirCelda(j, lp, fila, columna);

	if (esta_vacia(j, fila, columna)) {
		for (int k = 0; k < NUM_DIRECCIONES; k++) {
			descubrirRecursivo(j, lp, fila + DIRECCIONES[k][0], columna + DIRECCIONES[k][1]);
		}
	}
}

void descubrirCelda(tJuego& j, tListaPosiciones& lp, int fil, int col) {
	//la pone visible y actualiza lista pos
	tCelda c = dame_celda(j.tablero, fil, col);
	descubrir_celda(c);
	poner_celda(j.tablero, fil, col, c);
	//Añadimos a la lista de posiciones
	insertar_final(lp, col, fil);
	j.num_descubiertas++;
	//Si hemos descubierto una mina, el flag de mina_explotada a true
	if (es_mina(c)) j.mina_explotada = true;
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

int calcula_nivel(const tJuego& juego) {
	//Dificultad en base al porcentaje de minas/celtas ??
	return  (double) dame_num_minas(juego) * 100 / (dame_num_filas(juego) * dame_num_columnas(juego));
}

//Crea un tablero con las medidas especificadas
//Las minas son asignadas de forma aleatoria
tJuego crear_juego(int num_fils, int num_cols, int num_minas) {
	tJuego j;
	inicializar(j, num_fils, num_cols);
	//inicializamos el tablero
	inicializar_tablero(j.tablero, num_fils, num_cols);
	//ponemos las minas
	int minasPuestas = 0;
	while (minasPuestas < num_minas) {
		int fila = rand() % dame_num_filas(j);
		int columna = rand() % dame_num_columnas(j);
		//Si ya había una mina, repetimos
		if (!contiene_mina(j, fila, columna)) {
			poner_mina(j, fila, columna);
			minasPuestas++;
		}
	}
	return j;
}