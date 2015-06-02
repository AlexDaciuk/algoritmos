#include "Interfaz.h"

Interfaz::Interfaz()
{
  this->enlaces = NULL;
  this->centrales = NULL;
  this->lectorDeArchivos = NULL;
  this->procesadorLlamada = NULL;
}

void Interfaz::cambiarPunteroALectorDeArchivos(LectorArchivos* nuevoPuntero)
{
  this->lectorDeArchivos = nuevoPuntero;
}

std::string Interfaz::pedirRuta()
{
  std::string ruta;
  std::cout << "\n"
            << "Ingrese la ruta del archivo de llamadas:";
  std::cin >> ruta;
  return ruta;
}

void Interfaz::mostrarMenu()
{
  std::cout << "Bienvenido al sistema de informacion de la central telefonica.\n \n";
  std::cout << "A continuacion de detalla el menu:\n\n";
  std::cout << "1)Imprimir detalle de internos, nombres y números.\n";
  std::cout << "2)Imprimir detalle de centrales con su numeración.\n";
  std::cout << "3)Imprimir detalle de enlaces (origen, destino, canales). \n";
  std::cout << "4)Detalle de llamadas entre el interno 'X' de la central 'A' al interno 'Y' de la central 'B'.\n";
  std::cout << "5)Interno que mas hablo de todos y de cada central.\n";
  std::cout << "6)Interno que más llamó de todos y de cada central.\n";
  std::cout << "7)Interno que mas ocupados recibio de todos y de cada central.\n";
  std::cout << "8)Interno al que más llamaron de todos y de cada central.\n";
  std::cout << "9)Interno que mas gasto de todos y de cada central.\n";
  std::cout << "10)Interno al que más le hablaron de todos y de cada central.\n";
  std::cout << "11)Interno que más dio ocupado de todos y de cada central.\n";
  std::cout << "12)Detalle de llamadas emitidas por el interno X de la central A.\n";
  std::cout << "13)Detalle de llamadas recibidas por el interno X de la central A.\n";
  std::cout << "14)Detalle de llamadas realizadas de X de la central A a Y de la Central B.\n";
  std::cout << "15)Detalle de llamadas recibidas por X de la Central A y realizadas por Y de la Central B.\n";
  std::cout << "16)Imprimir cantidad de llamadas anuladas por falta de enlaces por central,ordenado por cantidad "
               "descendiente.\n";
  std::cout << "17)Salir. \n \n";
}

int Interfaz::pedirOpcionMenu()
{
  int opcion;
  std::cout << "Elija una opcion:";
  std::cin >> opcion;
  while (opcion < 1 || opcion > 17) {
    std::cout << "La opcion no existe. \n";
		std::cout << "Elija una opcion:";
		std::cin>>opcion;
		std::cout<<"\n";
  
  }

  return opcion;
}

int Interfaz::pedirInterno()
{
  int numeroInterno;
  std::cout << "Ingrese el numero de interno:";
  std::cin >> numeroInterno;
  std::cout << "\n";
  return numeroInterno;
}
std::string Interfaz::pedirAlgoritmoDeBusqueda()
{
  int opcion;
  std::string opcionAlgoritmo;
  std::cout << "Quiere usar algoritmo de: \n";
  std::cout << "1) Precio mas bajo \n";
  std::cout << "2) Distancia mas corta \n";
  std::cout << "Opcion:";
  std::cin >> opcion;
  switch (opcion) {
  case 1:
    opcionAlgoritmo = "Precio";
    break;

  case 2:
    opcionAlgoritmo = "Distancia";
    break;
  }
  std::cout << "\n";
  return opcionAlgoritmo;
}

Lista<Enlace*>* Interfaz::obtenerenlaces()
{
  return this->enlaces;
}
Lista<Central*>* Interfaz::obtenercentrales()
{
  return this->centrales;
}
void Interfaz::iniciarlizarPunteroAEnlaces(ProcesadorLlamada* procesadorDeLlamadas)
{
  this->enlaces = procesadorDeLlamadas->obtenerEnlaces();
}
void Interfaz::iniciarlizarPunteroACentrales(ProcesadorLlamada* procesadorDeLlamadas)
{
  this->centrales = procesadorDeLlamadas->obtenerCentrales();
}

