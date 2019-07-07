#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <math.h>
#include <cmath>
#include <GL/glut.h>
#include <vector>
#include <fstream>

#define KEY_ESC 27
#define KEY_UP_Y 87		//W
#define KEY_DOWN_Y 83	//S
#define KEY_RIGHT_X 65	//A
#define KEY_LEFT_X 68	//D

using namespace std;

unsigned n_dimensions = 2;
int PPR = 5;

template < class T>
class CPoint //punto bi dimensional
{
public:
	vector<T> coord; //vector almacena los datos

	CPoint(vector<T> a) //constructor para  dimensiones pasando el objeto con n dimensiones como un vector
	{
		coord = a;
	}
	CPoint(T x, T y) //constructor para dos dimensiones
	{
		coord.push_back(x);
		coord.push_back(y);
	}
	CPoint() {} 

	template<class U>friend ostream& operator<<(ostream& os, const CPoint<T>& cp)
	{
		os << " ( ";
		for (int i = 0; i < cp.coord.size(); i++)
			os << cp.coord[i] << ",";
		os << ")";
		return os;
	}
private:
};

template<class T>
class CMbr //rectangulo que almacena puntos
{
public:
	CPoint<T> cmbr_esq[2]; // puntos extremos del rectangulo

	CMbr(CPoint<T> e1, CPoint<T> e2) //constructor
	{
		cmbr_esq[0] = e1;
		cmbr_esq[1] = e2;
	}
	CMbr() {}

	bool contiene(CPoint<T> x) //verifica si el rectangulo contiene a un punto
	{
		T min, max;
		for (int i = 0; i < cmbr_esq[0].coord.size(); i++)
		{
			if (cmbr_esq[0].coord[i] < cmbr_esq[1].coord[i])
			{
				min = cmbr_esq[0].coord[i];
				max = cmbr_esq[1].coord[i];
			}
			else
			{
				min = cmbr_esq[1].coord[i];
				max = cmbr_esq[0].coord[i];
			}
			if (x.coord[i] < min or x.coord[i] > max)
			{
				return false;
			}
		}
		return true;
	}

	double calc_area() //calcula el area
	{
		double result = 1;
		for (int i = 0; i < cmbr_esq[0].coord.size(); i++)
		{
			result *= abs(cmbr_esq[0].coord[i] - cmbr_esq[1].coord[i]);
		}
		return result;
	}

	double calc_enlargement(CPoint<T> x) //calcula cuanto se alarga un rectangulo con un punto dado
	{
		CMbr<T> rect_enlargement = *this;
		T* min, * max;
		if (contiene(x))
		{
			return 0;
		}
		for (int i = 0; i < cmbr_esq[0].coord.size(); i++) //min.coord.size() esto lleva el numero de coordenadas que es la dimension
		{
			//primero identifico el minimo y el maximo de la dimension i
			if (rect_enlargement.cmbr_esq[0].coord[i] < rect_enlargement.cmbr_esq[1].coord[i])
			{
				min = &rect_enlargement.cmbr_esq[0].coord[i];
				max = &rect_enlargement.cmbr_esq[1].coord[i];
			}
			else
			{
				min = &rect_enlargement.cmbr_esq[1].coord[i];
				max = &rect_enlargement.cmbr_esq[0].coord[i];
			}
			//despues comparo las coordenadas del punto con cada coordenada del rectangulo_enlargement
			//para reencontrar el min y el maximo
			if (x.coord[i] < *min)
			{
				*min = x.coord[i];
			}
			else if (x.coord[i] > * max)
			{
				*max = x.coord[i];
			}
		}
		return rect_enlargement.calc_area() - this->calc_area();
	}

	double calc_enlargement(CMbr<T> rectang) //calcula cuanto se alarga con un rectangulo dado
	{
		CMbr<T> rect_enlargement = *this;
		
		if (contiene(rectang.cmbr_esq[0]) and contiene(rectang.cmbr_esq[1])) {
			return 0;
		}

		rect_enlargement.enlargement(rectang.cmbr_esq[0]);
		rect_enlargement.enlargement(rectang.cmbr_esq[1]);

		return rect_enlargement.calc_area() - this->calc_area();
	}

