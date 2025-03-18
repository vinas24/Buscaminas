#include "inputOutput.h"
#include "juego.h"
#include "listaPosiciones.h"



int main() {
	tJuego j;
	tListaPosiciones lp;
	int fila, columna;
	inicializar(j, 5, 5);
	poner_mina(j, 1, 1);
	poner_mina(j, 3, 3);
	poner_mina(j, 4, 1);
	inicializar(lp);

	do {
		mostrar_juego_consola(j);
		pedir_pos(fila, columna);
		juega(j, fila, columna, lp);
	} while (!esta_terminado(j));

	mostrar_resultado(j);
	mostrar_juego_consola(j);
	return 0;
}