void Interfaz::mostrarDetallesDeInternos()
{
  this->obtenercentrales()->iniciarCursorNodo();
  while (this->obtenercentrales()->avanzarCursorNodo()) {
    std::cout << "Internos de la central:" << this->obtenercentrales()->obtenerCursorNodo()->obtenerNumero() << ": \n";
    Lista<Interno*>* punteroAInternos = this->obtenercentrales()->obtenerCursorNodo()->obtenerInternos();
    punteroAInternos->iniciarCursorNodo();
    while (punteroAInternos->avanzarCursorNodo()) {
      std::cout << "Interno:" << punteroAInternos->obtenerCursorNodo()->obtenerNumero() << ". \n";
    }
    std::cout << "\n";
  }
}

void Interfaz::mostrarDetallesDeCentrales()
{
  std::cout << "A continuacion se indican los numeros de las centrales existentes: \n";
  this->obtenercentrales()->iniciarCursorNodo();
  while (this->obtenercentrales()->avanzarCursorNodo()) {
    std::cout << "Central numero:" << this->obtenercentrales()->obtenerCursorNodo()->obtenerNumero() << "\n";
  }
  std::cout << "\n";
}

void Interfaz::mostrarDetallesDeEnlaces()
{
  std::cout << "A continuacion se indican los dettalles de los enlaces existentes: \n";
  this->obtenerenlaces()->iniciarCursorNodo();
  int i = 0;
  while (this->obtenerenlaces()->avanzarCursorNodo()) {
    i++;
    std::cout << "Enlace " << i << ": \n";
    std::cout << "Central origen: " << obtenerenlaces()->obtenerCursorNodo()->obtenerOrigen()->obtenerNumero() << "\n";
    std::cout << "Central destino: " << obtenerenlaces()->obtenerCursorNodo()->obtenerDestino()->obtenerNumero()
              << "\n";
    std::cout << "Numero de canales: " << obtenerenlaces()->obtenerCursorNodo()->obtenerNumeroDeCanales() << "\n \n";
  }
}

int Interfaz::pedirCentral()
{
  int numeroDeCentral;
  std::cout << "Indique a que central pertenece:";
  std::cin >> numeroDeCentral;
  return numeroDeCentral;
}
void Interfaz::detallesLlamadasEntreInternoXDeLaCentralAYElInternoYDeLaCentralB()
{
  int primerInterno, centralPrimerInterno, segundoInterno, centralSegundoInterno;
  std::cout << "Ingrese el numero del primer interno:";
  std::cin >> primerInterno;
  centralPrimerInterno = pedirCentral();
  std::cout << "\n";
  std::cout << "Ingese el numero del segundo interno:";
  std::cin >> segundoInterno;
  centralSegundoInterno = pedirCentral();
  std::cout << "\n \n";
  Interno* DatosPrimerInterno = NULL;
  DatosPrimerInterno =
      obtenercentrales()->obtenerPunteroAlObjeto(centralPrimerInterno)->obtenerObjeto()->obtenerInterno(primerInterno);
  std::cout << "Detalles de llamadas entre el interno " << primerInterno << " de la central " << centralPrimerInterno;
  std::cout << " y " << segundoInterno << " de la central " << centralSegundoInterno << "\n";
  int numeroDeLlamadas = 0;
  int numeroDeOcupados = 0;
  int duracionDeLlamadas = 0;
  bool encontro = false;
  DatosPrimerInterno->obtenerLlamadas()->iniciarCursorNodo();
  while (DatosPrimerInterno->obtenerLlamadas()->avanzarCursorNodo() && !encontro) {
    if (DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerReceptorLlamada() == segundoInterno) {
      encontro = true;
      numeroDeLlamadas = DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerCantidadLlamadasHechas() +
                         DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerCantidadLlamadasRecibidas();
      numeroDeOcupados = DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerCantidadOcupadosDados() +
                         DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerCantidadOcupadosRecibidos();
      duracionDeLlamadas =
          DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerDuracionLlamadasHechas() +
          DatosPrimerInterno->obtenerLlamadas()->obtenerCursorNodo()->obtenerDuracionLlamadasRecibidas();
    }
  }
  std::cout << "Llamadas realizadas entre ambos:" << numeroDeLlamadas << "\n";
  std::cout << "Duracion total de llamadas entre ambos:" << duracionDeLlamadas << " minutos.\n";
  std::cout << "Cantidad de ocupados entre ambos:" << numeroDeOcupados << "\n \n";
}

