#include "inputOutput.h"
#include "juego.h"
#include "listaPosiciones.h"



int main() {
	tJuego j;
	tListaPosiciones lp;
	int fila, columna;
	bool abandonar = false;
	inicializar(j, 3, 3);
	poner_mina(j, 1, 1);
	poner_mina(j, 1, 2);
	poner_mina(j, 0, 1);
	inicializar(lp);

	do {
		mostrar_juego_consola(j);
		pedir_pos(fila, columna);
		if (fila == -1 && columna == -1) {
			abandonar = true;
		}
		else if (fila == -2 && columna == -2) {
			pedir_pos(fila, columna);
			marcar_desmarcar(j, fila, columna);
		}
		else if (fila == -3 && columna == -3) {
			//Iplementar Undo
		}
		else {
			juega(j, fila, columna, lp);
		}
	} while (!abandonar && !esta_terminado(j));

	mostrar_resultado(j);
	mostrar_juego_consola(j);

	return 0;
}