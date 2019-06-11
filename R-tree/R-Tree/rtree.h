#pragma once

#ifndef RTREE_H
#define RTREE_H

#include <math.h>
#include "rtreenode.h"
#include "rtreenode.cpp"

using namespace std;

template<class T>
class CRTree
{
public:
	CRTree(int, int, int, int, int);
	CRTree() {}

	bool find_point(T x, CRTreeNode<T>*& p);

	//-funciones usadas en la insercion y auxiliares
	bool insert_point(CPoint<T>);
	void choose_leaf(CPoint<T>, vector<pair< CRTreeNode<T>*, int > >&);
	void quadratic_split(CRTreeNode<T>*, CRTreeNode<T>*, int);
	void pick_seeds(CRTreeNode<T>*, CMbr<T>&, CMbr<T>&, int(&)[2]);
	void pick_next(CRTreeNode<T>*, int&, CMbr<T>, CMbr<T>);
	void adjust_tree(vector<pair< CRTreeNode<T>*, int > >&);
	// funcion busuqeda por region
	void find_by_region(CRTreeNode<T>*, CMbr<T>, vector<CPoint<T> >&);

	//funcion print
	void print();
	void drawTree();

	CRTreeNode<T>* crt_root;
private:
	int crt_M;
	int crt_x_min, crt_y_min, crt_x_max, crt_y_max;

};



#endif
