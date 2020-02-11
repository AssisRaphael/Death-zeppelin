#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "glm.h"
#include "glmint.h"
#include<math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include"funcoes.h"
#include<string.h>
#include<time.h>
#include <SOIL/SOIL.h>

void configuraProjecao() {

  float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, razaoAspecto, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	
  AjustaCamera();
  posicaoEsfera.x=posicaoCameras.x;
  posicaoEsfera.y=posicaoCameras.y;
  posicaoEsfera.z=posicaoCameras.z;

  	gluLookAt(posicaoCameras.x,posicaoCameras.y,posicaoCameras.z,Foco.x,Foco.y,Foco.z,0,1,0);


}

void LoadTexture(char* File,GLuint* T){
	*T = SOIL_load_OGL_texture(File,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
	if(*T == 0)
		printf("Erro do SOIL: '%s'\n",SOIL_last_result());
}

void redimensiona(int width, int height)
{
    glViewport(0, 0, width, height);
    configuraProjecao();
}

float AngleBetween(Vector v1,Vector v2){
  return 0;
}

int C_C_Colision(CubeColision c1,CubeColision c2){
	if(((c1.p.x+c1.w/2)<=(c2.p.x-c2.w/2)) || ((c1.p.x-c1.w/2)>=(c2.p.x+c2.w/2))){
		if(((c1.p.y+c1.h/2)<=(c2.p.y-c2.h/2)) || ((c1.p.y-c1.h/2)>=(c2.p.y+c2.h/2))){
			if(((c1.p.z+c1.d/2)<=(c2.p.z-c2.d/2)) || ((c1.p.z-c1.d/2)>=(c2.p.z+c2.d/2))){
				return 1;
			}	
		}
	}
	return 0;
}

int S_S_Colision(SphereColision c1,SphereColision c2){
	Vector v=SubtractPoints(c1.p,c2.p);
	float distance=Norm(v);
	if(distance<=c1.r || distance<=c2.r){
		return 1;
	}
	return 0;
}

int S_C_Colision(SphereColision c1,CubeColision c2){
	float r2=(c1.r*c1.r);
	if(r2-pow(((c2.p.x+c2.w/2)-c1.p.x),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)<=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.x-c2.w/2)-c1.p.x),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)<=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.y+c2.h/2)-c1.p.y),2)>=0){
		if((pow((c2.p.x+c2.w/2)-c1.p.x,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)<=r2) && (pow((c2.p.x-c2.w/2)-c1.p.x,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.y-c2.h/2)-c1.p.y),2)>=0){
		if((pow((c2.p.x+c2.w/2)-c1.p.x,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)<=r2) && (pow((c2.p.x-c2.w/2)-c1.p.x,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.z+c2.d/2)-c1.p.z),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.x+c2.w/2)-c1.p.x,2)<=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.x-c2.w/2)-c1.p.x,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.z-c2.d/2)-c1.p.z),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.x+c2.w/2)-c1.p.x,2)<=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.x-c2.w/2)-c1.p.x,2)>=r2)){
			return 1;
		}
	}
	return 0;
}

