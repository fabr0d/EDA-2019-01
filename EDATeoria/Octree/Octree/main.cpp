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

void printPoint(Point p1)
{
	cout << "[" << p1.x << "," << p1.y << "," << p1.z << "]" << endl;;
}

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
	double longi;
	vector<Point> Limits;
	vector<Point> Elements;
	bool Status;
	vector<Cube> Sons;
	Cube(Point P1, Point P2, double longi_) {
		Limits.push_back(P1);
		Limits.push_back(P2);
		longi = longi_;
	}
private:

};

//True = partido, false = !partido
//Nota: En el Octree los puntos que delimiten las dimensiones el primero debe ser 

void genSons(Cube Octree) {
	double p = Octree.longi/2;
	//cubo1
	Point Ptemp1; 
	Ptemp1.x = Octree.Limits[0].x; 
	Ptemp1.y = Octree.Limits[0].y; 
	Ptemp1.z = Octree.Limits[0].z;
	Point Ptemp2; 
	Ptemp2.x = (Octree.Limits[0].x + Octree.Limits[1].x) / 2;
	Ptemp2.y = (Octree.Limits[0].y + Octree.Limits[1].y) / 2;
	Ptemp2.z = (Octree.Limits[0].z + Octree.Limits[1].z) / 2;

	//cubo2
	Point Ptemp3; 
	Ptemp3.x = Octree.Limits[0].x;
	Ptemp3.y = Octree.Limits[0].y+p; 
	Ptemp3.z = Octree.Limits[0].z;
	Point Ptemp4; 
	Ptemp4.x = Octree.Limits[0].x-p; 
	Ptemp4.y = Octree.Limits[0].y+2*p;
	Ptemp4.z = Octree.Limits[0].z+p;

	//cubo3
	Point Ptemp5;
	Ptemp5.x = Octree.Limits[0].x-p;
	Ptemp5.y = Octree.Limits[0].y;
	Ptemp5.z = Octree.Limits[0].z;
	Point Ptemp6;
	Ptemp6.x = Octree.Limits[0].x-2*p;
	Ptemp6.y = Octree.Limits[0].y+p;
	Ptemp6.z = Octree.Limits[0].z+p;

	//cubo4
	Point Ptemp7;
	Ptemp7.x = Octree.Limits[0].x-p;
	Ptemp7.y = Octree.Limits[0].y+p;
	Ptemp7.z = Octree.Limits[0].z;
	Point Ptemp8;
	Ptemp8.x = Octree.Limits[0].x-2*p;
	Ptemp8.y = Octree.Limits[0].y+2*p;
	Ptemp8.z = Octree.Limits[0].z+p;

	//cubo5
	Point Ptemp9;
	Ptemp9.x = Octree.Limits[0].x;
	Ptemp9.y = Octree.Limits[0].y;
	Ptemp9.z = Octree.Limits[0].z+p;
	Point Ptemp10;
	Ptemp10.x = Octree.Limits[0].x-p;
	Ptemp10.y = Octree.Limits[0].y+p;
	Ptemp10.z = Octree.Limits[0].z+2*p;

	//cubo6
	Point Ptemp11;
	Ptemp11.x = Octree.Limits[0].x;
	Ptemp11.y = Octree.Limits[0].y+p;
	Ptemp11.z = Octree.Limits[0].z+p;
	Point Ptemp12;
	Ptemp12.x = Octree.Limits[0].x-p;
	Ptemp12.y = Octree.Limits[0].y+2*p;
	Ptemp12.z = Octree.Limits[0].z+2*p;

	//cubo7
	Point Ptemp13;
	Ptemp13.x = Octree.Limits[0].x-p;
	Ptemp13.y = Octree.Limits[0].y;
	Ptemp13.z = Octree.Limits[0].z+p;
	Point Ptemp14;
	Ptemp14.x = Octree.Limits[0].x-2*p;
	Ptemp14.y = Octree.Limits[0].y+p;
	Ptemp14.z = Octree.Limits[0].z+2*p;

	//cubo8
	Point Ptemp15;
	Ptemp15.x = (Octree.Limits[0].x + Octree.Limits[1].x) / 2;
	Ptemp15.y = (Octree.Limits[0].y + Octree.Limits[1].y) / 2;
	Ptemp15.z = (Octree.Limits[0].z + Octree.Limits[1].z) / 2;
	Point Ptemp16;
	Ptemp16.x = Octree.Limits[1].x;
	Ptemp16.y = Octree.Limits[1].y;
	Ptemp16.z = Octree.Limits[1].z;
	
	printPoint(Ptemp1);
	printPoint(Ptemp2);
	printPoint(Ptemp3);
	printPoint(Ptemp4);
	printPoint(Ptemp5);
	printPoint(Ptemp6);
	printPoint(Ptemp7);
	printPoint(Ptemp8);
	printPoint(Ptemp9);
	printPoint(Ptemp10);
	printPoint(Ptemp11);
	printPoint(Ptemp12);
	printPoint(Ptemp13);
	printPoint(Ptemp14);
	printPoint(Ptemp15);
	printPoint(Ptemp16);
}

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
	Point p1;
	Point p2;
	p1.x = 4;
	p1.y = -4;
	p1.z = 0;
	p2.x = -4;
	p2.y = 4;
	p2.z = 8;
	Cube Oct1(p1,p2,8);
	genSons(Oct1);
	getchar();
}