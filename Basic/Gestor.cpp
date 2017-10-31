#include "Gestor.h"
#include "OpenGL.h"

int Gestor::nivel=1;

Gestor::Gestor(void)
{
	estado=INICIO;
	delete juego;
	juego=new Juego;
}

Gestor::~Gestor(void)
{
	delete juego;
}

void Gestor::Dibuja(float alpha, float beta)
{
	if(estado==INICIO) 
	{
		OpenGL::Print("L - Empezar     P - Salir",550,325,0,255,0);
		OpenGL::Print("Bienvenido a APERTURE LABORATORIES. Usted es un sujeto de prueba y debera hacer lo posible para salir de la sala.",200,100,255,255,255);
		OpenGL::Print("Para ello dispone de de una pistola con la que puede realizar disparos. Ayudese de los portales asi como su ingenio le permita.",180,120,255,255,255);
		nivel=1;
		delete juego;
		juego=new Juego;
	}

	else if(estado==JUEGO) 
	{
		if(nivel==1 && juego->mujer.GetPos().z > 23)
		{
			nivel=2;
			delete juego;
			juego=new Juego;
		}
		if(nivel==2 && juego->mujer.GetPos().z > 103)
		{
			nivel=3;
			delete juego;
			juego=new Juego;
		}
		if(nivel==3 && juego->mujer.GetPos().z > 15)
		{
			estado=FIN;
		}
		juego->Dibuja(alpha, beta);
	}

	else if(estado==GAMEOVER)
	{
		OpenGL::Print("GAMEOVER",650,325,0,255,0);
		OpenGL::Print("Pulse C para continuar",620,350,255,255,255);
	}

	else if(estado==FIN) 
	{
		OpenGL::Print("FIN DEL JUEGO - Has superado todos los niveles",450,325,0,255,0); 
		OpenGL::Print("Pulse C para continuar",620,350,255,255,255);
	}
}

void Gestor::Tecla(unsigned char key,float alpha, float beta, Vector3D esferic)
{
	if(estado==INICIO)
	{
		if(key=='l') estado=JUEGO;
		if(key=='p') exit(0);
	} 
	else if(estado==JUEGO) 
	{ 
		juego->Tecla(key,alpha,beta,esferic);
	} 
	else if(estado==GAMEOVER)
	{ 
		if(key=='c') estado=INICIO; 
	} 
	else if(estado==FIN)
	{ 
		if(key=='c') estado=INICIO;
	}
}

void Gestor::Mueve()
{
	if(estado==JUEGO)
	{
		juego->Mueve();
		juego->Relaciona();
		if(nivel==5)
			estado=FIN;
		if(juego->mujer.GetVel().y < -30)
			estado=GAMEOVER;
	}
}
