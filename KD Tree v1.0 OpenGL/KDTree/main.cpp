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
#include <fstream>
#include <algorithm>
using namespace std;
//Octree oct1(Point(0, 0, 0), Point(50, 50, -50), 50);
double RandomFloat(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}
//--------------------------------KD Tree-------------------------------------------
const int k = 3; //dimensiones
const int maxPoints = 2;

void printVector(vector<double> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << ", ";
	}
	cout << "" << endl;
}

struct Point {
	double x;
	double y;
	double z;
	Point(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	Point() {
		x = 0;
		y = 0;
		z = 0;
	}
};

void printPoint(Point p1) {
	cout << "[" << p1.x << "," << p1.y << "," << p1.z << "]";
}

//	0 = x
//	1 = y
//	2 = z

double getmidval(vector<Point> points,int axis) {
	vector<double> tempo;
	for (int i = 0; i < points.size(); i++)
	{
		if (axis == 0)
		{
			tempo.push_back(points[i].x);
		}
		if (axis == 1)
		{
			tempo.push_back(points[i].y);
		}
		if (axis == 2)
		{
			tempo.push_back(points[i].z);
		}
	}
	sort(tempo.begin(), tempo.end());
	//printVector(tempo);
	if (tempo.size() % 2 == 0) // si es par // (numero de datos / 2) - 1 = posicion en lista
	{
		//cout << "pos mid: " << (tempo.size() / 2) - 1 << endl;
		return tempo[(tempo.size() / 2) - 1];
	}
	else	//es impar // (numero de datos - 1) / 2 = posicion en lista
	{
		//cout << "pos mid: " << (tempo.size() - 1) / 2 << endl;
		return tempo[(tempo.size() - 1) / 2];
	}
}

void printListOfPoints(vector<Point> lista) {
	for (int i = 0; i < lista.size(); i++)
	{
		printPoint(lista[i]);cout<< ", ";
	}
	cout << "" << endl;
}

class kdtree
{
public:
	int axis; // puede ser x, y o z
	double midval; // segun el axis
	vector<Point> Points; // puntos almacenados en un octree
	kdtree *left;
	kdtree *right;
	kdtree()
	{
		midval = 0;
		axis = 0;
		left = NULL;
		right = NULL;
	}

	kdtree(int _axis)
	{
		//midval = _midval;
		axis = _axis;
		left = NULL;
		right = NULL;
	}