int Interfaz::sumaDeDuracionDeLlamadas(Lista<Llamada*>* listaLlamadas)
{
  int duracionHechas = 0;
  int duracionRecibidas = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    duracionHechas += listaLlamadas->obtenerCursorNodo()->obtenerDuracionLlamadasHechas();
    duracionRecibidas += listaLlamadas->obtenerCursorNodo()->obtenerDuracionLlamadasRecibidas();
  }
  return (duracionHechas + duracionRecibidas);
}

void Interfaz::internoQueMasHabloEnUnaCentral(Lista<Interno*>* listaInternos,
                                              int& maximaDuracionEnLaCentral,
                                              int& internoQueMasHabloPorCentral)
{

  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int duracionPorInterno = 0;
    duracionPorInterno = sumaDeDuracionDeLlamadas(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (duracionPorInterno > maximaDuracionEnLaCentral) {
      internoQueMasHabloPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximaDuracionEnLaCentral = duracionPorInterno;
    }
  }
}

void Interfaz::internoQueMasHabloPorCentralYGeneral()
{
  int maximaDuracionGeneral = 0;
  int internoQueMasHabloPorCentral, internoQueMasHabloGeneral, centralQueMasHablo;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximaDuracionEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas hablo fue:";
    internoQueMasHabloEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                   maximaDuracionEnLaCentral,
                                   internoQueMasHabloPorCentral);
    std::cout << internoQueMasHabloPorCentral << "\n";
    if (maximaDuracionEnLaCentral > maximaDuracionGeneral) {
      centralQueMasHablo = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasHabloGeneral = internoQueMasHabloPorCentral;
      maximaDuracionGeneral = maximaDuracionEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas hablo de todos fue el interno " << internoQueMasHabloGeneral << " de la central "
            << centralQueMasHablo << ". \n";
}

int Interfaz::sumaDeLlamadasEmitidas(Lista<Llamada*>* listaLlamadas)
{
  int llamadas = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    llamadas += listaLlamadas->obtenerCursorNodo()->obtenerCantidadLlamadasHechas();
  }
  return llamadas;
}

void Interfaz::internoQueMasLlamoEnUnaCentral(Lista<Interno*>* listaInternos,
                                              int& maximoNumeroLLamadasEnLaCentral,
                                              int& internoQueMasLlamoPorCentral)
{

  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int llamadasPorInterno = 0;
    llamadasPorInterno = sumaDeLlamadasEmitidas(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (llamadasPorInterno > maximoNumeroLLamadasEnLaCentral) {
      internoQueMasLlamoPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximoNumeroLLamadasEnLaCentral = llamadasPorInterno;
    }
  }
}

void Interfaz::internoQueMasLlamoPorCentralYEnGeneral()
{
  int maximoNumeroLLamdadasGeneral = 0;
  int internoQueMasLlamoPorCentral, internoQueMasLlamoGeneral, centralQueMasLlamo;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximoNumeroLLamadasEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas llamo fue:";
    internoQueMasLlamoEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                   maximoNumeroLLamadasEnLaCentral,
                                   internoQueMasLlamoPorCentral);
    std::cout << internoQueMasLlamoPorCentral << "\n";
    if (maximoNumeroLLamadasEnLaCentral > maximoNumeroLLamdadasGeneral) {
      centralQueMasLlamo = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasLlamoGeneral = internoQueMasLlamoPorCentral;
      maximoNumeroLLamdadasGeneral = maximoNumeroLLamadasEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas llamo de todos fue el interno " << internoQueMasLlamoGeneral << " de la central "
            << centralQueMasLlamo << ". \n";
}

int Interfaz::sumaDeOcupadosRecibidos(Lista<Llamada*>* listaLlamadas)
{
  int ocupadosRecibidos = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    ocupadosRecibidos += listaLlamadas->obtenerCursorNodo()->obtenerCantidadOcupadosRecibidos();
  }
  return ocupadosRecibidos;
}

void Interfaz::internoQueMasOcupadosRecibioEnUnaCentral(Lista<Interno*>* listaInternos,
                                                        int& maximoNumeroOcupadosEnLaCentral,
                                                        int& internoQueMasRecibioOcupadosPorCentral)
{

  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int ocupadosRecibidosPorInterno = 0;
    ocupadosRecibidosPorInterno = sumaDeOcupadosRecibidos(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (ocupadosRecibidosPorInterno >= maximoNumeroOcupadosEnLaCentral) {
      internoQueMasRecibioOcupadosPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximoNumeroOcupadosEnLaCentral = ocupadosRecibidosPorInterno;
    }
  }
}

