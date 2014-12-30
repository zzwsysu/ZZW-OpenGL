#include "Camera.h"

#define PI 3.1415926535897932384626433832795

Camera::Camera(void)
{
	SetPerspective(45,1.0,0.1,50000);
	SetCamera(1,1,1, 0,0,0, 0,1,0);
}

Camera::Camera(Point3D eye, Point3D look, myVector _up)
{
	SetPerspective(45,1.0,0.1,50000);
	SetCamera(eye,look,_up);
}

Camera::Camera(float eyex,float eyey,float eyez, float lookx,float looky,float lookz, float upx,float upy,float upz)
{
	SetPerspective(45,1.0,0.1,500);
	SetCamera(eyex,eyey,eyez, lookx,looky,lookz, upx,upy,upz);
}

void Camera::SetViewCoord()
{
	n.SetVector(Look,Eye);
	u.SetVector(up.cross(n));
	v.SetVector(n.cross(u));
	n.normalize();u.normalize();v.normalize();
}

void Camera::SetCamera()
{
	SetViewCoord();
	SetModelViewMatrix();
}

void Camera::SetCamera(Point3D eye, Point3D look, myVector _up)
{
	Eye.Setpoint(eye);
	Look.Setpoint(look);
	up.SetVector(_up);
	SetCamera();
}

void Camera::SetCamera(float eyex,float eyey,float eyez, float lookx,float looky,float lookz, float upx,float upy,float upz)
{
	Point3D eye(eyex,eyey,eyez);
	Point3D look(lookx,looky,lookz);
	myVector _up(upx,upy,upz);
	SetCamera(eye,look,_up);
}

void Camera::SetModelViewMatrix()
{
	eyeV.SetVector(Eye.x,Eye.y,Eye.z);
	m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eyeV.dot(u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eyeV.dot(v);
	m[2] = n.x; m[6] = n.y; m[10]= n.z; m[14] = -eyeV.dot(n);
	m[3] = 0  ; m[7] = 0  ; m[11]= 0  ; m[15] = 1.0         ;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::SetPerspective(float angle, float aspect, float Near, float Far)
{
	viewAngle=angle;
	Aspect=aspect;
	nearDist=Near;
	farDis=Far;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle,Aspect,nearDist,farDis);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::SetOrtho(float _left, float _right, float _bottom, float _top, float _near, float _far)
{
	m_fleft=_left;
	m_fright=_right;
	m_ftop=_top;
	m_fbottom=_bottom;
	nearDist=_near;
	farDis=_far;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_fleft,m_fright,m_fbottom,m_ftop,nearDist,farDis);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::SetEye(float x,float y,float z)
{
	Eye.x=x,Eye.y=y,Eye.z=z;
	SetViewCoord();
	SetModelViewMatrix();
}

void Camera::SetLook(float x,float y,float z)
{
	Look.Setpoint(x,y,z);
	SetViewCoord();
	SetModelViewMatrix();
}

void Camera::Slide(float du, float dv, float dn)
{
	Eye.x+=du*u.x+dv*v.x+dn*n.x;
	Eye.y+=du*u.y+dv*v.y+dn*n.y;
	Eye.z+=du*u.z+dv*v.z+dn*n.z;
	myVector v1(n.x,n.y,n.z);
	v1.flip();
	Look=Eye+v1;
	SetModelViewMatrix();
}

void Camera::rotateAxis(myVector &a, myVector &b, float angle)
{
	float theta=PI/180*angle;
	myVector t(cos(theta)*a.x+sin(theta)*b.x,
				cos(theta)*a.y+sin(theta)*b.y,
				cos(theta)*a.z+sin(theta)*b.z);
	b.SetVector(-sin(theta)*a.x+cos(theta)*b.x,
				-sin(theta)*a.y+cos(theta)*b.y,
				-sin(theta)*a.z+cos(theta)*b.z);
	a.SetVector(t.x,t.y,t.z);
}

void Camera::Roll(float angle)
{
	rotateAxis(u,v,angle);
// 	up=v;
	SetModelViewMatrix();
}

void Camera::Yaw(float angle)
{
	rotateAxis(n,u,angle);
	myVector v1(n);
	v1.flip();
	Look=Eye+v1;
	SetViewCoord();//防止用鼠标控制相机视角的时候会造成出现Roll的情况
	SetModelViewMatrix();
}

void Camera::Pitch(float angle)
{
	rotateAxis(v,n,angle);
	myVector v1(n);
	v1.flip();
	Look=Eye+v1;
	SetViewCoord();//防止用鼠标控制相机视角的时候会造成出现Roll的情况
	SetModelViewMatrix();
}

void Camera::Rotate(double angle)
{
	up.SetVector(0,1,0);
	Look.Setpoint(0,Eye.y,0);
	float r=sqrtf(Eye.x*Eye.x+Eye.z*Eye.z);
	Eye.x=Eye.x*cos(angle)+Eye.z*sin(angle);
	Eye.z=-Eye.x*sin(angle)+Eye.z*cos(angle);
	myVector v1(Eye.x,0,Eye.z);
	v1.normalize();
	Eye.x=r*v1.x;Eye.z=r*v1.z;
	SetViewCoord();
	SetModelViewMatrix();
}

Point3D Camera::GetLook()
{
	return Look;
}

Point3D Camera::GetEye()
{
	return Eye;
}

myVector Camera::GetUp()
{
	return up;
}
