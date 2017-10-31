#define PI 3.1415926
#include<windows.h>
#include "glut.h"
#include "math.h"
#include <stdio.h>
#include "Juego.h"
#include "Gestor.h"


//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void Redimensionar(int sx, int sy);//sera llamada cuando se modifique el tamaño de la ventana
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void keyUp(unsigned char key, int x, int y);
void mouseB(int button,int state,int x,int y);
void mouseM (int x, int y);


Vector3D esferic;
//Juego juego;
Gestor gestor;

float alpha;
float beta;
float formato=(float)16/9;

void Redimensionar(int sx, int sy) 
{ 
 glViewport(0, 0, sx, sy);
 formato = (float) sx / (float) sy;
}


int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1300,650);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Portal");
	glutReshapeFunc(Redimensionar); //llama a la funcion redimensionar para no perder las proporciones del juego
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);//elimina el cursor de la pantalla

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, formato, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouseB);
	glutPassiveMotionFunc(mouseM);
	
	alpha=beta=0.0f;

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}
void keyUp (unsigned char key, int x, int y)
{
	if(key=='a'||key=='s'||key=='d'||key=='w') gestor.juego->mujer.SetVel(0.0,0.0,0.0);
}
void mouseB(int button,int state,int x,int y)
{	
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		gestor.juego->blue.Dispara(gestor.juego->mujer,esferic,1);
	}
	if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) {
		gestor.juego->orange.Dispara(gestor.juego->mujer,esferic,0);
	
	}
}
void mouseM (int x, int y)
{

	alpha=(-18.0/65.0*x+180)*PI/180;   //con esta ecuacion se puede girar desde 0 a 360 grados
	beta=(90.0/325.0*y)*PI/180;   //y con esta gira de -90 a 90, no gira sobre si mismo
   
	esferic.x = 2*(float)sin(beta)*sin(alpha);	//coordenadas esféricas para situar el punto al que
	esferic.y = 2*(float)cos(beta);				//mirará la cámara si el origen es (0,0,0)
	esferic.z = 2*(float)sin(beta)*cos(alpha);
	printf("x=%d \t y=%d\n alpha:%f\tbeta:%f\n%f\t%f\t%f\n\n\n",x,y,alpha*180/PI,beta*180/PI,esferic.x,esferic.y,esferic.z);
	
}

void OnDraw(void)
{
	//Borrado de la pantalla	
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
	gluLookAt(gestor.juego->mujer.GetPos().x, gestor.juego->mujer.GetPos().y+gestor.juego->mujer.GetAltura(), gestor.juego->mujer.GetPos().z,  // posicion del ojo
		gestor.juego->mujer.GetPos().x+esferic.x,gestor.juego->mujer.GetPos().y+gestor.juego->mujer.GetAltura()+esferic.y, gestor.juego->mujer.GetPos().z+esferic.z,  // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	//aqui es donde hay que poner el código de dibujo
	//juego.Dibuja(alpha,beta);
	gestor.Dibuja(alpha,beta);



	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//juego.Tecla(key,alpha,beta,esferic);
	gestor.Tecla(key,alpha,beta,esferic);
	glutPostRedisplay();
}

void OnTimer(int value)
{
	gestor.Mueve();
	//juego.Mueve();
	//juego.Relaciona();
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}