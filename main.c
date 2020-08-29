#include <GL/glut.h>
#include "minecraft.h"
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-90.0f;
// XZ position of the camera
float x;
float z;
float y;
int xsub = 0;
int zsub = 1;
int ysub = 1;
int direction=0;
int left_btn=0;
int on_cube=0;
int lookat_distance=8;
int teapot_x=0,teapot_y=0;
float red = 1.0f, green = 1.0f, blue = 1.0f;

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_COLOR_MATERIAL);
}

void processSpecialKeys(unsigned char key, int a, int b) {

	float fraction = 0.1f;
	int result,i,j;
    int temp_lifes;
    int dimz_before;
    lookat_distance=8;
    teapot_x=0;
    teapot_y=0;
	switch (key) {
		case 'a' :
		    if(direction==0){
                direction=1;
                xsub=-1;
                zsub=0;
		    }else if(direction==1){
                direction=2;
                xsub=0;
                zsub=-1;
		    }else if(direction==2){
                direction=3;
                xsub=1;
                zsub=0;
		    }else{
                direction=0;
                xsub=0;
                zsub=1;
		    }
			angle -= 1.57f;
			lx = sin(angle);
			lz = -cos(angle);
			if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
			break;
		case 'd' :
			angle += 1.57f;
			lx = sin(angle);
			lz = -cos(angle);
			if(direction==0){
                direction=3;
                xsub=1;
                zsub=0;
		    }else if(direction==1){
                direction=0;
                xsub=0;
                zsub=1;
		    }else if(direction==2){
                direction=1;
                xsub=-1;
                zsub=0;
		    }else{
                direction=2;
                xsub=0;
                zsub=-1;
		    }
		    if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                printf("sfgsf");
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
			break;
		case 'w' :
		    dimz_before=player.dimz;
		    result=movement(player.dimx+xsub,player.dimy-zsub);
		    if(player.lifes==0){
                printf("------------------------------------------------------------\n------------------------------------------------------------\n");
                printf("-------------------------GAME OVER!-------------------------\n");
                printf("------------------------------------------------------------\n------------------------------------------------------------\n");
                exit(0);
		    }
		    if(result==2){
                x = x+(5.0f*xsub);
                z = z-(5.0f*zsub);
		    }else if(result==1){
                x = x+(5.0f*xsub);
                z = z-(5.0f*zsub);
                y += (5.0f*ysub);
		    }
            else if(result==0 || result==-2){
                if (N%2==0){
                    x=-5.0f;
                    z=-5.0f;
                    player.dimx= (int) round(N/2-1);
                    player.dimy= (int) round(N/2-1);
                }else{
                    x=0.0f;
                    z=0.0f;
                    player.dimx= (int) round(N/2);
                    player.dimy= (int) round(N/2);
                }
                y=5.0f;
                player.dimz = 1;
                map[player.dimx][player.dimy][player.dimz]=-1;
            }else if(result==3){
                x = x+(5.0f*xsub);
                z = z-(5.0f*zsub);
                for(i=dimz_before; i>=player.dimz; i--){
                    y = (5.0f*i);
                    display();
                    delay(80);
                }
            }
            if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
			break;
		case 's' :
			angle += 3.14f;
			lx =sin(angle);
			lz =-cos(angle);
			xsub=-xsub;
            zsub=-zsub;
            if(direction-2<0){
                direction=direction+2;
            }else{
                direction=direction-2;
            }
            if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
			break;
        case ' ' :
            take_cube();
            if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
            break;
        case 'q' :
            destroy_cube(player.dimx+xsub,player.dimy-zsub);
            if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
            break;
        case 'e' :
            destroy_column(player.dimx+xsub,player.dimy-zsub);
            if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
            break;
        case 'r' :
            for (i = 1; i < N; i++) {
                for (j = 1; j < N; j++) {
                        temp_lifes=player.lifes;
                        collapse(j,&on_cube);
                        y=player.dimz*5;
                        if(player.lifes==temp_lifes-1){
                            if (N%2==0){
                                x=-5.0f;
                                z=-5.0f;
                            }else{
                                x=0.0f;
                                z=0.0f;
                            }
                            y=5.0f;
                        }
                        if(player.lifes==0){
                            printf("------------------------------------------------------------\n------------------------------------------------------------\n");
                            printf("-------------------------GAME OVER!-------------------------\n");
                            printf("------------------------------------------------------------\n------------------------------------------------------------\n");
                            exit(0);
                        }
                }
                display();
                delay(80);
            }
            on_cube=0;
            if(player.dimx-xsub>-1 && player.dimx-xsub<N && player.dimy+zsub>-1 && player.dimy+zsub<N && player.dimz>-1 && player.dimz<N && map[player.dimx-xsub][player.dimy+zsub][player.dimz]!=-1){
                lookat_distance=1;
                teapot_x=xsub*2;
                teapot_y=zsub*2;
            }
            break;
	case 27:
		exit(0);
    }
}

