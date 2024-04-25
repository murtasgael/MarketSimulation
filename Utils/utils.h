#ifndef UTILS
#define UTILS
#include <iostream>
#include <fstream>
#include "../Exception/exception.h"
//#include "../Trading/trading.h"

template<typename T> class TabExtError;
//tableau générique ultra rapide (une fois terminé x))
template<typename T>
class TabExt {
    protected:
      T * tab;//les données stocker dans un tableau standard
      size_t   size;//taille des données écrites
      size_t   alloc;//tailles du tableau alloué en mémoire

      void extend();//double la mémoire alloué
 
 public:
  TabExt();
  TabExt(size_t);
  TabExt(const TabExt<T> &);
  ~TabExt();
  //TabExt& operator=(const tabExt&);
  
  //accesseur !!! Indice de 1 à n !!!
  T& get (const size_t &);
  const T&  getConst (const size_t &) const;
  T  getCopie (const size_t &) const;

  //size_t  RechercherElement(const T&); // return the position of the element or -1
  size_t taille()const;  
  void ajouterElement(const T&); // add an element at the end (possibly extend array) 
  TabExt& operator + (const T&); // mm chose que AjouterElement
  void suprimerElement(const size_t &);          // remove the element at the given position
  
  //friend class TabExt2Error<T>;
  friend class TabExtException;
};

//tableau dynamique en dimension 2
template<typename T> class TabExt2 : private TabExt<T>
{
    using TabExt<T>::TabExt;

  private:
    size_t nbl;//nombre de ligne
    size_t nbc;//nombre de colonnes
    
  public:
    TabExt2(const TabExt<T> &);
    TabExt2(const size_t &, const size_t &);
    
    //accesseur
    T& get(const size_t &, const size_t &);
    T getCopie(const size_t &, const size_t &) const;
    size_t nLines() const;
    size_t nCols() const;

  friend class TabExtError<T>;
};

//feuille de donné pouvant lire et écrire en csv
class Table : public TabExt2<std::string>
{
    using TabExt2<std::string>::TabExt2;

    private:
    char dl,dc,df;//les délimiteur de lignes et colonnes pour les entrer ou sorties, ainsi que la valeur par défault des donnée vides
    
    std::string toString() const;//Renvoi un string avec tout le contenu de la table

  public :
    Table(const TabExt2<std::string> &);
    Table(const size_t &, const size_t &);
    //construction à partir du contenu d'un fichier
    Table(const std::string &);// délimiteur '\n', ',' et ' ' par défault
    Table(const std::string & path, const char &, const char &, const char &);
    void CSV(const std::string &) const;//écriture du contenue dans un fichier format csv
    void affiche() const;
};

/*
 * FONCTIONS UTILITAIRES
 */

//revoi un string avec le contenu d'un ficher
std::string readFile(const std::string &);

//nombre de lignes d'un fichier delL de délimiteur des lignes
size_t getFileLines( const std::string & path, const char & delL);//nombre de lignes d'un fichier delL de délimiteur des lignes
size_t getFileCols( const std::string & path, const char & delL, const char & delC);

#include "tabExt.hpp"
#include "tabExt2.hpp"
#endif
