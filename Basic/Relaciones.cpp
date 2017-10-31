#include"Relaciones.h"
#include"Juego.h"
#include <iostream>
using namespace std;

Relaciones::Relaciones(void)
{}

Relaciones::~Relaciones(void)
{}

bool Relaciones::Choque(Pared &p, ObjetoCinematico &o)
{
	float distancia;
	distancia=p.GetDistancia(o.GetPos());//calculamos la distancia ente la pared y la mujer

	if(distancia<0.3){	
		Vector3D pos = o.GetPos();	//cogemos la posicion de la mujer
		Vector3D lim1 = p.GetLimite(1);	//cogemos los limites superior e inferior de la pared
		Vector3D lim3 = p.GetLimite(3);
		switch (p.GetTipo()){
			case 1:	//el plano en Y-Z
				if(pos.y>lim1.y && pos.y<lim3.y && pos.z>lim1.z && pos.z<lim3.z)
				{
					if(o.GetVel().x < 0)
					o.SetPos(lim1.x+0.3F,o.GetPos().y,o.GetPos().z);

					if(o.GetVel().x > 0)
					o.SetPos(lim1.x-0.3F,o.GetPos().y,o.GetPos().z);
				}
				break;
			case 2:	//el plano en X-Z
				if(pos.x>lim1.x && pos.x<lim3.x && pos.z>lim1.z && pos.z<lim3.z)
				{
					if(o.GetVel().y < 0){
					o.SetPos(o.GetPos().x,lim1.y+0.3F,o.GetPos().z);
					o.SetVel(o.GetVel().x,0,o.GetVel().z);}
					if(o.GetVel().y > 0){
					o.SetPos(o.GetPos().x,lim1.y-0.3F,o.GetPos().z);
					o.SetVel(o.GetVel().x,0,o.GetVel().z);}
				}
				break;
			case 3:	//el plano en X-Y
				if(pos.y>lim1.y && pos.y<lim3.y && pos.x>lim1.x && pos.x<lim3.x)
				{
					if(o.GetVel().z < 0)
					o.SetPos(o.GetPos().x,o.GetPos().y,lim1.z+0.3F);

					if(o.GetVel().z > 0)
					o.SetPos(o.GetPos().x,o.GetPos().y,lim1.z-0.3F);
				}
				break;		
		}
		return 1;
	}
	else return 0;
}

int Relaciones::Choque(Disparo &d, Pared &p)
{
	float distancia;
	distancia=p.GetDistancia(d.GetPos());//calculamos la distancia ente la pared y el disparo
	
	//vamos a comprobar que el disparo impacta en la zona del plano limitada por los limites de la pared
	if(distancia<0.4 && d.GetRadio()!=0){	
		Vector3D pos = d.GetPos();	//cogemos la posicion del disparo
		Vector3D lim1 = p.GetLimite(1);	//cogemos los limites superior e inferior de la pared
		Vector3D lim3 = p.GetLimite(3);
		switch (p.GetTipo()){
			case 1:	//el plano en Y-Z
				if(pos.y>lim1.y && pos.y<lim3.y && pos.z>lim1.z && pos.z<lim3.z){
					if((p.GetColor()==1)){
					d.SetRadio(0);
					return 1;
					}
					if((p.GetColor()==0))
					{
						d.SetVel(0.0,0.0,0.0);
						d.SetRadio(0);
					}
				}
				break;
			case 2:	//el plano en X-Z
				if(pos.x>lim1.x && pos.x<lim3.x && pos.z>lim1.z && pos.z<lim3.z){
					if((p.GetColor()==1))
					{
					d.SetRadio(0);
					return 2;
					}
					if((p.GetColor()==0))
					{
						d.SetVel(0.0,0.0,0.0);
						d.SetRadio(0);
					}
				}
				break;
			case 3:	//el plano en X-Y
				if(pos.y>lim1.y && pos.y<lim3.y && pos.x>lim1.x && pos.x<lim3.x){
					if((p.GetColor()==1)){
					d.SetRadio(0);
					return 3;
					}
					if((p.GetColor()==0))
					{
						d.SetVel(0.0,0.0,0.0);
						d.SetRadio(0);
					}
				}
				break;		
		}
	}
	 return 0;
}

