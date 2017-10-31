#include "Boton.h"
#include "..\Basic\glut.h"

Boton::Boton(void)
{
	posicion=Vector3D(5,0,5);
	estado=0;
	muro.setPos(posicion,4);
}

Boton::Boton(Vector3D pos)
{
	posicion=pos;
	estado=0;
	muro.setPos(posicion,4);
}

Boton::~Boton(void)
{
}

void Boton::Dibuja(void)
{
	glPushMatrix();
	
	if(estado==0)glColor3ub(255,0,0);
	if(estado==1)glColor3ub(0,255,0);

	for(float x= (posicion.x-0.6) ; x<(posicion.x+0.6) ; x+=0.1)
				for(float z=(posicion.z-0.6) ; z<(posicion.z+0.6) ; z+=0.1){
					glTranslatef(x,posicion.y+0.75,z);
					glutSolidCube(0.1);
					glTranslatef(-x,-posicion.y-0.75,-z);
				}

	glColor3ub(75,75,75);
	for(float x= (posicion.x-0.8) ; x<(posicion.x+0.8) ; x+=0.2)
				for(float z=(posicion.z-0.8) ; z<(posicion.z+0.8) ; z+=0.2){
					glTranslatef(x,posicion.y+0.6,z);
					glutSolidCube(0.2);
					glTranslatef(-x,-posicion.y-0.6,-z);
				}
	glPopMatrix();
}

