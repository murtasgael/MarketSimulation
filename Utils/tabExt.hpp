#include "utilsException.hpp"

template<typename T> TabExt<T>::TabExt(){
    tab = new T[1];
    size=0;
    alloc=1;}

template<typename T> TabExt<T>::TabExt(size_t n){
    TabExtException::constructorCheck(n,std::source_location::current());
    tab = new T[n];
    size=n;
    alloc=n;}

template<typename T> TabExt<T>::TabExt(const TabExt<T> & A) : tab(new T[A.size]), size(A.size), alloc(size){
    for(size_t i=0;i<size;i++){
        tab[i]=A.tab[i];
    }
}

template<typename T> TabExt<T>::~TabExt(){ delete[] tab;}

template<typename T> T& TabExt<T>::get(const size_t & i)
{
  TabExtException::accessCheck(this, std::source_location::current(), size, alloc, i);
  return tab[i-1];
}

template<typename T> const T& TabExt<T>::getConst(const size_t & i) const  
{
  TabExtException::accessCheck(this, std::source_location::current(), size, alloc, i);
  return tab[i-1];}

template<typename T> T TabExt<T>::getCopie(const size_t & i) const  
{
  TabExtException::accessCheck(this, std::source_location::current(), size, alloc, i);
  return tab[i-1];
}

template<typename T> size_t TabExt<T>::taille()const {
    return size;}


template<typename T> void TabExt<T>::extend(){
  if (size < alloc) return;
  alloc=2*size;
  T* tmp = new T[alloc];
  for(size_t i=0;i<size;i++){tmp[i]=tab[i];}
  delete[] tab;
  tab=tmp;
}

template<typename T> void TabExt<T>::ajouterElement(const T& C){
  extend();
  tab[size]=C;
  size++;
}

template<typename T> TabExt<T>& TabExt<T>::operator+(const T& A){
    ajouterElement(A);
  return *this;}

template<typename T> void TabExt<T>::suprimerElement(const size_t & e){
    if (e>0 && e<=size){
    for(size_t i=e;i<size-1;i++)
      tab[i]=tab[i+1];
    size--;
  }
}
 
