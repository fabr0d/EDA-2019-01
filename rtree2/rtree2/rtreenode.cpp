#include "rtreenode.h"

template<class T>
CRTreeNode<T>::CRTreeNode()
{
  crtn_leaf = true;
}

template<class T>
bool CRTreeNode<T>::is_leaf()
{
  return crtn_leaf;
}

template<class T>
bool CRTreeNode<T>::insert_point(CPoint<T> x)
{
  crtn_points.push_back(x);
  return 1;
}

template<class T>
bool CRTreeNode<T>::insert_mbr(CMbr<T> x,CRTreeNode<T> *p,int pos)
{
  crtn_mbr.insert(crtn_mbr.begin()+pos,x);
  crtn_children_pointers.insert(crtn_children_pointers.begin()+pos,p);
  return 1;
}

template<class T>
bool CRTreeNode<T>::insert_mbr(CMbr<T> x,CRTreeNode<T> *p)
{
  crtn_mbr.push_back(x);
  crtn_children_pointers.push_back(p);
  return 1;
}
