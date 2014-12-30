#include "Texture.h"


myTexture::myTexture(void)
{
}

myTexture::~myTexture(void)
{
}

void myTexture::LoadBMP(char *Filename,GLuint &Texturename,bool IsRGBA/* =false */,float a/* =10 */,bool IsWhite/* =false */)
{
	FILE *File=NULL;
	File=fopen(Filename,"r");
	if (File)
	{
		fclose(File);
		Image1=auxDIBImageLoad(Filename);
	}
	else
	{
		std::string str1="Can't Open The File: ";
		str1+=Filename;
		MessageBox(NULL, str1.c_str(),"Error", MB_OK);
	}
	glGenTextures(1,&Texturename);
	glBindTexture(GL_TEXTURE_2D,Texturename); 
	if (IsRGBA)
	{
		int width,height;
		width=(int)Image1->sizeX; 
		height=(int)Image1->sizeY; 
		unsigned char *texture=new unsigned char [width*height*4];//注意：每个像素占用4个字节，不是原来的3个。 
		for(int i=0;i<width;i++) 
		{ 
			for(int j=0;j<height;j++) 
			{ 
				//把颜色值写入 
				texture[i*height*4+j*4+0] = (GLubyte)*(Image1->data+i*height*3+j*3+0); 
				texture[i*height*4+j*4+1] = (GLubyte)*(Image1->data+i*height*3+j*3+1); 
				texture[i*height*4+j*4+2] = (GLubyte)*(Image1->data+i*height*3+j*3+2); 
				if (IsWhite)
				{
					//设置alpha值,默认黑色为透明色 
					if(255-texture[i*height*4+j*4+0]<a &&
						255-texture[i*height*4+j*4+1]<a &&
						255-texture[i*height*4+j*4+2]<a) 
						texture[i*height*4+j*4+3] = 0;                 //透明，设为 0 
					else 
						texture[i*height*4+j*4+3] = 255;            //不透明，设为 255, 也就是以后用的1.0 
				} 
				else
				{
					//设置alpha值,默认黑色为透明色 
					if(texture[i*height*4+j*4+0]<a && 
						texture[i*height*4+j*4+1]<a && 
						texture[i*height*4+j*4+2]<a) 
						texture[i*height*4+j*4+3] = 0;                 //透明，设为 0 
					else 
						texture[i*height*4+j*4+3] = 255;            //不透明，设为 255, 也就是以后用的1.0 
				}
			} 
		} 
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,width,height,GL_RGBA,GL_UNSIGNED_BYTE,texture);
		delete [] texture;
	} 
	else
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,Image1->sizeX,Image1->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image1->data);
	}
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	if (Image1)
	{
		if (Image1->data)
		{
			free(Image1->data);
		}
		free(Image1);
		// 		cout<<"free the file: "<<Filename<<endl;
	}
}

//////////////////////////////////////////////////////////////////////////
TextureBox::TextureBox()
{
	SetBox(1);
}

TextureBox::TextureBox(float _size)
{
	SetBox(_size);
}

void TextureBox::SetBox(float _size)
{
	Size=_size;
	normal[0].SetVector(0,0,1);
	normal[1].SetVector(1,0,0);
	normal[2].SetVector(0,0,-1);
	normal[3].SetVector(-1,0,0);
	normal[4].SetVector(0,1,0);
	normal[5].SetVector(0,-1,0);
}

void TextureBox::SetSize(float _size)
{
	Size=_size;
}

void TextureBox::ReverseNormal()
{
	for (int i=0;i<6;i++)
	{
		normal[i].flip();
	}
}

