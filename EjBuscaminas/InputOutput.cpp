#include "inputOutput.h"
#include <iostream>
#include <iomanip>

const char CHAR_MINA = '*';     // Mina

void colorNumero(int numero);
void mostrarCoutSeparadorMat(int huecoCelda, const tJuego& j);
void mostrarCeldaConsola(const tTablero& t, int fila, int columna, int huecos);

istream& operator>>(istream& in, tJuego& juego) {
	int fil, col, minas;
    in >> fil >> col >> minas;
	inicializar(juego, fil, col);
    for (int i = 0; i < minas; i++) {
        in >> fil >> col;
        poner_mina(juego, fil, col);
    }
    return in;
}

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
        //si alguna mina esta descubierta
		if (mina_explotada(j)) {
			std::cout << "Has explotado\n";
		}
        //si todas las casillas no minas están descubiertas
		else if (esta_completo(j)) {
			std::cout << "Has ganado\n";
		}
	}
	else {
		std::cout << "Has abandonado\n";
	}
}

//Esta función hereda de inputOutputPintar
//hemos modificado las referencias a "tMatriz" por las de "tTablero"
//y modificado su contenido para que se pueda usar en nuestro programa
bool carga_juego(tJuego& j) {
	bool cargado = false;
	std::ifstream archivo;
    std::string fichero;
	//Pedir el nombre del fichero
	std::cout << "Introduce el nombre del fichero: ";
	std::cin >> fichero;
	archivo.open(fichero);
	if (archivo.is_open()) {
		//Usamos el operador >> para cargar el juego
		archivo >> j;
		archivo.close();
        cargado = true;
	}
	return cargado;
}

void mostrar_juego_consola(const tJuego& j) {
	if (!esta_terminado(j)) {
        mostrar_cabecera();
        //Hemos añadido esta información a la cabecera
        std::cout << "Jugadas: " << dame_num_jugadas(j) << std::endl;
        std::cout << "Minas: " << dame_num_minas(j) << std::endl;
        
	}
    std::cout << "\t  |";
    for (int col = 0; col < dame_num_columnas(j); col++) {
        std::cout << LBLUE << std::setw(N_HUECOS) << col << RESET << '|';
    }
    std::cout << std::endl;

    // mostrar separador
    mostrarCoutSeparadorMat(N_HUECOS, j);

    // mostrar tablero
    for (int f = 0; f < dame_num_filas(j); f++) {
        // mostrar numero de fila
        std::cout << "\t" << LBLUE << std::setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < dame_num_columnas(j); c++) {
            mostrarCeldaConsola(j.tablero, f, c, N_HUECOS);
            std::cout << '|';
        }
        std::cout << std::endl;

        mostrarCoutSeparadorMat(N_HUECOS, j);
    }
    std::cout << std::endl;
}

void colorNumero(int numero) {
    switch (numero)
    {
    case 1: std::cout << BLUE; break;
    case 2: std::cout << GREEN; break;
    case 3: std::cout << RED; break;
    case 4: std::cout << DBLUE; break;
    case 5: std::cout << DGREEN; break;
    case 6: std::cout << DRED; break;
    default:
        break;
    }
}

void mostrarCoutSeparadorMat(int huecoCelda, const tJuego& j) {
    std::cout << "\t -+";
    for (int col = 0; col < dame_num_columnas(j); ++col) {
        std::cout << std::setw(huecoCelda + 1) << std::setfill('-') << '+' << std::setfill(' ');
    }
    std::cout << std::endl;
}

void mostrarCeldaConsola(const tTablero& t, int fila, int columna, int huecos) {
    tCelda c = dame_celda(t, fila, columna);
    if (!es_visible(c) && !esta_marcada(c)) {
        std::cout << BG_GRAY << GRAY << std::setw(huecos) << std::setfill(' ') << ' ' << RESET;
    }
    else {
        std::cout << BG_BLACK << BLACK;
        if (!esta_marcada(c)) {
            if (dame_estado(c) == MINA) {
                std::cout << RED << std::setw(huecos) << std::setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (dame_estado(c) == VACIA) {
                    std::cout << std::setw(huecos) << std::setfill(' ') << ' ' << RESET;
                }
                else {
                    if (dame_estado(c) == NUMERO) {
                        int numero = dame_numero(c);
                        colorNumero(numero);
                        std::cout << std::setw(huecos) << std::setfill(' ') << numero << RESET;
                    }
                    else {
                        std::cout << BG_RED << RED << std::setw(huecos) << std::setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            std::cout << BG_ORANGE << ORANGE << std::setw(huecos) << std::setfill(' ') << ' ' << RESET;
        }
    }
}