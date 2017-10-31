#pragma once
#include "Vector3D.h"

class ObjetoCinematico
{
protected:
	Vector3D posicion;
	Vector3D velocidad;
	Vector3D aceleracion;
	int masa;
public:
	ObjetoCinematico(void);
	~ObjetoCinematico(void);
	 void Mueve(float t);
	 void SetVel(float vx, float vy, float vz);
	 void SetPos(float vx, float vy, float vz);
	 Vector3D GetPos();
	 Vector3D GetVel();
	 Vector3D GetAc();
	 int GetMasa();
};