void Interfaz::internoQueMasOcupadosRecibioPorCentralYGeneral()
{
  int maximoNumeroDeOcupadosGeneral = 0;
  int internoQueMasRecibioOcupadosPorCentral, internoQueMasRecibioOcupadosGeneral, centralQueMasRecibioOcupados;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximoNumeroOcupadosEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas ocupados recibio fue:";
    internoQueMasOcupadosRecibioEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                             maximoNumeroOcupadosEnLaCentral,
                                             internoQueMasRecibioOcupadosPorCentral);
    std::cout << internoQueMasRecibioOcupadosPorCentral << "\n";
    if (maximoNumeroOcupadosEnLaCentral >= maximoNumeroDeOcupadosGeneral) {
      centralQueMasRecibioOcupados = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasRecibioOcupadosGeneral = internoQueMasRecibioOcupadosPorCentral;
      maximoNumeroDeOcupadosGeneral = maximoNumeroOcupadosEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas ocupados recibio de todos fue el interno " << internoQueMasRecibioOcupadosGeneral
            << " de la central " << centralQueMasRecibioOcupados << ". \n";
}

int Interfaz::sumaDeLlamadasRecibidas(Lista<Llamada*>* listaLlamadas)
{
  int llamadasRecibidas = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    llamadasRecibidas += listaLlamadas->obtenerCursorNodo()->obtenerCantidadLlamadasRecibidas();
  }
  return llamadasRecibidas;
}

void Interfaz::internoQueMasLlamadasRecibioEnUnaCentral(Lista<Interno*>* listaInternos,
                                                        int& maximoLlamadasRecibidasEnLaCentral,
                                                        int& internoQueMasLlamaronPorCentral)
{

  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int llamadasRecibidasPorInterno = 0;
    llamadasRecibidasPorInterno = sumaDeLlamadasRecibidas(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (llamadasRecibidasPorInterno > maximoLlamadasRecibidasEnLaCentral) {
      internoQueMasLlamaronPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximoLlamadasRecibidasEnLaCentral = llamadasRecibidasPorInterno;
    }
  }
}

void Interfaz::internoAlQueMasLlamaronPorCentralYGeneral()
{
  int maximoNumeroLlamadasRecibidasGeneral = 0;
  int internoQueMasLlamaronPorCentral, internoQueMasLlamaronGeneral, centralQueMasLlamadasRecibio;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximoLlamadasRecibidasEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas llamo fue:";
    internoQueMasLlamadasRecibioEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                             maximoLlamadasRecibidasEnLaCentral,
                                             internoQueMasLlamaronPorCentral);
    std::cout << internoQueMasLlamaronPorCentral << "\n";
    if (maximoLlamadasRecibidasEnLaCentral > maximoNumeroLlamadasRecibidasGeneral) {
      centralQueMasLlamadasRecibio = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasLlamaronGeneral = internoQueMasLlamaronPorCentral;
      maximoNumeroLlamadasRecibidasGeneral = maximoLlamadasRecibidasEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas llamadas recibio de todos fue el interno " << internoQueMasLlamaronGeneral
            << " de la central " << centralQueMasLlamadasRecibio << ". \n";
}

int Interfaz::sumaDeGastos(Lista<Llamada*>* listaLlamadas)
{
  int gastos = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    gastos += listaLlamadas->obtenerCursorNodo()->obtenerCostoLlamadas();
  }
  return gastos;
}

void Interfaz::internoQueMasGastoEnUnaCentral(Lista<Interno*>* listaInternos,
                                              int& maximoGastoEnLaCentral,
                                              int& internoQueMasGastoPorCentral)
{
  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int GastosPorInterno = 0;
    GastosPorInterno = sumaDeGastos(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (GastosPorInterno > maximoGastoEnLaCentral) {
      internoQueMasGastoPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximoGastoEnLaCentral = GastosPorInterno;
    }
  }
}

void Interfaz::internoQueMasGastoPorCentralYGeneral()
{
  int maximoGastoGeneral = 0;
  int internoQueMasGastoPorCentral, internoQueMasGastoGeneral, centralQueMasGasto;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximoGastoEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas llamo fue:";
    internoQueMasGastoEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                   maximoGastoEnLaCentral,
                                   internoQueMasGastoPorCentral);
    std::cout << internoQueMasGastoPorCentral << "\n";
    if (maximoGastoEnLaCentral > maximoGastoGeneral) {
      centralQueMasGasto = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasGastoGeneral = internoQueMasGastoPorCentral;
      maximoGastoGeneral = maximoGastoEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas gasto en llamadas de todos fue el interno " << internoQueMasGastoGeneral
            << " de la central " << centralQueMasGasto << ". \n";
}

