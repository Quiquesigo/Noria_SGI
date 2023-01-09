/*!
	Interaccion.cpp
	Programa capturar eventos de usuario y modificar el
	grafico en consecuencia
	@author		Roberto Vivo' <rvivo@upv.es>
	@date		Nov,2022
 */

#define PROYECTO "ISGI::S6E01::Interaccion"

#include <iostream>			
#include <Utilidades.h>
#include <GL/freeglut.h>
#include <freeimage/FreeImage.h> 
#include <iostream>
#include <sstream>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <math.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <Utilidades.h>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;

using namespace std;

GLfloat v0[3] = { 50,50,0 }, v1[3] = { 0,50,0 }, v2[3] = { 0,0,0 }, v3[3] = { 50,0,0 }; //terreno basico
GLfloat v4[3] = { 0,0,0 }, v5[3] = { 0,-2,0 }, v6[3] = { 50,-2,0 }, v7[3] = { 50,0,0 }; //carretera
GLfloat v12[3] = { 50,-50,0 }, v13[3] = { 60,-50,-5 }, v14[3] = { 60,-5,-5 }, v15[3] = { 50,0,0 }; //bajada al lago
GLfloat v16[3] = { 90,-50,-5 }, v17[3] = { 60,-50,-5 }, v18[3] = { 60,-5,-5 }, v19[3] = { 90,-5,-5 }; //lago
GLfloat v20[3] = { 90,-50,-5 }, v21[3] = { 100,-50,0 }, v22[3] = { 100,0,0 }, v23[3] = { 90,-5,-5 }; //subida del lago
GLfloat v32[3] = { 100,0,0 }, v33[3] = { 50,0,0 }, v34[3] = { 60,-5,-5 }, v35[3] = { 90,-5,-5 }; //pared del lago
GLfloat v8[3] = { 0,40,0 }, v9[3] = { -5,35,-1 }, v10[3] = { -10,40,0 }, v11[3] = { -5,40,10 }; //montaña
GLfloat v24[3] = { 2,25,0 }, v25[3] = { 2.2,25,0 }, v26[3] = { 2.2,25,0.5 }, v27[3] = { 2,25,0.5 }; //tronco arbol
GLfloat v28[3] = { 1.5,25,0.5 }, v29[3] = { 2.7,25,0.5 }, v30[3] = { 2.7,25,1.2 }, v31[3] = { 1.5,25,1.2 }; //copa arbol

// Variables para la posición de la cámara
float cameraX = 0;
float cameraY = 0;
float cameraZ = 3;
float varcameraY = 3;

// Variables para el punto de vista de la cámara
float lookX = 1200;
float lookY = 0;
float lookZ = 0;

// Variables para la orientación de la cámara
float upX = 0;
float upY = 0;
float upZ = 1;

float vel = 0;
float angx = 1.0;

int nMonv = 9;
int nMonh = 60;

float num;
float num2;
int j;

int lastx, lasty;
int hori, vert;

//static enum Horario {Noche, Dia} hora;
bool dia = false;
bool lint = true;

GLfloat fogColor[] = { 0.6, 0.6, 0.6, 0.1 };
GLfloat luzB[] = { 0.4,0.4,0.4, 1.0 };
GLfloat Em[] = { 0.0,0.0,0.0,1.0 };
GLfloat Am[] = { 1.0,0.0,0.2,1.0 };
GLfloat Dm[] = { 0.8,0.8,0.8 };
GLfloat Sm[] = { 0.8,0.8,0.8 };
GLfloat s = 3.0;
GLfloat posicion1[] = { 0,0,3,1 };
GLfloat dir_central1[] = { 0,-1,-5 };
const GLfloat blanco[] = { 1,1,1,1 };
const GLfloat negro[] = { 0,0,0,1 };
GLfloat colorito[] = {0,0,0,1};
GLuint tex[10];

