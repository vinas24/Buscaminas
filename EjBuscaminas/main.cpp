#include "inputOutput.h"
#include "juego.h"
#include "listaUndo.h"

/**
* Autores: Álvaro Pérez Otero y Sergio Viñas González
* Grupo: 24
*/

tJuego crearNuevoJuego();
void limpiarCin();

int main() {
	tJuego j;
	tListaPosiciones lp;
	tListaUndo lu;
	tListaJuegos lj;
	int fila, columna;
	//Se inicializan las listas, con sus contadores a 0
	inicializar(lp);
	inicializar(lu);
	inicializar(lj);
	bool abandonar = false;

	if (!cargar_juegos(lj)) {
		//Esto debería hacerse a través de inputOutput, pero no podemos crear funciones publicas sooo...
		std::cout << "El fichero no existe, se creara un nuevo juego aleatorio\n";
		j = crearNuevoJuego();
		insertar(lj, j);
	}
	else {
		std::cout << "Deseas juegar a un juego nuevo (1), o a uno existente (2).\nIntroduce la opcion seleccionada:\n";
		int opt;
		do {
			std::cin >> opt;
			if (opt != 1 && opt != 2) {
				std::cout << "La opcion elegida no existe...\nElige entre las opciones 1 y 2.\n";
			}
		} while (opt != 1 && opt != 2);
		if (opt == 1) {
			j = crearNuevoJuego();
			insertar(lj, j);
		}
		else {
			mostrar_juegos(lj);
			do {
				std::cin >> opt;
				if (opt < 0 || opt >= lj.cont) {
					std::cout << "El juego seleccionado no existe...\nVuelve a seleccionar partida...\n";
				}
			} while (opt < 0 || opt >= lj.cont);
			j = dame_juego(lj, opt);

		}
	}
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
				std::cout << "No se pueden hacer undos.\n";
			}
			else {
				//LOS MARCAR NO HACEN UNDO
				//guardamos los ultimos mov en lp
				lp = ultimos_movimientos(lu);
				for (int i = 0; i < longitud(lp); i++) {
					//ocultamos las celdas de los ultimos mov
					ocultar(j, dame_posY(lp, i), dame_posX(lp, i));
				}
			}
		}
		//Si introduce cualquer otra, realizamos jugada
		else {
			juega(j, fila, columna, lp);
			//AHORA GUARDAMOS PARA EL SIGUENTE UNDO
				
			if(longitud(lp) != 0) insertar_final(lu, lp);
			std::cout << longitud(lp) << "  " << lu.cont << std::endl;
			//reseteamos la lista de posiciones
			destruye(lp);
			inicializar(lp);
		}
	} while (!abandonar && !esta_terminado(j));
	//Una vez finalizado, mostramos el resultado y
	// el tablero una última vez
	mostrar_resultado(j);
	mostrar_juego_consola(j);
	//pedimos confirmacion para guardar
	//REVISAR ESTO Q NO ME FIO
	if (!abandonar) {
		std::cout << "¿Quieres guardar el juego? (1/0)\n";
		int opt;
		std::cin >> opt;
		if (opt == 1) {
			if (!guardar_juegos(lj)) {
				std::cout << "No se ha podido guardar el juego.\n";
			}
			else {
				std::cout << "Juego guardado correctamente.\n";
			}
		}
	}
	//limpiamos el Heap
	destruye(lj);
	destruye(lp);
	return 0;
}

//Metodo para pedir fils, cols y minas para juegos aleatorios
tJuego crearNuevoJuego() {
	int nFila, nColumna, nMinas;
	//Pedimos las filas
	std::cout << "Introduce las filas:\n";
	std::cin >> nFila;
	while (nFila < 1) {
		limpiarCin();
		std::cout << "El numero de filas no es posible.\nVuelve a introducir el numero de filas:\n";
		std::cin >> nFila;
	}
	//Pedimos las columnas
	std::cout << "Introduce las columnas:\n";
	std::cin >> nColumna;
	while (nColumna < 1) {
		limpiarCin();
		std::cout << "El numero de columnas no es posible.\nVuelve a introducir el numero de columnas:\n";
		std::cin >> nColumna;
	}
	//Pedimos las minas
	std::cout << "Introduce el numero de minas:\n";
	std::cin >> nMinas;
	while (nMinas < 1 || nMinas > nFila * nColumna) {
		limpiarCin();
		std::cout << "El numero de minas es demasiado grande.\nVuelve a introducir el numero de minas:\n";
		std::cin >> nMinas;
	}

	return crear_juego(nFila, nColumna, nMinas);
}

//En caso de que se introduzca un char no valido
void limpiarCin() {
	if (!std::cin) {
		std::cin.clear();
		std::string ignore;
		std::cin >> ignore;
	}
}