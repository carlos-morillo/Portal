#include "Portal.h"
#include "glut.h"

Portal::Portal(void)
{}

Portal::Portal(Disparo &dis, int tip, int color)
{
	if(color==1){rojo=0;	verde=0;	azul=255;}// color==1 --> azul
	if(color==0){rojo=230;	verde=95;	azul=0;}// color==0 --> naranja
	posicion = dis.GetPos();
	tipo=tip;
	muro.setPos(posicion,tipo);
	if(tipo==1)
			normal=Vector3D(-dis.GetVel().x/10,0,0);
	if(tipo==2)
			normal=Vector3D(0,-dis.GetVel().y/10,0);
	if(tipo==3)
			normal=Vector3D(0,0,-dis.GetVel().z/10);
}

Portal::~Portal(void)
{}

void Portal::Dibuja()
{
	muro.Dibuja(rojo,verde,azul);
}

Vector3D Portal::GetPos()
{
	return this->posicion;
}

float Portal::GetDistancia(Vector3D &pto)
{
	return muro.GetDistancia(pto);
}

int Portal::GetTipo()
{
	return this->tipo;
}

Vector3D Portal::GetNormal()
{
	return this->normal;
}

Pared Portal::GetMuro()
{
	return this->muro;
}