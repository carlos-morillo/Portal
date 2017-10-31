#pragma once
#include "Portal.h"
#include "Mundo.h"
#include "..\Complement\Cubo.h"
#include "..\Complement\Puerta.h"
#include "..\Complement\Boton.h"
#include "Mujer.h"
#include "Disparo.h"

class Juego
{
	float *p;
public:
	Mundo mundo;
	Mujer mujer;
	Portal *portales[2];
	Puerta *puertas[5];
	Boton *botones[5];
	Cubo *cubos[5];
	Disparo blue;
	Disparo orange;

	Juego(void);
	~Juego(void);
	void Dibuja(float alpha, float beta);
	void Mueve();
	void Relaciona();
	void Tecla(unsigned char key,float alpha, float beta, Vector3D esferic);

	friend class Relaciones;
};
