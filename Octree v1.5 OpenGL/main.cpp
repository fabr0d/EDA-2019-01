#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include<GL/glut.h>
//#include <quadTree.h>
#define KEY_ESC 27
#include <cmath>
#include <vector>
#include <stdlib.h>
using namespace std;

double RandomFloat(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}
//--------------------------------OCTREE-------------------------------------------

struct Point{
	double x;
	double y;
	double z;
	Point(double _x, double _y, double _z){
		x = _x;
		y = _y;
		z = _z;
	}
	Point(){
		x = 0;
		y = 0;
		z = 0;
	}
};

void printPoint(Point p1) {
	cout << p1.x << "," << p1.y << "," << p1.z << endl;
}

void PuntoMedio(Point p1, Point p2) {
	Point temp;
	temp.x = (p1.x + p2.x) / 2;
	temp.y = (p1.y + p2.y) / 2;
	temp.z = (p1.z + p2.z) / 2;
	printPoint(temp);
}

//Objetos a almacenar en el octree
struct Node{
	Point pos;
	double data;
	Node(Point _pos, double _data){
		pos = _pos;
		data = _data;
	}
	Node(){
		data = 0;
	}
};

class Octree
{
public:
	bool status; // True partido False Intacto
	// Puntos limites del cubo
	Point PIIF; //Punto Inferior Izquierdo Frontal
	Point PSDP; //Punto Superior Derecho Posterior
	double ancho;
	//contiene un nodo
	Node *n;
	// Hijos del octree
	Octree *IIF;
	Octree *IDF;
	Octree *IIP;
	Octree *IDP;

	Octree *SIF;
	Octree *SDF;
	Octree *SIP;
	Octree *SDP;
	//contructor por default
	Octree(){
		PIIF = Point(0, 0, 0);
		PSDP = Point(0, 0, 0);
		n = NULL;

		IIF = NULL; //Cubo Inferior Izquierdo Frontal
		IDF = NULL; //Cubo Inferior Derecho Frontal
		IIP = NULL; //Cubo Inferior Izquierdo Posterior
		IDP = NULL; //Cubo Inferior Derecho Posterior

		SIF = NULL; //Cubo Superior Izquierdo Frontal
		SDF = NULL; //Cubo Superior Derecho Frontal
		SIP = NULL; //Cubo Superior Izquierdo Posterior
		SDP = NULL; //Cubo Superior Derecho Posterior

		ancho = 0.0;
	}
	Octree(Point PIIF_, Point PSDP_, double ancho_)
	{
		n = NULL;

		IIF = NULL; //Cubo Inferior Izquierdo Frontal
		IDF = NULL; //Cubo Inferior Derecho Frontal
		IIP = NULL; //Cubo Inferior Izquierdo Posterior
		IDP = NULL; //Cubo Inferior Derecho Posterior

		SIF = NULL; //Cubo Superior Izquierdo Frontal
		SDF = NULL; //Cubo Superior Derecho Frontal
		SIP = NULL; //Cubo Superior Izquierdo Posterior
		SDP = NULL; //Cubo Superior Derecho Posterior

		PIIF = PIIF_;
		PSDP = PSDP_;
		ancho = ancho_;
	}
	void insert(Node*);
	Node* search(Point);
	bool inBoundary(Point);
	void PrintOctree();
};

