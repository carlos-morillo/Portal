#pragma once
#include "ObjetoActivable.h"
#include"..\Basic\Pared.h"

class Boton:public ObjetoActivable
{
public:
	Boton(void);
	Boton(Vector3D pos);
	~Boton(void);
	virtual void Dibuja(void);

};
