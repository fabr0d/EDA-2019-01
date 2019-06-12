#include "rtree.h"


//implementacion
template<class T>
CRTree<T>::CRTree(int max,int x_min, int y_min, int x_max, int y_max )
  :crt_M(max), crt_x_min(x_min), crt_y_min(y_min), crt_x_max(x_max), crt_y_max(y_max)
{
  crt_root = new CRTreeNode<T>;
}



//---------------------------funcion insertar------------------------------//

template<class T>
bool CRTree<T>::insert_point(CPoint<T> x)
{
  //I1 Encontramos la posicion para el nuevo record
  vector<pair< CRTreeNode<T> *,int > > path;
  choose_leaf(x,path);
  //verificamos que p no contenga el mismo punto
  for(int i=0;i<path[path.size()-1].first->crtn_points.size();i++)
    if(x.coord == path[path.size()-1].first->crtn_points[i].coord)
      return 0;
  //cout << "sds" << endl;
  //I2 agregamos registro
  path[path.size()-1].first->crtn_points.push_back(x);

  //hacemos la verificacione ocn la funcion adjustTree
  adjust_tree(path);
  //cout << "num" << endl;

  return 1;
}


//funcion para elegir la posicion a insertar el dato nuevo, tambien devuelve el camino por donde ha transitado
template<class T>
void CRTree<T>::choose_leaf(CPoint<T> x,vector<pair< CRTreeNode<T> *,int > > &path)
{
  T min_distance,actual_distance;
  int pivot;

  CRTreeNode<T> *p;
  for(p = crt_root;!p->is_leaf(); p = p->crtn_children_pointers[pivot])
  {
    pivot =0;
    min_distance = p->crtn_mbr[0].calc_enlargement(x);
    for(int i=1;i <p->crtn_mbr.size();i++)
    {
      actual_distance = p->crtn_mbr[i].calc_enlargement(x);
      if(actual_distance == min_distance)
      {
        if(p->crtn_mbr[pivot].calc_area() > p->crtn_mbr[i].calc_area()) pivot = i;
      }
      else if(actual_distance < min_distance)
      {
        pivot = i;
        min_distance = actual_distance;
      }
    }
    path.push_back(make_pair(p,pivot));
  }
  path.push_back(make_pair(p,p->crtn_points.size()));

}



