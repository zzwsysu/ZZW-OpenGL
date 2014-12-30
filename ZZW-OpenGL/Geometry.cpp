#include <MATH.H>
#include <iostream>
using namespace std;
#include "Geometry.h"
#include <GL/glut.h>
#include "gl\glaux.h"

#define PI 3.1415926535897932384626433832795

#pragma comment (lib,"glaux.lib")

void Grid(double l)
{
	glColor3f(0,1,1);
	for (int i=0;i<50;i++)
	{
		glNormal3f(0,1,0);
		glBegin(GL_LINES);
			glVertex3f(-l/2,0,i*0.01*l);
			glVertex3f(l/2,0,i*0.01*l);

			glVertex3f(-l/2,0,-i*0.01*l);
			glVertex3f(l/2,0,-i*0.01*l);

			glVertex3f(i*0.01*l,0,-l/2);
			glVertex3f(i*0.01*l,0,l/2);

			glVertex3f(-i*0.01*l,0,-l/2);
			glVertex3f(-i*0.01*l,0,l/2);
		glEnd();
	}
}

//////////////////////////////////////////////////////////////////////////
coord3D::coord3D()
{
	coordSize=1;
	obj=gluNewQuadric();
}

coord3D::coord3D(float size)
{
	coordSize=size;
	obj=gluNewQuadric();
}

void coord3D::Setcoord3D(float size)
{
	coordSize=size;
}

void coord3D::arrow_y()
{
	float l = 1.0*coordSize;
	float r = 0.025*coordSize;
	glPushMatrix();
		glRotatef(180, 1, 0, 0);
		glTranslatef(0, -1, 0);
		auxWireCylinder(r, l);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,l,0);
		glRotatef(-90, 1, 0, 0);
		auxWireCone(r*4, 0.7);	
	glPopMatrix();
}

void coord3D::arrow_x()
{
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	arrow_y();
	glPopMatrix();
}

void coord3D::arrow_z()
{
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	arrow_y();
	glPopMatrix();
}

void coord3D::WireDraw()
{
	glColor3f(1, 0, 0);
	arrow_x();
	glColor3f(0, 1, 0);
	arrow_y();
	glColor3f(0, 0, 1);
	arrow_z();
}

