#include "Disparo.h"
#include "..\Basic\glut.h"

Disparo::Disparo(void)
{
	radio=0;
	posicion=Vector3D(0,0,0);
	velocidad=Vector3D(0,0,0);
	aceleracion=Vector3D(0,0,0);
	masa=0;
}

void Disparo::Dispara( Mujer &m, const Vector3D &e,int c)
{
	radio=0.1f;
	posicion = Vector3D(m.GetPos().x,m.GetAltura()+(m.GetPos().y),m.GetPos().z);
	direccion = Vector3D(e.x,e.y,e.z);
	velocidad = direccion.unitario()*20;
	aceleracion = Vector3D(0,0,0);

	if(c==1) //azul
	{
		rojo=0;
		verde=0;
		azul=255;
	}
	if(c==0) //naranja
	{
		rojo=230;
		verde=95;
		azul=0;
	}
}

Disparo::~Disparo(void)
{}

void Disparo::Dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x,posicion.y,posicion.z);
	glColor3ub(rojo,verde,azul);
	glutSolidSphere(radio,20,20);
	glEnd();
	glPopMatrix();
}

void Disparo::Elimina()
{}

void Disparo::SetRadio(float r)
{
	radio=r;	
}

float Disparo::GetRadio()
{
	return this->radio;
}