#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>



float rotateY = 0.0f; // horizontal rotation
float rotateX = 0.0f; // vertical rotation

float translateY = 0.0f;
float translateX = 0.0f;


int mouseActive = 0; // Indica se o mouse está ativo
int lastX, lastY; // Última posição do mouse

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


void pyramid(void){
	glBegin(GL_TRIANGLES);
		// Base do objeto (vermelho)
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		// Faces laterais

		// Frente (azul)
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		// Direita (verde)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);

		// Trás (amarelo)
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);
		
		// Esquerda (roxo)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);


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
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put axis drawing in here
	axis();

// put the geometric transformations here
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f); 
	glRotatef(rotateX, 0.0f, 0.0f, 1.0f);

	glTranslatef(translateX, translateY, 0.0f);

	glutPostRedisplay(); // Atualiza ecra  após a transformação

	// put pyramid drawing instructions here
	pyramid();

	// End of frame
	glutSwapBuffers();
}


void keyboardSpecialKey(int key_code, int x, int y) {
    switch (key_code) {
        case GLUT_KEY_LEFT: 
            rotateY += 1.0f; // Rotação no eixo Y (para esquerda)
            break;
        case GLUT_KEY_RIGHT: 
            rotateY += -1.0f;// Rotação no eixo Y (para direita)
            break;
        case GLUT_KEY_UP: 
            rotateX += 1.0f; // Rotação no eixo X (para cima)
            break;
        case GLUT_KEY_DOWN: 
            rotateX += -1.0f; // Rotação no eixo X (para baixo)
            break;
    }
    
}


void keyboardKeys(unsigned char key, int x, int y){
	switch (key){
		case 'w': translateY += 0.1f;break;
		case 'a': translateX += -0.1f;break;
		case 's': translateY += -0.1f;break;
		case 'd': translateX += 0.1f;break;
	}
}


// write function to process keyboard events


void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouseActive = 1;
			lastX = x;
			lastY = y;
		} else if (state == GLUT_UP) {
			mouseActive = 0;
		}
	}
}

// Captura movimento do mouse
void mouseMotion(int x, int y) {
	if (mouseActive) {
		int dx = x - lastX;
		int dy = y - lastY;
		rotateY += dx * 0.5f;
		rotateX -= dy * 0.5f;
		lastX = x;
		lastY = y;
	}
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

	
// put here the registration of the keyboard callbacks

	glutSpecialFunc(keyboardSpecialKey);
	glutKeyboardFunc(keyboardKeys);

	glutMouseFunc(mouseButton); // evita que as coordenadas do rato sejam consideradas para rotaçao no momento da rotação
	glutMotionFunc(mouseMotion);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
