#include "Puerta.h"
#include "..\Basic\glut.h"

Puerta::Puerta()
{
	estado=0;
	posicion=Vector3D(5,0,1);
	tipo=6;
	muro.setPos(posicion,tipo);
}

Puerta::Puerta(Vector3D pos, int tip)
{	
	posicion=pos;
	tipo=tip;
	muro.setPos(posicion,tipo);
	estado=0;
}

Puerta::~Puerta()
{}

void Puerta::Dibuja()
{
	if(estado==0){
	glPushMatrix();
	
	glColor3ub(255,255,255);

	if(tipo==5){//en el plano Y-Z
	for(float y= posicion.y+0.5 ; y<=posicion.y+0.5+2.2 ; y+=0.3)
				for(float z=posicion.z ; z<=posicion.z+2 ; z+=0.1){
					glTranslatef(posicion.x,y,z);
					glutSolidCube(0.1);
					glTranslatef(-posicion.x,-y,-z);
				}
	
	for(float y= posicion.y+0.5 ; y<=posicion.y+0.5+2 ; y+=0.1)
				for(float z=posicion.z ; z<=posicion.z+2.2 ; z+=0.3){
					glTranslatef(posicion.x,y,z);
					glutSolidCube(0.1);
					glTranslatef(-posicion.x,-y,-z);
				}
	}

	if(tipo==6){//en el plano X-Y
	for(float y= posicion.y+0.5 ; y<posicion.y+0.5+2 ; y+=0.1)
				for(float x=posicion.x ; x<posicion.x+2.2 ; x+=0.3){
					glTranslatef(x,y,posicion.z);
					glutSolidCube(0.1);
					glTranslatef(-x,-y,-posicion.z);
				}
	for(float y= posicion.y+0.5 ; y<posicion.y+0.5+2.2 ; y+=0.3)
				for(float x=posicion.x ; x<posicion.x+2 ; x+=0.1){
					glTranslatef(x,y,posicion.z);
					glutSolidCube(0.1);
					glTranslatef(-x,-y,-posicion.z);
				}
	}
	glPopMatrix();
	}
}


