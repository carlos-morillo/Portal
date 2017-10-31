#pragma once
#include "Vector3D.h"
#include "Mujer.h"

class Disparo:public ObjetoCinematico
{
	Vector3D direccion;
	float radio;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
public:
	Disparo(void);
	~Disparo(void);
	void Dispara( Mujer &m,const Vector3D &e,int c);
	void Dibuja();
	void Elimina(void);
	float GetRadio();
	void SetRadio(float r);
};
