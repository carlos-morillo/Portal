#include "Juego.h"
#include "math.h"
#include "Relaciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Gestor.h"
using namespace std;


Juego::Juego(void){
	portales[0]=0;
	portales[1]=0;
	for(int i=0;i<5;i++){
		puertas[i]=0;
		botones[i]=0;
		cubos[i]=0;
	}


/////////////////////////////////////////////////*****************/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CODIGO DE FICHERO ///////////cubos/////////////////////////////////////////////////////////////////////////////
	int i = 0,cap=0;

	FILE *cub;
	if(Gestor::nivel==1) cub = fopen("cubos1.txt","r");
	if(Gestor::nivel==2) cub = fopen("cubos2.txt","r");
	if(Gestor::nivel==3) cub = fopen("cubos3.txt","r");

	//cub = fopen("cubos.txt","r");

	if (cub==NULL){	cout<<"fallo"<<endl;}

	p = new float[3*sizeof(float)];

	while(feof(cub)==0)//recorremos el fichero mientras no lleguemos al final del fichero
	{	
		int j;
		j=i+3;

		cap+=3;

		for( i;i<j;i++) // i--> posicion del vector p de almacenamiento de coordenadas
						// j--> el bucle acaba cuando la i llega a j (final de la linea)
		{
			fscanf(cub,"%f",&(*(p+i)));
		}
	}

	fclose(cub);
	cout<<"CERRADO CUBOS"<<endl<<endl;

//////////////////////////////////////////////////////////////////FIN DEL FICHERO/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////*******************/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////CREAMOS LOS CUBOS////////////////////////////////////////////////////////////////////////////////////////

	for(int m=0, n=0;n<cap;n+=3){//Bucle que recorre todas las lineas del archivo (barrido vertical)
		cubos[m++]= new Cubo(Vector3D(*(p+n),*(p+n+1),*(p+n+2)));
	}

//////////////////////////////////////////////////////////////////FIN DE CREACION DE CUBOS/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	
/////////////////////////////////////////////////*****************/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CODIGO DE FICHERO ///////////puertas/////////////////////////////////////////////////////////////////////////////
	i = 0;
	cap=0;

	FILE *puer;

	if(Gestor::nivel==1) puer = fopen("puertas1.txt","r");
	if(Gestor::nivel==2) puer = fopen("puertas2.txt","r");
	if(Gestor::nivel==3) puer = fopen("puertas3.txt","r");

	//puer = fopen("puertas.txt","r");

	if (puer==NULL){	cout<<"fallo"<<endl;}

	p = new float[4*sizeof(float)];

	while(feof(puer)==0)//recorremos el fichero mientras no lleguemos al final del fichero
	{	
		int j;
		j=i+4;

		cap+=4;

		for( i;i<j;i++) // i--> posicion del vector p de almacenamiento de coordenadas
						// j--> el bucle acaba cuando la i llega a j (final de la linea)
		{
			fscanf(puer,"%f",&(*(p+i)));
		}
	}

	fclose(puer);
	cout<<"CERRADO PUERTAS"<<endl<<endl;

//////////////////////////////////////////////////////////////////FIN DEL FICHERO/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////*******************/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////CREAMOS LAS PUERTAS///////////////////////////////////////////////////////////////////////////////////////

	for(int m=0, n=0;n<cap;n+=4){//Bucle que recorre todas las lineas del archivo (barrido vertical)
		puertas[m++]= new Puerta(Vector3D(*(p+n),*(p+n+1),*(p+n+2)),*(p+n+3));
	}

//////////////////////////////////////////////////////////////////FIN DE CREACION DE PUERTAS/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////*****************/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CODIGO DE FICHERO ///////////botones/////////////////////////////////////////////////////////////////////////////
	i = 0;
	cap=0;

	FILE *bot;

	if(Gestor::nivel==1) bot = fopen("botones1.txt","r");
	if(Gestor::nivel==2) bot = fopen("botones2.txt","r");
	if(Gestor::nivel==3) bot = fopen("botones3.txt","r");

	//bot = fopen("botones.txt","r");

	if (bot==NULL){	cout<<"fallo"<<endl;}

	p = new float[3*sizeof(float)];

	while(feof(bot)==0)//recorremos el fichero mientras no lleguemos al final del fichero
	{	
		int j;
		j=i+3;

		cap+=3;

		for( i;i<j;i++) // i--> posicion del vector p de almacenamiento de coordenadas
						// j--> el bucle acaba cuando la i llega a j (final de la linea)
		{
			fscanf(bot,"%f",&(*(p+i)));
		}
	}

	fclose(bot);
	cout<<"CERRADO BOTONES"<<endl<<endl;

//////////////////////////////////////////////////////////////////FIN DEL FICHERO/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////*******************/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////CREAMOS LOS BOTONES///////////////////////////////////////////////////////////////////////////////////////

	for(int m=0, n=0;n<cap;n+=3){//Bucle que recorre todas las lineas del archivo (barrido vertical)
		botones[m++]= new Boton(Vector3D(*(p+n),*(p+n+1),*(p+n+2)));
	}

//////////////////////////////////////////////////////////////////FIN DE CREACION DE BOTONES/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

Juego::~Juego(void)
{
	delete portales[0];
	delete portales[1];
	for(int i=0;i<5;i++){
		delete puertas[i];
		delete botones[i];
		delete cubos[i];
	}
}

void Juego::Dibuja(float alpha, float beta)
{

	for(int i=0;i<5;i++){
		if(puertas[i]!=NULL)puertas[i]->Dibuja();
		if(botones[i]!=NULL)botones[i]->Dibuja();
		if(cubos[i]!=NULL)cubos[i]->Dibuja(mujer,alpha,beta);
	}
	mundo.Dibuja();
	mujer.Dibuja(alpha, beta);
	if(portales[0]!=NULL)
		portales[0]->Dibuja();
	if(portales[1]!=NULL)
		portales[1]->Dibuja();
	orange.Dibuja();
	blue.Dibuja();
}

void Juego::Mueve()
{
	mujer.Mueve(0.025f);
	blue.Mueve(0.025f);
	orange.Mueve(0.025f);
	for(int i=0;i<5;i++){
		if(cubos[i]!=NULL)cubos[i]->Mueve(0.025f);
	}
}

void Juego::Relaciona()
{
	int tipo_b,tipo_o,i;

	Relaciones::Choque(mundo,mujer);
	for(int i=0;i<5;i++){
		if(cubos[i]!=NULL)
			Relaciones::Choque(mundo,*cubos[i]);	
	}
	for(int i=0;i<5;i++){
		if(puertas[i]!=NULL)
			if(puertas[i]->GetEstado()==0){
				Relaciones::Choque(*puertas[i],mujer);
				Relaciones::Choque(*puertas[i],blue);
				Relaciones::Choque(*puertas[i],orange);
			}
	}
	for(int i=0;i<5;i++){
			if(botones[i]!=NULL && puertas[i]!=NULL)
				Relaciones::Activacion(*botones[i],*puertas[i]);	
	}
	
	tipo_b = Relaciones::Choque(blue,mundo);//comprobamos los choques
	if(tipo_b){	//si impacta la esfera azul se crea un portal azul
		delete portales[0];
		portales[0]=new Portal(blue,tipo_b,1);// posicion,orientacion,color
	}
	
	tipo_o = Relaciones::Choque(orange,mundo);//comprobamos los choques
	if(tipo_o!=0){//si impacta la esfera naranja se crea un portal naranja
		delete portales[1];
		portales[1]=new Portal(orange,tipo_o,0);// posicion,orientacion,color
	}

	Relaciones::Interaccion(portales[0], portales[1], mujer);
	for(int i=0;i<5;i++){
		if(cubos[i]!=NULL)
				Relaciones::Interaccion(portales[0], portales[1], *cubos[i]);
	}
	
	for(int i=0;i<5;i++){
		if(botones[i]!=NULL){
			if(Relaciones::Activacion(*botones[i],mujer))
				botones[i]->Activar();
			else
				for(int j=0;j<5;j++)
					if(cubos[j]!=NULL)
						if(Relaciones::Activacion(*botones[i],*cubos[j])){
							botones[i]->Activar();
							break;
						}
						else 
							botones[i]->Desactivar();
		}
	}
	
	for(int i=0;i<5;i++){
		if(botones[i]!=NULL)
			Relaciones::Activacion(*botones[i],blue);
	}
	for(int i=0;i<5;i++){
		if(botones[i]!=NULL)
			Relaciones::Activacion(*botones[i],orange);
	}

}


void Juego::Tecla(unsigned char key,float alpha, float beta, Vector3D esferic)
{
	float VEL=5;

	if(key=='a'){
		mujer.SetVel(VEL*cos(alpha),mujer.GetVel().y,-VEL*sin(alpha));
	}
	if(key=='s'){
		mujer.SetVel(-VEL*sin(alpha),mujer.GetVel().y,-VEL*cos(alpha));
	}
	if(key=='d'){
		mujer.SetVel(-VEL*cos(alpha),mujer.GetVel().y,VEL*sin(alpha));
	}
	if(key=='w') {
		mujer.SetVel(VEL*sin(alpha),mujer.GetVel().y,VEL*cos(alpha));
	}
	if(key==' ') {
		mujer.SetVel(mujer.GetVel().x,VEL,mujer.GetVel().z);//salto
	}
	if(key=='p') { //PARA SALIR DEL PROGRAMA DE MANERA SENCILLA
		exit(0);
	}
	if(key=='e') { 
		float d[5];
		float menor=3;
		int ind=5;
		for(int j=0;j<5;j++) d[j]=3;
		for(int i=0;i<5;i++){
			if(cubos[i]!=NULL){
				if(cubos[i]->Distancia(mujer.GetPos())<3)
				{
					d[i]=cubos[i]->Distancia(mujer.GetPos());
			
					if(d[0]<d[1] && d[0]<d[2] && d[0]<d[3] && d[0]<d[4]) ind=0;
					if(d[1]<d[0] && d[1]<d[2] && d[1]<d[3] && d[1]<d[4]) ind=1;
					if(d[2]<d[1] && d[2]<d[0] && d[2]<d[3] && d[2]<d[4]) ind=2;
					if(d[3]<d[1] && d[3]<d[2] && d[3]<d[0] && d[3]<d[4]) ind=3;
					if(d[4]<d[1] && d[4]<d[2] && d[4]<d[3] && d[4]<d[0]) ind=4;
					cubos[ind]->Coger(mujer);
				}
			}
		}	
	}
	
}
