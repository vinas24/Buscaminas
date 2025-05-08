#include "listaUndo.h"
#include <iostream>

void inicializar(tListaUndo& lu) {
	lu.cont = 0;
}

void insertar_final(tListaUndo& lu, const tListaPosiciones& lp) {
	//Si no hemos llegado al maximo de undos, insertamos al final
	if (lu.cont < MAX_UNDO) {
		lu.lista[lu.cont] = new tListaPosiciones(lp);
		lu.cont++;
	}
	//Si hemos llegado al max, insertamos al final desplazando el primero de todos
	//Similar a un FIFO
	else {
		delete lu.lista[0];
		for (int i = 0; i < MAX_UNDO - 1; i++) {
			lu.lista[i] = lu.lista[i + 1];
		}
		lu.lista[MAX_UNDO - 1] = new tListaPosiciones(lp);
	}
}

tListaPosiciones ultimos_movimientos(tListaUndo& lu) {
	tListaPosiciones lp  = * lu.lista[lu.cont -1];
	eliminar_ultimo(lu);
	return lp;
}


void eliminar_ultimo(tListaUndo& lu) {
	delete lu.lista[lu.cont - 1];
	lu.cont--;
}

void destruye(tListaUndo& lu) {
	for (int i = 0; i < lu.cont; i++) {
		destruye(*lu.lista[i]);
		delete lu.lista[i];
		lu.lista[i] = nullptr;
	}
}