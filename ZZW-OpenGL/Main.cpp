#include "Scene.h"
#include <GL/glut.h>
#include "gl/glaux.h"
#include "MP3Player.h"

#pragma comment (lib,"glaux.lib")

#define PI 3.1415926535897932384626433832795

enum
{
	BUTTUN_LEFT,
	BUTTUN_RIGHT,
	BUTTON_MIDDLE,
};

int mybutton=-1;	//������갴��
int OldX,OldY;		//������¼��ǰ����λ��

bool IsFullScreen;	//�ж��Ƿ�ȫ��

Camera cam;
Scene scene;
CMciMgr BackGround_Music;

/************************************************************************/
/* ��Ч����                                                             */
/************************************************************************/
void Fog()
{
	float color[4] = { 1, 1, 1, 0.1 };
	glEnable(GL_FOG);				// enable fog effect
	glFogi(GL_FOG_MODE,GL_LINEAR);		// ����ģ��Ҳ���Ը�ΪGL_EXP2��GL_LINEAR
	glFogfv(GL_FOG_COLOR, color);	// �����ɫ
	glFogf(GL_FOG_DENSITY, 0.02);	// ���Ũ��
	glHint(GL_FOG_HINT,GL_NICEST);  // �����㷨���ɸ�ΪGL_NICEST��GL_FASTEST
	glFogf(GL_FOG_START, 1.0);		// �������
	glFogf(GL_FOG_END, 3.0);		// �����յ�
}

/************************************************************************/
/* OpenGL��ʼ������                                                     */
/************************************************************************/
void myInit()
{
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);  
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	cam.SetCamera(0,0,5, 0,0,0, 0,1,0);
	scene.SetTexture();
}

void reshape ( int w, int h )
{
	glViewport     ( 0, 0, w, h );
	if ( h==0 )
		cam.SetPerspective(45.0, ( float ) w, 0.1, 50000.0);
	else
		cam.SetPerspective(45.0, ( float ) w / ( float ) h, 1.0, 50000.0);
}

/************************************************************************/
/* ���̰�������                                                         */
/************************************************************************/
void myKeyboard(unsigned char theKey, int x, int y)
{
	switch(theKey)
	{
	case 27:										//��Esc���˳�
		exit(0);
		break;
	case 13:										//��Enter���л�ȫ��
		IsFullScreen=!IsFullScreen;
		if (IsFullScreen)
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow(760,570);
			glutPositionWindow(10,30);
		}
		break;
	default:break;
	}
}

/************************************************************************/
/* ���ⰴ������                                                         */
/************************************************************************/
void mySpecialkey(int theSKey, int x, int y)
{
	switch(theSKey)
	{
	case GLUT_KEY_LEFT:
		cam.Slide(-0.1,0,0);
		break;
	case GLUT_KEY_RIGHT:
		cam.Slide(0.1,0,0);
		break;
	case GLUT_KEY_UP:
		cam.Slide(0,0,-0.1);
		break;
	case GLUT_KEY_DOWN:
		cam.Slide(0,0,0.1);
		break;
	case GLUT_KEY_PAGE_UP:
		cam.Slide(0,0.1,0);
		break;
	case GLUT_KEY_PAGE_DOWN:
		cam.Slide(0,-0.1,0);
		break;
	case GLUT_KEY_F1:
		cam.Rotate(-0.1);
		break;
	case GLUT_KEY_F2:
		cam.Rotate(0.1);
		break;
	default:break;
	}
}

/************************************************************************/
/* �����Ӧ����                                                         */
/************************************************************************/
void myMouse(int button,int state,int x,int y)
{
	if (state==GLUT_DOWN)
	{
		OldX=x,OldY=y;
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			mybutton=BUTTUN_LEFT;
			break;
		case GLUT_MIDDLE_BUTTON:
			mybutton=BUTTON_MIDDLE;
			break;
		}
	} 
	else
	{
		mybutton=-1;
	}
}

/************************************************************************/
/* ����ƶ�����                                                         */
/************************************************************************/
void myMotion(int x,int y)
{
	if (mybutton==BUTTUN_LEFT)
	{
		cam.Yaw((float)(OldX-x)/5.0);
		cam.Pitch((float)(OldY-y)/15.0);
		OldX=x,OldY=y;
	} 
	else if (mybutton==BUTTON_MIDDLE)
	{
	}
	else if(mybutton==BUTTUN_RIGHT)
	{
	}
}

/************************************************************************/
/* �˵���Ӧ����                                                         */
/************************************************************************/
void myMenu(int value)
{
	switch(value)
	{
	case 1:
		scene.IsButter=true;
		scene.IsCharry=false;
		scene.IsAs=false;
		scene.IsBs=false;
		BackGround_Music.close();
		BackGround_Music.open("data\\����� - ����.mp3");
		BackGround_Music.playloop();
		break;
	case 2:
		scene.IsButter=false;
		scene.IsCharry=true;
		scene.IsAs=false;
		scene.IsBs=false;
		BackGround_Music.close();
		BackGround_Music.open("data\\��ͷ��֮�� ���ޤʤ�.mp3");
		BackGround_Music.playloop();
		break;
	case 3:
		scene.IsButter=false;
		scene.IsCharry=false;
		scene.IsAs=true;
		scene.IsBs=false;
		BackGround_Music.close();
		BackGround_Music.open("data\\��ͷ��֮�� η���ޤȤ�.mp3");
		BackGround_Music.playloop();
		break;
	case 4:
		scene.IsButter=false;
		scene.IsCharry=false;
		scene.IsAs=false;
		scene.IsBs=true;
		BackGround_Music.close();
		BackGround_Music.open("data\\Bon Jovi - It's My Life.mp3");
		BackGround_Music.playloop();
		break;
	case 5:
		BackGround_Music.close();
		exit(0);
		break;
	}
}

/************************************************************************/
/* ���ƺ���                                                             */
/************************************************************************/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�������

	scene.Draw();

	glutSwapBuffers();
}

void main(int argc, char* argv[])
{
	glClearColor(0,0,0,0);						//�ú�ɫ�����ʾ����
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_MULTISAMPLE);	//�������Դ��ж�Ӧ����ʾ����
	glutInitWindowSize(760,570);				//���ô��ڵĴ�С
	glutInitWindowPosition(0,0);				//���ô��ڵ�λ��
	glutInit(&argc,argv);
	glutCreateWindow("zzw");					//�½�����

	// ���ֻص�����
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialkey);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	//��ʼ��OpenGL
	myInit();

	//�����˵���Ӧ����������м������˵�
	glutCreateMenu(myMenu);
	glutAddMenuEntry("show butterfly", 1);
	glutAddMenuEntry("show Charry", 2);
	glutAddMenuEntry("show A_particles", 3);
	glutAddMenuEntry("show B_particles", 4);
	glutAddMenuEntry("Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}