#ifndef _CAMERA_
#define _CAMERA_

#include <math.h>
#include "Geometry.h"

class Camera
{
private:
	Point3D Eye,Look;
	myVector u,v,n,up,eyeV;
	float viewAngle, Aspect, nearDist,farDis;
	float m_fleft, m_fright, m_ftop, m_fbottom;
	float m[16];
	void SetModelViewMatrix();
	void SetViewCoord();
	void rotateAxis(myVector &a, myVector &b, float angle);
public:
	Camera(void);
	Camera(Point3D eye, Point3D look, myVector _up);
	Camera(float eyex,float eyey,float eyez, float lookx,float looky,float lookz, float upx,float upy,float upz);
	void SetCamera();
	void SetCamera(Point3D eye, Point3D look, myVector _up);
	void SetCamera(float eyex,float eyey,float eyez, float lookx,float looky,float lookz, float upx,float upy,float upz);
	void SetPerspective(float angle, float aspect, float Near, float Far);
	void SetOrtho(float _left, float _right, float _bottom, float _top, float _near, float _far);
	void SetEye(float x,float y,float z);
	void SetLook(float x,float y,float z);
	//////////////////////////////////////////////////////////////////////////
	//函数功能：平移滑动
	//du是沿着u轴的步长，dv是沿着v轴的步长，dn是沿着n轴的步长
	void Slide(float du, float dv, float dn);
	//////////////////////////////////////////////////////////////////////////
	//函数功能：绕着n轴转动
	//由于这个功能不是很常用，因此下面的Yaw和Pitch函数会自动消除Roll的效果
	//如果不希望限制该效果，那么最好将Yaw和Pitch函数里面的SetViewCoord()语句消除
	void Roll(float angle);
	//////////////////////////////////////////////////////////////////////////
	//函数功能：绕着v轴转动
	void Yaw(float angle);
	//////////////////////////////////////////////////////////////////////////
	//函数功能：绕着u轴转动
	void Pitch(float angle);
	//////////////////////////////////////////////////////////////////////////
	//函数功能：绕着世界坐标中的y轴转动
	void Rotate(double angle);

	Point3D GetLook();
	Point3D GetEye();
	myVector GetUp();
};

#endif