	bool enlargement(CPoint<T> Point_a) //alarga el rectangulo a un punto dado
	{
		if (contiene(Point_a))
		{
			return 0;
		}

		T* min, * max;
		
		for (int i = 0; i < cmbr_esq[0].coord.size(); i++)
		{
			if (cmbr_esq[0].coord[i] < cmbr_esq[1].coord[i])
			{
				min = &cmbr_esq[0].coord[i];
				max = &cmbr_esq[1].coord[i];
			}
			else
			{
				min = &cmbr_esq[1].coord[i];
				max = &cmbr_esq[0].coord[i];
			}
			//despues comparo las coordenadas del punto con cada coordenada del rectangulo_enlargement
			//para reencontrar el min y el maximo
			if (Point_a.coord[i] < *min)
			{
				*min = Point_a.coord[i];
			}
			else if (Point_a.coord[i] > * max)
			{
				*max = Point_a.coord[i];
			}
		}
		return 1;
	}

	void print()
	{
		cout << "[ "; cmbr_esq[0].print(); cout << "   "; cmbr_esq[1].print(); cout << " ]";
	}

	void draw() //dibuja el rectangulo
	{
		glBegin(GL_LINES);
		//lineavertical
		glColor3d(0.129, 0.109, 0.949);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[0].coord[1]);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[1].coord[1]);
		glColor3d(0.129, 0.109, 0.949);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[0].coord[1]);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[1].coord[1]);

		//linea horizontal
		glColor3d(0.129, 0.109, 0.949);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[0].coord[1]);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[0].coord[1]);
		glColor3d(0.129, 0.109, 0.949);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[1].coord[1]);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[1].coord[1]);

		glEnd();
	}

	void draw(int r, int g, int b) //dibuja el rectangulo con colores definidps
	{
		r = r % 255;
		g = g % 255;
		b = b % 255;
		glBegin(GL_LINES);
		//lineavertical
		glColor3d(r, g, b);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[0].coord[1]);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[1].coord[1]);
		glColor3d(r, g, b);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[0].coord[1]);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[1].coord[1]);

		//linea horizontal
		glColor3d(r, g, b);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[0].coord[1]);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[0].coord[1]);
		glColor3d(r, g, b);
		glVertex2d(cmbr_esq[0].coord[0], cmbr_esq[1].coord[1]);
		glVertex2d(cmbr_esq[1].coord[0], cmbr_esq[1].coord[1]);

		glEnd();
	}

	template<class U>friend ostream& operator<<(ostream & os, const CMbr<T> & cm)
	{
		os << "[ " << cm.cmbr_esq[0] << "   " << cm.cmbr_esq[1] << " ]";
		return os;
	}
};

template<class T>
class CRTreeNode //objeto que almacena un rectangulo con varios puntos
{
public:
	CRTreeNode()
	{
		crtn_leaf = true; //hace hora al nodo
	}

	bool is_leaf() //pregunta si es hoja
	{
		return crtn_leaf;
	}

	bool insert_point(CPoint<T> x) //Inserta un punto en la lista de puntos "crtn_points"
	{
		crtn_points.push_back(x);
		return 1;
	}

	bool insert_mbr(CMbr<T> rectang_x, CRTreeNode<T>* p, int pos) //inserta un rectangulo en el vector de rectangulos en una posicion especifica
	{
		crtn_mbr.insert(crtn_mbr.begin() + pos, rectang_x);
		crtn_children_pointers.insert(crtn_children_pointers.begin() + pos, p);
		return 1;
	}

	bool insert_mbr(CMbr<T> x, CRTreeNode<T>* p) ////inserta un rectangulo en el vector de rectangulos 
	{
		crtn_mbr.push_back(x);
		crtn_children_pointers.push_back(p);
		return 1;
	}

