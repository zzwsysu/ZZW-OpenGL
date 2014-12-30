#include "Geometry.h"
#include "Texture.h"
#include "Materail.h"
#include "Camera.h"
#include "Light.h"
#include "Particle.h"

class Scene
{
private:
	myTexture t1;
	TextureBox skyBox;
	GLuint sky[6],snow,butter1,butter2,butter3,cs;
	Snows snows;
#define butter_num 20
	Butterflys butterflys1,butterflys2,butterflys3;
	A_particles As;
#define B_MAXNUM 10
	B_particles Bs[B_MAXNUM];
	C_particles Cs[3][butter_num];
	D_particles Ds;
	void BackGround();
	void Butterfly();
	void Charry();
	void Asplay();
	void Bsplay();
public:
	bool IsButter,IsCharry,IsAs,IsBs;
	Camera cam;
	Scene();
	void SetTexture();
	void Draw();
};