//-------------------------------funcion Split--------------------------------//
template<class T>
void CRTree<T>::quadratic_split(CRTreeNode<T> *s,CRTreeNode<T> * p,int pc)
{
  CMbr<T> seed_rect1,seed_rect2;
  int seed_pivots[2];
  int m = ceil(crt_M/2);
  double area1,area2,enlargement1,enlargement2;
  bool option; //0 es s 1 nn

  //split del root
  if(s == p )
  {
    CRTreeNode<T> *new_root = new CRTreeNode<T>;
    new_root->crtn_leaf = 0;
    p = crt_root = new_root;
    p->insert_mbr(seed_rect1,s,0);
  }


  //inicialization
  pick_seeds(s,seed_rect1,seed_rect2,seed_pivots);

  CRTreeNode<T> *nn = new CRTreeNode<T>();
  p->crtn_mbr[pc] =seed_rect1; ///////////////////////////////////////////
  p->insert_mbr(seed_rect2,nn,pc+1);


  if(s->is_leaf())
  {
    CRTreeNode<T>  aux_points;
    aux_points.crtn_points = s->crtn_points;

    s->crtn_points.clear();

    s->insert_point(aux_points.crtn_points[seed_pivots[0]]);
    nn->insert_point(aux_points.crtn_points[seed_pivots[1]]);


	///////////////////////////////////////////////////////////////////////
	if (seed_pivots[0] < seed_pivots[1])
	{
		aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[1]);
		aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[0]);
	}
	else
	{
		aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[0]);
		aux_points.crtn_points.erase(aux_points.crtn_points.begin() + seed_pivots[1]);
	}


	///////////////////////////////////////////////////////////////////////////

    int pos;
    while(s->crtn_points.size() <= m and nn->crtn_points.size() <= m)
    {
      pick_next(&aux_points,pos,seed_rect1,seed_rect2);
      enlargement1 = seed_rect1.calc_enlargement(aux_points.crtn_points[pos]);
      enlargement2 = seed_rect2.calc_enlargement(aux_points.crtn_points[pos]);
      if( enlargement1 == enlargement2 )
      {
        area1 = seed_rect1.calc_area();
        area2 = seed_rect2.calc_area();
        if(area1 == area2)
        {
          if(s->crtn_points.size() <=  nn->crtn_points.size())
            option = 0;
          else
            option = 1;
        }
        else
        {
          if(area1 < area2)
            option = 0;
          else
            option = 1;
        }
      }
      else if(enlargement1 < enlargement2)
        option = 0;
      else
        option = 1;

      if(option)
      {
        nn->insert_point(aux_points.crtn_points[pos]);
        p->crtn_mbr[pc+1].enlargement(aux_points.crtn_points[pos]);
      }
      else
      {
        s->insert_point(aux_points.crtn_points[pos]);
        p->crtn_mbr[pc].enlargement(aux_points.crtn_points[pos]);
      }
      aux_points.crtn_points.erase(aux_points.crtn_points.begin()+pos);

    }

    if(s->crtn_points.size() >= m)
    {
      for(int i =0;i<aux_points.crtn_points.size();i++)
        p->crtn_mbr[pc+1].enlargement(aux_points.crtn_points[i]);
      nn->crtn_points.insert(nn->crtn_points.end(),aux_points.crtn_points.begin(),aux_points.crtn_points.end());
    }
    else
    {
      for(int i=0;i<aux_points.crtn_points.size();i++)
        p->crtn_mbr[pc].enlargement(aux_points.crtn_points[i]);
      s->crtn_points.insert(s->crtn_points.end(),aux_points.crtn_points.begin(),aux_points.crtn_points.end());
    }


  }//fin del if-----------------------------------------------
  else
  {
    nn->crtn_leaf = 0; //hacemos que el nodo derecho sea nodo no hoja
    CRTreeNode<T>  aux_points;
    aux_points.crtn_leaf = false;
    aux_points.crtn_mbr = s->crtn_mbr;
    aux_points.crtn_children_pointers = s->crtn_children_pointers;
    s->crtn_mbr.clear();
    s->crtn_children_pointers.clear();

    s->insert_mbr(aux_points.crtn_mbr[seed_pivots[0]],aux_points.crtn_children_pointers[seed_pivots[0]],0);
    nn->insert_mbr(aux_points.crtn_mbr[seed_pivots[1]],aux_points.crtn_children_pointers[seed_pivots[1]],0);

    aux_points.crtn_mbr.erase(aux_points.crtn_mbr.begin()+seed_pivots[0]);
    aux_points.crtn_children_pointers.erase(aux_points.crtn_children_pointers.begin()+seed_pivots[0]);

    if(seed_pivots[0]<seed_pivots[1])
      seed_pivots[1]--;

    aux_points.crtn_mbr.erase(aux_points.crtn_mbr.begin()+seed_pivots[1]);
    aux_points.crtn_children_pointers.erase(aux_points.crtn_children_pointers.begin()+seed_pivots[1]);

    int pos;

    while(s->crtn_mbr.size() < m and nn->crtn_mbr.size() < m)
    {
      pick_next(&aux_points,pos,seed_rect1,seed_rect2);
      enlargement1 = seed_rect1.calc_enlargement(aux_points.crtn_mbr[pos]);
      enlargement2 = seed_rect2.calc_enlargement(aux_points.crtn_mbr[pos]);
      if( enlargement1 == enlargement2 )
      {
        area1 = seed_rect1.calc_area();
        area2 = seed_rect2.calc_area();
        if(area1 == area2)
        {
          if(s->crtn_mbr.size() <=  nn->crtn_mbr.size())
            option = 0;
          else
            option = 1;
        }
        else if(area1 < area2)
          option = 0;
        else
          option = 1;
        }
        else if(enlargement1 < enlargement2)
          option = 0;
        else
          option = 1;

        if(option)
        {
          nn->insert_mbr(aux_points.crtn_mbr[pos],aux_points.crtn_children_pointers[pos]);
          p->crtn_mbr[pc+1].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[0]);
          p->crtn_mbr[pc+1].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[1]);
        }
        else
        {
          s->insert_mbr(aux_points.crtn_mbr[pos],aux_points.crtn_children_pointers[pos]);
          p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[0]);
          p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[pos].cmbr_esq[1]);
        }
        aux_points.crtn_mbr.erase(aux_points.crtn_mbr.begin()+pos);
        aux_points.crtn_children_pointers.erase(aux_points.crtn_children_pointers.begin()+pos);
      }

    if(s->crtn_mbr.size() >= m)
    {
      for(int i =0;i<aux_points.crtn_mbr.size();i++)
      {
        p->crtn_mbr[pc+1].enlargement(aux_points.crtn_mbr[i].cmbr_esq[0]);
        p->crtn_mbr[pc+1].enlargement(aux_points.crtn_mbr[i].cmbr_esq[1]);

      }
      nn->crtn_mbr.insert(nn->crtn_mbr.end(),aux_points.crtn_mbr.begin(),aux_points.crtn_mbr.end());
      nn->crtn_children_pointers.insert(nn->crtn_children_pointers.end(),aux_points.crtn_children_pointers.begin(),aux_points.crtn_children_pointers.end());
    }
    else
    {
      for(int i=0;i<aux_points.crtn_mbr.size();i++)
      {
        p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[i].cmbr_esq[0]);
        p->crtn_mbr[pc].enlargement(aux_points.crtn_mbr[i].cmbr_esq[1]);

      }
      s->crtn_mbr.insert(s->crtn_mbr.end(),aux_points.crtn_mbr.begin(),aux_points.crtn_mbr.end());
      s->crtn_children_pointers.insert(s->crtn_children_pointers.end(),aux_points.crtn_children_pointers.begin(),aux_points.crtn_children_pointers.end());
    }

  }

}