void TextureBox::Draw6(GLuint (&tex)[6],float num1/* =1 */,float num2/* =1 */)
{
	glBindTexture(GL_TEXTURE_2D,tex[5]);
	glNormal3f(normal[5].x,normal[5].y,normal[5].z);
	glBegin(GL_QUADS);
	glTexCoord2f(num2,0);	glVertex3f(-Size/2,-Size/2,-Size/2);
	glTexCoord2f(0,0);glVertex3f(Size/2,-Size/2,-Size/2);
	glTexCoord2f(0,num2);	glVertex3f(Size/2,-Size/2,Size/2);
	glTexCoord2f(num2,num2);		glVertex3f(-Size/2,-Size/2,Size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[4]);
	glNormal3f(normal[4].x,normal[4].y,normal[4].z);
	glBegin(GL_QUADS);
	glTexCoord2f(num1,num1);glVertex3f(-Size/2,Size/2,Size/2);
	glTexCoord2f(0,num1);	glVertex3f(Size/2,Size/2,Size/2);
	glTexCoord2f(0,0);		glVertex3f(Size/2,Size/2,-Size/2);
	glTexCoord2f(num1,0);	glVertex3f(-Size/2,Size/2,-Size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[3]);
	glNormal3f(normal[3].x,normal[3].y,normal[3].z);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-Size/2,-Size/2,-Size/2);
	glTexCoord2f(1,0);glVertex3f(-Size/2,-Size/2,Size/2);
	glTexCoord2f(1,1);glVertex3f(-Size/2,Size/2,Size/2);
	glTexCoord2f(0,1);glVertex3f(-Size/2,Size/2,-Size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[2]);
	glNormal3f(normal[2].x,normal[2].y,normal[2].z);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(Size/2,-Size/2,-Size/2);
	glTexCoord2f(1,0);glVertex3f(-Size/2,-Size/2,-Size/2);
	glTexCoord2f(1,1);glVertex3f(-Size/2,Size/2,-Size/2);
	glTexCoord2f(0,1);glVertex3f(Size/2,Size/2,-Size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[1]);
	glNormal3f(normal[1].x,normal[1].y,normal[1].z);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(Size/2,-Size/2,Size/2);
	glTexCoord2f(1,0);glVertex3f(Size/2,-Size/2,-Size/2);
	glTexCoord2f(1,1);glVertex3f(Size/2,Size/2,-Size/2);
	glTexCoord2f(0,1);glVertex3f(Size/2,Size/2,Size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glNormal3f(normal[0].x,normal[0].y,normal[0].z);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);glVertex3f(-Size/2,-Size/2,Size/2);
	glTexCoord2f(1,0);glVertex3f(Size/2,-Size/2,Size/2);
	glTexCoord2f(1,1);glVertex3f(Size/2,Size/2,Size/2);
	glTexCoord2f(0,1);glVertex3f(-Size/2,Size/2,Size/2);
	glEnd();
}

