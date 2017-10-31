#pragma once
#include "..\Basic\Pared.h"

class ObjetoActivable
{
protected:
	Vector3D posicion;
	Pared muro;
	bool estado;
public:
	ObjetoActivable(void);
	~ObjetoActivable(void);
	ObjetoActivable(Vector3D pos);

	virtual void Dibuja(void);
	bool GetEstado(void);
	void Activar(void);
	void Desactivar(void);
	virtual Pared &GetMuro(void);

};