template<class T>
void CRTree<T>::pick_seeds(CRTreeNode<T> *p ,CMbr<T> &rect1, CMbr<T> &rect2,int (&pivots)[2])
{
  double area=0,aux_area;
  CMbr<T> rect_compare;
  int pivot1,pivot2;

  if(p->is_leaf())
  {
    //evaluamos con todos los puntos
    for(int i=0;i<p->crtn_points.size()-1;i++)
    {
      rect_compare.cmbr_esq[0] = p->crtn_points[i];

      for(int j=i+1;j<p->crtn_points.size();j++)
      {
        rect_compare.cmbr_esq[1] = p->crtn_points[j];
        aux_area = rect_compare.calc_area();

        if(aux_area > area)
        {
          pivot1 = i;
          pivot2 = j;
          area = aux_area;
        }
      }
    }
    //aqui creamos los dos rectangulos con los dos pivotes que son los puntos que forman el area mas grande
    rect1.cmbr_esq[0] = p->crtn_points[pivot1];
    rect1.cmbr_esq[1] = p->crtn_points[pivot1];
    rect2.cmbr_esq[0] = p->crtn_points[pivot2];
    rect2.cmbr_esq[1] = p->crtn_points[pivot2];
  }
  else
  {

    for(int i=0;i<p->crtn_mbr.size()-1;i++)
    {
      for(int j=i+1;j<p->crtn_mbr.size();j++)
      {
        rect_compare = p->crtn_mbr[i];
        rect_compare.enlargement(p->crtn_mbr[j].cmbr_esq[0]);
        rect_compare.enlargement(p->crtn_mbr[j].cmbr_esq[1]);
        aux_area = abs(rect_compare.calc_area() - p->crtn_mbr[i].calc_area() - p->crtn_mbr[j].calc_area());
        if(aux_area > area)
        {
          pivot1 = i;
          pivot2 = j;
          area = aux_area;
        }
      }
    }

    rect1 = p->crtn_mbr[pivot1];
    rect2 = p->crtn_mbr[pivot2];
  }

  pivots[0] = pivot1;
  pivots[1] = pivot2;
  //eliminamos los puntos evaluados
  //p->crtn_points.erase(p->crtn_points.begin()+pivot1);
  //p->crtn_points.erase(p->crtn_points.begin()+pivot2);

}

template<class T>
void CRTree<T>::pick_next(CRTreeNode<T> *p,int &pivot,CMbr<T> rect1, CMbr<T> rect2)
{
  double area1,area2,max;
  max = 0;
  pivot = 0;

  if(p->is_leaf())
  {
    for(int i=0;i<p->crtn_points.size();i++)
    {
      area1 =rect1.calc_enlargement(p->crtn_points[i]);
      area2 =rect2.calc_enlargement(p->crtn_points[i]);
      if(max < abs(area1 - area2 ))
      {
        pivot =i;
        max = abs(area1 - area2);
      }
    }
  }
  else
  {
    CMbr<T> mbr_aux;
    for(int i=0;i<p->crtn_mbr.size();i++)
    {
      mbr_aux = rect1;
      mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[0]);
      mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[1]);
      area1 = mbr_aux.calc_area() - rect1.calc_area();

      mbr_aux = rect2;
      mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[0]);
      mbr_aux.enlargement(p->crtn_mbr[i].cmbr_esq[1]);
      area2 = mbr_aux.calc_area() - rect2.calc_area();

      if( abs(area1 - area2 ) > max)
      {
        pivot =i;
        max = abs(area1 - area2);
      }
    }
  }
}

