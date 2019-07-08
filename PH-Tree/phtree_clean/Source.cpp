#include <iostream>
#include <chrono>
#include <vector>
#include <bitset>
#include <map>
#include <utility> 
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;
int N_bits = 4;

void printIntVec(vector<int> test)
{
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i] << ", ";
	}
	cout << "" << endl;
}

void printBoolVec(vector<bool> test)
{
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i] << ", ";
	}
	cout << "" << endl;
}

void printBitVec(vector<bitset<64>> test)
{
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i] << ", ";
	}
	cout << "" << endl;
}

struct Hyperdata //Estructura que almacenara el elemento 64-k
{
	vector<bitset<64>> datas;
	Hyperdata(vector<bitset<64>> temp)
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
	bitset<64> BitsEnPosXDeCadaDimDeUnDato(int pos) //pos >= 1
	{
		bitset<64> temp;
		for (int i = 0; i < datas.size(); i++)
		{
			temp[63 - i] = datas[i][64 - pos]; //temp[( Numero de bits - 1 )- i]
		}
		return temp;
	}
};

vector<bitset<64>> reconstructHD(vector<bitset<64>> keane)
{
	vector<bitset<64>> rpta;
	for (int i = 0; i < keane.size(); i++)
	{
		bitset<64> temp(0);
		rpta.push_back(temp);
	}
	for (int j = 0; j < keane.size(); j++)
	{
		for (int l = 0; l < keane.size(); l++)
		{
			rpta[j][63 - l] = keane[l][j]; //rpta[j][(numero de bits -1)-l]
		}
	}
	return rpta;
}

class LHC
{
public:
	vector<pair<bitset<64>, LHC*>> DatosEHijos;
	vector<bool> IsVisited;

	void insert(Hyperdata KPoint)
	{
		LHC* p = this;
		bitset<64> Bitstemp;
		int cont = 0;
		bool seEncontro = false;
		while (cont < 64)
		{      
			seEncontro = false;
			if (p->DatosEHijos.size() == 0)
			{
				pair <bitset<64>, LHC*> temporal;
				temporal.first = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				temporal.second = new LHC;
				p->DatosEHijos.push_back(temporal);
				p->IsVisited.push_back(false);
				p = temporal.second;
				cont++;
			}
			else
			{
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						break;
					}
				}
				if (seEncontro == false)
				{
					pair <bitset<64>, LHC*> temporal;
					temporal.first = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
					temporal.second = new LHC;
					p->DatosEHijos.push_back(temporal);
					p->IsVisited.push_back(false);
					p = temporal.second;
					cont++;
				}
			}
		}
	}

	bool search(Hyperdata KPoint)
	{
		LHC* p = this;
		bitset<64> Bitstemp;
		int cont = 0;
		int contadorSearch = 0;
		bool seEncontro = false;
		while (cont < 64)
		{
			seEncontro = false;
			if (p->DatosEHijos.size() == 0)
			{
				return false;
			}
			else
			{
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						contadorSearch++;
						break;
					}
				}
				if (seEncontro == false)
				{
					return false;
				}
			}
		}
		if (contadorSearch == 64)
		{
			return true;
		}
	}

	vector<vector < bitset<64> > > KNNQuery(int k, Hyperdata KPoint)
	{
		vector<vector<bitset<64>>> knn;
		vector<bitset<64>> toRec;
		vector<pair<LHC*, int>> path;
		LHC* p = this;
		bitset<64> Bitstemp;
		int cont = 0;
		int contadorSearch = 0;
		bool seEncontro = false;
		while (cont < 64)
		{
			seEncontro = false;
			if (p->DatosEHijos.size() == 0)
			{
				return knn;
			}
			else
			{
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						toRec.push_back(Bitstemp);
						pair<LHC*, int> PathTemp;
						PathTemp.first = p;
						PathTemp.second = i;
						path.push_back(PathTemp);
						p->IsVisited[i] = true;
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						contadorSearch++;
						break;
					}
				}
				if (seEncontro == false)
				{
					return knn;
				}
			}
		}
		p = path[path.size() - 1].first;
		if (p->DatosEHijos.size() > 1)
		{
			for (int i = 0; i < p->DatosEHijos.size(); i++)
			{
				if (p->IsVisited[i] == false)
				{
					toRec[63] = p->DatosEHijos[i].first;
					vector<bitset<64>> recons = reconstructHD(toRec);
					knn.push_back(recons);
					p->IsVisited[i] = true;
				}
			}
		}
		if (knn.size() < k)
		{
			int altura = 64 - 1;
			path.pop_back();
			p = path[path.size() - 1].first;
			while (knn.size() < k)
			{
				int contabuls = 0;
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					if (p->IsVisited[i] == true)
					{
						contabuls++;
					}
				}
				if (contabuls == p->DatosEHijos.size())
				{
					path.pop_back();
					p = path[path.size() - 1].first;
					altura--;
				}
				else
				{
					bool UltimoLvl = false;
					for (int i = 0; i < p->DatosEHijos.size(); i++)
					{
						if (p->IsVisited[i] == false)
						{
							toRec[altura - 1] = p->DatosEHijos[i].first;
							if (altura == 64)
							{
								UltimoLvl = true;
								vector<bitset<64>> recons = reconstructHD(toRec);
								knn.push_back(recons);
								p->IsVisited[i] = true;
								if (knn.size() >= k)
								{
									return knn;
								}
							}
							else
							{
								p->IsVisited[i] = true;
								p = p->DatosEHijos[i].second;
								pair<LHC*, int> PathTemp2;
								PathTemp2.first = p;
								PathTemp2.second = i;
								path.push_back(PathTemp2);
								altura++;
								i = -1;
							}
						}
					}
					if (UltimoLvl == true)
					{
						path.pop_back();
						p = path[path.size() - 1].first;
						altura--;
					}
				}
			}
		}
		else
		{
			return knn;
		}
	}

};

