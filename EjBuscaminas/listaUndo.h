#pragma once
#include "listaPosiciones.h"

const int MAX_UNDO = 5;

typedef struct {
	tListaPosiciones lista[MAX_UNDO];
	int cont;
} tListaUndo;

void inicializar(tListaUndo& lu);
void insertar_final(tListaUndo& lu, tListaPosiciones& lp);
tPosicion ultimos_movimientos(const tListaUndo& lu);
