#include <math.h>
#include "Particle.h"


Particles::Particles()
{
}

Particles::Particles(int _num)
{
	num=_num;
	particles=new Particle[num];
}

Particles::~Particles()
{
	delete particles;
}

float Particles::randomInRange(float min,float max)
{
	float x;
	x=(float)rand()/(float)RAND_MAX*(max - min)+min;
	return x;
}

void Particles::SetParticles(unsigned int _num,Particle _particle)
{
	num=_num;
	particles=new Particle[num];
	for (int i=0;i<num;i++)
	{
		particles[i].SetParticle(_particle);
	}
}

void Particles::SetArea(Area _area)
{
	area=_area;
}

Area Particles::GetArea()
{
	return area;
}

Particle Particles::GetParticle(int i)
{
	return particles[i];
}

void Particles::p_SelfUpdate(Particle &_particle)
{
	float l=sqrtf(2)*_particle.size/2;
	_particle.p0=_particle.pos0-(_particle.up+_particle.right)*l;
	_particle.p1=_particle.pos0+(_particle.right-_particle.up)*l;
	_particle.p2=_particle.pos0+(_particle.right+_particle.up)*l;
	_particle.p3=_particle.pos0+(_particle.up-_particle.right)*l;
}

void Particles::p_Update(float h,Particle &_particle)
{
	_particle.life-=_particle.fade_speed;

	_particle.pos1+=_particle.v1*h;
	_particle.v1+=_particle.a1*h;

	_particle.pos0=_particle.pos1+_particle.area.pos;
	_particle.v0=_particle.v1+_particle.area.v;
	_particle.a0=_particle.a1+_particle.area.a;
}

void Particles::p_Draw(Particle &_particle)
{
	glColor4ub(_particle.color[0],_particle.color[1],_particle.color[2],255);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(_particle.p0.x,_particle.p0.y,_particle.p0.z);
	glTexCoord2f(1,0);glVertex3f(_particle.p1.x,_particle.p1.y,_particle.p1.z);
	glTexCoord2f(1,1);glVertex3f(_particle.p2.x,_particle.p2.y,_particle.p2.z);
	glTexCoord2f(0,1);glVertex3f(_particle.p3.x,_particle.p3.y,_particle.p3.z);
	glEnd();
	glColor4ub(255,255,255,255);
}

void Particles::AreaUpdate(float h)
{
	area.v+=area.a*h;
	area.pos+=area.v*h;
}

void Particles::Play(GLuint tex,float h,bool IsDynamic/* =false */)
{
	if (IsDynamic)
	{
		myVector up,right;
		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
		right.SetVector(m[0],m[4],m[8]);
		up.SetVector(m[1],m[5],m[9]);
		right.normalize();up.normalize();
		for (int i=0;i<num;i++)
		{
			particles[i].up=up;
			particles[i].right=right;
		}
	}
	if (!start)
	{
		start=true;
		AreaInit();
		for (int i=0;i<num;i++)
		{
			p_Init(particles[i]);
		}
	}
	AreaUpdate(h);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER ,0.5);
	glBindTexture(GL_TEXTURE_2D,tex);
	for (int i=0;i<num;i++)
	{
		p_Update(h,particles[i]);
		p_SelfUpdate(particles[i]);
		p_Draw(particles[i]);
	}
	glDisable(GL_ALPHA_TEST);
}

//////////////////////////////////////////////////////////////////////////
Snows::Snows(int _num)
{
	num=_num;
	particles=new Particle[num];
}

Snows::~Snows(){}

void Snows::AreaInit()
{
	area.range=100;
}

void Snows::p_Init(Particle &_particle)
{
	_particle.pos1=myVector(randomInRange(-area.range/2,area.range/2),
							randomInRange(area.range/3,area.range/2),
							randomInRange(-area.range/2,area.range/2));
	_particle.v1=myVector(0,0,0);
	_particle.a1 = myVector(randomInRange(-0.8,0.8),
							randomInRange(-2.0,-0.1),
							randomInRange(-0.8,0.8));
}

void Snows::p_Update(float h,Particle &_particle)
{
	_particle.area=area;//如果要与整个粒子区域状态同步，必须在p_Update函数里对其区域进行绑定
	if (_particle.pos0.y<=-20)
	{
		p_Init(_particle);
	}
	Particles::p_Update(h,_particle);
}

void Snows::Play(GLuint tex,float h,bool IsDynamic/* =false */)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	Particles::Play(tex,h,IsDynamic);
	glDisable(GL_BLEND);
}

//////////////////////////////////////////////////////////////////////////
Butterflys::Butterflys()
{
}

Butterflys::Butterflys(int _num)
{
	num=_num;
	particles=new Particle[num];
}

Butterflys::~Butterflys(){}

void Butterflys::AreaInit()
{
	area.range=10;
}