	void insert(vector<Point> pts)
	{
		//cout << "el numero de puntos en la lista es :" << pts.size() << endl;
		if (pts.size() <= maxPoints)
		{
			//cout << "es menor o igual al permitido, se inserta" << endl;
			//printListOfPoints(pts);
			Points = pts;
			return;
		}
		else
		{
			//cout << "el numero de puntos es mayor" << endl;
			vector<Point> PuntosLadoIzq;
			vector<Point> PuntosLadoDer;
			midval = getmidval(pts, axis);	//toma el valor medio del eje
			//cout << "el valor medio del eje " << axis << " es: " << midval << endl;
			//cout << "comienza la division de la lista en 2" << endl;
			for (int i = 0; i < pts.size(); i++)
			{
				if (axis == 0) // Eje x
				{
					if (pts[i].x >= midval) //puntos a la derecha seran mayores iguales al medio
					{
						PuntosLadoDer.push_back(pts[i]);
					}
					else //puntos menores al medio que van a la izquierda
					{
						PuntosLadoIzq.push_back(pts[i]);
					}
				}
				if (axis == 1) // Eje y
				{
					if (pts[i].y >= midval) //puntos a la derecha seran mayores iguales al medio
					{
						PuntosLadoDer.push_back(pts[i]);
					}
					else //puntos menores al medio que van a la izquierda
					{
						PuntosLadoIzq.push_back(pts[i]);
					}
				}
				if (axis == 2) // Eje z
				{
					if (pts[i].z >= midval) //puntos a la derecha seran mayores iguales al medio
					{
						PuntosLadoDer.push_back(pts[i]);
					}
					else //puntos menores al medio que van a la izquierda
					{
						PuntosLadoIzq.push_back(pts[i]);
					}
				}
			}
			//ya tengo partida en 2 la lista de puntos dependiendo del eje
			//cout << "2 listas divididas" << endl;
			//cout << "lista de la izquierda" << endl;
			//printListOfPoints(PuntosLadoIzq);
			//cout << "lista de la derecha" << endl;
			//printListOfPoints(PuntosLadoDer);
			//PuntosLadoDer y PuntosLadoIzq
			if (axis==0)
			{
				//cout << "se crea los 2 hijos con el axis 1" << endl;
				left = new kdtree(1);
				right = new kdtree(1);
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
			if (axis == 1)
			{
				//cout << "se crea los 2 hijos con el axis 2" << endl;
				left = new kdtree(2);
				right = new kdtree(2);
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
			if (axis == 2)
			{
				//cout << "se crea los 2 hijos con el axis 0" << endl;
				left = new kdtree(0);
				right = new kdtree(0);
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
		}
	}

	void searchPointInReg(double exs, double ye, double ze)
	{
		if (Points.size()>0 && left==NULL && right==NULL)
		{
			printListOfPoints(Points);
			return;
		}
		if (Points.size() == 0 && left == NULL && right == NULL)
		{
			return;
		}
		if (axis == 0)
		{
			if (exs < midval)
			{
				left->searchPointInReg(exs, ye, ze);
			}
			else
			{
				right->searchPointInReg(exs, ye, ze);
			}
		}
		if (axis == 1)
		{
			if (ye < midval)
			{
				left->searchPointInReg(exs, ye, ze);
			}
			else
			{
				right->searchPointInReg(exs, ye, ze);
			}
		}
		if (axis == 2)
		{
			if (ze < midval)
			{
				left->searchPointInReg(exs, ye, ze);
			}
			else
			{
				right->searchPointInReg(exs, ye, ze);
			}
		}
	}
};

void printKDTree(kdtree *kd) {
	if (kd == NULL)
	{
		return;
	}
	if (kd->left == NULL && kd->right == NULL)
	{
		cout << "llegamos a una hoja sin hijos" << endl;
		cout << "Axis: " << kd->axis << endl;
		cout << "Imprimimos sus puntos: " << endl;
		printListOfPoints(kd->Points);
		cout << "----------------------------------------------" << endl;
		return;
	}
	cout << "nodo con hijos" << endl;
	cout << "Axis: " << kd->axis << endl;
	cout << "Valor medio segun axis: " << kd->midval << endl;
	cout << "voy hijo izquierdo" << endl;
	printKDTree(kd->left);
	cout << "voy hijo derecho" << endl;
	printKDTree(kd->right);
	cout << "--------------------------------------------------" << endl;
}

void printKDtree3D(kdtree *kd, Point p1, Point p2, int axis){
    if(){

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
Octree oct1(Point(-1, -1, 1), Point(1, 1, -1), 2);
void glPaint(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	gluPerspective(20.0,1,0.5,500.0);
	glTranslatef(0,0,-100.0);
	glRotatef(ax,0,1,0);
	glRotatef(ay,1,0,0);

	displayGizmo();

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	PrintKDtree(&kd3);

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

//en el caso que la ventana cambie de tama�o
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
    double equis;
    double ye;
    double zeta;
    vector<string> pointsList;
    ifstream bunny("C:\\Users\\Fab\\Documents\\GitHub\\EDA-2019-01\\Octree v1.5 OpenGL Points\\OctreeP\\bunny.txt");
    cout<<bunny.is_open()<<endl;
    while(bunny>>equis>>ye>>zeta){
            oct1.insert(Point(equis,ye,zeta));
    }

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700); //tama�o de la ventana
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