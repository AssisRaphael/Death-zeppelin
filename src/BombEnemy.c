void DrawBombEnemies(Point p){
	for(i=0;i<bombEnemy;i++){
		if(bombEnemies[i].exist){
			glPushMatrix();
				glTranslated(p.x,p.y.p.z);
				glmDraw(EnemyOBJ, GLM_TEXTURE);
			glPopMatrix();
		}
		else
			break;
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
		if(!bombEnemies[i].exist){
			bombEnemies[i].p=position;
			bombEnemies[i].damage=10;
			bombEnemies[i].hp=20;
			bombEnemies[i].c.p=position;
			bombEnemies[i].c.r=2;
			bombEnemies[i].exist=1;
		}
		else
			break;
	}
}

void ManageBombEnemy(){
	int i;
	for(i=0;i<bombEnemy;i++){
		if(bombEnemies[i].exist){
			if(bombEnemies[i].p.x>zep.p.x)
				bombEnemies[i].p.x++;
			else
				bombEnemies[i].p.y--;
			if(bombEnemies[i].p.y>zep.p.y)
				bombEnemies[i].p.y++;
			else
				bombEnemies[i].p.y--;
			if(bombEnemies[i].p.z>zep.p.z)
				bombEnemies[i].p.z++;
			else
				bombEnemies[i].p.z--;
			bombEnemies[i].c.p=bombEnemies[i].p;
		}
		else
			break;
	}
}
