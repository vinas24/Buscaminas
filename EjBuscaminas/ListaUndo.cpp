#include "listaUndo.h"

void inicializar(tListaUndo& lu) {
	lu.cont = 0;
}

void insertar_final(tListaUndo& lu, const tListaPosiciones& lp) {
	lu.lista[lu.cont] = lp;
	lu.cont++;
}

tListaPosiciones ultimos_movimientos(const tListaUndo& lu) {
	return lu.lista[lu.cont - 1];
}