#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <utility> 
#include <fstream>
#include <algorithm>
using namespace std;
int N_bits = 4;

struct Hyperdata //Estructura que almacenara el elemento 64-k
{
	vector<bitset<4>> datas;
	Hyperdata(vector<bitset<4>> temp)
	{
		datas = temp;
	}
	void print()
	{
		for (int i = 0; i < datas.size(); i++)
		{
			cout << datas[i] << ", ";
		}
		cout << "" << endl;
	}
	bitset<4> BitsEnPosXDeCadaDimDeUnDato(int pos) //pos >= 1
	{
		bitset<4> temp;
		for (int i = 0; i < datas.size(); i++)
		{
			temp[3 - i] = datas[i][4 - pos]; //temp[( Numero de bits - 1 )- i]
		}
		return temp;
	}
};

class LHC
{
public:
	vector<pair<bitset<4>, LHC*>> DatosEHijos;
	void insert(Hyperdata KPoint)
	{
		LHC* p = this;
		bitset<4> Bitstemp;
		int cont= 0;

		bool seEncontro = false;

		while (cont < 4)
		{
			//cout << "p: " << p << endl;
			seEncontro = false;
			if (p->DatosEHijos.size()==0)
			{
				cout << "esta vacio el hypercubo actual no tiene prefijos" << endl;
				pair <bitset<4>, LHC*> temporal;
				temporal.first = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont+1);
				cout << "uso de la funcion BitsEnPosXDeCadaDimDeUnDato en el nivel " << cont << " : " << temporal.first << endl;
				
				temporal.second = new LHC;
				//cout << "temporal.second: " << temporal.second << endl;
				p->DatosEHijos.push_back(temporal);
				p = temporal.second;
				cont++;
				cout << "----------------------------------------------------" << endl;
			}
			else
			{
				cout << "en el hypercubo hay datos" << endl;
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					cout << p->DatosEHijos[i].first <<" ==?"<< Bitstemp << endl;
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						cout << "encontre el prefijo en el hypercubo asi que solo bajo" << endl;
						//cout << "p antes de: " << p << " - p->DatosEHijos[i].second: " << p->DatosEHijos[i].second << endl;
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						cout << "----------------------------------------------------" << endl;
					}
				}
				if (seEncontro==false)
				{
					cout << "hay datos en el hypercubo pero no esta el prefijo" << endl;
					
					pair <bitset<4>, LHC*> temporal;
					temporal.first = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
					temporal.second = new LHC;
					p->DatosEHijos.push_back(temporal);
					cout << "inserto el prefijo que me falta : " << temporal.first << endl;
					p = temporal.second;
					cont++;
					cout << "----------------------------------------------------" << endl;
				}
			}
		}
		cout << "************************************FIN INSERT************************************" << endl;
	}

	bool search(Hyperdata KPoint)
	{
		LHC* p = this;
		bitset<4> Bitstemp;
		int cont = 0;
		int contadorSearch = 0;
		bool seEncontro = false;

		while (cont < 4)
		{
			//cout << "p: " << p << endl;
			seEncontro = false;
			if (p->DatosEHijos.size() == 0)
			{
				//cout << "esta vacio el hypercubo actual no tiene prefijos" << endl;
				return false;
			}
			else
			{
				//cout << "en el hypercubo hay datos" << endl;
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					cout << p->DatosEHijos[i].first << " ==?" << Bitstemp << endl;
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						cout << "encontre el prefijo en el hypercubo asi que solo bajo" << endl;
						//cout << "p antes de: " << p << " - p->DatosEHijos[i].second: " << p->DatosEHijos[i].second << endl;
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						contadorSearch++;
						//cout << "----------------------------------------------------" << endl;
					}
				}
				if (seEncontro == false)
				{
					//cout << "hay datos en el hypercubo pero no esta el prefijo" << endl;

					return false;
				}
			}
		}
		if (contadorSearch==4)
		{
			cout << "************************************FIN SEARCH************************************" << endl;
			return true;
		}
	}

	vector<Hyperdata> KNNQuery(int k, Hyperdata KPoint)
	{
		//primero buscar el dato que deseo sus vecinos mas cercanos guardando su camino
		//
		vector<LHC*> path;
		LHC* p = this;
		bitset<4> Bitstemp;
		int cont = 0;
		int contadorSearch = 0;
		bool seEncontro = false;



		//
	}
};

int main()
{
	LHC phtree;

	vector<int> equis = { 5,4,6,6,6,7 };
	vector<int> yes = { 1,1,8,9,11,10 };
	for (int i = 0; i < 6; i++)
	{
		bitset<4> temp1(equis[i]);
		bitset<4> temp2(yes[i]);

		vector<bitset<4>> tosend;
		tosend.push_back(temp1);
		tosend.push_back(temp2);

		Hyperdata toinsert(tosend);
		toinsert.print();
		cout << "x: " << equis[i] << " , " << "y: " << yes[i] << endl;
		phtree.insert(toinsert);
	}

	for (int i = 0; i < 6; i++)
	{
		bitset<4> temp1(equis[i]);
		bitset<4> temp2(yes[i]);

		vector<bitset<4>> tosend;
		tosend.push_back(temp1);
		tosend.push_back(temp2);

		Hyperdata to_search(tosend);
		to_search.print();
		cout << "x: " << equis[i] << " , " << "y: " << yes[i] << endl;
		cout << "phtree.search(to_search): " << phtree.search(to_search) << endl;
	}

	bitset<4> temp1(1);
	bitset<4> temp2(1);

	vector<bitset<4>> tosend;
	tosend.push_back(temp1);
	tosend.push_back(temp2);

	Hyperdata to_search(tosend);
	to_search.print();
	cout << "x: " << 1 << " , " << "y: " << 1 << endl;
	cout << "phtree.search(to_search): " << phtree.search(to_search) << endl;
}