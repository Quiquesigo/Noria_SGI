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
static const GLfloat colores[24] = { 1,0,0, 1,0,0,  1,0,0,  1,0,0,  1,0,0,  1,0,0,  1,0,0, 1,0,0 };
static const GLuint indices[72] = { 0,1,1, 1,2,2, 2,3,3, 3,4,4, 4,5,5, 5,6,6, 6,7,7, 7,0,0, 8,9,9, 9,10,10, 10,11,11, 11,12,12, 12,13,13, 13,14,14, 14,15,15, 15,8,8, 0,8,8, 1,9,9, 2,10,10, 3,11,11, 4,12,12, 5,13,13, 6,14,14, 7,15,15};

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	// Inicializaciones 
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY); // Activa el uso del array de vertices
	glVertexPointer(3, GL_FLOAT, 0, vertices);// Carga el array de vertices
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

	// si ha transcurrido mas de un segundo, se muestran los FPS y reinicio
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
	gluLookAt(5, 2, 5, 0, 0, 0, 0, 1, 0);
	glPopMatrix();
	glRotatef(angulo/4, 0, 0.5, 0);
	glPushMatrix();
	glRotatef(-angulo/2, 0, 0, 1); 
	glEnableClientState(GL_COLOR_ARRAY); 
	glColorPointer(3, GL_FLOAT, 0, colores); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glLineWidth(6);
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_COLOR_ARRAY); 
	glColor3f(0, 0, 0); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, indices);
	glLineWidth(1);

	//Metales que sujetan la noria al cilindro
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

	//Metal que sujeta asientos al circulo exterior
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0.45, 0.07); glVertex3f(0, 0.5, 0.07);
	glVertex3f(0, 0.5, -0.07); glVertex3f(0, 0.45, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.35, 0.35, 0.07); glVertex3f(0.4, 0.4, 0.07);
	glVertex3f(0.4, 0.4, -0.07); glVertex3f(0.35, 0.35, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.45, 0, 0.07); glVertex3f(0.5, 0, 0.07);
	glVertex3f(0.45, 0, -0.07); glVertex3f(0.5, 0, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.35, -0.35, 0.07); glVertex3f(0.4, -0.4, 0.07);
	glVertex3f(0.4, -0.4, -0.07); glVertex3f(0.35, -0.35, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0, -0.45, 0.07); glVertex3f(0, -0.5, 0.07);
	glVertex3f(0, -0.5, -0.07); glVertex3f(0, -0.45, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-0.35, -0.35, 0.07); glVertex3f(-0.4, -0.4, 0.07);
	glVertex3f(-0.4, -0.4, -0.07); glVertex3f(-0.35, -0.35, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-0.45, 0, 0.07); glVertex3f(-0.5, 0, 0.07);
	glVertex3f(-0.45, 0, -0.07); glVertex3f(-0.5, 0, -0.07);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-0.35, 0.35, 0.07); glVertex3f(-0.4, 0.4, 0.07);
	glVertex3f(-0.4, 0.4, -0.07); glVertex3f(-0.35, 0.35, -0.07);
	glEnd();

	//Asientos en alambrico
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.45, 0.07); glVertex3f(0, 0.45, -0.07);
	glVertex3f(0, 0.4, -0.07); glVertex3f(0, 0.4, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.4, -0.07); glVertex3f(0, 0.4, 0.07);
	glVertex3f(0.07, 0.4, 0.07); glVertex3f(0.07, 0.4, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, -0.45, 0.07); glVertex3f(0, -0.45, -0.07);
	glVertex3f(0, -0.4, -0.07); glVertex3f(0, -0.4, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, -0.4, -0.07); glVertex3f(0, -0.4, 0.07);
	glVertex3f(-0.07, -0.4, 0.07); glVertex3f(-0.07, -0.4, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.45, 0, 0.07); glVertex3f(0.45, 0, -0.07);
	glVertex3f(0.4, 0, -0.07); glVertex3f(0.4, 0, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.4, 0, -0.07); glVertex3f(0.4, 0, 0.07);
	glVertex3f(0.4, -0.07, 0.07); glVertex3f(0.4, -0.07, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0, 0.07); glVertex3f(-0.45, 0, -0.07);
	glVertex3f(-0.4, 0, -0.07); glVertex3f(-0.4, 0, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 0, -0.07); glVertex3f(-0.4, 0, 0.07);
	glVertex3f(-0.4, 0.07, 0.07); glVertex3f(-0.4, 0.07, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.35, 0.35, 0.07); glVertex3f(0.35, 0.35, -0.07);
	glVertex3f(0.3, 0.3, -0.07); glVertex3f(0.3, 0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.3, 0.3, -0.07); glVertex3f(0.3, 0.3, 0.07);
	glVertex3f(0.35, 0.25, 0.07); glVertex3f(0.35, 0.25, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 0.35, 0.07); glVertex3f(-0.35, 0.35, -0.07);
	glVertex3f(-0.3, 0.3, -0.07); glVertex3f(-0.3, 0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.3, 0.3, -0.07); glVertex3f(-0.3, 0.3, 0.07);
	glVertex3f(-0.25, 0.35, 0.07); glVertex3f(-0.25, 0.35, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.35, -0.35, 0.07); glVertex3f(0.35, -0.35, -0.07);
	glVertex3f(0.3, -0.3, -0.07); glVertex3f(0.3, -0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.3, -0.3, -0.07); glVertex3f(0.3, -0.3, 0.07);
	glVertex3f(0.25, -0.35, 0.07); glVertex3f(0.25, -0.35, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, -0.35, 0.07); glVertex3f(-0.35, -0.35, -0.07);
	glVertex3f(-0.3, -0.3, -0.07); glVertex3f(-0.3, -0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.3, -0.3, -0.07); glVertex3f(-0.3, -0.3, 0.07);
	glVertex3f(-0.35, -0.25, 0.07); glVertex3f(-0.35, -0.25, -0.07);
	glEnd();

	//Asientos rellenados
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.45, 0.07); glVertex3f(0, 0.45, -0.07);
	glVertex3f(0, 0.4, -0.07); glVertex3f(0, 0.4, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.4, -0.07); glVertex3f(0, 0.4, 0.07);
	glVertex3f(0.07, 0.4, 0.07); glVertex3f(0.07, 0.4, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, -0.45, 0.07); glVertex3f(0, -0.45, -0.07);
	glVertex3f(0, -0.4, -0.07); glVertex3f(0, -0.4, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, -0.4, -0.07); glVertex3f(0, -0.4, 0.07);
	glVertex3f(-0.07, -0.4, 0.07); glVertex3f(-0.07, -0.4, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.45, 0, 0.07); glVertex3f(0.45, 0, -0.07);
	glVertex3f(0.4, 0, -0.07); glVertex3f(0.4, 0, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.4, 0, -0.07); glVertex3f(0.4, 0, 0.07);
	glVertex3f(0.4, -0.07, 0.07); glVertex3f(0.4, -0.07, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0, 0.07); glVertex3f(-0.45, 0, -0.07);
	glVertex3f(-0.4, 0, -0.07); glVertex3f(-0.4, 0, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 0, -0.07); glVertex3f(-0.4, 0, 0.07);
	glVertex3f(-0.4, 0.07, 0.07); glVertex3f(-0.4, 0.07, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.35, 0.35, 0.07); glVertex3f(0.35, 0.35, -0.07);
	glVertex3f(0.3, 0.3, -0.07); glVertex3f(0.3, 0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.3, 0.3, -0.07); glVertex3f(0.3, 0.3, 0.07);
	glVertex3f(0.35, 0.25, 0.07); glVertex3f(0.35, 0.25, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 0.35, 0.07); glVertex3f(-0.35, 0.35, -0.07);
	glVertex3f(-0.3, 0.3, -0.07); glVertex3f(-0.3, 0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.3, 0.3, -0.07); glVertex3f(-0.3, 0.3, 0.07);
	glVertex3f(-0.25, 0.35, 0.07); glVertex3f(-0.25, 0.35, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.35, -0.35, 0.07); glVertex3f(0.35, -0.35, -0.07);
	glVertex3f(0.3, -0.3, -0.07); glVertex3f(0.3, -0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.3, -0.3, -0.07); glVertex3f(0.3, -0.3, 0.07);
	glVertex3f(0.25, -0.35, 0.07); glVertex3f(0.25, -0.35, -0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, -0.35, 0.07); glVertex3f(-0.35, -0.35, -0.07);
	glVertex3f(-0.3, -0.3, -0.07); glVertex3f(-0.3, -0.3, 0.07);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.3, -0.3, -0.07); glVertex3f(-0.3, -0.3, 0.07);
	glVertex3f(-0.35, -0.25, 0.07); glVertex3f(-0.35, -0.25, -0.07);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1);

	//Amarre delantero izquierdo
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.15);
	glVertex3f(0, 0, 0.15);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.2);
	glVertex3f(0, 0, 0.2);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.15);
	glVertex3f(-0.05, 0, 0.2);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0, 0, 0.15);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.15);
	glVertex3f(-0.05, 0, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.15);
	glVertex3f(0, 0, 0.15);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.2);
	glVertex3f(0, 0, 0.2);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0.15);
	glVertex3f(-0.05, 0, 0.2);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0, 0, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.45, -1, 0.15);
	glVertex3f(-0.45, -1, 0.2);
	glVertex3f(-0.65, -1, 0.2);
	glVertex3f(-0.65, -1, 0.15);
	glEnd();

	//Amarre delantero derecho
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0.05, 0, 0.15);
	glVertex3f(0.45, -1, 0.15);
	glVertex3f(0.25, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.05, 0, 0.2);
	glVertex3f(0.45, -1, 0.2);
	glVertex3f(0.25, -1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.05, 0, 0.2);
	glVertex3f(0.05, 0, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.25, -1, 0.15);
	glVertex3f(0.25, -1, 0.2);
	glVertex3f(0.45, -1, 0.2);
	glVertex3f(0.45, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.05, 0, 0.2);
	glVertex3f(0.05, 0, 0.15);
	glVertex3f(0.45, -1, 0.15);
	glVertex3f(0.45, -1, 0.2);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0.05, 0, 0.15);
	glVertex3f(0.45, -1, 0.15);
	glVertex3f(0.25, -1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.05, 0, 0.2);
	glVertex3f(0.45, -1, 0.2);
	glVertex3f(0.25,-1, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(0.05, 0, 0.2);
	glVertex3f(0.05, 0, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.25, -1, 0.15);
	glVertex3f(0.25, -1, 0.2);
	glVertex3f(0.45, -1, 0.2);
	glVertex3f(0.45, -1, 0.15);
	glEnd();

	//Amarre detras izquierdo
	glColor3f(0.5, 0.5, 0.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.15);
	glVertex3f(0, 0, -0.15);
	glVertex3f(-0.45, -1, -0.15);
	glVertex3f(-0.65, -1, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.2);
	glVertex3f(0, 0, -0.2);
	glVertex3f(-0.45, -1, -0.2);
	glVertex3f(-0.65, -1, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.15);
	glVertex3f(-0.05, 0, -0.2);
	glVertex3f(0, 0, -0.2);
	glVertex3f(0, 0, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.45, -1, -0.15);
	glVertex3f(-0.45, -1, -0.2);
	glVertex3f(-0.65, -1, -0.2);
	glVertex3f(-0.65, -1, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.15);
	glVertex3f(-0.05, 0, -0.2);
	glVertex3f(-0.65, -1, -0.2);
	glVertex3f(-0.65, -1, -0.15);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.15);
	glVertex3f(0, 0, -0.15);
	glVertex3f(-0.45, -1, -0.15);
	glVertex3f(-0.65, -1, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.2);
	glVertex3f(0, 0, -0.2);
	glVertex3f(-0.45, -1, -0.2);
	glVertex3f(-0.65, -1, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, -0.15);
	glVertex3f(-0.05, 0, -0.2);
	glVertex3f(0, 0, -0.2);
	glVertex3f(0, 0, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.45, -1, -0.15);
	glVertex3f(-0.45, -1, -0.2);
	glVertex3f(-0.65, -1, -0.2);
	glVertex3f(-0.65, -1, -0.15);
	glEnd();

	//Amarre detras derecho
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.15);
	glVertex3f(0.05, 0, -0.15);
	glVertex3f(0.45, -1, -0.15);
	glVertex3f(0.25, -1, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.2);
	glVertex3f(0.05, 0, -0.2);
	glVertex3f(0.45, -1, -0.2);
	glVertex3f(0.25, -1, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.15);
	glVertex3f(0, 0, -0.2);
	glVertex3f(0.05, 0, -0.2);
	glVertex3f(0.05, 0, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.25, -1, -0.15);
	glVertex3f(0.25, -1, -0.2);
	glVertex3f(0.45, -1, -0.2);
	glVertex3f(0.45, -1, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.05, 0, -0.2);
	glVertex3f(0.05, 0, -0.15);
	glVertex3f(0.45, -1, -0.15);
	glVertex3f(0.45, -1, -0.2);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.15);
	glVertex3f(0.05, 0, -0.15);
	glVertex3f(0.45, -1, -0.15);
	glVertex3f(0.25, -1, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.2);
	glVertex3f(0.05, 0, -0.2);
	glVertex3f(0.45, -1, -0.2);
	glVertex3f(0.25, -1, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.15);
	glVertex3f(0, 0, -0.2);
	glVertex3f(0.05, 0, -0.2);
	glVertex3f(0.05, 0, -0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.25, -1, -0.15);
	glVertex3f(0.25, -1, -0.2);
	glVertex3f(0.45, -1, -0.2);
	glVertex3f(0.45, -1, -0.15);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -0.05);

	//Circulo sujecion radios y amarres
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, 0.3);
	glVertex3f(0.05, 0.07, 0.3); 
	glVertex3f(0.1, 0, 0.3); 
	glVertex3f(0.05, -0.07, 0.3); 
	glVertex3f(0, -0.1, 0.3); 
	glVertex3f(-0.05, -0.07, 0.3); 
	glVertex3f(-0.1, 0, 0.3); 
	glVertex3f(-0.05, 0.07, 0.3); 
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, -0.2);
	glVertex3f(0.05, 0.07, -0.2); 
	glVertex3f(0.1, 0, -0.2); 
	glVertex3f(0.05, -0.07, -0.2); 
	glVertex3f(0, -0.1, -0.2);
	glVertex3f(-0.05, -0.07, -0.2); 
	glVertex3f(-0.1, 0, -0.2); 
	glVertex3f(-0.05, 0.07, -0.2); 
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, 0.3); glVertex3f(0, 0.1, -0.2);
	glVertex3f(0.05, 0.07, 0.3); glVertex3f(0.05, 0.07, -0.2);
	glVertex3f(0.1, 0, 0.3); glVertex3f(0.1, 0, -0.2);
	glVertex3f(0.05, -0.07, 0.3); glVertex3f(0.05, -0.07, -0.2);
	glVertex3f(0, -0.1, 0.3); glVertex3f(0, -0.1, -0.2);
	glVertex3f(-0.05, -0.07, 0.3); glVertex3f(-0.05, -0.07, -0.2);
	glVertex3f(-0.1, 0, 0.3); glVertex3f(-0.1, 0, -0.2);
	glVertex3f(-0.05, 0.07, 0.3); glVertex3f(-0.05, 0.07, -0.2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, 0.3);
	glVertex3f(0.05, 0.07, 0.3);
	glVertex3f(0.1, 0, 0.3);
	glVertex3f(0.05, -0.07, 0.3);
	glVertex3f(0, -0.1, 0.3);
	glVertex3f(-0.05, -0.07, 0.3);
	glVertex3f(-0.1, 0, 0.3);
	glVertex3f(-0.05, 0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, -0.2);
	glVertex3f(0.05, 0.07, -0.2);
	glVertex3f(0.1, 0, -0.2);
	glVertex3f(0.05, -0.07, -0.2);
	glVertex3f(0, -0.1, -0.2);
	glVertex3f(-0.05, -0.07, -0.2);
	glVertex3f(-0.1, 0, -0.2);
	glVertex3f(-0.05, 0.07, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, 0.3); glVertex3f(0, 0.1, -0.2);
	glVertex3f(0.05, 0.07, -0.2); glVertex3f(0.05, 0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.1, 0.3); glVertex3f(0, 0.1, -0.2);
	glVertex3f(-0.05, 0.07, -0.2); glVertex3f(-0.05, 0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1, 0, 0.3); glVertex3f(0.1, 0, -0.2);
	glVertex3f(0.05, 0.07, -0.2); glVertex3f(0.05, 0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.1, 0, 0.3); glVertex3f(-0.1, 0, -0.2);
	glVertex3f(-0.05, -0.07, -0.2); glVertex3f(-0.05, -0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1, 0, 0.3); glVertex3f(0.1, 0, -0.2);
	glVertex3f(0.05, -0.07, -0.2); glVertex3f(0.05, -0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, -0.1, 0.3); glVertex3f(0, -0.1, -0.2);
	glVertex3f(-0.05, -0.07, -0.2); glVertex3f(-0.05, -0.07, 0.3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.1, 0, 0.3); glVertex3f(-0.1, 0, -0.2);
	glVertex3f(-0.05, 0.07, -0.2); glVertex3f(-0.05, 0.07, 0.3);
	glEnd();
	glPopMatrix();

	//Cesped
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-5, -1, 5);
	glVertex3f(-5, -1, -5);
	glVertex3f(5, -1, -5);
	glVertex3f(5, -1, 5);
	glEnd();
	glPopMatrix();
	
	
	glutSwapBuffers();

	FPS();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	float relacionAspecto = float(w) / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, relacionAspecto, 0.1, 100);
}

void onIdle()
{
	// Callback de atencion al evento idle
	static const float vueltasPorSegundo = 0.1;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	angulo += vueltasPorSegundo * 360 * (ahora - antes) / 1000;

	antes = ahora;

	glutPostRedisplay();

}

void onTimer(int tiempo)
{
	// Callback de atencion
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
	printf("No he conseguido hacer girar los asientos de la noria respecto a su amarre superior. Todas las estructuras están hechas punto a punto y señalizadas en el código mediante comentarios");
	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);
	// Bucle de atencion a eventos
	glutMainLoop();
}