//CHOQUE ENTRE LA MUJER Y CUALQUIER PARED (LLAMADA A CHOQUE(MUJER,PARED))
void Relaciones::Choque(Mundo &mundo, ObjetoCinematico &m)
{	
	for(int i=0;i<mundo.GetNumParedes();i++){
		Relaciones::Choque(*(mundo.GetListaParedes(i)),m);
	}	
}

//CHOQUE ENTRE EL DISPARO Y CUALQUIER PARED (LLAMADA A CHOQUE (DISPARO,PARED))
int Relaciones::Choque(Disparo &d, Mundo &m)
{
	int tipo;
	for(int i=0;i<m.GetNumParedes();i++){
		tipo = Relaciones::Choque(d,*(m.GetListaParedes(i)));
		if(tipo)return tipo;
	}
	return 0;	
}

bool Relaciones::Interaccion(Portal *p0, Portal *p1, ObjetoCinematico &m)
{
	float distancia0, distancia1;
	if(p0!=NULL && p1!=NULL && m.GetVel().modulo()!=0)
	{
		distancia0=p0->GetDistancia(m.GetPos());
		distancia1=p1->GetDistancia(m.GetPos());

		Vector3D lim01 = p0->GetMuro().GetLimite(1);	
		Vector3D lim03 = p0->GetMuro().GetLimite(3);
		Vector3D lim11 = p1->GetMuro().GetLimite(1);	
		Vector3D lim13 = p1->GetMuro().GetLimite(3);

		if(distancia0<0.3){	
			Vector3D pos = m.GetPos();	//cogemos la posicion de la mujer
			Vector3D vel=(p1->GetNormal()) * (m.GetVel().modulo());  //nueva velocidad de salida, de igual módulo antes de entrar
			switch (p0->GetTipo()){
				case 1:	//el plano en Y-Z
					if(pos.y>lim01.y && pos.y<lim03.y && pos.z>lim01.z && pos.z<lim03.z)
					{
						m.SetPos(p1->GetPos().x + p1->GetNormal().x,p1->GetPos().y + p1->GetNormal().y,p1->GetPos().z + p1->GetNormal().z);
						m.SetVel(vel.x,vel.y, vel.z);
					}
					break;
				case 2:	//el plano en X-Z
					if(pos.x>lim01.x && pos.x<lim03.x && pos.z>lim01.z && pos.z<lim03.z)
					{
						m.SetPos(p1->GetPos().x + p1->GetNormal().x,p1->GetPos().y + p1->GetNormal().y,p1->GetPos().z + p1->GetNormal().z);
						m.SetVel(vel.x,vel.y, vel.z);
					}
					break;
				case 3:	//el plano en X-Y
					if(pos.y>lim01.y && pos.y<lim03.y && pos.x>lim01.x && pos.x<lim03.x)
					{
						m.SetPos(p1->GetPos().x + p1->GetNormal().x,p1->GetPos().y + p1->GetNormal().y,p1->GetPos().z + p1->GetNormal().z);
						m.SetVel(vel.x,vel.y, vel.z);
					}
					break;		
				}	
		}
		if(distancia1<0.3){	
			Vector3D pos = m.GetPos();	//cogemos la posicion de la mujer
			Vector3D vel=(p0->GetNormal()) * (m.GetVel().modulo());	
			switch (p1->GetTipo()){
				case 1:	//el plano en Y-Z
					if(pos.y>lim11.y && pos.y<lim13.y && pos.z>lim11.z && pos.z<lim13.z)
					{
						m.SetPos(p0->GetPos().x + p0->GetNormal().x,p0->GetPos().y + p0->GetNormal().y,p0->GetPos().z + p0->GetNormal().z);
						m.SetVel(vel.x,vel.y, vel.z);
					}
					break;
				case 2:	//el plano en X-Z
					if(pos.x>lim11.x && pos.x<lim13.x && pos.z>lim11.z && pos.z<lim13.z)
					{
						m.SetPos(p0->GetPos().x + p0->GetNormal().x,p0->GetPos().y + p0->GetNormal().y,p0->GetPos().z + p0->GetNormal().z);
						m.SetVel(vel.x,vel.y, vel.z);
					}
					break;
				case 3:	//el plano en X-Y
					if(pos.y>lim11.y && pos.y<lim13.y && pos.x>lim11.x && pos.x<lim13.x)
					{
						m.SetPos(p0->GetPos().x + p0->GetNormal().x,p0->GetPos().y + p0->GetNormal().y,p0->GetPos().z + p0->GetNormal().z);
						m.SetVel(vel.x,vel.y, vel.z);
					}
					break;		
				}	
		}
		return true;
	}
	else return false; 
}


