#include "inputOutput.h"
#include <iostream>

istream& operator>> (istream& in, tJuego& juego);

void mostrar_cabecera() {
	std::cout << "Buscaminas" << std::endl;
	std::cout << "----------" << std::endl;
}
void pedir_pos(int& fila, int& columna) {
	std::cout << "Introduce la fila y la columna: ";
	std::cin >> fila >> columna;
}
void mostrar_resultado(tJuego& j) {
	if (esta_terminado(j)) {
		if (mina_explotada(j)) {
			std::cout << "Has explotado\n";
		}
		else {
			std::cout << "Has ganado\n";
		}
	}
}
void mostrar_juego_consola(tJuego& j) {
	mostrar_cabecera();
	mostarTablero(j);
}

bool carga_juego(tJuego& j) {
	//lectura de archivo y tal
	return false;
}