void Octree::insert(Node *node)
{
	//si el nodo a ingresar es nulo
	if (node == NULL ) {
		return;
	}

	//Esta dentro del cubo?
	if (!inBoundary(node->pos)) {
		return;
	}

	//Si n dentro del octree es nulo y no esta partido
	if (n == NULL &&
		IIF == NULL && IDF == NULL && IIP == NULL && IDP == NULL &&
		SIF == NULL && SDF == NULL && SIP == NULL && SDP == NULL) {
		n = node;
		//cout << "se inserto el punto: "; printPoint(n->pos);
		return;
	}
	else
	{
		if (n == NULL &&
			IIF != NULL && IDF != NULL && IIP != NULL && IDP != NULL &&
			SIF != NULL && SDF != NULL && SIP != NULL && SDP != NULL)
		{	//Si el cubo grande esta partido y no tienen nodos dentro el cubo grande
			IIF->insert(node);
			IDF->insert(node);
			IIP->insert(node);
			IDP->insert(node);
			SIF->insert(node);
			SDF->insert(node);
			SIP->insert(node);
			SDP->insert(node);
		}
		else //cuando encuentra un cubo que tien datos
		{
			vector<Node*> nodes;
			nodes.push_back(node);
			nodes.push_back(n);

			double p = ancho / 2;
			//cout << "anchodel nuevo cubo: " << ancho / 2 << endl;

			SDF = new Octree(Point(PIIF.x + p, PIIF.y + p, PIIF.z), Point(PIIF.x + 2 * p, PIIF.y + 2 * p, PIIF.z - p), ancho / 2);
			//cout << "Se creo un Cubo Superior Derecho Frontal" << endl;
			//cout << "limites :" << endl;
			//printPoint(SDF->PIIF);
			//printPoint(SDF->PSDP);
			//cout << "Punto medio : "; PuntoMedio(SDF->PIIF, SDF->PSDP);
			SDP = new Octree(Point((PSDP.x + PIIF.x) / 2, (PSDP.y + PIIF.y) / 2, (PSDP.z + PIIF.z) / 2), Point(PSDP.x, PSDP.y, PSDP.z), ancho / 2);
			//cout << "Se creo un Cubo Superior Derecho Posterior" << endl;
			//cout << "limites :" << endl;
			//printPoint(SDP->PIIF);
			//printPoint(SDP->PSDP);
			//cout << "Punto medio : "; PuntoMedio(SDP->PIIF, SDP->PSDP);
			IDF = new Octree(Point(PIIF.x + p, PIIF.y, PIIF.z), Point(PIIF.x + 2 * p, PIIF.y + p, PIIF.z - p), ancho / 2);
			//cout << "Se creo un Cubo Inferior Derecho Frontal" << endl;
			//cout << "limites :" << endl;
			//printPoint(IDF->PIIF);
			//printPoint(IDF->PSDP);
			//cout << "Punto medio : "; PuntoMedio(IDF->PIIF, IDF->PSDP);
			IDP = new Octree(Point(PIIF.x + p, PIIF.y, PIIF.z - p), Point(PIIF.x + 2 * p, PIIF.y + p, PIIF.z - 2 * p), ancho / 2);
			//cout << "Se creo un Cubo Inferior Derecho Posterior" << endl;
			//cout << "limites :" << endl;
			//printPoint(IDP->PIIF);
			//printPoint(IDP->PSDP);
			//cout << "Punto medio : "; PuntoMedio(IDP->PIIF, IDP->PSDP);
			SIF = new Octree(Point(PIIF.x, PIIF.y + p, PIIF.z), Point(PIIF.x + p, PIIF.y + 2 * p, PIIF.z - p), ancho / 2);
			//cout << "Se creo un Cubo Superior Izquierdo Frontal" << endl;
			//cout << "limites :" << endl;
			//printPoint(SIF->PIIF);
			//printPoint(SIF->PSDP);
			//cout << "Punto medio : "; PuntoMedio(SIF->PIIF, SIF->PSDP);
			SIP = new Octree(Point(PIIF.x, PIIF.y + p, PIIF.z - p), Point(PIIF.x + p, PIIF.y + 2 * p, PIIF.z - 2 * p), ancho / 2);
			//cout << "Se creo un Cubo Superior Izquierdo Posterior" << endl;
			//cout << "limites :" << endl;
			//printPoint(SIP->PIIF);
			//printPoint(SIP->PSDP);
			//cout << "Punto medio : "; PuntoMedio(SIP->PIIF, SIP->PSDP);
			IIF = new Octree(Point(PIIF.x, PIIF.y, PIIF.z), Point((PSDP.x + PIIF.x) / 2, (PSDP.y + PIIF.y) / 2, (PSDP.z + PIIF.z) / 2), ancho / 2);
			//cout << "Se creo un Cubo Inferior Izquierdo Frontal" << endl;
			//cout << "limites :" << endl;
			//printPoint(IIF->PIIF);
			//printPoint(IIF->PSDP);
			//cout << "Punto medio : "; PuntoMedio(IIF->PIIF, IIF->PSDP);
			IIP = new Octree(Point(PIIF.x, PIIF.y, PIIF.z - p), Point(PIIF.x + p, PIIF.y + p, PIIF.z - 2 * p), ancho / 2);
			//cout << "Se creo un Cubo Inferior Izquierdo Posterior" << endl;
			//cout << "limites :" << endl;
			//printPoint(IIP->PIIF);
			//printPoint(IIP->PSDP);
			//cout << "Punto medio : "; PuntoMedio(IIP->PIIF, IIP->PSDP);
			//cout << "------------------------------------------------" << endl;

			for (int i = 0; i < nodes.size(); i++)
			{
				if (nodes[i]->pos.x >= (PIIF.x + PSDP.x) / 2) // True = Derecho
				{
					if (nodes[i]->pos.y >= (PIIF.y + PSDP.y) / 2) // True = Superior
					{
						if (nodes[i]->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
						{
							//Cubo Superior Derecho Frontal
							SDF->insert(nodes[i]);
						}
						else // Posterior
						{
							//Cubo Superior Derecho Posterior
							SDP->insert(nodes[i]);
						}
					}
					else // Inferior
					{
						if (nodes[i]->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
						{
							//Cubo Inferior Derecho Frontal
							IDF->insert(nodes[i]);
						}
						else // Posterior
						{
							//Cubo Inferior Derecho Posterior
							IDP->insert(nodes[i]);
						}
					}
				}
				else // Izquierdo
				{
					if (nodes[i]->pos.y >= (PIIF.y + PSDP.y) / 2) // True = Superior
					{
						if (nodes[i]->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
						{
							//Cubo Superior Izquierdo Frontal
							SIF->insert(nodes[i]);
						}
						else // Posterior
						{
							//Cubo Superior Izquierdo Posterior
							SIP->insert(nodes[i]);
						}
					}
					else // Inferior
					{
						if (nodes[i]->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
						{
							//Cubo Inferior Izquierdo Frontal
							IIF->insert(nodes[i]);
						}
						else // Posterior
						{
							//Cubo Inferior Izquierdo Posterior
							IIP->insert(nodes[i]);
						}
					}
				}
			}
			//cout << "borro el punto: "; printPoint(n->pos);
			//cout << "del cubo: ";
			//printPoint(PIIF);
			//printPoint(PSDP);
			n = NULL;
		}
	}
}
// Busca un Punto en el octree
Node* Octree::search(Point p)
{
	//Comprobar si esta en el limite
	if (!inBoundary(p)) {
		return NULL;
	}
	if (n != NULL) {
		if (n->pos.x==p.x && n->pos.y == p.y && n->pos.z == p.z)
		{
			return n;
		}
	}
	//primero comprobar si esta arriba o abajo del cubo
	if (p.x >= (PIIF.x + PSDP.x) / 2) // True = Derecho
	{
		if (p.y >= (PIIF.y + PSDP.y) / 2) // True = Superior
		{
			if (p.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Superior Derecho Frontal
				if (SDF == NULL)
				{
					return NULL;
				}
				SDF->search(p);
			}
			else // Posterior
			{
				//Cubo Superior Derecho Posterior
				if (SDP == NULL)
				{
					return NULL;
				}
				SDP->search(p);
			}
		}
		else // Inferior
		{
			if (p.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Inferior Derecho Frontal
				if (IDF == NULL)
				{
					return NULL;
				}
				IDF->search(p);
			}
			else // Posterior
			{
				//Cubo Inferior Derecho Posterior
				if (IDP == NULL)
				{
					return NULL;
				}
				IDP->search(p);
			}
		}
	}
	else // Izquierdo
	{
		if (p.y >= (PIIF.y + PSDP.y) / 2) // True = Superior
		{
			if (p.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Superior Izquierdo Frontal
				if (SIF == NULL)
				{
					return NULL;
				}
				SIF->search(p);
			}
			else // Posterior
			{
				//Cubo Superior Izquierdo Posterior
				if (SIP == NULL)
				{
					return NULL;
				}
				SIP->search(p);
			}
		}
		else // Inferior
		{
			if (p.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Inferior Izquierdo Frontal
				if (IIF == NULL)
				{
					return NULL;
				}
				IIF->search(p);
			}
			else // Posterior
			{
				//Cubo Inferior Izquierdo Posterior
				if (IIP == NULL)
				{
					return NULL;
				}
				IIP->search(p);
			}
		}
	}


};

// Verifica que un punto este en una region
bool Octree::inBoundary(Point p)
{
	return (p.x >= PIIF.x && p.x <= PSDP.x &&
		p.y >= PIIF.y && p.y <= PSDP.y &&
		p.z <= PIIF.z && p.z >= PSDP.z);
}

void PrintOctree(Octree *octo)
{
	if (octo == NULL)
	{
		return;
	}

	if (octo->n == NULL &&
		octo->IIF == NULL && octo->IDF == NULL && octo->IIP == NULL && octo->IDP == NULL &&
		octo->SIF == NULL && octo->SDF == NULL && octo->SIP == NULL && octo->SDP == NULL)
	{
        glPushMatrix();
        glTranslatef((octo->PIIF.x+octo->PSDP.x)/2,(octo->PIIF.y+octo->PSDP.y)/2,(octo->PIIF.z+octo->PSDP.z)/2);	//punto medio del cubo
        glutSolidCube(octo->ancho);		//ancho del cubo
        glPopMatrix();
		//cout << "Punto PIIF de cubo: ";
		//printPoint(octo->PIIF);
		//cout << "Punto PSDP de cubo: ";
		//printPoint(octo->PSDP);
		//cout << "Ancho del Cubo: " << octo->ancho << endl;
		//cout << "---------------------------" << endl;
	}

	if (octo->n != NULL)
	{
	    glPushMatrix();
        glTranslatef((octo->PIIF.x+octo->PSDP.x)/2,(octo->PIIF.y+octo->PSDP.y)/2,(octo->PIIF.z+octo->PSDP.z)/2);	//punto medio del cubo
        glutSolidCube(octo->ancho);		//ancho del cubo
        glPopMatrix();

        glBegin(GL_POINTS);
            glColor3d(250,0,0); 		//color
            glPointSize(5.0);			//ancho del punto (no funca)
            glVertex3d(octo->n->pos.x,octo->n->pos.y,octo->n->pos.z);	//ubicacion del punto
        glEnd();

		//cout << "punto dentro de cubo :";
		//printPoint(octo->n->pos);
		//cout << "Punto PIIF de cubo: ";
		//printPoint(octo->PIIF);
		//cout << "Punto PSDP de cubo: ";
		//printPoint(octo->PSDP);
		//cout << "Ancho del Cubo: " << octo->ancho << endl;
	}
	if (octo->n == NULL && octo->IIF != NULL && octo->IDF != NULL && octo->IIP != NULL && octo->IDP != NULL &&
		octo->SIF != NULL && octo->SDF != NULL && octo->SIP != NULL && octo->SDP != NULL)
	{
        glPushMatrix();
        glTranslatef((octo->PIIF.x+octo->PSDP.x)/2,(octo->PIIF.y+octo->PSDP.y)/2,(octo->PIIF.z+octo->PSDP.z)/2);	//punto medio del cubo
        glutSolidCube(octo->ancho);		//ancho del cubo
        glPopMatrix();

		//cout << "Punto PIIF de cubo: ";
		//printPoint(octo->PIIF);
		//cout << "Punto PSDP de cubo: ";
		//printPoint(octo->PSDP);
		//cout << "Ancho del Cubo: " << octo->ancho << endl;
		PrintOctree(octo->SDF);
		PrintOctree(octo->SDP);
		PrintOctree(octo->IDF);
		PrintOctree(octo->IDP);
		PrintOctree(octo->SIF);
		PrintOctree(octo->SIP);
		PrintOctree(octo->IIF);
		PrintOctree(octo->IIP);
	}
}
//---------------------------------------------------------------------------------

int mx = 0;
int my = 0;

float ax=0.0;
float ay=0.0;
float speed = 0.1;

//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
        glColor3d(255,0,0);//x
        glVertex3d(-30, 0,0);
        glVertex3d(30, 0,0);
        glColor3d(0, 255, 0);//y
        glVertex3d(0, -30,0);
        glVertex3d(0, 30,0);
        glColor3d(0, 0, 255);//z
        glVertex3d(0, 0,-30);
        glVertex3d(0, 0,30);
	glEnd();
}
bool r = false;

void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mx=x;
    my=y;
  }else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    r = true;
  }else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
    r = false;
  }
}

