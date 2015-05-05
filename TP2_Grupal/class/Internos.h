#ifndef INTERNOS_H
#define INTERNOS_H
#include "Llamada.h"
#include <iostream>
#include <cstddef> 
/**
 *Clase que define a cada interno de una central
 */

class Interno
{
 private:
  int numeroInterno;
  Llamada* punteroASusLlammadas;
 public:

  /**
   * Constructor de la clase Interno
   * Post: Queda creado el interno con el numero asignado
   */
  
  Interno(int numeroInternoTmp);

  int obtenerNumeroInterno();

  Llamada* agregarLlamada();
};

#endif
