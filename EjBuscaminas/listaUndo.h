#pragma once
#include "listaPosiciones.h"
#include "memoryLeaks.h"

//Esto está mal, este max undo debería guardar otra cosa
//no puede usarse para el tamaño de la lista, a menos que esta se vaya reduciendo
const int MAX_UNDO = 3;
typedef struct {
	int cont;
	tListaPosiciones* lista[MAX_UNDO];
} tListaUndo;

void inicializar(tListaUndo& lu);
void insertar_final(tListaUndo& lu, const tListaPosiciones& lp);
tListaPosiciones ultimos_movimientos(tListaUndo& lu);

void eliminar_ultimo(tListaUndo& lu);
void destruye(tListaUndo& lu);
