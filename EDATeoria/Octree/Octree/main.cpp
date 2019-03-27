#include<iostream>
#include<vector>
using namespace std;

struct Point
{
	double x;
	double y;
	double z;
};


//Nota: En el Octree los puntos que delimiten las dimensiones el primero debe ser 
bool ItsIn(vector<Point> Ranges, Point NPoint) 
{
	if (NPoint.x > Ranges[0].x and NPoint.x < Ranges[1].x &&
		NPoint.y > Ranges[0].y and NPoint.y < Ranges[1].y &&
		NPoint.z > Ranges[0].z and NPoint.z < Ranges[1].z )
	{
		return true;
	}
	return false;
}

class Octree
{
public:
	Octree();
	~Octree();
	void find(){}
	void insert(){}
	void delet(){}
	Octree *r1, *r2, *r3, *r4, *r5, *r6, *r7, *r8;

private:

};

Octree::Octree()
{
}

Octree::~Octree()
{
}


int main() {
	cout << "Aiuda D: !" << endl;
	getchar();
}