void loadImageFile(const char* nombre)
// Uso de FreeImage para cargar la imagen en cualquier formato
// nombre: nombre del fichero con extensión en el mismo directorio que el proyecto
// o con su path completo
{
	// Detección del formato, lectura y conversion a BGRA

	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(nombre, 0);
	FIBITMAP* imagen = FreeImage_Load(formato, nombre);
	FIBITMAP* imagen32b = FreeImage_ConvertTo32Bits(imagen);
	// Lectura de dimensiones y colores
	int w = FreeImage_GetWidth(imagen32b);
	int h = FreeImage_GetHeight(imagen32b);
	GLubyte* texeles = FreeImage_GetBits(imagen32b);
	// Carga como textura actual
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, texeles);
	// Liberar recursos
	FreeImage_Unload(imagen);
	FreeImage_Unload(imagen32b);
}

void loadTexture()
// Funcion de carga de texturas e inicializacion
{
	glGenTextures(10, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	loadImageFile("campo.jpg");

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	loadImageFile("montaña.jpg");

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	loadImageFile("suelo.jpg");

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	loadImageFile("agua.jpg");

	glBindTexture(GL_TEXTURE_2D, tex[4]);
	loadImageFile("cabina.png");

	glBindTexture(GL_TEXTURE_2D, tex[5]);
	loadImageFile("cielo.png");

	glBindTexture(GL_TEXTURE_2D, tex[7]);
	loadImageFile("carretera.jpg");

	glBindTexture(GL_TEXTURE_2D, tex[8]);
	loadImageFile("copa.png");

	glBindTexture(GL_TEXTURE_2D, tex[9]);
	loadImageFile("tronco.jpg");

	glBindTexture(GL_TEXTURE_2D, tex[6]);
	loadImageFile("campo1.jpg");

	glEnable(GL_TEXTURE_2D);
}

void modo_Hora() {
	if (dia == true) {
		glClearColor(0.6, 0.6, 0.6, 1.0);
		glEnable(GL_FOG);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	if(dia == false) {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glDisable(GL_FOG);
		glEnable(GL_LIGHT1);
		if (lint == true) {
			glEnable(GL_LIGHT0);
		}
		else { glDisable(GL_LIGHT0); }
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glutPostRedisplay();
}

char cambio(int x) {
	char y = (char)x;
	return y;
}

void control_hud() {
	float v0[3] = { -1,-1,0 };
	float v1[3] = { 1,-1,0 };
	float v2[3] = { 1,1.1,0 };
	float v3[3] = { -1,1.1,0 };

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	quadtex(v0, v1, v2, v3);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	glDisable(GL_BLEND);
}

void crear_indicadores() {
	if (dia == false) { 
		colorito[0] = { 1 }; 
		colorito[1] = { 1 };
		colorito[2] = { 1 };
	}
	else {
		colorito[0] = { 0 }; 
		colorito[1] = { 0 };
		colorito[2] = { 0 };
	}
	texto(1, 100, (char*)"Velocidad: ", colorito, GLUT_BITMAP_HELVETICA_18, false);
	stringstream aux;
	aux << vel*1000 << " km/h";
	texto(95, 100, (char*)aux.str().c_str(), colorito, GLUT_BITMAP_HELVETICA_18, false);

	texto(1,80, (char*)"Altitud: ", colorito, GLUT_BITMAP_HELVETICA_18, false);
	stringstream aux1;
	aux1 << cameraZ*10 << " m";
	texto(60, 80, (char*)aux1.str().c_str(), colorito, GLUT_BITMAP_HELVETICA_18, false);

	texto(1, 40, (char*)"Cabezada vertical: ", colorito, GLUT_BITMAP_HELVETICA_18, false);
	stringstream aux2;
	aux2 << -vert << " grados";
	texto(155, 40, (char*)aux2.str().c_str(), colorito, GLUT_BITMAP_HELVETICA_18, false);

	texto(1, 20, (char*)"Cabezada horizontal: ", colorito, GLUT_BITMAP_HELVETICA_18, false);
	stringstream aux3;
	aux3 << hori << " grados";
	texto(175, 20, (char*)aux3.str().c_str(), colorito, GLUT_BITMAP_HELVETICA_18, false);

	texto(1, 60, (char*)"Localización (x,y): ", colorito, GLUT_BITMAP_HELVETICA_18, false);
	stringstream aux4;
	aux4 << "(" << cameraX << ", " << cameraY << ")";
	texto(140, 60, (char*)aux4.str().c_str(), colorito, GLUT_BITMAP_HELVETICA_18, false);

}

void moverluzder() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	posicion1[0] += -1.8;
	glLightfv(GL_LIGHT1, GL_POSITION, posicion1);
	glPopMatrix();
}

void moverluzizq() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	posicion1[0] += 1.8;
	glLightfv(GL_LIGHT1, GL_POSITION, posicion1);
	glPopMatrix();
}

void crear_arbol() {
	
}

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	// Inicializaciones 
	glClearColor(0.6, 0.6, 0.6, 1.0);
	//hora = Dia;
	glDisable(GL_FOG);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzB);

	//glMaterialfv(GL_BACK, GL_EMISSION, Em);
	//glMaterialfv(GL_BACK, GL_AMBIENT, Am);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Dm);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Sm);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);
	GLfloat Al0[] = { 0.2,0.2,0.2,1.0 }; // Color ambiental de la luz
	GLfloat Dl0[] = { 1.0,1.0,1.0,1.0 }; // Color difuso de la luz
	GLfloat Sl0[] = { 1.0,1.0,1.0,1.0 }; // Color especular de la luz
	GLfloat Al1[] = { 0.2,0.2,0.2,1.0 }; // Color ambiental de la luz
	GLfloat Dl1[] = { 1.0,1.0,0,1.0 }; // Color difuso de la luz
	GLfloat Sl1[] = { 1.0,1.0,0,1.0 }; // Color especular de la luz
	GLfloat posicion[] = { cameraX,cameraY,cameraZ,1 };
	GLfloat dir_central[] = { 0,0,-1 };

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0); // Caracteristicas de LIGHT0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir_central);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1000.0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Al1); // Caracteristicas de LIGHT1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Dl1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Sl1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicion1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1000.0);
	modo_Hora();
	loadTexture();

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);
	//control_hud();
	glPopAttrib();
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	if (dia == false) {
		glBindTexture(GL_TEXTURE_2D, tex[5]);
		texturarFondo();
	}
	// Seleccionar la MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(hori, 0, 1, 0);
	glRotatef(vert, 1, 0, 0);
	gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, upX, upY, upZ);
	ejes();

	// Geometria
	glColor3f(1,1,1);
	glPolygonMode(GL_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quad(v0, v1, v2, v3);

	glPushMatrix();
	glTranslatef(-50, 0, 0);
	quad(v0, v1, v2, v3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, -50, 0);
	quad(v0, v1, v2, v3);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	if(dia == true){ glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	glPushMatrix();

	for (int k = 0; k < 4; k++) {
		glTranslatef(50, 0, 0);
		quadtex(v0, v1, v2, v3);

	}		
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	glPushMatrix();
	glTranslatef(0, -52, 0);
	quadtex(v0, v1, v2, v3);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v8, v9, v10, v11);
	glPushMatrix();
	for (int i = 0; i < nMonh; i++) {
		glTranslatef(4, 0, 0);
		quadtex(v8, v9, v10, v11);
	}
	glPopMatrix();
	glPushMatrix();
	for (int i = 0; i < nMonv; i++) {
		glTranslatef(0, -4, 0);
		quadtex(v8, v9, v10, v11);
	}
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v12, v13, v14, v15);

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v32, v33, v34, v35);

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v16, v17, v18, v19);

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v20, v21, v22, v23);

	glBindTexture(GL_TEXTURE_2D, tex[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v4, v5, v6, v7);

	glPushMatrix();
	glTranslatef(200, 0, 0);
	quadtex(v4, v5, v6, v7);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v24, v25, v26, v27);
	for (int j= 0; j < 30; j++) {
		
		glTranslatef(2, -0.4, 0);
		glBindTexture(GL_TEXTURE_2D, tex[9]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
		else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
		quadtex(v24, v25, v26, v27);
		glBindTexture(GL_TEXTURE_2D, tex[8]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
		else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
		quadtex(v28, v29, v30, v31);
	}

	for (int j = 0; j < 30; j++) {

		glTranslatef(2, 0.4, 0);
		glBindTexture(GL_TEXTURE_2D, tex[9]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
		else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
		quadtex(v24, v25, v26, v27);
		glBindTexture(GL_TEXTURE_2D, tex[8]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
		else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
		quadtex(v28, v29, v30, v31);
	}
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	if (dia == true) { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); }
	else { glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); }
	quadtex(v28, v29, v30, v31);


	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 60.0);

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-hori, 0, -1, 0);
	glRotatef(-vert, -1, 0, 0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central1);
	glPopMatrix();

	crear_indicadores();
	crear_arbol();

	//control_hud();

	//glPopMatrix();

	/*glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glColor4f(1.0, 0.0, 0.0,0.0);
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPushMatrix();
	glRotatef(-hori, 0, -1, 0);
	glRotatef(-vert, -1, 0, 0);
	glutSolidSphere(1,10,10);
	glPopMatrix();*/
	

	glutSwapBuffers();
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