void Butterflys::p_Init(Particle &_particle)
{
	_particle.pos1=myVector(randomInRange(-area.range/2,area.range/2),
							randomInRange(-area.range/2,area.range/2),
							randomInRange(-area.range/2,area.range/2));
}

void Butterflys::p_SelfUpdate(Particle &_particle)
{
	float h=0.01;
	Particles::p_SelfUpdate(_particle);
	if (wdir)
	{
		flag+=h;
	} 
	else
	{
		flag-=h;
	}
	if (flag>1.0f)
	{
		wdir=!wdir;
		flag=1.0;
	}
	else if (flag<-1.0f)
	{
		wdir=!wdir;
		flag=-1.0;
	}
	_particle.p3.z=_particle.size*flag+_particle.pos0.z;
	_particle.p1.z=_particle.size*flag+_particle.pos0.z;
}

void Butterflys::p_Update(float h,Particle &_particle)
{
	_particle.area=area;//如果要与整个粒子区域状态同步，必须在p_Update函数里对其区域进行绑定
	_particle.a1=myVector(randomInRange(-0.8,0.8),
						randomInRange(-0.8,0.8),
						randomInRange(-0.8,0.8));
	Particles::p_Update(h,_particle);
	Edge_detect(_particle);
}

void Butterflys::Edge_detect(Particle &_particle)
{
	if (_particle.pos1.x>area.range)
	{
		_particle.pos1.x=area.range;
		_particle.a1.flip();
		_particle.v1.SetVector(0,0,0);
	} 
	else if (_particle.pos1.x<-area.range)
	{
		_particle.pos1.x=-area.range;
		_particle.a1.flip();
		_particle.v1.SetVector(0,0,0);
	}
	if (_particle.pos1.z>area.range)
	{
		_particle.pos1.z=area.range;
		_particle.a1.flip();
		_particle.v1.SetVector(0,0,0);
	} 
	else if (_particle.pos1.z<-area.range)
	{
		_particle.pos1.z=-area.range;
		_particle.a1.flip();
		_particle.v1.SetVector(0,0,0);
	}
	if (_particle.pos1.y>area.range)
	{
		_particle.pos1.y=area.range;
		_particle.a1.flip();
		_particle.v1.SetVector(0,0,0);
	} 
	else if (_particle.pos1.y<-area.range)
	{
		_particle.pos1.y=-area.range;
		_particle.a1.flip();
		_particle.v1.SetVector(0,0,0);
	}
}

void Butterflys::p_Draw(Particle &_particle)
{
	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0,1.0);glVertex3f(_particle.p2.x,_particle.p2.y,_particle.p2.z);
	glTexCoord2f(0.0,1.0);glVertex3f(_particle.p3.x,_particle.p3.y,_particle.p3.z);
	glTexCoord2f(0.0,0.0);glVertex3f(_particle.p0.x,_particle.p0.y,_particle.p0.z);

	glTexCoord2f(1.0,1.0);glVertex3f(_particle.p2.x,_particle.p2.y,_particle.p2.z);
	glTexCoord2f(0.0,0.0);glVertex3f(_particle.p0.x,_particle.p0.y,_particle.p0.z);
	glTexCoord2f(1.0,0.0);glVertex3f(_particle.p1.x,_particle.p1.y,_particle.p1.z);
	glEnd();
}

//////////////////////////////////////////////////////////////////////////
void A_particles::p_Init(Particle &_particle)
{
	_particle.area=area;//仅仅当粒子重生的时候才对其区域进行绑定，这样可以得到较好的效果
	_particle.life=1;
	_particle.active=true;
	_particle.fade_speed=randomInRange(0.0001,0.1);
	_particle.color[0]=(unsigned int) randomInRange(0,255);
	_particle.color[1]=(unsigned int) randomInRange(0,255);
	_particle.color[2]=(unsigned int) randomInRange(0,255);
	_particle.pos1=myVector(randomInRange(-0.01,0.01),
							randomInRange(-0.01,0.01),
							randomInRange(-0.01,0.01));
}

void A_particles::p_Update(float h,Particle &_particle)
{
	if (_particle.life<0)
	{
		p_Init(_particle);
	}
	Particles::p_Update(h,_particle);
}

void A_particles::AreaInit()
{
	angle=0;
	area.pos=myVector(r,0,0);
}

void A_particles::AreaUpdate(float h)
{
	area.pos.x=r*cos(angle);
	area.pos.y=r*sin(angle);
	angle+=h;
	if (angle>2*PI&&angle<3*PI)
	{
		area.pos.x=r/2*cos(angle)+r/2;
		area.pos.y=r/2*sin(angle);
	}
	else if (angle>3*PI&&angle<4*PI)
	{
		area.pos.x=-r/2*cos(angle)-r/2;
		area.pos.y=r/2*sin(angle);
	}
	else if (angle>4*PI)
	{
		AreaInit();
	}
}

