#pragma once
#include "juego.h"
#include "inputOutput_pintar.h"

using std::istream;

istream& operator>> (istream& in, tJuego& juego);

void mostrar_cabecera();
void pedir_pos(int& fila, int& columna);
void mostrar_resultado(tJuego& j);
void mostrar_juego_consola(tJuego& j);
bool carga_juego(tJuego& j);
