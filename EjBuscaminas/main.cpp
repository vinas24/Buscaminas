#include "inputOutput.h"
#include "juego.h"
#include "listaUndo.h"



int main() {
	tJuego j;
	tListaPosiciones lp;
	tListaUndo lu;
	int fila, columna, nUndos = 0;
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
			if (fila == -1 && columna == -1) {
				abandonar = true;
			}
			else if (fila == -2 && columna == -2) {
				pedir_pos(fila, columna);
				marcar_desmarcar(j, fila, columna);
			}
			else if (fila == -3 && columna == -3) {
				if (lu.cont == 0) {
					std::cout << "No hay movimientos para hacer undo\n";
				}
				else if  (nUndos >= MAX_UNDO){
					std::cout << "No se pueden hacer más undos\n";
				}
				else {
					//LOS MARCAR NO FUNCIONAN 
					//guardamos los ultimos mov en lp
					lp = ultimos_movimientos(lu);
					nUndos++;
					for (int i = 0; i < longitud(lp); i++) {
						//ocultamos las celdas de los ultimos mov
						ocultar(j, dame_posY(lp, i), dame_posX(lp, i));
					}
					lu.cont--;
				}
				
			}
			else {
				juega(j, fila, columna, lp);

				//
				//AHORA GUARDAMOS PARA EL SIGUENTE UNDO
				// 
				//guardamos las jugadas en lu
				if(longitud(lp) != 0) insertar_final(lu, lp);
				//reseteamos la lista de posiciones
				lp.cont = 0;

			}

		} while (!abandonar && !esta_terminado(j));

		mostrar_resultado(j);
	}
	return 0;
}