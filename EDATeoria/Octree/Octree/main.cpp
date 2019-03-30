#include<iostream>
#include<vector>
using namespace std;
int maxpoints = 4;

struct Point
{
	double x;
	double y;
	double z;
};

bool ItsIn(vector<Point> Limits, Point NPoint)
{
	if (NPoint.x > Limits[0].x and NPoint.x < Limits[1].x &&
		NPoint.y > Limits[0].y and NPoint.y < Limits[1].y &&
		NPoint.z > Limits[0].z and NPoint.z < Limits[1].z)
	{
		return true;
	}
	return false;
}

bool Compare(Point p1, Point p2)
{
	if (p1.x==p2.x and p1.y == p2.y and p1.z == p2.z)
	{
		return true;
		//Si son iguales
	}
	else
	{
		return false;
	}
}

bool searchInElements(vector<Point> Elements, Point Pnt) 
{
	for (int i = 0; i < Elements.size(); i++)
	{
		if (Compare(Elements[i],Pnt)==true) 
		{
			return true;
		}
	}
	return false;
}

class Cube
{
public:
	vector<Point> Limits;
	vector<Point> Elements;
	bool Status;
	vector<Cube> Sons;
	Cube(Point P1, Point P2) {
		Limits.push_back(P1);
		Limits.push_back(P2);
	}
private:

};

//True = partido, false = !partido
//Nota: En el Octree los puntos que delimiten las dimensiones el primero debe ser 

void find(Cube Octree, Point Pnt) {
	if (Octree.Status==false)
	{
		cout << "Entre a un cubo" << endl;
		if (ItsIn(Octree.Limits, Pnt) == true)
		{
			if (searchInElements(Octree.Elements, Pnt) == true)
			{
				cout << "se encontro" << endl;
			}
		}
	}
	else
	{
		find(Octree.Sons[0], Pnt);
		find(Octree.Sons[1], Pnt);
		find(Octree.Sons[2], Pnt);
		find(Octree.Sons[3], Pnt);
		find(Octree.Sons[4], Pnt);
		find(Octree.Sons[5], Pnt);
		find(Octree.Sons[6], Pnt);
		find(Octree.Sons[7], Pnt);
	}
}

void insert(Cube Octree, Point Pnt) {

}

void erase(Cube Octree, Point Pnt) {

}

int main() {
	cout << "Aiuda D: !" << endl;
	getchar();
}