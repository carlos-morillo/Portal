#pragma once
#include"Juego.h"

class Relaciones
{
public:
	Relaciones(void);
	~Relaciones(void);
	static bool Choque(Pared &p, ObjetoCinematico &o);
	static int Choque(Disparo &d, Pared &p);
	static void Choque(Mundo &mundo, ObjetoCinematico &m);
	static int Choque(Disparo &d, Mundo &m);
	static bool Interaccion(Portal *p0, Portal *p1, ObjetoCinematico &m);
	static bool Activacion(Boton &b,ObjetoCinematico &o);
	static void Activacion(Boton &b,Puerta &p);
	static bool Choque(Puerta &p, ObjetoCinematico &o);	
};
