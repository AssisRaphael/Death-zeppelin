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
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)>=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.x-c2.w/2)-c1.p.x),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)>=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.y+c2.h/2)-c1.p.y),2)>=0){
		if((pow((c2.p.x+c2.w/2)-c1.p.x,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)>=r2) && (pow((c2.p.x-c2.w/2)-c1.p.x,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.y-c2.h/2)-c1.p.y),2)>=0){
		if((pow((c2.p.x+c2.w/2)-c1.p.x,2)+pow((c2.p.z+c2.d/2)-c1.p.z,2)>=r2) && (pow((c2.p.x-c2.w/2)-c1.p.x,2)+pow((c2.p.z-c2.d/2)-c1.p.z,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.z+c2.d/2)-c1.p.z),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.x+c2.w/2)-c1.p.x,2)>=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.x-c2.w/2)-c1.p.x,2)>=r2)){
			return 1;
		}
	}
	else if(r2-pow(((c2.p.z-c2.d/2)-c1.p.z),2)>=0){
		if((pow((c2.p.y+c2.h/2)-c1.p.y,2)+pow((c2.p.x+c2.w/2)-c1.p.x,2)>=r2) && (pow((c2.p.y-c2.h/2)-c1.p.y,2)+pow((c2.p.x-c2.w/2)-c1.p.x,2)>=r2)){
			return 1;
		}
	}
	return 0;
}
void ColisionManager(){
	
}