int Interfaz::sumaDuracionDeRecibidas(Lista<Llamada*>* listaLlamadas)
{
  int duracionRecibidas = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    duracionRecibidas += listaLlamadas->obtenerCursorNodo()->obtenerDuracionLlamadasRecibidas();
  }
  return duracionRecibidas;
}

void Interfaz::internoQueMasLeHbalaronEnUnaCentral(Lista<Interno*>* listaInternos,
                                                   int& maximoInternoQueMasLeHablaronEnLaCentral,
                                                   int& internoQueMasHablaronPorCentral)
{

  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int duracionRecibidasPorInterno = 0;
    duracionRecibidasPorInterno = sumaDuracionDeRecibidas(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (duracionRecibidasPorInterno > maximoInternoQueMasLeHablaronEnLaCentral) {
      internoQueMasHablaronPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximoInternoQueMasLeHablaronEnLaCentral = duracionRecibidasPorInterno;
    }
  }
}

void Interfaz::internoAlQueMasLeHablaronPorCentralYGeneral()
{
  int maximoInternoQueMasLeHablaronEnGeneral = 0;
  int internoQueMasHablaronPorCentral, internoQueMasHablaronGeneral, centralQueMasHablaron;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximoInternoQueMasLeHablaronEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas llamo fue:";
    internoQueMasLeHbalaronEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                        maximoInternoQueMasLeHablaronEnLaCentral,
                                        internoQueMasHablaronPorCentral);
    std::cout << internoQueMasHablaronPorCentral << "\n";
    if (maximoInternoQueMasLeHablaronEnLaCentral > maximoInternoQueMasLeHablaronEnGeneral) {
      centralQueMasHablaron = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasHablaronGeneral = internoQueMasHablaronPorCentral;
      maximoInternoQueMasLeHablaronEnGeneral = maximoInternoQueMasLeHablaronEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas gasto en llamadas de todos fue el interno " << internoQueMasHablaronGeneral
            << " de la central " << centralQueMasHablaron << ". \n";
}

int Interfaz::sumaDeOcupadosDados(Lista<Llamada*>* listaLlamadas)
{
  int ocupados = 0;
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo()) {
    ocupados += listaLlamadas->obtenerCursorNodo()->obtenerCantidadOcupadosDados();
  }
  return ocupados;
}

void Interfaz::internoQueMasDioOcuapadoEnUnaCentral(Lista<Interno*>* listaInternos,
                                                    int& maximoNumeroDeOcupadosDadosEnLaCentral,
                                                    int& internoQueMasDioOcupadoPorCentral)
{
  listaInternos->iniciarCursorNodo();
  while (listaInternos->avanzarCursorNodo()) {
    int cantidadOcupadosDadosPorInterno = 0;
    cantidadOcupadosDadosPorInterno = sumaDeOcupadosDados(listaInternos->obtenerCursorNodo()->obtenerLlamadas());
    if (cantidadOcupadosDadosPorInterno >= maximoNumeroDeOcupadosDadosEnLaCentral) {
      internoQueMasDioOcupadoPorCentral = listaInternos->obtenerCursorNodo()->obtenerNumero();
      maximoNumeroDeOcupadosDadosEnLaCentral = cantidadOcupadosDadosPorInterno;
    }
  }
}

void Interfaz::internoQueMasDioOcupadoPorCentralYGeneral()
{
  int maximoNumeroDeOcupadosDadosEnGeneral = 0;
  int internoQueMasDioOcupadoPorCentral, internoQueMasDioOcupadoEnGeneral, centralQueMasDioOcuapdo;
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    int maximoNumeroDeOcupadosDadosEnLaCentral = 0;
    std::cout << "De la central " << obtenercentrales()->obtenerCursorNodo()->obtenerNumero()
              << " el interno que mas ocupados dio fue:";
    internoQueMasDioOcuapadoEnUnaCentral(obtenercentrales()->obtenerCursorNodo()->obtenerInternos(),
                                         maximoNumeroDeOcupadosDadosEnLaCentral,
                                         internoQueMasDioOcupadoPorCentral);
    std::cout << internoQueMasDioOcupadoPorCentral << "\n";
    if (maximoNumeroDeOcupadosDadosEnLaCentral >= maximoNumeroDeOcupadosDadosEnGeneral) {
      centralQueMasDioOcuapdo = obtenercentrales()->obtenerCursorNodo()->obtenerNumero();
      internoQueMasDioOcupadoEnGeneral = internoQueMasDioOcupadoPorCentral;
      maximoNumeroDeOcupadosDadosEnGeneral = maximoNumeroDeOcupadosDadosEnLaCentral;
    }
  }
  std::cout << "\n El interno que mas dio ocupados de todos fue el interno " << internoQueMasDioOcupadoEnGeneral
            << " de la central " << centralQueMasDioOcuapdo << ". \n";
}

