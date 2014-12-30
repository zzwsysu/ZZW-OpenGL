#include "Light.h"

myLight::myLight()
{
	switchOn=true;
}

void myLight::SetPos(float x,float y,float z)
{
	light.position[0]=x;
	light.position[1]=y;
	light.position[2]=z;
}

void myLight::Set(lightStruct _light)
{
	light=_light;
}

void myLight::Get(lightStruct& _light)
{
	_light=light;
}

void myLight::LightUp(GLenum _lightId,bool IsAtten/* =false */,bool IsSpotLight/* =false */)
{
	lightId=_lightId;
	if (switchOn)
	{
		glEnable(lightId);
		glLightfv(lightId, GL_AMBIENT, light.ambient); 
		glLightfv(lightId, GL_DIFFUSE, light.diffuse); 
		glLightfv(lightId, GL_SPECULAR, light.specular); 
		glLightfv(lightId, GL_POSITION, light.position);
		if (IsAtten)
		{
			glLightf(lightId, GL_CONSTANT_ATTENUATION,light.kc);	// 设置 kc
			glLightf(lightId, GL_LINEAR_ATTENUATION, light.kl);		// 设置 kl
			glLightf(lightId, GL_QUADRATIC_ATTENUATION, light.kq);	// 设置 kq
		}
		if (IsSpotLight)
		{
			glLightf( lightId, GL_SPOT_CUTOFF, light.cutoff);		// 光锥半角
			glLightfv(lightId, GL_SPOT_DIRECTION, light.direction);	// 光锥方向
			glLightf( lightId, GL_SPOT_EXPONENT, light.exponent);	// 光锥衰减因子
		} 
	}
}

void myLight::Switch()
{
	if (switchOn)
	{
		glDisable(lightId);
	}
	switchOn=!switchOn;
}

//////////////////////////////////////////////////////////////////////////
SunLight::SunLight()
{
	lightStruct l1={
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		0.0,0.0,
		1.0,0.0,0.5
	};
	light=l1;
}

//////////////////////////////////////////////////////////////////////////
Lamp::Lamp()
{
	lightStruct l1={
		{0.1, 0.1, 0.1, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		{0.0, 0.0, 0.0},
		 0.0,0.0,
		 1.0,0.0,0.5
	};
	light=l1;
}

//////////////////////////////////////////////////////////////////////////
Daylightlamp::Daylightlamp()
{
	lightStruct l1={
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		{0.0, 0.0, 0.0},
		0.0,0.0,
		1.0,0.0,0.5
	};
	light=l1;
}

//////////////////////////////////////////////////////////////////////////
Flashlight::Flashlight()
{
	lightStruct l1={
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{0.0, 0.0, 10.0, 1.0},
		{0.0, 0.0, -1.0},
		20.0,5.0,
		1.0,0.0,0.5
	};
	light=l1;
}

void Flashlight::LightUp(GLenum _lightId,bool IsAtten/* =false */)
{
	myLight::LightUp(_lightId,IsAtten,true);
}

void Flashlight::SetDir(float x, float y, float z)
{
	light.direction[0]=x;
	light.direction[1]=y;
	light.direction[2]=z;
}

void Flashlight::SetCutOff(float _cutoff)
{
	light.cutoff=_cutoff;
}