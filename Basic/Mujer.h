#pragma once
#include "Vector3D.h"
#include "ObjetoCinematico.h"

class Mujer: public ObjetoCinematico{
private:
	float altura;
	bool ocupada;
public:
	Mujer(void);
	~Mujer(void);
	void Dibuja(float alpha, float beta);
	float GetAltura();
	bool GetOcupacion();
	void SetOcupacion();
	void ResetOcupacion();
};
