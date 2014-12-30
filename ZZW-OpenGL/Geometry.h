#ifndef  _SHAPE3D_
#define  _SHAPE3D_

#include <VECTOR>
using namespace std;
#include <gl/glut.h>

void Grid(double l);

/************************************************************************/
/*点类
/************************************************************************/
class Point3D
{
public:
	float x; float y;float z;
	//////////////////////////////////////////////////////////////////////////
	//构造函数
	Point3D();
	Point3D(float _x,float _y,float _z);
	//////////////////////////////////////////////////////////////////////////
	//函数作用：设置点
	void Setpoint(float _x,float _y,float _z);
	//////////////////////////////////////////////////////////////////////////
	//函数作用：设置点
	void Setpoint(Point3D& p);
};

/************************************************************************/
/*向量类
/************************************************************************/
class myVector
{
public:
	float x,y,z;
	myVector();
	myVector(float dx, float dy, float dz);
	void SetVector(float dx, float dy, float dz);
	void SetVector(myVector& v);
	//////////////////////////////////////////////////////////////////////////
	//设为向量(b-a);
	void SetVector(Point3D a, Point3D b);
	//////////////////////////////////////////////////////////////////////////
	//令该向量方向翻转
	void flip();
	//////////////////////////////////////////////////////////////////////////
	//单位向量化
	void normalize();
	//////////////////////////////////////////////////////////////////////////
	//与向量b点乘
	float dot(myVector b);
	//////////////////////////////////////////////////////////////////////////
	//与向量b叉乘
	myVector cross(myVector b); 
	//////////////////////////////////////////////////////////////////////////
	//向量的模
	float Length();
	//////////////////////////////////////////////////////////////////////////
	//与向量b的夹角
	float Angle(myVector b);
	//////////////////////////////////////////////////////////////////////////
	//重载“+”号运算符
	friend myVector operator+(myVector a, myVector b);
	friend myVector operator-(myVector a, myVector b);
	friend Point3D operator+(Point3D p, myVector v);
	//////////////////////////////////////////////////////////////////////////
	//重载“*”号运算符
	friend myVector operator*(float t, myVector v);
	friend myVector operator*(myVector v, float t);
	myVector operator+=(myVector v);
};

/************************************************************************/
/*基类，形状类
/************************************************************************/
class shape3D
{
public:
	shape3D(){}
	virtual void SolidDraw(){}
	virtual void WireDraw(){}
};

/************************************************************************/
/*坐标轴
/************************************************************************/
class coord3D:public shape3D
{
private:
	float coordSize;
	GLUquadric *obj;
	void arrow_y();
	void arrow_x();
	void arrow_z();
public:
	coord3D();
	coord3D(float size);
	void Setcoord3D(float size);
	void SolidDraw();
	void WireDraw();
};

/************************************************************************/
/*圆柱（圆锥）
/************************************************************************/
class myCylinder:public shape3D
{
private:
	float R1, R2, h;
	GLUquadric *obj;
public:
	myCylinder();
	myCylinder(float _R1,float _R2,float _h);
	void SetCylinder(float _R1,float _R2,float _h);
	void SolidDraw();
	void WireDraw();
};

/************************************************************************/
/*圆筒
/************************************************************************/
class myBarrel:public shape3D
{
private:
	float R_top, r_top,R_base,r_base, h;
public:
	myBarrel();
	myBarrel(float _Rbase,float _rbase,float _Rtop,float _rtop,float _h);
	void SetBarrel(float _Rbase,float _rbase,float _Rtop,float _rtop,float _h);
	void SolidDraw();
	void WireDraw();
};

/************************************************************************/
/*球
/************************************************************************/
class myBall:public shape3D
{
protected:
	float R;
	GLUquadric *obj;
public:
	myBall();
	myBall(float _R);
	void SetBall(float _R);
	void SolidDraw();
	void WireDraw();
};

class myCube:public shape3D
{
protected:
	float Size;
public:
	myCube();
	myCube(float _size);
	void SetCube(float _size);
	void SetCube(myCube c);
	float GetSize(){return Size;}
	void SolidDraw();
	void WireDraw();
};

#endif