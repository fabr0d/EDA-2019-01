#pragma once
#ifndef RTREENODE_H
#define RTREENODE_H

#include "mbr.h"
#include "mbr.cpp"

template<class T>
class CRTreeNode
{
public:
	CRTreeNode();
	bool is_leaf();
	bool insert_point(CPoint<T> x);
	bool insert_mbr(CMbr<T> x, CRTreeNode<T>* p, int pos);
	bool insert_mbr(CMbr<T> x, CRTreeNode<T>* p);
	bool crtn_leaf;  //si es un nodo hoja o no

	template<class U> friend class CRTree;
private:

	//vector<pair<Cmbr<T> ,CRTreeNode *> > crtn_mbr_and_pointers; //rectangulos con los punteros a los hijos
	vector<CMbr<T> > crtn_mbr; // hyperrectangulos
	vector<CRTreeNode<T>* > crtn_children_pointers; //esto crece si no es nodo hoja

	vector<CPoint<T> > crtn_points; //data espacial

};

#endif
