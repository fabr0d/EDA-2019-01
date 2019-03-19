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
		//srand(time(NULL));
		for (int i = 0; i < dimension; i++)
		{
			double random = 1.0 / (rand() % 100);
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
	double ans=0;
	cout<<"A.dimension: "<<A.dimension<<endl;
	A.printPoint();
	B.printPoint();
	for (int i = 0; i < A.dimension; i++)
	{
		ans=ans+((B.point[i]-A.point[i])*(B.point[i]-A.point[i]));
	}
	ans=sqrt(ans);
	cout<<"ans :"<<ans<<endl;
	cout<<""<<endl;
	return 0;
}

int main(int argc, char const *argv[])
{
	pointClass* RandomPoints = NULL;
	RandomPoints = new pointClass[11000];

	double min;
	double max;
	double prom;

	int dims[11] = { 2,3,10,100,200,500,1000,2000,3000,4000,5000 };
	//int tessst;

		for (int j = 0; j < 1000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[0]);
			RandomPoints[j].genPoint();
			RandomPoints[j].printPoint();
		}
		for (int j = 1000; j < 2000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[1]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 2000; j < 3000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[2]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 3000; j < 4000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[3]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 4000; j < 5000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[4]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 5000; j < 6000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[5]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 6000; j < 7000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[6]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 7000; j < 8000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[7]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 8000; j < 9000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[8]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 9000; j < 10000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[9]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}
		for (int j = 10000; j < 11000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[10]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
		}

		//cin>>tessst;

	cout<<"calculo de el menor mayor y promedio: "<<endl;
	cout<<"0-999 2D"<<endl;

	//cout<<"A.DIM: "<<A.dimension<<endl;

	max=EuclDis(RandomPoints[0],RandomPoints[1]);
	min=EuclDis(RandomPoints[0],RandomPoints[1]);
	
	cout<<"max: "<<max<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"test....."<<endl;
	/*
	for (int i = 0; i < 999; i++)
	{
		for (int j = 1; j < 1000; j++)
		{
			if (EuclDis(RandomPoints[i],RandomPoints[j]) > max)
			{
				max=EuclDis(RandomPoints[i],RandomPoints[j]);
			}
			if (EuclDis(RandomPoints[i],RandomPoints[j]) < min)
			{
				min=EuclDis(RandomPoints[i],RandomPoints[j]);
			}
			prom=prom+EuclDis(RandomPoints[i],RandomPoints[j]);
			//cout<<"Sum of eucl dist: "<<prom<<endl;
		}	
	}
	*/
	cout<<"PROM 0-999 2D: "<<prom/499500<<endl;

	cout<<"1000-1999 3D"<<endl;
	cout<<"2000-2999 10D"<<endl;
	cout<<"3000-3999 100D"<<endl;
	cout<<"4000-4999 200D"<<endl;
	cout<<"5000-5999 500D"<<endl;
	cout<<"6000-6999 1000D"<<endl;
	cout<<"7000-7999 2000D"<<endl;
	cout<<"8000-8999 3000D"<<endl;
	cout<<"9000-9999 4000D"<<endl;
	cout<<"10000-10999 5000D"<<endl;

	return 0;
}