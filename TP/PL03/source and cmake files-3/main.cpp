#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#define MIN_BETA -90
#define MAX_BETA 90

float alpha = 45.0f;
float beta = 45.0f;
float radius = 5.0f;

float px = 5.0f, py = 5.0f, pz = 5.0f; // initial camera Position
float lx = 0.0f, ly = 0.0f, lz = 0.0f; //camera lookAt


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {
	float delta = 2 * M_PI / slices;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    
    for (int i = 0; i < slices; ++i) {
        glVertex3f(0, -height / 2, 0);
        glVertex3f(radius * sin((i + 1) * delta), -height / 2, radius * cos((i + 1) * delta));
        glVertex3f(radius * sin(i * delta), -height / 2, radius * cos(i * delta));
    }
    
    for (int i = 0; i < slices; ++i) {
        glVertex3f(0, height / 2, 0);
        glVertex3f(radius * sin(i * delta), height / 2, radius * cos(i * delta));
        glVertex3f(radius * sin((i + 1) * delta), height / 2, radius * cos((i + 1) * delta));
    }
    
    for (int i = 0; i < slices; ++i) {
        glVertex3f(radius * sin((i + 1) * delta), height / 2, radius * cos((i + 1) * delta));
        glVertex3f(radius * sin(i * delta), height / 2, radius * cos(i * delta));
        glVertex3f(radius * sin(i * delta), -height / 2, radius * cos(i * delta));

        glVertex3f(radius * sin((i + 1) * delta), -height / 2, radius * cos((i + 1) * delta));
        glVertex3f(radius * sin((i + 1) * delta), height / 2, radius * cos((i + 1) * delta));
        glVertex3f(radius * sin(i * delta), -height / 2, radius * cos(i * delta));
    }
    
    glEnd();

}

void axis(void){
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	px = radius * cos(beta) * sin(alpha);
	py = radius * sin(beta);
	pz = radius * cos(beta) * cos (alpha);

	// camera mode for the assigment is just the explorer mode camera
	gluLookAt(px,py,pz, 
		      lx, ly, lz,
			  0.0f,1.0f,0.0f);

	axis();
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCylinder(1,2,100);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
    float moveSpeed = 1.0f;

    switch (c) {
        case 'w':
            radius -= moveSpeed;
            if (radius < 1.0f) radius = 1.0f; 
            break;
        case 's': 
            radius += moveSpeed;
            break;
        case 'a': 
            alpha -= 0.1f;
            break;
        case 'd': 
            alpha += 0.1f;
            break;
    }
	glutPostRedisplay();

}

void processSpecialKeys(int key, int xx, int yy) {
    float lookSpeed = 0.1f;

    switch (key) {
        case GLUT_KEY_UP: 
            beta += lookSpeed;
            if (beta > MAX_BETA) beta = MAX_BETA;
            break;
        case GLUT_KEY_DOWN:
			beta -= lookSpeed;
            if (beta < MIN_BETA) beta = MIN_BETA;
            break;
        case GLUT_KEY_LEFT:
            alpha -= lookSpeed;
            break;
        case GLUT_KEY_RIGHT:
            alpha += lookSpeed;
            break;
    }

    glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