void processMouseClick(int button, int state, int a, int b){
    switch(button){
        case GLUT_LEFT_BUTTON:
            left_btn++;
            if(left_btn%2==0){
                add_cube(player.dimx+xsub,player.dimy-zsub);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            kick_cube(player.dimx+xsub,player.dimy-zsub);
            break;
    }
}

void renderBitmapString(float x,void *font,const char *string){
    const char *c;
    glRasterPos3f(-1.0f,0.0f,-1.0f);
    for (c=string; *c != '\0'; c++) {

        glutBitmapCharacter(font, *c);
    }
}

void display()
{
    int i,j,k;
    char s[80];
    GLfloat color[]={1.0,1.0,1.0,1.0};
    sprintf(s, "Lifes: %d Points: %d Cubes: %d", player.lifes,player.points,player.v_cubes);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(x-xsub*lookat_distance, y+0.6, z+zsub*lookat_distance, x+lx, y-0.6, z+lz, 0.0f, 1.0f,  0.0f);
    //Teapot
    glPushMatrix();
    glTranslatef(x+teapot_x,(y-5)+2.8,z-teapot_y);
    glColor3ub(161,80,8);
    glutSolidTeapot(0.5);
    glPopMatrix();

    for (k=0; k<N; k++){
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                    if(map[i][j][k] == 1){
                       glPushMatrix();
                       glTranslatef(((i-(round(N/2)))*5),k*5,((j-(round(N/2)))*5));
                       glColor3ub(255,255,0);
                       glutSolidCube(5);
                       glPopMatrix();
                    }else if(map[i][j][k] == 2){
                       glPushMatrix();
                       glTranslatef(((i-(round(N/2)))*5),k*5,((j-(round(N/2)))*5));
                       glColor3ub(255,0,0);
                       glutSolidCube(5);
                       glPopMatrix();
                    }else if(map[i][j][k] == 3){
                       glPushMatrix();
                       glTranslatef(((i-(round(N/2)))*5),k*5,((j-(round(N/2)))*5));
                       glColor3ub(0,255,0);
                       glutSolidCube(5);
                       glPopMatrix();
                    }else if(map[i][j][k] == 0){
                       glPushMatrix();
                       glTranslatef(((i-(round(N/2)))*5),k*5,((j-(round(N/2)))*5));
                       glColor3ub(0,0,255);
                       glutSolidCube(5);
                       glPopMatrix();
                    }else if(map[i][j][k] == 4){
                       glPushMatrix();
                       glTranslatef(((i-(round(N/2)))*5),k*5,((j-(round(N/2)))*5));
                       glColor3ub(255,0,255);
                       glutSolidCube(5);
                       glPopMatrix();
                    }
            }

        }
    }


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    renderBitmapString(-1.0f,GLUT_BITMAP_9_BY_15,s);

    glEnable(GL_DEPTH_TEST); // turn depth testing back on
    glEnable(GL_LIGHTING); // turn lighting back on

    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); // revert back to the matrix we had before
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

    // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv)
{
    printf("Give dimension: ");
    scanf("%d",&N);
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("MINECRAFT");
    createMap();
    if (N%2==0){
        x=-5.0f;
        z=-5.0f;
    }else{
        x=0.0f;
        z=0.0f;
    }
    y=5.0f;

    GLfloat light_pos[4] = {0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat light_dir[3] = {0.0f, 0.0f, 0.0f};

    float light_diffuse[]={1.0,1.0,1.0,0.1};

    if(N%2==0){
        light_pos[0]= -5 * (N/2);
        light_pos[2]= -5 * (N/2);
    }else{
        light_pos[0]= -5 * floor(N/2);
        light_pos[2]= -5 * floor(N/2);
    }
    light_pos[1] = N * 5;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01/N);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);

    if(N%2==0){
        light_pos[0]= 5 * (N/2-1);
        light_pos[2]= -5 * (N/2);
    }else{
        light_pos[0]= 5 * floor(N/2);
        light_pos[2]= -5 * floor(N/2);
    }
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01/N);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);

    if(N%2==0){
        light_pos[0]= 5 * (N/2-1);
        light_pos[2]= 5 * (N/2-1);
    }else{
        light_pos[0]= 5 * floor(N/2);
        light_pos[2]= 5 * floor(N/2);
    }
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01/N);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);

    if(N%2==0){
        light_pos[0]= -5 * (N/2);
        light_pos[2]= 5 * (N/2-1);
    }else{
        light_pos[0]= -5 * floor(N/2);
        light_pos[2]= 5 * floor(N/2);
    }
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01/N);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

	glutKeyboardFunc(processSpecialKeys);
	glutMouseFunc(processMouseClick);

    init();

    glutMainLoop();
    return 0;
}