void OnMouseMotion(int x, int y)
{
    int dx = mx-x;
    int dy = my-y;
    mx=x;
    my=y;
    ax += dx*speed;
    ay += dy*speed;
}



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	gluPerspective(60.0,1.0,3,500.0);

	glTranslatef(0,0,-100.0);
	glRotatef(ax,0,1,0);
	glRotatef(ay,1,0,0);

	displayGizmo();

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //glutSolidTeapot(7);

    //glTranslatef(20,20,0);
    //glutSolidCube(5);
	//dibujar quadTree (qt->draw())

	/*glPushMatrix();
	glTranslatef(0,0,0);
    glutSolidSphere(5,50,50);
    glPopMatrix();*/

    /*glPushMatrix();
	glTranslatef(0,1,0);
    glutSolidCube(5);
    glPopMatrix();
    */
    Octree oct1(Point(0, 0, 0), Point(50, 50, -50), 50);
/*
    for (int i=0; i<4; i++){
        int exc=RandomFloat(0.0,50.0);
        int yes=RandomFloat(0.0,50.0);
        int zta=RandomFloat(0.0,-50.0);
        double random_number=rand() % 100 + 1;
        Node temporal(Point(exc,yes,zta),random_number);
        printPoint(temporal.pos);
        //oct1.insert(&temporal);
    }*/
	Node a(Point(18, 11, -26.0), 10);
	Node b(Point(1, 1 ,-19.1), 20);
	Node c(Point(14, 2 ,-6.1), 30);
	Node d(Point(45, 16 ,-8), 40);
	Node e(Point(9, 19 ,-30.1), 50);
	//cout << "insert del punto: "; printPoint(a.pos);
	oct1.insert(&a);
	//cout << "insert del punto :"; printPoint(b.pos);
	oct1.insert(&b);
	oct1.insert(&c);
	oct1.insert(&d);
	oct1.insert(&e);
	//cout << "Node a: " << oct1.search(a.pos)->data << "\n";
	//cout << "Node b: " << oct1.search(b.pos)->data << "\n";
	//cout << "Node c: " << oct1.search(c.pos)->data << "\n";
	//cout << "Non-existing node: "
		//<< oct1.search(Point(5, 5, 5)); cout << "" << endl;
	//cout << "-------------------------------------------------------------" << endl;
	PrintOctree(&oct1);
	//dibuja el gizmo

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(255, 255, 255, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
    glEnable(GL_DEPTH_TEST);
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	default:
		break;
	}
}
//
//el programa principal
//
int main(int argc, char** argv) {
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Octree"); //titulo de la ventana
	init_GL(); //funcion de inicializacion de OpenGL
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);

    //Aca empieza el octree
	//qt = new quadTree();


	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}
