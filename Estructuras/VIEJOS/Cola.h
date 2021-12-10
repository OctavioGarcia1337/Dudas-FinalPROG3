#ifndef U04_COLAS_COLA_COLA_H_
#define U04_COLAS_COLA_COLA_H_

#include "nodo.h"

/**
 * Clase que implementa una Cola generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Cola {
private:
  Nodo<T> *topNode, *bottomNode;
public:
  Cola();

  ~Cola();

  void encolar(T dato);

  T desencolar();

  bool esVacia();
};

/**
 * Constructor de la clase Cola
 * @tparam T
 */
template <class T> Cola<T>::Cola() {
  topNode = nullptr;
  bottomNode = nullptr;
}

/**
 * Destructor de la clase Cola, se encarga de liberar la memoria de todos los
 * nodos utilizados en la Cola
 * @tparam T
 */
template <class T> Cola<T>::~Cola() {
  while( !esVacia() ){
    desencolar();
  }
}

/**
 * Inserta un dato en la Cola
 * @tparam T
 * @param dato  dato a insertar
 */
template <class T> void Cola<T>::encolar(T dato) {
  Nodo<T> *newNode = new Nodo<T>();
  newNode->setDato( dato );
  newNode->setSiguiente(nullptr);

  if( bottomNode == nullptr ){
    topNode = newNode;
  }else{
    bottomNode->setSiguiente(newNode);
  }

  bottomNode = newNode;

}

/**
 * Obtener el dato de la Cola
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T> T Cola<T>::desencolar() {
  T aux;
  Nodo<T> *toErase;

  if(bottomNode == nullptr){
    throw 404;
  }

  aux = topNode->getDato();
  toErase = topNode;
  topNode = topNode->getSiguiente();

  if( topNode == nullptr){
    bottomNode = nullptr;
  }

  delete toErase;
  return aux;
}

/**
 * Responde si la Cola se encuentra Vacía
 * @tparam T
 * @return
 */
template <class T> bool Cola<T>::esVacia() {
  return bottomNode == nullptr;
}

#endif // U04_COLAS_COLA_COLA_H_
