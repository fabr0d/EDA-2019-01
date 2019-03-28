#include<iostream>
#include<vector>
using namespace std;

struct Point
{
	double x;
	double y;
	double z;
};

bool ItsIn(vector<Point> Ranges, Point NPoint)
{
	if (NPoint.x > Ranges[0].x and NPoint.x < Ranges[1].x &&
		NPoint.y > Ranges[0].y and NPoint.y < Ranges[1].y &&
		NPoint.z > Ranges[0].z and NPoint.z < Ranges[1].z)
	{
		return true;
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
	~Cube();

private:

};


//True = partido, false = !partido

//Nota: En el Octree los puntos que delimiten las dimensiones el primero debe ser 

void find(Cube Octree, Point Pnt) {

}

void insert(Cube Octree, Point Pnt) {

}

void erase(Cube Octree, Point Pnt) {

}

int main() {
	cout << "Aiuda D: !" << endl;
	getchar();
}