	bool crtn_leaf;  //si es un nodo hoja o no
	template<class U> friend class CRTree;
private:
	vector<CMbr<T> > crtn_mbr; // hyperrectangulos, vector de rectangulos
	vector<CRTreeNode<T>* > crtn_children_pointers; //esto crece si no es nodo hoja, lista de punteros a rectangulos con puntos
	vector<CPoint<T> > crtn_points; //data espacial en un vector
};

template<class T>
class CRTree //clase que genera el rtree
{
private:
	int crt_M;
	int crt_x_min, crt_y_min, crt_x_max, crt_y_max;

public:
	CRTreeNode<T>* crt_root;

	CRTree(int max1, int x_min, int y_min, int x_max, int y_max) : crt_M(max1), crt_x_min(x_min), crt_y_min(y_min), crt_x_max(x_max), crt_y_max(y_max)
	{
		crt_root = new CRTreeNode<T>;
	}

	CRTree() {}

	//funciones usadas en la insercion y auxiliares
	bool insert_point(CPoint<T> PointTI)
	{
		//I1 Encontramos la posicion para el nuevo record
		vector< pair<CRTreeNode<T>*, int> > camino;

		choose_leaf(PointTI, camino);

		//verificamos que p no contenga el mismo punto
		for (int i = 0; i < camino[camino.size()-1].first->crtn_points.size(); i++)
		{
			if (PointTI.coord == camino[camino.size()-1].first->crtn_points[i].coord)
			{
				return 0;
			}
		}

		//I2 agregamos registro
		camino[camino.size()-1].first->crtn_points.push_back(PointTI);
		
		//hacemos la verificacione ocn la funcion adjustTree
		adjust_tree(camino);

		return 1;
	}

	void choose_leaf(CPoint<T> PuntoTI, vector<pair< CRTreeNode<T>*, int > > & camino)
	{
		T min_distance, actual_distance; //cuanto crece el rectangulo
		int pivot; //guarda en que hijo se encuentra

		CRTreeNode<T>* p;
		for (p = crt_root; !p->is_leaf(); p = p->crtn_children_pointers[pivot])
		{
			pivot = 0;
			min_distance = p->crtn_mbr[0].calc_enlargement(PuntoTI);
			for (int i = 1; i < p->crtn_mbr.size(); i++)
			{
				actual_distance = p->crtn_mbr[i].calc_enlargement(PuntoTI);
				if (actual_distance == min_distance)
				{
					if (p->crtn_mbr[pivot].calc_area() > p->crtn_mbr[i].calc_area()) pivot = i;
				}
				else if (actual_distance < min_distance)
				{
					pivot = i;
					min_distance = actual_distance;
				}
			}
			camino.push_back(make_pair(p, pivot));
		}
		camino.push_back(make_pair(p, p->crtn_points.size()));
	}

