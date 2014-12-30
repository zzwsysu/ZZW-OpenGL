#include "Scene.h"

Scene::Scene()
{
	skyBox.SetSize(1000);
	skyBox.ReverseNormal();
	Particle particle0;
	particle0.size=0.5;
	snows.SetParticles(8000,particle0);
	butterflys1.SetParticles(butter_num,particle0);
	butterflys2.SetParticles(butter_num,particle0);
	butterflys3.SetParticles(butter_num,particle0);
	particle0.size=0.1;
	As.SetParticles(100,particle0);
	for (int i=0;i<B_MAXNUM;i++)
	{
		Bs[i].SetParticles(100,particle0);
	}
	for (int j=0;j<3;j++)
	{
		for (int i=0;i<butter_num;i++)
		{
			Cs[j][i].SetParticles(50,particle0);
		}
	}
	Ds.SetParticles(20,particle0);
}

void Scene::SetTexture()
{
	t1.LoadBMP("data\\skybox\\FullMoonBack2048.bmp",sky[0]);
	t1.LoadBMP("data\\skybox\\FullMoonRight2048.bmp",sky[1]);
	t1.LoadBMP("data\\skybox\\FullMoonFront2048.bmp",sky[2]);
	t1.LoadBMP("data\\skybox\\FullMoonLeft2048.bmp",sky[3]);
	t1.LoadBMP("data\\skybox\\FullMoonUp2048.bmp",sky[4]);
	t1.LoadBMP("data\\skybox\\FullMoonDown2048.bmp",sky[5]);
	t1.LoadBMP("data\\»¨°ê1.bmp",snow,true);
	t1.LoadBMP("data\\Butterfly1.bmp",butter1,true);
	t1.LoadBMP("data\\Butterfly2.bmp",butter2,true);
	t1.LoadBMP("data\\Butterfly3.bmp",butter3,true);
	t1.LoadBMP("data\\Star.bmp",cs,true);
}

void Scene::BackGround()
{
	glPushMatrix();
	glRotatef(-90,0,1,0);
	skyBox.Draw6(sky);
	glPopMatrix();
}

void Scene::Butterfly()
{
	butterflys1.Play(butter1,0.1);
	butterflys2.Play(butter2,0.1);
	butterflys3.Play(butter3,0.1);
	for (int i=0;i<butter_num;i++)
	{
		Particle p1=butterflys1.GetParticle(i);
		Area a1(p1.pos0,p1.v0,p1.a0,0);
		Cs[0][i].SetArea(a1);
		Cs[0][i].Play(cs,0.005,true);
		Particle p2=butterflys2.GetParticle(i);
		Area a2(p2.pos0,p2.v0,p2.a0,0);
		Cs[1][i].SetArea(a2);
		Cs[1][i].Play(cs,0.005,true);
		Particle p3=butterflys3.GetParticle(i);
		Area a3(p3.pos0,p3.v0,p3.a0,0);
		Cs[2][i].SetArea(a3);
		Cs[2][i].Play(cs,0.005,true);
	}
}

void Scene::Charry()
{
	snows.Play(snow,0.02,true);
}

void Scene::Asplay()
{
	glPushMatrix();
	glRotatef(90,0,0,1);
	As.Play(cs,0.02,true);
	Ds.Play(cs,0.01,true);
	glPushMatrix();
	glRotatef(180,0,1,0);
	Ds.Play(cs,0.01,true);
	glPopMatrix();
	glPopMatrix();
}

void Scene::Bsplay()
{
	for (int i=0;i<B_MAXNUM;i++)
	{
		Bs[i].Play(cs,0.03,true);
	}
}

void Scene::Draw()
{
	BackGround();
	if (IsButter)
	{
		Butterfly();
	}
	if (IsCharry)
	{
		Charry();
	}
	if (IsAs)
	{
		Asplay();
	}
	if (IsBs)
	{
		Bsplay();
	}
}