#ifndef NODO_H
#define NODO_H
#define NULL 0
#include <iostream>

template <class T>
class Nodo<T>
{
  private:
    T objeto;
    Nodo<T>* nodoSiguiente;
    Nodo<T>* nodoArnterior;
  public:
  /**
 *Clase que define a cada nodo de una lista simple
 */
    Nodo<T>(T objeto);
    void cambiarNodoSiguiente(Nodo<T>* nodoSiguiente);
    void cambiarNodoAnterior(Nodo<T>* nodoArnterior);
    void cambiarObjeto(T objeto);
    Nodo<T>* obtenerSiguiente();
    Nodo<T>* obtenerAnterior();
    T obtenerObjeto();
};

template <class T>
Nodo<T>::Nodo(T objeto)
{
  this-> objeto= objeto;
  this-> nodoSiguiente= NULL;
};

template <class T>
void Nodo<T>::cambiarNodoSiguiente(Nodo<T>* nodoSiguiente)
{
  this->nodoSiguiente=nodoSiguiente;
};

template <class T>
void cambiarNodoAnterior(Nodo<T>* nodoArnterior)
{
  this->nodoArnterior=nodoArnterior;
};

template <class T>
Nodo<T>* Nodo<T>::obtenerSiguiente()
{
  return nodoSiguiente;
};

template <class T>
Nodo<T>* Nodo<T>::obtenerAnterior()
{
  return nodoArnterior;
};


template <class T>
T Nodo<T>::obtenerObjeto()
{
  return objeto;
};

template <class T>
void Nodo<T>::cambiarObjeto(T objeto)
{
  this->objeto=objeto;
};

#endif
