#pragma once

const int MAX_LISTA = 10;

typedef struct {
	int posx;
	int posy;
} tPosicion;

typedef struct {
	tPosicion* lista;
	int cont;
	int capacidad;
} tListaPosiciones;

tPosicion newPos(int x, int y);
void inicializar(tListaPosiciones& lp);
void insertar_final(tListaPosiciones& lp, int x, int y);
int longitud(const tListaPosiciones& lp);
int dame_posX(const tListaPosiciones& lp, int i);
int dame_posY(const tListaPosiciones& lp, int i);

void destruye(tListaPosiciones &lp);