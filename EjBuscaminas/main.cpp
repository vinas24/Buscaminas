#include "inputOutput.h"
#include "juego.h"
#include "listaUndo.h"

/**
* Autores: Álvaro Pérez Otero y Sergio Viñas González
* Grupo: 24
*/


int main() {
	tJuego j;
	tListaPosiciones lp;
	tListaUndo lu;
	int fila, columna;
	//Se inicializan las listas, con sus contadores a 0
	inicializar(lp);
	inicializar(lu);
	bool abandonar = false;

	if (!carga_juego(j)) {
		//Esto debería hacerse a través de inputOutput, pero no podemos crear funciones publicas sooo...
		std::cout << "Error al cargar el juego\n";
	}
	else {
		do {
			mostrar_juego_consola(j);
			pedir_pos(fila, columna);
			//Si introduce -1 -1, abandonamos
			if (fila == -1 && columna == -1) {
				abandonar = true;
			}
			//Si introduce -2 -2, marcamos o desmarcamos
			else if (fila == -2 && columna == -2) {
				pedir_pos(fila, columna);
				marcar_desmarcar(j, fila, columna);
			}
			//Si introduce -3 -3, intentamos hacer undo
			else if (fila == -3 && columna == -3) {
				if (lu.cont == 0) {
					std::cout << "No se pueden hacer undos\n";
				}
				else {
					//LOS MARCAR NO HACEN UNDO
					//guardamos los ultimos mov en lp
					lp = ultimos_movimientos(lu);
					for (int i = 0; i < longitud(lp); i++) {
						//ocultamos las celdas de los ultimos mov
						ocultar(j, dame_posY(lp, i), dame_posX(lp, i));
					}
					lu.cont--;
				}
			}
			//Si introduce cualquer otra, realizamos jugada
			else {
				juega(j, fila, columna, lp);
				//AHORA GUARDAMOS PARA EL SIGUENTE UNDO
				if(longitud(lp) != 0) insertar_final(lu, lp);
				//reseteamos la lista de posiciones
				lp.cont = 0;

			}

		} while (!abandonar && !esta_terminado(j));
		//Una vez finalizado, mostramos el resultado y
		// el tablero una última vez
		mostrar_resultado(j);
		mostrar_juego_consola(j);
	}
	return 0;
}