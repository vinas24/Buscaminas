#include "inputOutput.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::setfill;

const char CHAR_MINA = '*';     // Mina



void colorNumero(int numero) {
    switch (numero)
    {
    case 1: cout << BLUE; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << DBLUE; break;
    case 5: cout << DGREEN; break;
    case 6: cout << DRED; break;
    default:
        break;
    }
}


void mostrarCoutSeparadorMat(int huecoCelda, const tJuego& j) {
    cout << "\t -+";
    for (int col = 0; col < dame_num_columnas(j); ++col) {
        cout << setw(huecoCelda + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}


void mostrarCeldaConsola(const tTablero& t, int fila, int columna, int huecos) {
	tCelda c = dame_celda(t, fila, columna);

    if (!es_visible(c) && !esta_marcada(c)) {
        cout << BG_GRAY << GRAY << setw(huecos) << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!esta_marcada(c)) {
            if (dame_estado(c) == MINA) {
                cout << RED << setw(huecos) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (dame_estado(c) == VACIA) {
                    cout << setw(huecos) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (dame_estado(c) == NUMERO) {
                        int numero = dame_numero(c);
                        colorNumero(numero);
                        cout << setw(huecos) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(huecos) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            cout << BG_ORANGE << ORANGE << setw(huecos) << setfill(' ') << ' ' << RESET;
        }
    }
}


istream& operator>>(istream& in, tJuego& juego);

void mostrar_cabecera() {
	cout << "Buscaminas" << endl;
	cout << "----------" << endl;
}

void pedir_pos(int& fila, int& columna) {
	cout << "Introduce la fila y la columna: ";
	std::cin >> fila >> columna;
}

void mostrar_resultado(tJuego& j) {
	if (esta_terminado(j)) {
		if (mina_explotada(j)) {
			std::cout << "Has explotado\n";
		}
		else if (esta_completo(j)) {
			std::cout << "Has ganado\n";
		}
	}
	else {
		std::cout << "Has abandonado\n";
	}
}

bool carga_juego(tJuego& j) {
	//lectura de archivo y tal
	return false;
}

void mostrar_juego_consola(const tJuego& j) {
    mostrar_cabecera();
    cout << "Jugadas: " << dame_num_jugadas(j) << endl;
    cout << "Minas: " << dame_num_minas(j) << endl;
    cout << "\t  |";
    for (int col = 0; col < dame_num_columnas(j); col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrarCoutSeparadorMat(N_HUECOS, j);

    // mostrar tablero
    for (int f = 0; f < dame_num_filas(j); f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < dame_num_columnas(j); c++) {
            mostrarCeldaConsola(j.tablero, f, c, N_HUECOS);
            cout << '|';
        }
        cout << endl;

        mostrarCoutSeparadorMat(N_HUECOS, j);
    }
    cout << endl;
}