	void quadratic_split(CRTreeNode<T> * s, CRTreeNode<T> * p, int pc) //hijo - padre - p->children nodes[pc]
	{
		CMbr<T> seed_rect1, seed_rect2;
		int seed_pivots[2]; //
		int m = ceil(crt_M / 2); //cantidad minima de hijos
		double area1, area2, enlargement1, enlargement2;
		bool option; //0 es s 1 nn cuando hago el choose leaf los 2 hijos que se crean

		//split del root
		if (s == p)
		{
			CRTreeNode<T>* new_root = new CRTreeNode<T>;
			new_root->crtn_leaf = 0;
			p = crt_root = new_root;
			p->insert_mbr(seed_rect1, s, 0);
		}

		//inicialization
		pick_seeds(s, seed_rect1, seed_rect2, seed_pivots);
		//s se reutiliza
		CRTreeNode<T>* nn = new CRTreeNode<T>(); //nuevo hijo
		p->crtn_mbr[pc] = seed_rect1; 
		p->insert_mbr(seed_rect2, nn, pc + 1); 

		if (s->is_leaf()) //puntos
		{
			CRTreeNode<T>  aux_points;
			aux_points.crtn_points = s->crtn_points;

			s->crtn_points.clear();

			s->insert_point(aux_points.crtn_points[seed_pivots[0]]);
			nn->insert_point(aux_points.crtn_points[seed_pivots[1]]);

			///////////////////////////////////////////////////////////////////////
			if (seed_pivots[0] < seed_pivots[1])
			{
				aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[1]);
				aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[0]);
			}
			else
			{
				aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[0]);
				aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[1]);
			}

			///////////////////////////////////////////////////////////////////////////
			int pos; //
			while (s->crtn_points.size() <= m and nn->crtn_points.size() <= m) //mandar de un lado a otro
			{
				pick_next(&aux_points, pos, seed_rect1, seed_rect2);
				enlargement1 = seed_rect1.calc_enlargement(aux_points.crtn_points[pos]);
				enlargement2 = seed_rect2.calc_enlargement(aux_points.crtn_points[pos]);

				if (enlargement1 == enlargement2)
				{
					area1 = seed_rect1.calc_area();
					area2 = seed_rect2.calc_area();
					if (area1 == area2)
					{
						if (s->crtn_points.size() <= nn->crtn_points.size())
							option = 0;
						else
							option = 1;
					}
					else
					{
						if (area1 < area2)
							option = 0;
						else
							option = 1;
					}
				}
				else if (enlargement1 < enlargement2)
					option = 0;
				else
					option = 1;

				if (option)
				{
					nn->insert_point(aux_points.crtn_points[pos]);
					p->crtn_mbr[pc + 1].enlargement(aux_points.crtn_points[pos]);
				}
				else
				{
					s->insert_point(aux_points.crtn_points[pos]);
					p->crtn_mbr[pc].enlargement(aux_points.crtn_points[pos]);
				}
				aux_points.crtn_points.erase(aux_points.crtn_points.begin() + pos);

			}

			if (s->crtn_points.size() >= m)
			{
				for (int i = 0; i < aux_points.crtn_points.size(); i++)
					p->crtn_mbr[pc + 1].enlargement(aux_points.crtn_points[i]);
				nn->crtn_points.insert(nn->crtn_points.end(), aux_points.crtn_points.begin(), aux_points.crtn_points.end());
			}
			else
			{
				for (int i = 0; i < aux_points.crtn_points.size(); i++)
					p->crtn_mbr[pc].enlargement(aux_points.crtn_points[i]);
				s->crtn_points.insert(s->crtn_points.end(), aux_points.crtn_points.begin(), aux_points.crtn_points.end());
			}
		}//fin del if-----------------------------------------------
		else //rectangulos
		{
			nn->crtn_leaf = 0; //hacemos que el nodo derecho sea nodo no hoja
			CRTreeNode<T>  aux_points;
			aux_points.crtn_leaf = false;
			aux_points.crtn_mbr = s->crtn_mbr;
			aux_points.crtn_children_pointers = s->crtn_children_pointers;
			s->crtn_mbr.clear();
			s->crtn_children_pointers.clear();

			s->insert_mbr(aux_points.crtn_mbr[seed_pivots[0]], aux_points.crtn_children_pointers[seed_pivots[0]], 0);
			nn->insert_mbr(aux_points.crtn_mbr[seed_pivots[1]], aux_points.crtn_children_pointers[seed_pivots[1]], 0);

			aux_points.crtn_mbr.erase(aux_points.crtn_mbr.begin() + seed_pivots[0]);
			aux_points.crtn_children_pointers.erase(aux_points.crtn_children_pointers.begin() + seed_pivots[0]);

			if (seed_pivots[0] < seed_pivots[1])
				seed_pivots[1]--;

			aux_points.crtn_mbr.erase(aux_points.crtn_mbr.begin() + seed_pivots[1]);
			aux_points.crtn_children_pointers.erase(aux_points.crtn_children_pointers.begin() + seed_pivots[1]);

			int pos;

			while (s->crtn_mbr.size() < m and nn->crtn_mbr.size() < m)
			{
				pick_next(&aux_points, pos, seed_rect1, seed_rect2);
				enlargement1 = seed_rect1.calc_enlargement(aux_points.crtn_mbr[pos]);
				enlargement2 = seed_rect2.calc_enlargement(aux_points.crtn_mbr[pos]);
				if (enlargement1 == enlargement2)
				{
					area1 = seed_rect1.calc_area();
					area2 = seed_rect2.calc_area();
					if (area1 == area2)
					{
						if (s->crtn_mbr.size() <= nn->crtn_mbr.size())
							option = 0;
						else
							option = 1;
					}
					else if (area1 < area2)
						option = 0;
					else
						option = 1;
				}
				else if (enlargement1 < enlargement2)
					option = 0;
				else
					option = 1;

				if (option)
				{
					nn->insert_mbr(aux_points.crtn_mbr[pos], aux_points.crtn_children_pointers[pos]);
					p->crtn_mbr[pc + 1].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[0]);
					p->crtn_mbr[pc + 1].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[1]);
				}
				else
				{
					s->insert_mbr(aux_points.crtn_mbr[pos], aux_points.crtn_children_pointers[pos]);
					p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[0]);
					p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[1]);
				}
				aux_points.crtn_mbr.erase(aux_points.crtn_mbr.begin() + pos);
				aux_points.crtn_children_pointers.erase(aux_points.crtn_children_pointers.begin() + pos);
			}

			if (s->crtn_mbr.size() >= m)
			{
				for (int i = 0; i < aux_points.crtn_mbr.size(); i++)
				{
					p->crtn_mbr[pc + 1].enlargement(aux_points.crtn_mbr[i].cmbr_esq[0]);
					p->crtn_mbr[pc + 1].enlargement(aux_points.crtn_mbr[i].cmbr_esq[1]);

				}
				nn->crtn_mbr.insert(nn->crtn_mbr.end(), aux_points.crtn_mbr.begin(), aux_points.crtn_mbr.end());
				nn->crtn_children_pointers.insert(nn->crtn_children_pointers.end(), aux_points.crtn_children_pointers.begin(), aux_points.crtn_children_pointers.end());
			}
			else
			{
				for (int i = 0; i < aux_points.crtn_mbr.size(); i++)
				{
					p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[i].cmbr_esq[0]);
					p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[i].cmbr_esq[1]);

				}
				s->crtn_mbr.insert(s->crtn_mbr.end(), aux_points.crtn_mbr.begin(), aux_points.crtn_mbr.end());
				s->crtn_children_pointers.insert(s->crtn_children_pointers.end(), aux_points.crtn_children_pointers.begin(), aux_points.crtn_children_pointers.end());
			}
		}
	}

	void pick_seeds(CRTreeNode<T> * p, CMbr<T> & rect1, CMbr<T> & rect2, int(&pivots)[2]) //
	{
		double area = 0, aux_area;
		CMbr<T> rect_compare;
		int pivot1, pivot2;

		if (p->is_leaf())
		{
			//evaluamos con todos los puntos para los mas lejanos
			for (int i = 0; i < p->crtn_points.size() - 1; i++)
			{
				rect_compare.cmbr_esq[0] = p->crtn_points[i];

				for (int j = i + 1; j < p->crtn_points.size(); j++)
				{
					rect_compare.cmbr_esq[1] = p->crtn_points[j];
					aux_area = rect_compare.calc_area();

					if (aux_area > area)
					{
						pivot1 = i;
						pivot2 = j;
						area = aux_area;
					}
				}
			}
			//aqui creamos los dos rectangulos con los dos pivotes que son los puntos que forman el area mas grande
			rect1.cmbr_esq[0] = p->crtn_points[pivot1];
			rect1.cmbr_esq[1] = p->crtn_points[pivot1];
			rect2.cmbr_esq[0] = p->crtn_points[pivot2];
			rect2.cmbr_esq[1] = p->crtn_points[pivot2];
		}
		else //con rectangulos
		{
			for (int i = 0; i < p->crtn_mbr.size() - 1; i++)
			{
				for (int j = i + 1; j < p->crtn_mbr.size(); j++)
				{
					rect_compare = p->crtn_mbr[i];
					rect_compare.enlargement(p->crtn_mbr[j].cmbr_esq[0]);
					rect_compare.enlargement(p->crtn_mbr[j].cmbr_esq[1]);
					aux_area = abs(rect_compare.calc_area() - p->crtn_mbr[i].calc_area() - p->crtn_mbr[j].calc_area());
					if (aux_area > area)
					{
						pivot1 = i;
						pivot2 = j;
						area = aux_area;
					}
				}
			}
			rect1 = p->crtn_mbr[pivot1];
			rect2 = p->crtn_mbr[pivot2];
		}

		pivots[0] = pivot1;
		pivots[1] = pivot2;
	}

	void pick_next(CRTreeNode<T> * p, int& pivot, CMbr<T> rect1, CMbr<T> rect2)
	{
		double area1, area2, max;
		max = 0;
		pivot = 0;

		if (p->is_leaf())
		{
			for (int i = 0; i < p->crtn_points.size(); i++)
			{
				area1 = rect1.calc_enlargement(p->crtn_points[i]);
				area2 = rect2.calc_enlargement(p->crtn_points[i]);
				if (max < abs(area1 - area2))
				{
					pivot = i;
					max = abs(area1 - area2);
				}
			}
		}
		else
		{
			CMbr<T> mbr_aux;
			for (int i = 0; i < p->crtn_mbr.size(); i++)
			{
				mbr_aux = rect1;
				mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[0]);
				mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[1]);
				area1 = mbr_aux.calc_area() - rect1.calc_area();

				mbr_aux = rect2;
				mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[0]);
				mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[1]);
				area2 = mbr_aux.calc_area() - rect2.calc_area();

				if (abs(area1 - area2) > max)
				{
					pivot = i;
					max = abs(area1 - area2);
				}
			}
		}
	}

	void adjust_tree(vector<pair< CRTreeNode<T>*, int > > & path)
	{
		for (int i = path.size() - 1; i > 0; i--)
		{
			if (path[i].first->crtn_mbr.size() > crt_M or path[i].first->crtn_points.size() > crt_M)
			{
				quadratic_split(path[i].first, path[i - 1].first, path[i - 1].second);
			}
			else
			{
				if (i == path.size() - 1)
				{
					path[i - 1].first->crtn_mbr[path[i - 1].second].enlargement(path[i].first->crtn_points[path[i].second]);
				}
				else
				{
					path[i - 1].first->crtn_mbr[path[i - 1].second].enlargement(path[i].first->crtn_mbr[path[i].second].cmbr_esq[0]);
					path[i - 1].first->crtn_mbr[path[i - 1].second].enlargement(path[i].first->crtn_mbr[path[i].second].cmbr_esq[1]);
				}
			}
		}
		if (path[0].first->crtn_mbr.size() > crt_M or path[0].first->crtn_points.size() > crt_M)
		{
			quadratic_split(path[0].first, path[0].first, 0);
		}
	}

	//funcion print
	void print()
	{
		vector<CRTreeNode<T>*> tail;
		tail.push_back(crt_root);
		int j = 0;
		int rects = 0;
		while (j < tail.size())
		{
			for (int i = 0; i < tail[j]->crtn_mbr.size(); i++)
				tail.push_back(tail[j]->crtn_children_pointers[i]);
			j++;
		}

		for (int i = 0; i < tail.size(); i++)
		{
			if (tail[i]->is_leaf())
			{
				for (int n = 0; n < tail[i]->crtn_points.size(); n++)
				{
					//cout << tail[i]->crtn_points[n] << endl;
				}
			}
			else
			{
				for (int n = 0; n < tail[i]->crtn_mbr.size(); n++)
				{
					//cout << tail[i]->crtn_mbr[n] << endl;
					rects++;
				}
			}
		}
		cout << rects << endl;
	}

	void drawTree()
	{
		vector<CRTreeNode<T>*> tail;
		tail.push_back(crt_root);
		int j = 0;
		while (j < tail.size())
		{
			for (int i = 0; i < tail[j]->crtn_mbr.size(); i++)
				tail.push_back(tail[j]->crtn_children_pointers[i]);
			j++;
		}

		for (int i = 0; i < tail.size(); i++)
		{
			if (tail[i]->is_leaf())
			{
				for (int n = 0; n < tail[i]->crtn_points.size(); n++)
				{
					glPointSize(2.0);
					glBegin(GL_POINTS);
					glColor3f(0.949, 0.109, 0.658);
					glVertex2f(tail[i]->crtn_points[n].coord[0], tail[i]->crtn_points[n].coord[1]);
					glEnd();
				}
			}
			else
			{
				for (int n = 0; n < tail[i]->crtn_mbr.size(); n++)
				{
					tail[i]->crtn_mbr[n].draw();
				}
			}
		}
	}
};

