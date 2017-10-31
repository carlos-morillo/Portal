#include "Pared.h"
#include "glut.h"
#include<math.h>

Pared::Pared(void)
{
	rojo=verde=azul=255;
}

Pared::Pared(float col,float xo, float yo, float zo, float xf, float yf, float zf,int n)
{
//////////////////////////////////////////////////////////////////***********************/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////CONSTRUCCION DE PAREDES////////////////////////////////////////////////////////////////////////////////////////

	color=col;

	float k=0.5;
	float Ao,Af,Bo,Bf,Co,Cf;
	//tenemos en cuenta los grosores del muro en funcion de la orientacion del mismo

	//plano y-z
	if(xo==xf){
		tipo=1;

		Ao= xo-k;	
		Af= xo+k;
		Bo= yo-k;	Bf= yf+k-1;// se resta 1 para que coincida con las dimensiones del dibujo
		Co= zo-k;	Cf= zf+k-1;
	
		if(n%2==0){//la pared por un lado del muro (Ao)
		limite1=Vector3D(Ao,Bo,Co);
		limite2=Vector3D(Ao,Bo,Cf);
		limite3=Vector3D(Ao,Bf,Cf);
		limite4=Vector3D(Ao,Bf,Co);
		}
		else{//la pared por el otro lado del muro (Af)
		limite1=Vector3D(Af,Bo,Co);
		limite2=Vector3D(Af,Bf,Co);
		limite3=Vector3D(Af,Bf,Cf);
		limite4=Vector3D(Af,Bo,Cf);
		}
	}
	//plano x-z
	if(yo==yf){
		tipo=2;

		Ao= xo-k;	Af= xf+k-1;// se resta 1 para que coincida con las dimensiones del dibujo
		Bo= yo+k;	
		Bf= yo-k;	
		Co= zo-k;	Cf= zf+k-1;	

		if(n%2==0){//la pared por un lado del muro (Bo)
		limite1=Vector3D(Ao,Bo,Co);
		limite2=Vector3D(Ao,Bo,Cf);
		limite3=Vector3D(Af,Bo,Cf);
		limite4=Vector3D(Af,Bo,Co);
		}
		else{//la pared por el otro lado del muro (Bf)
		limite1=Vector3D(Ao,Bf,Co);
		limite2=Vector3D(Ao,Bf,Cf);
		limite3=Vector3D(Af,Bf,Cf);
		limite4=Vector3D(Af,Bf,Co);
		}
	}
	//plano x-y
	if(zo==zf){
		tipo=3;

		Ao= xo-k;	Af= xf+k-1; // se resta 1 para que coincida con las dimensiones del dibujo
		Bo= yo-k;	Bf= yf+k-1;
		Co= zo+k;	
		Cf= zo-k;	

		if(n%2==0){//la pared por un lado del muro (Co)
		limite1=Vector3D(Ao,Bo,Co);
		limite2=Vector3D(Ao,Bf,Co);
		limite3=Vector3D(Af,Bf,Co);
		limite4=Vector3D(Af,Bo,Co);
		}
		else{//la pared por el otro lado del muro (Cf)
		limite1=Vector3D(Ao,Bo,Cf);
		limite2=Vector3D(Ao,Bf,Cf);
		limite3=Vector3D(Af,Bf,Cf);
		limite4=Vector3D(Af,Bo,Cf);
		}
	}
}
//////////////////////////////////////////////////////////////////FIN CONSTRUCCION DE PAREDES/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Pared::~Pared(void)
{}