void Interfaz::DetallesLlamadasEmitidasPorElInternoXDeLaCentralA()
{
	int interno = pedirInterno();
  int central = pedirCentral();
  Interno* internoPedido =
      obtenercentrales()->obtenerPunteroAlObjeto(central)->obtenerObjeto()->obtenerInterno(interno);
  std::cout << "Detalle de las llamadas emitidas por el interno " << interno << " de la central " << central << ".\n\n";
  internoPedido->obtenerLlamadas()->iniciarCursorNodo();
  while (internoPedido->obtenerLlamadas()->avanzarCursorNodo()) {
    std::cout << "Llamadas realizadas al interno:"
              << internoPedido->obtenerLlamadas()->obtenerCursorNodo()->obtenerReceptorLlamada() << ":\n";
    std::cout << "Duracion de las llamadas:"
              << internoPedido->obtenerLlamadas()->obtenerCursorNodo()->obtenerDuracionLlamadasHechas() << ".\n";
    std::cout << "Cantidad de ocupados recibidos:"
              << internoPedido->obtenerLlamadas()->obtenerCursorNodo()->obtenerCantidadOcupadosRecibidos() << ".\n\n";
  }
}

void Interfaz::DetallesLlamadasRecibidasPorElInternoXDeLaCentralA()
{
  int central = pedirCentral();
  int interno = pedirInterno();
  Interno* internoPedido =
      obtenercentrales()->obtenerPunteroAlObjeto(central)->obtenerObjeto()->obtenerInterno(interno);
  std::cout << "Detalle de las llamadas recibidas por el interno " << interno << " de la central " << central << ".\n";
  internoPedido->obtenerLlamadas()->iniciarCursorNodo();
  while (internoPedido->obtenerLlamadas()->avanzarCursorNodo()) {
    std::cout << "Llamadas recibidas del interno:"
              << internoPedido->obtenerLlamadas()->obtenerCursorNodo()->obtenerReceptorLlamada() << ":\n";
    std::cout << "Duracion de las llamadas:"
              << internoPedido->obtenerLlamadas()->obtenerCursorNodo()->obtenerDuracionLlamadasRecibidas() << ".\n";
    std::cout << "Cantidad de ocupados dados:"
              << internoPedido->obtenerLlamadas()->obtenerCursorNodo()->obtenerCantidadOcupadosDados() << ".\n";
  }
}

void Interfaz::DetalleDeLlamadasRealizadasPorXDeLaCentralAYRecibidasPorYDeLaCentralB()
{
  std::cout << "Emisor. \n";
  int emisor = pedirInterno();
  std::cout << "Central del emisor.\n";
  int numeroCentralEmisor = pedirCentral();
  std::cout << "Receptor. \n";
  int receptor = pedirInterno();
  std::cout << "Central del receptor.\n";
  int numeroCentralReceptor = pedirCentral();
  Central* centralEmisor = obtenercentrales()->obtenerPunteroAlObjeto(numeroCentralEmisor)->obtenerObjeto();
  Lista<Llamada*>* llamadasEmisor = centralEmisor->obtenerInterno(emisor)->obtenerLlamadas();
  llamadasEmisor->iniciarCursorNodo();
  bool estaElReceptor = false;
  while (llamadasEmisor->avanzarCursorNodo() && !estaElReceptor) {
    if (llamadasEmisor->obtenerCursorNodo()->obtenerReceptorLlamada() == receptor) {
      estaElReceptor = true;
    }
  }
  if (estaElReceptor) {
    std::cout << "Detalles de llamadas realizadas por " << emisor << " de la central " << numeroCentralEmisor << "\n";
    std::cout << "y recibidas por " << receptor << " de la central " << numeroCentralReceptor << ".\n";
    std::cout << "Llamadas realizadas:" << llamadasEmisor->obtenerCursorNodo()->obtenerCantidadLlamadasHechas()
              << ".\n";
    std::cout << "Duracion de las llamadas:" << llamadasEmisor->obtenerCursorNodo()->obtenerDuracionLlamadasHechas()
              << ".\n";
    std::cout << "Cantidad de ocupados recibidos:"
              << llamadasEmisor->obtenerCursorNodo()->obtenerCantidadOcupadosRecibidos() << ".\n";
  } else {
    std::cout << "No existen llamadas entre estos internos.\n";
  }
}