//Crear rtree
CRTree<double>* a = new CRTree<double>(PPR, -300, 300, 300, -300);
CMbr<int> rect(CPoint<int>(0, 0), CPoint<int>(0, 0));

int cont;
int cx = 0, cy = 0, check = 0, x2, x3, y2, y3;
int w_window = 600, h_window = 600;
vector<CPoint<double> > searched_points;

float speed = 10;
float Pointx = 0.0;
float Pointy = 0.0;

int conv_coord_x(int x)
{
	return x - (w_window / 2);
}
int conv_coord_y(int y)
{
	return (h_window / 2) - y;
}

vector<CPoint<double> > puntosCapitales;

void insert_txt()
{
	double maxx = 0, minx = 10000000; 	double maxy = 0, miny = 10000000;
	ifstream fe("crimesll.txt");
	double longitude, latitude;
	fe >> cont;
	vector<double> xvect;
	vector<double> yvect;
	vector<double> ll_point;
	for (int i = 0; i < cont; i++)
	{
		fe >> longitude >> latitude;
		if (maxx < longitude) { maxx = longitude; }
		if (minx > longitude) { minx = longitude; }
		if (maxy < latitude) { maxy = latitude; }
		if (miny > latitude) { miny = latitude; }

		//normalizacion
		ll_point.push_back(longitude);
		ll_point.push_back(latitude);

		puntosCapitales.push_back(CPoint<double>(ll_point));
		ll_point.clear();
	}
	int inserted_elements = 0;
	for (int i = 0; i < cont; i++)
	{
		puntosCapitales[i].coord[0] = ((puntosCapitales[i].coord[0] - minx) / (maxx - minx)) * 600;
		puntosCapitales[i].coord[1] = ((puntosCapitales[i].coord[1] - miny) / (maxy - miny)) * 600;

		puntosCapitales[i].coord[0] = puntosCapitales[i].coord[0] - 300;
		puntosCapitales[i].coord[1] = puntosCapitales[i].coord[1] - 300;

		a->insert_point(puntosCapitales[i]);
		//cout << " puntosCapitales "<<i<<" : "<< puntosCapitales[i].coord[0]<<" - "<< puntosCapitales[i].coord[0]<< endl;
	}
	fe.close();
}

