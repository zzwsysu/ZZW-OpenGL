#ifndef _M_Y_LIGHT
#define _M_Y_LIGHT

#include <gl/glut.h>

struct lightStruct 
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];
	GLfloat direction[3];
	GLfloat cutoff,exponent;
	GLfloat kc,kl,kq;
};

class myLight
{
protected:
	lightStruct light;
	GLenum lightId;
	bool switchOn;
public:
	myLight();
	void Set(lightStruct _light);
	void SetPos(float x,float y,float z);
	void Get(lightStruct& _light);
	virtual void LightUp(GLenum _lightId,bool IsAtten=false,bool IsSpotLight=false);
	void Switch();
};

class SunLight:public myLight
{
public:
	SunLight();
};

class Lamp:public myLight
{
public:
	Lamp();
};

class Daylightlamp:public myLight
{
public:
	Daylightlamp();
};

class Flashlight:public myLight
{
public:
	Flashlight();
	void LightUp(GLenum _lightId,bool IsAtten=false);
	void SetDir(float x, float y, float z);
	void SetCutOff(float _cutoff);
};

#endif