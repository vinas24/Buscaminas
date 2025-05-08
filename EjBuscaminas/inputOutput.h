#pragma once
#include "colors.h"
#include "juego.h"
#include <iostream>
#include "listaJuegos.h"

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.
using std::istream;

istream& operator>> (istream& in, tJuego& juego);

void mostrar_cabecera();
void pedir_pos(int& fila, int& columna);
void mostrar_resultado(tJuego& j);
void mostrar_juego_consola(const tJuego& j);
bool carga_juego(tJuego& j);

//metodos de la versión 2S
bool cargar_juegos(tListaJuegos& lj);
void mostrar_juegos(tListaJuegos& lj);
bool guardar_juegos(tListaJuegos& lj);
