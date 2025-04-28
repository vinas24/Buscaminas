#pragma once
#include "juego.h"

const int MAX_JUEGOS = 3;

typedef tJuego* tPtrJuego;

typedef struct {
	tPtrJuego* lista;
	int cont;
	int capacidad;
} tListaJuegos;

void inicializar(tListaJuegos &lista_juegos);
void destruye(tListaJuegos &lista_juegos);
void insertar(tListaJuegos &tListaJuegoslista_juegos, tJuego& juego);
int numero_juegos(const tListaJuegos& lista_juegos);
bool es_vacia(const tListaJuegos& lista_juegos);
tJuego dame_juego(tListaJuegos &lista_juegos, int pos);
void eliminar(tListaJuegos &lista_juegos, int pos);