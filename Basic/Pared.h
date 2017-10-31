#pragma once
#include "Vector3D.h"

class Pared
{
	Vector3D limite1;
	Vector3D limite2;
	Vector3D limite3;
	Vector3D limite4;
	int tipo;//define el tipo de pared, si es del plano X-Y, Y-Z o X-Z o es pared de un boton o una puerta
	float rojo;
	float verde;
	float azul;
	int color;
public:
	Pared(void);
	Pared(float color,float xo, float yo, float zo, float xf, float yf, float zf,int n);
	~Pared(void);
	void Dibuja(float r,float g, float b);
	void setPos(Vector3D pos,  int tip);
	void setColor(float r, float g, float b);
	float *GetParametros();
	float GetDistancia(Vector3D &pto);
	int GetTipo();
	int GetColor();
	Vector3D GetLimite(int n);
};
