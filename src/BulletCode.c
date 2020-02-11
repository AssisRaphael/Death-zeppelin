void CreateBullet(Point p, Vector v){
	int i;
	for(i=0;i<maxBullets;i++)
		if(!bullets[i].exist){
			bullets[i].p=p;
			bullets[i].damage=10;
			bullets[i].exist=1;
			break;
		}
}
void ResetBullet(int i){
	bullets[i].p=posicaoMetralhadora;
	bullets[i].v={0,0,0,0};
	bullets[i].damage=0;
	bullets[i].exist=0;
}
void DrawBullets(){
	for(i=0;i<maxBullets;i++){
		if(bullets[i].exist){
			glPushMatrix();
				glTranslated(bullets[i].p.x,bullets[i].p.y,bullets[i].p.z);
				glutSolidSphere(0.5,10,10);
			glPopMatrix();
		}
		else
			break;
	}
}

void ManageBullets(){
	for(i=0;i<maxBullets;i++){
		if(bullets[i].exist){
			bullets[i].p=AddPoint(bullets[i].p,bullets[i].v);
		}
		else
			break;
	}
}
