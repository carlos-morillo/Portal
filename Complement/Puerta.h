#pragma once
#include "ObjetoActivable.h"
#include "..\Basic\Pared.h"

class Puerta:public ObjetoActivable
{
	int tipo;
public:
	Puerta(void);
	~Puerta(void);
	Puerta(Vector3D pos, int tip);
	virtual void Dibuja(void);
};
