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
	Point PIIF; //Punto Inferior Izquierdo Frontal
	Point PSDP; //Punto Superior Derecho Posterior
	int axis; // puede ser x, y o z
	double midval; // segun el axis
	vector<Point> Points; // puntos almacenados en un octree
	kdtree *left;
	kdtree *right;
	kdtree() 
	{
		PIIF = Point(0, 0, 0);
		PSDP = Point(0, 0, 0);

		midval = 0;
		axis = 0;
		left = NULL;
		right = NULL;
	}

	kdtree(int _axis, Point PIIF_, Point PSDP_)
	{
		PIIF = PIIF_;
		PSDP = PSDP_;
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
				left = new kdtree(1, Point(PIIF.x, PIIF.y, PIIF.z), Point(midval, PSDP.y, PSDP.z));
				right = new kdtree(1, Point(midval, PIIF.y, PIIF.z), Point(PSDP.x, PSDP.y, PSDP.z));
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
			if (axis == 1)
			{
				cout << "se crea los 2 hijos con el axis 2" << endl;
				left = new kdtree(2, Point(PIIF.x, PIIF.y, PIIF.z), Point(PSDP.x, midval, PSDP.z));
				right = new kdtree(2, Point(PIIF.x, midval, PIIF.z), Point(PSDP.x, PSDP.y, PSDP.z));
				left->insert(PuntosLadoIzq);
				right->insert(PuntosLadoDer);
			}
			if (axis == 2)
			{
				cout << "se crea los 2 hijos con el axis 0" << endl;
				left = new kdtree(0, Point(PIIF.x, PIIF.y, midval), Point(PSDP.x, PSDP.y, PSDP.z));
				right = new kdtree(0, Point(PIIF.x, PIIF.y, PIIF.z), Point(PSDP.x, PSDP.y, midval));
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
	if (kd->left == NULL && kd->right == NULL)//Llegamos a un nodo hoja sin hijos se imprime sus hijos
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

void printKDtree3D(kdtree *kd) {
	if (kd == NULL)
	{
		return;
	}
	if (kd->left == NULL && kd->right == NULL)//Llegamos a un nodo hoja sin hijos se imprime sus hijos
	{
		printListOfPoints(kd->Points);
		return;
	}
	if (kd->Points.size() == 0 && kd->left != NULL && kd->right != NULL) //llegamos a una figura que se dividio a partir de un eje
	{
		if (kd->axis == 0)
		{
			//Linea 1
			Point one(kd->midval, kd->PIIF.y, kd->PIIF.z);
			Point two(kd->midval, kd->PSDP.y, kd->PIIF.z);
			//Linea 2
			Point three(kd->midval, kd->PSDP.y, kd->PIIF.z);
			Point four(kd->midval, kd->PSDP.y, kd->PSDP.z);
			//Linea 3
			Point five(kd->midval, kd->PSDP.y, kd->PSDP.z);
			Point six(kd->midval, kd->PIIF.y, kd->PSDP.z);
			//Linea 4
			Point seven(kd->midval, kd->PIIF.y, kd->PSDP.z);
			Point eight(kd->midval, kd->PIIF.y, kd->PIIF.z);

			printKDtree3D(kd->left);
			printKDtree3D(kd->right);
		}
		if (kd->axis == 1)
		{
			//Linea 1
			Point one(kd->PIIF.x, kd->midval, kd->PIIF.z);
			Point two(kd->PSDP.x, kd->midval, kd->PIIF.z);
			//Linea 2
			Point three(kd->PSDP.x, kd->midval, kd->PIIF.z);
			Point four(kd->PSDP.x, kd->midval, kd->PSDP.z);
			//Linea 3
			Point five(kd->PSDP.x, kd->midval, kd->PSDP.z);
			Point six(kd->PIIF.x, kd->midval, kd->PSDP.z);
			//Linea 4
			Point seven(kd->PIIF.x, kd->midval, kd->PSDP.z);
			Point eight(kd->PIIF.x, kd->midval, kd->PIIF.z);

			printKDtree3D(kd->left);
			printKDtree3D(kd->right);
		}
		if (kd->axis == 2)
		{
			//Linea 1
			Point one(kd->PIIF.x, kd->PSDP.y, kd->midval);
			Point two(kd->PSDP.x, kd->PSDP.y, kd->midval);
			//Linea 2
			Point three(kd->PSDP.x, kd->PSDP.y, kd->midval);
			Point four(kd->PSDP.x, kd->PIIF.y, kd->midval);
			//Linea 3
			Point five(kd->PSDP.x, kd->PIIF.y, kd->midval);
			Point six(kd->PIIF.x, kd->PIIF.y, kd->midval);
			//Linea 4
			Point seven(kd->PIIF.x, kd->PIIF.y, kd->midval);
			Point eight(kd->PIIF.x, kd->PSDP.y, kd->midval);

			printKDtree3D(kd->left);
			printKDtree3D(kd->right);
		}
	}

}

int main()
{
	vector<Point> PuntosRandom;
	for (int i = 0; i < 50; i++)
	{
		PuntosRandom.push_back(Point(rand() % 100 + 1, rand() % 100 + 1, 0-(rand() % 100 + 1)));
	}
	printListOfPoints(PuntosRandom); cout << "" << endl;
	kdtree kd1(0,Point(0,0,0),Point(100,100,-100));
	kd1.insert(PuntosRandom);
	cout << "--------------------inicio de la impresion del kdtree-------------------" << endl;
	printKDTree(&kd1);
	cout << "*****************************************************************************" << endl;
	double equis=1;
	double yegrigega=2;
	double zeta=3;

	kd1.searchPointInReg(equis, yegrigega, zeta);
	getchar();
	return 0;
}