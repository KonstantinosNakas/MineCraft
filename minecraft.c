#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct player_d {
	int dimx;
	int dimy;
	int dimz;
	int points;
	int lifes;
	int v_cubes;
} player_s;
int ***map,N;
player_s player;


void createMap(){
	int i, j, k, colour;
	//Instantiate map
	map = (int ***) malloc( N*sizeof(int **) );
	for (i = 0; i < N; i++) {
	   	map[i] = (int **) malloc(N*sizeof(int*));
		for (j = 0; j < N; j++) {
		    map[i][j] =(int *) malloc(N*sizeof(int));
		}
	}
	//Create blank map
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				map[i][j][k]=-1;
			}
		}
	}
	//Create cubes at level 1
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			colour = rand() % 4;
			map[i][j][0] = colour;
		}
	}
	if (N%2==0){
		map[(int)round(N/2-1)][(int)round(N/2-1)][0]= 4;
		player.dimx= (int) round(N/2-1);
		player.dimy= (int) round(N/2-1);
		player.dimz= 1;
	}else{
		map[(int)round(N/2)][(int)round(N/2)][0]= 4;
		player.dimx= (int) round(N/2);
		player.dimy= (int) round(N/2);
		player.dimz= 1;
	}
	player.points=50;
	player.lifes=3;
}

int movement(int x, int y){
	int count=0,i;
	if(abs(x-player.dimx)<=1 && abs(y-player.dimy)<=1){
		if(x>=0 && x<=N-1 && y>=0 && y<=N-1){
			for (i=player.dimz; i>=0; i--){
				if(map[x][y][i]==-1){
					count++;
					if(i==0){
						count = -1;
						break;
					}
				}else{
					break;
				}
			}
			if(count==-1){                            //xanei zwh peftei sto keno
				player.lifes--;
				player.points=50;
				return 0;
			}else if(count==0){                       //anevainei ena epipedo
				if(map[x][y][player.dimz+1]==-1 && map[player.dimx][player.dimy][player.dimz+1]==-1){
					player.points+=5;
					player.dimx=x;
					player.dimy=y;
					player.dimz++;
					if (player.dimz==N-1){
						player.points += 100;
						player.lifes++;
					}
					return 1;
				}else{                                 //den kanei kinhsh, vrhke diplo kai parapanw kyvo
					return -1;
				}
			}else if(count==1){                        //proxwraei sto idio epipedo
				player.dimx=x;
				player.dimy=y;
				return 2;
			}else{
				player.dimx=x;
				player.dimy=y;
				player.dimz -= count-1;
				if(player.points-((count-2)*5)>0){		//peftei count epipeda, xanei pontous
					player.points -= (count-2)*5;
					return 3;
				}else{                                  //peftei count epipeda, omws xanei zwh giati den eftasan oi pontoi
					player.lifes--;
					player.points = 50;
					return -2;
				}
			}
		}
	}
	return -3;
}

int take_cube(){
	if(player.points>5 && map[player.dimx][player.dimy][player.dimz-1]!=0 && map[player.dimx][player.dimy][player.dimz-1]!=4 ){
		player.points-=5;
		player.v_cubes++;
		map[player.dimx][player.dimy][player.dimz-1]--;
		return 1;
	}
	return 0;
}

void destroy_cube(int x,int y){
	map[x][y][player.dimz]=-1;
}

void destroy_column(int x, int y){
	int i;
	if(x>=0 && x<=N-1 && y>=0 && y<=N-1){

        for (i=0; i<N; i++){
            if(map[x][y][i]!=4){
                map[x][y][i]=-1;
            }
        }
        player.lifes++;
        if (player.points>20){
            player.points -= 20;
        }else{
            player.lifes--;
            player.points =50;
        }
	}
}

int add_cube(int x,int y){
    if(x<0 || x>N-1 || y<0 && y>N-1){
        return -1;
    }
    if(player.v_cubes<1 || player.dimz==N-1){
        return -1;
    }
	int count=player.dimz+1,flag=0;
	if (map[x][y][player.dimz]==-1){
		map[x][y][player.dimz]=rand()%4;
		player.points += 5;
		player.v_cubes--;
		return 1;
	}else{
		while (map[x][y][count]!=-1){
			if (count==N-1){
				flag=1;
				break;
			}
			count++;
		}
		if (flag==0){
			map[x][y][count]=rand()%4;
			player.points += 5;
			player.v_cubes--;
			return 1;
		}
		return 0;
	}

}

void collapse(int k,int *on_cube){
	int i,j,a;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				a=k;
				if(map[i][j][a-1]==-1){
					map[i][j][a-1]=map[i][j][a];
					map[i][j][a]=-1;
					if(player.dimx==i && player.dimy==j && player.dimz==a){
                        player.dimz=a-1;
                        *on_cube=1;
					}
				}
			}
		}
		if(map[player.dimx][player.dimy][a]!=-1 && *on_cube==0){
            if (N%2==0){
                player.dimx= (int) round(N/2-1);
                player.dimy= (int) round(N/2-1);
            }else{
                player.dimx= (int) round(N/2);
                player.dimy= (int) round(N/2);
            }
            player.dimz= 1;
            player.lifes--;
            player.points=50;
        }
}

void kick_cube(int x,int y){
	int tmp, tmp_x=x, tmp_y=y;
	while(tmp_x<=N-1 && tmp_x>=0 && tmp_y>=0 && tmp_y<=N-1 && map[tmp_x][tmp_y][player.dimz]!=-1){
		tmp_x=tmp_x+(x-player.dimx);
		tmp_y=tmp_y+(y-player.dimy);
	}
	if (tmp_x==N){
		tmp_x=N-1;
	}
	if (tmp_y==N){
		tmp_y=N-1;
	}
	if (tmp_x==-1){
		tmp_x=0;
	}
	if (tmp_y==-1){
		tmp_y=0;
	}
	while(tmp_x!=x || tmp_y!=y){
		map[tmp_x][tmp_y][player.dimz]=map[tmp_x-(x-player.dimx)][tmp_y-(y-player.dimy)][player.dimz];
		tmp_x=tmp_x-(x-player.dimx);
		tmp_y=tmp_y-(y-player.dimy);
	}
	map[tmp_x][tmp_y][player.dimz]=-1;
}

