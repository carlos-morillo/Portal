#pragma once

class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D(float ix=0.0f,float iy=0.0f, float iz=0.0f):x(ix),y(iy),z(iz){}
	~Vector3D(void);

	Vector3D operator +(Vector3D &op)
	{
		return Vector3D(x+op.x,y+op.y,z+op.z);
	}

	Vector3D operator -(Vector3D &op)
	{
		return Vector3D(x-op.x,y-op.y,z-op.z);
	}

	float operator *(Vector3D &op)
	{
		return (x*op.x+y*op.y+z*op.z);
	}

	Vector3D operator *(float f)
	{
		return Vector3D(x*f,y*f,z*f);
	}

	Vector3D operator =(const Vector3D &op)
	{
		this->x = op.x;
        this->y = op.y;
		this->z = op.z;
		return (*this);
	}
	
	float modulo(void);
	Vector3D unitario(void);
};
