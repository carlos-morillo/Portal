#include "ObjetoActivable.h"

ObjetoActivable::ObjetoActivable(void)
{}

ObjetoActivable::~ObjetoActivable(void)
{}

void ObjetoActivable::Dibuja(void)
{}

void ObjetoActivable::Activar(void)
{
	if(estado==0)estado=1;
}

void ObjetoActivable::Desactivar(void)
{
	if(estado==1)estado=0;
}

Pared & ObjetoActivable::GetMuro(void)
{
	return muro;
}

bool ObjetoActivable::GetEstado()
{
	return estado;
}