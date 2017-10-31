#include "Mundo.h"
#include "math.h"
#include "Relaciones.h"


//////////////////////////////// LIBRERIAS PARA PONER EL MAPA ///////////////////////////////////////////////
#include <memory.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Gestor.h"
#include "glut.h" //si no se pone esta libreria despues de la stdlib, da error de exit 

Mundo::Mundo(void)
{
/////////////////////////////////////////////////*****************/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CODIGO DE FICHERO////////////////////////////////////////////////////////////////////////////////////////
	capacidad = 0;
	int i = 0;

	FILE *mapa;

	if(Gestor::nivel==1) mapa = fopen("mapa1.txt","r");
	if(Gestor::nivel==2) mapa = fopen("mapa2.txt","r");
	if(Gestor::nivel==3) mapa = fopen("mapa3.txt","r");

	//mapa = fopen("mapa3.txt","r");

	if (mapa==NULL)
	{
		cout<<"fallo"<<endl;
	}

	p = new int[capacidad];

	while(feof(mapa)==0)//recorremos el fichero mientras no lleguemos al final del fichero
	{	
		int j;
		j=i+LONGITUD;

		//ASIGNACION DINAMICA DE MEMORIA:
		capacidad+=LONGITUD;
		aux = new int[capacidad];
		if (aux == NULL)
		{
			printf("ERROR DE RESERVA DE MEMORIA AL CARGAR EL MAPA");
			delete[]p;
		}
		memcpy(aux,p,(capacidad)*sizeof(int));
		delete[]p;
		p=aux;
		//FIN DE ASIGNACION DINAMICA DE MEMORIA

		for( i;i<j;i++) // i--> posicion del vector p de almacenamiento de coordenadas
						// j--> j=i+LONGITUD --> el bucle acaba cuando la i llega a j (final de la linea)
		{
			fscanf(mapa,"%d",&(*(p+i)));
		}


		//PARA VISUALIZAR LAS COORDENADAS QUE SE COJEN DEL MAPA
		cout<<endl<<endl<<capacidad<<endl<<endl; //CANTIDAD DE COORDENADAS
		for(int n=0;n<capacidad;n++)
		{
			cout<<(*(p+n))<<endl;
		}
	}

	fclose(mapa);
	cout<<"CERRADO"<<endl<<endl;

//////////////////////////////////////////////////////////////////FIN DEL FICHERO/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


////////////////////////////////////////////////////*******************/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////CREAMOS LAS PAREDES////////////////////////////////////////////////////////////////////////////////////////

	for(int num=0, n=0;n<capacidad;n+=LONGITUD){//Bucle que recorre todas las lineas del archivo (barrido vertical)
	// vamos a crear por cada linea del archivo (que es un muro con grosor en el juego) dos paredes:
	listaparedes[num++]= new Pared(*(p+n),*(p+n+1),*(p+n+2),*(p+n+3),*(p+n+4),*(p+n+5),*(p+n+6),num);
	listaparedes[num++]= new Pared(*(p+n),*(p+n+1),*(p+n+2),*(p+n+3),*(p+n+4),*(p+n+5),*(p+n+6),num);
	}

//////////////////////////////////////////////////////////////////FIN DE CREACION DE PAREDES/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

Mundo::~Mundo(void)
{
}

void Mundo::Dibuja()
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////CODIGO DE DIBUJO PARA CUBOS////////////////////////////////////////////////////////////////////////////////////////
	
	//Aqui dibujaremos los muros que componen el mapa:

	glPushMatrix();

	//glDisable(GL_LIGHTING);
	for(int n=0;n<capacidad;n+=LONGITUD){//Bucle que recorre todas las lineas del archivo (barrido vertical)
		//color
		if(*(p+n)==0)glColor3ub(17,142,25);
		if(*(p+n)==1)glColor3ub(200,200,200);
		
		int x,y,z;
		float tamagno=1;
		//plano y-z
		if(*(p+n+1)==*(p+n+4)){
		for( y=*(p+n+2);y<*(p+n+5);y+=tamagno)
				for( z=*(p+n+3);z<*(p+n+6);z+=tamagno){
					glTranslatef(*(p+n+1),y,z);
					glutSolidCube(tamagno);
					glTranslatef(-(*(p+n+1)),-y,-z);
				}
		}
		//plano x-z
		if(*(p+n+2)==*(p+n+5)){
			for( x=*(p+n+1);x<*(p+n+4);x+=tamagno)
				for( z=*(p+n+3);z<*(p+n+6);z+=tamagno){
					glTranslatef(x,*(p+n+2),z);
					glutSolidCube(tamagno);
					glTranslatef(-x,-(*(p+n+2)),-z);
				}
		}
		//plano x-y
		if(*(p+n+3)==*(p+n+6)){
			for( x=*(p+n+1);x<*(p+n+4);x+=tamagno)
				for( y=*(p+n+2);y<*(p+n+5);y+=tamagno){
					glTranslatef(x,y,*(p+n+3));
					glutSolidCube(tamagno);
					glTranslatef(-x,-y,-(*(p+n+3)));
				}
		}
	//glEnable(GL_LIGHTING);
	glPopMatrix();
//////////////////////////////////////////////////////////////////FIN/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
}

int Mundo::GetNumParedes()
{
	return ((capacidad/LONGITUD)*2);
}

Pared * Mundo::GetListaParedes(int i)
{
	return listaparedes[i];
}