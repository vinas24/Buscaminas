#include "celda.h"

void inicializar(tCelda& c) {
	c.visible = false;
	c.estado = VACIA;
	c.marcada = false;
	c.numero = 0;
}

tEstado dame_estado(const tCelda& c) {
	return c.estado;
}

int	dame_numero(const tCelda& c) {
	return c.numero;
}

bool es_visible(const tCelda& c) {
	return c.visible;
}

bool es_mina(const tCelda& c) {
	return c.estado == MINA;
}

bool esta_vacia(const tCelda& c) {
	return c.estado == VACIA;
}

bool contiene_numero(const tCelda& c) {
	return c.estado == NUMERO;
}

bool esta_marcada(const tCelda& c) {
	return c.marcada;
}

void descubrir_celda(tCelda& c) {
	c.visible = true;
}

void ocultar_celda(tCelda& c) {
	c.visible = false;
}

void poner_mina(tCelda& c) {
	c.estado = MINA;
}

void marcar_celda(tCelda& c) {
	c.marcada = true;
}

void desmarcar_celda(tCelda& c) {
	c.marcada = false;
}

void poner_numero(tCelda& c, int num) {
	c.estado = NUMERO;
	c.numero = num;
}