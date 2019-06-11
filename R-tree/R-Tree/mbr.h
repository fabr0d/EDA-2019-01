#pragma once
#ifndef MBR_H
#define MBR_H

#include <vector>
#include <cmath>
#include <GL/glut.h>
using namespace std;

#include "point.h"
#include "point.cpp"

///-------------------------------clase Mbr--------------------------------///
template<class T>
class CMbr
{
public:
	CPoint<T> cmbr_esq[2];

	CMbr(CPoint<T>, CPoint<T>); //constructor
	CMbr() {}

	bool contiene(CPoint<T>); //verifica si el rectaqngulo contiene a un punto
	double calc_area();
	double calc_enlargement(CPoint<T>); //calcula cuanto se alarga un rectangulo con un punto dado
	double calc_enlargement(CMbr<T>); //calcula cuanto se alarga con un rectangulo dado
	bool enlargement(CPoint<T>); //alarga el rectangulo a un punto dado
	void print();
	void draw(); //dibuja el rectangulo
	void draw(int, int, int); //dibuja el rectangulo con colores definidps

	template<class U>friend ostream& operator<<(ostream&, const CMbr<U>&);
};

#endif
