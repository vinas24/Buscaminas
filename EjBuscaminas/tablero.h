#pragma once
#include "celda.h"

const int MAX_FILS = 10, MAX_COLS = 10;

typedef struct {
	int nFils, nCols;
	tCelda datos[MAX_FILS][MAX_COLS];
} tTablero;

void inicializar(tTablero& t);
void inicializar_tablero(tTablero& t, int nfils, int ncols);
int num_filas(const tTablero& t);
int num_columnas(const tTablero& t);
tCelda dame_celda(const tTablero& t, int fila, int columna);
//
//QUITAR DAME CELDA REF y usar PONER_CELDA
//
void dame_celdaRef(const tTablero& t, tCelda& c, int fila, int columna);
bool es_valida(const tTablero& t, int fila, int columna);
void poner_celda(tTablero& t, int fila, int columna, const tCelda& c);