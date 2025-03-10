#pragma once

const int MAX_LISTA = 100;

typedef struct {
	int posx;
	int posy;
} tPosicion;

typedef struct {
	tPosicion lista[MAX_LISTA];
	int cont;
} tListaPosiciones;

tPosicion newPos(int x, int y);
void inicializar(tListaPosiciones& lp);
void insertar_final(tListaPosiciones& lp, int x, int y);
int longitud(const tListaPosiciones& lp);
int dame_posX(const tListaPosiciones& lp, int i);
int dame_posY(const tListaPosiciones& lp, int i);