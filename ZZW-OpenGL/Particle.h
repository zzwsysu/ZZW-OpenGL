#pragma once
#include "Geometry.h"
#include <gl/GL.h>

#define PI 3.1415926535897932384626433832795

struct Area
{
	myVector pos,v,a;				//������������λ��,�ٶȣ����ٶ�
	float range;					//��������Χ��С
	Area(){}
	Area(myVector _pos,myVector _v,myVector _a,float _range)
	{
		pos=_pos,v=_v,a=_a,range=_range;
	}
};

struct Particle
{
	Area area;
	myVector pos0,v0,a0;			//����λ�ã������ٶȣ����Լ��ٶ�
	myVector pos1,v1,a1;			//���λ�ã�����ٶȣ���Լ��ٶ�
	float size;						//���ӱ����С
	myVector p0,p1,p2,p3;			//������Ƭ���ĸ�����
	myVector up,right;				//������Ƭ��y��x��
	unsigned int color[3];			//������ɫRGB
	float life,fade_speed;			//�����������ڣ�˥���ٶ�
	bool active;					//�Ƿ񼤻��ʶ
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
/* ����ϵͳ����                                                         */
/* ����̳к����дp_Init,AreaInit,p_SelfUpdate,p_Update,AreaUpdate�Ⱥ���*/
/************************************************************************/
class Particles
{
protected:
	bool start;				//��ʼ����ʶ
	int num;				//���ӵ���Ŀ
	Particle *particles;	//��������ָ��
	Area area;				//����ϵͳ������

	//////////////////////////////////////////////////////////////////////////
	//�������������������min~max�����������
	float randomInRange(float min,float max);

	//////////////////////////////////////////////////////////////////////////
	//���ӳ�ʼ������������д��
	//ע��:���ɳ�ʼ�����ӵľ���λ��pos0,v0,a0��ֻ�ܳ�ʼ�������λ��pos1,v1,a1
	virtual void p_Init(Particle &_particle){}

	//////////////////////////////////////////////////////////////////////////
	//�����ʼ�����������Ҫʹ������ķ�Χ���ԣ��������д�����ڴ˳�ʼ����Χ
	virtual void AreaInit(){}

	//////////////////////////////////////////////////////////////////////////
	//����������״���º���������ֻ����д�ú����Ϳ��Եõ���ͬ���������
	virtual void p_SelfUpdate(Particle &_particle);

	//////////////////////////////////////////////////////////////////////////
	//�����˶�״̬���º���������ֻ����д�ú����Ϳ��Եõ���ͬ���˶�����
	virtual void p_Update(float h,Particle &_particle);

	//////////////////////////////////////////////////////////////////////////
	//����������ʾ������������ֻ���ı��εĻ��ƣ�������Ҫ������д
	virtual void p_Draw(Particle &_particle);

	//////////////////////////////////////////////////////////////////////////
	//������º�������д��ɵõ���ͬ�������˶�����
	virtual void AreaUpdate(float h);


public:
	Particles();
	Particles(int _num);
	virtual ~Particles();

	//////////////////////////////////////////////////////////////////////////
	//���ú�������Ҫ��������������Ŀ����������
	virtual void SetParticles(unsigned int _num,Particle _particle);

	//////////////////////////////////////////////////////////////////////////
	//��������������Ҫ���ڶ�����ϵͳ�����������ʵʱ����
	void SetArea(Area _area);

	//////////////////////////////////////////////////////////////////////////
	//��ȡ�������������ʵʱ������������
	Area GetArea();

	//////////////////////////////////////////////////////////////////////////
	//��ȡ�ض����ӵĺ�����iΪ������
	Particle GetParticle(int i);

	//////////////////////////////////////////////////////////////////////////
	//��ʾ����������Ĭ��û��ʹ�û�ϣ�������д
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