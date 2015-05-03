#ifndef INTERNOS_H
#define INTERNOS_H
#include <iostream>
#include <cstddef> 
/**
 *Clase que define a cada interno de una central
 */

class Interno
{
 private:
  int numeroInterno;
  //*Llamada* punteroASusLlammadas;
  Interno* internoSiguiente;
 public:

  /**
   * Constructor de la clase Interno
   * Post: Queda creado el interno con el numero asignado
   */
  
  Interno(int numeroInternoTmp);

  int obtenerNumeroInterno();
  
  void cambiarInternoSiguiente(Interno* nuevoSiguiente);

  Interno* obtenerInternoSiguiente();
    
  //*Llamada* agregarLlamada();
};

#endif
