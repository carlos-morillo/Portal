#include "ObjetoCinematico.h"


ObjetoCinematico::ObjetoCinematico(void)
{}

ObjetoCinematico::~ObjetoCinematico(void)
{}

void ObjetoCinematico::Mueve(float t)
{
	posicion=posicion+velocidad*t+aceleracion*(0.5f*t*t); 
	velocidad=velocidad+aceleracion*t;
}

void ObjetoCinematico::SetVel(float vx, float vy, float vz)
{
	velocidad.x=vx;
	velocidad.y=vy;
	velocidad.z=vz;
}
void ObjetoCinematico::SetPos(float vx, float vy, float vz)
{
	posicion.x=vx;
	posicion.y=vy;
	posicion.z=vz;
}

Vector3D ObjetoCinematico::GetPos()
{
	return this->posicion;
}

Vector3D ObjetoCinematico::GetVel()
{
	return this->velocidad;
}

Vector3D ObjetoCinematico::GetAc()
{
	return this->aceleracion;
}

int ObjetoCinematico::GetMasa()
{
	return masa;
}