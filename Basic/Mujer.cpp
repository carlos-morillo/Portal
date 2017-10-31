#include "Mujer.h"
#include "glut.h"
#include "math.h"
#include "Gestor.h"

Mujer::Mujer(void)
{
	masa=50;
	altura=1.7;
	if(Gestor::nivel==1) posicion=Vector3D(1,2,1);
	if(Gestor::nivel==2) posicion=Vector3D(15,12,11);
	if(Gestor::nivel==3) posicion=Vector3D(2,1,2);
	aceleracion.y=-9.8;
	ocupada=0;
}

Mujer::~Mujer(void)
{
}

void Mujer::Dibuja(float alpha, float beta)
{
//DIBUJA LA PISTOLA

	glPushMatrix();
	glTranslatef(posicion.x,posicion.y+altura,posicion.z);	   //lleva el origen a la posicion de la mujer

	glRotatef(alpha*180/3.1415926, 0.0, 1.0, 0.0); //esto gira el arma acorde al raton,
													//los 5 grados centran un poco mas el arma
	glRotatef(beta*180/3.1415926-90, 1.0, 0.0, 0.0); //rotamos los grados de la camara al arma en eje x	   
	
	glTranslatef(-0.35,-0.32,0.7);			 //coloca el arma en la posicion correcta referenciada a la mujer
	glColor3ub(255,255,255);				
	glutSolidSphere(0.15,50,50);			 //esfera grande

	glTranslatef(0,0.05,0.04);
	glColor3f(0,0,3);						//naranja (3.6,1.49,0), azul (0,0,3)
	GLUquadricObj *qobj;					//Codigo para hacer un cilindro alambrico
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj,GLU_LINE);
	gluCylinder(qobj,0.07,0.05,0.4,100,100);

	glTranslatef(0,0,0.35);
	glColor3f(250,250,250);
	glutSolidSphere(0.03,20,20);			//esfera pequeña

	glColor3ub(100,100,100);
	glutSolidTorus(0.02,0.05,20,20);		//toroide

	glColor3ub(100,100,100);				//cañon
	GLUquadricObj *qobj2;					
	qobj2 = gluNewQuadric();
	gluQuadricDrawStyle(qobj2,GLU_LINE);
	gluCylinder(qobj2,0.02,0.02,0.2,100,100);

	glPopMatrix();

//DIBUJA LA MIRA

	glPushMatrix();
	glTranslatef(posicion.x,posicion.y+altura,posicion.z); // situa el origen en la mujer
	
	glRotatef(alpha*180/3.1415926, 0.0, 1.0, 0.0); //esto gira la mira acorde al raton

	glRotatef(beta*180/3.1415926-90, 1.0, 0.0, 0.0); //rotamos los grados de la camara a la mira en eje x		   

	glTranslatef(0,0,1);				//coloca la mira en la posicion correcta referenciada a la mujer
	glColor3ub(255,255,255);
	glBegin(GL_LINES);
           for (float ang=0.0f; ang<3.1415926*2.0f; ang = ang + 3.1415926/2.0f )
		   {
              float x = 0.02*cos(ang);
              float y = 0.02*sin(ang);
              glVertex3f(0.0f,0.0f,0.0f);
              glVertex3f(x,y,0.0f);
           }
	glEnd();
	glPopMatrix();
}

float Mujer::GetAltura()
{
	return altura;
}

bool Mujer::GetOcupacion()
{
	return ocupada;
}

void Mujer::SetOcupacion()
{
	ocupada=1;
}

void Mujer::ResetOcupacion()
{
	ocupada=0;
}