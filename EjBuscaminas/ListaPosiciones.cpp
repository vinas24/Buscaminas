#include "listaPosiciones.h"



tPosicion newPos(int x, int y) {
	tPosicion p;
	p.posx = x;
	p.posy = y;

	return p;
}

void inicializar(tListaPosiciones& lp) {
	lp.cont = 0;
}

void insertar_final(tListaPosiciones& lp, int x, int y) {
	if (lp.cont < MAX_LISTA) {
		lp.lista[lp.cont] = newPos(x, y);
		lp.cont++;
	}
}

int longitud(const tListaPosiciones& lp) {
	return lp.cont;
}

int dame_posX(const tListaPosiciones& lp, int i) {
	return lp.lista[i].posx;
}

int dame_posY(const tListaPosiciones& lp, int i) {
	return lp.lista[i].posy;
}