void A_particles::Play(GLuint tex,float h,bool IsDynamic/* =false */)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	Particles::Play(tex,h,IsDynamic);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

//////////////////////////////////////////////////////////////////////////
void B_particles::p_Init(Particle &_particle)
{
	_particle.area=area;
	_particle.life=1;
	_particle.active=true;
	_particle.fade_speed=randomInRange(0.0001,0.6);
	_particle.color[0]=(unsigned int) randomInRange(0,255);
	_particle.color[1]=(unsigned int) randomInRange(0,255);
	_particle.color[2]=(unsigned int) randomInRange(0,255);
	_particle.pos1=myVector(randomInRange(-0.01,0.01),
							randomInRange(-0.01,0.01),
							randomInRange(-0.01,0.01));
	_particle.v1=myVector(0,-0.2,0);
	_particle.a1=myVector(randomInRange(-0.01,0.01),
						randomInRange(-0.01,0.01),
						randomInRange(-0.01,0.01));
}

void B_particles::p_Update(float h,Particle &_particle)
{
	if (_particle.life<0)
	{
		p_Init(_particle);
	}
	Particles::p_Update(h,_particle);
}

void B_particles::AreaInit()
{
	area1.range=5;
	area.pos=myVector(randomInRange(-area1.range/2,area1.range/2),
						randomInRange(-area1.range/2,area1.range/2),
						randomInRange(-area1.range/2,area1.range/2));
}

void B_particles::AreaUpdate(float h)
{
	area.a=myVector(randomInRange(-r1,r1),
					randomInRange(-r1,r1),
					randomInRange(-r1,r1));
	Particles::AreaUpdate(h);
	Edge_detect();
}

void B_particles::Edge_detect()
{
	if (area.pos.x>area1.range)
	{
		area.pos.x=area1.range;
		area.a.flip();
		area.v=myVector(randomInRange(-r2,r2),
			randomInRange(-r2,r2),
			randomInRange(-r2,r2));
	} 
	else if (area.pos.x<-area1.range)
	{
		area.pos.x=-area1.range;
		area.a.flip();
		area.v=myVector(randomInRange(-r2,r2),
			randomInRange(-r2,r2),
			randomInRange(-r2,r2));
	}
	if (area.pos.z>area1.range)
	{
		area.pos.z=area1.range;
		area.a.flip();
		area.v=myVector(randomInRange(-r2,r2),
			randomInRange(-r2,r2),
			randomInRange(-r2,r2));
	} 
	else if (area.pos.z<-area1.range)
	{
		area.pos.z=-area1.range;
		area.a.flip();
		area.v=myVector(randomInRange(-r2,r2),
			randomInRange(-r2,r2),
			randomInRange(-r2,r2));
	}
	if (area.pos.y>area1.range)
	{
		area.pos.y=area1.range;
		area.a.flip();
		area.v=myVector(randomInRange(-r2,r2),
			randomInRange(-r2,r2),
			randomInRange(-r2,r2));
	} 
	else if (area.pos.y<-area1.range)
	{
		area.pos.y=-area1.range;
		area.a.flip();
		area.v=myVector(randomInRange(-r2,r2),
			randomInRange(-r2,r2),
			randomInRange(-r2,r2));
	}
}

void B_particles::Play(GLuint tex,float h,bool IsDynamic/* =false */)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	Particles::Play(tex,h,IsDynamic);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

//////////////////////////////////////////////////////////////////////////
void C_particles::p_Init(Particle &_particle)
{
	_particle.area=area;
	_particle.life=1;
	_particle.active=true;
	_particle.fade_speed=randomInRange(0.01,0.1);
	_particle.color[0]=(unsigned int) randomInRange(0,255);
	_particle.color[1]=(unsigned int) randomInRange(0,255);
	_particle.color[2]=(unsigned int) randomInRange(0,255);
	_particle.pos1=myVector(randomInRange(-0.1,0.1),
							randomInRange(-0.1,0.1),
							randomInRange(-0.1,0.1));
	_particle.v1=myVector(0,0,0);
	_particle.a1=myVector(randomInRange(-0.01,0.01),
						randomInRange(-0.001,0),
						randomInRange(-0.01,0.01));
}

void C_particles::p_Update(float h,Particle &_particle)
{
	if (_particle.life<0)
	{
		p_Init(_particle);
	}
	Particles::p_Update(h,_particle);
}

void C_particles::Play(GLuint tex,float h,bool IsDynamic/* =false */)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	Particles::Play(tex,h,IsDynamic);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

//////////////////////////////////////////////////////////////////////////
void D_particles::AreaInit()
{
	angle=0;
	area.pos=myVector(1+r,0,0);
}

void D_particles::AreaUpdate(float h)
{
	area.pos.x=r*cos(angle)+1;
	area.pos.y=r*sin(angle);
	angle+=h;
}
