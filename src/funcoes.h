
typedef struct{
	float x,y,z,w;
}Point;

typedef Point Vector;
typedef Point Color;

typedef struct{
	float r,t,z;
}Cilindro;

typedef struct{
	float v,t;
}Polar;

typedef struct{
	float v,t,f;
}Esferico;

typedef struct{
	Point p;
	Vector v;
	float damage;
	int exist;
}Bullet;

typedef struct{
	Point p;
	Esferico c;
	int exist;
}Voador;

typedef struct{
	Point p;
	Esferico c;
	int exist;
}Cam;

typedef struct{
	Point p;
	float w;
	float h;
	float d;
}CubeColision;

typedef struct{
	Point p;
	float r;
}SphereColision;

typedef struct{
	Point p;
	SphereColision c;
	float damage;
	float hp;
	int exist;
}BombEnemy;

typedef struct{
	Point p;
	CubeColision c;
	int vida;
}Casas;

typedef struct{
	Point p;
	int d;
	int f;
	int exist;
}Explosion;

#define NumCasas 30
#define maxBullets 100
#define bombEnemy 5

int volume_musica=100;
int fade_out = 100;
Mix_Music *musicMenu=NULL;

Bullet bullets[maxBullets];
BombEnemy bombEnemies[bombEnemy];

Casas Casa[NumCasas], Torre;
Explosion explosions[10];
Vector vetorBomba;

int frame, explodiu;

SphereColision Bumb;
Point Explodido;

Point pos={0,-10,-15,1};//Posição

static int slices = 16;
static int stacks = 16;
int desl=4;

int Tampa = 0, TampaAberta=0;
float AnguloTampa =0, ScaleExplosion;

int rotacaoHelice = 0, rotacaoEngrenagem = 0;
int tiro, luz, Armagedom, FramesArmagedom, FramesTorre;

int fog, controleEnemy;
float DensidadeFog, AnguloTorre;

Voador zep;
Point Foco;

Vector vetorCamera;

Point trem;
int trilho;

Voador PontoMetralhadora;
Point MiraMetralhadora;

Point Bomba;
int  LancarBomba=0, FramesBomba=0;
Point PosicaoBase;
Bullet Balas[20];

int Score, Life;

int CAMERA, CAMERAGUN;
Voador posicaoCamera;
Point posicaoCameras;
Point posicaoEsfera;

float cor[] = { .7f, .7f, .7f };

GLuint TerrainTexture;

GLuint *sprite;

GLMmodel *ZepelinOBJ, *CityOBJ, *Base_Missil_L_OBJ, *Base_Missil_R_OBJ, *Eixo_L_OBJ, *Eixo_Missel_L_OBJ, *Eixo_Missel_R_OBJ, *MetrancaOBJ,
*Eixo_R_OBJ, *EngrenagensOBJ, *HeliceP_R_OBJ, *HeliceP_L_OBJ ,*HeliceG_R_OBJ ,*HeliceG_L_OBJ ,*LemeOBJ ,*Minigun_R_OBJ , *Minigun_L_OBJ,*MissilOBJ , *PortaOBJ, *EnemyOBJ, *BombWagonOBJ, *GreatGeorgeOBJ, *HouseOBJ, *LegendaryExpressOBJ, *HorizonteOBJ, *ExposaoOBJ, *House2OBJ, *CenarioOBJ, *BombOBJ, *GreatGeorgeTOBJ, *GreatGeorgeBOBJ, *BombEnemyOBJ, *BombEnemyHOBJ;

void configuraProjecao();
void redimensiona(int width, int height);
void desenhaRetangulo(int x, int y,  int z, int w, int h, int p);
void geraMundo();
void desenha();
static void teclado(unsigned char key, int x, int y);
static void atoa(void);
void ResetaPosicaoCamera();
void DesenhaZepelin();
void ConfiguraIluminacao();
void AjustaCamera();
void AtualizaZepelin();
int C_C_Colision(CubeColision c1,CubeColision c2);
int S_S_Colision(SphereColision c1,SphereColision c2);
int S_C_Colision(SphereColision c1,CubeColision c2);
void ColisionManager();
void DrawBombEnemies(Point p);
void ResetBombEnemy(int i);
void CreateBombEnemy(Point position);
void ManageBombEnemy();
void LoadTexture(char* File,GLuint* T);
void ApplyTexture(GLuint *Texture,Point p, float l, float a,float alpha);
void ResetaTrem();
int C_C_Colision(CubeColision c1,CubeColision c2);
int S_S_Colision(SphereColision c1,SphereColision c2);
int S_C_Colision(SphereColision c1,CubeColision c2);
void ColisionManager();
void CreateBullet(Point p, Vector v);
void ResetBullet(int i);
void DrawBullets();
void ManageBullets();
void DrawBombEnemies(Point p);
void ResetBombEnemy(int i);
void CreateBombEnemy(Point position);
void ManageBombEnemy();
float Norm(Vector v);
Vector SubtractPoints(Point p1,Point p2);
Point AddPoint(Point p,Vector v);
Vector Normalize(Vector v);
Esferico LookAt(Point eye,Point target);
void display();
void texto(void* font, char* s, float x, float y);
int P_C_Colision(Point p,CubeColision c);
int P_S_Colision(Point p,SphereColision c);
void DrawExplosion();
void CreateExplosion(Point p,int d);
void ManageExplosions();
void ResetExplosion(int i);
void ExplodirCasa(int i);
void AtualizaBomba();
void Kabum();



#define AturaMetralhadora 0.24

#define PosicaoCentroHelicePx 3.553
#define PosicaoCentroHelicePz 2.146
#define PosicaoCentroHelicePy 0.178

#define PosicaoCentroHeliceGx 3.682
#define PosicaoCentroHeliceGz -5.565
#define PosicaoCentroHeliceGy -1.45

#define PosicaoLemex 0
#define PosicaoLemey 2.27
#define PosicaoLemez -4.409

#define PosicaoEngrenagemSuperiorx 0
#define PosicaoEngrenagemSuperiory -2.345
#define PosicaoEngrenagemSuperiorz -4.167

#define PosicaoEngrenagemInferiorx 0
#define PosicaoEngrenagemInferiory -2.927
#define PosicaoEngrenagemInferiorz -2.852

#define PosicaoEixoHorizontalMetralhadorax 1.129
#define PosicaoEixoHorizontalMetralhadoray -2.569
#define PosicaoEixoHorizontalMetralhadoraz -2.586

#define PosicaoEixoVerticalMetralhadorax 1.697
#define PosicaoEixoVerticalMetralhadoray -2.569
#define PosicaoEixoVerticalMetralhadoraz -2.586

#define PosicaoEixoHorizontalLancaMissilx 1.129
#define PosicaoEixoHorizontalLancaMissily -2.569
#define PosicaoEixoHorizontalLancaMissilz -0.586

#define PosicaoEixoVerticalLancaMissilx 2.169
#define PosicaoEixoVerticalLancaMissily -2.569
#define PosicaoEixoVerticalLancaMissilz -0.586

#define PosicaoPortaBombax 0
#define PosicaoPortaBombay -1.357
#define PosicaoPortaBombaz 6.688