//dibuja un simple gizmo
void displayGizmo()
{
	if (check == 1)
	{
		check = 0;
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(cx, cy);
		glEnd();
	}
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//convertir x,y
		//insertar un nuevo punto en el rtree
		check = 1;
		cout << x << " " << y << endl;
		//cin >> x >> y;
		cx = x - (w_window / 2);
		cy = (h_window / 2) - y;
		a->insert_point(CPoint<double>(cx, cy));
	}

}

void OnMouseMotion(int x, int y)
{
	//nada
}

void idle() { // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

void glPaint(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-300.0f, 300.0f, -300.0f, 300.0f, -1.0f, 1.0f);

	//Point
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.839, 0, 0.498);
	glVertex2f(Pointx, Pointy);
	glEnd();

	//dibujar rtree
	a->drawTree();
	
	displayGizmo();
	glutSwapBuffers();
}

//inicializacion de OpenGL

void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
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
	case KEY_UP_Y:
		Pointy += 5;
		break;
	case KEY_DOWN_Y:
		Pointy -= 5;
		break;
	case KEY_RIGHT_X:
		Pointx -= 5;
		break;
	case KEY_LEFT_X:
		Pointx += 5;
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) 
{
	//insert_txt();
	a->print();
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("Rtree"); //titulo de la ventana
	init_GL(); //funcion de inicializacion de OpenGL
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutPassiveMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);

	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
}