void TextureBox::Draw2(GLuint tex2,GLuint tex4,
						float tex2Num/* =1 */,float tex4Num/* =1 */,
						bool IsDoor/* =false */)
{
	glBindTexture(GL_TEXTURE_2D,tex2);
	glBegin(GL_QUADS);
	glNormal3f(normal[5].x,normal[5].y,normal[5].z);
	glTexCoord2f(0,0);				glVertex3f(-Size/2,-Size/2,-Size/2);
	glTexCoord2f(tex2Num,0);		glVertex3f(Size/2,-Size/2,-Size/2);
	glTexCoord2f(tex2Num,tex2Num);	glVertex3f(Size/2,-Size/2,Size/2);
	glTexCoord2f(0,tex2Num);		glVertex3f(-Size/2,-Size/2,Size/2);

	glNormal3f(normal[4].x,normal[4].y,normal[4].z);
	glTexCoord2f(0,0);				glVertex3f(-Size/2,Size/2,Size/2);
	glTexCoord2f(tex2Num,0);		glVertex3f(Size/2,Size/2,Size/2);
	glTexCoord2f(tex2Num,tex2Num);	glVertex3f(Size/2,Size/2,-Size/2);
	glTexCoord2f(0,tex2Num);		glVertex3f(-Size/2,Size/2,-Size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex4);
	glBegin(GL_QUADS);
	glNormal3f(normal[3].x,normal[3].y,normal[3].z);
	glTexCoord2f(0,0);				glVertex3f(-Size/2,-Size/2,-Size/2);
	glTexCoord2f(tex4Num,0);		glVertex3f(-Size/2,-Size/2,Size/2);
	glTexCoord2f(tex4Num,tex4Num);	glVertex3f(-Size/2,Size/2,Size/2);
	glTexCoord2f(0,tex4Num);		glVertex3f(-Size/2,Size/2,-Size/2);

	glNormal3f(normal[2].x,normal[2].y,normal[2].z);
	glTexCoord2f(0,0);				glVertex3f(Size/2,-Size/2,-Size/2);
	glTexCoord2f(tex4Num,0);		glVertex3f(-Size/2,-Size/2,-Size/2);
	glTexCoord2f(tex4Num,tex4Num);	glVertex3f(-Size/2,Size/2,-Size/2);
	glTexCoord2f(0,tex4Num);		glVertex3f(Size/2,Size/2,-Size/2);

	glNormal3f(normal[1].x,normal[1].y,normal[1].z);
	glTexCoord2f(0,0);				glVertex3f(Size/2,-Size/2,Size/2);
	glTexCoord2f(tex4Num,0);		glVertex3f(Size/2,-Size/2,-Size/2);
	glTexCoord2f(tex4Num,tex4Num);	glVertex3f(Size/2,Size/2,-Size/2);
	glTexCoord2f(0,tex4Num);		glVertex3f(Size/2,Size/2,Size/2);
	glEnd();

	glNormal3f(normal[0].x,normal[0].y,normal[0].z);
	if (IsDoor)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);					glVertex3f(-Size/2,-Size/2,Size/2);
		glTexCoord2f(tex4Num/3,0);			glVertex3f(-Size/6,-Size/2,Size/2);
		glTexCoord2f(tex4Num/3,tex4Num);	glVertex3f(-Size/6,Size/2,Size/2);
		glTexCoord2f(0,tex4Num);			glVertex3f(-Size/2,Size/2,Size/2);

		glTexCoord2f(tex4Num/3,tex4Num/2);	glVertex3f(-Size/6,0,Size/2);
		glTexCoord2f(2*tex4Num/3,tex4Num/2);glVertex3f(Size/6,0,Size/2);
		glTexCoord2f(2*tex4Num/3,tex4Num);	glVertex3f(Size/6,Size/2,Size/2);
		glTexCoord2f(tex4Num/3,tex4Num);	glVertex3f(-Size/6,Size/2,Size/2);

		glTexCoord2f(2*tex4Num/3,0);		glVertex3f(Size/6,-Size/2,Size/2);
		glTexCoord2f(tex4Num,0);			glVertex3f(Size/2,-Size/2,Size/2);
		glTexCoord2f(tex4Num,tex4Num);		glVertex3f(Size/2,Size/2,Size/2);
		glTexCoord2f(2*tex4Num/3,tex4Num);	glVertex3f(Size/6,Size/2,Size/2);
		glEnd();
	} 
	else
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);				glVertex3f(-Size/2,-Size/2,Size/2);
		glTexCoord2f(tex4Num,0);		glVertex3f(Size/2,-Size/2,Size/2);
		glTexCoord2f(tex4Num,tex4Num);	glVertex3f(Size/2,Size/2,Size/2);
		glTexCoord2f(0,tex4Num);		glVertex3f(-Size/2,Size/2,Size/2);
		glEnd();
	}
}

//////////////////////////////////////////////////////////////////////////
TexCylider::TexCylider()
{
	obj=gluNewQuadric();
	Set(1,1,1,5,5);
}

TexCylider::TexCylider(float _bR,float _tR,float _h,int _slices,int _stacks)
{
	obj=gluNewQuadric();
	Set(_bR,_tR,_h,_slices,_stacks);
}

void TexCylider::Set(float _bR,float _tR,float _h,int _slices,int _stacks)
{
	bR=_bR,tR=_tR,h=_h,slices=_slices,stacks=_stacks;
}

void TexCylider::Draw(GLint tex)
{
	glBindTexture(GL_TEXTURE_2D,tex);
	gluQuadricNormals(obj, GLU_SMOOTH);	// 使用平滑法线
	gluQuadricTexture(obj, GL_TRUE);	// 使用纹理用了之后就可以贴上图了
	gluCylinder(obj,bR,tR,h,slices,stacks);
	gluQuadricTexture(obj, GL_FALSE);
}

//////////////////////////////////////////////////////////////////////////
TexDisk::TexDisk()
{
	obj=gluNewQuadric();
	Set(0,1,20,20);
}