void coord3D::SolidDraw()
{
	unsigned int m=20;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//z轴
	glColor3f(0,0,1);
	glPushMatrix();
		gluCylinder(obj,0.025*coordSize,0.025*coordSize,coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
		glTranslatef(0,0,coordSize);
		gluCylinder(obj,0.1*coordSize,0,0.3*coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
		gluDisk(obj,0,0.1*coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
	glPopMatrix();
	//y轴
	glColor3f(0,1,0);
	glPushMatrix();
		glRotatef(-90,1,0,0);
		gluCylinder(obj,0.025*coordSize,0.025*coordSize,coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
		glTranslatef(0,0,coordSize);
		gluCylinder(obj,0.1*coordSize,0,0.3*coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
		gluDisk(obj,0,0.1*coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
	glPopMatrix();
	//x轴
	glColor3f(1,0,0);
	glPushMatrix();
		glRotatef(90,0,1,0);
		gluCylinder(obj,0.025*coordSize,0.025*coordSize,coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
		glTranslatef(0,0,coordSize);
		gluCylinder(obj,0.1*coordSize,0,0.3*coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
		gluDisk(obj,0,0.1*coordSize,(int)m*coordSize+5,(int)m*coordSize+5);
	glPopMatrix();
	glColor3f(0,0,0);
}

//////////////////////////////////////////////////////////////////////////
Point3D::Point3D()
{
	x=0; y=0; z=0;
}

Point3D::Point3D(float _x,float _y,float _z)
{
	x=_x; y=_y; z=_z;
}

void Point3D::Setpoint(float _x,float _y,float _z)
{
	x=_x; y=_y; z=_z;
}

void Point3D::Setpoint(Point3D& p)
{
	x=p.x,y=p.y,z=p.z;
}

//////////////////////////////////////////////////////////////////////////
myVector::myVector()
{
	x=y=z=0;
}

myVector::myVector(float dx, float dy, float dz)
{
	x=dx; y=dy; z=dz;
}

void myVector::SetVector(float dx, float dy, float dz)
{
	x=dx; y=dy; z=dz;
}

void myVector::SetVector(myVector& v)
{
	x=v.x; y=v.y; z=v.z;
}

//////////////////////////////////////////////////////////////////////////
//设为向量(b-a),即点a指向点b的向量
void myVector::SetVector(Point3D a, Point3D b)
{
	x=b.x-a.x;
	y=b.y-a.y;
	z=b.z-a.z;
}

void myVector::flip()
{
	x=-x;y=-y;z=-z;
}

void myVector::normalize()
{
	double size=x*x+y*y+z*z;
	if (size<0.0000001)		//对零向量不做任何操作
	{
		cerr<<"\nnormalize() sees vector (0,0,0)!";
		return;
	}
	float scaleFactor=1.0/(float)sqrt(size);
	x*=scaleFactor;y*=scaleFactor;z*=scaleFactor;
}

float myVector::dot(myVector b)
{
	return (x*b.x+y*b.y+z*b.z);
}

myVector myVector::cross(myVector b)
{
	myVector c(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);
	return c;
}

float myVector::Length()
{
	return sqrtf(x*x+y*y+z*z);
}

float myVector::Angle(myVector b)
{
	float n=dot(b);
	float m=Length()*b.Length();
	return acos(n/m);
}

myVector operator+(myVector a, myVector b)
{
	myVector c;
	c.x=a.x+b.x;
	c.y=a.y+b.y;
	c.z=a.z+b.z;
	return c;
}

myVector operator-(myVector a, myVector b)
{
	myVector c;
	c.x=a.x-b.x;
	c.y=a.y-b.y;
	c.z=a.z-b.z;
	return c;
}

Point3D operator+(Point3D p,myVector v)
{
	Point3D b;
	b.x=p.x+v.x;
	b.y=p.y+v.y;
	b.z=p.z+v.z;
	return b;
}

myVector operator*(float t, myVector v)
{
	myVector v1;
	v1.x=t*v.x;
	v1.y=t*v.y;
	v1.z=t*v.z;
	return v1;
}

myVector operator*(myVector v, float t)
{
	return t*v;
}

myVector myVector::operator+=(myVector v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return(*this);
}

//////////////////////////////////////////////////////////////////////////
myCylinder::myCylinder()
{
	R1=0; R2=0; h=0;
	obj=gluNewQuadric();
}

myCylinder::myCylinder(float _R1,float _R2,float _h)
{
	R1=_R1; R2=_R2; h=_h;
	obj=gluNewQuadric();
}

void myCylinder::SetCylinder(float _R1,float _R2,float _h)
{
	R1=_R1; R2=_R2; h=_h;
}

void myCylinder::SolidDraw()
{
	unsigned int m=20;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float R=max(R1,R2);
	gluCylinder(obj, R1, R2, h, (int)(R*m)+5, (int)(h*m)+5);
	gluDisk(obj, 0, R1, (int)(R1*m)+5, (int)(R1*m)+5);
	
	glPushMatrix();
	glTranslatef(0, 0, h);
		gluDisk(obj, 0, R2, (int)(R2*m)+5, (int)(R2*m)+5);
	glPopMatrix();
}

void myCylinder::WireDraw()
{
	unsigned int m=20;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float R=max(R1,R2);
	gluCylinder(obj, R1, R2, h, (int)(R*m)+5, (int)(h*m)+5);
	gluDisk(obj, 0, R1, (int)(R1*m)+5, (int)(R1*m)+5);
	
	glPushMatrix();
		glTranslatef(0, 0, h);
		gluDisk(obj, 0, R2, (int)(R2*m)+5, (int)(R2*m)+5);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
myBarrel::myBarrel()
{
	R_top=0;r_top=0;h=0;
}

myBarrel::myBarrel(float _Rbase,float _rbase,float _Rtop,float _rtop,float _h)
{
	R_top=_Rtop,r_top=_rtop,R_base=_Rbase,r_base=_rbase,h=_h;
}

void myBarrel::SetBarrel(float _Rbase,float _rbase,float _Rtop,float _rtop,float _h)
{
	R_top=_Rtop,r_top=_rtop,R_base=_Rbase,r_base=_rbase,h=_h;
}

void myBarrel::SolidDraw()
{
	int stacks=10;						//圆筒的stacks
	int slices=20;						//圆筒的slices
	float step=h/stacks;				//圆筒长度方向上的增加步长
	float theta=2*PI/slices;			//圆筒圆周角度上的增加步长
	float k1=(R_base-R_top)/h;			//圆筒侧视图外轮廓的斜率
	float k2=(r_base-r_top)/h;			//圆筒侧视图内轮廓的斜率
	for (int i=0;i<stacks;i++)
	{
		float R1=R_base-k1*i*step;
		float R2=R_base-k1*(i+1)*step;
		float r1=r_base-k2*i*step;
		float r2=r_base-k2*(i+1)*step;
		for (int j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);
			glNormal3f(cos(j*theta),sin(j*theta),0);
			glVertex3f(R1*cos(j*theta),R1*sin(j*theta),i*step);

			glNormal3f(cos((j+1)*theta),sin((j+1)*theta),0);
			glVertex3f(R1*cos((j+1)*theta),R1*sin((j+1)*theta),i*step);

			glNormal3f(cos(j*theta),sin(j*theta),0);
			glVertex3f(R2*cos((j+1)*theta),R2*sin((j+1)*theta),(i+1)*step);

			glNormal3f(cos((j+1)*theta),sin((j+1)*theta),0);
			glVertex3f(R2*cos(j*theta),R2*sin(j*theta),(i+1)*step);
			glEnd();
			
			glBegin(GL_QUADS);
			glNormal3f(-cos(j*theta),-sin(j*theta),0);
			glVertex3f(r1*cos(j*theta),r1*sin(j*theta),i*step);

			glNormal3f(-cos((j+1)*theta),-sin((j+1)*theta),0);
			glVertex3f(r1*cos((j+1)*theta),r1*sin((j+1)*theta),i*step);

			glNormal3f(-cos((j+1)*theta),-sin((j+1)*theta),0);
			glVertex3f(r2*cos((j+1)*theta),r2*sin((j+1)*theta),(i+1)*step);

			glNormal3f(-cos(j*theta),-sin(j*theta),0);
			glVertex3f(r2*cos(j*theta),r2*sin(j*theta),(i+1)*step);
			glEnd();
		}
	}
	int stacks1=10;						//圆筒底面与顶面的圆环上的stacks，slices与圆筒上的一样
	float step1=(R_base-r_base)/stacks1;//底面圆环径向增长的步长
	float step2=(R_top-r_top)/stacks1;	//顶面圆环径向增长的步长
	for (int m=0;m<stacks1;m++)
	{
		float r1=m*step1+r_base;
		float r2=(m+1)*step1+r_base;
		float r3=m*step2+r_top;
		float r4=(m+1)*step2+r_top;
		for (int n=0;n<slices;n++)
		{
			glNormal3f(0,0,-1);
			glBegin(GL_QUADS);
			glVertex3f(r1*cos(n*theta),r1*sin(n*theta),0);
			glVertex3f(r1*cos((n+1)*theta),r1*sin((n+1)*theta),0);
			glVertex3f(r2*cos((n+1)*theta),r2*sin((n+1)*theta),0);
			glVertex3f(r2*cos(n*theta),r2*sin(n*theta),0);
			glEnd();
			
			glNormal3f(0,0,1);
			glBegin(GL_QUADS);
			glVertex3f(r3*cos(n*theta),r3*sin(n*theta),h);
			glVertex3f(r3*cos((n+1)*theta),r3*sin((n+1)*theta),h);
			glVertex3f(r4*cos((n+1)*theta),r4*sin((n+1)*theta),h);
			glVertex3f(r4*cos(n*theta),r4*sin(n*theta),h);
			glEnd();
		}
	}
}

void myBarrel::WireDraw()
{
	int stacks=10;						//圆筒的stacks
	int slices=20;						//圆筒的slices
	float step=h/stacks;				//圆筒长度方向上的增加步长
	float theta=2*PI/slices;			//圆筒圆周角度上的增加步长
	float k1=(R_base-R_top)/h;			//圆筒侧视图外轮廓的斜率
	float k2=(r_base-r_top)/h;			//圆筒侧视图内轮廓的斜率
	for (int i=0;i<stacks;i++)
	{
		float R1=R_base-k1*i*step;
		float R2=R_base-k1*(i+1)*step;
		float r1=r_base-k2*i*step;
		float r2=r_base-k2*(i+1)*step;
		for (int j=0;j<slices;j++)
		{
			glBegin(GL_LINE_LOOP);
			glNormal3f(cos(j*theta),sin(j*theta),0);
			glVertex3f(R1*cos(j*theta),R1*sin(j*theta),i*step);

			glNormal3f(cos((j+1)*theta),sin((j+1)*theta),0);
			glVertex3f(R1*cos((j+1)*theta),R1*sin((j+1)*theta),i*step);

			glNormal3f(cos(j*theta),sin(j*theta),0);
			glVertex3f(R2*cos((j+1)*theta),R2*sin((j+1)*theta),(i+1)*step);

			glNormal3f(cos((j+1)*theta),sin((j+1)*theta),0);
			glVertex3f(R2*cos(j*theta),R2*sin(j*theta),(i+1)*step);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glNormal3f(-cos(j*theta),-sin(j*theta),0);
			glVertex3f(r1*cos(j*theta),r1*sin(j*theta),i*step);

			glNormal3f(-cos((j+1)*theta),-sin((j+1)*theta),0);
			glVertex3f(r1*cos((j+1)*theta),r1*sin((j+1)*theta),i*step);

			glNormal3f(-cos((j+1)*theta),-sin((j+1)*theta),0);
			glVertex3f(r2*cos((j+1)*theta),r2*sin((j+1)*theta),(i+1)*step);

			glNormal3f(-cos(j*theta),-sin(j*theta),0);
			glVertex3f(r2*cos(j*theta),r2*sin(j*theta),(i+1)*step);
			glEnd();
		}
	}
	int stacks1=10;						//圆筒底面与顶面的圆环上的stacks，slices与圆筒上的一样
	float step1=(R_base-r_base)/stacks1;//底面圆环径向增长的步长
	float step2=(R_top-r_top)/stacks1;	//顶面圆环径向增长的步长
	for (int m=0;m<stacks1;m++)
	{
		float r1=m*step1+r_base;
		float r2=(m+1)*step1+r_base;
		float r3=m*step2+r_top;
		float r4=(m+1)*step2+r_top;
		for (int n=0;n<slices;n++)
		{
			glNormal3f(0,0,-1);
			glBegin(GL_LINE_LOOP);
			glVertex3f(r1*cos(n*theta),r1*sin(n*theta),0);
			glVertex3f(r1*cos((n+1)*theta),r1*sin((n+1)*theta),0);
			glVertex3f(r2*cos((n+1)*theta),r2*sin((n+1)*theta),0);
			glVertex3f(r2*cos(n*theta),r2*sin(n*theta),0);
			glEnd();

			glNormal3f(0,0,1);
			glBegin(GL_LINE_LOOP);
			glVertex3f(r3*cos(n*theta),r3*sin(n*theta),h);
			glVertex3f(r3*cos((n+1)*theta),r3*sin((n+1)*theta),h);
			glVertex3f(r4*cos((n+1)*theta),r4*sin((n+1)*theta),h);
			glVertex3f(r4*cos(n*theta),r4*sin(n*theta),h);
			glEnd();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
myBall::myBall()
{
	R=0;
	obj=gluNewQuadric();
}

myBall::myBall(float _R)
{
	R=_R;
	obj=gluNewQuadric();
}

void myBall::SolidDraw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(obj,R,(int)R*100+5,(int)R*100+5);
}

void myBall::WireDraw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	gluSphere(obj,R,(int)R*100+5,(int)R*100+5);
}

void myBall::SetBall(float _R)
{
	R=_R;
	obj=gluNewQuadric();
}

//////////////////////////////////////////////////////////////////////////
myCube::myCube()
{
	Size=1;
}

myCube::myCube(float _size)
{
	Size=_size;
}

void myCube::SetCube(float _size)
{
	Size=_size;
}

void myCube::SetCube(myCube c)
{
	*this=c;
}

void myCube::SolidDraw()
{
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glVertex3f(-Size/2,-Size/2,-Size/2);
	glVertex3f(Size/2,-Size/2,-Size/2);
	glVertex3f(Size/2,-Size/2,Size/2);
	glVertex3f(-Size/2,-Size/2,Size/2);

	glNormal3f(0,1,0);
	glVertex3f(-Size/2,Size/2,Size/2);
	glVertex3f(Size/2,Size/2,Size/2);
	glVertex3f(Size/2,Size/2,-Size/2);
	glVertex3f(-Size/2,Size/2,-Size/2);

	glNormal3f(-1,0,0);
	glVertex3f(-Size/2,-Size/2,-Size/2);
	glVertex3f(-Size/2,-Size/2,Size/2);
	glVertex3f(-Size/2,Size/2,Size/2);
	glVertex3f(-Size/2,Size/2,-Size/2);

	glNormal3f(0,0,-1);
	glVertex3f(Size/2,-Size/2,-Size/2);
	glVertex3f(-Size/2,-Size/2,-Size/2);
	glVertex3f(-Size/2,Size/2,-Size/2);
	glVertex3f(Size/2,Size/2,-Size/2);

	glNormal3f(1,0,0);
	glVertex3f(Size/2,-Size/2,Size/2);
	glVertex3f(Size/2,-Size/2,-Size/2);
	glVertex3f(Size/2,Size/2,-Size/2);
	glVertex3f(Size/2,Size/2,Size/2);

	glNormal3f(0,0,1);
	glVertex3f(-Size/2,-Size/2,Size/2);
	glVertex3f(Size/2,-Size/2,Size/2);
	glVertex3f(Size/2,Size/2,Size/2);
	glVertex3f(-Size/2,Size/2,Size/2);
	glEnd();
}

void myCube::WireDraw()

{
	glBegin(GL_LINES);
	glVertex3f(-Size/2,-Size/2,-Size/2);
	glVertex3f(Size/2,-Size/2,-Size/2);
	glVertex3f(Size/2,-Size/2,Size/2);
	glVertex3f(-Size/2,-Size/2,Size/2);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-Size/2,Size/2,Size/2);
	glVertex3f(Size/2,Size/2,Size/2);
	glVertex3f(Size/2,Size/2,-Size/2);
	glVertex3f(-Size/2,Size/2,-Size/2);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-Size/2,-Size/2,-Size/2);
	glVertex3f(-Size/2,-Size/2,Size/2);
	glVertex3f(-Size/2,Size/2,Size/2);
	glVertex3f(-Size/2,Size/2,-Size/2);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Size/2,-Size/2,-Size/2);
	glVertex3f(-Size/2,-Size/2,-Size/2);
	glVertex3f(-Size/2,Size/2,-Size/2);
	glVertex3f(Size/2,Size/2,-Size/2);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Size/2,-Size/2,Size/2);
	glVertex3f(Size/2,-Size/2,-Size/2);
	glVertex3f(Size/2,Size/2,-Size/2);
	glVertex3f(Size/2,Size/2,Size/2);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-Size/2,-Size/2,Size/2);
	glVertex3f(Size/2,-Size/2,Size/2);
	glVertex3f(Size/2,Size/2,Size/2);
	glVertex3f(-Size/2,Size/2,Size/2);
	glEnd();
}