void Interfaz::DetalleDeLlamadasRecibidasPorXDeLaCentralAYRealizadasPorYDeLaCentralB()
{
  std::cout << "Emisor. \n";
  int emisor = pedirInterno();
  std::cout << "Central del emisor.\n";
  int numeroCentralEmisor = pedirCentral();
  std::cout << "Receptor. \n";
  int receptor = pedirInterno();
  std::cout << "Central del receptor.\n";
  int numeroCentralReceptor = pedirCentral();
  Central* centralEmisor = obtenercentrales()->obtenerPunteroAlObjeto(numeroCentralEmisor)->obtenerObjeto();
  Lista<Llamada*>* llamadasEmisor = centralEmisor->obtenerInterno(emisor)->obtenerLlamadas();
  llamadasEmisor->iniciarCursorNodo();
  bool estaElReceptor = false;
  while (llamadasEmisor->avanzarCursorNodo() && !estaElReceptor) {
    if (llamadasEmisor->obtenerCursorNodo()->obtenerReceptorLlamada() == receptor) {
      estaElReceptor = true;
    }
  }
  if (estaElReceptor) {
    std::cout << "Detalles de llamadas recibidas por " << receptor << " de la central " << numeroCentralReceptor
              << "\n";
    std::cout << "y realizadas por " << emisor << " de la central " << numeroCentralEmisor << ".\n";
    std::cout << "Llamadas realizadas:" << llamadasEmisor->obtenerCursorNodo()->obtenerCantidadLlamadasRecibidas()
              << ".\n";
    std::cout << "Duracion de las llamadas:" << llamadasEmisor->obtenerCursorNodo()->obtenerDuracionLlamadasRecibidas()
              << ".\n";
    std::cout << "Cantidad de ocupados recibidos:"
              << llamadasEmisor->obtenerCursorNodo()->obtenerCantidadOcupadosDados() << ".\n";
  } else {
    std::cout << "No existen llamadas entre estos internos.\n";
  }
}

void Interfaz::llamadasAnuladasPorFaltaDeEnlacesPorCentralOrdenadoDecrecientemente()
{
  int totalCentrales = 0;
  int totalLlamadasAnuladas = 0;
  int i = 0;
  Lista<Ordenar*>* ordenarCentrales = new Lista<Ordenar*>;
  std::cout << "Lista de centrales ordenadas decrecientemente por numero de llamadas anuladas:\n \n";
  obtenercentrales()->iniciarCursorNodo();
  while (obtenercentrales()->avanzarCursorNodo()) {
    totalCentrales++;
    Central* centralActual = obtenercentrales()->obtenerCursorNodo();
    totalLlamadasAnuladas = centralActual->obtenerTotalDeLlamadasAnuladasDeInternos(centralActual->obtenerInternos());
    Ordenar* nuevaCentral = new Ordenar(centralActual->obtenerNumero(), totalLlamadasAnuladas);
    ordenarCentrales->insertar(nuevaCentral);
  }
  ordenarCentrales->ordenarDecrecientemente(totalCentrales);
  ordenarCentrales->iniciarCursorNodo();
  while (ordenarCentrales->avanzarCursorNodo()) {
    i++;
    std::cout << i << ") Central numero:" << ordenarCentrales->obtenerCursorNodo()->obtenerNombreNumerico() << "\n";
    std::cout << "   Numero de llamadas anuladas:" << ordenarCentrales->obtenerCursorNodo()->obtenerValorAOrdenar()
              << "\n \n";
  }
}

