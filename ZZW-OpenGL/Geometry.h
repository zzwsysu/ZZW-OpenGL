#ifndef  _SHAPE3D_
#define  _SHAPE3D_

#include <VECTOR>
using namespace std;
#include <gl/glut.h>

void Grid(double l);

/************************************************************************/
/*����
/************************************************************************/
class Point3D
{
public:
	float x; float y;float z;
	//////////////////////////////////////////////////////////////////////////
	//���캯��
	Point3D();
	Point3D(float _x,float _y,float _z);
	//////////////////////////////////////////////////////////////////////////
	//�������ã����õ�
	void Setpoint(float _x,float _y,float _z);
	//////////////////////////////////////////////////////////////////////////
	//�������ã����õ�
	void Setpoint(Point3D& p);
};

/************************************************************************/
/*������
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
	//��Ϊ����(b-a);
	void SetVector(Point3D a, Point3D b);
	//////////////////////////////////////////////////////////////////////////
	//�����������ת
	void flip();
	//////////////////////////////////////////////////////////////////////////
	//��λ������
	void normalize();
	//////////////////////////////////////////////////////////////////////////
	//������b���
	float dot(myVector b);
	//////////////////////////////////////////////////////////////////////////
	//������b���
	myVector cross(myVector b); 
	//////////////////////////////////////////////////////////////////////////
	//������ģ
	float Length();
	//////////////////////////////////////////////////////////////////////////
	//������b�ļн�
	float Angle(myVector b);
	//////////////////////////////////////////////////////////////////////////
	//���ء�+���������
	friend myVector operator+(myVector a, myVector b);
	friend myVector operator-(myVector a, myVector b);
	friend Point3D operator+(Point3D p, myVector v);
	//////////////////////////////////////////////////////////////////////////
	//���ء�*���������
	friend myVector operator*(float t, myVector v);
	friend myVector operator*(myVector v, float t);
	myVector operator+=(myVector v);
};

/************************************************************************/
/*���࣬��״��
/************************************************************************/
class shape3D
{
public:
	shape3D(){}
	virtual void SolidDraw(){}
	virtual void WireDraw(){}
};

/************************************************************************/
/*������
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
/*Բ����Բ׶��
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
/*ԲͲ
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
/*��
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