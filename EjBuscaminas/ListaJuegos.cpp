#include "listaJuegos.h"

void redimensionar(tListaJuegos& lj);
int busqueda(tListaJuegos& lj, const tJuego& j);

void inicializar(tListaJuegos& lista_juegos) {
	lista_juegos.capacidad = MAX_JUEGOS;
	lista_juegos.cont = 0;
	lista_juegos.lista = new tPtrJuego[lista_juegos.capacidad];
}

void destruye(tListaJuegos& lista_juegos) {
	for (int i = 0; i < lista_juegos.cont; i++) {
		delete lista_juegos.lista[i];
	}
	delete[] lista_juegos.lista;
	lista_juegos.lista = nullptr;
	lista_juegos.cont = 0;
}

//inserción ordenada por dificultad de los juegos
void insertar(tListaJuegos& lista_juegos, tJuego& juego) {
	if (lista_juegos.cont == lista_juegos.capacidad) {
		redimensionar(lista_juegos);
	}
	int pos = busqueda(lista_juegos, juego);
	//Desplazamos para hacer hueco al nuevo
	for (int i = lista_juegos.cont; i > pos; i--) {
		lista_juegos.lista[i] = lista_juegos.lista[i - 1];
	}
	//insertamos el nuevo juego
	lista_juegos.lista[pos] = new tJuego(juego);
	lista_juegos.cont++;
}

int numero_juegos(const tListaJuegos &lista_juegos) {
	return lista_juegos.cont;
}
bool es_vacia(const tListaJuegos &lista_juegos) {
	return lista_juegos.cont == 0;
}

tJuego* dame_juego(tListaJuegos &lista_juegos, int pos) {
	return lista_juegos.lista[pos];
}

//suponemos que la pos está dentro del array
void eliminar(tListaJuegos& lista_juegos, int pos) {
	delete lista_juegos.lista[pos];
	//movemos todos hacia la izq para rellenar el hueco
	//creado por la eliminación
	for (int i = pos; i < lista_juegos.cont - 1; i++) {
		lista_juegos.lista[i] = lista_juegos.lista[i + 1];
	}
	lista_juegos.cont--;
}


void redimensionar(tListaJuegos& lj) {
	lj.capacidad *= 2;
	tPtrJuego* newLista = new tPtrJuego[lj.capacidad];

	for (int i = 0; i < lj.cont; i++) {
		newLista[i] = lj.lista[i];
	}
	delete[] lj.lista;
	lj.lista = newLista;
}

//Implementamos una busqueda binaria
int busqueda(tListaJuegos& lj, const tJuego& j){
	int ini = 0, fin = lj.cont;
	while (ini < fin) {
		int mid = (ini + fin) / 2;
		if (j < *lj.lista[mid]) {
			fin = mid - 1;
		}
		else {
			ini = mid + 1;
		}
	}
	return ini;

}