void Interfaz::tratarOpcion(int opcion)
{
  bool continuar = true;
  while (continuar) {
    switch (opcion) {
    case 1:
      mostrarDetallesDeInternos();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 2:
      mostrarDetallesDeCentrales();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 3:
      mostrarDetallesDeEnlaces();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 4:
      detallesLlamadasEntreInternoXDeLaCentralAYElInternoYDeLaCentralB();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 5:
      internoQueMasHabloPorCentralYGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 6:
      internoQueMasLlamoPorCentralYEnGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 7:
      internoQueMasOcupadosRecibioPorCentralYGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 8:
      internoAlQueMasLlamaronPorCentralYGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 9:
      internoQueMasGastoPorCentralYGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 10:
      internoAlQueMasLeHablaronPorCentralYGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 11:
      internoQueMasDioOcupadoPorCentralYGeneral();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 12:
      DetallesLlamadasEmitidasPorElInternoXDeLaCentralA();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 13:
      DetallesLlamadasRecibidasPorElInternoXDeLaCentralA();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 14:
      DetalleDeLlamadasRealizadasPorXDeLaCentralAYRecibidasPorYDeLaCentralB();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 15:
      DetalleDeLlamadasRecibidasPorXDeLaCentralAYRealizadasPorYDeLaCentralB();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 16:
      llamadasAnuladasPorFaltaDeEnlacesPorCentralOrdenadoDecrecientemente();
      realizarOtraConsulta(opcion, continuar);
      break;

    case 17:
      continuar = false;
      std::cout << "\n";
      std::cout << "Hasta luego. \n";
      break;
    }
  }
}
void Interfaz::realizarOtraConsulta(int& opcion, bool& continuar)
{
  char respuesta;
  std::cout << "Desea realizar otra consulta? [s/n]:";
  std::cin >> respuesta;
  if (respuesta == 's') {
    continuar = true;
    std::cout << "\n";
    mostrarMenu();
    opcion = pedirOpcionMenu();
  } else {
    continuar = false;
    std::cout << "\n";
    std::cout << "Hasta luego.\n \n";
  }
}
void Interfaz::iniciarPrograma()
{
  std::string ruta = pedirRuta();
  std::cout << "\n";
  std::cout << "La ruta es " << ruta << "\n\n";
  LectorArchivos* lectorArchivos = new LectorArchivos(ruta);
  this->cambiarPunteroALectorDeArchivos(lectorArchivos);

  std::string variableDeBusqueda = pedirAlgoritmoDeBusqueda();

  procesadorLlamada = new ProcesadorLlamada(lectorDeArchivos, variableDeBusqueda);
  procesadorLlamada->procesarLlamadas();

  this->iniciarlizarPunteroACentrales(procesadorLlamada);
  this->iniciarlizarPunteroAEnlaces(procesadorLlamada);
	
	obtenercentrales()->iniciarCursorNodo();
	while (obtenercentrales()->avanzarCursorNodo())
	{
		std::cout<<"central "<<obtenercentrales()->obtenerCursorNodo()->obtenerNumero() <<"\n";
			Lista<Interno*>* Internos = obtenercentrales()->obtenerCursorNodo()->obtenerInternos();
			Internos->iniciarCursorNodo();
			while (Internos->avanzarCursorNodo())
			{
				std::cout<<"interno "<<Internos->obtenerCursorNodo()->obtenerNumero()<<"\n";
				Lista<Llamada*>* Llamadas = Internos->obtenerCursorNodo()->obtenerLlamadas();
				while (Llamadas->avanzarCursorNodo())
				{
					std::cout<<"receptor:"<<Llamadas->obtenerCursorNodo()->obtenerReceptorLlamada()<<"\n";
					std::cout<<"llamadas hechas:"<<Llamadas->obtenerCursorNodo()->obtenerCantidadLlamadasHechas()<<"\n";
					std::cout<<"llamadas recibidas:"<<Llamadas->obtenerCursorNodo()->obtenerCantidadLlamadasRecibidas()<<"\n";
					std::cout<<"Ocupados:"<<Llamadas->obtenerCursorNodo()->obtenerCantidadOcupadosDados()+Llamadas->obtenerCursorNodo()->obtenerCantidadOcupadosRecibidos()<<"\n";
					std::cout<<"Duracion hechas:"<<Llamadas->obtenerCursorNodo()->obtenerDuracionLlamadasHechas()<<"\n";
					std::cout<<"Duracion recibidas:"<<Llamadas->obtenerCursorNodo()->obtenerDuracionLlamadasRecibidas()<<"\n\n";
				}
			}
		}
	
  mostrarMenu();
  int opcion = pedirOpcionMenu();
  tratarOpcion(opcion);
}
