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
	/*~pointClass()
	{
		delete[] point;
	};*/
	void set_dim(int dimension_) {
		dimension = dimension_;
	};
	void genPoint() {
		point = new double[dimension];
		//srand(time(NULL));
		for (int i = 0; i < dimension; i++)
		{
			double random = ((double) rand() / (RAND_MAX));
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
	for (int i = 0; i < A.dimension; i++)
	{
		ans = ans + ( (B.point[i] - A.point[i]) * (B.point[i] - A.point[i]) );
	}
	ans=sqrt(ans);
	return ans;
}

int main(int argc, char const *argv[])
{
	pointClass* RandomPoints = NULL;
	RandomPoints = new pointClass[9000];

	double min;
	double max;
	double prom;
	int dims[9] = { 2,3,10,100,200,500,1000,3000,5000 };
	int count=0;

		for (int j = 0; j < 1000; j++)
		{
			//cout << dims[i] << endl;
			RandomPoints[j].set_dim(dims[0]);
			RandomPoints[j].genPoint();
			//RandomPoints[j].printPoint();
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

	cout<<"calculo de el menor mayor y promedio: "<<endl;
	double temporal;
	int contador=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"0-999 2D"<<endl;
	temporal=EuclDis(RandomPoints[0],RandomPoints[1]);
	max=temporal;
	min=temporal;
	for (int i = 0; i < 999; i++){
		for (int j = 1; j < 1000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"1000-1999 3D"<<endl;
	temporal=EuclDis(RandomPoints[1000],RandomPoints[1001]);
	max=temporal;
	min=temporal;
	for (int i = 1000; i < 1999; i++){
		for (int j = 1001; j < 2000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"2000-2999 10D"<<endl;
	temporal=EuclDis(RandomPoints[2000],RandomPoints[2001]);
	max=temporal;
	min=temporal;
	for (int i = 2000; i < 2999; i++){
		for (int j = 2001; j < 3000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"3000-3999 100D"<<endl;
	temporal=EuclDis(RandomPoints[3000],RandomPoints[3001]);
	max=temporal;
	min=temporal;
	for (int i = 3000; i < 3999; i++){
		for (int j = 3001; j < 4000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			//cout<<"temporal: "<<temporal<<endl;
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
			contador=contador+1;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"4000-4999 200D"<<endl;
	temporal=EuclDis(RandomPoints[4000],RandomPoints[4001]);
	max=temporal;
	min=temporal;
	for (int i = 4000; i < 4999; i++){
		for (int j = 4001; j < 5000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"5000-5999 500D"<<endl;
	temporal=EuclDis(RandomPoints[5000],RandomPoints[5001]);
	max=temporal;
	min=temporal;
	for (int i = 5000; i < 5999; i++){
		for (int j = 5001; j < 6000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"6000-6999 1000D"<<endl;
	temporal=EuclDis(RandomPoints[6000],RandomPoints[6001]);
	max=temporal;
	min=temporal;
	for (int i = 6000; i < 6999; i++){
		for (int j = 6001; j < 7000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"7000-7999 3000D"<<endl;
	temporal=EuclDis(RandomPoints[7000],RandomPoints[7001]);
	max=temporal;
	min=temporal;
	for (int i = 7000; i < 7999; i++){
		for (int j = 7001; j < 8000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;
	cout<<"8000-8999 5000D"<<endl;
	temporal=EuclDis(RandomPoints[8000],RandomPoints[8001]);
	max=temporal;
	min=temporal;
	for (int i = 8000; i < 8999; i++){
		for (int j = 8001; j < 9000; j++){
			temporal=EuclDis(RandomPoints[i],RandomPoints[j]);
			if (temporal > max){
				max=temporal;
			}
			if (temporal < min and temporal != 0){
				min=temporal;
			}
			prom=prom+temporal;
		}	
	}
	cout<<"PROM: "<<prom/998001<<endl;
	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;
	prom=0;
	cout<<"-------------------------------------"<<endl;

	return 0;
}