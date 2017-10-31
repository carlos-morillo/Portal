#pragma once
#include "Pared.h"
#include "Mujer.h"
#include "Disparo.h"

#define LONGITUD 7

class Mundo
{
	Pared *listaparedes[500];//punteros a las paredes que hay en el mundo
	long capacidad;//maximo espacio reservado de memoria	(ira cambiando gracias a la asignacion dinamica)
	int *p,*aux; //almacenes de coordenadas del fichero
public:
	Mundo(void);
	~Mundo(void);
	void Dibuja();
	int GetNumParedes();
	Pared *GetListaParedes(int i);
};
