#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_

#include "NodoArbol.h"
#include <iostream>

template <class T>
class ArbolBinario
{
protected:
  NodoArbol<T> *root;

public:
  ArbolBinario();

  void put(T data);

  T search(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinario();

  bool esVacio();

  void print();

  int sumarDesdeNivel(int nivel);

  int sumarNivel(int nivel);

  int LevelCounter();

  int sumarNivelPerValue(int value);

  int getLevelPerValue(int value, int *levelCatch);

  int getLevel(T v); //metodo @msmurgui

private:
  int getLevel(T v, int currentLevel, NodoArbol<T> *r); //metodo @msmurgui
  int LevelCounter(NodoArbol<T> *r, int levelCount, int *levelCatch);
  int getLevelPerValue(int value, NodoArbol<T> *r, int levelCount, int *levelCatch);
  int sumarNivel(int nivel, NodoArbol<T> *r, int *total);
  int sumarDesdeNivel(int nivel, NodoArbol<T> *r, int *total);
  T search(T data, NodoArbol<T> *r);
  NodoArbol<T> *put(T data, NodoArbol<T> *r);
  NodoArbol<T> *remove(T data, NodoArbol<T> *r);
  NodoArbol<T> *findMaxAndRemove(NodoArbol<T> *r, bool *found);
  void preorder(NodoArbol<T> *r);
  void inorder(NodoArbol<T> *r);
  void postorder(NodoArbol<T> *r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinario<T>::ArbolBinario() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinario<T>::search(T data)
{
  return search(data, root);
}

template <class T>
T ArbolBinario<T>::search(T data, NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData() == data)
  {
    return r->getData();
  }

  if (r->getData() > data)
  {
    return search(data, r->getLeft());
  }
  else
  {
    return search(data, r->getRight());
  }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolBinario<T>::put(T data) { root = put(data, root); }


template <class T> NodoArbol<T> *ArbolBinario<T>::put(T data, NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return new NodoArbol<T>(data);
  }

  if (r->getData() == data)
  {
    throw 200;
  }

  if (r->getData() > data)
  {
    r->setLeft(put(data, r->getLeft()));
  }
  else
  {
    r->setRight(put(data, r->getRight()));
  }

  return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T>
void ArbolBinario<T>::remove(T data)
{
  root = remove(data, root);
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r)
{
  NodoArbol<T> *aux;

  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData() == data)
  {

    if (r->getLeft() == nullptr && r->getRight() == nullptr)
    {
      delete r;
      return nullptr;
    }
    else if (r->getLeft() != nullptr && r->getRight() == nullptr)
    {
      aux = r->getLeft();
      delete r;
      return aux;
    }
    else if (r->getLeft() == nullptr && r->getRight() != nullptr)
    {
      aux = r->getRight();
      delete r;
      return aux;
    }
    else if (r->getLeft() != nullptr && r->getRight() != nullptr)
    {

      if (r->getLeft()->getRight() != nullptr)
      {
        // Aca tenemos que buscar el valor maximo
        bool found;
        aux = findMaxAndRemove(r->getLeft(), &found);
        aux->setRight(r->getRight());
        aux->setLeft(r->getLeft());
      }
      else
      {
        aux = r->getLeft();
        r->getLeft()->setRight(r->getRight());
      }
      delete r;
      return aux;
    }
  }
  else if (r->getData() > data)
  {
    r->setLeft(remove(data, r->getLeft()));
  }
  else
  {
    r->setRight(remove(data, r->getRight()));
  }

  return r;
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::findMaxAndRemove(NodoArbol<T> *r, bool *found)
{
  NodoArbol<T> ret;
  *found = false;

  if (r->getRight() == nullptr)
  {
    *found = true;
    return r;
  }

  ret = findMaxAndRemove(r->getRight(), found);
  if (*found)
  {
    r->setRight(nullptr);
    *found = false;
  }

  return ret;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T>
bool ArbolBinario<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolBinario<T>::preorder()
{
  preorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::preorder(NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  std::cout << r->getData() << " ";
  preorder(r->getLeft());
  preorder(r->getRight());
}

/**
 * Recorre un árbol en orden
 */
template <class T>
void ArbolBinario<T>::inorder()
{
  inorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::inorder(NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  inorder(r->getLeft());
  std::cout << r->getData() << " ";
  inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T>
void ArbolBinario<T>::postorder()
{
  postorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::postorder(NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  postorder(r->getLeft());
  postorder(r->getRight());
  std::cout << r->getData() << " ";
}

/**
 * Muestra un árbol por consola
 */
template <class T>
void ArbolBinario<T>::print()
{
  if (root != NULL)
    root->print(false, "");
}

template <class T>
int ArbolBinario<T>::sumarDesdeNivel(int nivel)
{
  int suma=0;
  return sumarDesdeNivel(nivel, root, &suma);
}

template <class T>
int ArbolBinario<T>::sumarDesdeNivel(int nivel, NodoArbol<T> *r, int *total)
{

  if (nivel<=0){
    
    if( r!=nullptr ) {
      *total = *total + r->getData();
    }
  
  }

  if(r->getLeft()!=nullptr) { sumarDesdeNivel(nivel-1, r->getLeft(), total); }
  if(r->getRight()!=nullptr) { sumarDesdeNivel(nivel-1, r->getRight(), total); }
  
  return *total;
}

template <class T>
int ArbolBinario<T>::sumarNivel(int nivel)
{
  int suma=0;
  return sumarNivel(nivel, root, &suma);
}

template <class T>
int ArbolBinario<T>::sumarNivel(int nivel, NodoArbol<T> *r, int *total)
{

  if (nivel==0){
    
    if( r!=nullptr ) {
      *total = *total + r->getData();
    }
  
  }

  if(r->getLeft()!=nullptr) { sumarNivel(nivel-1, r->getLeft(), total); }
  if(r->getRight()!=nullptr) { sumarNivel(nivel-1, r->getRight(), total); }
  
  return *total;
}

template <class T>
int ArbolBinario<T>::LevelCounter()
{
  int levelCount = 0;
  int levelCatch = 0;
  return LevelCounter(root, levelCount, &levelCatch);
}

template <class T>
int ArbolBinario<T>::LevelCounter(NodoArbol<T> *r, int levelCount, int *levelCatch)
{

  if( *levelCatch<levelCount ) {
    *levelCatch= levelCount;
  }
  

  if(r->getLeft()!=nullptr) { LevelCounter(r->getLeft(), levelCount+1, levelCatch); }
  if(r->getRight()!=nullptr) { LevelCounter(r->getRight(), levelCount+1, levelCatch); }
  
  return *levelCatch;
}


template <class T>
int ArbolBinario<T>::sumarNivelPerValue(int value)
{
  int levelCatch=0;
  getLevelPerValue(value, &levelCatch);
  return sumarNivel(levelCatch);
}

template <class T>
int ArbolBinario<T>::getLevelPerValue(int value, int *levelCatch)
{
  int levelCount = 0;
  return getLevelPerValue(value, root, levelCount, levelCatch);
}

template <class T> 
int ArbolBinario<T>::getLevelPerValue(int value, NodoArbol<T> *r, int levelCount,int *levelCatch)
{
  if(r->getData()==value) {
    *levelCatch= levelCount;
    return *levelCatch;
  }

  if(r->getLeft()!=nullptr) { getLevelPerValue(value, r->getLeft(), levelCount+1, levelCatch); }
  if(r->getRight()!=nullptr) { getLevelPerValue(value, r->getRight(), levelCount+1, levelCatch); }
  
}

template <class T>
int ArbolBinario<T>::getLevel(T v){
  return getLevel(v, 0, root);
}

template <class T>
int ArbolBinario<T>::getLevel(T v, int currentLevel, NodoArbol<T> *r){
  if (r == nullptr){   //Si no se encuentra el nivel se devuelve excepción con valor 404
    throw 404;
  }

  if (r->getData() == v){
    return currentLevel;
  }

  if (r->getData() > v){ //Si el valor actual es mayor al del nodo se busca por la rama derecha.
    return getLevel(v, currentLevel + 1, r->getLeft());
  }
  else{ //De lo contrario el valor del nodo se busca por la rama izquierda.
    return getLevel(v, currentLevel + 1, r->getRight());
  }
}



#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_