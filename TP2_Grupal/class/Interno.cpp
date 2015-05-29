ProcesadorLlamadaes#include "Interno.h"

Interno::Interno(int numeroInternoTemporal)
{
	this->numeroInterno = numeroInternoTemporal;
	Lista<Llamada*>* llamadas= new Lista<Llamada*>*;
	this->estaOcupado=false;
};

int Internos::obtenerNumero()
{
	return (this->numeroInterno);
};

Lista<Llamada*>* Interno::obtenerLlamadas()
{
	return (this->llamadas);
};

Lista<Enlace*>* Interno::devolverRecorridoLlamada(int emisorLlamadaTemporal, int receptorLlamadaTemporal)
{
	Llamada* llamadaTemporal = NULL;
	bool encontreLlamada = false;
	this->llamadas->iniciarCursorNodo();

	while ( this->llamadas->avanzarCursorNodo() && ! encontreLlamada) {
		llamadaTemporal = this->obtenerCursorNodo();
		encontreLlamada = llamadaTemporal->obtenerReceptorLlamada() == receptorLlamadaTemporal;
	}

	return llamadaTemporal->obtenerRecorridoLlamada();
}


bool Interno::internoOcupado()
{
	return (this->estaOcupado);
};

Llamada* Interno::creaReceptorLlamada(int receptorLlamadaTemporal)
{
	bool existeLlamada = false;
	Llamada* llamadaTemporal = NULL;
	this->llamadas->iniciarCursorNodo();

	while ( this->llamadas->avanzarCursorNodo() && ! existeLlamada) {
		llamadaTemporal = this->obtenerCursorNodo();
		existeLlamada = llamadaTemporal->obtenerReceptorLlamada() == receptorLlamadaTemporal;
	}

	if (! existeLlamada) {
		Llamada* nuevaLlamada = new Llamada(receptorLlamadaTemporal);
		llamadaTemporal = nuevaLlamada;
		llamadasTemporal->insertar(nuevaLlamada);
	}

	return llamadaTemporal;
};

void Interno::agregarLlamadaEmisor(int receptorTemporal, int horaTemporal, Interno* receptor, Lista<Enlace*>* recorridoLlamadaTemporal )
{
	// Me fijo si la llamada esta creada, sino, la creo
	Llamada* llamadaTemporal = creaReceptorLlamada(receptorLlamadaTemporal);


	if (! receptor->internoOcupado()) {
		llamadaTemporal->empezarLlamadaEmisor(horaInicioLlamadaEnCursoTemporal, recorridoLlamadaTemporal);
	} else {
		// Si recibio un ocupado, pongo la hora de inicio en 0, asi puedo diferenciar
		// ocupados en el metodo de terminar llamadas
		llamadaTemporal->empezarLlamadaEmisor(0, recorridoLlamadaTemporal);
		llamadaTemporal->agregarOcupadoRecibido();
	}

}

void Interno::agregarLlamadaReceptor(int emisorTemporal, int horaTemporal, Lista<Enlace*>* recorridoLlamadaTemporal )
{
	// Me fijo si la llamada con el receptor esta creada, sino, la creo
	Llamada* llamadaTemporal = creaReceptorLlamada(receptorLlamadaTemporal);

	//Consigo un puntero al receptor, para ver si esta ocupado

	if (! this->internoOcupado()) {
		llamadaTemporal->empezarLlamadaReceptor(horaInicioLlamadaEnCursoTemporal);
	} else {
		// Si dio un ocupado, pongo la hora de inicio en 0, asi puedo diferenciar
		// ocupados en el metodo de terminar llamadas
		llamadaTemporal->empezarLlamada(0, recorridoLlamadaTemporal);
		llamadaTemporal->agregarOcupadoDado();

	}
}

void Interno::terminarLlamadaEmisor(int receptorTemporal, int horaTemporal, int precioMinutoTemporal )
{
	// Busco la llamada
	this->llamadas->iniciarCursorNodo();
	bool encontroLlamada = false;
	Llamada* llamadaTemporal = NULL;

	while(this->llamadas->avanzarCursorNodo() && ! encontroLlamada) {
		llamadaTemporal = this->llamadas->obtenerCursorNodo();
		encontroLlamada = llamadaTemporal->obtenerReceptorLlamada() == receptorTemporal;
	}

	llamadaTemporal->terminarLlamadaEmisor(horaTemporal);
	this->estaOcupado = false;
}

void Interno::terminarLlamadaReceptor(int emisorTemporal, int horaTemporal, int precioMinutoTemporal )
{
	// Busco la llamada
	this->llamadas->iniciarCursorNodo();
	bool encontroLlamada = false;
	Llamada* llamadaTemporal = NULL;

	while(this->llamadas->avanzarCursorNodo() && ! encontroLlamada) {
		llamadaTemporal = this->llamadas->obtenerCursorNodo();
		encontroLlamada = llamadaTemporal->obtenerReceptorLlamada() == emisorTemporal;
	}

	llamadaTemporal->terminarLlamadaReceptor(horaTemporal);
	this->estaOcupado = false;
}

int Interno::contarLlamadasAnuladas(Lista<Llamada*>* listaLlamadas)
{
  int llamadasAnuladas
  listaLlamadas->iniciarCursorNodo();
  while (listaLlamadas->avanzarCursorNodo())
  {
    llamadasAnuladas += listaLlamadas->obtenerCursorNodo()->obtenerLlamadasAnuladas();
  }
}
