#pragma once
#include "listaPosiciones.h"

//Esto está mal, este max undo debería guardar otra cosa
//no puede usarse para el tamaño de la lista, a menos que esta se vaya reduciendo
const int MAX_UNDO = 80000;

typedef struct {
	tListaPosiciones lista[MAX_UNDO];
	int cont;
} tListaUndo;

void inicializar(tListaUndo& lu);
void insertar_final(tListaUndo& lu, const tListaPosiciones& lp);
tListaPosiciones ultimos_movimientos(const tListaUndo& lu);
