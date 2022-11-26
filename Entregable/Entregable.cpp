/*!
	Animacion.cpp

	Programa para manejar la variable temporal y
	actualizar la escena en cada frame

	@author		Roberto Vivo' <rvivo@upv.es>
	@date		Oct,2022
 */

#define PROYECTO "ISGI::S5E01::Animacion"

#include <iostream>		
#include <sstream>
#include <Utilidades.h>

 // Variables dependientes del tiempo
static float angulo = 0;

static const int tasaFPS = 60;

using namespace std;
int i;
float grosor = 1;
static const GLfloat vertices[48] = { 0,0.5,0.1, 0.4,0.4,0.1, 0.5,0,0.1, 0.4,-0.4,0.1, 0,-0.5,0.1, -0.4,-0.4,0.1, -0.5,0,0.1, -0.4,0.4,0.1, 0,0.5,-0.1, 0.4,0.4,-0.1, 0.5,0,-0.1, 0.4,-0.4,-0.1, 0,-0.5,-0.1, -0.4,-0.4,-0.1, -0.5,0,-0.1, -0.4,0.4,-0.1 };
static const GLfloat vertices2[24] = { 0,0.5,-0.1, 0.25,0.25,-0.1, 0.5,0,-0.1, 0.25,-0.25,-0.1, 0,-0.5,-0.1, -0.25,-0.25,-0.1, -0.5,0,-0.1, -0.25,0.25,-0.1 };
static const GLfloat colores[24] = { 1,0,0, 1,0,0,  1,0,0,  1,0,0,  1,0,0,  1,0,0,  1,0,0, 1,0,0 };
static const GLuint indices[72] = { 0,1,1, 1,2,2, 2,3,3, 3,4,4, 4,5,5, 5,6,6, 6,7,7, 7,0,0, 8,9,9, 9,10,10, 10,11,11, 11,12,12, 12,13,13, 13,14,14, 14,15,15, 15,8,8, 0,8,8, 1,9,9, 2,10,10, 3,11,11, 4,12,12, 5,13,13, 6,14,14, 7,15,15};

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	// Inicializaciones 
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY); // Activa el uso del array de vertices
	glVertexPointer(3, GL_FLOAT, 0, vertices);// Carga el array de vertices
	//glVertexPointer(3, GL_FLOAT, 0, vertices2);
}

