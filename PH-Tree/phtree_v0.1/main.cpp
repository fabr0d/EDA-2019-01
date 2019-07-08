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

	//bool Isleaf = false;
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
			//cout << "p: " << p << endl;
			seEncontro = false;
			if (p->DatosEHijos.size() == 0)
			{
				//cout << "esta vacio el hypercubo actual no tiene prefijos" << endl;
				pair <bitset<64>, LHC*> temporal;
				temporal.first = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				//cout << "uso de la funcion BitsEnPosXDeCadaDimDeUnDato en el nivel " << cont << " : " << temporal.first << endl;

				temporal.second = new LHC;
				//cout << "temporal.second: " << temporal.second << endl;
				p->DatosEHijos.push_back(temporal);
				p->IsVisited.push_back(false);
				p = temporal.second;
				cont++;
				//cout << "----------------------------------------------------" << endl;
			}
			else
			{
				//cout << "en el hypercubo hay datos" << endl;
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					//cout << p->DatosEHijos[i].first << " ==?" << Bitstemp << endl;
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						//cout << "encontre el prefijo en el hypercubo asi que solo bajo" << endl;
						//cout << "p antes de: " << p << " - p->DatosEHijos[i].second: " << p->DatosEHijos[i].second << endl;
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						break;
						//cout << "----------------------------------------------------" << endl;
					}
				}
				if (seEncontro == false)
				{
					//cout << "hay datos en el hypercubo pero no esta el prefijo" << endl;

					pair <bitset<64>, LHC*> temporal;
					temporal.first = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
					temporal.second = new LHC;
					p->DatosEHijos.push_back(temporal);
					//cout << "inserto el prefijo que me falta : " << temporal.first << endl;
					p->IsVisited.push_back(false);
					p = temporal.second;
					cont++;
					//cout << "----------------------------------------------------" << endl;
				}
			}
		}
		//cout << "************************************FIN INSERT************************************" << endl;
	}

	bool search(Hyperdata KPoint)
	{
		//cout << "*********************inicio serach*********************" << endl;
		LHC* p = this;
		bitset<64> Bitstemp;
		int cont = 0;
		int contadorSearch = 0;
		bool seEncontro = false;

		while (cont < 64)
		{
			//cout << "lvl: " << cont << endl;
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

				int i = 0;
				/*while (i < p->DatosEHijos.size())
				{
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
					i++;
				}*/

				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					//cout << p->DatosEHijos[i].first << " ==?" << Bitstemp << endl;
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						//cout << "encontre el prefijo en el hypercubo asi que solo bajo" << endl;
						//cout << "p antes de: " << p << " - p->DatosEHijos[i].second: " << p->DatosEHijos[i].second << endl;
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						contadorSearch++;
						break;
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
		if (contadorSearch == 64)
		{
			//cout << "******************FIN SEARCH*****************" << endl;
			return true;
		}
	}

	vector<vector < bitset<64> > > KNNQuery(int k, Hyperdata KPoint)
	{
		//
		vector<vector<bitset<64>>> knn;
		//
		//vector de bitsets para reconstruir un HD
		vector<bitset<64>> toRec;
		//
		//primero buscar el dato que deseo sus vecinos mas cercanos guardando su camino
		//
		vector<pair<LHC*, int>> path;

		LHC* p = this;
		bitset<64> Bitstemp;
		int cont = 0;
		int contadorSearch = 0;
		bool seEncontro = false;

		while (cont < 64)
		{
			//cout << "p: " << p << endl;
			seEncontro = false;
			if (p->DatosEHijos.size() == 0) 
			{ 
				//cout << "no esta el valor, nivel sin datos" << endl; 
				return knn; 
			}
			else
			{
				//cout << "en el hypercubo hay datos" << endl;
				Bitstemp = KPoint.BitsEnPosXDeCadaDimDeUnDato(cont + 1);
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					//cout << p->DatosEHijos[i].first << " ==?" << Bitstemp << endl;
					if (p->DatosEHijos[i].first == Bitstemp)
					{
						toRec.push_back(Bitstemp);
						//cout << "encontre el prefijo en el hypercubo asi que solo bajo" << endl;

						pair<LHC*, int> PathTemp;
						PathTemp.first = p;
						PathTemp.second = i;
						path.push_back(PathTemp);
						p->IsVisited[i] = true;

						//cout << "p antes de: " << p << ", ahora tendra la direccion de:  " << p->DatosEHijos[i].second << endl;
						p = p->DatosEHijos[i].second;
						cont++;
						seEncontro = true;
						contadorSearch++;
						break;
						//cout << "----------------------------------------------------" << endl;
					}
				}
				if (seEncontro == false) 
				{ 
					//cout << "no esta el valor , habian datos en el hypercubo pero no el prefijo que queria" << endl; 
					return knn;
				}
			}
		}
		if (contadorSearch == 64)
		{
			//cout << "se encontro el dato" << endl;
			/*
			for (int i = 0; i < path.size(); i++)
			{
				cout << "su respectivo direccion: " << path[i].first << " , su pos en el vector DatosEHijos: " << path[i].second << endl;
			}*/
		}
		//
		//paso a preguntar en el ultimo nivel si tiene mas de el valor encontrado
		p = path[path.size() - 1].first;
		//cout << "p: " << p << endl;
		//cout << "p->DatosEHijos.size(): " << p->DatosEHijos.size() << endl;


		if (p->DatosEHijos.size() > 1)
		{
			//printBoolVec(p->IsVisited);
			for (int i = 0; i < p->DatosEHijos.size(); i++)
			{
				if (p->IsVisited[i] == false)
				{
					toRec[63] = p->DatosEHijos[i].first;
					vector<bitset<64>> recons = reconstructHD(toRec);
					knn.push_back(recons);
					//cout << "encontre un knn !!!!!!! : " << knn.size() << endl;
					p->IsVisited[i] = true;
				}
			}

			//cout << "los vecinos mas cercanos encontrados en el mismo ultimo hypercubo" << endl;
			/*for (int a = 0; a < knn.size(); a++)
			{
				printBitVec(knn[a]);
			}*/
		}
		if (knn.size() < k)
		{
			//cout << "------me faltan knns :s ---------" << endl;
			int altura = 64 - 1; // numero de bits -1
			//cout << "p que apunta al hijo donde encontre los primeros knn: " << p << endl;
			path.pop_back();
			//cout << "borro el la ultima direccion porque es donde encontre los knn rapidos" << endl;
			//cout << "imprimo el path que ma queda:" << endl;
			/*for (int i = 0; i < path.size(); i++)
			{
				cout << "su respectivo direccion: " << path[i].first << " , su pos en el vector DatosEHijos: " << path[i].second << endl;
			}*/
			//cout << "p ya apunta a en penultino hypercubo" << endl;
			p = path[path.size() - 1].first;
			//cout << "p: " << p << endl;
			printBoolVec(p->IsVisited);

			while (knn.size() < k)
			{
				//cout << "altura : " << altura << endl;
				//cout << "paso para verificar si en el hypercubo que estoy ya todos fueron visitados" << endl;
				//printBoolVec(p->IsVisited);
				int contabuls = 0;
				for (int i = 0; i < p->DatosEHijos.size(); i++)
				{
					//cout << "test: " << p->IsVisited[i] << endl;
					if (p->IsVisited[i] == true)
					{
						contabuls++;
					}
				}

				if (contabuls == p->DatosEHijos.size()) //si todos fueron visitados subo un nivel en el arbol
				{
					//cout << "si todos fueron visitados subo un nivel en el arbol" << endl;
					//cout << "p actual: " << p << endl;
					path.pop_back();
					/*for (int i = 0; i < path.size(); i++)
					{
						cout << "su respectivo direccion: " << path[i].first << " , su pos en el vector DatosEHijos: " << path[i].second << endl;
					}*/
					p = path[path.size() - 1].first;
					//cout << "nuevo p: " << p << endl;
					altura--;
				}
				else // si no todos fueron visitados
				{
					//cout << "en el nivel donde estoy aun hay por visitar: " << endl;
					//printBoolVec(p->IsVisited);

					bool UltimoLvl = false;
					//cout << "paso a verificar cuales no estan visitados de un total de " << DatosEHijos.size() << "elementos " << endl;
					for (int i = 0; i < p->DatosEHijos.size(); i++)
					{
						if (p->IsVisited[i] == false)
						{
							//cout << "si no esta visitado" << endl;
							toRec[altura - 1] = p->DatosEHijos[i].first; //modifico el prefijo
							if (altura == 64) //estoy en las hojas // numero de bits
							{
								//cout << "si estoy en el ultimo nivel del arbol" << endl;
								UltimoLvl = true;
								vector<bitset<64>> recons = reconstructHD(toRec);
								knn.push_back(recons);
								//cout << "pucheo un knn nuevo :D" << endl;
								p->IsVisited[i] = true;
								if (knn.size() >= k)
								{
									return knn;
								}
							}
							else //bajo
							{
								//cout << "tengo que bajar un nivel porque no estoy en una hoja, marco como visitado y bajo" << endl;
								p->IsVisited[i] = true;
								//cout << "p antes de bajar: " << p << ", ahora tendra la direccion de un nodo mas abajo:  " << p->DatosEHijos[i].second << endl;
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
					if (UltimoLvl == true) //si recorri ya todo una hoja
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

	
	//data set de year prediccion de 90 dimensiones y cada num * 10 000 para evitar decimales - 515345 puntos k dim
	vector<Hyperdata> NDimDatas;

	for (int i = 0; i < 999999999; i++)
	{
		//cout << "i: " << i << endl;
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

		//printIntVec(nums);
		NDimDatas.push_back(toinsert);
		
		//printBitVec(toinsert.datas);
		
	}
	file.close();
	cout << "numero de datos: " << NDimDatas.size() << endl;

	auto start = chrono::steady_clock::now();
	for (size_t i = 0; i < NDimDatas.size(); i++)
	{
		phtree.insert(NDimDatas[i]);
		//cout << "se inserto id " <<i<< endl;
	}
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	cout << "fin del insert" << endl;


	cout << "ahora el find  test" << endl;///////////////////////////////////////////////

	int contB = 0;

	fstream fileB;
	int numB;
	string filenameB;
	filenameB = "C:\\Users\\Fabrizio\\source\\repos\\tests\\DataSetRand.txt";
	fileB.open(filenameB.c_str());

	vector<Hyperdata> NDimDatasB;

	for (int i = 0; i < 4; i++)
	{
		cout << "i: " << i << endl;
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
		//printBitVec(toinsert.datas);

	}
	fileB.close();

	cout << "numero de datos: " << NDimDatasB.size() << endl;

	auto startB = chrono::steady_clock::now();
	for (size_t i = 0; i < NDimDatasB.size(); i++)
	{
		cout << "phtree.search(NDimDatasB[i]): " << phtree.search(NDimDatasB[i]) << endl;
		cout << "se busco id " << i << endl;
	}
	auto endB = chrono::steady_clock::now();
	auto diffB = endB - startB;
	cout << chrono::duration <double, milli>(diffB).count() << " ms" << endl;
	cout << "fin del insert" << endl;

	cout << " FIN DEL SEARCH TEST" << endl;/////////////////////////////////////////////

	cout << "TEST DE LOS KNN--------------------" << endl;

	//rreuso NDimDatasB de los 4 datos que busque

	vector<vector<bitset<64>>> knns;
	auto startC = chrono::steady_clock::now();

	knns = phtree.KNNQuery(100, NDimDatasB[0]);
	cout << "numero de knn encontrados: " << knns.size() << endl;

	auto endC = chrono::steady_clock::now();
	auto diffC = endC - startC;
	cout << chrono::duration <double, milli>(diffC).count() << " ms" << endl;
	
	/*for (int i = 0; i < knns.size(); i++)
	{
		printBitVec(knns[i]);
	}*/
	
	cout << "fin del knn QUERY" << endl;
	/*
	LHC phtree;

	vector<int> equis = { 5,4,6,6,6,7,7,7 };
	vector<int> yes = { 1,1,8,9,11,10,11,3 };
	for (int i = 0; i < 8; i++)
	{
		bitset<64> temp1(equis[i]);
		bitset<64> temp2(yes[i]);

		vector<bitset<64>> tosend;
		tosend.push_back(temp1);
		tosend.push_back(temp2);

		Hyperdata toinsert(tosend);
		toinsert.print();
		cout << "x: " << equis[i] << " , " << "y: " << yes[i] << endl;
		phtree.insert(toinsert);
	}

	for (int i = 0; i < 8; i++)
	{
		bitset<64> temp1(equis[i]);
		bitset<64> temp2(yes[i]);

		vector<bitset<64>> tosend;
		tosend.push_back(temp1);
		tosend.push_back(temp2);

		Hyperdata to_search(tosend);
		to_search.print();
		cout << "x: " << equis[i] << " , " << "y: " << yes[i] << endl;
		cout << "phtree.search(to_search): " << phtree.search(to_search) << endl;
	}

	bitset<64> temp1(7);
	bitset<64> temp2(10);

	vector<bitset<64>> tosend;
	tosend.push_back(temp1);
	tosend.push_back(temp2);

	Hyperdata to_knn(tosend);
	to_knn.print();
	cout << "x: " << 7 << " , " << "y: " << 10 << endl;

	vector<vector<bitset<64>>> knns;
	knns = phtree.KNNQuery(7, to_knn);

	for (int i = 0; i < knns.size(); i++)
	{
		printBitVec(knns[i]);
	}
	*/
}