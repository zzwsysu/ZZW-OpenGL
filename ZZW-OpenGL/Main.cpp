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

int mybutton=-1;	//陣崙報炎梓囚
int OldX,OldY;		//喘栖芝村輝念報炎議了崔

bool IsFullScreen;	//登僅頁倦畠徳

Camera cam;
Scene scene;
CMciMgr BackGround_Music;

/************************************************************************/
/* 零丼痕方                                                             */
/************************************************************************/
void Fog()
{
	float color[4] = { 1, 1, 1, 0.1 };
	glEnable(GL_FOG);				// enable fog effect
	glFogi(GL_FOG_MODE,GL_LINEAR);		// 柴麻庁侏匆辛參個葎GL_EXP2賜GL_LINEAR
	glFogfv(GL_FOG_COLOR, color);	// 零議冲弼
	glFogf(GL_FOG_DENSITY, 0.02);	// 零議敵業
	glHint(GL_FOG_HINT,GL_NICEST);  // 柴麻麻隈��辛個葎GL_NICEST賜GL_FASTEST
	glFogf(GL_FOG_START, 1.0);		// 譜崔軟泣
	glFogf(GL_FOG_END, 3.0);		// 譜崔嶮泣
}

/************************************************************************/
/* OpenGL兜兵晒痕方                                                     */
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
/* 囚徒梓囚痕方                                                         */
/************************************************************************/
void myKeyboard(unsigned char theKey, int x, int y)
{
	switch(theKey)
	{
	case 27:										//梓Esc囚曜竃
		exit(0);
		break;
	case 13:										//梓Enter囚俳算畠徳
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
/* 蒙歩梓囚痕方                                                         */
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
/* 報炎�贄�痕方                                                         */
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
/* 報炎卞強痕方                                                         */
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
/* 暇汽�贄�痕方                                                         */
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
		BackGround_Music.open("data\\鮭刔遠 - 笹魚.mp3");
		BackGround_Music.playloop();
		break;
	case 2:
		scene.IsButter=false;
		scene.IsCharry=true;
		scene.IsAs=false;
		scene.IsBs=false;
		BackGround_Music.close();
		BackGround_Music.open("data\\錆遊麹岻柾 劑凩なる.mp3");
		BackGround_Music.playloop();
		break;
	case 3:
		scene.IsButter=false;
		scene.IsCharry=false;
		scene.IsAs=true;
		scene.IsBs=false;
		BackGround_Music.close();
		BackGround_Music.open("data\\錆遊麹岻柾 侶れをまとう.mp3");
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
/* 紙崙痕方                                                             */
/************************************************************************/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//賠茅魁尚

	scene.Draw();

	glutSwapBuffers();
}

void main(int argc, char* argv[])
{
	glClearColor(0,0,0,0);						//喘菜弼賠腎�塋焦�囃
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_MULTISAMPLE);	//畳協阻�坿耿亢墫Φ掴塋焦�囃
	glutInitWindowSize(760,570);				//譜崔完笥議寄弌
	glutInitWindowPosition(0,0);				//譜崔完笥議了崔
	glutInit(&argc,argv);
	glutCreateWindow("zzw");					//仟秀完笥

	// 光嶽指距痕方
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialkey);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	//兜兵晒OpenGL
	myInit();

	//幹秀暇汽�贄�痕方��旺溢協嶄囚起竃暇汽
	glutCreateMenu(myMenu);
	glutAddMenuEntry("show butterfly", 1);
	glutAddMenuEntry("show Charry", 2);
	glutAddMenuEntry("show A_particles", 3);
	glutAddMenuEntry("show B_particles", 4);
	glutAddMenuEntry("Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}