//octree con 1 punto x cubo
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
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
		cout << "se inserto el punto: "; printPoint(n->pos);
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
			cout << "anchodel nuevo cubo: " << ancho / 2 << endl;

			SDF = new Octree(Point(PIIF.x + p, PIIF.y + p, PIIF.z), Point(PIIF.x + 2 * p, PIIF.y + 2 * p, PIIF.z - p), ancho / 2);
			cout << "Se creo un Cubo Superior Derecho Frontal" << endl;
			cout << "limites :" << endl;
			printPoint(SDF->PIIF);
			printPoint(SDF->PSDP);
			cout << "Punto medio : "; PuntoMedio(SDF->PIIF, SDF->PSDP);
			
			SDP = new Octree(Point((PSDP.x + PIIF.x) / 2, (PSDP.y + PIIF.y) / 2, (PSDP.z + PIIF.z) / 2), Point(PSDP.x, PSDP.y, PSDP.z), ancho / 2);
			cout << "Se creo un Cubo Superior Derecho Posterior" << endl;
			cout << "limites :" << endl;
			printPoint(SDP->PIIF);
			printPoint(SDP->PSDP);
			cout << "Punto medio : "; PuntoMedio(SDP->PIIF, SDP->PSDP);
			
			IDF = new Octree(Point(PIIF.x + p, PIIF.y, PIIF.z), Point(PIIF.x + 2 * p, PIIF.y + p, PIIF.z - p), ancho / 2);
			cout << "Se creo un Cubo Inferior Derecho Frontal" << endl;
			cout << "limites :" << endl;
			printPoint(IDF->PIIF);
			printPoint(IDF->PSDP);
			cout << "Punto medio : "; PuntoMedio(IDF->PIIF, IDF->PSDP);
			
			IDP = new Octree(Point(PIIF.x + p, PIIF.y, PIIF.z - p), Point(PIIF.x + 2 * p, PIIF.y + p, PIIF.z - 2 * p), ancho / 2);
			cout << "Se creo un Cubo Inferior Derecho Posterior" << endl;
			cout << "limites :" << endl;
			printPoint(IDP->PIIF);
			printPoint(IDP->PSDP);
			cout << "Punto medio : "; PuntoMedio(IDP->PIIF, IDP->PSDP);
			
			SIF = new Octree(Point(PIIF.x, PIIF.y + p, PIIF.z), Point(PIIF.x + p, PIIF.y + 2 * p, PIIF.z - p), ancho / 2);
			cout << "Se creo un Cubo Superior Izquierdo Frontal" << endl;
			cout << "limites :" << endl;
			printPoint(SIF->PIIF);
			printPoint(SIF->PSDP);
			cout << "Punto medio : "; PuntoMedio(SIF->PIIF, SIF->PSDP);
			
			SIP = new Octree(Point(PIIF.x, PIIF.y + p, PIIF.z - p), Point(PIIF.x + p, PIIF.y + 2 * p, PIIF.z - 2 * p), ancho / 2);
			cout << "Se creo un Cubo Superior Izquierdo Posterior" << endl;
			cout << "limites :" << endl;
			printPoint(SIP->PIIF);
			printPoint(SIP->PSDP);
			cout << "Punto medio : "; PuntoMedio(SIP->PIIF, SIP->PSDP);
			
			IIF = new Octree(Point(PIIF.x, PIIF.y, PIIF.z), Point((PSDP.x + PIIF.x) / 2, (PSDP.y + PIIF.y) / 2, (PSDP.z + PIIF.z) / 2), ancho / 2);
			cout << "Se creo un Cubo Inferior Izquierdo Frontal" << endl;
			cout << "limites :" << endl;
			printPoint(IIF->PIIF);
			printPoint(IIF->PSDP);
			cout << "Punto medio : "; PuntoMedio(IIF->PIIF, IIF->PSDP);
			
			IIP = new Octree(Point(PIIF.x, PIIF.y, PIIF.z - p), Point(PIIF.x + p, PIIF.y + p, PIIF.z - 2 * p), ancho / 2);
			cout << "Se creo un Cubo Inferior Izquierdo Posterior" << endl;
			cout << "limites :" << endl;
			printPoint(IIP->PIIF);
			printPoint(IIP->PSDP);
			cout << "Punto medio : "; PuntoMedio(IIP->PIIF, IIP->PSDP);
			cout << "------------------------------------------------" << endl;

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
			cout << "borro el punto: "; printPoint(n->pos);
			cout << "del cubo: ";
			printPoint(PIIF);
			printPoint(PSDP);
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
		cout << "Punto PIIF de cubo: ";
		printPoint(octo->PIIF);
		cout << "Punto PSDP de cubo: ";
		printPoint(octo->PSDP);
		cout << "Ancho del Cubo: " << octo->ancho << endl;
		cout << "---------------------------" << endl;
	}

	if (octo->n != NULL)
	{
		cout << "punto dentro de cubo :";
		printPoint(octo->n->pos);
		cout << "Punto PIIF de cubo: ";
		printPoint(octo->PIIF);
		cout << "Punto PSDP de cubo: ";
		printPoint(octo->PSDP);
		cout << "Ancho del Cubo: " << octo->ancho << endl;
	}
	if (octo->n == NULL && octo->IIF != NULL && octo->IDF != NULL && octo->IIP != NULL && octo->IDP != NULL &&
		octo->SIF != NULL && octo->SDF != NULL && octo->SIP != NULL && octo->SDP != NULL)
	{
		cout << "Punto PIIF de cubo: ";
		printPoint(octo->PIIF);
		cout << "Punto PSDP de cubo: ";
		printPoint(octo->PSDP);
		cout << "Ancho del Cubo: " << octo->ancho << endl;
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

// Driver program
int main()
{
	Octree oct1(Point(0, 0, 0), Point(8, 8, -8), 8);
	Node a(Point(1, 1, -1.0), 10);
	Node b(Point(1, 1 ,-2.1), 20);
	Node c(Point(7, 4, -7.1), 30);
	//Node c(Point(5, 5, -5), 30);
	cout << "insert del punto: "; printPoint(a.pos);
	oct1.insert(&a);
	cout << "insert del punto :"; printPoint(b.pos);
	oct1.insert(&b);
	cout << "insert del punto :"; printPoint(c.pos);
	oct1.insert(&c);

	//cout << "cubo del octree SIP datos manuales : " << oct1.SIP->n->data << endl;

	cout << "Node a: " << oct1.search(a.pos)->data << "\n";
	cout << "Node b: " << oct1.search(b.pos)->data << "\n";
	cout << "Node c: " << oct1.search(c.pos)->data << "\n";
	//cout << "Node c: " << oct1.search(c.pos)->data << "\n";
	cout << "Non-existing node: "
		<< oct1.search(Point(5, 5, 5)); cout << "" << endl;
	cout << "-------------------------------------------------------------" << endl;
	PrintOctree(&oct1);

	getchar();
	return 0;
}
