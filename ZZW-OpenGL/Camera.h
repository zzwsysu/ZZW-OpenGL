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
	//�������ܣ�ƽ�ƻ���
	//du������u��Ĳ�����dv������v��Ĳ�����dn������n��Ĳ���
	void Slide(float du, float dv, float dn);
	//////////////////////////////////////////////////////////////////////////
	//�������ܣ�����n��ת��
	//����������ܲ��Ǻܳ��ã���������Yaw��Pitch�������Զ�����Roll��Ч��
	//�����ϣ�����Ƹ�Ч������ô��ý�Yaw��Pitch���������SetViewCoord()�������
	void Roll(float angle);
	//////////////////////////////////////////////////////////////////////////
	//�������ܣ�����v��ת��
	void Yaw(float angle);
	//////////////////////////////////////////////////////////////////////////
	//�������ܣ�����u��ת��
	void Pitch(float angle);
	//////////////////////////////////////////////////////////////////////////
	//�������ܣ��������������е�y��ת��
	void Rotate(double angle);

	Point3D GetLook();
	Point3D GetEye();
	myVector GetUp();
};

#endif