int main()
{
	LHC phtree;
	int cont = 0;
	fstream file;
	int num;
	string filename;
	filename = "C:\\Users\\Fabrizio\\source\\repos\\tests\\DataSetRand.txt";
	file.open(filename.c_str());
	vector<Hyperdata> NDimDatas;
	for (int i = 0; i < 1000000; i++)
	{
		vector<bitset<64>> tosend;
		vector<int> nums;
		while (cont < 64)
		{
			file >> num;
			nums.push_back(num);
			bitset<64> temp(num);
			tosend.push_back(temp);
			cont++;

		}
		cont = 0;
		Hyperdata toinsert(tosend);
		NDimDatas.push_back(toinsert);
	}
	file.close();

	cout << "Inicio del insert test" << endl;
	cout << "numero de datos: " << NDimDatas.size() << endl;
	auto start = chrono::steady_clock::now();
	for (size_t i = 0; i < NDimDatas.size(); i++)
	{
		phtree.insert(NDimDatas[i]);
	}
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "tiempo del insert :";
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	cout << "Fin del insert test" << endl;
	
	cout << "Inicio del find test" << endl;
	int contB = 0;
	fstream fileB;
	int numB;
	string filenameB;
	filenameB = "C:\\Users\\Fabrizio\\source\\repos\\tests\\DataSetRand.txt";
	fileB.open(filenameB.c_str());
	vector<Hyperdata> NDimDatasB;
	for (int i = 0; i < 4; i++)
	{
		vector<bitset<64>> tosend;
		vector<int> nums;
		while (cont < 64)
		{
			fileB >> num;
			nums.push_back(num);
			bitset<64> temp(num);
			tosend.push_back(temp);
			cont++;
		}
		cont = 0;
		Hyperdata toinsert(tosend);
		printIntVec(nums);
		NDimDatasB.push_back(toinsert);
	}
	fileB.close();
	cout << "numero de datos: " << NDimDatasB.size() << endl;

	auto startB = chrono::steady_clock::now();
		cout << "phtree.search(NDimDatasB[i]): " << phtree.search(NDimDatasB[1]) << endl;
	auto endB = chrono::steady_clock::now();
	auto diffB = endB - startB;
	cout << "tiempo del find :";
	cout << chrono::duration <double, milli>(diffB).count() << " ms" << endl;
	cout << "fin del find test" << endl;

	cout << "Inicio de las pruebas de Knn query" << endl;
	vector<vector<bitset<64>>> knns;
	auto startC = chrono::steady_clock::now();
	knns = phtree.KNNQuery(100, NDimDatasB[0]);
	cout << "numero de knn encontrados: " << knns.size() << endl;
	auto endC = chrono::steady_clock::now();
	auto diffC = endC - startC;
	cout << "tiempo del knn :";
	cout << chrono::duration <double, milli>(diffC).count() << " ms" << endl;
	cout << "fin del knn QUERY" << endl;
}