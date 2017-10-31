#pragma once
#include "Disparo.h"
#include "Pared.h"
#include "Vector3D.h"

class Portal
{
	Vector3D posicion;
	Pared muro;
	Vector3D normal;
	int tipo;	
	float rojo;
	float verde;
	float azul;
public:
	Portal(void);
	Portal(Disparo &dis, int tip,int color);
	~Portal(void);
	void Dibuja();
	Vector3D GetPos();
	float GetDistancia(Vector3D &pto);
	int GetTipo();
	Vector3D GetNormal();
	Pared GetMuro();
};