void FPS()
{
	// Cuenta los fotogramas por segundo y los muestra en
	// la barra de titulo de la ventana

	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int fotogramas = 0;
	int ahora, tiempoTranscurrido;

	fotogramas++;

	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempoTranscurrido = (ahora - antes) / 1000;

	// si ha transcurrido mas de un segundo, muestro los FPS y reinicio
	// la cuenta y el reloj
	if (tiempoTranscurrido >= 1) {
		stringstream titulo;
		titulo << "FPS= " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		// reinicio
		antes = ahora;
		fotogramas = 0;
	}
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Seleccionar la MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Situar y orientar la camara
	gluLookAt(3, 2, 3, 0, 0, 0, 0, 1, 0);
	ejes();
	glPushMatrix();
	//glRotatef(20, -1, -5, 0);
	glRotatef(angulo/2, 0, 0, 1); 
	//glTranslatef(0, 1, 0); 
	//glutWireSphere(0.1, 20,10); 
	//glutWireTeapot(0.2);
	//glRotatef(angulo, 0, 0, 1);
	//glTranslatef(0, 1, 0);
	//glRotatef(90, 0, 1, 0);
	glEnableClientState(GL_COLOR_ARRAY); // Activa el uso del array de colores
	glColorPointer(3, GL_FLOAT, 0, colores); // Carga el array de colores
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Las caras del poligono rellenas
	glLineWidth(6);
	// Dibujo del octaedro como 8 triangulos coloreados
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_COLOR_ARRAY); // Desactiva el array de colores
	glColor3f(1, 1, 0); // Fija el color a blaco
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Las caras del poligono en alambrico
	// Dibujo del octaedro como 8 triangulos en alambrico
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, indices);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0, 0.1, 0.1); glVertex3f(0, 0.5, 0.1);
	glVertex3f(0, 0.1, -0.1); glVertex3f(0, 0.5, -0.1);
	glVertex3f(0.05, 0.07, 0.1); glVertex3f(0.4, 0.4, 0.1);
	glVertex3f(0.1, 0, 0.1); glVertex3f(0.5, 0, 0.1);
	glVertex3f(0.05, -0.07, 0.1); glVertex3f(0.4, -0.4, 0.1);
	glVertex3f(0, -0.1, 0.1); glVertex3f(0, -0.5, 0.1);
	glVertex3f(-0.05, -0.07, 0.1); glVertex3f(-0.4, -0.4, 0.1);
	glVertex3f(-0.1, 0, 0.1); glVertex3f(-0.5, 0, 0.1);
	glVertex3f(-0.05, 0.07, 0.1); glVertex3f(-0.4, 0.4, 0.1);
	glVertex3f(0.05, 0.07, -0.1); glVertex3f(0.4, 0.4, -0.1);
	glVertex3f(0.1, 0, -0.1); glVertex3f(0.5, 0, -0.1);
	glVertex3f(0.05, -0.07, -0.1); glVertex3f(0.4, -0.4, -0.1);
	glVertex3f(0, -0.1, -0.1); glVertex3f(0, -0.5, -0.1);
	glVertex3f(-0.05, -0.07, -0.1); glVertex3f(-0.4, -0.4, -0.1);
	glVertex3f(-0.1, 0, -0.1); glVertex3f(-0.5, 0, -0.1);
	glVertex3f(-0.05, 0.07, -0.1); glVertex3f(-0.4, 0.4, -0.1);
	glEnd();
	//glRotatef(angulo / 2, 0, 1, 0);
	glPopMatrix();

	glPushMatrix();
	//glLoadIdentity();
	glColor3f(1, 0.5, 0.5);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0.1, 0, 0.15);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(0.1, 0, 0.15);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0.1, 0, 0.15);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(0.1, 0, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glColor3f(1, 0.5, 0.5);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0.1, 0, 0.15);
	glVertex3f(0.65, -1, 0.15);
	glVertex3f(0.45, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(0.65, -1, 0.2);
	glVertex3f(0.45, -1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(0.1, 0, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.45, -1, 0.15);
	glVertex3f(0.45, -1, 0.2);
	glVertex3f(0.65, -1, 0.2);
	glVertex3f(0.65, -1, 0.15);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0.1, 0, 0.15);
	glVertex3f(0.65, -1, 0.15);
	glVertex3f(0.45, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(0.65, -1, 0.2);
	glVertex3f(0.45,-1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.1, 0, 0.2);
	glVertex3f(0.1, 0, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.45, -1, 0.15);
	glVertex3f(0.45, -1, 0.2);
	glVertex3f(0.65, -1, 0.2);
	glVertex3f(0.65, -1, 0.15);
	glEnd();

	//glColor3f(1, 0.5, 0);
	//glBegin(GL_POLYGON);


	/*glPushMatrix();
	glTranslatef(0.2, 1, 0);
	glRotatef(90, 0, 1, 0);
	glEnableClientState(GL_COLOR_ARRAY); // Activa el uso del array de colores
	glColorPointer(3, GL_FLOAT, 0, colores); // Carga el array de colores
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Las caras del poligono rellenas
	// Dibujo del octaedro como 8 triangulos coloreados
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_COLOR_ARRAY); // Desactiva el array de colores
	glColor3f(1, 1, 1); // Fija el color a blaco
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Las caras del poligono en alambrico
	// Dibujo del octaedro como 8 triangulos en alambrico
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
	//glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glEnableClientState(GL_COLOR_ARRAY); // Activa el uso del array de colores
	glColorPointer(3, GL_FLOAT, 0, colores); // Carga el array de colores
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Las caras del poligono rellenas
	// Dibujo del octaedro como 8 triangulos coloreados
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_COLOR_ARRAY); // Desactiva el array de colores
	glColor3f(1, 1, 1); // Fija el color a blaco
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Las caras del poligono en alambrico
	// Dibujo del octaedro como 8 triangulos en alambrico
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
	//glPopMatrix();
	glPopMatrix();

	/*glPushMatrix();
	glTranslatef(0.2, 1, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glEnableClientState(GL_COLOR_ARRAY); // Activa el uso del array de colores
	glColorPointer(3, GL_FLOAT, 0, colores); // Carga el array de colores
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Las caras del poligono rellenas
	// Dibujo del octaedro como 8 triangulos coloreados
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_COLOR_ARRAY); // Desactiva el array de colores
	glColor3f(1, 1, 1); // Fija el color a blaco
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Las caras del poligono en alambrico
	// Dibujo del octaedro como 8 triangulos en alambrico
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
	//glPopMatrix();
	glPopMatrix();

	float p = 0.4;
	for (i = 0; i <= 5; i++) {
		glPushMatrix();
		glTranslatef(p, 1, 0);
		glRotatef(90, 0, 1, 0);//NO SE PUEDE HACER ASÍ PORQUE ROTAN 2 ANGULOS A LA VEZ Y NO ES EL RESULTADO ESPERADO, CAMBIAR LAS COORDENADAS
		glEnableClientState(GL_COLOR_ARRAY); // Activa el uso del array de colores
		glColorPointer(3, GL_FLOAT, 0, colores); // Carga el array de colores
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Las caras del poligono rellenas
		// Dibujo del octaedro como 8 triangulos coloreados
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
		glDisableClientState(GL_COLOR_ARRAY); // Desactiva el array de colores
		glColor3f(1, 1, 1); // Fija el color a blaco
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Las caras del poligono en alambrico
		// Dibujo del octaedro como 8 triangulos en alambrico
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
		p += 0.1;
		glPopMatrix();
	}*/
	glutSwapBuffers();

	FPS();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	float relacionAspecto = float(w) / h;
	glViewport(0, 0, w, h);

	// Definir la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	if(relacionAspecto>1)
		glOrtho(-2*relacionAspecto, 2*relacionAspecto, -2, 2, -20, 20);
	else
		glOrtho(-2, 2, -2/relacionAspecto, 2/relacionAspecto, -20, 20);
	*/

	gluPerspective(30, relacionAspecto, 0.1, 100);
}

void onIdle()
{
	// Callback de atencion al evento idle (sin faena)

	// sin control del tiempo
	///angulo += 0.1;

	// con control del tiempo
	static const float vueltasPorSegundo = 0.1;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	angulo += vueltasPorSegundo * 360 * (ahora - antes) / 1000;

	antes = ahora;

	glutPostRedisplay();

}

void onTimer(int tiempo)
{
	// Callback de atencion a la cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);

	onIdle();
}

int main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(onIdle);
	glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}