TexDisk::TexDisk(float _iR,float _oR,int _slices,int _loops)
{
	obj=gluNewQuadric();
	Set(_iR,_oR,_slices,_loops);
}

void TexDisk::Set(float _iR,float _oR,int _slices,int _loops)
{
	iR=_iR,oR=_oR,slices=_slices,loops=_loops;
}

void TexDisk::Draw(GLuint tex)
{
	glBindTexture(GL_TEXTURE_2D,tex);
	gluQuadricNormals(obj, GLU_SMOOTH);	// 使用平滑法线
	gluQuadricTexture(obj, GL_TRUE);	// 使用纹理用了之后就可以贴上图了
	gluDisk(obj,iR,oR,slices,loops);
	gluQuadricTexture(obj, GL_FALSE);
}

//////////////////////////////////////////////////////////////////////////
TexSphere::TexSphere()
{
	obj=gluNewQuadric();
	Set(1,50,50);
}

TexSphere::TexSphere(float _R,int _slices,int _stacks)
{
	obj=gluNewQuadric();
	Set(_R,_slices,_stacks);
}

void TexSphere::Set(float _R,int _slices,int _stacks)
{
	R=_R,slices=_slices,stacks=_stacks;
}

void TexSphere::Draw(GLuint tex)
{
	glBindTexture(GL_TEXTURE_2D,tex);
	gluQuadricNormals(obj, GLU_SMOOTH);	// 使用平滑法线
	gluQuadricTexture(obj, GL_TRUE);	// 使用纹理用了之后就可以贴上图了
	gluSphere(obj,R,slices,stacks);
	gluQuadricTexture(obj, GL_FALSE);
}

//////////////////////////////////////////////////////////////////////////
Door::Door()
{
	theta=0,IsOpen=false;
}

void Door::Draw2(GLuint tex2,GLint tex4)
{
	glPushMatrix();
	glTranslatef(0.667*Size/2,0,0);
	glRotatef(-theta,0,1,0);
	glTranslatef(-0.667*Size/2,0,0);
	if (IsOpen)
	{
		theta+=0.1;
		if (theta>90)
		{
			theta=90;
		}
	} 
	else
	{
		theta-=0.1;
		if (theta<0)
		{
			theta=0;
		}
	}
	TextureBox::Draw2(tex2,tex4);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
TexturePiece::TexturePiece()
{
	Set(1,1);
}

TexturePiece::TexturePiece(float w, float h)
{
	Set(w,h);
}

void TexturePiece::Set(float w,float h)
{
	width=w,height=h;
	myVector right(1,0,0);
	myVector up(0,1,0);
	right=right*(width/2);up=up*(height/2);
	pos0=pos-(up+right);
	pos1=pos+(right-up);
	pos2=pos+(up+right);
	pos3=pos+(up-right);
}

void TexturePiece::SetPos(myVector _pos)
{
	myVector right(1,0,0);
	myVector up(0,1,0);
	right=right*(width/2);up=up*(height/2);
	pos.SetVector(_pos);
	pos0=pos-(up+right);
	pos1=pos+(right-up);
	pos2=pos+(up+right);
	pos3=pos+(up-right);
}

void TexturePiece::Update()
{
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	myVector right(m[0],m[4],m[8]);
	myVector up(m[1],m[5],m[9]);
	right.normalize();up.normalize();
	right=right*(width/2);up=up*(height/2);
	pos0=pos-(up+right);
	pos1=pos+(right-up);
	pos2=pos+(up+right);
	pos3=pos+(up-right);
}

void TexturePiece::Draw(GLuint _tex, bool IsDynamic/* =false */, float Wtexnum/* =1 */, float Htexnum/* =1 */)
{
	if (IsDynamic)
	{
		Update();
	} 
	glBindTexture(GL_TEXTURE_2D,_tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);				glVertex3f(pos0.x,pos0.y,pos0.z);
	glTexCoord2f(Wtexnum,0);		glVertex3f(pos1.x,pos1.y,pos1.z);
	glTexCoord2f(Wtexnum,Htexnum);	glVertex3f(pos2.x,pos2.y,pos2.z);
	glTexCoord2f(0,Htexnum);		glVertex3f(pos3.x,pos3.y,pos3.z);
	glEnd();
}