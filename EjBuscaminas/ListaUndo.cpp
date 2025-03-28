#include "listaUndo.h"

void inicializar(tListaUndo& lu) {
	lu.cont = 0;
}

void insertar_final(tListaUndo& lu, const tListaPosiciones& lp) {
	//Si no hemos llegado al maximo de undos, insertamos al final
	if (lu.cont < MAX_UNDO) {
		lu.lista[lu.cont] = lp;
		lu.cont++;
	} 
	//Si hemos llegado al max, insertamos al final desplazando el primero de todos
	//Similar a un FIFO
	else {
		for (int i = 0; i < MAX_UNDO - 1; i++) {
			lu.lista[i] = lu.lista[i + 1];
		}
		lu.lista[MAX_UNDO - 1] = lp;
	}
};

tListaPosiciones ultimos_movimientos(const tListaUndo& lu) {
	return lu.lista[lu.cont - 1];
}