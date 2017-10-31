#pragma once
#include "Juego.h"
#include "glut.h"
#include "Vector3D.h"

class Gestor
{
protected:
	enum Estado {INICIO, JUEGO, GAMEOVER, FIN}; 
	Estado estado;
public:
	static int nivel;
	Juego *juego;
	Gestor(void);
	~Gestor(void);
	void Tecla(unsigned char key,float alpha, float beta, Vector3D esferic);
	void Mueve();
	void Dibuja(float alpha, float beta);
};