void Pared::setPos(Vector3D pos,int tip)
{
	float largo=0.9,ancho=0.6,altura=2;
	switch(tip){
		case 1: //plano Y-Z portal
			limite1=Vector3D(pos.x , pos.y-largo , pos.z-ancho);
			limite2=Vector3D(pos.x , pos.y+largo , pos.z-ancho);
			limite3=Vector3D(pos.x , pos.y+largo , pos.z+ancho);
			limite4=Vector3D(pos.x , pos.y-largo , pos.z+ancho);
			break;
		case 2: //plano X-Z portal
			limite1=Vector3D(pos.x-largo , pos.y , pos.z-ancho);
			limite2=Vector3D(pos.x-largo , pos.y , pos.z+ancho);
			limite3=Vector3D(pos.x+largo , pos.y , pos.z+ancho);
			limite4=Vector3D(pos.x+largo , pos.y , pos.z-ancho);
			break;
		case 3: //plano X-Y portal
			limite1=Vector3D(pos.x-ancho , pos.y-largo , pos.z);
			limite2=Vector3D(pos.x-ancho , pos.y+largo , pos.z);
			limite3=Vector3D(pos.x+ancho , pos.y+largo , pos.z);
			limite4=Vector3D(pos.x+ancho , pos.y-largo , pos.z);
			break;
		case 4: //Boton
			limite1=Vector3D(pos.x-ancho , pos.y+0.8 , pos.z-ancho);
			limite2=Vector3D(pos.x-ancho , pos.y+0.8 , pos.z+ancho);
			limite3=Vector3D(pos.x+ancho , pos.y+0.8 , pos.z+ancho);
			limite4=Vector3D(pos.x+ancho , pos.y+0.8 , pos.z-ancho);
			break;
		case 5: //plano Y-Z puerta
			tipo=5;
			limite1=Vector3D(pos.x , pos.y+0.5 , pos.z);
			limite2=Vector3D(pos.x , pos.y+altura+0.5 , pos.z);
			limite3=Vector3D(pos.x , pos.y+altura+0.5 , pos.z+altura);
			limite4=Vector3D(pos.x , pos.y+0.5 , pos.z+altura);
			break;
		case 6: //plano X-Y puerta
			tipo=6;
			limite1=Vector3D(pos.x , pos.y+0.5 , pos.z);
			limite2=Vector3D(pos.x , pos.y+altura+0.5 , pos.z);
			limite3=Vector3D(pos.x+altura , pos.y+altura+0.5 , pos.z);
			limite4=Vector3D(pos.x+altura , pos.y+0.5 , pos.z);
			break;
	}
}

void Pared::Dibuja(float r,float g,float b)
{
	glDisable(GL_LIGHTING); 
	glColor3ub(r,g,b);
	glBegin(GL_POLYGON);
	glVertex3d(limite1.x,limite1.y,limite1.z);
	glVertex3d(limite2.x,limite2.y,limite2.z); 
	glVertex3d(limite3.x,limite3.y,limite3.z);
	glVertex3d(limite4.x,limite4.y,limite4.z);
	glEnd(); 
	glEnable(GL_LIGHTING);
}

void Pared::setColor(float r, float g, float b)
{
	rojo=r;
	verde=g;
	azul=b;
}

float * Pared::GetParametros()
{
	float v[4];
	float x1=limite1.x,y1=limite1.y,z1=limite1.z;
	float x2=limite2.x,y2=limite2.y,z2=limite2.z;
	float x3=limite3.x,y3=limite3.y,z3=limite3.z;

	v[0]= y1*z2 - y1*z3 - y2*z1 + y2*z3 + y3*z1 - y3*z2;
	v[1]= - x1*z2 + x1*z3 + x2*z1 - x2*z3 - x3*z1 + x3*z2;
	v[2]= x3*y1 + x1*y2 - x1*y3 - x2*y1 + x2*y3 - x3*y2;
	v[3]= - x1*y2*z3 + x1*y3*z2 + x2*y1*z3 - x2*y3*z1 - x3*y1*z2 + x3*y2*z1;

	return v;
	
}

float Pared::GetDistancia(Vector3D &pto)
{
	float *v,A,B,C,D,distancia;
	v = this->GetParametros();//Objetenemos los parametros de la ecuacion del plano
	A=*v;	B=*(v+1);	C=*(v+2);	D=*(v+3);
	distancia = abs(A*pto.x + B*pto.y + C*pto.z + D)/sqrt(A*A+B*B+C*C);//ecuacion de la distancia entre plano y recta
	return distancia;
}

int Pared::GetTipo()
{
	return tipo;
}

Vector3D Pared::GetLimite(int n)
{	
	switch (n){
		case 1:
			return limite1;
		case 2:
			return limite2;
		case 3:
			return limite3;
		case 4:
			return limite4;
	}	
}

int Pared::GetColor()
{
	return color;
}