bool Relaciones::Activacion(Boton &b,ObjetoCinematico &o){
	
	float distancia;
	distancia=b.GetMuro().GetDistancia(o.GetPos());//calculamos la distancia ente el muro del boton y el objeto
	
	Vector3D pos = o.GetPos();	//cogemos la posicion del objeto
	Vector3D lim1 = b.GetMuro().GetLimite(1);	//cogemos los limites superior e inferior del muro del boton
	Vector3D lim3 = b.GetMuro().GetLimite(3);

	if(distancia<=0.5){	
		Vector3D pos = o.GetPos();	//cogemos la posicion del objeto
		Vector3D lim1 = b.GetMuro().GetLimite(1);	//cogemos los limites superior e inferior del muro del boton
		Vector3D lim3 = b.GetMuro().GetLimite(3);

		if(pos.x>lim1.x && pos.x<lim3.x && pos.z>lim1.z && pos.z<lim3.z){//si da en el boton
			if(o.GetMasa()==5){
				o.SetPos(o.GetPos().x,lim1.y+0.3,o.GetPos().z);
				return 1;
			}
			if(o.GetMasa()>0){//si el objeto tiene masa
				return 1;
			}
			else o.SetVel(0,10,0);
		}
		else return 0;
	}
	//si no da en el boton
	if(pos.x>lim1.x && pos.x<lim3.x && pos.z>lim1.z && pos.z<lim3.z && distancia>=0.9)return 0;
	else return 0;
}


bool Relaciones::Choque(Puerta &p, ObjetoCinematico &o){

	float distancia;
	distancia=p.GetMuro().GetDistancia(o.GetPos());//calculamos la distancia ente el muro del boton y el objeto
		
	if(distancia<=0.3){	
		Vector3D pos = o.GetPos();	//cogemos la posicion del objeto
		Vector3D lim1 = p.GetMuro().GetLimite(1);	//cogemos los limites superior e inferior del muro del boton
		Vector3D lim3 = p.GetMuro().GetLimite(3);
	switch (p.GetMuro().GetTipo()){
			case 5:	//el plano en Y-Z
				if(pos.y>lim1.y && pos.y<lim3.y && pos.z>lim1.z && pos.z<lim3.z)
				{
					if(o.GetMasa()==0)
					{
						o.SetVel(-o.GetVel().x,0,o.GetVel().z);
					}
					else{
					if(o.GetVel().x < 0)
					o.SetPos(lim1.x+0.3F,o.GetPos().y,o.GetPos().z);

					if(o.GetVel().x > 0)
						o.SetPos(lim1.x-0.3F,o.GetPos().y,o.GetPos().z);}
				}
				break;
			case 6:	//el plano en X-Y
				if(pos.y>lim1.y && pos.y<lim3.y && pos.x>lim1.x && pos.x<lim3.x)
				{
					if(o.GetMasa()==0)
					{
						o.SetVel(o.GetVel().x,0,-o.GetVel().z);
					}
					else{
					if(o.GetVel().z < 0)
					o.SetPos(o.GetPos().x,o.GetPos().y,lim1.z+0.3F);

					if(o.GetVel().z > 0)
						o.SetPos(o.GetPos().x,o.GetPos().y,lim1.z-0.3F);}
				}
				break;		
		}
		return 1;
	}
	
	else return 0;

}

void Relaciones::Activacion(Boton &b,Puerta &p)
{
	if(b.GetEstado())p.Activar();
	if(b.GetEstado()==0)p.Desactivar();
}