void onKey(unsigned char tecla, int x, int y)
{
	// Callback de atencion a los eventos de teclas alfanumericas
	switch (tecla) {
	case 'S':
	case 's':
		if (cameraZ > 0.01) {
			cameraZ -= 0.01;
		}
		break;
	case 'W':
	case 'w':
		cameraZ += 0.01;
		break;
	case 'A':
	case 'a':
		vel += 0.01;
		break;
	case 'Z':
	case 'z':
		if (vel > 0) {
			vel -= 0.01;
		}
		break;
	case 'Q':
	case 'q':
		dia = !dia;
		modo_Hora();
		break;
	case 'L':
	case 'l':
		lint = !lint;
		modo_Hora();
		break;
	case 'c':
		if (angx >= 0) {
			angx -= 0.05;
			moverluzder();
		}
		printf("%f",angx);
		break;
	case 'v':
		angx += 0.05;
		moverluzizq();
		break;
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
	switch (key)
	{
	case 27: // Tecla 'ESC'
		exit(0);
		break;
	case GLUT_KEY_UP: // Tecla de flecha hacia arriba
		cameraY += 0.1;
		break;
	case GLUT_KEY_DOWN: // Tecla de flecha hacia abajo
		cameraY -= 0.1;
		break;
	}
}

void mouseMove(int x, int y)
{
	
		int dx = x - lastx;
		int dy = y - lasty;

		hori += dx * 0.2;
		vert += dy * 0.2;

		lastx = x;
		lasty = y;
	
		if (vert > 90) vert = 90;
		if (vert < -45) vert = -45;
		if (hori > 90) hori = 90;
		if (hori < -90) hori = -90;
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		lastx = x;
		lasty = y;
	}
}

void onIdle() 
{
	float angy = 1 - angx;
	if (angx > 1 && angy>= -1) { cameraX += vel; cameraY += vel * angy; }
	if (angx > 1 && angy <= -1) { cameraY += -vel; printf("%f", vel); }
	else {
		cameraX += vel * angx;
		cameraY += vel * angy;
		if (vel < 0) { vel = 0; }
		if (angx < 0) { angx = 0; }
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(onKey);
	glutIdleFunc(onIdle);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutSpecialFunc(keyboard);

	// Bucle de atencion a eventos
	glutMainLoop();
	FreeImage_DeInitialise();
}