#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>   
using namespace std;
class pointClass
{
public:
	int dimension;
	double *point = NULL;
	pointClass() = default;
	~pointClass()
	{
		delete[] point;
	};
	void set_dim(int dimension_) {
		dimension = dimension_;
	};
	void genPoint() {
		point = new double[dimension];
		srand(time(NULL));
		for (int i = 0; i < dimension; i++)
		{
			double random = 1.0 / (rand() % 5000);
			point[i] = random;
		}
	}
	void printPoint() {
		cout << "[";
		for (int i = 0; i < dimension; i++)
		{
			cout << point[i] << ", ";
		}
		cout << "]" << endl;
	}

};


double EuclDis(pointClass A, pointClass B) {
	double ans;
	double temp=0;
	for (int i = 0; i < A.dimension; i++)
	{
		temp=temp+((B.point[i]-A.point[i])*(B.point[i]-A.point[i]));
	}
	ans=sqrt(ans);
	return 0;
}

int main(int argc, char const *argv[])
{
	pointClass* RandomPoints = NULL;
	RandomPoints = new pointClass[11000];

	int* ListDist=NULL;
	ListDist = new int[1000];

	int dims[11] = { 2,3,10,100,200,500,1000,2000,3000,4000,5000 };

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			cout << dims[j] << endl;
			RandomPoints[i].set_dim(dims[j]);
			RandomPoints[i].genPoint();
			RandomPoints[i].printPoint();
		}
		system("pause");
	}

	return 0;
}