#include <GL/glut.h>
#include <stdio.h>

#define RED 1,0,0
#define YELLOW 1,1,0
#define GREY .5,.5,.5
#define VERTICAL 1
#define HORIZONTAL 0

const GLfloat vertices[] ={
2,0,-1, 2,1,-1, -2,1,-1, -2,0,-1, /* back wall */
2,0, 1, 2,1, 1, -2,1, 1, -2,0, 1, /* front wall */
2,2,0, -2,2,0, 2.2,2,0, -2.2,2,0, /* top */
2.2,0.9,-1.1, -2.2,0.9,-1.1, 2.2,0.9,1.1, -2.2,0.9,1.1, /* edges of the roof */
1,0,0.5, 1.25,0,0.5, 1.25,0,0.25, 1,0,0.25, 1,2.5,0.5, 1.25,2.5,0.5, 1.25,2.5,0.25, 1,2.5,0.25 /* chimney */
};

const GLfloat colours[] = {
  GREY, GREY, GREY, GREY,
  GREY, GREY, GREY, GREY,
  GREY, GREY, RED, RED,
  RED, RED, RED, RED,
  YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW
};

const GLubyte triangles[] = {
16,20,21,
16,17,21,

17,21,18,
18,21,22,

18,19,22,
19,22,23,

19,16,23,
23,16,20,

20,21,22,
20,22,23,
  
0,1,2,
2,3,0,

0,4,1,
1,5,4,

4,5,6,
6,7,4,

7,6,2,
7,3,2,

6,2,9,
1,5,8,

11,12,13,
11,10,12,

11,14,15,
11,10,14
};

GLenum polygonMode = GL_FILL;
double rotationVertical = 0.;
double rotationHorizontal = 0.;
int runOnTimer = 0;

void display() {
        glClearColor(1., 1., 1., 1.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-1, 0,0,0, 0,1,0);
	glOrtho(-10., 10., -10., 10., -10., 100.);
	
	glRotatef(rotationVertical, 0., 1., 0.);
	glRotatef(rotationHorizontal, 1., 0., 0.);
	
        glDrawElements(GL_TRIANGLES, sizeof(triangles) / sizeof(GLubyte), GL_UNSIGNED_BYTE, triangles);

        glutSwapBuffers();
}

void rotateAroundCenter(double angle, int axis) {
  if(VERTICAL == axis) 
    rotationVertical += angle;
  else
    rotationHorizontal += angle;
  
  //printf("called with %lf degrees round axis %d - result: vertical: %lf , horizontal: %lf\n", angle, axis, rotationVertical, rotationHorizontal);
  
  glutPostRedisplay();
}

// slowly rotates on its own around the y-axis
void timer(int value) {
  if(!runOnTimer) return;
  
  rotateAroundCenter(.4, VERTICAL);
  glutTimerFunc(20, timer, 0);
}

// WASD for rotation, f for switching between filled faces and wireframe, t for toggling auto-rotation, c for resetting orientation
void keyboardInput(unsigned char key, int x, int y) {
  switch(key) {
    case 'f':
      polygonMode = polygonMode == GL_LINE ? GL_FILL : GL_LINE;
      glutPostRedisplay();
      break;
    case 'w': rotateAroundCenter(20., HORIZONTAL); break;
    case 'a': rotateAroundCenter(-20., VERTICAL); break;
    case 's': rotateAroundCenter(-20., HORIZONTAL); break;
    case 'd': rotateAroundCenter(20., VERTICAL); break;
    case 't': runOnTimer = !runOnTimer; 
	      glutTimerFunc(20, timer, 0); 
	      break;
    case 'c': rotationHorizontal = rotationVertical = 0.;
	      glutPostRedisplay(); 
	      break;
  }
}

int main (int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(900, 600);
	glutCreateWindow("House");
        glutKeyboardFunc(keyboardInput);
	glutDisplayFunc(display);

	glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colours);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

        return 0;
}