//----------------------------funcion adjust_tree---------------------------//
template<class T>
void CRTree<T>::adjust_tree(vector<pair< CRTreeNode<T> *,int > > &path)
{

  for(int i=path.size()-1;i>0;i--)
  {
    if(path[i].first->crtn_mbr.size()>crt_M or path[i].first->crtn_points.size()> crt_M)
    {
      quadratic_split(path[i].first,path[i-1].first,path[i-1].second);
    }
    else
    {
      if( i == path.size()-1)
      {
        path[i-1].first->crtn_mbr[path[i-1].second].enlargement(path[i].first->crtn_points[path[i].second]);
      }
      else
      {
        path[i-1].first->crtn_mbr[path[i-1].second].enlargement(path[i].first->crtn_mbr[path[i].second].cmbr_esq[0]);
        path[i-1].first->crtn_mbr[path[i-1].second].enlargement(path[i].first->crtn_mbr[path[i].second].cmbr_esq[1]);
      }
    }
  }
  if(path[0].first->crtn_mbr.size()>crt_M or path[0].first->crtn_points.size()> crt_M)
  {
    quadratic_split(path[0].first,path[0].first,0);
  }
}

//---------------------------funcion busquedad------------------------------//

template<class T>
void CRTree<T>::find_by_region(CRTreeNode<T> *p,CMbr<T> rect,vector<CPoint<T> > &points_vec)
{

  if(p->is_leaf())
  {
    for(int i=0;i<p->crtn_points.size();i++)
    {
      if(rect.contiene(p->crtn_points[i]))
        points_vec.push_back(p->crtn_points[i]);
    }
    return;
  }

  for(int i=0;i<p->crtn_mbr.size();i++)
  {
    CPoint<T> esq1_mbr(p->crtn_mbr[i].cmbr_esq[0].coord[0],p->crtn_mbr[i].cmbr_esq[1].coord[1]);
    CPoint<T> esq2_mbr(p->crtn_mbr[i].cmbr_esq[1].coord[0],p->crtn_mbr[i].cmbr_esq[0].coord[1]);

    CPoint<T> esq1_rect(rect.cmbr_esq[0].coord[0],rect.cmbr_esq[1].coord[1]);
    CPoint<T> esq2_rect(rect.cmbr_esq[1].coord[0],rect.cmbr_esq[0].coord[1]);

    if(rect.contiene(p->crtn_mbr[i].cmbr_esq[0]) or rect.contiene(p->crtn_mbr[i].cmbr_esq[1]) or rect.contiene(esq1_mbr) or rect.contiene(esq2_mbr)
       or p->crtn_mbr[i].contiene(rect.cmbr_esq[0]) or p->crtn_mbr[i].contiene(rect.cmbr_esq[1]) or p->crtn_mbr[i].contiene(esq1_rect) or p->crtn_mbr[i].contiene(esq2_rect))
    {
      find_by_region(p->crtn_children_pointers[i],rect,points_vec);
    }
  }


}




///////-----------------------funcion imprimir------------------------------///
template<class T>
void CRTree<T>::print()
{
  vector<CRTreeNode<T> *> tail;
  tail.push_back(crt_root);
  int j = 0;
  int rects =0;
  while(j <tail.size())
  {
    for(int i=0;i<tail[j]->crtn_mbr.size();i++)
      tail.push_back(tail[j]->crtn_children_pointers[i]);
    j++;
  }

  for(int i=0;i < tail.size();i++)
  {
    if(tail[i]->is_leaf())
    {
      for(int n=0;n<tail[i]->crtn_points.size();n++)
      {
        //cout << tail[i]->crtn_points[n] << endl;
      }
    }
    else
    {
      for(int n=0;n<tail[i]->crtn_mbr.size();n++)
      {
        //cout << tail[i]->crtn_mbr[n] << endl;
        rects++;
      }
    }
  }
  cout << rects << endl;
}


template<class T>
void CRTree<T>::drawTree()
{
  vector<CRTreeNode<T> *> tail;
  tail.push_back(crt_root);
  int j = 0;
  while(j <tail.size())
  {
    for(int i=0;i<tail[j]->crtn_mbr.size();i++)
      tail.push_back(tail[j]->crtn_children_pointers[i]);
    j++;
  }

  for(int i=0;i < tail.size();i++)
  {
    if(tail[i]->is_leaf())
    {
      for(int n=0;n<tail[i]->crtn_points.size();n++)
      {
        			glPointSize(1.0);
        			glBegin(GL_POINTS);
        			glColor3f(0.0,1.0,0.0);
        			glVertex2f(tail[i]->crtn_points[n].coord[0],tail[i]->crtn_points[n].coord[1]);
        			glEnd();
      }
    }
    else
    {
      for(int n=0;n<tail[i]->crtn_mbr.size();n++)
      {
        tail[i]->crtn_mbr[n].draw();
      }
    }
  }
}
