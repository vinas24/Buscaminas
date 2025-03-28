#pragma once
#include "tablero.h"
#include "listaPosiciones.h"

const int NUM_DIRECCIONES = 8;
const int VECTOR_DIRECCION = 2;
const int DIRECCIONES[NUM_DIRECCIONES][VECTOR_DIRECCION] =
{ -1, 0, -1, -1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, 1};

typedef struct {
	tTablero tablero;
	int num_jugadas;
	bool mina_explotada;
	int num_minas;
	int num_descubiertas;
} tJuego;

void inicializar(tJuego& j);
void inicializar(tJuego& j, int nfils, int ncols);
int dame_num_jugadas(const tJuego& j);
int dame_num_filas(const tJuego& j);
int dame_num_columnas(const tJuego& j);
int dame_num_minas(const tJuego& j);
bool contiene_mina(const tJuego& j, int fila, int columna);
bool es_visible(const tJuego& j, int fila, int columna);
bool esta_marcada(const tJuego& j, int fila, int columna);
bool esta_vacia(const tJuego& j, int fila, int columna);
bool contiene_numero(const tJuego& j, int fila, int columna);
int dame_numero(const tJuego& j, int fila, int columna);
bool esta_completo(const tJuego& j);
bool mina_explotada(const tJuego& j);
bool esta_terminado(const tJuego& j);
void poner_mina(tJuego& j, int fila, int columna);
void marcar_desmarcar(tJuego& j, int fila, int columna);
void ocultar(tJuego& j, int fila, int columna);
void juega(tJuego& j, int fila, int columna, tListaPosiciones& lp);