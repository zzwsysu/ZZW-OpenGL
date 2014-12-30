#pragma once
#include "Geometry.h"
#include <gl/GL.h>

#define PI 3.1415926535897932384626433832795

struct Area
{
	myVector pos,v,a;				//粒子区域中心位置,速度，加速度
	float range;					//粒子区域范围大小
	Area(){}
	Area(myVector _pos,myVector _v,myVector _a,float _range)
	{
		pos=_pos,v=_v,a=_a,range=_range;
	}
};

struct Particle
{
	Area area;
	myVector pos0,v0,a0;			//绝对位置，绝对速度，绝对加速度
	myVector pos1,v1,a1;			//相对位置，相对速度，相对加速度
	float size;						//粒子本身大小
	myVector p0,p1,p2,p3;			//粒子面片的四个顶点
	myVector up,right;				//粒子面片的y，x轴
	unsigned int color[3];			//粒子颜色RGB
	float life,fade_speed;			//粒子生命周期，衰减速度
	bool active;					//是否激活标识
	Particle()
	{
		up=myVector (0,1,0);
		right=myVector (1,0,0);
		color[0]=color[1]=color[2]=255;
		life=1.0;
	}
	void SetParticle(Particle _particle)
	{
		*this=_particle;
	}
};

/************************************************************************/
/* 粒子系统父类                                                         */
/* 子类继承后可重写p_Init,AreaInit,p_SelfUpdate,p_Update,AreaUpdate等函数*/
/************************************************************************/
class Particles
{
protected:
	bool start;				//初始化标识
	int num;				//粒子的数目
	Particle *particles;	//粒子数组指针
	Area area;				//粒子系统的区域

	//////////////////////////////////////////////////////////////////////////
	//随机数产生函数，产生min~max区域间的随机数
	float randomInRange(float min,float max);

	//////////////////////////////////////////////////////////////////////////
	//粒子初始化函数，可重写。
	//注意:不可初始化粒子的绝对位置pos0,v0,a0，只能初始化其相对位置pos1,v1,a1
	virtual void p_Init(Particle &_particle){}

	//////////////////////////////////////////////////////////////////////////
	//区域初始化函数，如果要使用区域的范围属性，则必须重写，并在此初始化范围
	virtual void AreaInit(){}

	//////////////////////////////////////////////////////////////////////////
	//粒子自身形状更新函数，子类只需重写该函数就可以得到不同的自身更新
	virtual void p_SelfUpdate(Particle &_particle);

	//////////////////////////////////////////////////////////////////////////
	//粒子运动状态更新函数，子类只需重写该函数就可以得到不同的运动更新
	virtual void p_Update(float h,Particle &_particle);

	//////////////////////////////////////////////////////////////////////////
	//单个粒子显示函数，在这里只作四边形的绘制，如有需要，可重写
	virtual void p_Draw(Particle &_particle);

	//////////////////////////////////////////////////////////////////////////
	//区域更新函数，重写后可得到不同的区域运动更新
	virtual void AreaUpdate(float h);


public:
	Particles();
	Particles(int _num);
	virtual ~Particles();

	//////////////////////////////////////////////////////////////////////////
	//设置函数，主要用于设置粒子数目、粒子属性
	virtual void SetParticles(unsigned int _num,Particle _particle);

	//////////////////////////////////////////////////////////////////////////
	//设置区域函数，主要用于对粒子系统所在区域进行实时更新
	void SetArea(Area _area);

	//////////////////////////////////////////////////////////////////////////
	//获取区域参数，用于实时跟踪粒子区域
	Area GetArea();

	//////////////////////////////////////////////////////////////////////////
	//获取特定粒子的函数，i为索引号
	Particle GetParticle(int i);

	//////////////////////////////////////////////////////////////////////////
	//显示函数，里面默认没有使用混合，可以重写
	virtual void Play(GLuint tex,float h,bool IsDynamic=false);
};

class Snows:public Particles
{
private:
	void AreaInit();
	void p_Init(Particle &_particle);
	void p_Update(float h,Particle &_particle);
public:
	Snows(){}
	Snows(int _num);
	void Play(GLuint tex,float h,bool IsDynamic=false);
	~Snows();
};

class Butterflys:public Particles
{
private:
	float flag;
	bool wdir;
	void AreaInit();
	void p_Init(Particle &_particle);
	void p_SelfUpdate(Particle &_particle);
	void p_Update(float h,Particle &_particle);
	void p_Draw(Particle &_particle);
	void Edge_detect(Particle &_particle);
public:
	Butterflys();
	Butterflys(int _num);
	~Butterflys();
};

class A_particles:public Particles
{
protected:
	float r,angle;
	void p_Init(Particle &_particle);
	void p_Update(float h,Particle &_particle);
	void AreaInit();
	void AreaUpdate(float h);
public:
	A_particles(){r=2;}
	~A_particles(){}
	void Play(GLuint tex,float h,bool IsDynamic=false);
};

class B_particles:public Particles
{
private:
	float r1,r2;
	Area area1;
	void p_Init(Particle &_particle);
	void p_Update(float h,Particle &_particle);
	void AreaInit();
	void AreaUpdate(float h);
	void Edge_detect();
public:
	B_particles(){r1=1;r2=1;}
	~B_particles(){}
	void Play(GLuint tex,float h,bool IsDynamic=false);
};

class C_particles:public Particles
{
private:
	void p_Init(Particle &_particle);
	void p_Update(float h,Particle &_particle);
public:
	C_particles(){}
	~C_particles(){}
	void Play(GLuint tex,float h,bool IsDynamic=false);
};

class D_particles:public A_particles
{
private:
	void AreaInit();
	void AreaUpdate(float h);
public:
	D_particles(){r=0.2;}
	~D_particles(){}
};