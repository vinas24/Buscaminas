#pragma once
#include <iostream>
#include <fstream>
typedef enum { NUMERO, VACIA, MINA } tEstado;

typedef struct {
	bool visible;
	tEstado estado;
	int numero;
	bool marcada;
} tCelda;

void inicializar(tCelda& c);
tEstado dame_estado(const tCelda& c);
int	dame_numero(const tCelda& c);
bool es_visible(const tCelda& c);
bool es_mina(const tCelda& c);
bool esta_vacia(const tCelda& c);
bool contiene_numero(const tCelda& c);
bool esta_marcada(const tCelda& c);
void descubrir_celda(tCelda& c);
void ocultar_celda(tCelda& c);
void poner_mina(tCelda& c);
void marcar_celda(tCelda& c);
void desmarcar_celda(tCelda& c);
void poner_numero(tCelda& c, int num);