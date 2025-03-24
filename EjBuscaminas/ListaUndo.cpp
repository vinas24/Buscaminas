#include "listaUndo.h"

void inicializar(tListaUndo& lu) {
	lu.cont = 0;
}

void insertar_final(tListaUndo& lu, const tListaPosiciones& lp) {
	if (lu.cont < MAX_UNDO) {
		lu.lista[lu.cont] = lp;
		lu.cont++;
	} else {
		for (int i = 0; i < MAX_UNDO - 1; i++) {
			lu.lista[i] = lu.lista[i + 1];
		}
		lu.lista[MAX_UNDO - 1] = lp;
	}
};

tListaPosiciones ultimos_movimientos(const tListaUndo& lu) {
	return lu.lista[lu.cont - 1];
}