int P_C_Colision(Point p,CubeColision c){
	if(p.x>=(c.p.x-c.w/2) && p.x<=(c.p.x+c.w/2)){
		if(p.y>=(c.p.y-c.h/2) && p.y<=(c.p.y+c.h/2)){
			if(p.z>=(c.p.z-c.d/2) && p.z<=(c.p.z+c.d/2))
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

int P_S_Colision(Point p,SphereColision c){
	Vector v=SubtractPoints(p,c.p);
	float distance=Norm(v);
	if(distance<=c.r)
		return 1;
	else 
		return 0;
}

void ColisionManager(){
	for(int i=0;i<maxBullets;i++){
		if(bullets[i].exist==1){
			for(int j=0;j<5;j++){
					if(bombEnemies[j].exist){
						if(P_S_Colision(bullets[i].p,bombEnemies[j].c)){
							bombEnemies[j].hp-=bullets[i].damage;
							ResetBullet(i);
					}
				}
			}
			for(int j=0;j<NumCasas;j++){
			    if(Casa[j].vida>0){
			        if(P_C_Colision(bullets[i].p,Casa[j].c)){
			            Casa[j].vida-=bullets[i].damage;
			            ResetBullet(i);
			        }
			    }
			}
		}
		else break;	
	}
}

void CreateBullet(Point p, Vector v){
	int i;
	for(i=0;i<maxBullets;i++)
		if(!bullets[i].exist){
			bullets[i].p=p;
			bullets[i].v=v;
			bullets[i].damage=10;
			bullets[i].exist=1;
			break;
		}
}
void ResetBullet(int i){
	bullets[i].p=PontoMetralhadora.p;
	bullets[i].v.x=0;
	bullets[i].v.y=0;
	bullets[i].v.z=0;
	bullets[i].v.w=0;
	bullets[i].damage=0;
	bullets[i].exist=0;
}
void DrawBullets(){
	for(int i=0;i<maxBullets;i++){
		if(bullets[i].exist){
			glPushMatrix();
				glTranslated(bullets[i].p.x,bullets[i].p.y,bullets[i].p.z);
				glColor3d(1,0,0);
				glutSolidSphere(0.5,10,10);
			glPopMatrix();
		}
		else
			break;
	}
}

void ManageBullets(){
	for(int i=0;i<maxBullets;i++){
		if(bullets[i].p.x>400 || bullets[i].p.z>400 || bullets[i].p.y>200 ||
		   bullets[i].p.x<-400 || bullets[i].p.z<-400 || bullets[i].p.y<-200){
			ResetBullet(i);
		}
		if(bullets[i].exist){
			bullets[i].p.x+=bullets[i].v.x;
			bullets[i].p.y+=bullets[i].v.y;
			bullets[i].p.z+=bullets[i].v.z;
		}
	}
}

void DrawBombEnemies(Point p){
	for(int i=0;i<bombEnemy;i++){
		if(bombEnemies[i].exist){
			glPushMatrix();
				glTranslated(p.x,p.y,p.z);
				glmDraw(BombEnemyOBJ, GLM_TEXTURE);
				glRotated(rotacaoHelice,0,1,0);
		   		glmDraw(BombEnemyHOBJ, GLM_TEXTURE);
			glPopMatrix();
		}
	}
}

void ResetBombEnemy(int i){
	Point position={0,0,0,1};
	bombEnemies[i].p=position;
	bombEnemies[i].damage=0;
	bombEnemies[i].hp=0;
	bombEnemies[i].c.p=position;
	bombEnemies[i].c.r=0;
	bombEnemies[i].exist=0;
}

void CreateBombEnemy(Point position){
	int i;
	for(i=0;i<bombEnemy;i++){
		if(bombEnemies[i].exist==0){
			bombEnemies[i].p=position;
			bombEnemies[i].damage=10;
			bombEnemies[i].hp=60;
			bombEnemies[i].c.p=position;
			bombEnemies[i].c.r=2;
			bombEnemies[i].exist=1;
			break;
		}
	}
}

void DrawExplosion(){
  	for(int i=0;i<10;i++)
		if(explosions[i].exist){
			glPushMatrix();
				glTranslated(explosions[i].p.x,explosions[i].p.y,explosions[i].p.z);
				glScalef(explosions[i].f+1,explosions[i].f+1,explosions[i].f+1);
				glmDraw(ExposaoOBJ,GLM_TEXTURE);
			glPopMatrix();
		}
}

void ResetExplosion(int i){
	explosions[i].p=(Point){0,0,0,1};
	explosions[i].f=-1;
	explosions[i].d=0;
	explosions[i].exist=0;
}
void CreateExplosion(Point p,int d){
	for(int i=0;i<10;i++){
		if(!explosions[i].exist)
			explosions[i].p=p;
			explosions[i].f=0;
			explosions[i].d=d;
			explosions[i].exist=1;
			break;
	}
}
void ManageExplosions(){
	for(int i=0;i<10;i++){
		if(explosions[i].exist){
			explosions[i].f++;
			if(explosions[i].f>=explosions[i].d)
				ResetExplosion(i);
		}
	}

}

void ManageBombEnemy(){
	int i;
	for(i=0;i<bombEnemy;i++){
		if(bombEnemies[i].hp<=0){
			CreateExplosion(bombEnemies[i].p,10);
			ResetBombEnemy(i);	
		}
		if(bombEnemies[i].exist){
			if(bombEnemies[i].p.x>zep.p.x)
				bombEnemies[i].p.x-=0.08;
			else if(bombEnemies[i].p.x<zep.p.x)
				bombEnemies[i].p.x+=0.08;
			if(bombEnemies[i].p.y>zep.p.y)
				bombEnemies[i].p.y=zep.p.y;
			else if(bombEnemies[i].p.y<zep.p.y)
				bombEnemies[i].p.y+=0.08;
			if(bombEnemies[i].p.z>zep.p.z)
				bombEnemies[i].p.z-=0.08;
			else if(bombEnemies[i].p.z<zep.p.z)
				bombEnemies[i].p.z+=0.08;
			bombEnemies[i].c.p=bombEnemies[i].p;
		}
		else
			break;
	}
}

float Norm(Vector v){
	return sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
}

Vector SubtractPoints(Point p1,Point p2){
	Point result = {p2.x-p1.x,p2.y-p1.y,p2.z-p1.z,p2.w-p1.w};
	return result;
}
Point AddPoint(Point p,Vector v){
	Point result = {p.x+v.x,p.y+v.y,p.z+v.z,p.w+v.w};
	return result;
}

Vector Normalize(Vector v){
	Vector result = {v.x/Norm(v),v.y/Norm(v),v.z/Norm(v),0};
	return result;
}

Esferico LookAt(Point eye,Point target){
	Vector newTarget={target.x-eye.x,target.y-eye.y,target.z-eye.z,0};
	newTarget=Normalize(newTarget);
	Esferico coordinates;
	coordinates.f=acos(target.z);
	coordinates.t=acos(target.x/sin(coordinates.f));
	coordinates.v=1;
	return coordinates;
}

void ResetaPosicaoCamera(){
//Reseta a posição da camera 0 no ponto atras do zepelin

	Vector vector;

	glPushMatrix();
		glTranslated(zep.p.x,zep.p.y,zep.p.z);
		vector.y=0;
		vector.x=-sin(zep.c.t+3.1415);
		vector.z=-cos(zep.c.t+3.1415);
		float modulo = sqrt(pow(vector.x,2)+pow(vector.z,2));
		vector.x/=modulo;
		vector.z/=modulo;
	glPopMatrix();
	posicaoCamera.p.x=zep.p.x+25*vector.x;
	posicaoCamera.p.y=zep.p.y+30;
	posicaoCamera.p.z=zep.p.z+25*vector.z;
	Foco.x=zep.p.x;
	Foco.y=zep.p.y;
	Foco.z=zep.p.z;
	posicaoCamera.c.v=0;
	posicaoCamera.c.t=zep.c.t;
}

void AjustaCamera(){
	
	Vector vector, vector2;
	
	if (CAMERAGUN==-1){
		vector.x=-sin(PontoMetralhadora.c.t)*sin(PontoMetralhadora.c.f);
		vector.z=-cos(PontoMetralhadora.c.t)*sin(PontoMetralhadora.c.f);
		vector.y=cos(PontoMetralhadora.c.f);
		float modulo = sqrt(pow(vector.x,2)+pow(vector.z,2)+pow(vector.y,2));
		vector.x/=modulo;
		vector.z/=modulo;
		vector.y/=modulo;
		
		PontoMetralhadora.p.x=zep.p.x;
		PontoMetralhadora.p.y=zep.p.y+5;
		PontoMetralhadora.p.z=zep.p.z;
		
		posicaoCameras.x=PontoMetralhadora.p.x;
		posicaoCameras.y=PontoMetralhadora.p.y;
		posicaoCameras.z=PontoMetralhadora.p.z;
		Foco.x=posicaoCameras.x+20*vector.x;
		Foco.z=posicaoCameras.z+20*vector.z;
		Foco.y=posicaoCameras.y+20*vector.y;
		
		vector.x=5*vector.x/modulo;
		vector.y=5*vector.y/modulo;
		vector.z=5*vector.z/modulo;
		vetorCamera=vector;
		return;
	}

	if (CAMERA==0){
		vector.x=-sin(posicaoCamera.c.t);
		vector.z=-cos(posicaoCamera.c.t);
		float modulo = sqrt(pow(vector.x,2)+pow(vector.z,2));
		vector.x/=modulo;
		vector.z/=modulo;
		posicaoCameras.x=posicaoCamera.p.x;
		posicaoCameras.y=posicaoCamera.p.y;
		posicaoCameras.z=posicaoCamera.p.z;
		Foco.x=posicaoCameras.x+20*vector.x;
		Foco.z=posicaoCameras.z+20*vector.z;
		return;
	}

	if (CAMERA==1){
		vector.x=-sin(zep.c.t+3.1415);
		vector.z=-cos(zep.c.t+3.1415);
	}
	else if (CAMERA==2){
		vector.x=-sin(zep.c.t+1.57);
		vector.z=-cos(zep.c.t+1.57);
	}
	else if (CAMERA==3){
		vector.x=-sin(zep.c.t-1.57);
		vector.z=-cos(zep.c.t-1.57);
	}
	else if (CAMERA==4){
		vector.x=-sin(zep.c.t);
		vector.z=-cos(zep.c.t);
	}
	float modulo = sqrt(pow(vector.x,2)+pow(vector.z,2));
	vector.x/=modulo;
	vector.z/=modulo;

	if (CAMERA==1){
			//Perspectiva 3 pessoa por tras
	  		posicaoCameras.x=zep.p.x+20*vector.x;
			posicaoCameras.y=zep.p.y+20;
			posicaoCameras.z=zep.p.z+20*vector.z;
	}
	else if (CAMERA==2){
		//Perspectiva 3 pessoa pela direita
	  	posicaoCameras.x=zep.p.x+20*vector.x;
		posicaoCameras.y=zep.p.y+20;
		posicaoCameras.z=zep.p.z+20*vector.z;
	}
	else if (CAMERA==3){
		//Perspectiva 3 pessoa pela esquerda
	  	posicaoCameras.x=zep.p.x+20*vector.x;
		posicaoCameras.y=zep.p.y+20;
		posicaoCameras.z=zep.p.z+20*vector.z;
	}
	else if (CAMERA==4){
		//Perspectiva 3 pessoa pela frente
	  	posicaoCameras.x=zep.p.x+20*vector.x;
		posicaoCameras.y=zep.p.y+20;
		posicaoCameras.z=zep.p.z+20*vector.z;
	}
	Foco.x=zep.p.x;
	Foco.y=zep.p.y;
	Foco.z=zep.p.z;
}

void ApplyTexture(GLuint *Texture,Point p, float l, float a,float alpha){
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,*Texture);
  glBegin(GL_POLYGON);
        glTexCoord2f(0, 0);glVertex3f(p.x-(l/2),p.y-(a/2),1);
        glTexCoord2f(1, 0);glVertex3f(p.x+(l/2),p.y-(a/2),1);
        glTexCoord2f(1, 1);glVertex3f(p.x+(l/2),p.y+(a/2),1);
        glTexCoord2f(0, 1);glVertex3f(p.x-(l/2),p.y+(a/2),1);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void iniciar_musica(char *music){
	if(!Mix_PlayingMusic()){
		Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,1024);
		musicMenu=Mix_LoadMUS(music);
		Mix_VolumeMusic(volume_musica);
		Mix_PlayMusic(musicMenu,-1);
	}
}
void parar_musica(){
	if(Mix_PlayingMusic()){
		Mix_FadeOutMusic(fade_out);
	}
}

void desenhaRetangulo(int x, int y,  int z, int w, int h, int p) {
  glBegin(GL_POLYGON);
      glVertex3i(x, y, z);
      glVertex3i(x+w, y, z);
      glVertex3i(x + w, y + h, z+p);
      glVertex3i(x, y + h, z+p);
  glEnd();
}

void DesenhaZepelin(){
	Point t={0,0,0,1};
	Esferico s=LookAt(t,zep.p);
	zep.c.t*=180/3.1415;
	glPushMatrix();
		glRotated(s.t,0,1,0);
		glRotated(s.f,0,0,1);
		glmDraw(MissilOBJ, GLM_TEXTURE);
	glPopMatrix();
    glPushMatrix();
			glColor3d(1,1,1);// clear
			glTranslated(zep.p.x,zep.p.y,zep.p.z);
			glRotated(90,0,1,0);
			glRotated(zep.c.t,0,1,0);
			glTranslated(0,0,zep.c.v);
		  glmDraw(ZepelinOBJ, GLM_TEXTURE);
		  if(CAMERAGUN==1){
		  //Metranca
			  glPushMatrix();
				glTranslated(0,AturaMetralhadora,0);
			   	glmDraw(MetrancaOBJ, GLM_TEXTURE);
			  glPopMatrix();
		  }
		  //Helice direira P
		  glPushMatrix();
		    glTranslated(PosicaoCentroHelicePz,PosicaoCentroHelicePy,PosicaoCentroHelicePx);
		   	glRotated(rotacaoHelice*zep.c.v*6,1,0,0);
		   	glmDraw(HeliceP_R_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Helice esquerda P
		  glPushMatrix();
		    glTranslated(PosicaoCentroHelicePz,PosicaoCentroHelicePy,-PosicaoCentroHelicePx);
		   	glRotated(-rotacaoHelice*zep.c.v*6,1,0,0);
		   	glmDraw(HeliceP_L_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Helice direira G
		  glPushMatrix();
		   	glTranslated(PosicaoCentroHeliceGz,PosicaoCentroHeliceGy,PosicaoCentroHeliceGx);
		   	glRotated(rotacaoHelice*zep.c.v*6,1,0,0);
		   	glmDraw(HeliceG_R_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Helice esquerda G
		  glPushMatrix();
		   	glTranslated(PosicaoCentroHeliceGz,PosicaoCentroHeliceGy,-PosicaoCentroHeliceGx);
		   	glRotated(-rotacaoHelice*zep.c.v*6,1,0,0);
		   	glmDraw(HeliceG_L_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Minigun D
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoVerticalMetralhadoraz,PosicaoEixoVerticalMetralhadoray,PosicaoEixoVerticalMetralhadorax);
		   	glmDraw(Minigun_R_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Minigun E
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoVerticalMetralhadoraz,PosicaoEixoVerticalMetralhadoray,-PosicaoEixoVerticalMetralhadorax);
		   	glmDraw(Minigun_L_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Engrenagem Inferior
		  glPushMatrix();
		   	glTranslated(PosicaoEngrenagemInferiorz,PosicaoEngrenagemInferiory,PosicaoEngrenagemInferiorx);
		   	glRotated(rotacaoEngrenagem,0,0,1);
		   	glmDraw(EngrenagensOBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Engerenagem Superior
		  glPushMatrix();
		   	glTranslated(PosicaoEngrenagemSuperiorz,PosicaoEngrenagemSuperiory,PosicaoEngrenagemSuperiorx);
		   	glRotated(-rotacaoEngrenagem,0,0,1);
		   	glmDraw(EngrenagensOBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Eixo minigun D
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoHorizontalMetralhadoraz,PosicaoEixoHorizontalMetralhadoray,PosicaoEixoHorizontalMetralhadorax);
		   	glmDraw(Eixo_R_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Eixo minigun E
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoHorizontalMetralhadoraz,PosicaoEixoHorizontalMetralhadoray,-PosicaoEixoHorizontalMetralhadorax);
		   	glmDraw(Eixo_L_OBJ,GLM_TEXTURE);
		  glPopMatrix();
		   //Eixo Missil D
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoHorizontalLancaMissilz,PosicaoEixoHorizontalLancaMissily,PosicaoEixoHorizontalLancaMissilx);
		   	glmDraw(Eixo_Missel_R_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Eixo Missil E
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoHorizontalLancaMissilz,PosicaoEixoHorizontalLancaMissily,-PosicaoEixoHorizontalLancaMissilx);
		   	glmDraw(Eixo_Missel_L_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Eixo Base Missil D
		  glPushMatrix();
		   	glTranslated(-PosicaoEixoVerticalLancaMissilz,PosicaoEixoVerticalLancaMissily,PosicaoEixoVerticalLancaMissilx);
		   	glmDraw(Base_Missil_R_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Eixo Base Missil E
		  glPushMatrix(); 
		   	glTranslated(-PosicaoEixoVerticalLancaMissilz,PosicaoEixoVerticalLancaMissily,-PosicaoEixoVerticalLancaMissilx);
		   	glmDraw(Base_Missil_L_OBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Leme
		  glPushMatrix();
		   	glTranslated(PosicaoLemez,PosicaoLemey,PosicaoLemex);
		   	glmDraw(LemeOBJ, GLM_TEXTURE);
		  glPopMatrix();
		   //Porta
		  glPushMatrix();
		   	glTranslated(-PosicaoPortaBombaz,PosicaoPortaBombay,PosicaoPortaBombax);
		   	if(Tampa){
		   		glRotated(-AnguloTampa,0,0,1);
		   		if(AnguloTampa<=90 && Tampa==1)
		   			AnguloTampa+=2;
		   		if(AnguloTampa>0 && Tampa==2)
		   			AnguloTampa-=2;
		   	}
		   	glmDraw(PortaOBJ, GLM_TEXTURE);
		  glPopMatrix();
    glPopMatrix();

    	//Missil D
		glPushMatrix();
			glTranslated(zep.p.x,zep.p.y,zep.p.z);
			glRotated(90,0,1,0);
			glRotated(zep.c.t,0,1,0);
			glTranslated(0,0,zep.c.v);
		   	glTranslated(-PosicaoEixoVerticalLancaMissilz,PosicaoEixoVerticalLancaMissily,PosicaoEixoVerticalLancaMissilx);
		   	glmDraw(MissilOBJ, GLM_TEXTURE);
	    glPopMatrix();

	    //Missil E
		glPushMatrix();
			glTranslated(zep.p.x,zep.p.y,zep.p.z);
			glRotated(90,0,1,0);
			glRotated(zep.c.t,0,1,0);
			glTranslated(0,0,zep.c.v);
		   	glTranslated(-PosicaoEixoVerticalLancaMissilz,PosicaoEixoVerticalLancaMissily,-PosicaoEixoVerticalLancaMissilx);
		   	glmDraw(MissilOBJ, GLM_TEXTURE);
	    glPopMatrix();
		
    rotacaoHelice+=20;
    rotacaoEngrenagem+=5;
    zep.c.t*=3.1415/180;
}

void ResetaTrem(){
	trem.x=-220;
	trem.y=-48.64;
	if(trilho==4)
		trilho=0;
	if(trilho == 0)
		trem.z= 154;
	else if(trilho == 1)
		    trem.z= 70;
	     else if(trilho == 2)
	     	trem.z= -70;
	     	else
	     		trem.z= -154;
	trem.w=0;
	trilho++;
	controleEnemy=0;
}

void AtualizaTrem(){
	trem.x+=0.5;
	if(trem.x>=230)
		ResetaTrem();
	if(trem.x==-60){
		Point p;
		p=trem;
		p.x-=10;
		p.y+=3.1;
		CreateBombEnemy(p);
	}
}

void ExplodirCasa(int i){	
	if(Casa[i].p.x>=Bumb.p.x-100 && Casa[i].p.x<=Bumb.p.x+100)
			if(Casa[i].p.z>Bumb.p.z-100 && Casa[i].p.z<=Bumb.p.z+100)
				Casa[i].vida=0;
}

void geraMundo(){

	AtualizaTrem();
	glColor3d(1,1,1);
	
	// ESFERA de visualizaçãoinclinacaoCamera
    glPushMatrix();
		glTranslated(posicaoEsfera.x,0,posicaoEsfera.z+20);
		glScalef(395,395,395);
        glmDraw(HorizonteOBJ, GLM_TEXTURE);
    glPopMatrix();
    
    int Trilhos=0;
 
	//Casas
  	for(int i=0;i<28;i++){
		glPushMatrix();
			glTranslated(Casa[i].p.x,Casa[i].p.y,Casa[i].p.z);
			//glRotated(180,0,1,0);
			glScalef(2,2,2);
			if(Casa[i].vida>0)
		   		glmDraw(HouseOBJ, GLM_TEXTURE);
			else{
				glPushMatrix();
		   			glmDraw(House2OBJ, GLM_TEXTURE);
				glPopMatrix();
			}
	    glPopMatrix();
  	}
  	
  	//Relógio
  	glPushMatrix();
  		if(Torre.vida){
			glTranslated(Torre.p.x,Torre.p.y,Torre.p.z);
			glScalef(3,3,3);
			glRotated(90,0,1,0);
        	glmDraw(GreatGeorgeOBJ, GLM_TEXTURE);
        } else {
        	glTranslated(0,-50,0);
			glScalef(3,3,3);
			glRotated(90,0,1,0);
			glmDraw(GreatGeorgeBOBJ, GLM_TEXTURE);
			glTranslated(2.28,11.08,0);
			glRotated(AnguloTorre,1,0,1);
			glmDraw(GreatGeorgeTOBJ, GLM_TEXTURE);
			if(FramesTorre<=200){
				AnguloTorre+=0.57;
				FramesTorre++;
			}
			if(FramesTorre==200){
				Casa[14].vida=0;
			}
        }
    glPopMatrix();
    
    //Cenario
    glPushMatrix();
		glTranslated(0,-50,0);
        glmDraw(CenarioOBJ, GLM_TEXTURE);
    glPopMatrix();
    
    //Trem
  	glPushMatrix();
		glTranslated(trem.x,trem.y,trem.z);
		glScalef(1.5,1.5,1.5);
        glmDraw(LegendaryExpressOBJ, GLM_TEXTURE);
    glPopMatrix();

	 //Bomba
  	glPushMatrix();
		glTranslated(Bumb.p.x,Bumb.p.y,Bumb.p.z);
        glmDraw(BombOBJ, GLM_TEXTURE);
    glPopMatrix();
    
    //Vagoes
    glPushMatrix();
        glTranslated(trem.x-16.25821,trem.y,trem.z);
        glScalef(1.5,1.5,1.5);
        glmDraw(BombWagonOBJ, GLM_TEXTURE);
        glTranslated(-10,0,0);
        glmDraw(BombWagonOBJ, GLM_TEXTURE);
    glPopMatrix();
    
    for(int i=0; i<bombEnemy; i++)
    	if(bombEnemies[i].exist)
    		DrawBombEnemies(bombEnemies[i].p);
    	else
    		break;

}

void AtualizaZepelin(){
	zep.p.z-=zep.c.v*cos(zep.c.t);
	zep.p.x-=zep.c.v*sin(zep.c.t);
	posicaoCamera.p.z-=posicaoCamera.c.v*cos(posicaoCamera.c.t);
	posicaoCamera.p.x-=posicaoCamera.c.v*sin(posicaoCamera.c.t);
	posicaoCamera.c.v=0;
}

void desenha()
{
	configuraProjecao();
    ConfiguraIluminacao();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	geraMundo();
	DesenhaZepelin();
	DrawBullets();
	//DrawExplosion();
	Kabum();
	AtualizaZepelin();
	ManageBullets();
	ManageBombEnemy();
	//ManageExplosions();
	ColisionManager();
	AtualizaBomba();
    glutSwapBuffers();
    
	frame++;	
	if(frame==2000){
		luz=-1;
	}
	if(frame==4000){
		luz=-1;
		fog=-1;
	}
	if(frame==6000){
		luz=-1;
		fog=1;
	}
	if(frame==8000){
		luz=1;
		fog=-1;
		frame=0;
	}
}

void AtualizaBomba(){
	if(LancarBomba==0){
		Bumb.p.x=zep.p.x; Bumb.p.y=zep.p.y; Bumb.p.z=zep.p.z;
	}
	else{
		Bumb.p.x+=vetorBomba.x*0.1;
		Bumb.p.z+=vetorBomba.z*0.1;
		Bumb.p.y-=0.5;
	}
	if(Bumb.p.y<=-505){
		Bumb.p.x=zep.p.x; Bumb.p.y=zep.p.y-2.5; Bumb.p.z=zep.p.z;
		LancarBomba=0;
		FramesArmagedom=0; ScaleExplosion=0; explodiu=0;
	}
}

void Kabum(){
	if(LancarBomba){
		if(Bumb.p.y==-50){
			Explodido.x=Bumb.p.x;
			Explodido.z=Bumb.p.z;
			explodiu=1;
		}
		if(FramesArmagedom<=180 && explodiu){
		    ScaleExplosion+=0.4;
		    CAMERA=4;
		    zep.c.v=0.4;
		    glPushMatrix();
		    	glTranslated(Explodido.x,-50,Explodido.z);
				glScalef(ScaleExplosion,ScaleExplosion,ScaleExplosion);
				glmDraw(ExposaoOBJ, GLM_TEXTURE);
			glPopMatrix();
			FramesArmagedom++;
		}
		if(FramesArmagedom==170){
			for(int i=0;i<29;i++)
				ExplodirCasa(i);
			if(Torre.p.x>=Bumb.p.x-100 && Torre.p.x<=Bumb.p.x+100 && Torre.p.z>=Bumb.p.z-100 && Torre.p.z<=Bumb.p.z+100)
				Torre.vida=0;
		}
	}
}

void inicializa(void){

	srand(time(NULL));
	CAMERA = 1;
	CAMERAGUN = 1;
	tiro=0; luz=1;
	zep.c.t=0; zep.c.v=0.2;

	frame=0; Explodido.x=0; Explodido.z=0;
	
	for(int i=0;i<maxBullets;i++){
		bullets[i].exist=0;
		ResetBullet(i);	
	}
	
	posicaoCamera.p.x=0; posicaoCamera.p.y=20; posicaoCamera.p.z=165;
	posicaoCamera.c.t=0; posicaoCamera.c.v=0;
	PontoMetralhadora.c.t=0; PontoMetralhadora.c.v=0;  PontoMetralhadora.c.f=1.57;
	LancarBomba=0;
	rotacaoHelice = 0, rotacaoEngrenagem = 0;
	Tampa = 0, TampaAberta=0;
	AnguloTampa =0; FramesTorre =0; AnguloTorre =0;	
	zep.p.x=0; zep.p.y=0; zep.p.z=145;
	fog=1; explodiu=0;
	Torre.p.x=0; Torre.p.z=0; Torre.p.y=-50; Torre.vida=300;
	Torre.c.p.x=0; Torre.c.p.y=46; Torre.c.p.z=0; Torre.c.h=96; Torre.c.w=16; Torre.c.d=16;	
	Bumb.p.x=zep.p.x; Bumb.p.y=zep.p.y; Bumb.p.z=zep.p.z;

	DensidadeFog=0.006; Score=0; Life=100;
	Armagedom=0; ScaleExplosion=0;
	
	ResetaTrem();
	
	Casa[0].p.x=-160; Casa[10].p.x=-160; Casa[14].p.x=50;   Casa[18].p.x=-140;
	Casa[0].p.y=-50;  Casa[10].p.y=-50;  Casa[14].p.y=-50;  Casa[18].p.y=-50;
	Casa[0].p.z=134;  Casa[10].p.z=20;  Casa[14].p.z=20;  Casa[18].p.z=-100;
	Casa[0].p.w=1;    Casa[10].p.w=1;    Casa[14].p.w=1;    Casa[18].p.w=1;

	//Primeiras 10 casas
	for(int i=1; i<NumCasas/3;i++){
	  if(i%2!=0){
		Casa[i].p.x=Casa[i-1].p.x;
		Casa[i].p.y=-50;
		Casa[i].p.z=Casa[i-1].p.z-30;
		Casa[i].p.w=1;
	  } else{
	  	Casa[i].p.x=Casa[i-1].p.x+60;
		Casa[i].p.y=-50;
		Casa[i].p.z=134;
		Casa[i].p.w=1;
	  }
	}
	// 4 casas lado esquerdo centro
	for(int i=11; i<14;i++){
		if(i%2!=0){
		Casa[i].p.x=Casa[i-1].p.x;
		Casa[i].p.y=-50;
		Casa[i].p.z=Casa[i-1].p.z-50;
		Casa[i].p.w=1;
	  } else{
	  	Casa[i].p.x=Casa[i-1].p.x+60;
		Casa[i].p.y=-50;
		Casa[i].p.z=20;
		Casa[i].p.w=1;
	  }
	}
	// 4 casas lado direito centro
	for(int i=15; i<18;i++){
		if(i%2!=0){
		Casa[i].p.x=Casa[i-1].p.x;
		Casa[i].p.y=-50;
		Casa[i].p.z=Casa[i-1].p.z-50;
		Casa[i].p.w=1;
	  } else{
	  	Casa[i].p.x=Casa[i-1].p.x+60;
		Casa[i].p.y=-50;
		Casa[i].p.z=20;
		Casa[i].p.w=1;
	  }
	}
	// 10 ultimas casas
	for(int i=19; i<28;i++){
	  if(i%2!=0){
		Casa[i].p.x=Casa[i-1].p.x;
		Casa[i].p.y=-50;
		Casa[i].p.z=Casa[i-1].p.z-30;
		Casa[i].p.w=1;
	  } else{
	  	Casa[i].p.x=Casa[i-1].p.x+60;
		Casa[i].p.y=-50;
		Casa[i].p.z=-100;
		Casa[i].p.w=1;
	  }
	}
	
	for(int i=0;i<29;i++){
		Casa[i].vida=50;
		Casa[i].c.p.x=Casa[i].p.x;
		Casa[i].c.p.y=Casa[i].p.y+6.48;
		Casa[i].c.p.z=Casa[i].p.z;
		Casa[i].c.w=12.96;
		Casa[i].c.h=12.96;
		Casa[i].c.d=12.96;
	}

    //OBJs
    ZepelinOBJ = glmReadOBJ("..//cenario//Zepellin.obj");
    Base_Missil_L_OBJ = glmReadOBJ("..//cenario//Base_Missil_L.obj");
    Base_Missil_R_OBJ = glmReadOBJ("..//cenario//Base_Missil_R.obj");
    Eixo_L_OBJ = glmReadOBJ("..//cenario//Eixo_L.obj");
    Eixo_Missel_L_OBJ = glmReadOBJ("..//cenario//Eixo_Missel_L.obj");
    Eixo_Missel_R_OBJ = glmReadOBJ("..//cenario//Eixo_Missel_R.obj");
    Eixo_R_OBJ = glmReadOBJ("..//cenario//Eixo_R.obj");
    EngrenagensOBJ = glmReadOBJ("..//cenario//Engrenagens.obj");
    HeliceP_R_OBJ = glmReadOBJ("..//cenario//HeliceP_R.obj");
    HeliceP_L_OBJ = glmReadOBJ("..//cenario//HeliceP_L.obj");
    HeliceG_R_OBJ = glmReadOBJ("..//cenario//HeliceG_R.obj");
    HeliceG_L_OBJ = glmReadOBJ("..//cenario//HeliceG_L.obj");
    LemeOBJ = glmReadOBJ("..//cenario//Leme.obj");
    Minigun_R_OBJ = glmReadOBJ("..//cenario//Minigun_R.obj");
    Minigun_L_OBJ = glmReadOBJ("..//cenario//Minigun_L.obj");
    MissilOBJ = glmReadOBJ("..//cenario//Missil.obj");
    PortaOBJ = glmReadOBJ("..//cenario//Porta.obj");  
    BombWagonOBJ = glmReadOBJ("..//cenario//BombWagon.obj");
    GreatGeorgeOBJ = glmReadOBJ("..//cenario//GreatGeorge.obj");
    HouseOBJ = glmReadOBJ("..//cenario//House.obj");
    LegendaryExpressOBJ = glmReadOBJ("..//cenario//LegendaryExpress.obj");
    HorizonteOBJ = glmReadOBJ("..//cenario//SkySphere.obj");
    ExposaoOBJ = glmReadOBJ("..//cenario//Explosion.obj");   
    House2OBJ = glmReadOBJ("..//cenario//DestroyedHouse.obj");
    CenarioOBJ = glmReadOBJ("..//cenario//cenario_2.obj");
    BombOBJ = glmReadOBJ("..//cenario//Bomb.obj"); 
    GreatGeorgeTOBJ = glmReadOBJ("..//cenario//GreatGeorgeDestroyedTop.obj");
    GreatGeorgeBOBJ = glmReadOBJ("..//cenario//GreatGeorgeDestroyedBottom.obj");
    BombEnemyOBJ = glmReadOBJ("..//cenario//BombEnemy.obj");
    BombEnemyHOBJ = glmReadOBJ("..//cenario//BombEnemyProppeler.obj");
	MetrancaOBJ = glmReadOBJ("..//cenario//Minigun.obj");

	iniciar_musica("..//sounds//musica.mp3");
    
}

static void teclado(unsigned char key, int x, int y){
	posicaoCamera.c.v=0;
	int i;
    switch (key){
        case 27 :// Tecla 'ESC
            exit(0); break;
		case '1':
				CAMERA=0;
				CAMERAGUN=1;
				ResetaPosicaoCamera();
        	break;
		case '2':
				CAMERAGUN=1; CAMERA=1; break;
        case 'w':
		case 'W':
		 if(zep.c.v<=0.3)
			zep.c.v+=0.15; break;
        case 'a':
		case 'A':
        	zep.c.t+=(3.1415/220); break;
        case 's':
		case 'S':
			if(zep.c.v>=-0.3)
			zep.c.v-=0.15; break;
        case 'd':
		case 'D':
        	zep.c.t-=(3.1415/220); break;
		case 'c':
		case 'C':
			if(CAMERA==0)
				ResetaPosicaoCamera();
				CAMERA++;
				if(CAMERA==5)
					CAMERA=1;
        	break;
		case 'z':
		case 'Z':
        	break;
		case 'u':
			if(CAMERA==0)
				posicaoCamera.c.v=0.8;
			if(CAMERAGUN==-1 && PontoMetralhadora.c.f>0.34905)
				PontoMetralhadora.c.f-=(3.1415/100);
			break;
		case 'U':
        	Foco.y+=0.4; break;
		case 'j':
			if(CAMERA==0)
				posicaoCamera.c.v=-0.8;
			if(CAMERAGUN==-1 && PontoMetralhadora.c.f<2.44338)
				PontoMetralhadora.c.f+=(3.1415/100);
		    break;
		case 'J':
			Foco.y-=0.4; break;
        	break;
		case 'h':
			if(CAMERA==0)
				posicaoCamera.c.t+=(3.1415/100);
			if(CAMERAGUN==-1)
				PontoMetralhadora.c.t+=(3.1415/80);
					break;
		case 'H':
		if(posicaoCamera.p.y>=-45){
			posicaoCamera.p.y--;
			Foco.y--;
		}
        	break;
		case 'k':
			if(CAMERA==0)
				posicaoCamera.c.t-=(3.1415/100);
			if(CAMERAGUN==-1)
				PontoMetralhadora.c.t-=(3.1415/80);
				break;
		case 'K':
			if(posicaoCamera.p.y<=170){
			posicaoCamera.p.y++;
			Foco.y++;
			}
        	break;
       case 'l':
			luz*=-1; break;
        case 'm':
			CAMERAGUN*=-1; break;
		case 't':
			Tampa=1; break;
		case 'b':
		case 'B':
			if(LancarBomba==0){
				vetorBomba.x=sin(zep.c.t);
				vetorBomba.z=cos(zep.c.t);
			}
			if(Tampa==1)
				LancarBomba=1;
			float modulo = sqrt(pow(vetorBomba.x,2)+pow(vetorBomba.z,2));
			vetorBomba.x/=modulo;
			vetorBomba.z/=modulo;
			break;
		case 'T':
			Tampa=2; break;
		case 'p':
		case 'P':
			zep.c.v=0; break;
		case 'r':
			inicializa(); break;
        case 'f':
			CreateBullet(PontoMetralhadora.p,vetorCamera);
        	break;
        case 'n':     
            	fog*=-1; break;
        case '+':      
            	DensidadeFog+=0.001; break;
        case '-':       
            if(DensidadeFog>=0.01)
            	DensidadeFog-=0.001;
             break;
    }
    glutPostRedisplay();
}

static void atoa(void){
    glutPostRedisplay();
}

// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 1.0f, 0.4f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, -1.0f, 0.0f, 0.0f };//luz 1
const GLfloat light_ambient1[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light_diffuse1[]  = { 0.8f, 0.5f, 0.4f, 1.0f };
const GLfloat light_specular1[] = { 0.5f, 1.0f, 0.1f, 1.0f };
const GLfloat light_position1[] = { 0.0f, 50.0f, 0.0f, 1.0f };//luz 2

// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void ConfiguraIluminacao(){

	if(luz>0){
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
    }
    else{
    	glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
    }
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
  	glClearColor(cor[0], cor[1], cor[2], 1.0f);

 	 glFogi(GL_FOG_MODE, GL_EXP2);        // Linear, exp. ou exp²
 	 glFogfv(GL_FOG_COLOR, cor);         // Cor
 	 glFogf(GL_FOG_DENSITY,DensidadeFog);      // Densidade
 	 glHint(GL_FOG_HINT, GL_DONT_CARE);  // Não aplicar se não puder
 	 glFogf(GL_FOG_START, 390.0f);         // Profundidade inicial
 	 glFogf(GL_FOG_END, 395.0f);           // Profundidade final
  	 
  	 if(fog==1)
  	 	glEnable(GL_FOG);                   // Liga GL_FOG
  	 else
  	 	glDisable(GL_FOG);
}

int main(int argc, char *argv[]){

	//Configurações da janela
    glutInit(&argc, argv);
    glutInitWindowSize(1200,650);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("FieldFlyers");

    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);
    //glutTimerFunc(1000,desenha,0);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atoa);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	inicializa();

    glutMainLoop();

    return EXIT_SUCCESS;
}
