#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#define GL_SILENCE_DEPRECATION
#include <math.h>
#include <stdio.h>

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// finally set the viewport to be the entire window
	glViewport(0, 0, w, h);
}


void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	gluLookAt(3.0f, 1.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
		
	// put drawing instructions here

	static float time = 0.0f;
	time += 0.01f;
	float scale = 0.5f * sin(time) + 1.5f;
	float colors = 0.5f * cos(time) + 1.0f;

	//defines object color
	glColor3f(colors, 0.5f * (1.0f - colors), 1.0f - colors); 

	glScalef(scale, scale, scale);

	glutWireTeapot(1);
	//glutWireSphere(1.0f, 100, 100);
	
	// End of frame
	glutSwapBuffers();
}


void printInfo() {
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv){
	// put GLUT init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(900, 900);
	glutCreateWindow("CG@DI");
    
	// put callback registry here
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	
	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background color
	
	printInfo();

	// enter GLUT�s main cycle
	glutMainLoop();
	
	return 1;
}