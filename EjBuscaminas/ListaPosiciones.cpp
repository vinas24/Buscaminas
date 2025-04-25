#include "listaPosiciones.h"

void redimensionar(tListaPosiciones& lp);

tPosicion newPos(int x, int y) {
	tPosicion p;
	p.posx = x;
	p.posy = y;

	return p;
}

void inicializar(tListaPosiciones& lp) {
	lp.capacidad = MAX_LISTA;
	lp.cont = 0;
	lp.lista = new tPosicion[lp.capacidad];
}

void insertar_final(tListaPosiciones& lp, int x, int y) {
	if (lp.cont == lp.capacidad) {
		redimensionar(lp);
	}
	lp.lista[lp.cont] =  newPos(x, y);
	lp.cont++;
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

//a esto le falta algo fijo
void destruye(tListaPosiciones& lp) {
	delete lp.lista;
}

void redimensionar(tListaPosiciones& lp) {
	lp.capacidad *= 2;
	tPosicion* newLista = new tPosicion[lp.capacidad];

	for (int i = 0; i < lp.cont; i++) {
		newLista[i] = lp.lista[i];
	}
	delete lp.lista;
	lp.lista = newLista;
}