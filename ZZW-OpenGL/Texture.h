#ifndef _M_Y_TEXTURE
#define _M_Y_TEXTURE

#include <stdio.h>
#include <IOSTREAM>
using namespace std;
#include <gl/GLAUX.H>
#include <gl/glut.h>
#include "Geometry.h"

#pragma comment (lib,"glaux.lib")

class myTexture
{
private:
	AUX_RGBImageRec *Image1;
public:
	myTexture(void);
	~myTexture(void);
	void LoadBMP(char *Filename,GLuint &Texturename,bool IsRGBA=false,float a=10,bool IsWhite=false);
};

class TextureBox
{
protected:
	myVector normal[6];
	float Size;
public:
	TextureBox();
	TextureBox(float _size);
	void SetBox(float _size);
	void SetSize(float _size);
	void ReverseNormal();
	//////////////////////////////////////////////////////////////////////////
	//tex[6]分别是前后左右上下的纹理；num1，num2分别是上下的纹理重复数
	void Draw6(GLuint (&tex)[6],float num1=1,float num2=1);
	//////////////////////////////////////////////////////////////////////////
	//tex2是上下的纹理，tex4是前后左右的纹理
	void Draw2(GLuint tex2,GLuint tex4, float tex2Num=1,float tex4Num=1,bool IsDoor=false);
};

class TexCylider
{
private:
	float bR,tR,h;
	int slices,stacks;
	GLUquadric *obj;
public:
	TexCylider();
	TexCylider(float _bR,float _tR,float _h,int _slices,int _stacks);
	void Set(float _bR,float _tR,float _h,int _slices,int _stacks);
	float GetbR(){return bR;}
	float GettR(){return tR;}
	float Geth(){return h;}
	void Draw(GLint tex);
};

class TexDisk
{
private:
	float iR,oR;
	int slices,loops;
	GLUquadric *obj;
public:
	TexDisk();
	TexDisk(float _iR,float _oR,int _slices,int _loops);
	void Set(float _iR,float _oR,int _slices,int _loops);
	float GetiR(){return iR;}
	float GetoR(){return oR;}
	void Draw(GLuint tex);
};

class TexSphere
{
private:
	float R;
	int slices,stacks;
	GLUquadric *obj;
public:
	TexSphere();
	TexSphere(float _R,int _slices,int _stacks);
	void Set(float _R,int _slices,int _stacks);
	float GetR(){return R;}
	void Draw(GLuint tex);
};

class Door:public TextureBox
{
private:
	float theta;
public:
	bool IsOpen;
	Door();
	void Draw2(GLuint tex2,GLint tex4);
};

class TexturePiece
{
private:
	float width,height;
	myVector pos,pos0,pos1,pos2,pos3;
	void Update();
public:
	TexturePiece();
	TexturePiece(float w, float h);
	void Set(float w,float h);
	void SetPos(myVector _pos);
	void Draw(GLuint _tex, bool IsDynamic=false, float Wtexnum=1, float Htexnum=1);
};

#endif

