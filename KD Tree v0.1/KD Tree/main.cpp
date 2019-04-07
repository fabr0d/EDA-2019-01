#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

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
		cout << "el numero de puntos en la lista es :" << pts.size() << endl;
		if (pts.size() <= maxPoints)
		{
			cout << "es menor o igual al permitido, se inserta" << endl;
			printListOfPoints(pts);
			Points = pts;
			return;
		}
		else
		{
			cout << "el numero de puntos es mayor" << endl;
			vector<Point> PuntosLadoIzq;
			vector<Point> PuntosLadoDer;
			midval = getmidval(pts, axis);	//toma el valor medio del eje
			cout << "el valor medio del eje " << axis << " es: " << midval << endl;
			cout << "comienza la division de la lista en 2" << endl;
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
			cout << "2 listas divididas" << endl;
			cout << "lista de la izquierda" << endl;
			printListOfPoints(PuntosLadoIzq);
			cout << "lista de la derecha" << endl;
			printListOfPoints(PuntosLadoDer);
			//PuntosLadoDer y PuntosLadoIzq
			if (axis==0)
			{
				cout << "se crea los 2 hijos con el axis 1" << endl;
				left = new kdtree(1);
				right = new kdtree(1);
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
			if (axis == 1)
			{
				cout << "se crea los 2 hijos con el axis 2" << endl;
				left = new kdtree(2);
				right = new kdtree(2);
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
			if (axis == 2)
			{
				cout << "se crea los 2 hijos con el axis 0" << endl;
				left = new kdtree(0);
				right = new kdtree(0);
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
		}
	}

	void searchPointInReg();
	
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

int main()
{
	vector<Point> PuntosRandom;
	for (int i = 0; i < 10; i++)
	{
		PuntosRandom.push_back(Point(rand() % 20 + 1, rand() % 20 + 1, rand() % 20 + 1));
	}
	printListOfPoints(PuntosRandom); cout << "" << endl;
	kdtree kd1(0);
	kd1.insert(PuntosRandom);
	cout << "--------------------inicio de la impresion del kdtree-------------------" << endl;
	printKDTree(&kd1);
	getchar();
	return 0;
}