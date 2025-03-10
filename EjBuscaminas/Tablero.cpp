#pragma once
#include "tablero.h"

void inicializar(tTablero& t) {
	t.nCols = 0;
	t.nFils = 0;
}

void inicializar_tablero(tTablero& t, int nfils, int ncols)
{
	inicializar(t);
	t.nCols = ncols;
	t.nFils = ncols;
	for (int i = 0; i < nfils; i++) {
		for (int j = 0; j < ncols; j++) {
			inicializar(t.datos[i][j]);
		}
	}
}

int num_filas(const tTablero& t) {
	return t.nFils;
}

int num_columnas(const tTablero& t) {
	return t.nCols;
}

tCelda dame_celda(const tTablero& t, int fila, int columna) {
	return t.datos[fila][columna];
}

void dame_celdaRef(const tTablero& t, tCelda& c, int fila, int columna) {
	c = t.datos[fila][columna];
}

bool es_valida(const tTablero& t, int fila, int columna) {
	return (fila >= 0 && fila < t.nFils) && (columna >= 0 && columna < t.nCols);
}

void poner_celda(tTablero& t, int fila, int columna, const tCelda& c) {
	t.datos[fila][columna] = c;
}