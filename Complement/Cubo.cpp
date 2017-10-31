#include "Cubo.h"
#include "math.h"
#include "..\Basic\glut.h"

Cubo::Cubo(void)
{
	posicion=Vector3D(5,3,7);
	lado=0.5;
	masa=5;
	aceleracion.y=-9.8;
	estado=0;
}

Cubo::Cubo(Vector3D pos)
{
	lado=0.5;
	masa=5;
	aceleracion.y=-9.8;
	estado=0;
	posicion=pos;
}
Cubo::~Cubo(void)
{
}

void Cubo::Dibuja(Mujer &m, float alpha, float beta)//cuando la mujer coja el cubo necesitaremos saber la posicion de la mujer para cogerlo
{
	glPushMatrix();

	//centros del cubo
	if(estado==0){
		glTranslatef(posicion.x,posicion.y,posicion.z);
	}
	if(estado==1){
		posicion=Vector3D(m.GetPos().x+2*sin(alpha),m.GetPos().y+1.2,m.GetPos().z+2*cos(alpha));
		velocidad=Vector3D(0,0,0);
		glTranslatef(m.GetPos().x,m.GetPos().y+m.GetAltura(),m.GetPos().z); // situa el origen en la mujer
		glRotatef(alpha*180/3.1415926, 0.0, 1.0, 0.0); //esto gira el cubo acorde al raton
		glRotatef(beta*180/3.1415926-90, 1.0, 0.0, 0.0); //rotamos los grados de la camara a la mira en eje x		   
		glTranslatef(0,0,2);				//coloca la mira en la posicion correcta referenciada a la mujer
	}	

	//esquinas del cubo
	{
	float i,j,k;
	i = j = k = lado*0.5*0.7; //ejes de traslacion de la posicion de las esquinas
	for(int n=0;n<2;n++){
		for(int n=0;n<2;n++){
			for(int n=0;n<2;n++){
				glTranslatef(i,j,k);
				glColor3ub(200,200,200);
				glutSolidCube(0.4*lado);
				glTranslatef(-i,-j,-k);
				i=-i;
			}
			j=-j;
		}
		k=-k;
	}
	}

	//aristas del cubo
	{
	float i,j,k;
	i = j = k = lado*0.5; //ejes de traslacion de la posicion de las aristas
	
	for(int n=0;n<2;n++){
		for(int n=0;n<2;n++){
			glTranslatef(i,j,0);
			glColor3ub(200,200,200);
			glutSolidCube(0.1*lado);
			glTranslatef(-i,-j,0);
			i=-i;
		}
		j=-j;
	}
	for(int n=0;n<2;n++){
		for(int n=0;n<2;n++){
			glTranslatef(i,0,k);
			glColor3ub(200,200,200);
			glutSolidCube(0.1*lado);
			glTranslatef(-i,0,-k);
			i=-i;
		}
		k=-k;
	}
	for(int n=0;n<2;n++){
		for(int n=0;n<2;n++){
			glTranslatef(0,j,k);
			glColor3ub(200,200,200);
			glutSolidCube(0.1*lado);
			glTranslatef(0,-j,-k);
			j=-j;
		}
		k=-k;
	}

	}

	//cubo principal
	glColor3ub(100,100,100);
	glutSolidCube(lado);
	glPopMatrix();
}

void Cubo::Coger(Mujer &m){

	if(estado==0 && m.GetOcupacion()==0)
	{
		estado=1;
		posicion=m.GetPos();
		m.SetOcupacion();
	}
	else if(estado==1)
	{
		estado=0;
		m.ResetOcupacion();
	}
}

float Cubo::Distancia(Vector3D &pto)
{
	return abs((pto-posicion).modulo());
}



