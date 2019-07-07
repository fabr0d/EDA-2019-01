#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <fstream>
using namespace std;
int dims = 3;

bool lessbt(bitset<64> a, bitset<64> b)
{
	return a.to_ullong() < b.to_ullong();
}

struct Hyperdata //Estructura que almacenara el elemento 64-k
{
	vector<bitset<64>> datas;
	Hyperdata(vector<bitset<64>> temp)
	{
		datas = temp;
	}
	bitset<64> z(int pos) //empieza de 1
	{
		bitset<64> temp;
		for (int i = 0; i < datas.size(); i++)
		{
			temp[i] = datas[i][64 - pos];
		}
		return temp;
	}
};

class LHC //Nodo
{
public:
	map<bitset<64>, LHC, bool(*)(bitset<64>, bitset<64>) >sons;

	LHC()
	{
		sons = map<bitset<64>, LHC, bool(*)(bitset<64>, bitset<64>)>(lessbt);
	}

	void insert(Hyperdata data)
	{
		LHC* p = this;
		int cont = 0;
		while (cont < 64)
		{
			p = &p->sons[data.z(64 - cont++)];
		}
	}
	bool search(Hyperdata data)
	{
		LHC* p = this;
		int cont = 0;
		while (cont < 64)
		{
			if (p->sons.count(data.z(64 - cont)) == 0) {
				return false;
			}

			p = &p->sons[data.z(64 - cont++)];
		}

		return true;
	}
};
int main()
{
	double equis;
	double ye;
	double zeta;
	ifstream figure("D:\\EDA\\DataSets\\skyscraper(2022).txt");
	cout << figure.is_open() << endl;

	LHC phtree;

	while (figure >> equis >> ye >> zeta) {
		vector<bitset<64>> tosend;
		int x = equis * 100000;
		int y = ye * 100000;
		int z = zeta * 100000;
		bitset<64> temp1(x);
		bitset<64> temp2(y);
		bitset<64> temp3(z);

		tosend.push_back(temp1);
		tosend.push_back(temp2);
		tosend.push_back(temp3);
		Hyperdata toinsert(tosend);
		phtree.insert(toinsert);
	}
	cout << "busqueda" << endl;
	cout << "inserte 3 numeros a buscar: " << endl;
	equis = 2.511563 * 100000; ye = 26.914238 * 100000; zeta = -4.279754 * 100000;
	vector<bitset<64>> toread;
	int xx = equis;
	int yy = ye;
	int zz = zeta;
	bitset<64> temp1(xx);
	bitset<64> temp2(yy);
	bitset<64> temp3(zz);
	toread.push_back(temp1);
	toread.push_back(temp2);
	toread.push_back(temp3);
	Hyperdata tosearch(toread);

	cout << phtree.search(toread) << endl;


	/*
	bitset<64>a(1);
	bitset<64>b(5);
	vector<bitset<64>> temp;
	temp.push_back(a);
	temp.push_back(b);

	Hyperdata test(temp);
	LHC ph;
	ph.insert(test);
	cout << ph.search(test) << endl;
	*/
	//cout << "pos 62: " << test.z(62) << endl;

	return 0;
}