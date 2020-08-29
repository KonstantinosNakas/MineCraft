#ifndef MINECRAFT_H_INCLUDED
#define MINECRAFT_H_INCLUDED

void createMap();
int movement(int x, int y);
int take_cube();
void destroy_cube(int x,int y);
void destroy_column(int x, int y);
int add_cube(int x,int y);
void collapse();
void kick_cube(int x,int y);
extern int N;
extern int ***map;
typedef struct player_d {
	int dimx;
	int dimy;
	int dimz;
	int points;
	int lifes;
	int v_cubes;
} player_s;
extern player_s player;

#endif // MINECRAFT_H_INCLUDED
