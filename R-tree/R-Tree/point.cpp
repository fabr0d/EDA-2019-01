#include "point.h"

template<class T>
CPoint<T>::CPoint(vector<T> a)
{
	coord = a;
}
template<class T>
CPoint<T>::CPoint(T x, T y)
{
	coord.push_back(x);
	coord.push_back(y);
}

template<class T>
ostream& operator<<(ostream& os, const CPoint<T>& cp)
{
	os << " ( ";
	for (int i = 0; i < cp.coord.size(); i++)
		os << cp.coord[i] << ",";
	os << ")";
	return os;
}
