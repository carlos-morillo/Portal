#pragma once
#include "..\Basic\Mujer.h"

class Cubo:public ObjetoCinematico
{
	float lado;
	bool estado;
public:
	Cubo(void);
	~Cubo(void);
	Cubo(Vector3D pos);
	void Dibuja(Mujer &m,float apha,float beta);
	void Coger(Mujer &m);
	float Distancia(Vector3D &pto);
};
