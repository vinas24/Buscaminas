#include "listaUndo.h"

void inicializar(tListaUndo& lu) {
	lu.cont = 0;
}

void insertar_final(tListaUndo& lu, tListaPosiciones& lp) {

}

tPosicion ultimos_movimientos(const tListaUndo& lu) {
	return lu.lista->lista[lu.cont - 1];
}