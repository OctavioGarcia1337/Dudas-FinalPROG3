#ifndef U03_PILAS_PILA_PILA_H_
#define U03_PILAS_PILA_PILA_H_

#include "nodo.h"

/**
 * Clase que implementa una Pila generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Pila {
private:
  Nodo<T> *topNode;
public:
  Pila();

  ~Pila();

  void push(T dato);

  T pop();

  bool esVacia();
};

/**
 * Constructor de la clase Pila
 * @tparam T
 */
template <class T> Pila<T>::Pila() {
  topNode = nullptr;
}

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Pila<T>::~Pila() {
  while( topNode != nullptr ){
    pop();
  }
}

/**
 * Inserta un dato en la pila
 * @tparam T
 * @param dato  dato a insertar
 */
template <class T> void Pila<T>::push(T dato) {

  Nodo<T> *newNode = new Nodo<T>;
  newNode->setDato( dato );
  newNode->setSiguiente( topNode );
  topNode = newNode;

}

/**
 * Obtener el dato de la pila
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T> T Pila<T>::pop() {
  T data;
  Nodo<T> *toErase = topNode;

  if( topNode == nullptr ){
    throw 404;
  }

  data = topNode->getDato();
  topNode = topNode->getSiguiente();

  delete toErase;
  return data;
}

/**
 * Responde si la pila se encuentra Vacía
 * @tparam T
 * @return
 */
template <class T> bool Pila<T>::esVacia() {
  return topNode == nullptr;
}

#endif // U03_PILAS_PILA_PILA_H_
